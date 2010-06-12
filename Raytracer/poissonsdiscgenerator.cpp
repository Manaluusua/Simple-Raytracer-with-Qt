#include "poissonsdiscgenerator.h"

PoissonsDiscGenerator::PoissonsDiscGenerator()
{
}


void PoissonsDiscGenerator::generatePoissonsDisc(qreal min_dist, qreal num_samples, qreal area_width, qreal area_height)
{
    //To Do: the actual poissons disc generation. For now just use precalculated samples
    /*area_height /=2;
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
    }*/

    samples_.append( QPair<qreal,qreal>(0.007937789*area_width, 0.73124397*area_height));
            samples_.append( QPair<qreal,qreal>(-0.10177308*area_width, -0.6509396*area_height));
            samples_.append( QPair<qreal,qreal>(-0.9906806*area_width, -0.63400936*area_height));
            samples_.append( QPair<qreal,qreal>(-0.5583586*area_width, -0.3614012*area_height));
            samples_.append( QPair<qreal,qreal>(0.7163085*area_width, 0.22836149*area_height));
            samples_.append( QPair<qreal,qreal>(-0.65210974*area_width, 0.37117887*area_height));
            samples_.append( QPair<qreal,qreal>(-0.12714535*area_width, 0.112056136*area_height));
            samples_.append( QPair<qreal,qreal>(0.48898065*area_width, -0.66669613*area_height));
            samples_.append( QPair<qreal,qreal>(-0.9744036*area_width, 0.9155904*area_height));
            samples_.append( QPair<qreal,qreal>(0.9274436*area_width, -0.9896486*area_height));
            samples_.append( QPair<qreal,qreal>(0.9782181*area_width, 0.90990245*area_height));
            samples_.append( QPair<qreal,qreal>(0.96427417*area_width, -0.25506377*area_height));
            samples_.append( QPair<qreal,qreal>(-0.5021933*area_width, -0.9712455*area_height));
            samples_.append( QPair<qreal,qreal>(0.3091557*area_width, -0.17652994*area_height));
            samples_.append( QPair<qreal,qreal>(0.4665941*area_width, 0.96454906*area_height));
            samples_.append( QPair<qreal,qreal>(-0.461774*area_width, 0.9360856*area_height));






}

SampleList PoissonsDiscGenerator::getDiscSamples()
{
    return samples_;
}
