#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(BUTTONSHADOWTOSHOW_LIB)
#  define BUTTONSHADOWTOSHOW_EXPORT Q_DECL_EXPORT
# else
#  define BUTTONSHADOWTOSHOW_EXPORT Q_DECL_IMPORT
# endif
#else
# define BUTTONSHADOWTOSHOW_EXPORT
#endif
