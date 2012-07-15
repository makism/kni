#include "knionicontext.h"

KniOniContext::KniOniContext(const QString &oniFile, QObject* parent)
    : KniContext(parent),
      m_recording(oniFile)
{
    initContext();

    xn::EnumerationErrors errors;
    XnStatus statusCode = XN_STATUS_OK;

    statusCode = m_xnContext.OpenFileRecording(m_recording.toLatin1().data(), m_xnPlayer);
}

KniOniContext::~KniOniContext()
{
    m_xnPlayer.Release();
}

void KniOniContext::update()
{
    KniContext::update();
}

xn::Player& KniOniContext::xnPlayer()
{
    return m_xnPlayer;
}
