#pragma once

#include "buttonreplaceimagecontrol_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XYCross.h"
#include <QLineEdit>
#include <QColor>
#include <QPainter>
#include <QFont>
#include "XDisplayImageHook.h"
#include "XDisplayImage.h"

class	ReplaceImageControlForm;
class	DisplayImage;
class	FlexArea;

class	ButtonReplaceImageControl : public GUIFormBase,public FunctionServerClass
{
	Q_OBJECT

	ReplaceImageControlForm	*Form;
	QPushButton	Button;
	DisplayImage	*HookPanel;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int		CurrentPage;
	QString	HookPanelInst;

	ButtonReplaceImageControl(LayersBase *Base ,QWidget *parent);
	~ButtonReplaceImageControl(void);

	virtual	void	Prepare(void)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)override;

	void	DrawPanel(QPainter &pnt,int movx ,int movy,double ZoomRate ,int CanvasWidth ,int CanvasHeight);
	void	PanelDrawEnd(FlexArea &Area);
	bool	IsAvailableShowMask(void);
	bool	IsAvailableDrawAreaForMask(void);
	bool    IsAvailableMouseLDouble(void);
	void    ExeMouseLDown(int X, int Y);
    void    CloseForm(void);

	void	SetHook(void);
	void	DeleteHook(void);

protected:
	virtual	void	closeEvent(QCloseEvent *event)	override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};


class	CmdReplaceImagePopupWindow : public GUIDirectMessage
{
public:
	CmdReplaceImagePopupWindow(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceImagePopupWindow(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};