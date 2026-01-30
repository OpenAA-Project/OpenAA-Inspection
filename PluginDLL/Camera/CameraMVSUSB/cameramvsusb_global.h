#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CAMERAMVSUSB_LIB)
#  define CAMERAMVSUSB_EXPORT Q_DECL_EXPORT
# else
#  define CAMERAMVSUSB_EXPORT Q_DECL_IMPORT
# endif
#else
# define CAMERAMVSUSB_EXPORT
#endif
