#if	!defined(XTREEMASTERCOMMON_H)
#define	XTREEMASTERCOMMON_H

#include "XFlexArea.h"
#include "XColorSpace.h"
#include "NListComp.h"


class	AreaWithColor : public NPListSaveLoad<AreaWithColor>
{
public:
	FlexArea	Area;
	ColorLogic	Color;

	AreaWithColor(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	FlexArea	&GetArea(void)	{	return Area;	}
	void	MoveTo(int dx ,int dy);
};

class	AreaWithColorContainer : public NPListPackSaveLoad<AreaWithColor>
{
public:
	AreaWithColorContainer(void){}

	virtual	AreaWithColor	*Create(void){	return new AreaWithColor();	}
	void	MoveTo(int dx ,int dy);
};


#endif