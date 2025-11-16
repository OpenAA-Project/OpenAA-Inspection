#ifndef IMAGEBANK_GLOBAL_H
#define IMAGEBANK_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef IMAGEBANK_LIB
# define IMAGEBANK_EXPORT Q_DECL_EXPORT
#else
# define IMAGEBANK_EXPORT Q_DECL_IMPORT
#endif

#endif // IMAGEBANK_GLOBAL_H
