#include "PropertyDXFOperationResource.h"
#include "AllocationLibByColorDialog.h"
#include "ui_AllocationLibByColorDialog.h"
#include "XLibraryType.h"
#include "XDataInLayer.h"
#include "XRememberer.h"
#include "XPropertyDXFOperationPacket.h"
#include <QColorDialog>
#include "XGeneralDialog.h"
#include "PropertyDXFOperationForm.h"

extern	const	char	*AlgoRoot;
extern	const	char	*AlgoName;
extern	const	char	*sRoot;
extern	const	char	*sName;

ColotButtonInList::ColotButtonInList(int row ,QWidget *parent)
	:mtPushButtonColored(parent)
{	
	Row=row;
	connect(this,SIGNAL(SignalClicked()),this,SLOT(SlotClicked()));
}
void	ColotButtonInList::SlotClicked()
{
	emit	SignalClicked(Row);
}

AllocationLibByColorDialog::AllocationLibByColorDialog(LayersBase *base, PropertyDXFOperationForm *p,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
	,AllocationLibByColorContainerInst(DXFCommonDataID)
	,ui(new Ui::AllocationLibByColorDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	Parent=p;
	pLibFolderSelect=new GeneralLibFolderForm(-1,GetLayersBase(),ui->frameLibFolderSelect);
	connect(pLibFolderSelect,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolderSelect(int,QString)));
	ui->tableWidget->setColumnWidth (0, 50);
	ui->tableWidget->setColumnWidth (1, 110);
	ui->tableWidgetLibListSelect->setColumnWidth (0, 40);
	ui->tableWidgetLibListSelect->setColumnWidth (1, 150);
	ui->tableWidgetSelected->setColumnWidth (0, 130);
	ui->tableWidgetSelected->setColumnWidth (1, 50);
	ui->tableWidgetSelected->setColumnWidth (2, 130);
	SetLibTypeInComboBox();

	DXFOperationBase	*Base=GetDXFOperationBase();
	if(Base==NULL)
		return;
	CmdLoadAllocationLibByColor	Cmd(GetLayersBase());
	Base->TransmitDirectly(&Cmd);

	int	LevelID=GetLayersBase()->GetThresholdLevelID();
	ReqAllocationLibByColorContainer(LevelID);
	ShowAllocationLibByColorContainerList();

	QString	DLLRoot,DLLName;
	Base->GetAlgorithmRootName(DLLRoot,DLLName);
	pLibFolderSelect->SetCurrentLibFolder(ControlRememberer::GetInt(DLLName+objectName()+pLibFolderSelect->objectName(),0));

	InstallOperationLog(this);
}

