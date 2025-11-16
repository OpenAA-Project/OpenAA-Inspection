#ifndef COPYMIRROREDTRANSFER_H
#define COPYMIRROREDTRANSFER_H

#include "copymirroredtransfer_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	CopyMirroredTransfer : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	InitializeAfterEdit;
	bool	MirrorX;
	bool	MirrorY;
	int32	CopySourcePhase;
	int32	CopyDestinationPhase;
	bool	CopyToSync;
	int32	CoppiedOffsetX;
	int32	CoppiedOffsetY;

	CopyMirroredTransfer(LayersBase *Base ,QWidget *parent);
	~CopyMirroredTransfer(void);
	
	virtual void	Prepare(void)			override;

	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)		override;

	virtual	void	RxSync(QByteArray &f)	override;

public slots:
	void SlotClicked (bool checked);

private slots:
	void	ResizeAction();

};

class	GUICmdReqBuild : public GUICmdPacketBase
{
public:
	int		phase	;
	bool	MirrorX	;
	bool	MirrorY	;

	GUICmdReqBuild(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckBuild : public GUICmdPacketBase
{
public:
	QByteArray	Array;

	GUICmdAckBuild(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetBuild : public GUICmdPacketBase
{
public:
	int		phase;
	bool	MirrorX;
	bool	MirrorY;
	int		CenterX,CenterY;
	QByteArray	Array;

	GUICmdSetBuild(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // COPYMIRROREDTRANSFER_H
