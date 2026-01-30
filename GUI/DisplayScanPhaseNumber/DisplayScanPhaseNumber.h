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

#ifndef DISPLAYSCANPHASENUMBER_H
#define DISPLAYSCANPHASENUMBER_H

#include "displayscanphasenumber_global.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

class	DisplayScanPhaseNumber : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	**Buttons;
	int					AllocatedCount;

public:
	QStringList		ScanPhaseNames;
	QFont			CFont;
	QColor			CharColor;
	QColor			ActiveColor;
	QColor			NormalColor;
	QString			OrientationStr;		//Horizontal,Vertical

	DisplayScanPhaseNumber(LayersBase *Base ,QWidget *parent);
	~DisplayScanPhaseNumber(void);

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

protected:
	virtual	bool OnIdle(void)	override;

public slots:
	void	SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

#endif // DISPLAYSCANPHASENUMBER_H