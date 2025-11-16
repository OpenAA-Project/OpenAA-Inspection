#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(BUTTONSWITCHSHADE_LIB)
#  define BUTTONSWITCHSHADE_EXPORT Q_DECL_EXPORT
# else
#  define BUTTONSWITCHSHADE_EXPORT Q_DECL_IMPORT
# endif
#else
# define BUTTONSWITCHSHADE_EXPORT
#endif
