#include "knicontext.h"
#include "kniimagegenerator.h"
#include "knidepthgenerator.h"

KniContext::KniContext(QObject* parent)
    : QThread(parent),
      m_hasInited(false),
      m_waitForGenerators(false)
{

}

KniContext::~KniContext()
{
    if (m_hasInited)
        m_xnContext.Release();
}

void KniContext::update()
{
    if (!m_hasInited)
        return;

    XnStatus statusCode = m_xnContext.WaitAnyUpdateAll();

    if (statusCode == XN_STATUS_OK) {
        emit updated();
    } else {
        emit updateError(statusCode, xnGetStatusString(statusCode));
    }
}

//KniDepthGenerator& KniContext::depthGenerator()
//{
//    static KniDepthGenerator kniDepthGenerator(this);
//    return kniDepthGenerator;
//}

//KniImageGenerator& KniContext::imageGenerator()
//{
//    static KniImageGenerator kniImageGenerator(this);
//    return kniImageGenerator;
//}

bool KniContext::initContext()
{
    if (m_hasInited)
        return true;

    XnStatus status = m_xnContext.Init();
    m_hasInited = (status == XN_STATUS_OK) ? true : false;

    return m_hasInited;
}

xn::Context& KniContext::xnContext()
{
    return m_xnContext;
}

void KniContext::addLicense(const QString& vendor, const QString& key)
{
    Q_UNUSED(vendor);
    Q_UNUSED(key);
}

void KniContext::run()
{
    while (isRunning()) {
        if (!m_waitForGenerators) {
            m_waitForGenerators = true;
            update();
        }
    }
}

void KniContext::generatorUpdated()
{
    m_generatorsUpdated++;

    // A bit hacky... :/
    if (m_generatorsUpdated == children().size()) {
        m_generatorsUpdated = 0;
        m_waitForGenerators = false;
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
            generator->deleteLater();
        }
    }

    quit();
}
