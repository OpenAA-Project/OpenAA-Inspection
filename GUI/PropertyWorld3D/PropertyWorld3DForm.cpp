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

#include "PropertyWorld3DForm.h"
#include "ui_PropertyWorld3DForm.h"
#include "XPropertyWorld3DPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


PropertyWorld3DForm::PropertyWorld3DForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyWorld3DForm)
{
    ui->setupUi(this);
}

PropertyWorld3DForm::~PropertyWorld3DForm()
{
    delete ui;
}

World3DBase	*PropertyWorld3DForm::GetWorld3DBase(void)
{
	return (World3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"World3D");
}

void PropertyWorld3DForm::on_pushButtonAddStepFile_clicked()
{
    QString FileName=QFileDialog::getSaveFileName(NULL
                                                ,"Load step file"
                                                ,QString()
                                                ,/**/"Step file(*.step *.stp;;All files(*.*)");
    if(FileName.isEmpty()==false){
        QFile   File(FileName);
        if(File.open(QIODevice::ReadWrite)==true){
            QByteArray  FArray=File.readAll();
            for(int page=0;page<GetPageNumb();page++){
                int GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
                GUICmdLoadStepFile  RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
                RCmd.FArray=FArray;
                RCmd.Send(NULL,GlobalPage,0);
            }
        }
    }
}
