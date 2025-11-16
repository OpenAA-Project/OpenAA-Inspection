#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(ROBOTFAIRINODLL_LIB)
#  define ROBOTFAIRINODLL_EXPORT Q_DECL_EXPORT
# else
#  define ROBOTFAIRINODLL_EXPORT Q_DECL_IMPORT
# endif
#else
# define ROBOTFAIRINODLL_EXPORT
#endif
