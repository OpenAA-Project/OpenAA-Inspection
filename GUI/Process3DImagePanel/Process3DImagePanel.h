#ifndef PROCESS3DIMAGEPANEL_H
#define PROCESS3DIMAGEPANEL_H

#include "process3dimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XPropertyProcess3DPacket.h"


class	Process3DImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT
	ListPageLayerIDPack	CurrentItem;

public:
	Process3DImagePanel(LayersBase *Base ,QWidget *parent);
	~Process3DImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void				ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;
	virtual	void				SlotMouseLDown(int globalX,int globalY)					override;
	virtual void				StartPage(void)		override;

private slots:
	void	SlotTouchItems(ListPageLayerIDPack *);
};

//=========================================================

class	GUICmdReqProcess3DInfo : public GUICmdPacketBase
{
public:
	int	LocalX,LocalY;

	GUICmdReqProcess3DInfo(LayersBase *Base ,QString &EmitterRoot,QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendProcess3DInfo : public GUICmdPacketBase
{
public:
	IntList		LibIDList;
	int	LocalX,LocalY;

	GUICmdSendProcess3DInfo(LayersBase *Base ,QString &EmitterRoot,QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	MakeData(int localPage, int localX, int localY,LayersBase	&LocalLBase);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // PROCESS3DIMAGEPANEL_H
