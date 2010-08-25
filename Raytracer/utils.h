#ifndef UTILS_H
#define UTILS_H

#include <QColor>
#include <QVector3D>
#include <QDebug>
#include <math.h>


namespace utils
{
    inline qreal max(qreal a, qreal b){ return a>b?a:b; }
    inline qreal min(qreal a, qreal b){ return a<b?a:b; }
    inline qreal clamp(qreal num){ return num<0?0:(num>1?1:num);}
    inline void convertToViewportRelative(qreal &x, qreal &y)
    {
        x = (x*2)-1;
        //flip y to get +y up, -y down
        y = 1-y;
        y = (y*2)-1;
    }

    inline qreal clampBetween(qreal min, qreal max, qreal value)
    {
        value = value<min?min:value;
        value = value>max?max:value;
        return value;
    }

    inline QColor convertAndClampToColor(QVector3D color)
    {
        qreal r = color.x();
        qreal g = color.y();
        qreal b = color.z();

        r = r>255?255:r;
        g = g>255?255:g;
        b = b>255?255:b;

        r = r<0?0:r;
        g = g<0?0:g;
        b = b<0?0:b;
        return QColor(static_cast<int>(r),static_cast<int>(g),static_cast<int>(b));

    }

    inline QVector3D convertToColorVector(QColor c)
    {
        return QVector3D(c.redF(),c.greenF(),c.blueF());
    }

    inline QVector3D reflectVector(const QVector3D& dir,const QVector3D& normal)
    {
        QVector3D vec = dir-2*(dir.dotProduct(dir, normal)*(normal));
        vec.normalize();
        return vec;

    }


    inline QVector3D refractVector(const QVector3D & dir, const QVector3D& normal, qreal refract_angle)
    {
        QVector3D vec = dir.dotProduct(dir, normal) * normal;
        QVector3D temp = -(dir - vec);
        vec = dir-refract_angle*temp;
        return vec;
    }

    inline void doFresnel(const QVector3D &normal, const QVector3D &view_dir, qreal &reflection_amount, qreal &refraction_amount)
    {
        qreal dot =fabs( normal.dotProduct(normal, view_dir));
        qreal total_max = reflection_amount + refraction_amount;
        reflection_amount = (1-dot)*total_max;
        refraction_amount = (dot)*total_max;
        //qDebug()<< "reflect: " << reflection_amount << " refract: " << refraction_amount;
    }


}
#endif // UTILS_H
