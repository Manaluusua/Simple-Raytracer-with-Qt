#include "material.h"



Material::Material( QVector3D surf_col, QVector3D spec, qreal shininess, qreal spec_amount, QVector3D ambient, qreal am_amount, qreal reflection , qreal refraction  ):
        surf_col_(surf_col),
        ambient_col_(ambient),
        ambient_amount_(am_amount),
        specular_col_(spec),
        shininess_(shininess),
        spec_amount_(spec_amount),
        reflection_(reflection),
        refraction_(refraction)
{
    //sanitycheck
    if((reflection_+refraction_)>1)
    {
        refraction_ = 1-reflection;
    }


}

void Material::setReflectionAmount(qreal ref)
{
    if((ref+refraction_)>1)
    {
        reflection_= 1-refraction_;
    }
    else
    {
        reflection_=ref;
    }

}


void Material::setRefractionAmount(qreal ref)
{
    if((ref+reflection_)>1)
    {
        refraction_ = 1-reflection_;
    }
    else
    {
        refraction_ = ref;
    }
}
