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

#include "CompressImageListResource.h"

#include "CompressImgeListForm.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

CompressImgeListForm::CompressImgeListForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	ModeToDisplayList	=true;
	ListNumb	=0;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	PDim=NULL;
}

CompressImgeListForm::~CompressImgeListForm()
{
	if(PDim!=NULL)
		delete	[]PDim;
	PDim=NULL;
}

void	CompressImgeListForm::Prepare(void)
{
	if(ModeToDisplayList==true){
		ui.stackedWidget->setCurrentIndex(0);
	}
	else{
		ui.stackedWidget->setCurrentIndex(1);
		ScrollArea=new QScrollArea(ui.stackedWidget);
		ScrollArea->move(0,0);
		ScrollArea->resize(ui.stackedWidget->width(),ui.stackedWidget->height());
		ScrollArea->setBackgroundRole(QPalette::Dark);
		SImagePanel	=new ScrollerImage();
		SImagePanel->resize(1000,ui.stackedWidget->height()-10);
		ScrollArea->setWidget(SImagePanel);
	}
}

AutoSaveImageBase	*CompressImgeListForm::GetAutoSaveImageBase(void)
{
	return (AutoSaveImageBase	*)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoSaveImage");
}

int	PDimFunc(const void *a ,const void *b)
{
	if(((IDAndFileNameList **)a)[0]->InspectionID<((IDAndFileNameList **)b)[0]->InspectionID)
		return 1;
	if(((IDAndFileNameList **)a)[0]->InspectionID<((IDAndFileNameList **)b)[0]->InspectionID)
		return -1;
	return 0;
}

QString	GetBaseIDName(const QString &FileName)
{
	QFileInfo	Info(FileName);
	QString		path=Info.path();
	QString		Base=Info.baseName();
	QStringList	NValues=Base.split('-');
	QString		XIDBase;
	for(int i=0;i<NValues.count()-2;i++){
		XIDBase+=NValues[i];
	}
	return path+XIDBase;
}


