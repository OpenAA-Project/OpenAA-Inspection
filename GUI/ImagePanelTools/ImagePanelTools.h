/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ImagePanelTools\ImagePanelTools.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef IMAGEPANELTOOLS_H
#define IMAGEPANELTOOLS_H

#include "imagepaneltools_global.h"

#include <QToolButton>
#include <QToolBar>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtImageToolButtonWithBalloon.h"
#include "mtFrameDraw.h"

class	ImagePanelTools : public GUIFormBase
{
	Q_OBJECT

	mtImageToolButtonWithBalloon	*NoneButton;
	mtImageToolButtonWithBalloon	*RectangleButton;
	mtImageToolButtonWithBalloon	*EndlessLineButton;
	mtImageToolButtonWithBalloon	*LineButton;
	mtImageToolButtonWithBalloon	*HLineButton;
	mtImageToolButtonWithBalloon	*VLineButton;
	mtImageToolButtonWithBalloon	*HalfLineButton;
	mtImageToolButtonWithBalloon	*EllipseButton;
	mtImageToolButtonWithBalloon	*Ellipse4Button;
	mtImageToolButtonWithBalloon	*RotRectangleButton;
	mtImageToolButtonWithBalloon	*RotEllipseButton;
	mtImageToolButtonWithBalloon	*ArcButton;
	mtImageToolButtonWithBalloon	*Arc3Button;
	mtImageToolButtonWithBalloon	*CircleButton;
	mtImageToolButtonWithBalloon	*Circle3Button;
	mtImageToolButtonWithBalloon	*LongCircleButton;
	mtImageToolButtonWithBalloon	*RingButton;
	mtImageToolButtonWithBalloon	*DotButton;
	mtImageToolButtonWithBalloon	*PolylineButton;
	mtImageToolButtonWithBalloon	*FreelineButton;
	mtImageToolButtonWithBalloon	*RingArc1Button;
	mtImageToolButtonWithBalloon	*RingArc4Button;
	QToolBar	IBar;

public:
	bool	ShowRectangle;
	bool	ShowEndlessLine;
	bool	ShowLine;
	bool	ShowHLine;
	bool	ShowVLine;
	bool	ShowHalfLine;
	bool	ShowEllipse;
	bool	ShowEllipse4;
	bool	ShowRotRectangle;
	bool	ShowRotEllipse;
	bool	ShowArc;
	bool	ShowArc3;
	bool	ShowCircle;
	bool	ShowCircle3;
	bool	ShowLongCircle;
	bool	ShowRing;
	bool	ShowDot;
	bool	ShowPolyline;
	bool	ShowFreeline;
	bool	ShowRingArc1;
	bool	ShowRingArc4;
	QColor	LineColor;
	QStringList	RelatedPanels;
	int32	IconSize;

	ImagePanelTools(LayersBase *Base ,QWidget *parent);
	~ImagePanelTools(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	CreatedInEditMode(GUIFormBase *PutTop)	override;

	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	QStringList	GetRelatedForm(void)				override	{	return RelatedPanels;	}
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)						override;

private slots:
	void NoneButtonDown (bool checked);
	void RectangleButtonDown (bool checked);
	void EndlessLineButtonDown (bool checked);
	void LineButtonDown (bool checked);
	void HLineButtonDown (bool checked);
	void VLineButtonDown (bool checked);
	void HalfLineButtonDown (bool checked);
	void EllipseButtonDown (bool checked);
	void Ellipse4ButtonDown (bool checked);
	void RotRectangleButtonDown (bool checked);
	void RotEllipseButtonDown (bool checked);
	void ArcButtonDown (bool checked);
	void Arc3ButtonDown (bool checked);
	void CircleButtonDown (bool checked);
	void Circle3ButtonDown (bool checked);
	void LongCircleButtonDown (bool checked);
	void RingButtonDown (bool checked);
	void DotButtonDown (bool checked);
	void PolylineButtonDown (bool checked);
	void FreelineButtonDown (bool checked);
	void RingArc1ButtonDown (bool checked);
	void RingArc4ButtonDown (bool checked);
	void	ResizeAction();

	void RectangleButtonRDown (QMouseEvent * event);
	void EndlessLineButtonRDown (QMouseEvent * event);
	void LineButtonRDown (QMouseEvent * event);
	void HLineButtonRDown (QMouseEvent * event);
	void VLineButtonRDown (QMouseEvent * event);
	void HalfLineButtonRDown (QMouseEvent * event);
	void EllipseButtonRDown (QMouseEvent * event);
	void Ellipse4ButtonRDown (QMouseEvent * event);
	void RotRectangleButtonRDown (QMouseEvent * event);
	void RotEllipseButtonRDown (QMouseEvent * event);
	void ArcButtonRDown (QMouseEvent * event);
	void Arc3ButtonRDown (QMouseEvent * event);
	void CircleButtonRDown (QMouseEvent * event);
	void Circle3ButtonRDown (QMouseEvent * event);
	void LongCircleButtonRDown (QMouseEvent * event);
	void RingButtonRDown (QMouseEvent * event);
	void RingArc1ButtonRDown (QMouseEvent * event);
	void RingArc4ButtonRDown (QMouseEvent * event);

	void	SlotDoubleClicked	(QMouseEvent * event);
};


#endif // IMAGEPANELTOOLS_H
