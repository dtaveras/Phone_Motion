#include "glwindow.h"
#include <GL/freeglut.h>
#include <QDebug>

GLWindow::GLWindow(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer.start(16);
    angle = 0.0;
}

void GLWindow::initializeGL()
{
  qDebug() << "initializeGL";
  glClearColor(0.0,0.0,0.0,0.0);
}

void GLWindow::paintGL()
{
  qDebug() << "paintGL";
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  angle += 0.1;
  glPushMatrix();
  glTranslatef(0.0,0.0,-5.0);
  glRotatef(angle,0.0,1.0,0.0);
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
  glPopMatrix();
}

void GLWindow::resizeGL(int w, int h)
{
  qDebug() << "resizeGL";
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
