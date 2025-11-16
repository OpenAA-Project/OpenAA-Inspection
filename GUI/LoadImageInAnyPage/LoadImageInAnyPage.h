#ifndef LOADIMAGEINANYPAGE_H
#define LOADIMAGEINANYPAGE_H

#include "loadimageinanypage_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>

class	LoadImageInAnyPage : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ToMaster;
	int32	InPage;

	QString LoadedFileName;

	LoadImageInAnyPage(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	bool	LoadFile(QString &FileName,int CPage ,bool iToMaster);

private:
	void	LoadFile(QString &FileName);

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdSendLoadImageInAnyPage : public GUICmdPacketBase
{
public:
	bool	ToMaster;

	int	Phase;
	int	TopY;
	int	YCount;
	int	Layer;
	int	iDotPerLine;
	QByteArray	Data;

	GUICmdSendLoadImageInAnyPage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdLoadImageInAnyPagePacket : public GUIDirectMessage
{
public:
	QString FileName;
	CmdLoadImageInAnyPagePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadImageInAnyPagePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
#endif // LOADIMAGEINANYPAGE_H
