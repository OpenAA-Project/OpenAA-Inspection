#ifndef PANELHIDE_GLOBAL_H
#define PANELHIDE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PANELHIDE_LIB
# define PANELHIDE_EXPORT Q_DECL_EXPORT
#else
# define PANELHIDE_EXPORT Q_DECL_IMPORT
#endif

#endif // PANELHIDE_GLOBAL_H
