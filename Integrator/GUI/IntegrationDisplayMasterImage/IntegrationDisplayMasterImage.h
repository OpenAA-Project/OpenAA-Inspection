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

#ifndef INTEGRATIONDISPLAYMASTERIMAGE_H
#define INTEGRATIONDISPLAYMASTERIMAGE_H

#include "integrationdisplaymasterimage_global.h"
#include <QToolButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XParamIntegrationMaster.h"
#include "IntegrationLib.h"

class	InspectionList;
class	EachMaster;
class	IntegNGImage;
class	NGPoint;

class	IntegrationDisplayMasterImage: public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	QImage	**Image;
	int		PhaseNumb;
	InspectionList	*CurrentInspection;
	double	ZoomRate;
	NGPoint			*CurrentNGPoint;
	IntegNGImage	*CurrentImagePoint;
public:
	int	MachineCode;
	int	CurrentPhase;
	bool	ShowNGPoint;

	IntegrationDisplayMasterImage(LayersBase *Base ,QWidget *parent);
	~IntegrationDisplayMasterImage();

private:
	virtual void paintEvent ( QPaintEvent * ) override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	void	MakeImage(EachMaster *f);
	virtual void	StartLot	(void) override;
private slots:
	void	ResizeAction();
};

#endif // INTEGRATIONDISPLAYMASTERIMAGE_H