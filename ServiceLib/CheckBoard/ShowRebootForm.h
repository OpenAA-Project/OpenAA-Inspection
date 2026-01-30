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

#ifndef SHOWREBOOTFORM_H
#define SHOWREBOOTFORM_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class ShowRebootForm;
}

class ShowRebootForm : public QWidget
{
    Q_OBJECT

    QTimer  TM;
public:
    explicit ShowRebootForm(int ReasonIndex ,QWidget *parent = nullptr);
    ~ShowRebootForm();

private slots:
    void OnTimerTicked();

signals:
	void    SignalTimeUp();
private:
    Ui::ShowRebootForm *ui;
};

#endif // SHOWREBOOTFORM_H