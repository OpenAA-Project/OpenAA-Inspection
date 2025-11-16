#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(FILTERMERGECOLOR_LIB)
#  define FILTERMERGECOLOR_EXPORT Q_DECL_EXPORT
# else
#  define FILTERMERGECOLOR_EXPORT Q_DECL_IMPORT
# endif
#else
# define FILTERMERGECOLOR_EXPORT
#endif
