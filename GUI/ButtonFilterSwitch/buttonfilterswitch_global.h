#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(BUTTONFILTERSWITCH_LIB)
#  define BUTTONFILTERSWITCH_EXPORT Q_DECL_EXPORT
# else
#  define BUTTONFILTERSWITCH_EXPORT Q_DECL_IMPORT
# endif
#else
# define BUTTONFILTERSWITCH_EXPORT
#endif
