#if	!defined(XBlockManualExecuter_h)
#define	XBlockManualExecuter_h

#include "XManualExecuter.h"
#include "XBlockInspection.h"
#include "XGeneralFunc.h"

class	ManualExecuterBlockBBrightL : public ManualExecuterItem
{
public:
	int32	NewValue;

	ManualExecuterBlockBBrightL(int v) : ManualExecuterItem(1),NewValue(v){}

	virtual	ManualExecuterItem	*Create(void)	{	return new ManualExecuterBlockBBrightL(0);	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(AlgorithmItemRoot *item);
};
class	ManualExecuterBlockBBrightH : public ManualExecuterItem
{
public:
	int32	NewValue;

	ManualExecuterBlockBBrightH(int v) : ManualExecuterItem(2),NewValue(v){}

	virtual	ManualExecuterItem	*Create(void)	{	return new ManualExecuterBlockBBrightH(0);	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(AlgorithmItemRoot *item);
};

class	ManualExecuterBlockNBrightL : public ManualExecuterItem
{
public:
	int32	NewValue;

	ManualExecuterBlockNBrightL(int v) : ManualExecuterItem(3),NewValue(v){}

	virtual	ManualExecuterItem	*Create(void)	{	return new ManualExecuterBlockNBrightL(0);	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(AlgorithmItemRoot *item);
};
class	ManualExecuterBlockNBrightH : public ManualExecuterItem
{
public:
	int32	NewValue;

	ManualExecuterBlockNBrightH(int v) : ManualExecuterItem(4),NewValue(v){}

	virtual	ManualExecuterItem	*Create(void)	{	return new ManualExecuterBlockNBrightH(0);	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(AlgorithmItemRoot *item);
};


#endif