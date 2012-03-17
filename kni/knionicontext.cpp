#include "knionicontext.h"

KniOniContext::KniOniContext()
{
}

KniOniContext::KniOniContext(const QString &oniFile)
    : KniContext(),
      mOniFile(oniFile)
{
    xn::EnumerationErrors errors;
    XnStatus statusCode = mXnContext.Init();

    statusCode = mXnContext.OpenFileRecording(mOniFile.toLatin1().data());

    if(statusCode != XN_STATUS_OK) {
        qDebug() << "Not ok!\n";
    }

    qDebug() << xnGetStatusString(statusCode);
}

KniOniContext::~KniOniContext()
{

}

void KniOniContext::update()
{
    KniContext::update();
}
