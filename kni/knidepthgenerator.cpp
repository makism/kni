#include "knidepthgenerator.h"

KniDepthGenerator::KniDepthGenerator()
    : KniGenerator(),
      m_depthRaw(0)
{
}

KniDepthGenerator::KniDepthGenerator(KniContext* context)
    : KniGenerator(context),
      m_depthRaw(0)
{
    XnStatus result = XN_STATUS_OK;
    result = context->xnContext().FindExistingNode(XN_NODE_TYPE_DEPTH, m_xnDepthGen);

//    if(result != XN_STATUS_OK) {
//        qDebug() << "Not ok!\n";
//    }

//    qDebug() << xnGetStatusString(result);

    m_xnDepthGen.GetMapOutputMode(m_xnMapOutput);
    m_depthRaw = new unsigned char[m_xnMapOutput.nXRes * m_xnMapOutput.nYRes * 4];

    startGenerating();
}

KniDepthGenerator::~KniDepthGenerator()
{
    m_xnDepthGen.Release();

    if (m_depthRaw != 0) {
        delete m_depthRaw;
        m_depthRaw = 0;
    }
}

void KniDepthGenerator::update()
{
    m_xnDepthGen.GetMetaData(m_xnDepthMeta);

    const XnDepthPixel* depth = m_xnDepthMeta.Data();

    if (m_xnDepthMeta.FrameID() == 0)
       return;

    for (XnUInt16 y = m_xnDepthMeta.YOffset(); y < m_xnDepthMeta.YRes() + m_xnDepthMeta.YOffset(); ++y) {
        unsigned char * texture = (unsigned char*)m_depthRaw + y * m_xnDepthMeta.XRes() * 4 + m_xnDepthMeta.XOffset() * 4;
        for (XnUInt16 x = 0; x < m_xnDepthMeta.XRes(); ++x, ++depth, texture += 4) {
            XnUInt8 red = 0;
            XnUInt8 green = 0;
            XnUInt8 blue = 0;
            XnUInt8 alpha = 255;

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

    // Make this optional; will speed up things?
    m_depthImage = QImage(m_depthRaw, m_xnMapOutput.nXRes, m_xnMapOutput.nYRes, QImage::Format_RGB32);

    emit updated();
}

xn::DepthGenerator& KniDepthGenerator::xnDepth()
{
    return m_xnDepthGen;
}

xn::DepthMetaData& KniDepthGenerator::xnMeta()
{
    return m_xnDepthMeta;
}

bool KniDepthGenerator::startGenerating()
{
    XnStatus status = m_xnDepthGen.StartGenerating();
    m_isGenerating = (status == XN_STATUS_OK) ? true : false;

    if (m_isGenerating) {
        emit startSuccess();
    } else {
        emit startError(status, xnGetStatusString(status));
    }
}

bool KniDepthGenerator::stopGenerating()
{
    XnStatus status = m_xnDepthGen.StopGenerating();
    m_isGenerating = (status == XN_STATUS_OK) ? false : m_isGenerating;

    if (!m_isGenerating) {
        emit stopSuccess();
    } else {
        emit stopError(status, xnGetStatusString(status));
    }
}

int KniDepthGenerator::width() const
{
    return m_xnMapOutput.nXRes;
}

int KniDepthGenerator::height() const
{
    return m_xnMapOutput.nYRes;
}

int KniDepthGenerator::fps() const
{
    return m_xnMapOutput.nFPS;
}

QImage KniDepthGenerator::depthAsImage()
{
    return m_depthImage;
}

unsigned char* KniDepthGenerator::rawDepth() const
{
    return m_depthRaw;
}
