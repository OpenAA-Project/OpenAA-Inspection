#ifndef HOLEWALLINSPECTION_H
#define HOLEWALLINSPECTION_H

#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XPropertyHoleWallPacket.h"

class	HoleWallImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT
	ListPageLayerIDPack	CurrentItem;

public:
	HoleWallImagePanel(LayersBase *Base ,QWidget *parent);
	~HoleWallImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void				ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;
	virtual	void				SlotMouseLDown(int globalX,int globalY)					override;
	virtual void				StartPage(void)	override;

private slots:
	void	SlotTouchItems(ListPageLayerIDPack *);
};

//=========================================================

class	GUICmdReqHoleWallInfo : public GUICmdPacketBase
{
public:
	int	LocalX,LocalY;

	GUICmdReqHoleWallInfo(LayersBase *Base ,QString &EmitterRoot,QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendHoleWallInfo : public GUICmdPacketBase
{
public:
	IntList		LibIDList;
	int	LocalX,LocalY;

	GUICmdSendHoleWallInfo(LayersBase *Base ,QString &EmitterRoot,QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	MakeData(int localPage, int localX, int localY,LayersBase	&LocalLBase);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // HOLEWALLINSPECTION_H
