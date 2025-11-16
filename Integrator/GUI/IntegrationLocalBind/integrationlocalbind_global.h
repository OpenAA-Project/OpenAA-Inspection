#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(INTEGRATIONLOCALBIND_LIB)
#  define INTEGRATIONLOCALBIND_EXPORT Q_DECL_EXPORT
# else
#  define INTEGRATIONLOCALBIND_EXPORT Q_DECL_IMPORT
# endif
#else
# define INTEGRATIONLOCALBIND_EXPORT
#endif
