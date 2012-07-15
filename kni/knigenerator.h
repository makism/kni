#ifndef KNIGENERATOR_H
#define KNIGENERATOR_H

#include <QtCore>
#include <QThread>

#include "knicontext.h"

#include <XnOpenNI.h>
#include <XnCodecIDs.h>
#include <XnCppWrapper.h>


class KniGenerator: public QThread
{
    Q_OBJECT
    Q_DISABLE_COPY(KniGenerator)

    friend class KniContext;

public:
    KniGenerator();
    KniGenerator(QObject* parent);
    virtual ~KniGenerator();

    void run();
    virtual bool startGenerating()= 0;
    virtual bool stopGenerating() = 0;

    bool isGenerating();

protected:
    virtual void update() = 0;

protected slots:
    void doUpdate();

signals:
    void updated();
    void startSuccess();
    void startError(int code, const QString& message);
    void stopSuccess();
    void stopError(int code, const QString& message);

protected:
    bool m_doUpdate;
    bool m_isValid;
    bool m_isGenerating;
};

#endif // KNIGENERATOR_H
