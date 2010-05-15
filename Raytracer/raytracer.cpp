#include "raytracer.h"
#include "object.h"
#include <QDebug>
#include "utils.h"
#include "light.h"
#include <cmath>

RayTracer::RayTracer(qreal image_width, qreal image_height, World *world):
        renderImage_(new QImage(image_width, image_height, QImage::Format_ARGB32)),
        world_(world),
        lock(QMutex::NonRecursive)
{
    Camera* camera = new Camera(QVector3D(4,0,0), QVector3D(0,0,-1), static_cast<qreal>(image_width)/image_height, 4    );
    world_->setCamera(camera);
}

Ray RayTracer::getCameraToViewportRay(int image_space_x, int image_space_y)
{

    //we assume that the viewport z = 0 and set x and y between -1 and 1
    qreal x = static_cast<qreal>(image_space_x)/(renderImage_->size().width()-1);
    x = (x*2)-1;
    qreal y = static_cast<qreal>(image_space_y)/(renderImage_->size().height()-1);
    //flip y to get y up, -y down
    y=1-y;
    y = (y*2)-1;
    return world_->getCamera()->getCameraToViewportRay(x,y);
}

void RayTracer::run()
{
    Q_ASSERT(world_!= 0);
    if(!world_)
        return;
    Q_ASSERT(world_->getCamera()!=0);
    if(!world_->getCamera())
        return;




    QSize img_size = renderImage_->size();

    for(int y = 0; y<img_size.height();y++)
    {
        lock.lock();

        for(int x=0; x<img_size.width();x++)
        {
            renderImage_->setPixel(x,y, getColorForPixel(x,y).rgba());

        }
        lock.unlock();
        emit partialRendering(renderImage_.data());
    }

    emit renderingReady(renderImage_.data());
}


QColor RayTracer::getColorForPixel(int x, int y)
{
    Ray ray( this->getCameraToViewportRay(x,y) );
    return utils::ConvertAndClampToColor(raytrace(ray,2));
}

QVector3D RayTracer::raytrace(Ray &ray, int depth,Object *ignore)
{
    depth--;
    QVector3D final_col(0,0,0);
    QVector<Object*> objects = world_->getObjects();
    if(objects.empty())
        return final_col;

    Object* nearest =  0;
    qreal nearest_distance = -1;
    for(int i=0;i<objects.size();i++)
    {
        Object* obj = objects.at(i);
        Geometry::RayQueryResults result =  obj->getGeometry()->getIntersectionInfo(ray);
        if(result.hit)
        {
            if((nearest_distance > result.distance || nearest_distance==-1) && obj !=ignore)
            {
                nearest = obj;
                nearest_distance = result.distance;
            }
        }
    }
    if(!nearest)
        return final_col;
    QVector3D inters_point = ray.getStartPoint() +  ray.getDirection()* nearest_distance;
    QVector3D diffuse_col(0,0,0);
    QVector<Light*> lights = getAffectingLights(nearest, inters_point);
    qreal reflection_amount = nearest->getMaterial()->getReflectionAmount();
    qreal refraction_amount = nearest->getMaterial()->getRefractionAmount();
    qreal diffuse_amount = 1-reflection_amount-refraction_amount;
    QVector3D reflection_color(0,0,0);
    QVector3D refraction_color(0,0,0);
    QVector3D normal =  nearest->getGeometry()->getNormal(inters_point);

    //ambient
    diffuse_col+= nearest->getMaterial()->getSurfaceColor() * nearest->getMaterial()->getAmbientColor()*nearest->getMaterial()->getAmbientAmount();
    foreach(Light *light, lights)
    {
        QVector3D overall_col_from_light;
        QVector3D viewdir = ray.getDirection();

        //diffuse lighting
        QVector3D diff_l = getDiffuseFactor(light,&inters_point, &normal, nearest->getMaterial().data());
        //specular lighting
        QVector3D spec_l = getSpecularFactor(light,&inters_point, &normal, &viewdir, nearest->getMaterial().data());
        overall_col_from_light = diff_l + spec_l;
        diffuse_col += overall_col_from_light;
    }


    if(depth>0)
    {

        if(reflection_amount>0 )
        {
            QVector3D reflection_vector = ray.getDirection();
            reflection_vector =  utils::reflectVector(reflection_vector,normal);
            reflection_vector.normalize();
            Ray reflection_ray(inters_point+reflection_vector, reflection_vector);
            reflection_color += raytrace(reflection_ray,depth, nearest);
        }
        if(refraction_amount>0 )
        {

        }
    }

    final_col += diffuse_amount*diffuse_col + refraction_amount*refraction_color + reflection_amount*reflection_color;
    return final_col;

}

QVector<Light*> RayTracer::getAffectingLights(Object* obj,const QVector3D& point)
{
    return world_->getLights();
}


QVector3D RayTracer::getDiffuseFactor(Light*const light,const QVector3D *point, const QVector3D *normal, const Material* mat)
{
    QVector3D light_dir = getLightDir(light, point);
    qreal dot = utils::clamp(normal->dotProduct( *normal, light_dir));


    QVector3D color = mat->getSurfaceColor()* mat->getDiffuseAmount() *light->getDiffuseColor()*dot;
    return color;
}

QVector3D RayTracer::getSpecularFactor( Light*const light,const QVector3D *point, const QVector3D *normal,const QVector3D *viewdir, const Material* mat)
{
    QVector3D light_dir = getLightDir(light, point);
    QVector3D halfVector = light_dir + (-(*viewdir));
    halfVector.normalize();

    qreal dot = utils::clamp(normal->dotProduct(*normal, halfVector));
    QVector3D col = mat->getSpecularAmount()*(pow(dot,mat->getShininess())*mat->getSpecularColor());
    return col;

}

QVector3D RayTracer::getLightDir(Light* const light,const QVector3D* point)
{
    QVector3D light_dir;
    if(light->getLightType() == Light::POINT)
    {
        light_dir = light->getPosition()-*point;

    }
    else if(light->getLightType() == Light::DIRECTIONAL)
    {

        light_dir = light->getDirection();
    }
    light_dir.normalize();
    return light_dir;

}
