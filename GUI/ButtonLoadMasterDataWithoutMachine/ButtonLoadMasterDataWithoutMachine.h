#ifndef BUTTONLOADMASTERDATAWITHOUTMACHINE_H
#define BUTTONLOADMASTERDATAWITHOUTMACHINE_H

#include "buttonloadmasterdatawithoutmachine_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	SignalOperandInt;
class	SignalOperandBit;
class LoadMasterDataWindow;

class	ButtonLoadMasterDataWithoutMachine : public GUIFormBase
{
	Q_OBJECT

	friend class LoadMasterDataWindow;

	QPushButton	Button;
	SignalOperandInt	*iExeLoadMasterData;
	SignalOperandBit	*iOnLoading;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ShowLoadedInfo;
	bool	EnableManyTimes;
	QString	SelectLotSRoot;
	QString	SelectLotSName;
	bool	InitializeAfterEdit;
	bool	ShowSelectToLoadImage;
	QStringList	IncludedMachines;
	bool	ReleaseAutoMode;

	ButtonLoadMasterDataWithoutMachine(LayersBase *Base ,QWidget *parent);
	~ButtonLoadMasterDataWithoutMachine(void);
	
	virtual void	Prepare(void)		override;

	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
	void	CommandLoadMaster(int MasterCode,bool	ModeLoadMasterImage);

public slots:
	void SlotClicked (bool checked);
	void	OperandExeLoadMAsterData();

private slots:
	void	ResizeAction();
	void	SlotShowInfo(void);

signals:
	void	SignalShowInfo(void);

};


class	GUICmdSendInitialXYPixelsData : public GUICmdPacketBase
{
public:
	int		DotPerLine;
	int		MaxLines;

	GUICmdSendInitialXYPixelsData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // BUTTONLOADMASTERDATAWITHOUTMACHINE_H
