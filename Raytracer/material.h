#ifndef MATERIAL_H
#define MATERIAL_H

#include <QVector3D>

class Material
{
public:

    Material( QVector3D surf_col =  QVector3D(0,0,0), qreal diff_amount = 1 , QVector3D spec =  QVector3D(10,10,10), qreal shininess=32.f, qreal spec_amount=50, QVector3D ambient=QVector3D(1,1,1), qreal amb_amount =10, qreal reflection = 0, qreal refraction = 0, qreal refr_angle = 0 );

    QVector3D getAmbientColor()const{return ambient_col_;}
    void setAmbientColor(QVector3D col){ambient_col_ = col;}

    qreal getDiffuseAmount()const{return diff_amount_;}
    void setDiffuseAmount(qreal am){diff_amount_ = am;}

    QVector3D getSurfaceColor() const{return surf_col_;}
    void setSurfaceColor(QVector3D col){surf_col_ = col;}

    void setAmbientAmount(qreal amb) {ambient_amount_=amb;}
    qreal getAmbientAmount()const{return ambient_amount_;}

    void setSpecularColor(QVector3D spec) {specular_col_=spec;}
    QVector3D getSpecularColor() const{return specular_col_;}

    void setSpecularAmount(qreal spec_am) {spec_amount_=spec_am;}
    qreal getSpecularAmount()const{return spec_amount_;}

    void setShininess(qreal s){shininess_=s;}
    qreal getShininess() const{return shininess_;}

    void setReflectionAmount(qreal ref);
    qreal getReflectionAmount()const{return reflection_;}

    void setRefractionAmount(qreal ref);
    qreal getRefractionAmount()const{return refraction_;}

    void setRefractionAngle(qreal angle){ refr_angle_ = angle;}
    qreal getRefractionAngle(){return refr_angle_;}




private:
    QVector3D surf_col_;
    qreal diff_amount_;
    QVector3D ambient_col_;
    qreal ambient_amount_;


    QVector3D specular_col_;
    qreal shininess_;
    qreal spec_amount_;

    qreal reflection_;

    qreal refraction_;
    qreal refr_angle_;


};

#endif // MATERIAL_H
