#ifndef ADJUSTMOVEALLAFTERLOADMASTER_H
#define ADJUSTMOVEALLAFTERLOADMASTER_H

#include "adjustmoveallafterloadmaster_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XYCross.h"


class	MoveAllInMaster : public XYClassContainer ,public NPList<MoveAllInMaster>
{
public:
	int	MasterCode;

	MoveAllInMaster(void){	MasterCode-1;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	void	SetPageCount(int n);
};

class	MoveAllInfo : public NPListPack<MoveAllInMaster>
{
public:
	MoveAllInfo(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	void	SetPageCount(int n);

	MoveAllInMaster	*FindMasterData(int mastercode);
};

//------------------------------------------------------------------------------------

class	AdjustMoveAllAfterLoadMaster : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	MoveAllInfo		MoveXY;

	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	SavedFileName;

	AdjustMoveAllAfterLoadMaster(LayersBase *Base ,QWidget *parent);
	~AdjustMoveAllAfterLoadMaster(void);
	
	virtual void	Prepare(void)	override;	

	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)						override;

	bool	LoadFile(void);
	bool	SaveFile(void);
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};


class	GUICmdMoveAll: public GUICmdPacketBase
{
public:
	int	MovX;
	int	MovY;
	bool	MoveMasterImage;
	bool	MoveTargetImage;
	bool	ChangeChanged;

	GUICmdMoveAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // ADJUSTMOVEALLAFTERLOADMASTER_H
