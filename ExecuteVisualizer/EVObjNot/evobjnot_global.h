#ifndef EVOBJNOT_GLOBAL_H
#define EVOBJNOT_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef EVOBJNOT_LIB
# define EVOBJNOT_EXPORT Q_DECL_EXPORT
#else
# define EVOBJNOT_EXPORT Q_DECL_IMPORT
#endif

#endif // EVOBJNOT_GLOBAL_H
