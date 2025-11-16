#ifndef SHOWBINDNGNAMINGLISTFORM_H
#define SHOWBINDNGNAMINGLISTFORM_H

#include "XGUIFormBase.h"
#include <QWidget>
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"

namespace Ui {
class ShowBindNGNamingListForm;
}

class NGListInAreaName : public NPList<NGListInAreaName>
{
public:
	NGAreaList	*AreaPoint;
	IntList		PhaseList;

	NGListInAreaName(){}
	~NGListInAreaName(){}

private:

};
class ShowBindNGNamingListForm : public GUIFormBase
{
    Q_OBJECT
    
	NGAreaListContainer	*NGData;
public:
	NPListPack<NGListInAreaName>	NGNameContainer;
public:
    explicit ShowBindNGNamingListForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowBindNGNamingListForm();
    
	virtual void	Prepare(void)	override;
	virtual void	ShowInPlayer	(int64 shownInspectionID)	override;
	virtual void	OnTheWayInPlayer(int64 shownInspectionID=-1)override;
private:
    Ui::ShowBindNGNamingListForm *ui;

private slots:
	void	ResizeAction();
};

//==========================================================

class	GUICmdReqNGNamingPhaseList : public GUICmdPacketBase
{
public:
	int32		ShownInspectionID;
	int32		Phase;

	GUICmdReqNGNamingPhaseList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendNGNamingPhaseList : public GUICmdPacketBase
{
public:
	NGAreaListContainer	NGData;

	GUICmdSendNGNamingPhaseList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

#endif // SHOWBINDNGNAMINGLISTFORM_H
