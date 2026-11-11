#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(XRAY3DIMAGEPANEL_LIB)
#  define XRAY3DIMAGEPANEL_EXPORT Q_DECL_EXPORT
# else
#  define XRAY3DIMAGEPANEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define XRAY3DIMAGEPANEL_EXPORT
#endif
