#include "renderwindow.h"
#include "ui_renderwindow.h"
#include "raytracer.h"
#include "world.h"
#include <QDebug>
#include <QMessageBox>

RenderWindow::RenderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RenderWindow),
    tracer(0),
    world_(0)
{
    ui->setupUi(this);
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->Renderview->setScene(scene);
    QObject::connect(ui->actionRender, SIGNAL(triggered()), this, SLOT(render()));
    QObject::connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exit()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()),this, SLOT(about()));
    world_ = new World();
    world_->createWorld();


}

void RenderWindow::render()
{
    ui->actionRender->setDisabled(true);

    QSize image_size =  ui->Renderview->size();
    ui->Renderview->scene()->setSceneRect(0,0,image_size.width(), image_size.height());
    if(tracer)
    {
        while(tracer->isRunning());
        delete tracer;
        tracer=0;
    }
    tracer = new RayTracer(image_size.width(), image_size.height(), world_);
    QObject::connect(tracer, SIGNAL(partialRendering(QImage*)),this, SLOT(displayPartialImage(QImage*)));
    QObject::connect(tracer, SIGNAL(renderingReady(QImage*)),this,SLOT(renderingFinished(QImage*)));
    tracer->start();
}

void RenderWindow::about()
{
    QMessageBox::information(this, "About", "Primitive raytracer \n © Mana");

}

void RenderWindow::renderingFinished(QImage* final)
{
    ui->Renderview->scene()->clear();
    ui->Renderview->scene()->addPixmap(QPixmap::fromImage(*final));
    ui->actionRender->setDisabled(false);


}

void RenderWindow::displayPartialImage(QImage* partial)
{
    tracer->GetRenderImageLock().lock();
    ui->Renderview->scene()->clear();
    ui->Renderview->scene()->addPixmap(QPixmap::fromImage(*partial));
    tracer->GetRenderImageLock().unlock();
}

void RenderWindow::exit()
{
    QApplication::exit();

}

RenderWindow::~RenderWindow()
{
    delete ui;
    delete world_;
    world_ = 0;
}

void RenderWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
