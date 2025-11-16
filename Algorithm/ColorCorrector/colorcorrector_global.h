#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(COLORCORRECTOR_LIB)
#  define COLORCORRECTOR_EXPORT Q_DECL_EXPORT
# else
#  define COLORCORRECTOR_EXPORT Q_DECL_IMPORT
# endif
#else
# define COLORCORRECTOR_EXPORT
#endif
