#include "poissonsdiscgenerator.h"

PoissonsDiscGenerator::PoissonsDiscGenerator()
{
}


void PoissonsDiscGenerator::generatePoissonsDisc(qreal min_dist, qreal num_samples, qreal area_width, qreal area_height)
{
    //To Do: the actual poissons disc generation. For now just use simple 3x3 - center grid
    area_height /=2;
    area_width /=2;

    for(qreal i = -area_width; i<=area_width; i += area_width)
    {
        for(qreal j = area_height; j<=area_height; j+= area_height)
        {
            if(i!=0 || j!=0)
            {
                samples_.append(QPair<qreal, qreal>(i,j));
            }
        }
    }





}

SampleList PoissonsDiscGenerator::getDiscSamples()
{
    return samples_;
}
