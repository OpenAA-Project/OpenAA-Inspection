#ifndef ADLINKPIO_GLOBAL_H
#define ADLINKPIO_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef ADLINKPIO_LIB
# define ADLINKPIO_EXPORT Q_DECL_EXPORT
#else
# define ADLINKPIO_EXPORT Q_DECL_IMPORT
#endif

#endif // ADLINKPIO_GLOBAL_H
