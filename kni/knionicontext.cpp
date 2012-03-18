#include "knionicontext.h"

KniOniContext::KniOniContext(const QString &oniFile)
    : KniContext(),
      mOniFile(oniFile)
{
    initContext();

    xn::EnumerationErrors errors;
    XnStatus statusCode = XN_STATUS_OK;

    statusCode = mXnContext.OpenFileRecording(mOniFile.toLatin1().data(), mXnPlayer);
}

KniOniContext::~KniOniContext()
{
    mXnPlayer.Release();
}

void KniOniContext::update()
{
    KniContext::update();
}

xn::Player& KniOniContext::xnPlayer()
{
    return mXnPlayer;
}