AllocationLibByColorDialog::~AllocationLibByColorDialog()
{
    delete ui;
}
DXFOperationBase	*AllocationLibByColorDialog::GetDXFOperationBase(void)
{
	DXFOperationBase	*Base=(DXFOperationBase *)GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	return Base;
}
void	AllocationLibByColorDialog::SetLibTypeInComboBox(void)
{
	ui->comboBoxLibTypeSelect->clear();
	for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
		if(ABase!=NULL){
			ui->comboBoxLibTypeSelect->addItem(ABase->GetNameByCurrentLanguage()
												,(int)L->GetLibType());
		}
	}
}
void	AllocationLibByColorDialog::ShowFolder(int LibType)
{
	pLibFolderSelect->SetLibType(LibType);
}
void	AllocationLibByColorDialog::SlotSelectLibFolderSelect(int libFolderID ,QString FolderName)
{
	CurrentLibFolderID=libFolderID;

	DXFOperationBase	*BBase=GetDXFOperationBase();
	QString	DLLRoot,DLLName;
	BBase->GetAlgorithmRootName(DLLRoot,DLLName);
	ControlRememberer::SetValue(DLLName+objectName()+pLibFolderSelect->objectName() ,CurrentLibFolderID);

	ui->tableWidgetLibListSelect->setRowCount(0);
	AlgorithmLibraryContainerForEnum		LibList(GetLayersBase());
	LibIDListSelect.RemoveAll();
	LibList.EnumLibrary(GetLayersBase()->GetDatabase(),CurrentLibType,CurrentLibFolderID ,LibIDListSelect);

	int	row=0;
	ui->tableWidgetLibListSelect->setRowCount(LibIDListSelect.GetNumber());
	for(AlgorithmLibraryList *a=LibIDListSelect.GetFirst();a!=NULL;a=a->GetNext(),row++){
		::SetDataToTable(ui->tableWidgetLibListSelect,0,row ,QString::number(a->GetLibID()));
		::SetDataToTable(ui->tableWidgetLibListSelect,1,row ,a->GetLibName());
	}
}
void	AllocationLibByColorDialog::ShowAllocationLibByColorContainerList(void)
{
	ui->tableWidget->setRowCount(AllocationLibByColorContainerInst.GetCount());
	int	row=0;
	for(AllocationLibByColor *a=AllocationLibByColorContainerInst.GetFirst();a!=NULL;a=a->GetNext(),row++){
		int	col=0;
		QTableWidgetItem *L=ui->tableWidget->item ( row, col);
		if(L==NULL || dynamic_cast<ColotButtonInList *>(L)==NULL){
			ColotButtonInList	*b=new ColotButtonInList(row);
			b->setColor(a->GetColor());
			ui->tableWidget->setCellWidget(row,col,b);
			connect(b,SIGNAL(SignalClicked(int)),this,SLOT(SignalClickedColorList(int)));
		}
		else{
			ColotButtonInList	*b=dynamic_cast<ColotButtonInList *>(L);
			b->setColor(a->GetColor());
		}
	}
}
void	AllocationLibByColorDialog::SignalClickedColorList(int row)
{
	AllocationLibByColor *a=AllocationLibByColorContainerInst.GetItem(row);
	if(a!=NULL){
		QColor Col=QColorDialog::getColor ( a->GetColor(), NULL, LangSolver.GetString(AllocationLibByColorDialog_LS,LID_0)/*"DXF color"*/);
		if(Col.isValid()==true){
			a->Color=Col;
		}
		int	col=0;
		QTableWidgetItem *L=ui->tableWidget->item ( row, col);
		if(L==NULL || dynamic_cast<mtPushButtonColored *>(L)==NULL){
			ColotButtonInList	*b=new ColotButtonInList(row);
			b->setColor(a->GetColor());
			ui->tableWidget->setCellWidget(row,col,b);
			connect(b,SIGNAL(SignalClicked(int)),this,SLOT(SignalClickedColorList(int)));
		}
		else{
			ColotButtonInList	*b=dynamic_cast<ColotButtonInList *>(L);
			b->setColor(a->GetColor());
		}
	}
}
void AllocationLibByColorDialog::on_tableWidget_clicked(const QModelIndex &index)
{
	int	cRow=ui->tableWidget->currentRow();
	AllocationLibByColor *a=AllocationLibByColorContainerInst.GetItem(cRow);
	if(a!=NULL){
		Libraries=a->LibList;
		ShowLibraries();
	}
}

void AllocationLibByColorDialog::on_pushButtonAddColor_clicked()
{
	AllocationLibByColor	*a=new AllocationLibByColor();
	if(a!=NULL){
		int	row=ui->tableWidget->rowCount();
		ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

		QColor Col=QColorDialog::getColor ( a->GetColor(), NULL, LangSolver.GetString(AllocationLibByColorDialog_LS,LID_1)/*"DXF color"*/);
		if(Col.isValid()==true){
			a->Color=Col;
		}
		int	col=0;
		QTableWidgetItem *L=ui->tableWidget->item ( row, col);
		if(L==NULL || dynamic_cast<mtPushButtonColored *>(L)==NULL){
			ColotButtonInList	*b=new ColotButtonInList(row);
			b->setColor(a->GetColor());
			ui->tableWidget->setCellWidget(row,col,b);
			connect(b,SIGNAL(SignalClicked(int)),this,SLOT(SignalClickedColorList(int)));
		}
		else{
			ColotButtonInList	*b=dynamic_cast<ColotButtonInList *>(L);
			b->setColor(a->GetColor());
		}
		AllocationLibByColorContainerInst.AppendList(a);
	}
}

void AllocationLibByColorDialog::on_pushButtonSubColor_clicked()
{
	int	cRow=ui->tableWidget->currentRow();
	AllocationLibByColor *a=AllocationLibByColorContainerInst.GetItem(cRow);
	if(a!=NULL){
		AllocationLibByColorContainerInst.RemoveList(a);
		delete	a;

		ShowAllocationLibByColorContainerList();
	}
}

