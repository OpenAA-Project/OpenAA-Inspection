#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SHIFTMARKIMAGEPANEL_LIB)
#  define SHIFTMARKIMAGEPANEL_EXPORT Q_DECL_EXPORT
# else
#  define SHIFTMARKIMAGEPANEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define SHIFTMARKIMAGEPANEL_EXPORT
#endif
