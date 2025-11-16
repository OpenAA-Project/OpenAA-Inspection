#ifndef TREEMASTERSHOWRESULTFORM_H
#define TREEMASTERSHOWRESULTFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XTreeMasterPacket.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
    class TreeMasterShowResultForm;
}

class TreeMasterShowResultForm : public GUIFormBase
{
    Q_OBJECT

	TreeMasterResultListForPacketPack	TreeMasterInfo;
public:
    explicit TreeMasterShowResultForm(LayersBase *base,QWidget *parent = 0);
    ~TreeMasterShowResultForm();

	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
private:
    Ui::TreeMasterShowResultForm *ui;
};

class	GUICmdReqTreeMasterResultList : public GUICmdPacketBase
{
public:
	GUICmdReqTreeMasterResultList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendTreeMasterResultList : public GUICmdPacketBase
{
public:
	TreeMasterResultListForPacketPack	TreeMasterInfo;

	GUICmdSendTreeMasterResultList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeTreeMasterResultList(int localPage ,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


#endif // TREEMASTERSHOWRESULTFORM_H
