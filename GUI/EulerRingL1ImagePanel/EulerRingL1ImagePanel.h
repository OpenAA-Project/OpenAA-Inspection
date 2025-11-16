#ifndef EulerRingL1L1IMAGEPANEL_H
#define EulerRingL1L1IMAGEPANEL_H

//#include "EulerRingL1imagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XPropertyEulerRingL1Packet.h"

class	EulerRingL1ImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT
	ListPageLayerIDPack	CurrentItem;

public:
	EulerRingL1ImagePanel(LayersBase *Base ,QWidget *parent);
	~EulerRingL1ImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void				ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;
	virtual	void				SlotMouseLDown(int globalX,int globalY)					override;
	virtual void				StartPage(void)	override;

private slots:
	void	SlotTouchItems(ListPageLayerIDPack *);
};

//=========================================================

class	GUICmdReqEulerRingL1Info : public GUICmdPacketBase
{
public:
	int	LocalX,LocalY;

	GUICmdReqEulerRingL1Info(LayersBase *Base ,QString &EmitterRoot,QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendEulerRingL1Info : public GUICmdPacketBase
{
public:
	IntList		LibIDList;
	int	LocalX,LocalY;

	GUICmdSendEulerRingL1Info(LayersBase *Base ,QString &EmitterRoot,QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	MakeData(int localPage, int localX, int localY,LayersBase	&LocalLBase);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // EulerRingL1L1IMAGEPANEL_H
