/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ColorBlockInspection\ColorChangeShiftForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ColorBlockFormResource.h"
#include "ColorChangeShiftForm.h"
#include "XGeneralFunc.h"
#include "XDataInLayerCommander.h"
#include "XColorBlockInspection.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ColorChangeShiftForm::ColorChangeShiftForm(LayersBase *Base,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	SetWidgetCenter(this);
	IData=NULL;
	ImageParent=NULL;

	InstallOperationLog(this);
}

ColorChangeShiftForm::~ColorChangeShiftForm()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;

}


void ColorChangeShiftForm::on_pushButton_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketSend.BuildData(sRoot,sName,ColorBlockReqChangeShiftCommand ,NULL);
		((ColorBlockChangeShift *)PacketSend.Data)->GlobalPage	=D->GlobalPage;
		((ColorBlockChangeShift *)PacketSend.Data)->BlockItemID	=DA->GetID();
		((ColorBlockChangeShift *)PacketSend.Data)->Dx			=ui.spinBoxXDir->value();
		((ColorBlockChangeShift *)PacketSend.Data)->Dy			=ui.spinBoxYDir->value();

		PacketSend.Send(NULL,D->GlobalPage,0);
	}
	if(ImageParent!=NULL)
		ImageParent->repaint();

}

void ColorChangeShiftForm::on_pushButtonCancel_clicked()
{
	close();
}
void	ColorChangeShiftForm::Initial(QWidget *parent ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	ImageParent=parent;
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
}
