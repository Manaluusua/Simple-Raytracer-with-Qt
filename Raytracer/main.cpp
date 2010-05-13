#include <QtGui/QApplication>
#include "renderwindow.h"




#include <QDebug>
#include "plane.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RenderWindow w;
    w.show();
    return a.exec();
}


