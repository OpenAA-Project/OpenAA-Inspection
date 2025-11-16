#ifndef EVOBJOR_H
#define EVOBJOR_H

#include "evobjor_global.h"
#include "XExecuteVisualizer.h"

class	OrOutput : public RunnerConnectorOut
{
public:
	OrOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("Output");		}

	virtual	bool		GetOutputBool(void);
};

class	OrInput : public RunnerConnectorIn
{
public:
	int	Number;

	OrInput(RunnerObject *parent ,int n) : RunnerConnectorIn(parent),Number(n){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("Input")+QString::number(Number);	}
};

class	EVObjOr : public RunnerObject
{
public:
	int	InputNumb;
	bool	Value;

	EVObjOr(LayersBase *Base ,RunnerMap *rmap);
	~EVObjOr(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override{	return 0;	}
	virtual	void	IntervalExecute(void)						override;

	void	SetInputConnectors(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	bool		GetValue(void)	{	return Value;	}

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};
#endif // EVOBJOR_H
