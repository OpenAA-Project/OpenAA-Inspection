/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\CameraSettingButton\SelectCameraDialog.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "CameraSettingButtonResource.h"
#include "SelectCameraDialog.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include <QPushButton>

SelectCameraDialog::SelectCameraDialog(LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);

	for(int page=0;page<GetPageNumb();page++){
		int	Cam=GetParamGlobal()->GetCameraNo(page);
		if(Cam<GetParamGlobal()->TotalCameraNumb){
			IntClass *s;
			for(s=CamList.GetFirst();s!=NULL;s=s->GetNext()){
				if(s->GetValue()==Cam)
					break;
			}
			if(s==NULL){
				CamList.Add(Cam);
			}
		}
	}
	if(CamList.GetFirst()!=NULL)
		CamNo=CamList.GetFirst()->GetValue();

	if(CamList.GetCount()>1){
		ScrollBack.move(0,0);
		ui.scrollArea->setWidget(&ScrollBack);
		int	N=0;
		for(IntClass *s=CamList.GetFirst();s!=NULL;s=s->GetNext(),N++){
			int	Cam=s->GetValue();
			QPushButton	*B=new QPushButton();
			B->setParent(&ScrollBack);
			B->setText(QString(/**/"Camera ")+QString::number(Cam));
			B->setGeometry(0,N*32,ui.scrollArea->width()-2,30);

			CamButtons.addButton(B,Cam);
		}
		ScrollBack.resize(ui.scrollArea->width(),32*N);
		connect(&CamButtons,SIGNAL(buttonClicked(int)),this,SLOT(SlotButtonClicked(int)));
	}
	SetWidgetCenter(this);
	InstallOperationLog(this);
}

SelectCameraDialog::~SelectCameraDialog()
{

}

void SelectCameraDialog::SlotButtonClicked ( int Cam )
{
	CamNo=Cam;
	done((int)true);
}