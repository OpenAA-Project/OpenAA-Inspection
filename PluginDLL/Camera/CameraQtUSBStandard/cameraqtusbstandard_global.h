#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CAMERAQTUSBSTANDARD_LIB)
#  define CAMERAQTUSBSTANDARD_EXPORT Q_DECL_EXPORT
# else
#  define CAMERAQTUSBSTANDARD_EXPORT Q_DECL_IMPORT
# endif
#else
# define CAMERAQTUSBSTANDARD_EXPORT
#endif
