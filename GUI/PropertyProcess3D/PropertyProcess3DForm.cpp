#include "PropertyProcess3DForm.h"
#include "ui_PropertyProcess3DForm.h"
#include "XProcess3D.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "EditProcess3DLibraryDialog.h"
#include "XGeneralFunc.h"
#include "XPropertyProcess3DPacket.h"
#include "XPropertyProcess3DCommon.h"
#include "SelectLibraryDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyProcess3DForm::PropertyProcess3DForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyProcess3DForm)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	Process3DBase	*BBase=GetProcess3DBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui->tableWidget->setColumnWidth (0,48);
	ui->tableWidget->setColumnWidth (1,48);
	ui->tableWidget->setColumnWidth (2,48);
	ui->tableWidget->setColumnWidth (3,120);

}

PropertyProcess3DForm::~PropertyProcess3DForm()
{
    delete ui;
}
Process3DBase	*PropertyProcess3DForm::GetProcess3DBase(void)
{
	return (Process3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Process3D");
}

void PropertyProcess3DForm::on_pushButtonEditLibrary_clicked()
{
	EditProcess3DLibraryDialog	D(GetLayersBase(),this);
	D.exec();
}

void	PropertyProcess3DForm::BuildForShow(void)
{
	ShowList();
}
void PropertyProcess3DForm::ShowList(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	Process3DInfos.RemoveAll();
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendProcess3DInfoList	**BmpReceiver=new GUICmdSendProcess3DInfoList*[GetParamGlobal()->PageNumb];
	GUICmdReqProcess3DInfoList	**BmpRequester=new GUICmdReqProcess3DInfoList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpReceiver[page]	=new GUICmdSendProcess3DInfoList	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[page]	=new GUICmdReqProcess3DInfoList		(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	}
	int row=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		GetLayersBase()->TF_SetCurrentScanPhaseNumber(phase);
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page])==true
			&& BmpReceiver[page]->IsReceived()==true){
				Process3DInfos+=BmpReceiver[page]->Process3DInfos;
			}
		}
	}
	GetLayersBase()->TF_SetCurrentScanPhaseNumber(0);
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	BmpRequester[page];
		delete	BmpReceiver[page];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	row=0;
	int	Numb=Process3DInfos.GetNumber();
	ui->tableWidget->setRowCount(Numb);
	for(Process3DInfoList *L=Process3DInfos.GetFirst();L!=NULL;L=L->GetNext() ,row++){
		SetDataToTable(ui->tableWidget ,0,row,L->GlobalPage);
		SetDataToTable(ui->tableWidget ,1,row,QString::number(L->Layer));
		SetDataToTable(ui->tableWidget ,2,row,QString::number(L->ItemID));
		SetDataToTable(ui->tableWidget ,3,row,L->ItemName);
	}

	ReEntrant=false;
}

void PropertyProcess3DForm::on_tableWidget_clicked(const QModelIndex &index)
{
	Process3DInfoList *L=Process3DInfos.GetItem(index.row());
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(L->GlobalPage);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
									,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"Process3DImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->GlobalPage,L->Layer,L->ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}

void PropertyProcess3DForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{

}
void	PropertyProcess3DForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdProcess3DDrawEnd	*CmdProcess3DDrawEndVar=dynamic_cast<CmdProcess3DDrawEnd *>(packet);
	if(CmdProcess3DDrawEndVar!=NULL){
		SelectLibraryDialog	D(GetLayersBase());
		if(D.exec()==(int)true){
			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual Process3D");

			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(CmdProcess3DDrawEndVar->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=CmdProcess3DDrawEndVar->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdSendAddManualProcess3D	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
					Cmd.Area=A;
					Cmd.ItemName	=D.ItemName;
					Cmd.LibID		=D.SelectedLibID;
					Cmd.Layer		=(CmdProcess3DDrawEndVar->LayerList.GetCount()==0)?0:CmdProcess3DDrawEndVar->LayerList.GetFirst()->GetValue();
					Cmd.SendOnly(GlobalPage,0);
				}
			}
		}
		ShowList();
		
	}
}
