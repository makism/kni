#include <QtCore/QCoreApplication>

#include "kni.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    KniOniContext context("/home/makism/Temp/ONIs/me.oni");
    KniDepthGenerator& depth = context.depthGenerator();

    context.startAll();

    return a.exec();
}
