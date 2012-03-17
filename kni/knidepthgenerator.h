#ifndef KNIDEPTHGENERATOR_H
#define KNIDEPTHGENERATOR_H

#include <QtCore>
#include <QtGui/QImage>

#include "kni_global.h"
#include "kni_namespace.h"
#include "knicontext.h"

class KniDepthGenerator: public QObject
{
    Q_OBJECT

public:
    KniDepthGenerator(KniContext* context);
    ~KniDepthGenerator();

public:
    void update();

private:
    // KniContext
    KniContext* mKniContext;

    xn::DepthGenerator mXnDepthGen;
    xn::DepthMetaData mXnDepthMeta;

    // Image;
    QImage mImgDepth;

    // Raw depth image;
    unsigned char* mRawDepth;
};

#endif // KNIDEPTHGENERATOR_H
