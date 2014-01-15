#include "mainwindow.h"
#include "glwindow.h"
#include "leapcontroller.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QBoxLayout>
#include <QDebug>
#include <QFrame>
#include <QMenuBar>
#include <QTranslator>
#include <QStatusBar>
#include <QSplitter>
#include <GL/glut.h>

#define W_SC 1.0
#define H_SC 0.88


int main(int argc, char *argv[])
{    
    glutInit(&argc, argv);
    QApplication app(argc, argv);
    QDesktopWidget dw;
    QWidget* window = new QWidget;

    LeapController leapController;

    window->setWindowTitle("Phone Motion");
    window->setMinimumSize(QSize(dw.width()*W_SC,dw.height()*H_SC));
    window->setStyleSheet("background-color: #353439");

    QFrame* lFrame = new QFrame;
    GLWindow* rGLWindow = new GLWindow;
    lFrame->setMinimumWidth(150);
    lFrame->setStyleSheet("background-color: #353439");
    rGLWindow->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    QHBoxLayout* windLayout = new QHBoxLayout;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QBoxLayout* sideLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    QString widgetStyle = "background-color: #404143; \
                     border-top-left-radius: 10px;\
                     border-top-right-radius: 10px;\
                     border-bottom-left-radius: 10px;\
                     border-bottom-right-radius: 10px;";
    QFrame* widget1 = new QFrame;
    widget1->setMaximumHeight(100);
    widget1->setStyleSheet(widgetStyle);

    QFrame* widget2 = new QFrame;
    widget2->setMaximumHeight(100);
    widget2->setStyleSheet(widgetStyle);

    QFrame* widget3 = new QFrame;
    widget3->setMaximumHeight(100);
    widget3->setStyleSheet(widgetStyle);

    QFrame* widget4 = new QFrame;
    widget4->setMaximumHeight(100);
    widget4->setStyleSheet(widgetStyle);

    sideLayout->addWidget(widget1);
    sideLayout->addWidget(widget2);
    sideLayout->addWidget(widget3);
    sideLayout->addWidget(widget4);

    sideLayout->setContentsMargins(5,0,5,0);
    //sideLayout->setSpacing(0);
    lFrame->setLayout(sideLayout);
    //Add MenuBar
    QMenuBar *menuBar = new QMenuBar(0);
    menuBar->addMenu(QObject::tr("&File"));
    windLayout->setMenuBar(menuBar);

    QFrame* statusBar = new QFrame;
    statusBar->setStyleSheet("background-color: #404143; border-style: outset;\
                             border-top-left-radius: 5px;\
                             border-top-right-radius: 5px;");
    statusBar->setMaximumHeight(22);

    //Change layout spacing to have no margins
    windLayout->setSpacing(5);
    windLayout->setContentsMargins(5,10,10,10);

    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    //add the widgets to the layout
    windLayout->addWidget(lFrame);
    windLayout->addWidget(rGLWindow);

    mainLayout->addLayout(windLayout);
    mainLayout->addWidget(statusBar);
    window->setLayout(mainLayout);

    window->showFullScreen();
    return app.exec();
}
