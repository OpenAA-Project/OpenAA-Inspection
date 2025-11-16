#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RASTERIMAGEPANEL_LIB)
#  define RASTERIMAGEPANEL_EXPORT Q_DECL_EXPORT
# else
#  define RASTERIMAGEPANEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define RASTERIMAGEPANEL_EXPORT
#endif
