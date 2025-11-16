#ifndef STARTSCANNINGAGAIN_H
#define STARTSCANNINGAGAIN_H

#include "startscanningagain_global.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	StartScanningAgain : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

	int	RepeatCount_StartByInspection;
	int	RepeatCount_Captured;
	int	RepeatCount_PreAlignent;
	int	RepeatCount_Alignent;
	int	RepeatCount_PreScanning;
	int	RepeatCount_Scanning;
	int	RepeatCount_PostScanning;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ExecInitialAfterEdit;
	int32	MaxInspectMilisec;

	StartScanningAgain(LayersBase *Base ,QWidget *parent);
	~StartScanningAgain(void);
	
	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

public slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};


class	GUICmdPushed : public GUICmdPacketBase
{
public:
	int64	InspectionID;
	bool	IsExecInitialAfterEdit;
	QString	ImageType;	//"Master" "Target"
	int32	MaxInspectMilisec;

	int	RepeatCount_StartByInspection;
	int	RepeatCount_Captured;
	int	RepeatCount_PreAlignent;
	int	RepeatCount_Alignent;
	int	RepeatCount_PreScanning;
	int	RepeatCount_Scanning;
	int	RepeatCount_PostScanning;

	GUICmdPushed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdScanningAgainReplied : public GUICmdPacketBase
{
public:
	int			ExecuterID;

	CmdScanningAgainReplied(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif // STARTSCANNINGAGAIN_H
