#ifndef RAY_H
#define RAY_H

#include <QVector3D>


class Ray
{
public:
    Ray(QVector3D start, QVector3D dir);
    ~Ray(){}

    virtual QVector3D getStartPoint(){return start_point_;}
    virtual void setStartPoint(QVector3D start){start_point_ = start;}

    virtual QVector3D getDirection(){return direction_;}
    virtual void setDirection(QVector3D dir){dir.normalize(); direction_ = dir;}

protected:
    QVector3D start_point_;
    //normalized
    QVector3D direction_;
};

#endif // RAY_H
