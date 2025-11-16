#ifndef EVOBJBUTTONAUTOINSPECTION_H
#define EVOBJBUTTONAUTOINSPECTION_H

#include "evobjbuttonautoinspection_global.h"
#include "XExecuteVisualizer.h"

class	ButtonAutoInspectionOutput : public RunnerConnectorOut
{
public:
	ButtonAutoInspectionOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("AutoMode");		}

	virtual	bool	GetOutputBool(void);
};

#define	AutoMode_On		1
#define	AutoMode_Off	2

class	RunnerButtonAutoInspection : public RunnerObject
{
	QImage	*ImageModeOn[2];
	QImage	*ImageModeOff[2];
	int		ShowingNumber;
public:
	RunnerButtonAutoInspection(LayersBase *Base ,RunnerMap *rmap);
	~RunnerButtonAutoInspection(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override;
	virtual	void	IntervalExecute(void)						override;

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

#endif // EVOBJBUTTONAUTOINSPECTION_H
