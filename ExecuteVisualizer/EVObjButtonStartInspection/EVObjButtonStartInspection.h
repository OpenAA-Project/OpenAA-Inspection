#ifndef EVOBJBUTTONSTARTINSPECTION_H
#define EVOBJBUTTONSTARTINSPECTION_H

#include "evobjbuttonstartinspection_global.h"
#include "XExecuteVisualizer.h"

class	ButtonStartInspectionOutput : public RunnerConnectorOut
{
public:
	ButtonStartInspectionOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("StartMode");	}
	virtual	bool	GetOutputBool(void);
};

#define	StartMode_On	1
#define	StartMode_Off	2

class	RunnerButtonStartInspection : public RunnerObject
{
	QImage	*ImageModeOn[2];
	QImage	*ImageModeOff[2];
	int		ShowingNumber;
public:
	RunnerButtonStartInspection(LayersBase *Base ,RunnerMap *rmap);
	~RunnerButtonStartInspection(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override;
	virtual	void	IntervalExecute(void)						override;
protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};
#endif // EVOBJBUTTONSTARTINSPECTION_H
