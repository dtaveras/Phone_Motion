#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QGLWidget>
#include <QTimer>
#include "Leap.h"
#include "mesh.hpp"
using namespace _462;

class GLWindow : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWindow(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    QTimer timer;
    float x_angle;
    float y_angle;
    float z_angle;
    float x_trans;
    float y_trans;
    float z_trans;
    float rot;
    float rot2;
    int start;
    Leap::Frame LeapFrame;
    Leap::Frame prevFrame;
    float prevHeight;
    void keyPressEvent(QKeyEvent* key);
    int change_switch;
 private:
    void sendToArdunio(char input);
    void drawMesh(Mesh* msh);
    void drawAxis();
    void drawCube();
    Mesh lowerArm;
    Mesh upperArm;

};

#endif // GLWINDOW_H
