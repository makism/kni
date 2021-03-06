#ifndef KNI_GLOBAL_H
#define KNI_GLOBAL_H

#include <kdemacros.h>

#if defined(KNI_LIBRARY)
#  define KNISHARED_EXPORT KDE_EXPORT
#else
#  define KNISHARED_EXPORT KDE_IMPORT
#endif

# ifndef KNISHARED_EXPORT_DEPRECATED
#  define KNISHARED_EXPORT_DEPRECATED KDE_DEPRECATED KNISHARED_EXPORT
# endif

#endif // KNI_GLOBAL_H
