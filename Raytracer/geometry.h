#ifndef GEOMETRY_H
#define GEOMETRY_H


#include <QVector3D>

class Ray;



class Geometry
{
public:

    struct RayQueryResults
    {
        RayQueryResults():hit(false), distance(-1){}
        bool hit;
        qreal distance;
    };
    virtual RayQueryResults getIntersectionInfo(Ray &ray) const =0;
    virtual QVector3D getNormal(QVector3D& point) const =0;


};

#endif // GEOMETRY_H
