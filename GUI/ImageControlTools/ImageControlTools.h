/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ImageControlTools\ImageControlTools.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef IMAGECONTROLTOOLS_H
#define IMAGECONTROLTOOLS_H

#include "imagecontroltools_global.h"
#include <QToolButton>
#include <QToolBar>
#include <QComboBox>
#include <QTranslator>
#include <QMouseEvent>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtImageToolButtonWithBalloon.h"
#include "mtToolButtonColored.h"
#include "XDisplayImage.h"
#include "XIntClass.h"
#include "XBoolList.h"

class SelectLayerDialog;

class	ImageControlTools : public GUIFormBase
{
	Q_OBJECT
	friend	class SelectLayerDialog;

	mtImageToolButtonWithBalloon	*ImageMaster;
	mtImageToolButtonWithBalloon	*ImageMasterN;
	mtImageToolButtonWithBalloon	*ImageBackGround;
	mtImageToolButtonWithBalloon	*ImageTarget;
	mtImageToolButtonWithBalloon	*ImageBitBuff;
	mtImageToolButtonWithBalloon	*ImageTargetTR;
	//mtToolButtonWithBalloon	*ImageGrayLower;
	//mtToolButtonWithBalloon	*ImageGrayUpper;
	QToolBar	IBar;
	QToolBar	LayerBar;
	mtToolButtonColored	**LButtonList;
	int						LNumb;
	int	XPos;
	int	ButtonNumb;
	int	ButtonW;
	int	LayerButtonW;

	QToolButton		*ButtonManyLayers;

	void	ClearLButtonList();
public:
	bool	ShowImageMaster;
	bool	ShowImageMaster2;
	bool	ShowImageTarget;
	bool	ShowImageBackGround;
	bool	ShowImageGrayLower;
	bool	ShowImageGrayUpper;
	bool	ShowImageTargetTR;
	bool	ExclusiveLayer;
	int		ShowLayerAtFirst;
	bool	ShowLayer;
	QStringList	RelatedPanels;
	int32	IconSize;
	QImage	MasterIcon;
	QImage	TargetIcon;
	bool	BitBuffForMasterImage;

	ImageControlTools(LayersBase *Base ,QWidget *parent);
	~ImageControlTools(void);
	virtual void	Prepare(void)		override;
	virtual void	ReadyParam(void)	override;
	virtual	void	CreatedInEditMode(GUIFormBase *PutTop)	override;
	virtual	bool	ReallocateMasterCount(int CountMaster)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	QStringList	GetRelatedForm(void)	override	{	return RelatedPanels;	}
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

signals:
	void	SignalChangeCurrentLayer(int newLayer);
private:
	void	SendShowingMode(void);

private slots:
	void ImageMasterDown (bool checked);
	void ImageMasterNDown(bool checked);
	void ImageBackGroundDown (bool checked);
	void ImageTargetDown (bool checked);
	void ImageTargetTRDown (bool checked);
	void ImageBitBuffDown (bool checked);
	void ImageGrayLowerDown (bool checked);
	void ImageGrayUpperDown (bool checked);
	void	ResizeAction();
	void LayerClicked(bool checked);
	void	SlotButtonManyLayersClicked(bool checked);
	void	PrepareImageButton(void);
	void	SlotSelectMasterClick(QMouseEvent *);
};

class	GUICmdSetImageControlTools : public GUICmdPacketBase
{
public:
	bool		ModeImageMaster;
	bool		ModeImageMasterN;
	bool		ModeImageBackGround;
	bool		ModeImageTarget;
	bool		ModeImageTargetTR;
	BoolList	ShowingLayer;
	QString		InstName;

	GUICmdSetImageControlTools(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	CmdSetImageControlTools : public GUIDirectMessage
{
public:
	bool		ModeImageMaster;
	bool		ModeImageMasterN;
	bool		ModeImageBackGround;
	bool		ModeImageTarget;
	bool		ModeImageTargetTR;
	BoolList	ShowingLayer;

	CmdSetImageControlTools(LayersBase *base):GUIDirectMessage(base){}
	CmdSetImageControlTools(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif // IMAGECONTROLTOOLS_H
