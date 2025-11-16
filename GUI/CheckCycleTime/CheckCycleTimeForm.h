#ifndef CHECKCYCLETIMEFORM_H
#define CHECKCYCLETIMEFORM_H

#include <QDialog>
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class CheckCycleTimeForm;
}
class	SignalOperandBit;

class	CycleTimeList : public NPList<CycleTimeList>
{
	DWORD	CycleTime;
public:
	CycleTimeList(DWORD d)	{	CycleTime=d;	}

	int	GetCycleTime(void)	{	return CycleTime;	}
};

class	CycleTimeContainer : public NPListPack<CycleTimeList>
{
public:
	CycleTimeContainer(void){}

	void	AddCycleTime(DWORD d);
	bool	IsAverageTimeAvailable(void);
	DWORD	GetAverageCycleTime(void);
};


class CheckCycleTimeForm : public GUIFormBase
{
    Q_OBJECT
    
	CycleTimeContainer	CTime;
	DWORD				LastTime;
public:
	SignalOperandBit	*iCycleDone;
	SignalOperandBit	*iError;

    explicit CheckCycleTimeForm(LayersBase *Base ,QWidget *parent = 0);
    ~CheckCycleTimeForm();
    
    virtual	void	Prepare(void)		override;
	virtual	void	BuildForShow(void)	override;

private slots:
    void on_pushButtonSet_clicked();
	void	OperandChanged();
	void	OperandClearChanged();
private:
    Ui::CheckCycleTimeForm *ui;
};

#endif // CHECKCYCLETIMEFORM_H
