#ifndef SHOWRESULTMULTIDELIVERYFORM_H
#define SHOWRESULTMULTIDELIVERYFORM_H

#include "XGUIFormBase.h"
#include "XStandardPropertyForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDateTime.h"


namespace Ui {
class ShowResultMultiDeliveryForm;
}
class	SignalOperandInt;
class	SignalOperandBit;
class	ResultXMLMultiDelivery;


class ShowResultMultiDeliveryForm : public GUIFormBase
{
    Q_OBJECT

	class	OperandUnit : public IdentifiedClass 
	{
	public:
		int					Number;
		SignalOperandInt	*iNGStockedCounter;
		SignalOperandBit	*iReqChangeLot;
		QString	SelectedLotID;
		int		LotSubNumber;
		int		StackCount;

		OperandUnit(void);
		~OperandUnit(void);

		void	Initial(int Number ,int SysNoNGStockedCounter,int SysNoReqChangeLot,SeqControlParam	*Param);
	};
	OperandUnit			*OperandDeliver;
	int					AllocatedCount;
	ResultXMLMultiDelivery	*ResultDelivery;

	SignalOperandBit	*iMutex;
	SignalOperandBit	*iAutoChangeLot;

	bool	SyncMode;

public:
	bool	ChangeToClear;
	int		SysNoNGStockedCounter;
	int		SysNoReqChangeLot;

public:
    explicit ShowResultMultiDeliveryForm(LayersBase *base ,QWidget *parent = 0);
    ~ShowResultMultiDeliveryForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
private:
	void SetLotToSystem(int iLotAutoCount
						,const QString &iLotID
						,const QString &iLotName
						,int LotCountNumber);
	bool	ChangeLotAction(int n);
	void	ShowHeader(void);

private slots:
	void	OperandNGStocked(int);
	void	OperandChangedLot(int);
	void	ResizeAction();
    void on_pushButtonSet_clicked();

private:
    Ui::ShowResultMultiDeliveryForm *ui;
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

class	CmdReqLotSubNumber : public GUIDirectMessage
{
public:
	IntList		LotSubNumbers;
	CmdReqLotSubNumber(LayersBase *base):GUIDirectMessage(base){}
};


#endif // SHOWRESULTMULTIDELIVERYFORM_H
