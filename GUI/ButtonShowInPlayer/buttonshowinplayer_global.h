#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(BUTTONSHOWINPLAYER_LIB)
#  define BUTTONSHOWINPLAYER_EXPORT Q_DECL_EXPORT
# else
#  define BUTTONSHOWINPLAYER_EXPORT Q_DECL_IMPORT
# endif
#else
# define BUTTONSHOWINPLAYER_EXPORT
#endif
