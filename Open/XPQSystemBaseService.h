#if	!defined(XPQSystemBaseService_H)
#define	XPQSystemBaseService_H

#include<QString>

class	PQSystemBase;

class	PQSystemBaseService
{
	PQSystemBase	*Base;
public:
	PQSystemBaseService(PQSystemBase *base):Base(base){}
	virtual	~PQSystemBaseService(void){	Base=NULL;	}

	PQSystemBase	*GetPQSystemBase(void){	return Base;	}
};


#endif