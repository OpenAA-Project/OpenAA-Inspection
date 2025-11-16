#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(TRIALTERM_LIB)
#  define TRIALTERM_EXPORT Q_DECL_EXPORT
# else
#  define TRIALTERM_EXPORT Q_DECL_IMPORT
# endif
#else
# define TRIALTERM_EXPORT
#endif
