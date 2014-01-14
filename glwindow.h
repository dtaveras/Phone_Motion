#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QGLWidget>
#include <QTimer>

class GLWindow : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWindow(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    QTimer timer;
    float angle;
};

#endif // GLWINDOW_H
