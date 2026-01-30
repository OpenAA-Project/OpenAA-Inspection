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