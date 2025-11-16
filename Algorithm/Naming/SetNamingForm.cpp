/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Naming\SetNamingForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "NamingResource.h"
#include "SetNamingForm.h"
#include "XNaming.h"
#include "XDataInLayerCommander.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"


extern	const	char	*sRoot;
extern	const	char	*sName;

SetNamingForm::SetNamingForm(ShowAndSetItemsBaseClass *Something ,LayersBase *Base,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	SetWidgetCenter(this);
	IData=NULL;

	InstallOperationLog(this);
}

SetNamingForm::~SetNamingForm()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}


void SetNamingForm::on_pushButtonOK_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		NamingItem	*BData=dynamic_cast<NamingItem *>(DA);
		if(BData==NULL)
			continue;

		BData->SetItemName(ui.lineEditName->text());
		BData->Column	=ui.spinBoxX->value();
		BData->Row		=ui.spinBoxY->value();
	}
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Set name");

	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"));
	Packet.Command=SetIndependentItemDataCommand_OnlyOne;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();

	GetLayersBase()->GetMainWidget()->BroadcastBuildForShow();
	close();
}

void	SetNamingForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		NamingItem	*BData=dynamic_cast<NamingItem *>(DA);
		if(BData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,NamingReqNameReqCommand ,NamingReqNameSendCommand);
		((NamingNameReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((NamingNameReq *)PacketReq.Data)->ItemID	=DA->GetID();
		((NamingNameReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			NamingNameSend	*ThrePoint=(NamingNameSend *)PacketSend.GetData();
			AreaName	=ThrePoint->AreaName;
			ui.lineEditName->setText(AreaName);
			ui.spinBoxX	->setValue(ThrePoint->Column);
			ui.spinBoxY	->setValue(ThrePoint->Row);
			break;
		}
	}
}
