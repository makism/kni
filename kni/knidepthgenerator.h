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
    Q_DISABLE_COPY(KniDepthGenerator)

    friend class KniContext;

public:
    KniDepthGenerator();
    explicit KniDepthGenerator(KniContext* context);
    virtual ~KniDepthGenerator();

    bool startGenerating();
    bool stopGenerating();

    int width() const;
    int height() const;
    int fps() const;

    QImage depthAsImage();
    unsigned char* rawDepth() const;

    xn::DepthGenerator& xnDepth();
    xn::DepthMetaData& xnMeta();
    XnMapOutputMode& xnMap();

protected:
    void update();

private:
    xn::DepthGenerator m_xnDepthGen;
    xn::DepthMetaData m_xnDepthMeta;
    XnMapOutputMode m_xnMapOutput;

    // Image;
    QImage m_depthImage;

    // Raw depth image;
    unsigned char* m_depthRaw;
};

#endif // KNIDEPTHGENERATOR_H
