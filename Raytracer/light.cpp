#include "light.h"

Light::Light(QVector3D pos, QVector3D dir,LightType type,  QVector3D diff_col,qreal diff_intensity):
        type_(type),
        diff_col_(diff_col),
        diff_intensity_(diff_intensity),
        pos_(pos),
        dir_(dir)
{
    dir_.normalize();

}

Light::LightType Light::getLightType()
{
    return type_;
}

 QVector3D Light::getDiffuseColor()
{
    return diff_col_;
}

void Light::setDiffuseColor( QVector3D c)
{
    diff_col_ = c;
}

qreal Light::getDiffuseIntensity()
{
    return diff_intensity_;
}

void Light::setDiffuseIntensity(qreal i)
{
    diff_intensity_ = i;
}

