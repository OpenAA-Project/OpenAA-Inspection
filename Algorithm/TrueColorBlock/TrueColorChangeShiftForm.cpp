/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TrueColorBlock\TrueColorChangeShiftForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTrueColorBlockResource.h"
#include "TrueColorChangeShiftForm.h"
#include "XGeneralFunc.h"
#include "XDataInLayerCommander.h"
#include "XTrueColorBlock.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

TrueColorChangeShiftForm::TrueColorChangeShiftForm(LayersBase *Base,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	SetWidgetCenter(this);
	IData=NULL;
	ImageParent=NULL;

	InstallOperationLog(this);
}

TrueColorChangeShiftForm::~TrueColorChangeShiftForm()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;

}


void TrueColorChangeShiftForm::on_pushButton_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketSend.BuildData(sRoot,sName,TrueColorBlockReqChangeShiftCommand ,NULL);
		((TrueColorBlockChangeShift *)PacketSend.Data)->GlobalPage	=D->GlobalPage;
		((TrueColorBlockChangeShift *)PacketSend.Data)->Layer		=D->Layer;
		((TrueColorBlockChangeShift *)PacketSend.Data)->BlockItemID	=DA->GetID();
		((TrueColorBlockChangeShift *)PacketSend.Data)->Dx			=ui.spinBoxXDir->value();
		((TrueColorBlockChangeShift *)PacketSend.Data)->Dy			=ui.spinBoxYDir->value();

		PacketSend.Send(NULL,D->GlobalPage,0);
	}
	if(ImageParent!=NULL)
		ImageParent->repaint();

}

void TrueColorChangeShiftForm::on_pushButtonCancel_clicked()
{
	close();
}
void	TrueColorChangeShiftForm::Initial(QWidget *parent ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
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
