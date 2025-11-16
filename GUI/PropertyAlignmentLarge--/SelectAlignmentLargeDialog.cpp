#include "SelectAlignmentLargeDialog.h"
#include "ui_SelectAlignmentLargeDialog.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

SelectAlignmentLargeDialog::SelectAlignmentLargeDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SelectAlignmentLargeDialog)
{
    ui->setupUi(this);

	//LangSolver.SetUI(this);
	SelectedLibID=-1;
	AlignmentLargeLibID	 =-1;

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentLarge");
	int	LibType=-1;
	if(Ab!=NULL){
		CmdCreateTempAlignmentLargeLibraryPacket	LibPacket(GetLayersBase());
		Ab->TransmitDirectly(&LibPacket);
		TempLib=LibPacket.Point;
		LibType=Ab->GetLibType();
	}
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
	
	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetLibList->setRowCount(0);
	ui->ButtonOK->setEnabled(false);

	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		QToolButton	*LayerButton=new QToolButton(ui->frameGenLayer);
		LayerButton->move(Layer*90,0);
		LayerButton->resize(88,20);
		LayerButton->setCheckable(true);
		LayerButton->setAutoExclusive(false);
		LayerButton->setText(GetParamGlobal()->GetLayerName(Layer));
		QPalette	PL=LayerButton->palette();
		PL.setColor(QPalette::Button,GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LayerButton->setPalette(PL);
		LayerGenButtons.append(LayerButton);
	}

	if(GetParamGlobal()->AllocBitBuffer==true
		&& ((AlignmentLargeBase *)Ab)->UseBitBuff==true){
		ui->labelCautionForOrigin->setText("Pick up/Generate from BitBuffer");
	}
	else{
		ui->labelCautionForOrigin->setText("Pick up/Generate from Master image");
	}

	InstallOperationLog(this);
}

SelectAlignmentLargeDialog::~SelectAlignmentLargeDialog()
{
    delete ui;

	if(TempLib!=NULL)
		delete	TempLib;
	TempLib=NULL;
}

void	SelectAlignmentLargeDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentLarge");
	if(Ab!=NULL){
		CmdGetAlignmentLargeLibraryListInPastePacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		Ab->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui->tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			::SetDataToTable(ui->tableWidgetLibList ,0 ,row ,QString::number(a->GetLibID()));
			::SetDataToTable(ui->tableWidgetLibList ,1 ,row ,a->GetLibName());
		}
	}
}
void SelectAlignmentLargeDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a==NULL)
		return;
	TempLib->SetLibID(a->GetLibID());

	CmdLoadAlignmentLargeLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentLarge");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Packet);

		if(Packet.Success==true){
			AlignmentLargeLibrary	*ALib=dynamic_cast<AlignmentLargeLibrary *>(TempLib->GetLibrary());
			AlignmentLargeLibID		=TempLib->GetLibID();
			ui->EditLibID			->setText(QString::number(TempLib->GetLibID()));
			ui->EditLibName			->setText(a->GetLibName());

			ui->EditMoveDot			->setValue(ALib->MoveDotX);
			ui->EditMoveDotY		->setValue(ALib->MoveDotY);
			ui->EditMoveDot2		->setValue(ALib->MoveDotX2);
			ui->EditMoveDotY2		->setValue(ALib->MoveDotY2);
			ui->checkBoxUsageGlobal	->setChecked(ALib->UsageGlobal);
		
			ui->spinBoxMaxCountHLine->setValue(ALib->MaxCountHLine);
			ui->spinBoxMaxCountVLine->setValue(ALib->MaxCountVLine);

			for(IntClass *a=TempLib->GetAdaptedGenLayers().GetFirst();a!=NULL;a=a->GetNext()){
				int	Layer=a->GetValue();
				if(0<=Layer && Layer<GetLayerNumb()){
					LayerGenButtons[Layer]->setChecked(true);
				}
			}

			ui->ButtonOK->setEnabled(true);
		}
		else{
			QMessageBox::critical(NULL	,"Library error"
										,"Not loaded this library record");
		}
	}
}
void	SelectAlignmentLargeDialog::GetDataFromWindow(XAlignmentLarge &data)
{
	data.SetLibID(AlignmentLargeLibID);
	data.SetItemName(ui->EditItemName->text());

	data.GetThresholdW()->MoveDotX		=ui->EditMoveDot	->value();
	data.GetThresholdW()->MoveDotY		=ui->EditMoveDotY	->value();
	data.GetThresholdW()->MoveDotX2		=ui->EditMoveDot2	->value();
	data.GetThresholdW()->MoveDotY2		=ui->EditMoveDotY2	->value();

	data.GetThresholdW()->UsageGlobal	=ui->checkBoxUsageGlobal	->isChecked();
	data.GetThresholdW()->MaxCountHLine	=ui->spinBoxMaxCountHLine	->value();
	data.GetThresholdW()->MaxCountVLine	=ui->spinBoxMaxCountVLine	->value();
}
void SelectAlignmentLargeDialog::on_ButtonOK_clicked()
{
	done(true);
}

void SelectAlignmentLargeDialog::on_ButtonCancel_clicked()
{
	done(false);
}

void SelectAlignmentLargeDialog::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_ButtonOK_clicked();
}
