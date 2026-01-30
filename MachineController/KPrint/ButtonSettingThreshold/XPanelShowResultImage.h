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

#if	!defined(XPanelShowResultImage_h)
#define	XPanelShowResultImage_h

#include <QWidget>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XParamCustomized.h"
#include "mtGraphicUnit.h"
#include <QTimer>

class ButtonSettingThresholdForm;
class	EachThresholdCommon;

class	PanelShowResultImage : public mtGraphicUnit,public ServiceForLayers
{
    Q_OBJECT
		
	ButtonSettingThresholdForm	*Parent;
	EachThresholdCommon			*ThCommon;
	int GlobalX ,GlobalY;
	QTimer	TM;
public:
	bool	DrawMode;
	int		DrawGx,DrawGy;
	QColor	DrawColor;

	bool	OverlapNG;

	PanelShowResultImage(ButtonSettingThresholdForm *p ,EachThresholdCommon *wnd);

	void	SetGlobalPoint(int GlobalX ,int GlobalY);

	void	SetClickFunc(void);
	void	ReleaseClickFunc(void);
	void	ShowMarkerPosition(void);
protected:
	virtual	bool	event(QEvent *event)	override;
	
private slots:
	void	SlotOnPaint(QPainter &pnt);
	void	SlotMouseLDoubleClick(int ,int);
	void	SlotMouseWheel(int delta ,int globalX,int globalY);
	void	SlotTimeOut();
};

#endif