#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>

#include "ray.h"
class Camera : public Ray
{
public:
    Camera(QVector3D start, QVector3D dir, qreal aspect_ratio, qreal near_clip);

    Ray getCameraToViewportRay(qreal relative_x, qreal relative_y);
private:
    QMatrix4x4 viewmat_;
    qreal asp_ratio_;
    qreal n_clip_;
};

#endif // CAMERA_H
