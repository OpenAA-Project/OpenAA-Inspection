#ifndef PROCESS3D_GLOBAL_H
#define PROCESS3D_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PROCESS3D_LIB
# define PROCESS3D_EXPORT Q_DECL_EXPORT
#else
# define PROCESS3D_EXPORT Q_DECL_IMPORT
#endif

#endif // PROCESS3D_GLOBAL_H
