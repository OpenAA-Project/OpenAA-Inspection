#include "PropertyNickInspectionResource.h"
#include "EditNickInspectionDialog.h"
#include "ui_EditNickInspectionDialog.h"
#include "XRememberer.h"
#include "XLibraryType.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditNickInspectionDialog::EditNickInspectionDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::EditNickInspectionDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	NickInspectionBase	*BBase=GetNickInspectionBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempNickInspectionLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui->tableWidgetLibList->setColumnWidth ( 0, 32);
	ui->tableWidgetLibList->setColumnWidth ( 1, 160);

	for(int Layer=0;Layer<GetLayerNumb(0);Layer++){
		QToolButton	*LayerButton=new QToolButton(ui->framePickLayer);
		LayerButton->move(Layer*90,0);
		LayerButton->resize(88,20);
		LayerButton->setCheckable(true);
		LayerButton->setAutoExclusive(true);
		LayerButton->setText(GetParamGlobal()->GetLayerName(Layer));
		QPalette	PL=LayerButton->palette();
		PL.setColor(QPalette::Button,GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LayerButton->setPalette(PL);
		LayerPickButtons.append(LayerButton);
	}
	for(int Layer=0;Layer<GetLayerNumb(0);Layer++){
		QToolButton	*LayerButton=new QToolButton(ui->frameGenLayer);
		LayerButton->move(Layer*90,0);
		LayerButton->resize(88,20);
		LayerButton->setCheckable(true);
		LayerButton->setAutoExclusive(true);
		LayerButton->setText(GetParamGlobal()->GetLayerName(Layer));
		QPalette	PL=LayerButton->palette();
		PL.setColor(QPalette::Button,GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LayerButton->setPalette(PL);
		LayerGenButtons.append(LayerButton);
	}

	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);

	pLibFolderSelect=new GeneralLibFolderForm(-1,GetLayersBase(),ui->frameLibFolderSelect);
	connect(pLibFolderSelect,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolderSelect(int,QString)));
	ui->tableWidgetLibListSelect->setColumnWidth (0, 40);
	ui->tableWidgetLibListSelect->setColumnWidth (1, 150);
	ui->tableWidgetSelected->setColumnWidth (0, 130);
	ui->tableWidgetSelected->setColumnWidth (1, 50);
	ui->tableWidgetSelected->setColumnWidth (2, 130);
	SetLibTypeInComboBox();
	ShowLibraries();

	InstallOperationLog(this);
}

EditNickInspectionDialog::~EditNickInspectionDialog()
{
    delete ui;
}
NickInspectionBase	*EditNickInspectionDialog::GetNickInspectionBase(void)
{
	return (NickInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"NickInspection");
}
void	EditNickInspectionDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	NickInspectionBase	*BBase=GetNickInspectionBase();
	if(BBase!=NULL){
		CmdGetNickInspectionLibraryListPacket	Packet(GetLayersBase());
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
void	EditNickInspectionDialog::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}
void	EditNickInspectionDialog::SetLibTypeInComboBox(void)
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
void	EditNickInspectionDialog::SlotSelectLibFolderSelect(int libFolderID ,QString FolderName)
{
	CurrentLibFolderID=libFolderID;

	NickInspectionBase	*BBase=GetNickInspectionBase();
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
void EditNickInspectionDialog::ShowLibraries(void)
{
	ui->tableWidgetSelected->setRowCount(Libraries.GetCount());
	int	row=0;
	for(AlgorithmLibraryList *a=Libraries.GetFirst();a!=NULL;a=a->GetNext(),row++){
		LibraryTypeList	*LType=GetLayersBase()->GetInstalledLibType()->FindLibraryType(a->GetLibType());
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
			::SetDataToTable(ui->tableWidgetSelected,0,row ,LangSolver.GetString(EditNickInspectionDialog_LS,LID_0)/*"Not registered"*/);
		}
		::SetDataToTable(ui->tableWidgetSelected,1,row ,QString::number(a->GetLibID()));
		::SetDataToTable(ui->tableWidgetSelected,2,row ,a->GetLibName());
	}
}

void EditNickInspectionDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadNickInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		NickInspectionBase	*BBase=GetNickInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui->ButtonLibSave	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL	,/**/"Library error"
											,/**/"Not loaded this library record");
			}
		}
	}
}

