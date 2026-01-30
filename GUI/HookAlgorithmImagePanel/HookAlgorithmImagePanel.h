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

#ifndef HOOKALGORITHMIMAGEPANEL_H
#define HOOKALGORITHMIMAGEPANEL_H

#include "hookalgorithmimagepanel_global.h"
#include "XServiceForLayers.h"
#include <QTcpSocket>
#include <QThread>
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "XDisplayImageHook.h"
#include "XDisplayImage.h"

class	HookAlgorithmImagePanel : public GUIFormBase,public FunctionServerClass
{
	Q_OBJECT
	
	DisplayImage	*SrcImg;
	DisplayImage	*TargetImg;
	QImage			*IData;
	double			LastZoomRate;
	int				LastMovX;
	int				LastMovY;
	int				LastWidth;
	int				LastHeight;
public:
	QString		SrcAlgoImagePanelRoot;
	QString		SrcAlgoImagePanelName;
	QString		SrcAlgoImagePanelInst;

	QString		TargetImagePanelRoot;
	QString		TargetImagePanelName;
	QString		TargetImagePanelInst;


	HookAlgorithmImagePanel(LayersBase *Base ,QWidget *parent);
	~HookAlgorithmImagePanel(void);

	virtual	void	ReadyParam(void)	override;
	void	Draw(QPainter &pnt ,double ZoomRate ,int movx ,int movy);

signals:
	void	SignalOnPaint(QPainter &);
private slots:

};


#endif // HOOKALGORITHMIMAGEPANEL_H