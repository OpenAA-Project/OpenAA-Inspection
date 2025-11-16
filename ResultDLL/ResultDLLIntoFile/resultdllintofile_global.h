#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RESULTDLLINTOFILE_LIB)
#  define RESULTDLLINTOFILE_EXPORT Q_DECL_EXPORT
# else
#  define RESULTDLLINTOFILE_EXPORT Q_DECL_IMPORT
# endif
#else
# define RESULTDLLINTOFILE_EXPORT
#endif
