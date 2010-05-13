#ifndef UTILS_H
#define UTILS_H

#include <QColor>
#include <QVector3D>
#include <QDebug>


namespace utils
{
    inline qreal max(qreal a, qreal b){ return a>b?a:b; }
    inline qreal min(qreal a, qreal b){ return a<b?a:b; }
    inline qreal clamp(qreal num){ return num<0?0:(num>1?1:num);}
    inline QColor ConvertAndClampToColor(QVector3D color)
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

    inline QVector3D reflectVector(QVector3D& dir, QVector3D& normal)
    {
        QVector3D vec = dir-2*(dir.dotProduct(dir, normal)*(normal));

        return vec;

    }


}
#endif // UTILS_H
