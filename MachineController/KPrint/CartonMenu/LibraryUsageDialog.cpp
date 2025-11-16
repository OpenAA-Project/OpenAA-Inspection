#include "CartonMenuResource.h"
#include "LibraryUsageDialog.h"
#include "ui_LibraryUsageDialog.h"
#include "LibFolderForm.h"
#include "CartonMenuForm.h"
#include "XLibraryType.h"
#include "XDataInLayer.h"
#include "XAlignmentLarge.h"
#include "XDatabaseLoader.h"

LibraryUsageDialog::LibraryUsageDialog(LayersBase *Base ,CartonMenuForm *p,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),Parent(p),
    ui(new Ui::LibraryUsageDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
    pLibFolderForm=new LibFolderForm(-1,GetLayersBase(),ui->frameLibFolderSelect);
    connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));

	int	SlaveCount=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	if(SlaveCount>=1){
		ui->toolButtonSide1->setVisible(true);
		ui->toolButtonSide1->setChecked(true);
		EachMaster	*m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(0);
		if(m!=NULL){
			ui->toolButtonSide1->setText(m->GetMachineName());
		}
	}
	else
		ui->toolButtonSide1->setVisible(false);

	if(SlaveCount>=2){
		ui->toolButtonSide2->setVisible(true);
		EachMaster	*m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(1);
		if(m!=NULL){
			ui->toolButtonSide2->setText(m->GetMachineName());
		}
	}
	else
		ui->toolButtonSide2->setVisible(false);

	if(SlaveCount>=3){
		ui->toolButtonSide3->setVisible(true);
		EachMaster	*m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(2);
		if(m!=NULL){
			ui->toolButtonSide3->setText(m->GetMachineName());
		}
	}
	else
		ui->toolButtonSide3->setVisible(false);

	if(SlaveCount>=4){
		ui->toolButtonSide4->setVisible(true);
		EachMaster	*m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(3);
		if(m!=NULL){
			ui->toolButtonSide4->setText(m->GetMachineName());
		}
	}
	else
		ui->toolButtonSide4->setVisible(false);


	::SetColumnWidthInTable(ui->tableWidget,0, 90);
	//::SetColumnWidthInTable(ui->tableWidget,1, 45);

	::SetColumnWidthInTable(ui->tableWidgetLibListSelect,0,20);
	::SetColumnWidthInTable(ui->tableWidgetLibListSelect,1,70);

	::SetColumnWidthInTable(ui->tableWidgetLibListUsage,0,40);
	::SetColumnWidthInTable(ui->tableWidgetLibListUsage,1,15);
	::SetColumnWidthInTable(ui->tableWidgetLibListUsage,2,40);

    ui->comboBoxLibTypeSelect->clear();
    for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext()){
       AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
       ui->comboBoxLibTypeSelect->addItem(ABase->GetNameByCurrentLanguage(),(int)L->GetLibType());
    }

	if(SlaveCount>=1){
		on_toolButtonSide1_clicked();
	}
}

LibraryUsageDialog::~LibraryUsageDialog()
{
    delete ui;
}

void LibraryUsageDialog::on_toolButtonSide1_clicked()
{
	ShowList(Parent->Param.UsageTopSide);
}

void LibraryUsageDialog::on_toolButtonSide2_clicked()
{
	ShowList(Parent->Param.UsageBottomSide);
}

void LibraryUsageDialog::on_toolButtonSide3_clicked()
{
	ShowList(Parent->Param.UsageMonoSide);
}

void LibraryUsageDialog::on_toolButtonSide4_clicked()
{
	ShowList(Parent->Param.UsageMonoSide2);
}


void LibraryUsageDialog::ShowList(LibraryUsageContainer &Container)
{
	int	N=Container.GetCount();
	ui->tableWidget->setRowCount(N);
	int	Row=0;
	for(LibraryUsage *L=Container.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		::SetDataToTable(ui->tableWidget, 0, Row, L->UsageName);
		//QString	s=GetLayersBase()->GetLibraryName(L->LibType,L->LibID);
		//::SetDataToTable(ui->tableWidget, 1, Row, s);
	}
}

