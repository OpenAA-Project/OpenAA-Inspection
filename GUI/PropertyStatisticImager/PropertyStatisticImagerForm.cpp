#include "PropertyStatisticImagerResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyStatisticImager\PropertyStatisticImagerForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyStatisticImagerForm.h"
#include "XDisplayImage.h"
#include "XGUI.h"
#include "XGeneralDialog.h"
#include "ImageControlTools.h"
#include <omp.h>
#include "XStatisticPacket.h"
#include "XPropertyStatisticImagerCommon.h"

PropertyStatisticImagerForm::PropertyStatisticImagerForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);

	//‰æ–Ê•\Ž¦•”‚ÌŒ¾Œê‘Î‰ž
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
GUICmdReqMakeAverageImage::GUICmdReqMakeAverageImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
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
