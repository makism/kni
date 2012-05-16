#ifndef KNIONICONTEXT_H
#define KNIONICONTEXT_H

#include <QFile>

#include "kni_global.h"
#include "knicontext.h"


class KniOniContext : public KniContext
{
    Q_OBJECT

public:
    KniOniContext(const QString& oniFile, QObject* parent=0);
    ~KniOniContext();

    void update();

    xn::Player& xnPlayer();

private:
    const QString mOniFile; // convert to QFile?

    xn::Player mXnPlayer;
};

#endif // KNIONICONTEXT_H
