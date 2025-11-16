#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PALLETIZEIMAGEPANEL_LIB)
#  define PALLETIZEIMAGEPANEL_EXPORT Q_DECL_EXPORT
# else
#  define PALLETIZEIMAGEPANEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define PALLETIZEIMAGEPANEL_EXPORT
#endif
