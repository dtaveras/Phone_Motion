#include "glwindow.h"
#include <GL/freeglut.h>
#include <QDebug>
#include <QKeyEvent>
#include <ostream>
#include <iostream>
#include <fstream>
#include <stdio.h>

#define ROT_RATE 1.0
#define TRANS_RATE 1.0
//#define DBG
GLWindow::GLWindow(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer.start(16);

}

void GLWindow::initializeGL()
{
#ifdef DBG
  qDebug() << "initializeGL";
#endif
  std::string arm1file("/Users/delvistaveras/Desktop/Build_18/Phone_Motion/models/lowerArm.obj");
  std::string arm2file("/Users/delvistaveras/Desktop/Build_18/Phone_Motion/models/upperArm.obj");
  lowerArm.filename = arm1file;
  upperArm.filename = arm2file;
  if(!lowerArm.load() || !upperArm.load()){
      exit(0);
  }
  x_angle = 0.0;
  y_angle = 0.0;
  z_angle = 0.0;
  x_trans = 0.0;
  y_trans = 0.0;
  rot = 0.0;
  rot2 = 0.0;
  start = 0;
  change_switch = 0;
  glClearColor(0.0,0.0,0.0,0.0);
}

void GLWindow::drawCube()
{
    glBegin(GL_QUADS);
    glColor3f(1,0,0);
    glVertex3f(-1,-1,-1);
    glVertex3f( 1,-1,-1);
    glVertex3f( 1, 1,-1);
    glVertex3f(-1, 1,-1);
    glColor3f(0,1,0);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1,-1);
    glColor3f(0,0,1);
    glVertex3f( 1,-1, 1);
    glVertex3f( 1,-1,-1);
    glVertex3f( 1, 1,-1);
    glVertex3f( 1, 1, 1);
    glColor3f(1,1,0);
    glVertex3f(-1,-1,-1);
    glVertex3f( 1,-1,-1);
    glVertex3f( 1,-1, 1);
    glVertex3f(-1,-1, 1);
    glColor3f(0,1,1);
    glVertex3f(-1,-1, 1);
    glVertex3f( 1,-1, 1);
    glVertex3f( 1, 1, 1);
    glVertex3f(-1, 1, 1);
    glColor3f(1,1,1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1,-1);
    glVertex3f( 1, 1,-1);
    glVertex3f( 1, 1, 1);
    glEnd();
}

void printVector(char* name, Leap::Vector vect){
    std::cout << name;
    std::cout << "X: " << vect.x << "Y: " << vect.y << "Z: " << vect.z << std::endl;
}

void GLWindow::drawMesh(Mesh* msh)
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_TRIANGLES);
    Leap::Vector tmp_tri0;
    for(unsigned int i=0; i< msh->triangles.size(); i++){
        tmp_tri0.x = msh->triangles[i].vertices[0];
        tmp_tri0.y = msh->triangles[i].vertices[1];
        tmp_tri0.z = msh->triangles[i].vertices[2];

        glVertex3f(msh->vertices[tmp_tri0.x].position[0],
                msh->vertices[tmp_tri0.x].position[1],
                msh->vertices[tmp_tri0.x].position[2]);
        glVertex3f(msh->vertices[tmp_tri0.y].position[0],
                msh->vertices[tmp_tri0.y].position[1],
                msh->vertices[tmp_tri0.y].position[2]);
        glVertex3f(msh->vertices[tmp_tri0.z].position[0],
                msh->vertices[tmp_tri0.z].position[1],
                msh->vertices[tmp_tri0.z].position[2]);
    }
    glEnd();
}

void GLWindow::drawAxis()
{
    glBegin(GL_LINES);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.0,-10.0,0.0);
    glVertex3f(0.0,10.0,0.0);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(-10.0,0.0,0.0);
    glVertex3f(10.0, 0.0,0.0);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.0,0.0,-10.0);
    glVertex3f(0.0,0.0,10.0);
    glEnd();
}

void GLWindow::keyPressEvent(QKeyEvent *kEvent)
{
    switch (kEvent->key()) {
        case Qt::Key_A:
            y_angle-= ROT_RATE;
        break;
        case Qt::Key_D:
            y_angle+= ROT_RATE;
        break;
        case Qt::Key_W:
            x_angle-= ROT_RATE;
        break;
        case Qt::Key_S:
            x_angle+= ROT_RATE;
        break;
        case Qt::Key_Q:
            z_angle-= ROT_RATE;
        break;
        case Qt::Key_E:
            z_angle+= ROT_RATE;
        break;
        case Qt::Key_Up:
            y_trans+= 1.0;
        break;
        case Qt::Key_Down:
            y_trans-= 1.0;
        break;
        case Qt::Key_Left:
            x_trans-= 1.0;
        break;
        case Qt::Key_Right:
            x_trans+= 1.0;
        break;
        case Qt::Key_R:
            z_trans+= 1.0;
        break;
        case Qt::Key_F:
            z_trans-= 1.0;
        break;
        case Qt::Key_M:
            rot-=1.0;
        break;
        case Qt::Key_N:
            rot+=1.0;
        break;
        case Qt::Key_H:
            rot2+=1.0;
        break;
        case Qt::Key_J:
            rot2-=1.0;
        break;
        case Qt::Key_Space:
            if(change_switch == 0){
                change_switch = 1;
            }
            else{
                change_switch = 0;
            }
        break;
     }
}

