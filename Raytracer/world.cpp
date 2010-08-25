#include "world.h"
#include "light.h"
#include "plane.h"
#include "object.h"
#include "sphere.h"
World::World():
        cam_(0)
{
}

void World::createWorld()
{
    destroyWorld();
    Light* l = new Light(QVector3D(0,5,-40),QVector3D(0,0,0), Light::POINT, QVector3D(15,15,15) );
    lights_.append(l);

   // l = new Light(QVector3D(20,-10,-40),QVector3D(0,0,0), Light::POINT, QVector3D(0,80,35) );
   // lights_.append(l);

    Sphere *s = new Sphere(QVector3D(4,0,-48), 4);
    Material* mat = new Material(QVector3D(0,0,0),1,QVector3D(50,50,50),1024.f,150, QVector3D(1,1,1),5,0.4 );
    Object *obj = new Object(s,mat);
    objects_.append(obj);
    s = new Sphere(QVector3D(-5,0,-50), 4);

     mat = new Material(QVector3D(40,10,5),1,QVector3D(50,50,50),512.f,5, QVector3D(1,1,1),0,0.3,0.3,-1.5f);
    obj = new Object(s,mat);
    objects_.append(obj);

    s = new Sphere(QVector3D(-14,0,-50), 4);
     mat = new Material(QVector3D(0,0,0),0,QVector3D(50,50,50),2048.f,5, QVector3D(1,1,1),5,1);
    obj = new Object(s,mat);
    objects_.append(obj);

    s = new Sphere(QVector3D(13,0,-50), 4);
     mat = new Material(QVector3D(0,1,0),20,QVector3D(50,50,50),2048.f,9, QVector3D(1,1,1),4,0,0.4,2.f);
    obj = new Object(s,mat);
    objects_.append(obj);




/////////////////////////

    Plane* p = new Plane(QVector3D(0,1,0),4);
     mat = new Material(QVector3D(3,0,0),1,QVector3D(50,50,50),512.f,5, QVector3D(1,1,1),5,0.03);
    obj = new Object(p,mat);
    objects_.append(obj);

    p = new Plane(QVector3D(0,-1,0),10);
         mat = new Material(QVector3D(3,0,0),1,QVector3D(50,50,50),512.f,5, QVector3D(1,1,1),5,0.03);
        obj = new Object(p,mat);
        objects_.append(obj);

     p = new Plane(QVector3D(0,0,1),70);
     mat = new Material(QVector3D(1,1,1),5,QVector3D(50,50,50),512.f,5, QVector3D(1,1,1),5,0.03);
    obj = new Object(p,mat);
    objects_.append(obj);

    p = new Plane(QVector3D(0,0,-1),25);
    mat = new Material(QVector3D(1,1,1),5,QVector3D(50,50,50),512.f,5, QVector3D(1,1,1),5,0.01);
   obj = new Object(p,mat);
   objects_.append(obj);

    p = new Plane(QVector3D(1,0,0),25);
    mat = new Material(QVector3D(1,1,1),7,QVector3D(50,50,50),512.f,5, QVector3D(1,1,1),5,0.01);
   obj = new Object(p,mat);
   objects_.append(obj);

   p = new Plane(QVector3D(-1,0,0),25);
   mat = new Material(QVector3D(1,1,1),7,QVector3D(50,50,50),512.f,5, QVector3D(1,1,1),5,0.01);
  obj = new Object(p,mat);
  objects_.append(obj);









}

void World::destroyWorld()
{
    if(cam_)
    {
        delete cam_;
        cam_=0;
    }

    for(int i=0; i<objects_.size(); i++)
    {
        delete objects_.at(i);
    }
    for(int i=0;i<lights_.size();i++)
    {
        delete lights_.at(i);
    }
}


World::~World()
{
    destroyWorld();
}
