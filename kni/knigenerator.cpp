#include "knigenerator.h"

KniGenerator::KniGenerator()
    : mIsGenerating(false)
{

}

KniGenerator::~KniGenerator()
{

}

bool KniGenerator::isGenerating()
{
    return mIsGenerating;
}
