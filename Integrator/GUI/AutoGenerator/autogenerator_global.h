#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(AUTOGENERATOR_LIB)
#  define AUTOGENERATOR_EXPORT Q_DECL_EXPORT
# else
#  define AUTOGENERATOR_EXPORT Q_DECL_IMPORT
# endif
#else
# define AUTOGENERATOR_EXPORT
#endif