void GLWindow::sendToArdunio(char input)
{
    FILE* ardOutput;
    ardOutput = fopen("/dev/cu.usbmodem411", "w");
    if(ardOutput == NULL)
      perror("Error Ardunio not Connected");
    else
      {
        putc(input,ardOutput);
        fclose(ardOutput);
      }
}

void GLWindow::paintGL()
{
#ifdef DBG
  qDebug() << "paintGL";
#endif
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  Leap::HandList Hands = LeapFrame.hands();
  if(Hands.count() !=0)
    {
#ifdef DBG
      std::cout << "I SEE ONE HAND" << std::endl;
#endif

      Leap::Hand hand1 = Hands[0];
      Leap::Vector hpos = hand1.palmPosition();
      Leap::Finger middle_finger = hand1.fingers().frontmost();
      //std::cout << "Middle finger: " << middle_finger.tipPosition() << std::endl;
      if(change_switch == 0){
      float dist = hpos.y - middle_finger.tipPosition().y;
      if(dist < -12){
          //std::cout << "UPPPPPPP" << std::endl;
          this->sendToArdunio('a');
      }
      else if(dist > 12){
          //std::cout << "DOwnNnnn" << std::endl;
          this->sendToArdunio('c');
      }
      else{
          this->sendToArdunio('b');
      }
        }

      if(change_switch == 1){
      if(start== 1){
        float rot_angl = hand1.rotationAngle(prevFrame, Leap::Vector::xAxis());
        this->prevFrame = LeapFrame;
        float pi = 3.14;
        rot_angl = (rot_angl*180.0)/pi;
        if(hand1.palmPosition().x < -40){
        rot-= rot_angl;
        }
        //std::cout << "ROTATION ANGLE " << rot_angl << std::endl;
        float diff_pos = prevHeight-hpos.y;
        if(hand1.palmPosition().x > 40){
        rot2-= diff_pos*1.5;
        }
        this->prevHeight = hpos.y;
      }
      else if(start == 0){
          start = 1;
          this->prevFrame = LeapFrame;
          this->prevHeight = hpos.y;
      }

      hpos.y -= 140.0;
      //printVector("HPos", hpos);
      glColor3f(1.0,1.0,0.0);
      glPointSize(10.0);

      glPushMatrix();
      glTranslatef(0.0, 0.0, -20.0);
      glBegin(GL_POINTS);
      glVertex3f(0.0,0.0,0.0);
      glColor3f(0.0,0.0,1.0);
      glVertex3f(hpos.x,hpos.y,0);
      glEnd();
      glPopMatrix();
      }
   }

  //Draw Axis
#ifdef DBG
  std::cout << "x_angle " << x_angle << std::endl;
  std::cout << x_trans << std::endl;
#endif
  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(x_trans, y_trans, z_trans, 0.0, 0.0, -10.0, 0.0, 1.0, 0.0);

  glRotatef(x_angle,1.0,0.0,0.0);
  glRotatef(y_angle,0.0,1.0,0.0);
  glRotatef(z_angle,0.0,0.0,1.0);
  glPushMatrix();
  drawAxis();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,0.0,-100.0);
  glRotatef(90,0.0,1.0,0.0);

  //glPushMatrix();
  glColor3f(1.0,1.0,0.0);
  glTranslatef(120,0.0,0.0);
  glRotatef(rot2+180,0.0,0.0,1.0);
  drawMesh(&lowerArm);
  //glPopMatrix();

  glPushMatrix();
  glColor3f(0.0,0.0,1.0);
  glTranslatef(130,0.0,0.0);
  glRotatef(rot-180,0.0,0.0,1.0);
  drawMesh(&upperArm);
  glPopMatrix();

  glPopMatrix();

  glPopMatrix();
}

void GLWindow::resizeGL(int w, int h)
{
#ifdef DBG
  qDebug() << "resizeGL";
#endif

  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 0.1, 1000.0);
  //glOrtho(-100, 100, -100, 100,0.1, 1000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0, 0.2, 0.0, 0.0, -10.0, 0.0, 1.0, 0.0);
}
