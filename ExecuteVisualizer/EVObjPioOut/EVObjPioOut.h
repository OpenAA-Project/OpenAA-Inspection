#ifndef EVOBJPIOOUT_H
#define EVOBJPIOOUT_H

#include "evobjpioout_global.h"
#include "XExecuteVisualizer.h"

class	PIOOutInput : public RunnerConnectorIn
{
public:
	PIOOutInput(RunnerObject *parent) : RunnerConnectorIn(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("InBit");		}
	virtual	void	SetInputBool(bool b);
};

class	RunnerPIOOut : public RunnerObject
{
	QImage	*ImageOn[2];
	QImage	*ImageOff[2];
	int		ShowingNumber;
public:
	int		BoardNumber;
	int		Port;
	int		BitNumber;

	RunnerPIOOut(LayersBase *Base ,RunnerMap *rmap);
	~RunnerPIOOut(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override{	return 0;	}
	virtual	void	IntervalExecute(void)						override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	void	SetPIOData(bool d);
protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;

	bool	GetPIOData(void);
};

#endif // EVOBJPIOOUT_H
