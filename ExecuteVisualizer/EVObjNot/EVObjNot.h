#ifndef EVOBJNOT_H
#define EVOBJNOT_H

#include "evobjnot_global.h"
#include "XExecuteVisualizer.h"

class	NotOutput : public RunnerConnectorOut
{
public:
	NotOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("Output");		}

	virtual	bool		GetOutputBool(void);
};

class	NotInput : public RunnerConnectorIn
{
public:
	NotInput(RunnerObject *parent) : RunnerConnectorIn(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("Input");		}
};

class	EVObjNot : public RunnerObject
{
public:
	bool	Value;

	EVObjNot(LayersBase *Base ,RunnerMap *rmap);
	~EVObjNot(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override{	return 0;	}
	virtual	void	IntervalExecute(void)						override;

	bool	GetValue(void)	{	return Value;	}

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};
#endif // EVOBJNOT_H
