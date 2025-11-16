#ifndef THINMETAL_GLOBAL_H
#define THINMETAL_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef THINMETAL_LIB
# define THINMETAL_EXPORT Q_DECL_EXPORT
#else
# define THINMETAL_EXPORT Q_DECL_IMPORT
#endif

#endif // THINMETAL_GLOBAL_H
