#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RESULTCATEGORIZER_LIB)
#  define RESULTCATEGORIZER_EXPORT Q_DECL_EXPORT
# else
#  define RESULTCATEGORIZER_EXPORT Q_DECL_IMPORT
# endif
#else
# define RESULTCATEGORIZER_EXPORT
#endif