void LibraryUsageDialog::on_tableWidget_itemSelectionChanged()
{
	LibraryUsageContainer *Container=NULL;
	if(ui->toolButtonSide1->isChecked()==true)
		Container=&Parent->Param.UsageTopSide;
	if(ui->toolButtonSide2->isChecked()==true)
		Container=&Parent->Param.UsageBottomSide;
	if(ui->toolButtonSide3->isChecked()==true)
		Container=&Parent->Param.UsageMonoSide;
	if(ui->toolButtonSide4->isChecked()==true)
		Container=&Parent->Param.UsageMonoSide2;
	if(Container==NULL)
		return;
	LibraryUsage *U=Container->GetItem(ui->tableWidget->currentRow());
	if(U==NULL)
		return;
	//int	ComboRow=0;
	//for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext(),ComboRow++){
	//	if(L->GetLibType()==U->LibType){
	//		ui->comboBoxLibTypeSelect->setCurrentIndex(ComboRow);
	//		on_comboBoxLibTypeSelect_currentIndexChanged(ComboRow);
	//		break;
	//	}
	//}
	if(U->AlignmentPriority==XAlignmentLargeArea::_PriorityGlobal)
		ui->radioButtonPriorityGlobal->setChecked(true);
	else
		ui->radioButtonPriorityMiddle->setChecked(true);

	//int LibFolderID=GetLayersBase()->GetDatabaseLoader()->S_GetLibraryFolderID(GetLayersBase()->GetDatabase(),U->LibType,U->LibID);
	//SlotSelectLibFolder(LibFolderID ,/**/"");

    //int	row=0;
    //for(AlgorithmLibraryList *a=LibIDList.GetFirst();a!=NULL;a=a->GetNext(),row++){
	//	if(a->GetLibID()==U->LibID){
	//		::SetCurrentRow(ui->tableWidgetLibListSelect, row);
	//	}
	//}
	LibIDListUsage=U->LibList;
	ShowUsageLibList();

	ui->lineEditUsageName->setText(U->UsageName);
	ui->checkBoxDefault	->setChecked(U->DefaultPushed);
}

void    LibraryUsageDialog::ShowUsageLibList(void)
{
	ui->tableWidgetLibListUsage->setRowCount(LibIDListUsage.GetCount());
	int	Row=0;
	for(AlgorithmLibraryList *L=LibIDListUsage.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		QString	LibTypeName=GetLayersBase()->GetLibTypeName(L->GetLibType());
		::SetDataToTable(ui->tableWidgetLibListUsage, 0, Row, LibTypeName);

		::SetDataToTable(ui->tableWidgetLibListUsage, 1, Row, QString::number(L->GetLibID()));
		QString	s=GetLayersBase()->GetLibraryName(L->GetLibType(),L->GetLibID());
		::SetDataToTable(ui->tableWidgetLibListUsage, 2, Row, s);
	}
}

void LibraryUsageDialog::on_comboBoxLibTypeSelect_currentIndexChanged(int index)
{
    int	Index=ui->comboBoxLibTypeSelect->currentIndex();
    LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetItem(Index);
    if(L==NULL){
        return;
	}
	if(pLibFolderForm!=NULL){
		pLibFolderForm->SetLibType(L->GetLibType());
	}
}

