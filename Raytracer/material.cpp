#include "material.h"



Material::Material( QVector3D surf_col, qreal diff_amount, QVector3D spec, qreal shininess, qreal spec_amount, QVector3D ambient, qreal am_amount, qreal reflection , qreal refraction, qreal refr_angle  ):
        surf_col_(surf_col),
        diff_amount_ (diff_amount),
        ambient_col_(ambient),
        ambient_amount_(am_amount),
        specular_col_(spec),
        shininess_(shininess),
        spec_amount_(spec_amount),
        reflection_(reflection),
        refraction_(refraction),
        refr_angle_(refr_angle)
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
