#ifndef EVOBJCURRENTPHASE_H
#define EVOBJCURRENTPHASE_H

#include "evobjcurrentphase_global.h"
#include "XExecuteVisualizer.h"

class	CurrentPhaseOutput : public RunnerConnectorOut
{
public:
	CurrentPhaseOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Output");		}
	virtual	int		GetOutputInt(void);
};

class	CurrentPhaseInput : public RunnerConnectorIn
{
public:
	CurrentPhaseInput(RunnerObject *parent) : RunnerConnectorIn(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Input");		}

	virtual	void	SetInputInt(int d);
};

class	RunnerCurrentPhase : public RunnerObject
{
public:
	RunnerCurrentPhase(LayersBase *Base ,RunnerMap *rmap);
	~RunnerCurrentPhase(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override{	return 0;	}
	virtual	void	IntervalExecute(void)						override;

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};
#endif // EVOBJCURRENTPHASE_H
