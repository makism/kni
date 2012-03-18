#ifndef KNIGENERATOR_H
#define KNIGENERATOR_H

#include <QtCore>
#include <QThread>

#include <XnOpenNI.h>
#include <XnCodecIDs.h>
#include <XnCppWrapper.h>


class KniGenerator: public QThread
{
    Q_OBJECT

public:
    KniGenerator(QObject* parent);
    virtual ~KniGenerator();

    void run();
    virtual bool startGenerating()= 0;
    virtual bool stopGenerating() = 0;

    bool isGenerating();

protected:
    virtual void update() = 0;

private:
    KniGenerator(const KniGenerator& copy);
    KniGenerator* operator=(const KniGenerator& rhs);

protected slots:
    void slotUpdate();

signals:
    void updated();
    void startSuccess();
    void startError(int errorId, const QString& errorStr);
    void stopSuccess();
    void stopError(int errorId, const QString& errorStr);

protected:
    bool mIsGenerating;
};

#endif // KNIGENERATOR_H
