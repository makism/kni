#ifndef KNIIMAGEGENERATOR_H
#define KNIIMAGEGENERATOR_H

#include "kni_global.h"
#include "kni_namespace.h"
#include "knicontext.h"
#include "knigenerator.h"

class KniImageGenerator : public KniGenerator
{
    Q_OBJECT
    Q_DISABLE_COPY(KniImageGenerator)

    friend class KniContext;

public:
    KniImageGenerator();
    explicit KniImageGenerator(KniContext* context);
    virtual ~KniImageGenerator();

    bool startGenerating();
    bool stopGenerating();

protected:
    void update();
};

#endif // KNIIMAGEGENERATOR_H
