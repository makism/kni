#include "knicontext.h"
#include "knidepthgenerator.h"

KniContext::KniContext(QObject* parent)
    : QThread(parent),
      mHasInited(false)
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
    static KniImageGenerator kniImageGenerator(this);
    return kniImageGenerator;
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
        if (!mWaitForGenerators)
            update();
    }
}

void KniContext::generatorUpdated()
{
    mGeneratorsUpdated++;

    qDebug() << "generatorUpdated() \t" << mGeneratorsUpdated << "\n";

    if (mGeneratorsUpdated == children().size()) {
        mGeneratorsUpdated = 0;
        mWaitForGenerators = true;
    }
}

void KniContext::startAll()
{
    start();
    foreach(QObject* child, children()) {
        KniGenerator* generator = qobject_cast<KniGenerator*>(child);

        if (generator != NULL) {
            generator->start();
        }
    }
}

void KniContext::stopAll()
{
    foreach(QObject* child, children()) {
        KniGenerator* generator = qobject_cast<KniGenerator*>(child);

        if (generator != NULL) {
            generator->quit();
        }
    }
    quit();
}
