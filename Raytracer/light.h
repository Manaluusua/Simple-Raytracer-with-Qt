#ifndef LIGHT_H
#define LIGHT_H

#include <QColor>
#include <QVector3D>

class Light
{


public:
    enum LightType { POINT, DIRECTIONAL };
    Light(QVector3D pos, QVector3D dir= QVector3D(0,0,0), LightType type=POINT,  QVector3D diff_col =  QVector3D(20,20,20),qreal diff_intensity=1 );
    LightType getLightType();

     QVector3D getDiffuseColor();
    void setDiffuseColor( QVector3D c);
    qreal getDiffuseIntensity();
    void setDiffuseIntensity(qreal i);

    void setDirection(QVector3D dir){dir_=dir; dir_.normalize();}
    QVector3D getDirection(){return dir_;}

    void setPosition(QVector3D pos){pos_=pos;}
    QVector3D getPosition(){return pos_;}

protected:
    LightType type_;
    QVector3D diff_col_;
    qreal diff_intensity_;

    QVector3D pos_;
    QVector3D dir_;

};

#endif // LIGHT_H
