#ifndef POISSONSDISCGENERATOR_H
#define POISSONSDISCGENERATOR_H

#include <QVector>
#include <QPair>
typedef QVector<QPair<qreal,qreal> > SampleList;

class PoissonsDiscGenerator
{

public:
    PoissonsDiscGenerator();
    void generatePoissonsDisc(qreal min_dist, qreal num_samples, qreal area_width, qreal area_height);
    SampleList getDiscSamples();

private:

    SampleList samples_;
};

#endif // POISSONSDISCGENERATOR_H
