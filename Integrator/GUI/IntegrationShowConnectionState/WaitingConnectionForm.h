/*
 * Copyright (C) 2021
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

#ifndef WAITINGCONNECTIONFORM_H
#define WAITINGCONNECTIONFORM_H

#include <QWidget>
#include <QTimer>
#include <QCheckBox>
#include "XServiceForLayers.h"
#include "XDateTime.h"

namespace Ui {
class WaitingConnectionForm;
}
class	IntegrationShowConnectionState;

class WaitingConnectionForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

	IntegrationShowConnectionState	*Parent;
	QTimer	TM;
	QCheckBox	**CheckBox;
	int			Count;
public:
    explicit WaitingConnectionForm(LayersBase *base ,IntegrationShowConnectionState *p,QWidget *parent = 0);
    ~WaitingConnectionForm();
    
private slots:
	void	SlotTimeOut();
	void	SlotConnectedAll();
    void on_toolButtonStopLoading_clicked();

private:
    Ui::WaitingConnectionForm *ui;
};

#endif // WAITINGCONNECTIONFORM_H