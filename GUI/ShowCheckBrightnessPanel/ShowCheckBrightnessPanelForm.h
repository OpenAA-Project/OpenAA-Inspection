#ifndef SHOWCHECKBRIGHTNESSPANELFORM_H
#define SHOWCHECKBRIGHTNESSPANELFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XCheckBrightness.h"

namespace Ui {
class ShowCheckBrightnessPanelForm;
}


class	SignalOperandInt;

class ShowCheckBrightnessPanelForm : public GUIFormBase
{
    Q_OBJECT
    
	CBPanelListContainer	CBContainer;
	SignalOperandInt	*iResultNG;			//0:None	1:OK	2:NG
public:
    explicit ShowCheckBrightnessPanelForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowCheckBrightnessPanelForm();
    
	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
private:
    Ui::ShowCheckBrightnessPanelForm *ui;
};

//----------------------------------------------------------------------------

class	GUICmdReqCBInfo : public GUICmdPacketBase
{
public:
	int		Layer;

	GUICmdReqCBInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendCBInfo : public GUICmdPacketBase
{
public:
	CBPanelListContainer	CBList;

	GUICmdSendCBInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdReqCBResult : public GUICmdPacketBase
{
public:
	int		Layer;
	int		ItemID;

	GUICmdReqCBResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendCBResult : public GUICmdPacketBase
{
public:
	bool	ResultOK;

	GUICmdSendCBResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif // SHOWCHECKBRIGHTNESSPANELFORM_H
