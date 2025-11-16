#ifndef SHOWRESULTFRAMEFORM_H
#define SHOWRESULTFRAMEFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XFrameDef.h"

namespace Ui {
class ShowResultFrameForm;
}

class ShowResultFrameForm : public GUIFormBase
{
    Q_OBJECT

	GroupFrameNumberResultContainer	Structure;

public:
    explicit ShowResultFrameForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowResultFrameForm();

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
private slots:
	void	ResizeAction();
private:
    Ui::ShowResultFrameForm *ui;
};

//----------------------------------------------------------------------------------

class	GUICmdReqGroupFrameList : public GUICmdPacketBase
{
public:
	GUICmdReqGroupFrameList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckGroupFrameList : public GUICmdPacketBase
{
public:
	GroupFrameNumberResultContainer	Structure;

	GUICmdAckGroupFrameList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//----------------------------------------------------------------------------------

class	GUICmdReqResultGroupFrameList : public GUICmdPacketBase
{
public:
	GUICmdReqResultGroupFrameList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckResultGroupFrameList : public GUICmdPacketBase
{
public:
	GroupFrameNumberResultContainer	Structure;

	GUICmdAckResultGroupFrameList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif // SHOWRESULTFRAMEFORM_H
