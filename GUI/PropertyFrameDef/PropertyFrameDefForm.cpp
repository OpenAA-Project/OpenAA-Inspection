#include "PropertyFrameDefResource.h"
#include "PropertyFrameDefForm.h"
#include "ui_PropertyFrameDefForm.h"
#include"XPropertyFrameDefPacket.h"
#include "XDisplayImagePacket.h"
#include "InputFrameDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyFrameDefForm::PropertyFrameDefForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base ,parent),
    ui(new Ui::PropertyFrameDefForm)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	ui->tableWidget->setColumnWidth(0,60);
	ui->tableWidget->setColumnWidth(1,60);
	ui->tableWidget->setColumnWidth(2,200);
}

PropertyFrameDefForm::~PropertyFrameDefForm()
{
    delete ui;
}

void	PropertyFrameDefForm::BuildForShow(void)
{
	ShowItemGrid();
}
void	PropertyFrameDefForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqDrawAttrPacket	*CmdReqDrawAttrPacketVar=dynamic_cast<CmdReqDrawAttrPacket *>(packet);
	if(CmdReqDrawAttrPacketVar!=NULL){
		CmdReqDrawAttrPacketVar->Overlapped	= ui->toolButtonOverlap->isChecked();
		return;
	}
	CmdCreateFrameDefManualPacket	*CmdCreateFrameDefManualPacketVer=dynamic_cast<CmdCreateFrameDefManualPacket *>(packet);
	if(CmdCreateFrameDefManualPacketVer!=NULL){
		InputFrameDialog	D(false,GetLayersBase());
		if(D.exec()==(int)true){
			for(int page=0;page<GetPageNumb();page++){
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(pdata->GetPage());
				GUICmdAddFrameAreaManual	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
				Cmd.Area	=CmdCreateFrameDefManualPacketVer->Area;
				Cmd.GroupNumber	=D.GroupNumber;
				Cmd.FrameNumber	=D.FrameNumber;
				Cmd.Original	=D.Origin;
				Cmd.SendOnly(GlobalPage,0);
			}
		}
		ShowItemGrid();
		return;
	}
}

static	int	SortFrameListFunc(const void *a,const void *b)
{
	FrameList	*pa=((FrameList **)a)[0];
	FrameList	*pb=((FrameList **)b)[0];

	if(pa->GroupNumber<pb->GroupNumber)
		return -1;
	if(pa->GroupNumber>pb->GroupNumber)
		return 1;

	if(pa->FrameNumber<pb->FrameNumber)
		return -1;
	if(pa->FrameNumber>pb->FrameNumber)
		return 1;
	return 0;
}

void	PropertyFrameDefForm::ShowItemGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	FrameGrid.RemoveAll();
	int row=0;
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqFrameContainer		RCmd(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdAckFrameContainer		ACmd(GetLayersBase(),sRoot,sName,globalPage);
		if(RCmd.Send(globalPage,0,ACmd)==true
		&& ACmd.IsReceived()==true){
			for(FrameList *s=ACmd.ItemContainer.GetFirst();s!=NULL;s=s->GetNext()){
				bool	Found=false;
				for(FrameList *d=FrameGrid.GetFirst();d!=NULL;d=d->GetNext()){
					if(s->GroupNumber==d->GroupNumber && s->FrameNumber==d->FrameNumber){
						d->Items.Merge(s->Items);
						Found=true;
						break;
					}
				}
				if(Found==false){
					FrameList	*e=new FrameList();
					*e=*s;
					FrameGrid.AppendList(e);
				}
			}
		}
	}
	FrameGrid.Sort(SortFrameListFunc);

	row=0;
	int	Numb=FrameGrid.GetNumber();
	ui->tableWidget->setRowCount(Numb);
	for(FrameList *L=FrameGrid.GetFirst();L!=NULL;L=L->GetNext() ,row++){
		QColor	Col=(L->Original==true)?Qt::green:Qt::white;
		::SetDataToTable(ui->tableWidget ,0,row,QString::number(L->GroupNumber));
		::SetDataToTable(ui->tableWidget ,1,row,QString::number(L->FrameNumber));
		QString	s=QString(/**/"(")
				+ QString::number(L->GlobalX1)+QString(/**/",")+QString::number(L->GlobalY1)
				+ QString(/**/")-(")
				+ QString::number(L->GlobalX2)+QString(/**/",")+QString::number(L->GlobalY2)
				+ QString(/**/")");
		::SetDataToTable(ui->tableWidget ,2,row,s);

		::SetTableColor(ui->tableWidget ,0,row ,Col);
		::SetTableColor(ui->tableWidget ,1,row ,Col);
		::SetTableColor(ui->tableWidget ,2,row ,Col);
	}

	ReEntrant=false;
}

void PropertyFrameDefForm::on_tableWidget_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	FrameList *L=FrameGrid[Row];
	if(L==NULL || L->Items.GetCount()==0)
		return;
	int	Page=L->Items.GetFirst()->Page;
	DataInPage	*P=GetLayersBase()->GetPageData(Page);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->GlobalX1,L->GlobalY1
									,L->GlobalX2,L->GlobalY2);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"FrameDefImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),Page,0,L->Items.GetFirst()->ID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}

void PropertyFrameDefForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	FrameList *L=FrameGrid[Row];
	if(L==NULL)
		return;
			
	InputFrameDialog	D(true,GetLayersBase());
	D.Initial(L->GroupNumber,L->FrameNumber,L->Original);
	if(D.exec()==(int)true){
		for(ListPageID *p=L->Items.GetFirst();p!=NULL;p=p->GetNext()){
			int	globalPage=p->Page;	
			GUICmdSetItemNumber	RCmd(GetLayersBase(),sRoot,sName,globalPage);
			RCmd.ItemID	=p->ID;
			RCmd.GroupNumber	=D.GroupNumber;
			RCmd.FrameNumber	=D.FrameNumber;
			RCmd.Original		=D.Origin;
			RCmd.Send(NULL,globalPage,0);
		}
	}
	ShowItemGrid();
}

void PropertyFrameDefForm::on_toolButtonOverlap_clicked()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"FrameDefImagePanel" ,/**/"");
	if(GProp!=NULL)
		GProp->Repaint();
}
