#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(REGULUSWORLDLIBRARY_LIB)
#  define REGULUSWORLDLIBRARY_EXPORT Q_DECL_EXPORT
# else
#  define REGULUSWORLDLIBRARY_EXPORT Q_DECL_IMPORT
# endif
#else
# define REGULUSWORLDLIBRARY_EXPORT
#endif
