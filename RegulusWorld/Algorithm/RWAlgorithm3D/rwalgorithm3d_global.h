#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RWALGORITHM3D_LIB)
#  define RWALGORITHM3D_EXPORT Q_DECL_EXPORT
# else
#  define RWALGORITHM3D_EXPORT Q_DECL_IMPORT
# endif
#else
# define RWALGORITHM3D_EXPORT
#endif
