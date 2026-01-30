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

#ifndef BUTTONLIGHTSHORTCUTFORM_H
#define BUTTONLIGHTSHORTCUTFORM_H

#include <QWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtPushButton.h"

namespace Ui {
class ButtonLightShortCutForm;
}

class ButtonLightShortCutForm : public GUIFormBase
{
    Q_OBJECT

	mtPushButton		Button;
	DWORD	LastKeyTime;
public:
	QString	Msg;
	QFont	CFont;
	QColor	ButtonColor;
	int32	IDNumber;
	int32	ShortcutKey;

	
	explicit ButtonLightShortCutForm(LayersBase *base ,QWidget *parent = 0);
    ~ButtonLightShortCutForm();
    
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_pushButton_clicked();
	void	ResizeAction();
	void	SlotRightClick();
private:
    Ui::ButtonLightShortCutForm *ui;

	QString	GetFileName(void);
	virtual	void	keyPressEvent ( QKeyEvent * event )	override;
};

#endif // BUTTONLIGHTSHORTCUTFORM_H