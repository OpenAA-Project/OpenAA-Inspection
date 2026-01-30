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

#ifndef BUTTONTOSHOWCROSSLINEFORM_H
#define BUTTONTOSHOWCROSSLINEFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QStringList>
#include <QColor>

namespace Ui {
class ButtonToShowCrossLineForm;
}

class	CrossLineButton : public QToolButton
{
    Q_OBJECT
public:
	CrossLineButton ( QWidget * parent = 0);

signals:
	void	SignalRightButton();
protected:
	void	mouseReleaseEvent ( QMouseEvent * e );
};

class ButtonToShowCrossLineForm : public GUIFormBase
{
    Q_OBJECT

	CrossLineButton	Button;
public:
	QStringList		ImagePanelInst;
	QColor			LineColor;
	bool			CrossLine;
	bool			MatrixLine;

    explicit ButtonToShowCrossLineForm(LayersBase *Base ,QWidget *parent = 0);
    ~ButtonToShowCrossLineForm();

	virtual void	AfterPrepare(void)	override;
private slots:
    void on_toolButtonCrossLine_clicked(bool b);
	void	ResizeAction();
    void on_toolButtonCrossLine_pressed();

private:
    Ui::ButtonToShowCrossLineForm *ui;
};

#endif // BUTTONTOSHOWCROSSLINEFORM_H