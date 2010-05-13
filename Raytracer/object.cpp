#include "object.h"
#include "geometry.h"
#include "material.h"

Object::Object(Geometry* geo, Material* mat)
{
    geometry_ = QSharedPointer<Geometry>(geo);
    material_ = QSharedPointer<Material>(mat);
}
