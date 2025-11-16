#ifndef BUTTONSELECTCOUNTEDLOT_H
#define BUTTONSELECTCOUNTEDLOT_H

#include "buttonselectcountedlot_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDateTime.h"

class	ButtonSelectCountedLot : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	bool	LoadLastID;
	int		StartCount;
	int		NGCount;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	SelectedLotID;
	int		LotCountNumber;

	ButtonSelectCountedLot(LayersBase *Base ,QWidget *parent);
	~ButtonSelectCountedLot(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)		override;

	virtual	void	RxSync(QByteArray &f)	override;
private:
	QString	CalcLotID(const QString &iLotID,int iStartCount);
	void SetLotToSystem(int iLotAutoCount
						,const QString &iLotID
						,const QString &iLotName
						,int LotCountNumber);
	int		GetMaxLotID(const QString &iLotID);

private slots:
	void	SlotWroteCommon(XDateTime tm);
	void	SlotClicked (bool checked);
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
	int		LotAutoCount;
	QString	LotID;
	QString	LotName;
	int		LotCountNumber;

	GUICmdSelectLot(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif // BUTTONSELECTCOUNTEDLOT_H
