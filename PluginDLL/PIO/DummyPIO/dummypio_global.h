#ifndef DUMMYPIO_GLOBAL_H
#define DUMMYPIO_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef DUMMYPIO_LIB
# define DUMMYPIO_EXPORT Q_DECL_EXPORT
#else
# define DUMMYPIO_EXPORT Q_DECL_IMPORT
#endif

#endif // DUMMYPIO_GLOBAL_H
