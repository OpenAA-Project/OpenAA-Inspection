#ifndef FILTERHSV_GLOBAL_H
#define FILTERHSV_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef FILTERHSV_LIB
# define FILTERHSV_EXPORT Q_DECL_EXPORT
#else
# define FILTERHSV_EXPORT Q_DECL_IMPORT
#endif

#endif // FILTERHSV_GLOBAL_H
