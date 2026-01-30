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

#ifndef INDICATORWINDOW_H
#define INDICATORWINDOW_H

#include <QDialog>
#include <QTimer>

namespace Ui {
    class IndicatorWindow;
}

class CopyMultiple;

class IndicatorWindow : public QWidget
{
    Q_OBJECT

	QTimer	TM;
	CopyMultiple	*Parent;
	int		DestCount;
public:
    explicit IndicatorWindow(QWidget *parent = 0);
    ~IndicatorWindow();

	virtual	void closeEvent ( QCloseEvent * event )	override;

private:
    Ui::IndicatorWindow *ui;

private slots:
	void	SlotTimeout ();

};

#endif // INDICATORWINDOW_H