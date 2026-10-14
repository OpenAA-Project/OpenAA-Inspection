#include "XAlignmentShiftRotationCommon.h"

	
RotationRange::RotationRange(void)
{ 
	MinAngleDegree = 0;
	MaxAngleDegree = 0; 
}

RotationRange::RotationRange(double minAngle,double maxAngle)
	: MinAngleDegree(minAngle),MaxAngleDegree(maxAngle)
{}

RotationRange::RotationRange(const RotationRange &src)
{ 
	MinAngleDegree = src.MinAngleDegree;
	MaxAngleDegree = src.MaxAngleDegree;
}

RotationRange &RotationRange::operator=(const RotationRange &src)
{
	MinAngleDegree = src.MinAngleDegree;
	MaxAngleDegree = src.MaxAngleDegree;
	return *this;
}
bool	RotationRange::operator==(const RotationRange &src)	const
{
	if(MinAngleDegree!=src.MinAngleDegree)	return false;
	if(MaxAngleDegree!=src.MaxAngleDegree)	return false;
	return true;
}

bool	RotationRange::operator!=(const RotationRange &src)	const
{
	if(MinAngleDegree!=src.MinAngleDegree)	return true;
	if(MaxAngleDegree!=src.MaxAngleDegree)	return true;
	return false;
}

bool	RotationRange::Save(QIODevice *f)
{
	if(::Save(f,MinAngleDegree)==false)
		return false;
	if(::Save(f,MaxAngleDegree)==false)
		return false;
	return true;
}
bool	RotationRange::Load(QIODevice *f)
{
	if(::Load(f,MinAngleDegree)==false)
		return false;
	if(::Load(f,MaxAngleDegree)==false)
		return false;
	return true;
}

RotationRangeContainer	&RotationRangeContainer::operator=(const RotationRangeContainer &src)
{
	this->RemoveAll();
	for(RotationRange *r=src.GetFirst();r!=NULL;r=r->GetNext()){
		RotationRange *newR = new RotationRange(*r);
		this->AppendList(newR);
	}
	return *this;
}

bool	RotationRangeContainer::operator==(const RotationRangeContainer &src)	const
{
	if(this->GetCount()!=src.GetCount())
		return false;
	RotationRange *a=this->GetFirst();
	RotationRange *b=src.GetFirst();
	while(a!=NULL && b!=NULL){
		if(*a!=*b)
			return false;
		a=a->GetNext();
		b=b->GetNext();
	}
	return true;
}
bool	RotationRangeContainer::operator!=(const RotationRangeContainer &src)	const
{
	return !(*this==src);
}
