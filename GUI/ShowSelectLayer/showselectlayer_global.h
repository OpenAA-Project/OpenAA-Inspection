#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SHOWSELECTLAYER_LIB)
#  define SHOWSELECTLAYER_EXPORT Q_DECL_EXPORT
# else
#  define SHOWSELECTLAYER_EXPORT Q_DECL_IMPORT
# endif
#else
# define SHOWSELECTLAYER_EXPORT
#endif
