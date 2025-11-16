#ifndef LISTPIECE_GLOBAL_H
#define LISTPIECE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LISTPIECE_LIB
# define LISTPIECE_EXPORT Q_DECL_EXPORT
#else
# define LISTPIECE_EXPORT Q_DECL_IMPORT
#endif

#endif // LISTPIECE_GLOBAL_H
