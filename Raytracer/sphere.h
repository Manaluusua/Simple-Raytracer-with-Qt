#ifndef SPHERE_H
#define SPHERE_H
#include "geometry.h"



class Sphere: public Geometry
{
public:
    Sphere(QVector3D center, qreal rad);

    Geometry::RayQueryResults getIntersectionInfo(Ray &ray) const;
    QVector3D getNormal(QVector3D &point) const;
private:
    QVector3D center_;
    qreal rad_;
};

#endif // SPHERE_H
