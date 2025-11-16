#ifndef SKIPMARK_GLOBAL_H
#define SKIPMARK_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef SKIPMARK_LIB
# define SKIPMARK_EXPORT Q_DECL_EXPORT
#else
# define SKIPMARK_EXPORT Q_DECL_IMPORT
#endif

#endif // SKIPMARK_GLOBAL_H
