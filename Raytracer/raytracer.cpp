#include "raytracer.h"
#include "object.h"
#include <QDebug>
#include "utils.h"
#include "light.h"
#include <cmath>
#include "poissonsdiscgenerator.h"

RayTracer::RayTracer(qreal image_width, qreal image_height, World *world, int depth):
        renderImage_(new QImage(image_width, image_height, QImage::Format_ARGB32)),
        world_(world),
        lock(QMutex::NonRecursive),
        depth_(depth)
{
    Camera* camera = new Camera(QVector3D(4,0,10), QVector3D(0,0,-1), static_cast<qreal>(image_width)/image_height, 4    );
    world_->setCamera(camera);
}

Ray RayTracer::getCameraToViewportRay(int image_space_x, int image_space_y)
{


    qreal x = static_cast<qreal>(image_space_x)/(renderImage_->size().width()-1);

    qreal y = static_cast<qreal>(image_space_y)/(renderImage_->size().height()-1);

    utils::convertToViewportRelative(x,y);
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

    emit partialRendering(renderImage_.data());

    antialias();

    emit renderingReady(renderImage_.data());

}


QColor RayTracer::getColorForPixel(int x, int y)
{
    Ray ray( this->getCameraToViewportRay(x,y) );
    return utils::convertAndClampToColor(raytrace(ray,depth_));
}

QVector3D RayTracer::raytrace(Ray ray, int depth,Object *ignore)
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
        QVector3D reflection_vector;
        QVector3D refraction_vector;

        if(reflection_amount>0 )
        {
            reflection_vector = ray.getDirection();
            reflection_vector =  utils::reflectVector(reflection_vector,normal);
            reflection_vector.normalize();
            Ray reflection_ray(inters_point, reflection_vector);
            reflection_color += raytrace(reflection_ray,depth, nearest);
        }
        if(refraction_amount>0 )
        {
            refraction_vector = ray.getDirection();
            refraction_vector = utils::refractVector(refraction_vector, normal,nearest->getMaterial()->getRefractionAngle());
            refraction_vector.normalize();
            Ray refraction_ray(inters_point, refraction_vector);
            refraction_color += raytrace(refraction_ray,depth,nearest);
        }

        if( refraction_amount>0)
        {

            utils::doFresnel(normal, ray.getDirection(), reflection_amount, refraction_amount);
        }
    }

    if( refraction_amount>0 && reflection_amount>0)
    {

        final_col += refraction_amount*(diffuse_amount*diffuse_col + refraction_color) + reflection_amount*reflection_color;
    }
    else
    {
        final_col += diffuse_amount*diffuse_col + refraction_amount*refraction_color + reflection_amount*reflection_color;
    }
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

void RayTracer::antialias()
{
    PoissonsDiscGenerator disc_generator;
    QSize img_size = renderImage_->size();
    qreal area_x = 1.f/img_size.width();
    qreal area_y = 1.f/img_size.height();
    int num_of_samples = 12;
    qreal min_dist = (area_x + area_y)/(2.f*num_of_samples);
    disc_generator.generatePoissonsDisc(min_dist, num_of_samples,area_x, area_y);

    for(int y = 0; y<img_size.height();y++)
    {
        lock.lock();

        for(int x=0; x<img_size.width();x++)
        {
            if(calculateMaximumDelta(x,y)>aa_delta_treshold_)
            {
                renderImage_->setPixel(x,y, utils::convertAndClampToColor(multisample(x,y, disc_generator)).rgba());
            }
        }
        lock.unlock();
        emit partialRendering(renderImage_.data());
    }

}

QVector3D RayTracer::multisample(int x, int y, PoissonsDiscGenerator& generator)
{
    QRgb rgb = renderImage_->pixel(x,y);
    QVector3D original_color(qRed(rgb), qGreen(rgb), qBlue(rgb));
    qreal move_x = 1.f/renderImage_->width();
    qreal move_y = 1.f/renderImage_->height();
    qreal origin_x = static_cast<qreal>(x)*move_x;
    qreal origin_y = static_cast<qreal>(y)*move_y;



    Camera* cam = world_->getCamera();
    utils::convertToViewportRelative(origin_x, origin_y);
    SampleList samples = generator.getDiscSamples();
    QPair<qreal, qreal> sample;
    foreach(sample, samples)
    {
        original_color += raytrace(cam->getCameraToViewportRay(origin_x + sample.first, origin_y + sample.second),depth_);
    }



    original_color /= samples.size()+1;
    return original_color;

}

qreal RayTracer::calculateMaximumDelta(int x, int y)
{
    QRgb origin_col = renderImage_->pixel(x,y);
    qreal comp = qRed(origin_col) + qGreen(origin_col) + qBlue(origin_col);
    qreal max_diff = 0;
    int min_x = utils::clampBetween(0,renderImage_->width()-1,x-1);
    int min_y = utils::clampBetween(0,renderImage_->height()-1,y-1);
    int max_x =  utils::clampBetween(0,renderImage_->width()-1,x+1);
    int max_y =  utils::clampBetween(0,renderImage_->height()-1,y+1);

    for(int i = min_x; i<=max_x; i++)
    {
        for(int j = min_y;j<=max_y; j++)
        {
            QRgb temp = renderImage_->pixel(i,j);
            qreal col_sum = qRed(temp) + qGreen(temp) + qBlue(temp);
            qreal diff = abs(col_sum - comp);
            if(diff>max_diff)
                max_diff = diff;
        }
    }
    return max_diff;
}
