#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LIGHTOPENAACAM1B_LIB)
#  define LIGHTOPENAACAM1B_EXPORT Q_DECL_EXPORT
# else
#  define LIGHTOPENAACAM1B_EXPORT Q_DECL_IMPORT
# endif
#else
# define LIGHTOPENAACAM1B_EXPORT
#endif
