#include "plane.h"
#include "utils.h"
#include "ray.h"

#include <QDebug>

Plane::Plane(QVector3D normal, qreal d):
        normal_(normal),
        d_(d)
{
    normal_.normalize();

}

QVector3D Plane::getNormal(QVector3D &point) const
{
    return normal_;
}


Geometry::RayQueryResults Plane::getIntersectionInfo(Ray &ray) const
{
    Geometry::RayQueryResults result;
    qreal den = QVector3D::dotProduct(normal_, ray.getDirection());
    //check if parallel
    if(den!=0)
    {
        qreal nom = -(QVector3D::dotProduct(normal_, ray.getStartPoint()) + d_);
        qreal t = nom/den;
        if(t>0)
        {
            result.hit = true;
            result.distance = t;
        }
    }
    return result;

}
