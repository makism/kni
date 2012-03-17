#include <QtCore/QCoreApplication>

#include "kni.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    KniOniContext context("/home/makism/Temp/ONIs/me.oni");
//    KniDepthGenerator depth(&context);
    KniDepthGenerator& depth = context.depthGenerator();

    for (int i=0; i<100; i++) {
        context.update();
        depth.update();
    }

//    return a.exec();
}
