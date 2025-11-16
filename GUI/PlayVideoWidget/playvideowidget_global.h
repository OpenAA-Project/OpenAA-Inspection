#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PLAYVIDEOWIDGET_LIB)
#  define PLAYVIDEOWIDGET_EXPORT Q_DECL_EXPORT
# else
#  define PLAYVIDEOWIDGET_EXPORT Q_DECL_IMPORT
# endif
#else
# define PLAYVIDEOWIDGET_EXPORT
#endif
