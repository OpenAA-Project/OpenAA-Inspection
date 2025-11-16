#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LEARNINGCOMMANDPANEL_LIB)
#  define LEARNINGCOMMANDPANEL_EXPORT Q_DECL_EXPORT
# else
#  define LEARNINGCOMMANDPANEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define LEARNINGCOMMANDPANEL_EXPORT
#endif
