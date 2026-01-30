/*
 * Copyright (C) 2022
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

#ifndef SHOWMULTIIMAGE_H
#define SHOWMULTIIMAGE_H

#include "showmultiimage_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDataInLayer.h"
#include "mtGraphicUnit.h"
#include "XServiceForLayers.h"
#include "XMainSchemeMemory.h"
#include<QImage>
#include<QPushButton>

class	ShowMultiImage;

class	ChildImagePanel : public mtGraphicUnit,public ServiceForLayers
{
	Q_OBJECT

	ShowMultiImage	*Parent;
public:
	class	ImageBufferPhase : public NPList<ImageBufferPhase>
	{
		ChildImagePanel	*ParentImage;
	public:
		class	ImageBufferPage : public NPList<ImageBufferPage>
		{
			ImageBufferPhase	*Parent;
			ChildImagePanel		*ParentImage;
		public:
			class	ImageBufferLayer : public NPList<ImageBufferLayer>
			{
				ImageBufferPage	*Parent;
				ChildImagePanel	*ParentImage;
				ImageBuffer	Image;
				int		Layer;

			public:
				ImageBufferLayer(int layer ,ImageBufferPage *parent,ChildImagePanel *p)
					:Parent(parent),ParentImage(p),Layer(layer){}

				void	Allocate(int DotPerLine ,int MaxLines);
				ImageBuffer	*GetImage(void)	{	return &Image;	}
				LayersBase	*GetLayersBase(void)	{	return ParentImage->GetLayersBase();	}
			};
		protected:
			NPListPack<ImageBufferLayer>	BufferLayer;
			int			Page;
			XYData              OutlineOffset;
		public:
			ImageBufferPage(int page ,ImageBufferPhase *parent,ChildImagePanel *p)
				:Parent(parent),ParentImage(p),Page(page){}

			int		GetPage(void)	{	return Page;	}
			void	Allocate(int LayerNumb ,int DotPerLine ,int MaxLines);
			ImageBuffer	*GetImage(int Layer);
			XYData              &GetOutlineOffset(void)	{	return OutlineOffset;	}
			LayersBase	*GetLayersBase(void)	{	return ParentImage->GetLayersBase();	}
		};
	protected:
		NPListPack<ImageBufferPage>	BufferPage;
		int			Phase;
	public:
		ImageBufferPhase(int phase ,ChildImagePanel *p):ParentImage(p),Phase(phase){}

		void	Allocate(int PageNumb ,int LayerNumb ,int DotPerLine ,int MaxLines);
		ImageBuffer	*GetImage(int Page ,int Layer);
		ImageBufferPage	*GetPageData(int Page)	{	return BufferPage[Page];	}
		LayersBase	*GetLayersBase(void)	{	return ParentImage->GetLayersBase();	}
		void	GetXY(int &x1,int &y1,int &x2,int &y2);
	};
protected:
	NPListPack<ImageBufferPhase>	BufferPhase;
	QImage	*Img;
	int		CurrentPhase;

public:
	QString	FileName;

	ChildImagePanel(LayersBase *Base,ShowMultiImage *parent);
	virtual	~ChildImagePanel(void);
	void	SetCurrentPhase(int phase);

	void	Allocate(int PhaseNumb ,int PageNumb ,int LayerNumb ,int DotPerLine ,int MaxLines);
	ImageBuffer	*GetImage(int Phase ,int Page ,int Layer);

private slots:
	void	SlotOnPaint(QPainter &pnt);
	void	SlotMouseMove(int ,int);
	void	SlotMouseLDown(int ,int);
	void	SlotMouseRDown(int ,int);
	void	SlotMouseWheel(int delta ,int globalX,int globalY);
	void	SlotShiftAll(void);
};

class	ImageButton : public QPushButton
{
	Q_OBJECT

	int	ID;
public:
	ImageButton(void);

	void	SetID(int id)	{	ID=id;	}

signals:
	void	SignalClicked(int id);
	
private slots:
	void	SlotClicked();
};


class ShowMultiImage:public GUIFormBase
{
	Q_OBJECT

public:
	ImageButton		*ButtonFileName;
	ChildImagePanel	**ChildPanel;
	int				AllocatedChildPanelCount;
public:
	int32	ImageCountX;
	int32	ImageCountY;
	double	MaxZoomValue;
	double	MinZoomValue;
	QFont	FontFileName;

	ShowMultiImage(LayersBase *Base ,QWidget *parent = 0);
	~ShowMultiImage(void);

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	DrawAll(ChildImagePanel *src,double ZoomRate ,int movx ,int movy);
private:
	bool	LoadImage(const QString &PixFileName,ChildImagePanel *CPanel);
	void	SendImageToTarget(int phase,int page,int layer ,ImageBuffer *Buff);
private slots:
	void	ResizeAction();
	void	SlotClicked(int id);
};


class	GUICmdSendImagePartial : public GUICmdPacketBase
{
public:
	int		Y;
	int		YLen;
	int		Phase,Layer;
	QByteArray	Data;

	GUICmdSendImagePartial(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	CmdLoadImages : public GUIDirectMessage
{
public:
	QStringList FileNames;
	CmdLoadImages(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdReqPanelCount : public GUIDirectMessage
{
public:
	int		PanelCount;
	;
	CmdReqPanelCount(LayersBase *base):GUIDirectMessage(base){}
};

#endif // SHOWMULTIIMAGE_H