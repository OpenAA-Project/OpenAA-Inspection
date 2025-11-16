#ifndef EVOBJPROCESSOR_H
#define EVOBJPROCESSOR_H

#include "evobjprocessor_global.h"
#include "XExecuteVisualizer.h"

class	ProcessorFinishOutput : public RunnerConnectorOut
{
public:
	ProcessorFinishOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("Finish Output");	}
	virtual	bool	GetOutputBool(void);
};

class	ProcessorStartInput : public RunnerConnectorIn
{
public:
	ProcessorStartInput(RunnerObject *parent) : RunnerConnectorIn(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("StartIn");		}
	virtual	void	SetInputBool(bool b);
};

class	ProcessorCancalInput : public RunnerConnectorIn
{
public:
	ProcessorCancalInput(RunnerObject *parent) : RunnerConnectorIn(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("CancelIn");		}
	virtual	void	SetInputBool(bool b);
};

#define	StateProcessor_Waiting				1
#define	StateProcessor_Running				2

class	RunnerProcessor : public RunnerObject
{
	QImage	*WaitingImage[12];
	QImage	*RunningImage[9];
	int		ShowingNumber;

public:
	bool	ModeStartCalc;

	RunnerProcessor(LayersBase *Base ,RunnerMap *rmap);
	~RunnerProcessor(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override;
	virtual	void	IntervalExecute(void)						override;

	void	StartCalc(void);
	void	CancelCalc(void);

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

#endif // EVOBJPROCESSOR_H
