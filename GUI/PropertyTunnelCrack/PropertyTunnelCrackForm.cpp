#include "CreateTunnelFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyTunnelCrack\PropertyTunnelCrackForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyTunnelCrackForm.h"
#include "CreateTunnelForm.h"
#include "EditTunnelCrackLibrary.h"
#include "XGeneralFunc.h"
#include "ButtonLoadBmpJpg.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"


extern	char	*sRoot;
extern	char	*sName;

PropertyTunnelCrackForm::PropertyTunnelCrackForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
}

PropertyTunnelCrackForm::~PropertyTunnelCrackForm()
{
}

TunnelCrackBase	*PropertyTunnelCrackForm::GetTunnelCrackBase(void)
{
	return (TunnelCrackBase *)GetLayersBase()->GetAlgorithmBase(/**/"Customized",/**/"TunnelCrack");
}

void	PropertyTunnelCrackForm::BuildForShow(void)
{
	ShowAreaGrid();
}
void	PropertyTunnelCrackForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreateTunnelCrackDrawEnd	*CmdCreateTunnelCrackDrawEndVar=dynamic_cast<CmdCreateTunnelCrackDrawEnd *>(packet);
	if(CmdCreateTunnelCrackDrawEndVar!=NULL){
		CreateTunnelForm	D(GetLayersBase(),this);
		if(D.exec()==(int)true){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(CmdCreateTunnelCrackDrawEndVar->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=CmdCreateTunnelCrackDrawEndVar->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					GUICmdSendAddManualTunnelCrack	Cmd(GetLayersBase(),sRoot,sName,page);
					Cmd.Area=A;
					Cmd.SelectedLibID	=D.SelectedLibID;
					Cmd.LayerList=CmdCreateTunnelCrackDrawEndVar->LayerList;
					Cmd.SendOnly(GetLayersBase()->GetGlobalPageFromLocal(page),0);
				}
			}
			ShowAreaGrid();
		}
	}
}
void	PropertyTunnelCrackForm::ShowAreaGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	TunnelCrackBase	*BBase=GetTunnelCrackBase();

	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendTunnelCrackList	**BmpReceiver=new GUICmdSendTunnelCrackList*[GetParamGlobal()->PageNumb];
	GUICmdReqTunnelCrackList	**BmpRequester=new GUICmdReqTunnelCrackList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpReceiver[page]=new GUICmdSendTunnelCrackList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[page]=new GUICmdReqTunnelCrackList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	}

	TunnelCrackInfo.RemoveAll();
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page])==true
		&& BmpReceiver[page]->IsReceived()==true){
			TunnelCrackInfo+=BmpReceiver[page]->TunnelCrackInfo;
		}
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	BmpRequester[page];
		delete	BmpReceiver[page];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	int	Row=0;
	int	Numb=TunnelCrackInfo.GetNumber();
	ui.tableWidget->setRowCount(Numb);
	for(TunnelCrackInfoList *L=TunnelCrackInfo.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		QTableWidgetItem *w;
		w=ui.tableWidget->item (Row, 0);
		if(w==NULL){
			ui.tableWidget->setItem(Row,0,(w=new QTableWidgetItem()));
			w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		w->setText(QString::number(L->GlobalPage));
		
		w=ui.tableWidget->item (Row, 1);
		if(w==NULL){
			ui.tableWidget->setItem(Row,1,(w=new QTableWidgetItem()));
			w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		w->setText(QString::number(L->Layer));
	
		w=ui.tableWidget->item (Row, 2);
		if(w==NULL){
			ui.tableWidget->setItem(Row,2,(w=new QTableWidgetItem()));
			w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		w->setText(QString::number(L->LibID));
	
		w=ui.tableWidget->item (Row, 3);
		if(w==NULL){
			ui.tableWidget->setItem(Row,3,(w=new QTableWidgetItem()));
			w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		CmdGetLibName	Cmd;
		Cmd.LibID=L->LibID;
		BBase->TransmitDirectly(&Cmd);
		w->setText(Cmd.LibName);
	}

	ReEntrant=false;
}

void PropertyTunnelCrackForm::on_pushButtonEditLibrary_clicked()
{
	EditTunnelCrackLibrary	D(GetLayersBase(),this);
	D.exec();
}

void PropertyTunnelCrackForm::on_pushButtonSaveAll_clicked()
{
	QString FileName=GetLayersBase()->LGetSaveFileName(this, /**/""
													, QString()
													, /**/"Pix with Algorithm(*.pwa)");

	if(FileName.isEmpty()==true)
		return;

	QFile	FL(FileName);

	if(FL.open(QIODevice::WriteOnly)==false)
		return;

	QString	ImgFileName;
	GUIFormBase	*TProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"ButtonLoadBmpJpg" ,/**/"");
	if(TProp!=NULL){
		ButtonLoadBmpJpg	*b=dynamic_cast<ButtonLoadBmpJpg *>(TProp);
		if(b!=NULL){
			ImgFileName=b->LoadedFileName;
		}
	}
	::Save(&FL,ImgFileName);

	if(GetLayersBase()->SavePixWithAlgorithm(&FL)==false){
		return;
	}
}

void PropertyTunnelCrackForm::on_pushButtonLoadAll_clicked()
{
	QString FileName=GetLayersBase()->LGetOpenFileName(this, /**/""
													, QString(), /**/"Pix with Algorithm(*.pwa)");

	if(FileName.isEmpty()==true)
		return;

	QFile	FL(FileName);

	if(FL.open(QIODevice::ReadOnly)==false)
		return;

	QString	ImgFileName;
	::Load(&FL,ImgFileName);

	GUIFormBase	*TProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"ButtonLoadBmpJpg" ,/**/"");
	if(TProp!=NULL){
		ButtonLoadBmpJpg	*b=dynamic_cast<ButtonLoadBmpJpg *>(TProp);
		if(b!=NULL){
			CmdLoadBmpJpgPacket	Cmd;
			Cmd.FileName=ImgFileName;
			b->TransmitDirectly(&Cmd);
		}
	}
	if(GetLayersBase()->LoadPixWithAlgorithm(&FL)==false){
		return;
	}

	ShowAreaGrid();
}
//=====================================================================================
GUICmdSendAddManualTunnelCrack::GUICmdSendAddManualTunnelCrack(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAddManualTunnelCrack::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	if(::Load(f,SelectedLibID)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualTunnelCrack::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	if(::Save(f,SelectedLibID)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualTunnelCrack::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	TunnelCrackBase *BBase=(TunnelCrackBase *)GetLayersBase()->GetAlgorithmBase(/**/"Customized",/**/"TunnelCrack");
	if(BBase!=NULL){
		CmdAddTunnelCrackItemPacket	Cmd;
		Cmd.Area			=Area;
		Cmd.LayerList		=LayerList;
		Cmd.LocalPage		=localPage;
		Cmd.SelectedLibID	=SelectedLibID;
		BBase->TransmitDirectly(&Cmd);
	}

	SendAck(localPage);
}

//=====================================================================================

GUICmdReqTunnelCrackList::GUICmdReqTunnelCrackList(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqTunnelCrackList::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqTunnelCrackList::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqTunnelCrackList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendTunnelCrackList	*SendBack=GetSendBack(GUICmdSendTunnelCrackList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	SendBack->MakeData(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendTunnelCrackList::GUICmdSendTunnelCrackList(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendTunnelCrackList::Load(QIODevice *f)
{
	TunnelCrackInfo.Load(f);
	return true;
}
bool	GUICmdSendTunnelCrackList::Save(QIODevice *f)
{
	TunnelCrackInfo.Save(f);
	return true;
}

void	GUICmdSendTunnelCrackList::MakeData(int localPage)
{
	TunnelCrackBase *BBase=(TunnelCrackBase *)GetLayersBase()->GetAlgorithmBase(/**/"Customized",/**/"TunnelCrack");
	TunnelCrackInPage *P=(TunnelCrackInPage *)BBase->GetPageData(localPage);
	if(P==NULL){
		return;
	}
	CmdTunnelCrackInfoPacket	Cmd;
	Cmd.Point=&TunnelCrackInfo;
	P->TransmitDirectly(&Cmd);
}
void	GUICmdSendTunnelCrackList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

