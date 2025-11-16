#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(NETWORKDRIVE_LIB)
#  define NETWORKDRIVE_EXPORT Q_DECL_EXPORT
# else
#  define NETWORKDRIVE_EXPORT Q_DECL_IMPORT
# endif
#else
# define NETWORKDRIVE_EXPORT
#endif
