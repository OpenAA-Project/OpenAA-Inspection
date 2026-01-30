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


#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "SelectMovePastePage.h"
#include "ui_SelectMovePastePage.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"

void	SelectMovePastePageFrame::Initial(int N,QWidget *parent ,IntList *_PageList)
{
    PageList=_PageList;
    PageFrame.setParent(parent);
    PageFrame.setGeometry(10,10+N*45,240,40);
    SourceLabel.setParent(&PageFrame);
    SourceLabel.setGeometry(10,10,51,16);
    SourceLabel.setText(LangDISolver.GetString(SelectMovePastePage_LS,LID_8)/*"Page "*/+QString::number(SourcePage));
    IntClass	*c=PageList->GetFirst();
    if(c!=NULL){
        DestPage1.setParent(&PageFrame);
        DestPage1.setGeometry(80,10,61,18);
        DestPage1.setText(LangDISolver.GetString(SelectMovePastePage_LS,LID_9)/*"Page "*/+QString::number(c->GetValue()));
        DestPage1.setChecked(true);
        c=c->GetNext();
        if(c!=NULL){
            DestPage2.setParent(&PageFrame);
            DestPage2.setGeometry(160,10,61,18);
            DestPage2.setText(LangDISolver.GetString(SelectMovePastePage_LS,LID_10)/*"Page "*/+QString::number(c->GetValue()));
            DestPage2.setChecked(true);
        }
    }
}

void	SelectMovePastePageFrame::LodFromWindow(void)
{
    IntClass	*c=PageList->GetFirst();
    if(c!=NULL){
        IntClass	*d=c->GetNext();
        if(DestPage1.isChecked()==false){
            PageList->RemoveList(c);
            delete	c;
        }
        if(d!=NULL){
            if(DestPage2.isChecked()==false){
                PageList->RemoveList(d);
                delete	d;
            }
        }
    }
}

SelectMovePastePage::SelectMovePastePage(LayersBase *Base,IntList *_PageList,int _PageCount,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectMovePastePage)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
    LangDISolver.SetUI(this);

    SetWidgetCenter(this);

    PageList=_PageList;
    PageCount=_PageCount;
    FrameCount=0;
    for(int i=0;i<PageCount;i++){
        if(PageList[i].GetCount()!=0){
            FrameCount++;
        }
    }
    Frames=new SelectMovePastePageFrame[FrameCount];
    SArea.setParent(this);
    SArea.setGeometry(ui->frameBase->geometry().left(),ui->frameBase->geometry().top()
                     ,ui->frameBase->width(),ui->frameBase->height());
    delete	ui->frameBase;
    ui->frameBase=NULL;
    int	L=0;
    for(int page=0;page<PageCount;page++){
        if(PageList[page].GetCount()!=0){
            Frames[L].SourcePage=page;
            Frames[L].Initial(L,&SArea,&PageList[page]);
            L++;
        }
    }
    Base->InstallOperationLog(this);
}

SelectMovePastePage::~SelectMovePastePage()
{
    delete ui;
    delete	[]Frames;
}

void SelectMovePastePage::on_pushButton_clicked()
{
    for(int i=0;i<FrameCount;i++){
        Frames[i].LodFromWindow();
    }
    done(true);
}

void SelectMovePastePage::on_pushButton_2_clicked()
{
    done(false);
}