#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PIOOPENAACAM1B_LIB)
#  define PIOOPENAACAM1B_EXPORT Q_DECL_EXPORT
# else
#  define PIOOPENAACAM1B_EXPORT Q_DECL_IMPORT
# endif
#else
# define PIOOPENAACAM1B_EXPORT
#endif
