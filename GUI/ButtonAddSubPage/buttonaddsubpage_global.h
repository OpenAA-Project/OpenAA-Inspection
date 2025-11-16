#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(BUTTONADDSUBPAGE_LIB)
#  define BUTTONADDSUBPAGE_EXPORT Q_DECL_EXPORT
# else
#  define BUTTONADDSUBPAGE_EXPORT Q_DECL_IMPORT
# endif
#else
# define BUTTONADDSUBPAGE_EXPORT
#endif
