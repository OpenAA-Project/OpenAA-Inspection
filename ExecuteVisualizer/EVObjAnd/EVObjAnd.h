#ifndef EVOBJAND_H
#define EVOBJAND_H

#include "evobjand_global.h"
#include "XExecuteVisualizer.h"

class	AndOutput : public RunnerConnectorOut
{
public:
	AndOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("Output");		}

	virtual	bool		GetOutputBool(void);
};

class	AndInput : public RunnerConnectorIn
{
public:
	int	Number;

	AndInput(RunnerObject *parent ,int n) : RunnerConnectorIn(parent),Number(n){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("Input")+QString::number(Number);	}
};

class	EVObjAnd : public RunnerObject
{
public:
	int	InputNumb;
	bool	Value;

	EVObjAnd(LayersBase *Base ,RunnerMap *rmap);
	~EVObjAnd(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override{	return 0;	}
	virtual	void	IntervalExecute(void)						override;

	void	SetInputConnectors(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	bool		GetValue(void)	{	return Value;	}

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};
#endif // EVOBJAND_H
