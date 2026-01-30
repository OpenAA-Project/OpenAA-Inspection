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

#ifndef BUTTONAUTOGENERATEMEASURELINEMOVE_H
#define BUTTONAUTOGENERATEMEASURELINEMOVE_H

#include "buttonautogeneratemeasurelinemove_global.h"
#include <QPushButton>
#include <QBuffer>
//#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XMeasureLineMove.h"

class	ButtonAutoGenerateMeasureLineMove : public GUIFormBase
{
	Q_OBJECT
	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	GUIInst;

	QByteArray		AutoGenInfo;

	int	BladePickupRL;
	int	BladePickupRH;
	int	BladePickupGL;
	int	BladePickupGH;
	int	BladePickupBL;
	int	BladePickupBH;
	int	LineLib;
	int	DistanceLib;
	BladeMeasure	BladeMeasureData;



	ButtonAutoGenerateMeasureLineMove(LayersBase *Base ,QWidget *parent);
	~ButtonAutoGenerateMeasureLineMove();
	virtual void	Prepare(void)	override;
private:

public slots:
	void	SlotClicked (bool checked);
	void	SlotExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data);
private slots:
	void	ResizeAction();
};

#endif // BUTTONAUTOGENERATEMEASURELINEMOVE_H