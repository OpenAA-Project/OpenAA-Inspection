#pragma once

#include "XTypeDef.h"

class StackForAverage
{
	DWORD	*ValueDim;
	DWORD	MaxValue;
	DWORD	MinValue;
	int		AllocatedCount;
	int		WPoint;
	int		StackedCount;
	DWORD	LastTime;
public:
	StackForAverage(int MaxCount);
	StackForAverage(const StackForAverage &src);
	~StackForAverage();

	StackForAverage	&operator=(const StackForAverage &src);

	void	SetCurrentMilisec(DWORD d);
	void	SetValue(DWORD d);
	double	GetAverage(void);
	DWORD	GetMaximum(void);
	DWORD	GetMinimum(void);
	int		GetStackedCount(void);
	DWORD	GetValue(int n);	//Latest:n=0 ,1 older n=1
	void	Clear(void);
	DWORD	GetLastTime(void);
	DWORD	GetSpanToLastTime(void);
	DWORD	GetSpanToLastTime(DWORD CurrentMilisec);
private:

};
