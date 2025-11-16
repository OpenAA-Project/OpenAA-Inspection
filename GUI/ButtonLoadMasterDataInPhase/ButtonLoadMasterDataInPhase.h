#ifndef BUTTONLOADMASTERDATAINPHASE_H
#define BUTTONLOADMASTERDATAINPHASE_H

#include "buttonloadmasterdatainphase_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


class	SignalOperandInt;
class	SignalOperandBit;
class LoadMasterDataWindow;

class	ButtonLoadMasterDataInPhase : public GUIFormBase
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
	QString	SelectMachineSRoot;
	QString	SelectMachineSName;
	bool	InitializeAfterEdit;
	bool	ShowSelectToLoadImage;
	bool	ReleaseAutoMode;
	int32	DestinationPhase;

	ButtonLoadMasterDataInPhase(LayersBase *Base ,QWidget *parent);
	~ButtonLoadMasterDataInPhase(void);
	
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

#endif // BUTTONLOADMASTERDATAINPHASE_H
