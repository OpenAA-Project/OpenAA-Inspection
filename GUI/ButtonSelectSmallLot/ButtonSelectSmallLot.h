#ifndef BUTTONSELECTSMALLLOT_H
#define BUTTONSELECTSMALLLOT_H

#include "buttonselectsmalllot_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


class	ButtonSelectSmallLot : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	bool	LoadLastID;

	QString		iLotID;
	QString		iLotName;
	QString		iRemark;
	int			iIDNumber;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	MaxLines;

	ButtonSelectSmallLot(LayersBase *Base ,QWidget *parent);
	~ButtonSelectSmallLot(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
private:
	void SetLotToSystem(int iLotAutoCount
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
	int			LotAutoCount;
	QString		LotID;
	QString		LotName;
	QString		Remark;
	XDateTime	CurrentInspectTime;
	ExecuteInspectBase::AutoRepeatMode	AMode;
	int			CPoints[3];

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
	int		IDNumber;

	CmdReqLotInfo(LayersBase *base):GUIDirectMessage(base){}
};

#endif // BUTTONSELECTSMALLLOT_H
