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

#ifndef INTEGRATIONSHOWNGARROW_H
#define INTEGRATIONSHOWNGARROW_H

#include "integrationshowngarrow_global.h"
#include "XGUIFormBase.h"
#include <QLabel>
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"

class IntegrationShowNGArrow : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

	GUIFormBase	*SourceNG;
	GUIFormBase	*Destination;
	EachMaster	*Master;
	NGPoint		*CurrentNG;
	IntegNGImage	*CurrentImagePoint;
public:
	QString		SourceNGGUIInstName;
	QString		DestinationGUIInstName;
	QColor		ArrowColor;
	bool		ExtendSize;

	IntegrationShowNGArrow(LayersBase *Base ,QWidget *parent = 0);
	~IntegrationShowNGArrow();

	virtual void	ReadyParam(void)	override;
private:
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	virtual	void	paintEvent ( QPaintEvent * event )	override;

private slots:
	void	ResizeAction();
};

#endif // INTEGRATIONSHOWNGARROW_H