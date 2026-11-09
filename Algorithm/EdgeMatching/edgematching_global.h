#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(EDGEMATCHING_LIB)
#  define EDGEMATCHING_EXPORT Q_DECL_EXPORT
# else
#  define EDGEMATCHING_EXPORT Q_DECL_IMPORT
# endif
#else
# define EDGEMATCHING_EXPORT
#endif
