#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(GENERALSTOCKERFAIINO_LIB)
#  define GENERALSTOCKERFAIINO_EXPORT Q_DECL_EXPORT
# else
#  define GENERALSTOCKERFAIINO_EXPORT Q_DECL_IMPORT
# endif
#else
# define GENERALSTOCKERFAIINO_EXPORT
#endif
