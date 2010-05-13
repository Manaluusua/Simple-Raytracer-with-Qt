#ifndef PLANE_H
#define PLANE_H

#include <QVector3D>
#include "geometry.h"

class Plane: public Geometry
{
public:
    Plane(QVector3D normal, qreal d);

    //Geometry
    Geometry::RayQueryResults getIntersectionInfo(Ray &ray) const;
    QVector3D getNormal(QVector3D &point) const;

private:
    //normalized
    QVector3D normal_;
    qreal d_;
};

#endif // PLANE_H
