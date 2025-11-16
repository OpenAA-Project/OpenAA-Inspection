#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(COUNTERIMAGEPANEL_LIB)
#  define COUNTERIMAGEPANEL_EXPORT Q_DECL_EXPORT
# else
#  define COUNTERIMAGEPANEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define COUNTERIMAGEPANEL_EXPORT
#endif
