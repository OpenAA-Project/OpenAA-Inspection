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

#ifndef SHOWPARTIALIMAGINGPANEL_H
#define SHOWPARTIALIMAGINGPANEL_H

#include "showpartialimagingpanel_global.h"
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "XPartialImaging.h"

class ShowPartialImagingPanel : public GUIFormBase
{
	Q_OBJECT

	WriteBufferInItem	*PointData;

public:
	ShowPartialImagingPanel(LayersBase *Base ,QWidget *parent);
	~ShowPartialImagingPanel(void);

	virtual void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
	virtual	void paintEvent ( QPaintEvent * event )	override;
	
	PartialImagingBase	*GetPartialImagingBase(void);
	void	MakeImage(QImage &Img,WriteBufferInItem *Pointer);

private slots:
	void	ResizeAction();
};
#endif // SHOWPARTIALIMAGINGPANEL_H