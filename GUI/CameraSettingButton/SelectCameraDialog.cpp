/*
 * Copyright (C) 2025
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
		connect(&CamButtons,SIGNAL(idClicked(int)),this,SLOT(SlotButtonClicked(int)));
	}
	SetWidgetCenter(this);
	InstallOperationLog(this);
}

SelectCameraDialog::~SelectCameraDialog()
{

}

void SelectCameraDialog::SlotButtonClicked(int Cam)
{
	CamNo=Cam;
	done((int)true);
}