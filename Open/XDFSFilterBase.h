#if	!defined(XDFSFilterBase_h)
#define	XDFSFilterBase_h

#include <QIODevice>

class	XDFSFilterBase
{
public:
	XDFSFilterBase(void){}

	virtual	bool	Save(QIODevice *f)	{	return true;	}
	virtual	bool	Load(QIODevice *f)	{	return true;	}
};

#endif