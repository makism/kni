#include "knigenerator.h"

KniGenerator::KniGenerator(QObject* parent)
    : QThread(parent),
      mIsGenerating(false)
{
    // Inform parent that we have "updated()" in our QThread.
    connect(this, SIGNAL(updated()),
            parent, SLOT(generatorUpdated()));

    // Parent informs us that we can update.
    connect(parent, SIGNAL(updated()),
            this, SLOT(doUpdate()));
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

void KniGenerator::doUpdate()
{

}
