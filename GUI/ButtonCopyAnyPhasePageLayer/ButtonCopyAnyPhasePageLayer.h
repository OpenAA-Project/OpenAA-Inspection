#ifndef BUTTONCOPYANYPHASEPAGELAYER_H
#define BUTTONCOPYANYPHASEPAGELAYER_H

#include "buttoncopyanyphasepagelayer_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QIODevice>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonCopyAnyPhasePageLayer : public GUIFormBase
{
    Q_OBJECT

	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonCopyAnyPhasePageLayer(LayersBase *Base ,QWidget *parent = 0);
	~ButtonCopyAnyPhasePageLayer();

	virtual void	Prepare(void)	override;
private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdReqAnyData : public GUICmdPacketBase
{
public:
	int		Phase,Layer;
	bool	ReqMasterImage;
	bool	ReqTargetImage;
	bool	ReqAlgorithm;

	GUICmdReqAnyData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAnyData : public GUICmdPacketBase
{
public:
	int		Phase,Layer;
	bool	ReqMasterImage;
	bool	ReqTargetImage;
	bool	ReqAlgorithm;
	QByteArray	Data;
	bool	Success;

	GUICmdAckAnyData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};


class	GUICmdSendAnyData : public GUICmdPacketBase
{
public:
	int		Phase,Layer;
	bool	ReqMasterImage;
	bool	ReqTargetImage;
	bool	ReqAlgorithm;
	QByteArray	Data;

	GUICmdSendAnyData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONCOPYANYPHASEPAGELAYER_H
