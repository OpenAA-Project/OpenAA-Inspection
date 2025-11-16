#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(REPEATCONTROL_LIB)
#  define REPEATCONTROL_EXPORT Q_DECL_EXPORT
# else
#  define REPEATCONTROL_EXPORT Q_DECL_IMPORT
# endif
#else
# define REPEATCONTROL_EXPORT
#endif
