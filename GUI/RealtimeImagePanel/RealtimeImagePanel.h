/*
 * Copyright (C) 2025
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

#ifndef REALTIMEIMAGEPANEL_H
#define REALTIMEIMAGEPANEL_H

#include "realtimeimagepanel_global.h"
#include "XDisplayImage.h"
#include <QTimer>


class ImageBufferDimClass
{
public:
	ImageBuffer	*IBuff[3];

	ImageBufferDimClass(void);
	~ImageBufferDimClass(void);

	void	Alloc(int XLen ,int YLen);
};


class	RealtimeImagePanel : public DisplayImage
{
	Q_OBJECT

	ImageBufferDimClass	*IBuff;
	CameraClass			**Cam;
	int					CountCamera;
	QTimer				Timer;
	QImage				Image;
public:
	QString		ImageType;
	int32		IntervalMilisec;

	RealtimeImagePanel(LayersBase *Base ,QWidget *parent);
	~RealtimeImagePanel(void);

	virtual	void	Prepare(void) override;
	virtual void	ReadyParam(void)							override;
	virtual	void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	virtual void	ShowInScanning(int64 shownInspectionID=-1)	override;

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);

private slots:
	void	ResizeAction();
	void	SlotTimeout();
	virtual	void	CanvasSlotOnPaint(QPainter &pnt);
};
#endif // REALTIMEIMAGEPANEL_H