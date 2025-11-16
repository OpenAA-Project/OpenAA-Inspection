#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(ANGLEINSPECTION_LIB)
#  define ANGLEINSPECTION_EXPORT Q_DECL_EXPORT
# else
#  define ANGLEINSPECTION_EXPORT Q_DECL_IMPORT
# endif
#else
# define ANGLEINSPECTION_EXPORT
#endif
