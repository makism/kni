#ifndef KNICONTEXT_H
#define KNICONTEXT_H

#include <QtCore>

#include <XnOpenNI.h>
#include <XnCodecIDs.h>
#include <XnCppWrapper.h>

#include "kni_global.h"
#include "kni_namespace.h"

class KniDepthGenerator;

class KniContext: public QObject
{
    Q_OBJECT

public:
    KniContext();
    virtual ~KniContext();

    virtual void update();
    KniDepthGenerator& depthGenerator();

    xn::Context& xnContext();

signals:
    void updated();
    void error(int errorId, const QString& errorStr);

protected:
    xn::Context mXnContext;
};

#endif // KNICONTEXT_H
