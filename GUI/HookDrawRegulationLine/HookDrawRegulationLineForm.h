#ifndef HOOKDRAWREGULATIONLINEFORM_H
#define HOOKDRAWREGULATIONLINEFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include <QToolButton>
#include "XGUIPacketForDLL.h"
#include "XDisplayImageHook.h"
#include "XDisplayImage.h"
#include "NListComp.h"

namespace Ui {
class HookDrawRegulationLineForm;
}


class	CrossButton : public QToolButton
{
    Q_OBJECT
public:
	CrossButton ( QWidget * parent = 0);

signals:
	void	SignalRightButton();
protected:
	void	mouseReleaseEvent ( QMouseEvent * e );
};

class HookDrawRegulationLineForm : public GUIFormBase,public FunctionServerClass
{
    Q_OBJECT

	DisplayImage		*TargetPanel[10];
	int		LineWidth;
	QColor	Color;
	int		Mode;
	QTimer	TM;
public:
	QStringList			HookTargetInst;

    explicit HookDrawRegulationLineForm(LayersBase *Base ,QWidget *parent = 0);
    ~HookDrawRegulationLineForm();

	virtual void	Prepare(void)		override;
	virtual void	ReadyParam(void)	override;
	void	Draw	(QPainter &pnt	,DataInPage *P 
					,double ZoomRate,int movx ,int movy 
					,int CanvasWidth , int CanvasHeight);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:
    Ui::HookDrawRegulationLineForm *ui;
	void	SetMode(void);
signals:
	void	SignalReDraw();
private slots:
	void	ResizeAction();
    void	SlotClicked();
	void	SlotRClicked();
	void	SlotRedraw();
};


class	CmdHookDrawRegulationLine_GetMode : public GUIDirectMessage
{
public:
	int	Mode;	//-1:Off

	CmdHookDrawRegulationLine_GetMode(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdHookDrawRegulationLine_SetMode : public GUIDirectMessage
{
public:
	int	Mode;

	CmdHookDrawRegulationLine_SetMode(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdReqHookDrawRegulationInfo : public GUIDirectMessage
{
public:
	int		LineWidth;
	QColor	LineColor;

	CmdReqHookDrawRegulationInfo(LayersBase *base):GUIDirectMessage(base){}
	CmdReqHookDrawRegulationInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetHookDrawRegulationInfo : public GUIDirectMessage
{
public:
	int		LineWidth;
	QColor	LineColor;

	CmdSetHookDrawRegulationInfo(LayersBase *base):GUIDirectMessage(base){}
	CmdSetHookDrawRegulationInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif // HOOKDRAWREGULATIONLINEFORM_H
