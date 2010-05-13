#ifndef OBJECT_H
#define OBJECT_H

#include <QSharedPointer>
#include "geometry.h"
#include "material.h"


class Object
{
public:
    Object(Geometry* geo, Material* mat);
    QSharedPointer<Geometry> getGeometry(){ return geometry_;}
    QSharedPointer<Material> getMaterial(){ return material_;}

private:
    QSharedPointer<Geometry> geometry_;
    QSharedPointer<Material> material_;
};

#endif // OBJECT_H
