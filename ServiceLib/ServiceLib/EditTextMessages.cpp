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

#include "ServiceLibResource.h"
#include "XTypeDef.h"
#include "EditTextMessages.h"
#include "ui_EditTextMessages.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"

EditTextMessages::EditTextMessages(LayersBase *pbase ,TextMessageContainer &_TextMessageContainerData,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(pbase)
    ,ui(new Ui::EditTextMessages)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);

    TextMessageContainerData=_TextMessageContainerData;
    SetDataToWindow();
    InstallOperationLog(this);
}

EditTextMessages::~EditTextMessages()
{
    delete ui;
}


void	EditTextMessages::resizeEvent ( QResizeEvent * event )
{
    ui->tableWidget->resize(width()-2,ui->tableWidget->height());
}

void EditTextMessages::on_pushButtonOK_clicked()
{
    GetDataFromWindow();
    done(true);
}

void EditTextMessages::GetDataFromWindow(void)
{
    int	Row=0;
    for(TextMessageList *a=TextMessageContainerData.GetFirst();a!=NULL;a=a->GetNext()){
        a->Message=GetDataToTable(ui->tableWidget,0,Row);
        Row++;
    }
}
void EditTextMessages::SetDataToWindow(void)
{
    ui->tableWidget->setRowCount(TextMessageContainerData.GetNumber());
    QStringList	Labs;
    int	Row=0;
    for(TextMessageList *a=TextMessageContainerData.GetFirst();a!=NULL;a=a->GetNext()){
        Labs.append(a->PathAndName);
        SetDataToTable(ui->tableWidget,0,Row ,a->Message);
        QTableWidgetItem	*s=ui->tableWidget->item(Row,0);
        s->setFlags(s->flags() | Qt::ItemIsEditable);
        Row++;
    }
    ui->tableWidget->setVerticalHeaderLabels(Labs);
}

void EditTextMessages::on_pushButtonCancel_clicked()
{
    done(false);
}

void EditTextMessages::on_pushButtonSave_clicked()
{
    GetDataFromWindow();

    QString FileName=QFileDialog::getSaveFileName (this
                                                    , LangLibSolver.GetString(EditTextMessages_LS,LID_4009)/*"Save Mesage"*/
                                                    , QString()
                                                    ,LangLibSolver.GetString(EditTextMessages_LS,LID_4010)/*"MessageFile (*.Mxt)"*/);
    if(FileName.isEmpty()==false){
        QFile	FL(FileName);
        if(FL.open(QIODevice::WriteOnly)==true){
            TextMessageContainerData.Save(&FL);
        }
    }
}

void EditTextMessages::on_pushButtonLoad_clicked()
{
    QString FileName=QFileDialog::getOpenFileName (this
                                                , LangLibSolver.GetString(EditTextMessages_LS,LID_4011)/*"Load Mesage"*/
                                                , QString()
                                                ,LangLibSolver.GetString(EditTextMessages_LS,LID_4012)/*"MessageFile (*.Mxt)"*/);
    if(FileName.isEmpty()==false){
        QFile	FL(FileName);
        if(FL.open(QIODevice::ReadOnly)==true){
            TextMessageContainer	_TextMessageContainerData;
            _TextMessageContainerData.Save(&FL);
            for(TextMessageList *a=_TextMessageContainerData.GetFirst();a!=NULL;a=a->GetNext()){
                for(TextMessageList *b=TextMessageContainerData.GetFirst();b!=NULL;b=b->GetNext()){
                    if(b->PathAndName==a->PathAndName){
                        b->Message=a->Message;
                    }
                }
            }
            SetDataToWindow();
        }
    }
}