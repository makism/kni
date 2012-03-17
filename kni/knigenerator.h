#ifndef KNIGENERATOR_H
#define KNIGENERATOR_H

class KniGenerator
{
public:
    KniGenerator();
    ~KniGenerator();

    virtual bool startGenerating() = 0;
    virtual bool stopGenerating() = 0;

    bool isGenerating();

protected:
    bool mIsGenerating;
};

#endif // KNIGENERATOR_H
