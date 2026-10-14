#pragma once
#include "NListComp.h"

class   RotationRange : public NPListSaveLoad<RotationRange>
{
public:
	double	MinAngleDegree;	
	double	MaxAngleDegree;	

	RotationRange(void);
	RotationRange(double minAngle,double maxAngle);
	RotationRange(const RotationRange &src);

	RotationRange &operator=(const RotationRange &src);
		
	bool	operator==(const RotationRange &src)	const;
	bool	operator!=(const RotationRange &src)	const;

	bool	Save(QIODevice *f)	override;
	bool	Load(QIODevice *f)	override;
};

class RotationRangeContainer : public NPListPackSaveLoad<RotationRange>
{
public:
	RotationRangeContainer(void){}
	virtual	RotationRange	*Create(void)	{	return new RotationRange();	}

	RotationRangeContainer	&operator=(const RotationRangeContainer &src);

	bool	operator==(const RotationRangeContainer &src)	const;
	bool	operator!=(const RotationRangeContainer &src)	const;
};

