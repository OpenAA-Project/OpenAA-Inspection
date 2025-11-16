#ifndef EVOBJSTRATEGYCOUNTER_H
#define EVOBJSTRATEGYCOUNTER_H

#include "evobjstrategycounter_global.h"
#include "XExecuteVisualizer.h"

class	StrategyCounterOutput : public RunnerConnectorOut
{
public:
	StrategyCounterOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Output");		}
	virtual	int		GetOutputInt(void);
};

class	StrategyCounterInput : public RunnerConnectorIn
{
public:
	StrategyCounterInput(RunnerObject *parent) : RunnerConnectorIn(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Input");		}
	virtual	void	SetInputInt(int d);
};

class	RunnerStrategyCounter : public RunnerObject
{
public:
	RunnerStrategyCounter(LayersBase *Base ,RunnerMap *rmap);
	~RunnerStrategyCounter(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override{	return 0;	}
	virtual	void	IntervalExecute(void)						override;
protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

#endif // EVOBJSTRATEGYCOUNTER_H
