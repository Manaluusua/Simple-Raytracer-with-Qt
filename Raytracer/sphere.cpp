#include "sphere.h"
#include "ray.h"
#include "cmath"
#include "utils.h"
#include <QDebug>
Sphere::Sphere(QVector3D center, qreal rad):
        center_(center),
        rad_(rad)
{
}

Geometry::RayQueryResults Sphere::getIntersectionInfo(Ray &ray) const
{
    Geometry::RayQueryResults results;
    //A=1, so no need to calculate
    qreal B = 2*(ray.getDirection().x() * (ray.getStartPoint().x() - center_.x()) + ray.getDirection().y() * (ray.getStartPoint().y() - center_.y())  + ray.getDirection().z() * (ray.getStartPoint().z() - center_.z()));
    qreal C = pow(ray.getStartPoint().x() - center_.x(),2) + pow(ray.getStartPoint().y() - center_.y(),2) + pow(ray.getStartPoint().z() - center_.z(),2) - pow(rad_,2);
    qreal disc = pow(B,2) - 4*C;
    if(disc>0)
    {
        results.hit = true;
        qreal t1 = (-B - sqrt(disc))/2;
        qreal t2 = (-B + sqrt(disc))/2;
        results.distance = utils::min(t1,t2);
        if(results.distance<0)
        {
            results.distance = utils::max(t1,t2);
            if(results.distance<0)
            {
                results.hit = false;
            }
        }
    }

    return results;
}

QVector3D Sphere::getNormal(QVector3D &point) const
{
    QVector3D normal = point-center_;
    normal.normalize();
    return normal;
}
