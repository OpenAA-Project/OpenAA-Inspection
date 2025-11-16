#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MASTERLOTLIST_LIB)
#  define MASTERLOTLIST_EXPORT Q_DECL_EXPORT
# else
#  define MASTERLOTLIST_EXPORT Q_DECL_IMPORT
# endif
#else
# define MASTERLOTLIST_EXPORT
#endif
