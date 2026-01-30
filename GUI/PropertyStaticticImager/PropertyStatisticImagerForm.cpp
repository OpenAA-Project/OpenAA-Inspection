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

#include "PropertyStaticticImagerResource.h"

#include "PropertyStatisticImagerForm.h"
#include "XDisplayImage.h"
#include "XGUI.h"
#include "XGeneralDialog.h"
#include "ImageControlTools.h"
#include <omp.h>
#include "XStatisticPacket.h"

PropertyStatisticImagerForm::PropertyStatisticImagerForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);

	//���ʕ\�����̌����Ή�
	LangSolver.SetUI(this);
}

PropertyStatisticImagerForm::~PropertyStatisticImagerForm()
{

}

void	PropertyStatisticImagerForm::BuildForShow(void)
{
}
void	PropertyStatisticImagerForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetDrawModeStatistic	*CmdGetDrawModeStatisticVar=dynamic_cast<CmdGetDrawModeStatistic *>(packet);
	if(CmdGetDrawModeStatisticVar!=NULL){
	//////////////
		if(ui.toolButtonMaster->isChecked()==true)
			CmdGetDrawModeStatisticVar->DrawMode=StatisticImagerDrawAttr::_None;
		else if(ui.toolButtonAverage->isChecked()==true)
			CmdGetDrawModeStatisticVar->DrawMode=StatisticImagerDrawAttr::_Average;
		else if(ui.toolButtonDark->isChecked()==true)
			CmdGetDrawModeStatisticVar->DrawMode=StatisticImagerDrawAttr::_Dark;
		else if(ui.toolButtonLight->isChecked()==true)
			CmdGetDrawModeStatisticVar->DrawMode=StatisticImagerDrawAttr::_Light;
		else if(ui.toolButtonDisorder->isChecked()==true)
			CmdGetDrawModeStatisticVar->DrawMode=StatisticImagerDrawAttr::_Disorder;

	/////////////
		/*if(ui.toolButtonMaster->isChecked()==true)
			CmdGetDrawModeStatisticVar->DrawMode=StatisticImagerDrawAttr::_None;
		if(ui.toolButtonAverage->isChecked()==true)
			CmdGetDrawModeStatisticVar->DrawMode=StatisticImagerDrawAttr::_Average;
		if(ui.toolButtonDark->isChecked()==true)
			CmdGetDrawModeStatisticVar->DrawMode=StatisticImagerDrawAttr::_Dark;
		if(ui.toolButtonLight->isChecked()==true)
			CmdGetDrawModeStatisticVar->DrawMode=StatisticImagerDrawAttr::_Light;
		if(ui.toolButtonDisorder->isChecked()==true)
			CmdGetDrawModeStatisticVar->DrawMode=StatisticImagerDrawAttr::_Disorder;*/
	//////////////

	}
}
void	PropertyStatisticImagerForm::ShowInEdit(void)
{
}



void PropertyStatisticImagerForm::on_toolButtonMaster_clicked()
{

}

void PropertyStatisticImagerForm::on_toolButtonAverage_clicked()
{

}

void PropertyStatisticImagerForm::on_toolButtonDark_clicked()
{

}

void PropertyStatisticImagerForm::on_toolButtonLight_clicked()
{

}

void PropertyStatisticImagerForm::on_toolButtonDisorder_clicked()
{

}

//===================================================================
GUICmdReqMakeAverageImage::GUICmdReqMakeAverageImage(LayersBase *Base ,QString &EmitterRoot,QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqMakeAverageImage::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqMakeAverageImage::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqMakeAverageImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticImager");
	if(BBase!=NULL){
		CmdMakeAverageStatistic	RCmd(this);
		BBase->TransmitDirectly(&RCmd);
	}
}