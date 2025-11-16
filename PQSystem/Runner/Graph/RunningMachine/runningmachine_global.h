#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RUNNINGMACHINE_LIB)
#  define RUNNINGMACHINE_EXPORT Q_DECL_EXPORT
# else
#  define RUNNINGMACHINE_EXPORT Q_DECL_IMPORT
# endif
#else
# define RUNNINGMACHINE_EXPORT
#endif
