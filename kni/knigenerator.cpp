#include "knigenerator.h"

KniGenerator::KniGenerator(QObject* parent)
    : QThread(parent),
      mIsGenerating(false)
{

}

KniGenerator::~KniGenerator()
{

}

void KniGenerator::run()
{
    while (isRunning()) {
        if (mIsGenerating) {
            update();
        }
    }
}

bool KniGenerator::isGenerating()
{
    return mIsGenerating;
}
