#ifndef SHOWSWITCHPHASERESULTLISTFORM_H
#define SHOWSWITCHPHASERESULTLISTFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ShowSwitchPhaseResultListForm;
}

class ShowSwitchPhaseResultListForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	bool	Horizontal;

    explicit ShowSwitchPhaseResultListForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowSwitchPhaseResultListForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
    virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
private:
    Ui::ShowSwitchPhaseResultListForm *ui;

private slots:
	void	ResizeAction();
    void on_pushButtonClear_clicked();
};

//============================================================================================

class	GUICmdReqSwitchPhaseResult : public GUICmdPacketBase
{
public:
	GUICmdReqSwitchPhaseResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckSwitchPhaseResult : public GUICmdPacketBase
{
public:
	int32	*InspectionCountInPhase;
	int32	InspectionCountInPhaseNumb;

	GUICmdAckSwitchPhaseResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);
	~GUICmdAckSwitchPhaseResult(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	GUICmdClearSwitchPhaseResult : public GUICmdPacketBase
{
public:
	GUICmdClearSwitchPhaseResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // SHOWSWITCHPHASERESULTLISTFORM_H