void AllocationLibByColorDialog::on_comboBoxLibTypeSelect_currentIndexChanged(const QString &arg1)
{
	int	Index=ui->comboBoxLibTypeSelect->currentIndex();
	if(Index<0)
		return;
	
	QVariant V=ui->comboBoxLibTypeSelect->itemData (Index);

	CurrentLibType=V.toInt();
	ShowFolder(CurrentLibType);
	LibIDListSelect.RemoveAll();
	ui->tableWidgetLibListSelect->setRowCount(0);
}

void AllocationLibByColorDialog::on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelectButton_clicked();
}

void AllocationLibByColorDialog::on_pushButtonSelectButton_clicked()
{
	int	r=ui->tableWidgetLibListSelect->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=LibIDListSelect[r];
	if(a==NULL)
		return;
	AlgorithmLibraryList	*d=new AlgorithmLibraryList(*a);
	Libraries.AppendList(d);

	ShowLibraries();
}

void AllocationLibByColorDialog::on_tableWidgetSelected_doubleClicked(const QModelIndex &index)
{
	int	r=ui->tableWidgetSelected->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*d=Libraries[r];
	if(d!=NULL){
		Libraries.RemoveList(d);
		delete	d;
		ShowLibraries();
	}
}

void AllocationLibByColorDialog::on_pushButtonUpdate_clicked()
{
	int	cRow=ui->tableWidget->currentRow();
	AllocationLibByColor *a=AllocationLibByColorContainerInst.GetItem(cRow);
	if(a!=NULL){
		a->LibList=Libraries;
	}
}

void AllocationLibByColorDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
void AllocationLibByColorDialog::ShowLibraries(void)
{
	ui->tableWidgetSelected->setRowCount(Libraries.GetCount());
	int	row=0;
	for(AlgorithmLibraryList *a=Libraries.GetFirst();a!=NULL;a=a->GetNext(),row++){
		LibraryTypeList	*LType=GetLayersBase()->GetLibType()->FindLibraryType(a->GetLibType());
		if(LType!=NULL){
			AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(LType->GetLibType());
			if(ABase!=NULL){
				::SetDataToTable(ui->tableWidgetSelected,0,row ,ABase->GetNameByCurrentLanguage());
			}
			else{
				::SetDataToTable(ui->tableWidgetSelected,0,row ,LType->GetLibName());
			}
		}
		else{
			::SetDataToTable(ui->tableWidgetSelected,0,row ,LangSolver.GetString(AllocationLibByColorDialog_LS,LID_2)/*"Not registered"*/);
		}
		::SetDataToTable(ui->tableWidgetSelected,1,row ,QString::number(a->GetLibID()));
		::SetDataToTable(ui->tableWidgetSelected,2,row ,a->GetLibName());
	}
}

void AllocationLibByColorDialog::on_pushButtonOK_clicked()
{
	DXFOperationBase	*Base=GetDXFOperationBase();
	if(Base==NULL)
		return;

	int	GlobalPage=0;

	GUICmdSetAllocationLibByColor	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	RCmd.LevelID=GetLayersBase()->GetThresholdLevelID();
	RCmd.AllocationLibByColorContainerInst=AllocationLibByColorContainerInst;
	RCmd.Send(NULL,GlobalPage,0);

    done(true);
}

void AllocationLibByColorDialog::on_pushButtonFromDXFData_clicked()
{
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqColorFromDXF	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdAckColorFromDXF	ACmd(GetLayersBase(),sRoot,sName,globalPage);
		if(RCmd.Send(globalPage,0,ACmd)==true){
			for(AllocationLibByColor *a=ACmd.ColorList.GetFirst();a!=NULL;a=a->GetNext()){
				if(AllocationLibByColorContainerInst.IsExist(a->Color)==false){
					AllocationLibByColorContainerInst.AppendList(new AllocationLibByColor(a->ColorCode,a->Color));
				}
				else{
					AllocationLibByColor	*v=AllocationLibByColorContainerInst.Find(a->Color);
					if(v!=NULL){
						v->ColorCode.Merge(a->ColorCode);
					}
				}
			}
		}
	}
	ShowAllocationLibByColorContainerList();
}
void	AllocationLibByColorDialog::ReqAllocationLibByColorContainer(int LevelID)
{
	CmdReqAllocationLibByColor	RCmd(GetLayersBase());
	RCmd.ThresholdLevelID=LevelID;
	Parent->TransmitDirectly(&RCmd);
	AllocationLibByColorContainerInst=RCmd.Container;
}
