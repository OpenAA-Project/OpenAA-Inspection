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

#ifndef BUTTONSELECTSTACKEDPAGEFORM_H
#define BUTTONSELECTSTACKEDPAGEFORM_H

#include "XGUIFormBase.h"
#include <QToolButton>
#include <QString>
#include <QStringList>
#include <QColor>
#include <QFont>

namespace Ui {
class ButtonSelectStackedPageForm;
}

class ButtonSelectStackedPageForm : public GUIFormBase
{
    Q_OBJECT
    
	QToolButton	**B[10];
public:
	QString		StackFormInst;
	QStringList	Msg;
	QColor		CharColor;
	QFont		CFont;
	int32		FirstPage;

    explicit ButtonSelectStackedPageForm(LayersBase *Base ,QWidget *parent = 0);
    ~ButtonSelectStackedPageForm();
    
	virtual void	Prepare(void)			override;
	void	SelectPage(int page);
private slots:

    void on_toolButton1_clicked();
    void on_toolButton2_clicked();
    void on_toolButton3_clicked();
    void on_toolButton4_clicked();
    void on_toolButton5_clicked();
    void on_toolButton6_clicked();
    void on_toolButton7_clicked();
    void on_toolButton8_clicked();
    void on_toolButton9_clicked();
    void on_toolButton10_clicked();
	void	ResizeAction();
private:
    Ui::ButtonSelectStackedPageForm *ui;
};

#endif // BUTTONSELECTSTACKEDPAGEFORM_H