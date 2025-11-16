#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(EASYBCODEIMAGEPANEL_LIB)
#  define EASYBCODEIMAGEPANEL_EXPORT Q_DECL_EXPORT
# else
#  define EASYBCODEIMAGEPANEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define EASYBCODEIMAGEPANEL_EXPORT
#endif
