/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AutoSaveImageViewPanel\AutoSaveImageViewPanel.h
** Author : YYYYYYYYYY
*******************************************************************************/

#ifndef AUTOSAVEIMAGEVIEWPANEL_H
#define AUTOSAVEIMAGEVIEWPANEL_H

//#include "AutoSaveImageViewPanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	AutoSaveImageViewPanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	AutoSaveImageViewPanel(LayersBase *Base ,QWidget *parent);
	~AutoSaveImageViewPanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void ExecutePasteShape(const QString &OriginRoot ,const QString &OriginName)	override;
	virtual void	StartPage	(void)	override;

	virtual	void	ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;

	int nStartX;
	int nStartY;
	int nWidth;
	int nHeight;

protected :
	virtual	void	DrawAfterImage(QPainter &pnt ,QImage &PntImage)	override;

private slots:
};

//=========================================================
class	GUICmdReqNamingBmp : public GUICmdPacketBase
{
public:
	struct	GUIReqBmpStruct
	{
		DisplayImage::DisplayType	DType;
		int32	Gx1;
		int32	Gy1;
		int32	Gx2;
		int32	Gy2;
		int32	Dx1;
		int32	Dy1;
		int32	Dx2;
		int32	Dy2;
		double	ZoomRate;
		int32	MovX;
		int32	MovY;
		int32	GlobalPage;
		int32	CurrentGlobalX;
		int32	CurrentGlobalY;
	}Data;
	IntList	LayerList;

	GUICmdReqNamingBmp(QString &EmitterRoot,QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendNamingBmp : public GUICmdPacketBase
{
public:
	QImage		*IData;

	GUICmdSendNamingBmp(QString &EmitterRoot,QString &EmitterName ,int globalPage=-1);
	~GUICmdSendNamingBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

	void	MakeImage(DisplayImage::DisplayType dtype
					 ,IntList &LayerList
					 ,int Gx1,int Gy1 ,int Gx2,int Gy2
					 ,int Dx1,int Dy1 ,int Dx2,int Dy2
					 ,int MovX,int MovY, double ZoomRate
					 ,int localPage
					 ,LayersBase &LocalLBase);
};

#endif // AUTOSAVEIMAGEVIEWPANEL_H
