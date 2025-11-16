#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(ROBOTACTION_LIB)
#  define ROBOTACTION_EXPORT Q_DECL_EXPORT
# else
#  define ROBOTACTION_EXPORT Q_DECL_IMPORT
# endif
#else
# define ROBOTACTION_EXPORT
#endif
