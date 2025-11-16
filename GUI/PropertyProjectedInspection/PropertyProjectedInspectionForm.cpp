#include "EditLibraryDialogResource.h"
#include "PropertyProjectedInspectionForm.h"
#include "ui_PropertyProjectedInspectionForm.h"
#include "EditLibraryDialog.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XGeneralFunc.h"
#include "XPropertyProjectedInspectionPacket.h"
#include "ManualInputProjectedInspectionDialog.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


PropertyProjectedInspectionForm::PropertyProjectedInspectionForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyProjectedInspectionForm)
{
    ui->setupUi(this);

	LibFolderID =-1;
	ProjectedInspectionBase	*BBase=GetProjectedInspectionBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetGeneratedLibList	->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList	->setColumnWidth (1, 80);	

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempProjectedInspectionLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}

	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyProjectedInspectionForm::~PropertyProjectedInspectionForm()
{
    delete ui;
}

ProjectedInspectionBase	*PropertyProjectedInspectionForm::GetProjectedInspectionBase(void)
{
	return (ProjectedInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ProjectedInspection");
}

void PropertyProjectedInspectionForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &Index)
{
	on_pushButtonSetFrom_clicked();
}
void PropertyProjectedInspectionForm::SetLayersFromLib(IntList &LayerList)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ProjectedInspectionImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->SetActiveLayerList(LayerList);
		}
	}
}
void PropertyProjectedInspectionForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBack_clicked();
}

void PropertyProjectedInspectionForm::on_pushButtonSetFrom_clicked()
{
	int	r=ui->tableWidgetLibList->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==a->GetLibID())
			return;
	}
	SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	ShowSelectedLibList();
}

void PropertyProjectedInspectionForm::on_pushButtonGetBack_clicked()
{
	int	r=ui->tableWidgetGeneratedLibList->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		SelectedLibList.RemoveList(a);
		delete	a;
		ShowSelectedLibList();
	}
}

void PropertyProjectedInspectionForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyProjectedInspectionForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void PropertyProjectedInspectionForm::on_tableWidgetAllItems_clicked(const QModelIndex &index)
{

}

void PropertyProjectedInspectionForm::on_tableWidgetAllItems_doubleClicked(const QModelIndex &index)
{

}

void PropertyProjectedInspectionForm::on_pushButtonEditLibrary_clicked()
{
	EditLibraryDialog	D(GetLayersBase(),this);
	D.exec();
}

void PropertyProjectedInspectionForm::on_pushButtonEditLibFolder_clicked()
{
	ProjectedInspectionBase	*BBase=GetProjectedInspectionBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}
void	PropertyProjectedInspectionForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void	PropertyProjectedInspectionForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	ProjectedInspectionBase	*BBase=GetProjectedInspectionBase();
	if(BBase!=NULL){
		CmdGetProjectedInspectionLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui->tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui->tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui->tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}
struct	AlgorithmLibraryListClass
{
	AlgorithmLibraryList	*a;
};

void	PropertyProjectedInspectionForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	ProjectedInspectionBase	*BBase=GetProjectedInspectionBase();
	if(BBase!=NULL){
		CmdCreateTempProjectedInspectionLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadProjectedInspectionLibraryPacket	Packet(GetLayersBase());
			Packet.Point=SLib;
			BBase->TransmitDirectly(&Packet);
		}
		for(;;){
			AlgorithmLibraryList *a=SelectedLibList.GetFirst();
			if(a==NULL)
				break;
			SelectedLibList.RemoveList(a);
		}
		for(int i=0;i<row;i++){
			SelectedLibList.AppendList(DDim[i].a);
		}
	}

	int	row=0;
	ui->tableWidgetGeneratedLibList->setRowCount(SelectedLibList.GetNumber());
	for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
		QTableWidgetItem *W;
		W=ui->tableWidgetGeneratedLibList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetGeneratedLibList->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->GetLibID()));
		W=ui->tableWidgetGeneratedLibList->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetGeneratedLibList->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(a->GetLibName());
	}
}
void PropertyProjectedInspectionForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadProjectedInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		ProjectedInspectionBase	*BBase=GetProjectedInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SetLayersFromLib(TempLib->GetAdaptedPickLayers());
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	, /**/"Library error"
											, /**/"Not loaded this library record");
			}
		}
	}
}

void PropertyProjectedInspectionForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
    int	r=Index.row();
    AlgorithmLibraryList	*a=LibList.GetItem(r);
    if(a!=NULL){
        TempLib->SetLibID(a->GetLibID());
        CmdLoadProjectedInspectionLibraryPacket	Packet(GetLayersBase());
        Packet.Point=TempLib;
        ProjectedInspectionBase	*BBase=GetProjectedInspectionBase();
        if(BBase!=NULL){
            BBase->TransmitDirectly(&Packet);
            if(Packet.Success==true){
                SetLayersFromLib(TempLib->GetAdaptedPickLayers());
                ShowLibrary(*TempLib);
            }
            else{
                QMessageBox::critical(NULL	, /**/"Library error"
                                            , /**/"Not loaded this library record");
            }
        }
    }
}
void	PropertyProjectedInspectionForm::TransmitDirectly(GUIDirectMessage *packet)
{
	ProjectedInspectionBase	*BBase=GetProjectedInspectionBase();

	CmdProjectedInspectionExecuteDrawEnd	*BlockDEnd=dynamic_cast<CmdProjectedInspectionExecuteDrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		ManualInputProjectedInspectionDialog	D(GetLayersBase(),NULL);
		if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual ProjectedInspection");

			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=BlockDEnd->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdSendAddManualProjectedInspection	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
					Cmd.Area=A;
					Cmd.LibID	=D.BItem->GetLibID();
					Cmd.LayerList=BlockDEnd->LayerList;
					Cmd.SendOnly(GlobalPage,0);
				}
			}
		//ShowDotMatchingInfoList();
		}
	}
}
void	PropertyProjectedInspectionForm::BuildForShow(void)
{
}

void	PropertyProjectedInspectionForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
}
void	PropertyProjectedInspectionForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
}
void PropertyProjectedInspectionForm::on_ButtonPickupTest_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm("Pickup Test",7);

	GetLibraryFromWindow(*TempLib);

	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ProjectedInspectionImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdPickupTestList	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibPoint	=TempLib;
		Cmd.LayerList	=LayerList;
		Cmd.SendOnly(GlobalPage,0);
	}

	GetLayersBase()->CloseProcessingForm();
}

void PropertyProjectedInspectionForm::on_ButtonGenerateLibs_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Generate Blocks automatically");

	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ProjectedInspectionImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}
	
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Generating items",false,SelectedLibList.GetCount()*(7+7));
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdGenerateProjectedInspection	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibList		=SelectedLibList.GetIDList();
		Cmd.LayerList	=LayerList;
		Cmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}

void PropertyProjectedInspectionForm::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.Send(NULL,GlobalPage,0);
	}
}
