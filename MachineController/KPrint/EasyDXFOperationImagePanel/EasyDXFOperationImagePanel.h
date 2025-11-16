#ifndef EASYDXFOPERATIONIMAGEPANEL_H
#define EASYDXFOPERATIONIMAGEPANEL_H

#include "easydxfoperationimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
//#include "mtToolButtonWithBalloon.h"
#include "XIntegrationSimpleImagePanel.h"
#include "XIntegrationPacketComm.h"

class	EasyPropertyDXFOperationForm;

class	EasyDXFOperationImagePanel : public IntegrationAlgoSimpleImagePanel
{
	Q_OBJECT

public:
	bool	OnMoving;
	int	LastPosX,LastPosY;
	int	MoveStartPosX,MoveStartPosY;

	EasyDXFOperationImagePanel(LayersBase *Base ,QWidget *parent);
	~EasyDXFOperationImagePanel(void){}

	virtual void	Prepare(void)	override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

	bool	IsMoveMode(void);
protected slots:
	virtual	void	SlotCanvasMouseMove (int globalX ,int globalY) override;
	//virtual	void	SlotCanvasMouseLDown(int globalX ,int globalY) override;
	//virtual	void	SlotCanvasMouseRDown(int globalX ,int globalY) override;

	virtual	void	SlotJustMouseLPress  (int UniversalDx,int UniversalDy) override;
	virtual	void	SlotJustMouseLRelease(int UniversalDx,int UniversalDy) override;
	
	virtual	void	SlotModeChanged  ();

private:

	EasyPropertyDXFOperationForm	*GetPropertyForm(void);
};


class	IntegrationCmdMove: public IntegrationCmdPacketBase
{
public:
	int	GlobalDx,GlobalDy;

	IntegrationCmdMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdSelect: public IntegrationCmdPacketBase
{
public:
	bool	SelectMode;
	int		ActivePage;

	IntegrationCmdSelect(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};


#endif // EASYDXFOPERATIONIMAGEPANEL_H
