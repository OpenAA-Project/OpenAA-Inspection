#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LOCKSTARDLL_LIB)
#  define LOCKSTARDLL_EXPORT Q_DECL_EXPORT
# else
#  define LOCKSTARDLL_EXPORT Q_DECL_IMPORT
# endif
#else
# define LOCKSTARDLL_EXPORT
#endif
