#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PANELRESOLUTIONSIZE_LIB)
#  define PANELRESOLUTIONSIZE_EXPORT Q_DECL_EXPORT
# else
#  define PANELRESOLUTIONSIZE_EXPORT Q_DECL_IMPORT
# endif
#else
# define PANELRESOLUTIONSIZE_EXPORT
#endif
