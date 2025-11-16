#ifndef BUTTONSAVEBMPJPG_H
#define BUTTONSAVEBMPJPG_H

#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include <QStringList>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonSaveBmpJpg : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ToMaster;
	QStringList	RelatedItems;
	int32	SavedPage;

	QString SavedFileName;

	ButtonSaveBmpJpg(LayersBase *Base ,QWidget *parent);
	virtual void	Prepare(void)								override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

	QString	SaveFileWithDialog(void);
	bool	SaveFile(QString &FileName,bool iToMaster);
	bool	SaveFile(QString &FileName,int ImageXLen ,int ImageYLen ,bool iToMaster);
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)						override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdReqSaveBmpJpg : public GUICmdPacketBase
{
public:
	QImage	Img;
	bool	ToMaster;

	GUICmdReqSaveBmpJpg(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdSaveBmpJpgPacket : public GUIDirectMessage
{
public:
	QString FileName;
	bool	Success;
	CmdSaveBmpJpgPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSaveBmpJpgImagePacket : public GUIDirectMessage
{
public:
	int		ImageXLen;
	int		ImageYLen;
	bool	MasterImage;
	QString FileName;
	bool	Success;
	CmdSaveBmpJpgImagePacket(LayersBase *base):GUIDirectMessage(base){	MasterImage=true;	ImageXLen=-1;	ImageYLen=-1;	}
};

class	CmdSaveBmpJpgDirectPacket : public GUIDirectMessage
{
public:
	int		ImageXLen;
	int		ImageYLen;
	QImage	SourceImage;
	QString FileName;
	bool	Success;
	CmdSaveBmpJpgDirectPacket(LayersBase *base):GUIDirectMessage(base){	ImageXLen=-1;	ImageYLen=-1;	}
};

class	CmdSaveBmpJpgWithDialogPacket : public GUIDirectMessage
{
public:
	QString FileName;
	bool	Success;
	CmdSaveBmpJpgWithDialogPacket(LayersBase *base):GUIDirectMessage(base){}
};

#endif // BUTTONSAVEBMPJPG_H
