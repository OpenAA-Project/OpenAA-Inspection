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

#include "PropertyXRay3DForm.h"
#include "ui_PropertyXRay3DForm.h"
#include "XGeneralFunc.h"
#include "XPropertyXRay3DPacket.h"
#include "XXRay3D.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralDialog.h"
#include "XStandardCommand.h"
#include "XDisplayImagePacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyXRay3DForm::PropertyXRay3DForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyXRay3DForm)
{
    ui->setupUi(this);

	//::SetColumnWidthInTable(ui->tableWidgetList ,0, 33);
	//::SetColumnWidthInTable(ui->tableWidgetList ,1, 33);
	//::SetColumnWidthInTable(ui->tableWidgetList ,2, 33);

}

PropertyXRay3DForm::~PropertyXRay3DForm()
{
    delete ui;
}
XRay3DBase	*PropertyXRay3DForm::GetXRay3DBase(void)
{
	return (XRay3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"XRay3D");
}

void	PropertyXRay3DForm::TransmitDirectly(GUIDirectMessage *packet)
{
	//GUICmdXRay3DDrawEnd	*GUICmdXRay3DDrawEndVar=dynamic_cast<GUICmdXRay3DDrawEnd *>(packet);
	//if(GUICmdXRay3DDrawEndVar!=NULL){
	//	EditItemDialog	D(GetLayersBase());
	//	if(D.exec()==(int)true){
	//		IntList PageList;
	//		GetLayersBase()->GetLocalPageFromArea(GUICmdXRay3DDrawEndVar->Area,PageList);
	//		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
	//			int	page=P->GetValue();
	//			DataInPage	*pdata=GetLayersBase()->GetPageData(page);
	//			FlexArea	A=GUICmdXRay3DDrawEndVar->Area;
	//			pdata->ClipMoveAreaFromGlobal(A);
	//			if(A.GetPatternByte()>0){
	//				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
	//				GUICmdSendAddManualXRay3D	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
	//				Cmd.Area=A;
	//				Cmd.RepeatCount		=D.RepeatCount		;
	//				Cmd.MeshSize		=D.MeshSize			;
	//				Cmd.SequenceOffset	=D.SequenceOffset	;
	//				Cmd.GatherAllPhase	=D.GatherAllPhase	;
	//				Cmd.Send(NULL,GlobalPage,0);
	//			}
	//		}
	//		ShowList();
	//	}
	//	return;
	//}
	//CmdXRay3DDrawAttr	*CmdXRay3DDrawAttrVar=dynamic_cast<CmdXRay3DDrawAttr *>(packet);
	//if(CmdXRay3DDrawAttrVar!=NULL){
	//	XRay3DBase	*ABase=GetXRay3DBase();
	//	CmdXRay3DDrawAttrVar->BlockColor0	=ABase->Color0;
	//	CmdXRay3DDrawAttrVar->BlockColor1	=ABase->Color1;
	//	CmdXRay3DDrawAttrVar->BlockColor2	=ABase->Color2;
	//	CmdXRay3DDrawAttrVar->BlockColor3	=ABase->Color3;
	//	CmdXRay3DDrawAttrVar->BlockColor4	=ABase->Color4;
	//	CmdXRay3DDrawAttrVar->BlockColor5	=ABase->Color5;
	//	CmdXRay3DDrawAttrVar->BlockColor6	=ABase->Color6;
	//	CmdXRay3DDrawAttrVar->BlockColor7	=ABase->Color7;
	//	CmdXRay3DDrawAttrVar->ShowingItemID	=0;
	//	return;
	//}
}

void	PropertyXRay3DForm::StartPage(void)
{
	//ShowList();
}
void	PropertyXRay3DForm::BuildForShow(void)
{
	//XRay3DBase	*BBase=GetXRay3DBase();
	//ui->spinBoxWholeRepeatCount->setValue(BBase->DefaultRepeatCount);
	//ShowList();
}


void PropertyXRay3DForm::on_verticalSliderImageFiles_valueChanged(int value)
{
	GUICmdSetPointY	RCmd(GetLayersBase(),sRoot,sName);
	RCmd.PointToDraw = value;
	RCmd.Send(NULL,0,0);

	ui->labelCounter->setText(QString::number(value));

	ReviewImage();
}


void PropertyXRay3DForm::on_pushButtonLoadImageFiles_clicked()
{
	QStringList	FileList = QFileDialog::getOpenFileNames(NULL
											,/**/"Select Image Files"
											,QString()
											,/**/"Image Files (*.bmp *.jpg *.jpeg *.png *.tif *.tiff);;All Files (*.*)");
	if(FileList.size()>0){
		ui->listWidgetXRayImage->addItems(FileList);
		ui->verticalSliderImageFiles->setMaximum(FileList.count()-1);
		GUICmdLoadImages	RCmd(GetLayersBase(),sRoot,sName,0);
		RCmd.ImageFileNames = FileList;
		RCmd.Send(NULL,0,0);

		ui->verticalSliderImageFiles->setValue(FileList.count()/2);
	}
}


void PropertyXRay3DForm::on_pushButtonLoadGerber_clicked()
{
	QString	FileName = QFileDialog::getOpenFileName(NULL
											,/**/"Select Gerber Image File"
											,QString()
											,/**/"Gerber Image Files (*.gbr *.gb *.gerber);;All Files (*.*)");
	if(!FileName.isEmpty()){
		ui->lineEditGerber->setText(FileName);
		GUICmdReqMatchFile	RCmd(GetLayersBase(),sRoot,sName,0);
		GUICmdAckMatchFile	ACmd(GetLayersBase(),sRoot,sName,0);
		RCmd.FileName = FileName;
		if(RCmd.Send(0,0,ACmd)==true){
			ui->lineEditPosition->setText(QString("L:")+QString::number(ACmd.RetFileNo)
										 +QString(" X:")+QString::number(ACmd.RetX)
										 +QString(" Y:")+QString::number(ACmd.RetY));
		}
	}
}

void PropertyXRay3DForm::ReviewImage(void)
{
	GUIFormBase *GProp = GetLayersBase()->FindByName(/**/"Inspection",/**/"XRay3DImagePanel",/**/"");
	if(GProp!=NULL){
		GProp->Repaint();
	}
}

void PropertyXRay3DForm::on_pushButtonSmooth_clicked()
{
	GUICmdReqSmooth	RCmd(GetLayersBase(),sRoot,sName);
	RCmd.Send(NULL,0,0);

	ReviewImage();
}


void PropertyXRay3DForm::on_pushButtonEmphasize_clicked()
{
	GUICmdReqEmphasize	RCmd(GetLayersBase(),sRoot,sName);
	RCmd.Send(NULL,0,0);

	ReviewImage();
}


void PropertyXRay3DForm::on_pushButtonSearchPosition_clicked()
{

}

