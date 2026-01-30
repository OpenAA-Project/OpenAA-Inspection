/*
 * Copyright (C) 2023
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


#ifndef STARTCAPTUREBUTTON_H
#define STARTCAPTUREBUTTON_H

#include "startcapturebutton_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

class	StartCaptureButton : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	Button;
	bool	SyncMode;

	int		ClickOn;
	bool	Calculating;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	ImageType;	//"Master" "Target"
	QColor	NormalColor;
	QColor	PushedColor;

	bool	MasterImageMode;

	StartCaptureButton(LayersBase *Base ,QWidget *parent);
	~StartCaptureButton(void);
	
	virtual void	Prepare(void)			override;
	virtual	void keyPressEvent ( QKeyEvent * event )	override;
	virtual	void	RxSync(QByteArray &f)	override;
	void	CommandStart(void);
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
protected:
	virtual	bool OnIdle(void)	override;
public slots:
	//void	SlotClicked (bool checked);
	void	SlotToggled (bool checked);
	void	ResizeAction();
};


#endif // STARTCAPTUREBUTTON_H