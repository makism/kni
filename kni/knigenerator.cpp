#include "knigenerator.h"


KniGenerator::KniGenerator()
    : m_isValid(false),
      m_isGenerating(false),
      m_doUpdate(false)
{
}

KniGenerator::KniGenerator(QObject* parent)
    : QThread(parent),
      m_isValid(true),
      m_isGenerating(false),
      m_doUpdate(true)
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
        if (m_isGenerating)
            if (m_doUpdate) {
                m_doUpdate = false;
                update();
            }
    }
}

bool KniGenerator::isGenerating()
{
    return m_isGenerating;
}

void KniGenerator::doUpdate()
{
    m_doUpdate = true;
}
