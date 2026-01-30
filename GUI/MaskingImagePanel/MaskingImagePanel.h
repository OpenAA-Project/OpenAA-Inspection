/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#ifndef MASKINGIMAGEPANEL_H
#define MASKINGIMAGEPANEL_H

#include "maskingimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	MaskingImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	MaskingImagePanel(LayersBase *Base ,QWidget *parent);
	~MaskingImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void ExecutePasteShape(const QString &OriginRoot ,const QString &OriginName)	override;
	virtual void	StartPage	(void)	override;

	virtual	void	ExecuteMouseLDown(int globalX ,int globalY)	override;
	virtual	void	StartMenu(QToolButton *Btn ,QMenu *menu)	override;

protected:
	virtual	void	ButtonExecuteDeleteSelected(void)	override;
private slots:
	void	SlotSelectByLimited();
};

//=========================================================
class	GUICmdReqMaskingBmp : public GUICmdPacketBase
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

	GUICmdReqMaskingBmp(QString &EmitterRoot,QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendMaskingBmp : public GUICmdPacketBase
{
public:
	QImage		*IData;

	GUICmdSendMaskingBmp(QString &EmitterRoot,QString &EmitterName ,int globalPage=-1);
	~GUICmdSendMaskingBmp(void);

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

class	GUICmdSelectMaskLimited : public GUICmdPacketBase
{
public:
	AlgorithmLibraryListContainer	SelectedList;
	bool							AllMode;
	IntList							Layers;
	bool							IneffectiveMode;
	bool							EffectiveMode;
	bool							IneffectiveLimitedMode;
	bool							EffectiveLimitedMode;

	GUICmdSelectMaskLimited(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//=========================================================

#endif // MASKINGIMAGEPANEL_H