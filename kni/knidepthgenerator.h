#ifndef KNIDEPTHGENERATOR_H
#define KNIDEPTHGENERATOR_H

#include <QtCore>
#include <QtGui/QImage>

#include "kni_global.h"
#include "kni_namespace.h"
#include "knicontext.h"
#include "knigenerator.h"

class KniDepthGenerator: public KniGenerator
{
    Q_OBJECT

public:
    explicit KniDepthGenerator(KniContext* context);
    virtual ~KniDepthGenerator();

    bool startGenerating();
    bool stopGenerating();

    int width() const;
    int height() const;
    int fps() const;

    QImage& depth();
    unsigned char* rawDepth() const;

    xn::DepthGenerator& xnDepth();
    xn::DepthMetaData& xnMeta();
    XnMapOutputMode& xnMap();

protected:
    void update();

private:
    xn::DepthGenerator mXnDepthGen;
    xn::DepthMetaData mXnDepthMeta;
    XnMapOutputMode mXnMapOutput;

    // Image;
    QImage mDepthImage;

    // Raw depth image;
    unsigned char* mDepthRaw;
};

#endif // KNIDEPTHGENERATOR_H
