#ifndef KNI_H
#define KNI_H

#define KniServicePath "kni"

#include <QDBusConnection>
#include <KUniqueApplication>


class KNI: public KUniqueApplication
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "kni.kni")

public:
    KNI();
};

#endif // KNI_H