void	CompressImgeListForm::BuildForShow(void)
{
	IDAndFileNames.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqFileEntryList	RCmd(GetLayersBase(),sRoot,sName,page);
		GUICmdAckFileEntryList	ACmd(GetLayersBase(),sRoot,sName,page);
		RCmd.Send(page,0,ACmd);
		if(ACmd.IsReceived()==true){
			for(FileEntryList *a=ACmd.FileEntries.GetFirst();a!=NULL;a=a->GetNext()){
				IDAndFileNameList	*b;
				QString	ABaseID=GetBaseIDName(a->FileName);
				for(b=IDAndFileNames.GetFirst();b!=NULL;b=b->GetNext()){
					QString	BBaseID=GetBaseIDName(b->FileName);
					if(a->InspectionID==b->InspectionID && ABaseID==BBaseID)
						break;
				}
				if(b==NULL){
					b=new IDAndFileNameList();
					b->FileStamp=a->FileStamp;
					b->FileName=a->FileName;
					b->InspectionID=a->InspectionID;
					b->LotAutoCount=a->LotAutoCount;
					IDAndFileNames.AppendList(b);
				}
			}
		}
	}
	ListNumb=IDAndFileNames.GetNumber();
	if(PDim!=NULL)
		delete	[]PDim;
	PDim=new IDAndFileNameList*[ListNumb];
	int	i=0;
	for(IDAndFileNameList *a=IDAndFileNames.GetFirst();a!=NULL;a=a->GetNext()){
		PDim[i]=a;
		i++;
	}
	QSort(PDim,ListNumb,sizeof(PDim[0]),PDimFunc);

	if(ModeToDisplayList==true){
		XDateTime tmpDT;

		ui.tableWidget->setColumnWidth(0,50);
		ui.tableWidget->setColumnWidth(1,50);
		ui.tableWidget->setColumnWidth(2,ui.tableWidget->width()-160);
		ui.tableWidget->setRowCount(ListNumb);
		for(int j=0;j<ListNumb;j++){
			QTableWidgetItem *w;
			w=ui.tableWidget->item (j, 0);
			if(w==NULL){
				ui.tableWidget->setItem(j,0,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(QString::number(j+1));
		
			w=ui.tableWidget->item (j, 1);
			if(w==NULL){
				ui.tableWidget->setItem(j,1,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(QString::number(PDim[j]->InspectionID));
		
			w=ui.tableWidget->item (j, 2);
			if(w==NULL){
				ui.tableWidget->setItem(j,2,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(PDim[j]->FileStamp.toString(/**/"yy.MM.dd hh:mm:ss"));
			
		}
	}
	else{
		SImagePanel->resize(100*ListNumb,SImagePanel->height());
		for(int j=0;j<ListNumb;j++){
			QImage	Img(64,64,QImage::Format_RGB32);
			SMakeImage(PDim[j]);
			PDim[j]->LabelImage.setParent(SImagePanel);
			PDim[j]->LabelImage.move(100*j,10);
		}
	}
//	ui.tableWidget->resizeColumnToContents(0);	//������column�̃T�C�Y�����߂Ă�����
//	ui.tableWidget->resizeColumnToContents(1);	//���x���S�z�Ȃ̂ŃR�����g�A�E�g
//	ui.tableWidget->resizeColumnToContents(2);
}

void	CompressImgeListForm::SMakeImage(IDAndFileNameList *p)
{

}

void	CompressImgeListForm::ShowInEdit(void)
{
}


void CompressImgeListForm::on_pushButtonUpdate_clicked()
{
	BuildForShow();
}

void CompressImgeListForm::on_tableWidget_clicked(const QModelIndex &)
{
	int	R=ui.tableWidget->currentRow();
	if(ListNumb>R){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqLoad	RCmd(GetLayersBase(),sRoot,sName,page);
			GUICmdAckLoad	ACmd(GetLayersBase(),sRoot,sName,page);
			RCmd.InspectionID	=PDim[R]->InspectionID;
			RCmd.LotAutoCount	=PDim[R]->LotAutoCount;
			RCmd.FileName		=PDim[R]->FileName;
			RCmd.Send(page,0,ACmd);
		}
	}
}


void	CompressImgeListForm::ResizeAction(void)
{
	ui.pushButtonUpdate->resize(width(), ui.pushButtonUpdate->height());
	ui.stackedWidget->resize(width(), height()-ui.pushButtonUpdate->height());

	if(ModeToDisplayList==true){
		ui.tableWidget->resize(ui.stackedWidget->width(),ui.stackedWidget->height());
	}
	else{
		ScrollArea->resize(ui.stackedWidget->width(),ui.stackedWidget->height());
	}
}

//=========================================================================

GUICmdReqFileEntryList::GUICmdReqFileEntryList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqFileEntryList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckFileEntryList	*SendBack=GetSendBack(GUICmdAckFileEntryList,GetLayersBase(),EmitterRoot,EmitterName,localPage);

	SendBack->MakeData(localPage);
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckFileEntryList::GUICmdAckFileEntryList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdAckFileEntryList::MakeData(int LocalPage)
{
	AutoSaveImageBase	*ABase=(AutoSaveImageBase	*)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoSaveImage");
	if(ABase!=NULL){
		CmdGetFileEntries	Cmd(GetLayersBase());
		Cmd.LocalPage=LocalPage;
		ABase->TransmitDirectly(&Cmd);
		FileEntries=Cmd.Entries;
	}
}

bool	GUICmdAckFileEntryList::Load(QIODevice *f)
{
	if(FileEntries.Save(f)==false)
		return false;
	return true;
}
bool	GUICmdAckFileEntryList::Save(QIODevice *f)
{
	if(FileEntries.Load(f)==false)
		return false;
	return true;
}


GUICmdReqLoad::GUICmdReqLoad(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqLoad::Load(QIODevice *f)
{
	if(::Load(f,InspectionID)==false)
		return false;
	if(::Load(f,LotAutoCount)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	return true;
}
bool	GUICmdReqLoad::Save(QIODevice *f)
{
	if(::Save(f,InspectionID)==false)
		return false;
	if(::Save(f,LotAutoCount)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	return true;
}

void	GUICmdReqLoad::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckLoad	*SendBack=GetSendBack(GUICmdAckLoad,GetLayersBase(),EmitterRoot,EmitterName,localPage);

	AutoSaveImageBase	*ABase=(AutoSaveImageBase	*)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoSaveImage");
	if(ABase!=NULL){
		CmdLoadFile	Cmd(GetLayersBase());
		Cmd.InspectionID	= InspectionID;
		Cmd.LocalPage		= localPage;
		Cmd.LotAutoCount	= LotAutoCount;
		Cmd.FileName		= FileName;
		ABase->TransmitDirectly(&Cmd);
	}
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckLoad::GUICmdAckLoad(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
