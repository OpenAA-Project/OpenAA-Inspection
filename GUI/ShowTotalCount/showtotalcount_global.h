#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SHOWTOTALCOUNT_LIB)
#  define SHOWTOTALCOUNT_EXPORT Q_DECL_EXPORT
# else
#  define SHOWTOTALCOUNT_EXPORT Q_DECL_IMPORT
# endif
#else
# define SHOWTOTALCOUNT_EXPORT
#endif
