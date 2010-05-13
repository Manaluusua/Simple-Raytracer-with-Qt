/********************************************************************************
** Form generated from reading UI file 'renderwindow.ui'
**
** Created: Thu 13. May 20:57:59 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERWINDOW_H
#define UI_RENDERWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RenderWindow
{
public:
    QAction *actionExit;
    QAction *actionRender;
    QAction *actionAbout;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QGraphicsView *Renderview;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *RenderWindow)
    {
        if (RenderWindow->objectName().isEmpty())
            RenderWindow->setObjectName(QString::fromUtf8("RenderWindow"));
        RenderWindow->resize(800, 600);
        actionExit = new QAction(RenderWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionRender = new QAction(RenderWindow);
        actionRender->setObjectName(QString::fromUtf8("actionRender"));
        actionAbout = new QAction(RenderWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralwidget = new QWidget(RenderWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        Renderview = new QGraphicsView(groupBox);
        Renderview->setObjectName(QString::fromUtf8("Renderview"));
        Renderview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Renderview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout_2->addWidget(Renderview);


        verticalLayout->addWidget(groupBox);

        RenderWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RenderWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        RenderWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(RenderWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        RenderWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionRender);
        menuFile->addSeparator();
        menuFile->addAction(actionAbout);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(RenderWindow);

        QMetaObject::connectSlotsByName(RenderWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RenderWindow)
    {
        RenderWindow->setWindowTitle(QApplication::translate("RenderWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("RenderWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionRender->setText(QApplication::translate("RenderWindow", "Render", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("RenderWindow", "About", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("RenderWindow", "Raytracer", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("RenderWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RenderWindow: public Ui_RenderWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERWINDOW_H
