#ifndef SHOWRESULTSMALLLOTFORM_H
#define SHOWRESULTSMALLLOTFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XStandardPropertyForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDateTime.h"

namespace Ui {
class ShowResultSmallLotForm;
}
class	SignalOperandInt;
class	SignalOperandBit;

class ShowResultSmallLotForm : public GUIFormBase
{
    Q_OBJECT
    
	SignalOperandInt	*iNGStockedCounter;
	SignalOperandBit	*iReqChangeLot;
	SignalOperandBit	*iMutex;
	SignalOperandBit	*iAutoChangeLot;

	int		NGCount;
	int		MaxAutoCount;
	bool	SyncMode;

public:
	QString	SelectedLotID;
	int		LotSubNumber;
	int		MaxSubNumber;
	bool	ChangeToClear;
	bool	TransmitLotInfo;
public:
    explicit ShowResultSmallLotForm(LayersBase *base ,QWidget *parent = 0);
    ~ShowResultSmallLotForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
private:
	void	SetLotToSystem(int iLotAutoCount
						,const QString &iLotID
						,const QString &iLotName
						,int LotCountNumber);
	bool	UpdateSubNumber(int MaxAutoCount , int LotSubNumber);

private:
    Ui::ShowResultSmallLotForm *ui;

	void	ChangeLotAction(void);
private slots:
	void	OperandNGStocked();
	void	OperandChangedLot();
    void on_pushButtonChange_clicked();
};


class	CmdReqShowLot : public GUIDirectMessage
{
public:
	int		IDNumber;
	CmdReqShowLot(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdChangeLot : public GUICmdPacketBase
{
public:
	XDateTime	CurrentInspectTime;

	GUICmdChangeLot(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // SHOWRESULTSMALLLOTFORM_H
