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

#include "RobotRegulusWorld.h"

RobotRegulusWorld::RobotRegulusWorld(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    WorldBase=new RegulusWorld(); 

	SplitterH	=new QSplitter(this);
	SplitterH	->setOrientation(Qt::Horizontal);
	SplitterH	->addWidget(ui.openGLWidget);
	SplitterH	->addWidget(ui.frame);
	SplitterH	->setGeometry(0,0,width(),height());

	SplitterV	=new QSplitter(ui.frame);
	SplitterV	->setOrientation(Qt::Vertical);
	SplitterV	->addWidget(ui.treeWidgetObject);
	SplitterV	->addWidget(ui.tableWidgetProperty);
	SplitterV	->addWidget(ui.listWidgetCommand);
	SplitterV	->addWidget(ui.widgetExecutePanel);
}

RobotRegulusWorld::~RobotRegulusWorld()
{}

void RobotRegulusWorld::resizeEvent(QResizeEvent *event)
{
	SplitterH->setGeometry(0,0,width(),height());

	SplitterV->setGeometry(0,0,ui.frame->width(),ui.frame->height()-ui.widgetExecutePanel->height());
}

void RobotRegulusWorld::on_toolButtonExecute_clicked()
{

}

void RobotRegulusWorld::on_toolButtonOrigin_clicked()
{

}
