#ifndef EVOBJCHANGEDLOT_H
#define EVOBJCHANGEDLOT_H

#include "evobjchangedlot_global.h"
#include "XExecuteVisualizer.h"
#include "XTypeDef.h"

class	ChangedLotOutput : public RunnerConnectorOut
{
public:
	ChangedLotOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("LotChanged");		}
	virtual	bool	GetOutputBool(void);
};

#define	ChangedLotMode_On	1
#define	ChangedLotMode_Off	2

class	RunnerChangedLot : public RunnerObject
{
	QImage		*ImageModeOn[6];
	QImage		*ImageModeOff[6];
	int			ShowingNumber;
	int32		LastLotAutoCount;
	DWORD		LastTimeToChange;
public:
	RunnerChangedLot(LayersBase *Base ,RunnerMap *rmap);
	~RunnerChangedLot(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override;
	virtual	void	IntervalExecute(void)						override;
protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};
#endif // EVOBJCHANGEDLOT_H
