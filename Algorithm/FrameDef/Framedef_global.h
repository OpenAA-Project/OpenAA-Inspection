#ifndef FRAMEDEF_GLOBAL_H
#define FRAMEDEF_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef FRAMEDEF_LIB
# define FRAMEDEF_EXPORT Q_DECL_EXPORT
#else
# define FRAMEDEF_EXPORT Q_DECL_IMPORT
#endif

#endif // FRAMEDEF_GLOBAL_H
