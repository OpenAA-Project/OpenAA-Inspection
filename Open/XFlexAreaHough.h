#pragma once

#include "XTypeDef.h"
#include "XFlexArea.h"

class HoughLine : public NPListSaveLoad<HoughLine>
{
public:
	double	X1,Y1,X2,Y2;
	int		DotCount;

	HoughLine(void);
	~HoughLine(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class HoughLineContainer : public NPListPackSaveLoad<HoughLine>
{
public:
	HoughLineContainer(void){}
	~HoughLineContainer(void){}

	virtual	HoughLine	*Create(void)	{	return new HoughLine();	}
};

//=========================================================================
void	PickupLinesByHough(FlexArea &Area
							,HoughLineContainer &PickedLines
							,int LineArea=2);

void	PickupLinesByHough(PureFlexAreaListContainer &FPack
							,HoughLineContainer &PickedLines
							,int LineArea=2);

