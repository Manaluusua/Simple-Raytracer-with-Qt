#include "ray.h"


Ray::Ray(QVector3D start, QVector3D dir):
        start_point_(start),
        direction_(dir)
{
    direction_.normalize();
}

