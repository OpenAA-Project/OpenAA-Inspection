#ifndef EVOBJADD_H
#define EVOBJADD_H

#include "evobjadd_global.h"
#include "XExecuteVisualizer.h"

class	AddOutput : public RunnerConnectorOut
{
public:
	AddOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Output");		}

	virtual	int		GetOutputInt(void);
};

class	AddInput : public RunnerConnectorIn
{
public:
	int	Number;

	AddInput(RunnerObject *parent ,int n) : RunnerConnectorIn(parent),Number(n){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Input")+QString::number(Number);	}
};

class	EVObjAdd : public RunnerObject
{
public:
	int	InputNumb;
	int	Value;

	EVObjAdd(LayersBase *Base ,RunnerMap *rmap);
	~EVObjAdd(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override{	return 0;	}
	virtual	void	IntervalExecute(void)						override;

	void	SetInputConnectors(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	int		GetValue(void)	{	return Value;	}
protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

#endif // EVOBJADD_H
