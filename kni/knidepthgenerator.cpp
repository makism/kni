#include "knidepthgenerator.h"

KniDepthGenerator::KniDepthGenerator(KniContext* context)
    : KniGenerator(context),
      mDepthRaw(0)
{
    XnStatus result = XN_STATUS_OK;
    result = qobject_cast<KniContext*>(parent())->xnContext().FindExistingNode(XN_NODE_TYPE_DEPTH, mXnDepthGen);

    if(result != XN_STATUS_OK) {
        qDebug() << "Not ok!\n";
    }

    qDebug() << xnGetStatusString(result);

    mXnDepthGen.GetMapOutputMode(mXnMapOutput);
    mDepthRaw = new unsigned char[mXnMapOutput.nXRes * mXnMapOutput.nYRes * 4];

    startGenerating();
}

KniDepthGenerator::~KniDepthGenerator()
{
    mXnDepthGen.Release();

    if (mDepthRaw!=0) {
        delete mDepthRaw;
        mDepthRaw = 0;
    }
}

void KniDepthGenerator::update()
{
   mXnDepthGen.GetMetaData(mXnDepthMeta);

   const XnDepthPixel* depth = mXnDepthMeta.Data();

   if (mXnDepthMeta.FrameID() == 0)
       return;

   for (XnUInt16 y = mXnDepthMeta.YOffset(); y < mXnDepthMeta.YRes() + mXnDepthMeta.YOffset(); y++) {
       unsigned char * texture = (unsigned char*)mDepthRaw + y * mXnDepthMeta.XRes() * 4 + mXnDepthMeta.XOffset() * 4;
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

   mDepthImage = QImage(mDepthRaw, mXnMapOutput.nXRes, mXnMapOutput.nYRes, QImage::Format_RGB32);
   QString file("/tmp/depth_%1.jpg");
   file = file.arg(mXnDepthMeta.FrameID());
   mDepthImage.save(file);

   emit updated();
}

xn::DepthGenerator& KniDepthGenerator::xnDepth()
{
    return mXnDepthGen;
}

xn::DepthMetaData& KniDepthGenerator::xnMeta()
{
    return mXnDepthMeta;
}

bool KniDepthGenerator::startGenerating()
{
    XnStatus status = mXnDepthGen.StartGenerating();
    mIsGenerating = (status == XN_STATUS_OK) ? true : false;

    if (mIsGenerating) {
        emit startSuccess();
    } else {
        emit startError(status, xnGetStatusString(status));
    }
}

bool KniDepthGenerator::stopGenerating()
{
    XnStatus status = mXnDepthGen.StopGenerating();
    mIsGenerating = (status == XN_STATUS_OK) ? false : mIsGenerating;

    if (!mIsGenerating) {
        emit stopSuccess();
    } else {
        emit stopError(status, xnGetStatusString(status));
    }
}

int KniDepthGenerator::width() const
{
    return mXnMapOutput.nXRes;
}

int KniDepthGenerator::height() const
{
    return mXnMapOutput.nYRes;
}

int KniDepthGenerator::fps() const
{
    return mXnMapOutput.nFPS;
}

QImage& KniDepthGenerator::depth()
{
    return mDepthImage;
}

unsigned char* KniDepthGenerator::rawDepth() const
{
    return mDepthRaw;
}
