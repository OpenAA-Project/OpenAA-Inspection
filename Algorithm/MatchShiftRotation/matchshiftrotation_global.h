#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MATCHSHIFTROTATION_LIB)
#  define MATCHSHIFTROTATION_EXPORT Q_DECL_EXPORT
# else
#  define MATCHSHIFTROTATION_EXPORT Q_DECL_IMPORT
# endif
#else
# define MATCHSHIFTROTATION_EXPORT
#endif
