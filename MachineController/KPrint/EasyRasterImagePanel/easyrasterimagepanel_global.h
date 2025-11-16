#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(EASYRASTERIMAGEPANEL_LIB)
#  define EASYRASTERIMAGEPANEL_EXPORT Q_DECL_EXPORT
# else
#  define EASYRASTERIMAGEPANEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define EASYRASTERIMAGEPANEL_EXPORT
#endif
