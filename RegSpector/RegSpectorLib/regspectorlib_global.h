#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(REGSPECTORLIB_LIB)
#  define REGSPECTORLIB_EXPORT Q_DECL_EXPORT
# else
#  define REGSPECTORLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define REGSPECTORLIB_EXPORT
#endif
