#ifndef KNIONICONTEXT_H
#define KNIONICONTEXT_H

#include "kni_global.h"
#include "knicontext.h"


class KniOniContext : public KniContext
{
    Q_OBJECT

public:
    KniOniContext();
    KniOniContext(const QString& oniFile);
    ~KniOniContext();

    void update();

private:
    QString mOniFile;
};

#endif // KNIONICONTEXT_H
