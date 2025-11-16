#ifndef LIGHT500_GLOBAL_H
#define LIGHT500_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LIGHT500_LIB
# define LIGHT500_EXPORT Q_DECL_EXPORT
#else
# define LIGHT500_EXPORT Q_DECL_IMPORT
#endif

#endif // LIGHT500_GLOBAL_H