void	LibraryUsageDialog::SlotSelectLibFolder(int _LibFolderID ,QString FolderName)
{
    int	LibFolderID=_LibFolderID;

    int	Index=ui->comboBoxLibTypeSelect->currentIndex();
    LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetItem(Index);
    if(L==NULL)
        return;

    ui->tableWidgetLibListSelect->setRowCount(0);
    AlgorithmLibraryContainerForEnum		LibList(GetLayersBase());
    LibIDList.RemoveAll();
    LibList.EnumLibrary(GetLayersBase()->GetDatabase(),L->GetLibType(),LibFolderID ,LibIDList);

    int	row=0;
    ui->tableWidgetLibListSelect->setRowCount(LibIDList.GetNumber());
    for(AlgorithmLibraryList *a=LibIDList.GetFirst();a!=NULL;a=a->GetNext(),row++){
        QTableWidgetItem *W;
        W=ui->tableWidgetLibListSelect->item ( row, 0);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetLibListSelect->setItem ( row, 0,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(QString::number(a->GetLibID()));
        W=ui->tableWidgetLibListSelect->item ( row, 1);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetLibListSelect->setItem ( row, 1,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(a->GetLibName());
    }
}

void LibraryUsageDialog::on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index)
{

}

void LibraryUsageDialog::on_pushButtonUpdate_clicked()
{
	LibraryUsageContainer *Container=NULL;
	if(ui->toolButtonSide1->isChecked()==true)
		Container=&Parent->Param.UsageTopSide;
	if(ui->toolButtonSide2->isChecked()==true)
		Container=&Parent->Param.UsageBottomSide;
	if(ui->toolButtonSide3->isChecked()==true)
		Container=&Parent->Param.UsageMonoSide;
	if(ui->toolButtonSide4->isChecked()==true)
		Container=&Parent->Param.UsageMonoSide2;
	if(Container==NULL)
		return;

	int	Row=0;
	for(LibraryUsage *L=Container->GetFirst();L!=NULL;L=L->GetNext(),Row++){
		if(Row==ui->tableWidget->currentRow()){
			L->UsageName=ui->lineEditUsageName->text();
			L->LibList	=LibIDListUsage;
			L->AlignmentPriority=(ui->radioButtonPriorityGlobal->isChecked()==true)?
									 XAlignmentLargeArea::_PriorityGlobal
									:XAlignmentLargeArea::_PriorityMiddle;
			L->DefaultPushed=ui->checkBoxDefault	->isChecked();
			break;
		}
	}
	ShowList(*Container);
}

void LibraryUsageDialog::on_pushButtonAdd_clicked()
{
    int	Index=ui->comboBoxLibTypeSelect->currentIndex();
    LibraryTypeList *LL=GetLayersBase()->GetInstalledLibType()->GetItem(Index);
    if(LL==NULL)
        return;

    AlgorithmLibraryList *a=LibIDList.GetItem(ui->tableWidgetLibListSelect->currentRow());
	if(a==NULL)
		return;

	LibraryUsageContainer *Container=NULL;
	if(ui->toolButtonSide1->isChecked()==true)
		Container=&Parent->Param.UsageTopSide;
	if(ui->toolButtonSide2->isChecked()==true)
		Container=&Parent->Param.UsageBottomSide;
	if(ui->toolButtonSide3->isChecked()==true)
		Container=&Parent->Param.UsageMonoSide;
	if(ui->toolButtonSide4->isChecked()==true)
		Container=&Parent->Param.UsageMonoSide2;
	if(Container==NULL)
		return;
	LibraryUsage	*L=new LibraryUsage();
	L->UsageName=ui->lineEditUsageName->text();
	L->LibList	=LibIDListUsage;
	L->AlignmentPriority=(ui->radioButtonPriorityGlobal->isChecked()==true)?
							 XAlignmentLargeArea::_PriorityGlobal
							:XAlignmentLargeArea::_PriorityMiddle;
	L->DefaultPushed=ui->checkBoxDefault	->isChecked();
	Container->AppendList(L);
	ShowList(*Container);
}

void LibraryUsageDialog::on_pushButtonDelete_clicked()
{
	LibraryUsageContainer *Container=NULL;
	if(ui->toolButtonSide1->isChecked()==true)
		Container=&Parent->Param.UsageTopSide;
	if(ui->toolButtonSide2->isChecked()==true)
		Container=&Parent->Param.UsageBottomSide;
	if(ui->toolButtonSide3->isChecked()==true)
		Container=&Parent->Param.UsageMonoSide;
	if(ui->toolButtonSide4->isChecked()==true)
		Container=&Parent->Param.UsageMonoSide2;
	if(Container==NULL)
		return;

	int	Row=0;
	for(LibraryUsage *L=Container->GetFirst();L!=NULL;L=L->GetNext(),Row++){
		if(Row==ui->tableWidget->currentRow()){
			Container->RemoveList(L);
			delete	L;
			break;
		}
	}
	ShowList(*Container);
}

void LibraryUsageDialog::on_pushButtonCancel_clicked()
{
	close();
}

void LibraryUsageDialog::on_pushButtonPickup_clicked()
{
	int	CRow=ui->tableWidgetLibListSelect->currentRow();
	AlgorithmLibraryList *a=LibIDList.GetItem(CRow);
	if(a!=NULL){
		AlgorithmLibraryList	*b=new AlgorithmLibraryList(*a);
		LibIDListUsage.AppendList(b);
	}
	ShowUsageLibList();
}


void LibraryUsageDialog::on_pushButtonPushBack_clicked()
{
	int	CRow=ui->tableWidgetLibListUsage->currentRow();
	AlgorithmLibraryList *a=LibIDListUsage.GetItem(CRow);
	if(a!=NULL){
		LibIDListUsage.RemoveList(a);
	}
	ShowUsageLibList();
}

