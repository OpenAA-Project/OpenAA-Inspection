#ifndef EVOBJCOUNTUP_H
#define EVOBJCOUNTUP_H

#include "evobjcountup_global.h"
#include "XExecuteVisualizer.h"

class	CountUpOutput : public RunnerConnectorOut
{
public:
	CountUpOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Output");		}

	virtual	int		GetOutputInt(void);
};

class	CountUpInput : public RunnerConnectorIn
{
public:
	CountUpInput(RunnerObject *parent) : RunnerConnectorIn(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Input");		}

	virtual	void	SetInputInt(int d);
};

class	RunnerCountUp : public RunnerObject
{
public:
	int	Value;

	RunnerCountUp(LayersBase *Base ,RunnerMap *rmap);
	~RunnerCountUp(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override{	return 0;	}
	virtual	void	IntervalExecute(void)						override;

	int		GetValue(void)	{	return Value;	}
protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

#endif // EVOBJCOUNTUP_H
