#include "CreateTunnelFormResource.h"
#include "CreateTunnelForm.h"
#include "EditTunnelCrackLibrary.h"
#include "XGeneralDialog.h"

CreateTunnelForm::CreateTunnelForm(LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	LibFolderID =-1;
	TunnelCrackBase	*BBase=GetTunnelCrackBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempTunnelCrackLibraryPacket	Packet;
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
}

CreateTunnelForm::~CreateTunnelForm()
{
	if(TempLib!=NULL){
		delete	TempLib;
		TempLib=NULL;
	}
}

TunnelCrackBase	*CreateTunnelForm::GetTunnelCrackBase(void)
{
	return (TunnelCrackBase *)GetLayersBase()->GetAlgorithmBase(/**/"Customized",/**/"TunnelCrack");
}

void	CreateTunnelForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	TunnelCrackBase	*BBase=GetTunnelCrackBase();
	if(BBase!=NULL){
		CmdGetTunnelCrackLibraryListPacket	Packet;
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui.tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui.tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui.tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}

void CreateTunnelForm::on_pushButtonCancel_clicked()
{
	done(false);
}

void CreateTunnelForm::on_pushButtonEditLibrary_clicked()
{
	EditTunnelCrackLibrary	D(GetLayersBase(),this);
	D.exec();
}

void CreateTunnelForm::on_ButtonOK_clicked()
{
	int	r=ui.tableWidgetLibList->currentRow();
	if(r<0){
		return;
	}
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadTunnelCrackLibraryPacket	Packet;
		Packet.Point=TempLib;
		TunnelCrackBase	*BBase=GetTunnelCrackBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SelectedLibID=TempLib->GetLibID();
				done(true);
			}
		}
	}
}