#ifndef EVOBJRESULT_H
#define EVOBJRESULT_H

#include "evobjresult_global.h"
#include "XExecuteVisualizer.h"

class	ResultEmitCommonOutput : public RunnerConnectorOut
{
public:
	ResultEmitCommonOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("EmitCommon");	}
	virtual	bool	GetOutputBool(void);
};

class	ResultEmitAllPagesOutput : public RunnerConnectorOut
{
public:
	ResultEmitAllPagesOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("EmitPages");	}
	virtual	bool	GetOutputBool(void);
};

class	ResultErrorOutput : public RunnerConnectorOut
{
public:
	ResultErrorOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("Error");		}
	virtual	bool	GetOutputBool(void);
};


class	ResultStartInput : public RunnerConnectorIn
{
public:
	ResultStartInput(RunnerObject *parent) : RunnerConnectorIn(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("ResultIn");		}
	virtual	void	SetInputBool(bool b);
};

#define	StateResult_Waiting				1
#define	StateResult_WritingCommon		2
#define	StateResult_WritingPages		3

class	RunnerResult : public RunnerObject
{
	QImage	*WaitingImage[2];
	QImage	*WritingCommonImage[4];
	QImage	*WritingPagesImage[6];
	int		ShowingNumber;
public:
	bool	ModeWriteOut;

	RunnerResult(LayersBase *Base ,RunnerMap *rmap);
	~RunnerResult(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override;
	virtual	void	IntervalExecute(void)						override;

	void	WriteOut(void);

private:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

#endif // EVOBJRESULT_H
