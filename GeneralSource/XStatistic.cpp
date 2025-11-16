#include "XTypeDef.h"
#include "XStatistic.h"

StackForAverage::StackForAverage(int MaxCount)
{
	ValueDim=new DWORD[MaxCount];
	MaxValue=0;
	MinValue=0;
	AllocatedCount=MaxCount;
	WPoint=0;
	StackedCount=0;
	LastTime=0;
}
StackForAverage::StackForAverage(const StackForAverage &src)
{
	ValueDim=new DWORD[src.AllocatedCount];
	MaxValue	=src.MaxValue;
	MinValue	=src.MinValue;
	AllocatedCount=src.AllocatedCount;
	WPoint		=src.WPoint		;
	StackedCount=src.StackedCount;
	LastTime	=src.LastTime	;
	if(AllocatedCount!=0){
		memcpy(ValueDim,src.ValueDim,AllocatedCount*sizeof(DWORD));
	}
}

StackForAverage::~StackForAverage()
{
	if(ValueDim!=NULL){
		delete	[]ValueDim;
		ValueDim=NULL;
	}
	MaxValue=0;
	MinValue=0;
	AllocatedCount=0;
	WPoint=0;
	StackedCount=0;
}

StackForAverage	&StackForAverage::operator=(const StackForAverage &src)
{
	if(this!=&src){
		if(AllocatedCount!=src.AllocatedCount){
			delete	[]ValueDim;
			ValueDim=new DWORD[src.AllocatedCount];
		}
		MaxValue	=src.MaxValue;
		MinValue	=src.MinValue;
		AllocatedCount=src.AllocatedCount;
		WPoint		=src.WPoint		;
		StackedCount=src.StackedCount;
		LastTime	=src.LastTime	;
		if(AllocatedCount!=0){
			memcpy(ValueDim,src.ValueDim,AllocatedCount*sizeof(DWORD));
		}
	}
	return *this;
}

void	StackForAverage::SetCurrentMilisec(DWORD d)
{
	if(StackedCount==0 && LastTime==0){
		LastTime=d;
	}
	else{
		DWORD	s=d-LastTime;
		ValueDim[WPoint]=s;
		WPoint++;
		StackedCount++;
		LastTime=d;
		if(MaxValue<s)
			MaxValue=s;
		if(MinValue>s)
			MinValue=s;
		if(WPoint>=AllocatedCount){
			WPoint=0;
		}
		if(StackedCount>AllocatedCount){
			StackedCount=AllocatedCount;
		}
	}
}
void	StackForAverage::SetValue(DWORD d)
{
	ValueDim[WPoint]=d;
	WPoint++;
	StackedCount++;
	if(MaxValue<d)
		MaxValue=d;
	if(MinValue>d)
		MinValue=d;
	if(WPoint>=AllocatedCount){
		WPoint=0;
	}
	if(StackedCount>AllocatedCount){
		StackedCount=AllocatedCount;
	}
}
double	StackForAverage::GetAverage(void)
{
	if(StackedCount==0)
		return 0.0;
	double	Value=0;
	for(int i=0;i<StackedCount;i++){
		Value+=ValueDim[i];
	}
	return Value/StackedCount;
}
DWORD	StackForAverage::GetMaximum(void)
{
	return MaxValue;
}
DWORD	StackForAverage::GetMinimum(void)
{
	return MinValue;
}
int		StackForAverage::GetStackedCount(void)
{
	return StackedCount;
}
DWORD	StackForAverage::GetValue(int n)
{
	if(StackedCount<=n)
		return 0;
	int	k=WPoint-n-1;
	if(k<0){
		k+=AllocatedCount;
	}
	return ValueDim[k];
}
void	StackForAverage::Clear(void)
{
	MaxValue=0;
	MinValue=0;
	WPoint=0;
	StackedCount=0;
	LastTime=0;
}
DWORD	StackForAverage::GetLastTime(void)
{
	return LastTime;
}
DWORD	StackForAverage::GetSpanToLastTime(void)
{
	return GetValue(0);
}
DWORD	StackForAverage::GetSpanToLastTime(DWORD CurrentMilisec)
{
	return CurrentMilisec-LastTime;
}