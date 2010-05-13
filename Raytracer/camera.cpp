#include "camera.h"
#include <QMatrix4x4>
#include <QVector4D>
Camera::Camera(QVector3D start, QVector3D dir, qreal aspect_ratio, qreal near_clip)
    :Ray(start, dir),
    asp_ratio_(aspect_ratio),
    n_clip_(near_clip)
{
}

Ray Camera::getCameraToViewportRay(qreal relative_x, qreal relative_y)
{
    QMatrix4x4 cam_transf;
    qreal x = asp_ratio_ * relative_x;
    qreal y = relative_y;
    QVector3D viewportdir(x,y,-n_clip_);
    viewportdir.normalize();

    cam_transf.lookAt(start_point_,start_point_ + direction_,QVector3D(0,1,0));
    bool invertible;
    QVector3D newdir = cam_transf.inverted(&invertible).mapVector( viewportdir);
    return Ray(start_point_, newdir);

}
