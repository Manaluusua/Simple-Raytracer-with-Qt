#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QSharedPointer>
#include <QPixmap>
#include <QMainWindow>
class RayTracer;
class World;
namespace Ui {
    class RenderWindow;
}

class RenderWindow : public QMainWindow {
    Q_OBJECT
public:
    RenderWindow(QWidget *parent = 0);
    ~RenderWindow();

public slots:
    void exit();
    void render();
    void about();
    void displayPartialImage(QImage* partial);
    void renderingFinished(QImage* final);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::RenderWindow *ui;
    RayTracer *tracer;
    World *world_;

};

#endif // RENDERWINDOW_H
