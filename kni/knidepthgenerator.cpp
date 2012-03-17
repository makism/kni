#include "knidepthgenerator.h"

KniDepthGenerator::KniDepthGenerator(KniContext* context)
    : mKniContext(context),
      mRawDepth(0)
{
    XnStatus result = XN_STATUS_OK;
    result = mKniContext->xnContext().FindExistingNode(XN_NODE_TYPE_DEPTH, mXnDepthGen);

    if(result != XN_STATUS_OK) {
        qDebug() << "Not ok!\n";
    }

    qDebug() << xnGetStatusString(result);


    mRawDepth = new unsigned char[640 * 480 * 4];
    mXnDepthGen.StartGenerating();
}

KniDepthGenerator::~KniDepthGenerator()
{
    mXnDepthGen.Release();

    if (mRawDepth!=0) {
        delete mRawDepth;
        mRawDepth = 0;
    }
}

void KniDepthGenerator::update()
{
   mXnDepthGen.GetMetaData(mXnDepthMeta);

   const XnDepthPixel* depth = mXnDepthMeta.Data();

   if (mXnDepthMeta.FrameID() == 0)
       return;

   qDebug() << "update\n";

   for (XnUInt16 y = mXnDepthMeta.YOffset(); y < mXnDepthMeta.YRes() + mXnDepthMeta.YOffset(); y++) {
       unsigned char * texture = (unsigned char*)mRawDepth + y * mXnDepthMeta.XRes() * 4 + mXnDepthMeta.XOffset() * 4;
       for (XnUInt16 x = 0; x < mXnDepthMeta.XRes(); x++, depth++, texture += 4) {
           XnUInt8 red = 0;
           XnUInt8 green = 0;
           XnUInt8 blue = 0;
           XnUInt8 alpha = 255;

           XnUInt16 col_index;

           XnUInt8 a = (XnUInt8)(((*depth) / ( 10000 / 255)));
           red = a;
           green = a;
           blue = a;


           texture[0] = red;
           texture[1] = green;
           texture[2] = blue;

           if (*depth == 0)
               texture[3] = 0;
           else
               texture[3] = alpha;
       }
   }

   mImgDepth = QImage(mRawDepth, 640, 480, QImage::Format_RGB32);
   QString file("/tmp/depth_%1.jpg");
   file = file.arg(mXnDepthMeta.FrameID());
   mImgDepth.save(file);
}