void EditNickInspectionDialog::on_comboBoxLibTypeSelect_currentIndexChanged(int index)
{
	int	Index=ui->comboBoxLibTypeSelect->currentIndex();
	if(Index<0)
		return;
	
	QVariant V=ui->comboBoxLibTypeSelect->itemData (Index);

	//LibraryTypeList *L=GetLayersBase()->GetLibType()->GetItem(Index);
	//if(L==NULL)
	//	return;
	//CurrentLibType=L->LibType;
	CurrentLibType=V.toInt();
	ShowFolder(CurrentLibType);
	LibIDListSelect.RemoveAll();
	ui->tableWidgetLibListSelect->setRowCount(0);
}

void EditNickInspectionDialog::on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelectButton_clicked();
}

void EditNickInspectionDialog::on_pushButtonSelectButton_clicked()
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

void EditNickInspectionDialog::on_tableWidgetSelected_doubleClicked(const QModelIndex &index)
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
void	EditNickInspectionDialog::ShowFolder(int LibType)
{
	pLibFolderSelect->SetLibType(LibType);
}
void EditNickInspectionDialog::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearNickInspectionLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	NickInspectionBase	*BBase=GetNickInspectionBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditNickInspectionDialog::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=QString(/**/"Delete OK?");
	int	ret=QMessageBox::question(NULL, /**/"Choose"
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteNickInspectionLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		NickInspectionBase	*BBase=GetNickInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditNickInspectionDialog::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertNickInspectionLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	NickInspectionBase	*BBase=GetNickInspectionBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditNickInspectionDialog::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertNickInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		NickInspectionBase	*BBase=GetNickInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateNickInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		NickInspectionBase	*BBase=GetNickInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditNickInspectionDialog::on_pushButtonClose_clicked()
{
	close();
}

void	EditNickInspectionDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	NickInspectionLibrary	*ALib=dynamic_cast<NickInspectionLibrary *>(data.GetLibrary());
	ui->spinBoxLimitSize			->setValue	(ALib->LimitSize	);
	ui->spinBoxNGPercentage			->setValue	(ALib->NGPercentage);
	ui->spinBoxRefBrightness		->setValue	(ALib->RefBrightness);
	ui->checkBoxEnableWhite			->setChecked(ALib->EnableWhite);

	for(IntClass *a=data.GetAdaptedPickLayers().GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<GetLayerNumb(0)){
			LayerPickButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayerNumb(0);Layer++){
		bool	Found=false;
		for(IntClass *a=data.GetAdaptedPickLayers().GetFirst();a!=NULL;a=a->GetNext()){
			if(Layer==a->GetValue()){
				Found=true;
				break;
			}
		}
		if(Found==false){
			LayerPickButtons[Layer]->setChecked(false);
		}
	}
	for(IntClass *a=data.GetAdaptedGenLayers().GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<GetLayerNumb(0)){
			LayerGenButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayerNumb(0);Layer++){
		bool	Found=false;
		for(IntClass *a=data.GetAdaptedGenLayers().GetFirst();a!=NULL;a=a->GetNext()){
			if(Layer==a->GetValue()){
				Found=true;
				break;
			}
		}
		if(Found==false){
			LayerGenButtons[Layer]->setChecked(false);
		}
	}
	Libraries	=ALib->LibList;
	ShowLibraries();
}

void	EditNickInspectionDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	NickInspectionLibrary	*ALib=dynamic_cast<NickInspectionLibrary *>(data.GetLibrary());
	ALib->LimitSize		=ui->spinBoxLimitSize		->value	();
	ALib->NGPercentage	=ui->spinBoxNGPercentage	->value	();
	ALib->RefBrightness	=ui->spinBoxRefBrightness	->value	();
	ALib->EnableWhite	=ui->checkBoxEnableWhite	->isChecked();

	IntList	LayersPickList;
	for(int Layer=0;Layer<LayerPickButtons.count();Layer++){
		if(LayerPickButtons[Layer]->isChecked()==true){
			LayersPickList.Add(Layer);
		}
	}
	data.SetAdaptedPickLayers(LayersPickList);

	IntList	LayersGenList;
	for(int Layer=0;Layer<LayerGenButtons.count();Layer++){
		if(LayerGenButtons[Layer]->isChecked()==true){
			LayersGenList.Add(Layer);
		}
	}
	data.SetAdaptedGenLayers(LayersGenList);
	ALib->LibList	= Libraries;
}
