#ifndef EVOBJADD_GLOBAL_H
#define EVOBJADD_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef EVOBJADD_LIB
# define EVOBJADD_EXPORT Q_DECL_EXPORT
#else
# define EVOBJADD_EXPORT Q_DECL_IMPORT
#endif

#endif // EVOBJADD_GLOBAL_H
