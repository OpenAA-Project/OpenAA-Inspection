#ifndef SHAREDPIO_GLOBAL_H
#define SHAREDPIO_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef SHAREDPIO_LIB
# define SHAREDPIO_EXPORT Q_DECL_EXPORT
#else
# define SHAREDPIO_EXPORT Q_DECL_IMPORT
#endif

#endif // SHAREDPIO_GLOBAL_H
