#include "XUnicodeGeneralFunc.h"
#include "XGeneralFunc.h"
#include<qstring.h>

bool	Save(QIODevice *f,wchar_t *d)
{
	QString	s=QString::fromWCharArray(d);
	return ::Save(f,s);
}
bool	Load(QIODevice *f,wchar_t *d,int64 &len ,int64 maxbuffsize)
{
	QString	dtmp;
	if(::Load(f,dtmp)==false){
		return false;
	}
	memset(d,0,sizeof(wchar_t)*maxbuffsize);
	len=dtmp.toWCharArray(d);
	d[len]=L'\0';
	return true;
}
