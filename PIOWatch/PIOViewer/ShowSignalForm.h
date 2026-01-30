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

#ifndef SHOWSIGNALFORM_H
#define SHOWSIGNALFORM_H

#include <QDialog>
#include <QFrame>
#include <QWidget>
#include <QLabel>
#include "XTypeDef.h"

namespace Ui {
    class ShowSignalForm;
}

class	PIOViewer;
class	ShowOneSignal;
class	SignalData;

class ShowSignalForm : public QDialog
{
    Q_OBJECT

	PIOViewer		*Parent;
	ShowOneSignal	*InSignal;
	ShowOneSignal	*OutSignal;
	ShowOneSignal	**IndexSignal;
	int				AllocInSignal;
	int				AllocOutSignal;
	int				AllocIndex;

public:
    explicit ShowSignalForm(PIOViewer *parent = 0);
    ~ShowSignalForm();

	int		GetStartMilisec(void);
	int		GetZoomRate(void);
	void	ReDrawSignal(void);
	void	ShowCurrentMilisec(void);

	DWORD	CurrentMilisec;

private slots:
        void on_verticalScrollBar_valueChanged(int value);

        void on_horizontalScrollBar_valueChanged(int value);

        void on_comboBox_currentIndexChanged(int index);

private:
    Ui::ShowSignalForm *ui;

	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

//============================================================================

class	ShowSignalPanel : public QWidget
{
public:
	ShowSignalPanel(QWidget *parent);

protected:
	virtual	void 	paintEvent ( QPaintEvent * event )		override;
	virtual	void	mouseMoveEvent ( QMouseEvent * event )	override;
};

class	ShowOneSignal : public QFrame
{
	QLabel			SignalName;
	ShowSignalPanel	SignalPanel;

	PIOViewer		*Parent;
	ShowSignalForm	*Form;
	bool			InData;
	int				BitNumber;
public:
	ShowOneSignal(void);

	void	Set(bool InData, int BitNumber ,PIOViewer *VParent ,ShowSignalForm *form);
	PIOViewer		*GetParent(void)	{	return Parent;	}
	ShowSignalForm	*GetForm(void)		{	return Form;	}
	SignalData		*GetSignal(void);
	void			ReDraw(void);

protected:
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};


#endif // SHOWSIGNALFORM_H