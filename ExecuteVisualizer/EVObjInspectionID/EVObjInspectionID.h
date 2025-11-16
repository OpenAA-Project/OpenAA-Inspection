#ifndef EVOBJINSPECTIONID_H
#define EVOBJINSPECTIONID_H

#include "evobjinspectionid_global.h"
#include "XExecuteVisualizer.h"

class	InspectionIDOutput : public RunnerConnectorOut
{
public:
	InspectionIDOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Output");		}
	virtual	int		GetOutputInt(void);
};

class	InspectionIDInput : public RunnerConnectorIn
{
public:
	InspectionIDInput(RunnerObject *parent) : RunnerConnectorIn(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Input");		}
	virtual	void	SetInputInt(int d);
};

class	RunnerInspectionID : public RunnerObject
{
public:
	RunnerInspectionID(LayersBase *Base ,RunnerMap *rmap);
	~RunnerInspectionID(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override{	return 0;	}
	virtual	void	IntervalExecute(void)						override;
protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

#endif // EVOBJINSPECTIONID_H
