#ifndef KNICONTEXT_H
#define KNICONTEXT_H

#include <QtCore>

#include <XnOpenNI.h>
#include <XnCodecIDs.h>
#include <XnCppWrapper.h>

#include "kni_global.h"
#include "kni_namespace.h"

class KniDepthGenerator;
class KniImageGenerator;

class KNISHARED_EXPORT KniContext: public QThread // inherit KniGenerator?
{
    Q_OBJECT

public:
    KniContext();
    virtual ~KniContext();

    void run();

    virtual void update();
    KniDepthGenerator& depthGenerator();
    KniImageGenerator& imageGenerator();

    void addLicense(const QString& vendor = "PrimeSense", const QString& key = "0KOIk2JeIBYClPWVnMoRKn5cdY4=");

    bool toggleMirror();
    bool setMirror(bool mirroring);

    bool toggleRegisterViewport();
    bool registerViewport();
    bool unregisterViewport();

    bool initContext();
    xn::Context& xnContext();

signals:
    void updated();
    void updateError(int errorId, const QString& errorStr);

protected:
    bool mHasInited;
    xn::Context mXnContext;
};

#endif // KNICONTEXT_H
