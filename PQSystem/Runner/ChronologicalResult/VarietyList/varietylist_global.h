#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(VARIETYLIST_LIB)
#  define VARIETYLIST_EXPORT Q_DECL_EXPORT
# else
#  define VARIETYLIST_EXPORT Q_DECL_IMPORT
# endif
#else
# define VARIETYLIST_EXPORT
#endif
