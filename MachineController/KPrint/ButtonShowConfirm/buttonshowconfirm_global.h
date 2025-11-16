#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(BUTTONSHOWCONFIRM_LIB)
#  define BUTTONSHOWCONFIRM_EXPORT Q_DECL_EXPORT
# else
#  define BUTTONSHOWCONFIRM_EXPORT Q_DECL_IMPORT
# endif
#else
# define BUTTONSHOWCONFIRM_EXPORT
#endif
