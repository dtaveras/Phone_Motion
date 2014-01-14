#include "mainwindow.h"
#include "glwindow.h"
#include "leapcontroller.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QDebug>
#include <QFrame>
#include <QMenuBar>
#include <QTranslator>
#include <GL/glut.h>

#define W_SC 1.0
#define H_SC 0.88


int main(int argc, char *argv[])
{    
    glutInit(&argc, argv);
    QApplication app(argc, argv);
    QCoreApplication* qapp = QApplication::instance();
    QDesktopWidget dw;
    QWidget* window = new QWidget;

    LeapController leapController;

    window->setWindowTitle("Phone Motion");
    window->setMinimumSize(QSize(dw.width()*W_SC,dw.height()*H_SC));

    QFrame* lFrame = new QFrame;
    GLWindow* rGLWindow = new GLWindow;
    QPalette lpalette = lFrame->palette();

    lpalette.setColor(QPalette::Window, QColor( 0, 0, 255 ));
    lFrame->setPalette(lpalette);
    lFrame->setAutoFillBackground(true);
    lFrame->setMinimumWidth(150);

    rGLWindow->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    QHBoxLayout* windLayout = new QHBoxLayout;

    //Add MenuBar
    QMenuBar *menuBar = new QMenuBar(0);
    menuBar->addMenu(QObject::tr("&File"));
    windLayout->setMenuBar(menuBar);

    //Change layout spacing to have no margins
    windLayout->setSpacing(0);
    windLayout->setMargin(1);

    //add the widgets to the layout
    windLayout->addWidget(lFrame);
    windLayout->addWidget(rGLWindow);
    window->setLayout(windLayout);
    window->show();
    return app.exec();
}
