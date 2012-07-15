#ifndef KNIONICONTEXT_H
#define KNIONICONTEXT_H

#include <QFile>

#include "kni_global.h"
#include "knicontext.h"


class KniOniContext : public KniContext
{
    Q_OBJECT

public:
    KniOniContext(const QString& oniFile, QObject* parent = 0);
    ~KniOniContext();

    void update();

    xn::Player& xnPlayer();

private:
    const QString m_recording; // convert to QFile?

    xn::Player m_xnPlayer;
};

#endif // KNIONICONTEXT_H
