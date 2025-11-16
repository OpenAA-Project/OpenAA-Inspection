#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DISPLAYTARGETLIST_LIB)
#  define DISPLAYTARGETLIST_EXPORT Q_DECL_EXPORT
# else
#  define DISPLAYTARGETLIST_EXPORT Q_DECL_IMPORT
# endif
#else
# define DISPLAYTARGETLIST_EXPORT
#endif
