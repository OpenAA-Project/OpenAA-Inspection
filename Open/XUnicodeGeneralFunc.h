#if	!defined(XUNICODEGENERALFUNC_H)
#define	XUNICODEGENERALFUNC_H

#include<QIODevice>
#include"XTypeDef.h"

bool	Save(QIODevice *f,wchar_t *d);
bool	Load(QIODevice *f,wchar_t *d,int64 &len ,int64 maxbuffsize);

#endif