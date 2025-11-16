#ifndef DOTCOLORMATCHINGIMAGEPANEL_H
#define DOTCOLORMATCHINGIMAGEPANEL_H

#include "dotcolormatchingimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include <QMenu>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
//#include "XDotColorMatching.h"

class	DotColorMatchingImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

	ListPageLayerIDPack	CurrentItem;

public:
	DotColorMatchingImagePanel(LayersBase *Base ,QWidget *parent);
	~DotColorMatchingImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void				ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;
	virtual	void				SlotMouseLDown(int globalX,int globalY)					override;
	virtual void	StartPage(void)	override;

	virtual	void	AddMenuSelectMenuBtn(QMenu &menu)	override;
private slots:
	void	SlotTouchItems(ListPageLayerIDPack *);
	void	SlotSelectByLibOutline();
};

//=========================================================

class	GUICmdReqDotColorMatchingInfo : public GUICmdPacketBase
{
public:
	int	LocalX,LocalY;

	GUICmdReqDotColorMatchingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendDotColorMatchingInfo : public GUICmdPacketBase
{
public:
	IntList		LayerList;
	IntList		LibIDList;
	int	LocalX,LocalY;

	GUICmdSendDotColorMatchingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	MakeData(int localPage, int localX, int localY,LayersBase	&LocalLBase);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif // DOTCOLORMATCHINGIMAGEPANEL_H
