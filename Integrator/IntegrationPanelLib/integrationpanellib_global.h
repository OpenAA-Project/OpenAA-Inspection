#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(INTEGRATIONPANELLIB_LIB)
#  define INTEGRATIONPANELLIB_EXPORT Q_DECL_EXPORT
# else
#  define INTEGRATIONPANELLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define INTEGRATIONPANELLIB_EXPORT
#endif
