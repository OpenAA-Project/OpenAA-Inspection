#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CAMERAXTIUMPX8REPEAT_LIB)
#  define CAMERAXTIUMPX8REPEAT_EXPORT Q_DECL_EXPORT
# else
#  define CAMERAXTIUMPX8REPEAT_EXPORT Q_DECL_IMPORT
# endif
#else
# define CAMERAXTIUMPX8REPEAT_EXPORT
#endif
