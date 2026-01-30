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


#include "ButtonExitResource.h"
#include "CloseMessageForm.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XParamGlobal.h"

extern	char	*sRoot;
extern	char	*sName;

CloseMessageForm::CloseMessageForm(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	LogoInQWidget(Base,this,sRoot ,sName);

	SetWidgetCenter(this);
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);
//	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	if(GetLayersBase()->GetParamComm()->ConnectedPCNumb==0){
		ui.pushButtonCloseAll->setVisible(false);
		ui.pushButtonCloseOne->setDefault(true);
	}
}

CloseMessageForm::~CloseMessageForm()
{

}

void CloseMessageForm::on_pushButtonCloseAll_clicked()
{
	GetLayersBase()->CloseAll();
	QCoreApplication::quit();	
}

void CloseMessageForm::on_pushButtonCloseOne_clicked()
{
	GetLayersBase()->CloseOne();
	QCoreApplication::quit();	
}

void CloseMessageForm::on_pushButtonCalcen_clicked()
{
	close();
}