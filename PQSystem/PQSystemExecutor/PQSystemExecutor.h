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

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PQSystemExecutor.h"
#include "XPQRunnerController.h"
#include "XServiceForLayers.h"
#include <QToolButton>

class PQSystemExecutor;

class MenuButton : public QToolButton ,public NPList<MenuButton>
{
	Q_OBJECT
	PQSystemExecutor	*Parent;
public:
	QString	TabName;
	QString	ButtonName;
	PQRunnerController	*Controller;

	MenuButton(PQSystemExecutor *p);
	~MenuButton(){}

private slots:
	void	SlotClicked();
};

class PQSystemExecutor : public QMainWindow,public ServiceForLayers
{
    Q_OBJECT

	PQRunnerControllerContainer	Runners;

	NPListPack<MenuButton>	Tabs[100];
	int						TabCount;
	PQSystemRunner			*CurrentRunner;
public:
    PQSystemExecutor(LayersBase *base,QWidget *parent = Q_NULLPTR);

	bool	LoadDLL(const QString &DLLPath);
	void	ShowController(PQRunnerController *Controller);

protected:
	virtual	void resizeEvent(QResizeEvent *event) override;

private:
    Ui::PQSystemExecutorClass ui;
};