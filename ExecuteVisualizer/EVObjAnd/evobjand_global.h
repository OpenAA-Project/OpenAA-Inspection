#ifndef EVOBJAND_GLOBAL_H
#define EVOBJAND_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef EVOBJAND_LIB
# define EVOBJAND_EXPORT Q_DECL_EXPORT
#else
# define EVOBJAND_EXPORT Q_DECL_IMPORT
#endif

#endif // EVOBJAND_GLOBAL_H
