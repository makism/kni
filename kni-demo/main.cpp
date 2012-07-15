#include <QCoreApplication>

#include "knionicontext.h"
#include "knidepthgenerator.h"
#include "kniimagegenerator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    KniOniContext context("/opt/temp/ONIs/me.oni");
//    KniDepthGenerator* depth = new KniDepthGenerator(&context);
    KniDepthGenerator depth;
    KniDepthGenerator depth2(&context);

    context.startAll();

    return a.exec();
}
