/*
 * Copyright (C) 2021
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

#ifndef DISPLAYREALTIMEGRAPH_H
#define DISPLAYREALTIMEGRAPH_H

#include "displayrealtimegraph_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"

class DisplayRealtimeGraphBrightness;
class DisplayRealtimeGraphFocus;
class DisplayImage;

class	DisplayRealtimeGraph :public GUIFormBase
{
    Q_OBJECT

public:
	DisplayRealtimeGraphBrightness	*PanelBrightness;
	DisplayRealtimeGraphFocus		*PanelFocus;

	GUIFormBase		*PropertyRealtimeGraphPointer;
	DisplayImage	*RealtimeImagePanelPointer	;

	DisplayRealtimeGraph(LayersBase *Base ,QWidget *parent);
	~DisplayRealtimeGraph();

	virtual void	AfterStartSequence(void)	override;

	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	virtual void	ShowInScanning(int64 shownInspectionID=-1)	override;
	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:

private slots:
	void	ResizeAction();
};

#endif // DISPLAYREALTIMEGRAPH_H