#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(ROBOTACTIONEDITPANEL_LIB)
#  define ROBOTACTIONEDITPANEL_EXPORT Q_DECL_EXPORT
# else
#  define ROBOTACTIONEDITPANEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define ROBOTACTIONEDITPANEL_EXPORT
#endif
