#ifndef SAVETARGETINNG_H
#define SAVETARGETINNG_H

#include "savetargetinng_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"
#include "XResult.h"

class	SaveTargetInNG : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	Button;
	int64		LastInspectionID;
	GUIFormBase	*SaveForm;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	SavedFolder;
	bool	OnlyNG;
	bool	BootupON;
	bool	UseCamImage;
	bool	CheckDisk;
	bool	UseGeneralStockerToGetPath;
	QStringList		SaveFolderList;
	int32			DiskSpaceToCheck;
	int32	UseLayer;	//-1::Save all layers


	SaveTargetInNG(LayersBase *Base ,QWidget *parent);
	~SaveTargetInNG(void);
	
	virtual void	Prepare(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;

private slots:

	void	ResizeAction();
};

//-----------------------------------------------------------------------

class	GUICmdReqOkNG : public GUICmdPacketBase
{
public:
	int	ShownInspectionID;

	GUICmdReqOkNG(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendOkNG : public GUICmdPacketBase
{
public:
	ResultInspection::CriticalErrorMode	CriticalError;
	bool3	ResultOk;
	bool	ResultTimeOut ;
	bool	ResultMaxError;

	GUICmdSendOkNG(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // SAVETARGETINNG_H
