#ifndef EVOBJOR_GLOBAL_H
#define EVOBJOR_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef EVOBJOR_LIB
# define EVOBJOR_EXPORT Q_DECL_EXPORT
#else
# define EVOBJOR_EXPORT Q_DECL_IMPORT
#endif

#endif // EVOBJOR_GLOBAL_H
