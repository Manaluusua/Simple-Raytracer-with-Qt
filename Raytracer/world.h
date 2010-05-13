#ifndef WORLD_H
#define WORLD_H

#include <QVector>
#include "camera.h"

class Light;
class Object;

class World
{
public:
    World();
    virtual ~World();
    void createWorld();
    void destroyWorld();
    Camera* getCamera(){return cam_;}
    void setCamera(Camera* cam){cam_ = cam;}

    QVector<Object*>& getObjects(){return objects_;}
    QVector<Light*>& getLights(){return lights_;}

private:
    QVector<Object*> objects_;
    QVector<Light*> lights_;

    Camera* cam_;

};

#endif // WORLD_H
