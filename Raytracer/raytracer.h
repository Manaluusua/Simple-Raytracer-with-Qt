#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <QThread>
#include <QPixmap>
#include <QMutex>
#include "world.h"

class Material;
class PoissonsDiscGenerator;
class RayTracer : public QThread
{
    Q_OBJECT
public:
    RayTracer(qreal image_width, qreal image_height, World *world,int depth =2);
    void run();

    QMutex& GetRenderImageLock(){return lock;}


signals:
    void partialRendering(QImage* partial);
    void renderingReady(QImage* final);

private:
    QSharedPointer<QImage> renderImage_;
    World *world_;
    QMutex lock;

    const static qreal aa_delta_treshold_=50.f;

    void antialias();
    QVector3D multisample(int x, int y,PoissonsDiscGenerator& generator);
    qreal calculateMaximumDelta(int x, int y);

    int depth_;

    QVector3D getLightDir(Light* const light,const QVector3D*  point);
    QColor getColorForPixel(int x, int y);
    Ray getCameraToViewportRay(int image_space_x, int image_space_y);
    QVector3D raytrace(Ray ray, int depth, Object *ignore = 0);
    QVector<Light*> getAffectingLights(Object* obj,const QVector3D& point);
    QVector3D getDiffuseFactor(Light* const light,const QVector3D *point, const QVector3D *normal, const Material* mat);
    QVector3D getSpecularFactor(Light* const light,const QVector3D *point, const QVector3D *normal,const QVector3D *viewdir, const Material* mat);
};

#endif // RAYTRACER_H
