#ifndef BUTTONSELECTMULTIDELIVERY_H
#define BUTTONSELECTMULTIDELIVERY_H

#include "buttonselectmultidelivery_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


class	ButtonSelectMultiDelivery : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	bool	LoadLastID;

	QString		iLotID;
	QString		iLotName;
	QString		iRemark;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	MaxLines;

	ButtonSelectMultiDelivery(LayersBase *Base ,QWidget *parent);
	~ButtonSelectMultiDelivery(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)		override;

	virtual	void	RxSync(QByteArray &f)	override;
private:
	bool SetLotToSystem(IntList &FirstLotAutoCount
						,QString iLotID
						,QString iLotName);

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	CmdSelectLot : public GUIDirectMessage
{
public:
	CmdSelectLot(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdSelectLot : public GUICmdPacketBase
{
public:
	IntList			LotAutoCount;
	QStringList		LotID;
	QStringList		LotName;
	QString			Remark;
	XDateTime		CurrentInspectTime;
	ExecuteInspectBase::AutoRepeatMode	AMode;

	GUICmdSelectLot(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	CmdReqLotInfo : public GUIDirectMessage
{
public:
	QString	LotID;
	QString	LotName;
	QString	Remark;

	CmdReqLotInfo(LayersBase *base):GUIDirectMessage(base){}
};


#endif // BUTTONSELECTMULTIDELIVERY_H
