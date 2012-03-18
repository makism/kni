#include "knicontext.h"
#include "knidepthgenerator.h"

KniContext::KniContext()
    : mHasInited(false)
{

}

KniContext::~KniContext()
{
    if (mHasInited)
        mXnContext.Release();
}

void KniContext::update()
{
    if (!mHasInited)
        return;

    XnStatus statusCode = mXnContext.WaitAnyUpdateAll();

    if (statusCode == XN_STATUS_OK) {
        emit updated();
    } else {
        emit updateError(statusCode, xnGetStatusString(statusCode));
    }
}

KniDepthGenerator& KniContext::depthGenerator()
{
    static KniDepthGenerator kniDepthGenerator(this);
    return kniDepthGenerator;
}

KniImageGenerator& KniContext::imageGenerator()
{

}

bool KniContext::initContext()
{
    if (mHasInited)
        return true;

    XnStatus status = mXnContext.Init();
    mHasInited = (status == XN_STATUS_OK) ? true : false;

    return mHasInited;
}

xn::Context& KniContext::xnContext()
{
    return mXnContext;
}

void KniContext::addLicense(const QString &vendor, const QString &key)
{
}

void KniContext::run()
{
    while (isRunning()) {
        update();
    }
}
