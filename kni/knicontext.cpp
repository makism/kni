#include "knicontext.h"
#include "knidepthgenerator.h"

KniContext::KniContext()
{

}

KniContext::~KniContext()
{
    mXnContext.Shutdown();
}

void KniContext::update()
{
    XnStatus statusCode = mXnContext.WaitAnyUpdateAll();

    if (statusCode == XN_STATUS_OK) {
        emit updated();
    } else {
        emit error(statusCode, xnGetStatusString(statusCode));
    }
}

KniDepthGenerator& KniContext::depthGenerator()
{
    static KniDepthGenerator kniDepthGenerator(this);
    return kniDepthGenerator;
}

xn::Context & KniContext::xnContext()
{
    return mXnContext;
}
