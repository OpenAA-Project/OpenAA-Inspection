/*
 * Copyright (C) 2020
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

#ifndef BUTTONSHOWSTOCKEDIMAGE_H
#define BUTTONSHOWSTOCKEDIMAGE_H

#include "buttonshowstockedimage_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XMainSchemeMemory.h"

class	ImageBufferWithInfo : public NPList<ImageBufferWithInfo> ,public ImageBuffer
{
public:
	int		Phase;
	int		Page;
	int		Layer;
	bool	Mastered;
	XDateTime	DateTime;
	int		ID;
	DWORD	ComputerMilisec;

	ImageBufferWithInfo(LayersBase *Base);
	ImageBufferWithInfo &operator=(ImageBuffer &src);
};

class	ImageBufferWithInfoPointer : public NPList<ImageBufferWithInfoPointer>
{
public:
	ImageBufferWithInfo	*Point;

	ImageBufferWithInfoPointer(ImageBufferWithInfo *p):Point(p){}

	virtual	int	Compare(ImageBufferWithInfoPointer &src)	override;
};

class	ImageBufferWithInfoPointerContainer : public NPList<ImageBufferWithInfoPointerContainer> ,public NPListPack<ImageBufferWithInfoPointer>
{
public:
	ImageBufferWithInfoPointerContainer(void){}

	virtual	int	Compare(ImageBufferWithInfoPointerContainer &src)	override;
};


class ButtonShowStockedImage: public GUIFormBase
{
	Q_OBJECT
	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	AllocatedCount;

	NPListPack<ImageBufferWithInfo>		StockImages;


	ButtonShowStockedImage(LayersBase *Base ,QWidget *parent);
	~ButtonShowStockedImage();

	virtual void	ReadyParam(void) override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;

	void	PushImageHPL(int phase ,int page ,int layer ,bool Mastered=false);
	void	PushImagePL (int page ,int layer ,bool Mastered=false);
	void	PushImageHP (int phase ,int page ,bool Mastered=false);
	void	PushImageP(int page ,bool Mastered=false);

	ImageBufferWithInfo	*GetOldBuffer(void);
	
	void	MakeList(NPListPack<ImageBufferWithInfoPointerContainer> &List);

public slots:
	void SlotClicked (bool checked);
private slots:
	void	ResizeAction();
private:
	ImageBuffer	*GetImage(int phase ,int page ,int layer ,bool Mastered=false);
	int		GetMaxID(void);
};

//==================================================================================================
class	GUICmdPushImage : public GUICmdPacketBase
{
public:
	int		Phase	;
	int		Page	;
	int		Layer	;
	bool	Mastered;

	GUICmdPushImage(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONSHOWSTOCKEDIMAGE_H