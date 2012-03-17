#ifndef KNI_GLOBAL_H
#define KNI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KNI_LIBRARY)
#  define KNISHARED_EXPORT Q_DECL_EXPORT
#else
#  define KNISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // KNI_GLOBAL_H
