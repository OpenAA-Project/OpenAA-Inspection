#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(REPLACEIMAGEPANEL_LIB)
#  define REPLACEIMAGEPANEL_EXPORT Q_DECL_EXPORT
# else
#  define REPLACEIMAGEPANEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define REPLACEIMAGEPANEL_EXPORT
#endif
