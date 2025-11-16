#include "EditGUILibResource.h"
#include "XTypeDef.h"
#include "EditScanPhaseNumber.h"
#include "ui_EditScanPhaseNumber.h"
#include "XDataInExe.h"
#include "XGeneralDialog.h"


void	ScanPhaseNumberGrid::ChangeValue(int row ,int col,const QVariant &value)
{
	if(col==1){
		EParent->GetLayersBase()->GetParamGlobal()->SetScanPhaseNumber(row,value.toInt());
	}
}

void	ScanPhaseNumberGrid::GetValue(int row ,int col,QVariant &value)
{
	if(col==0){
		value=QVariant(QString(/**/"Phase ")+QString::number(row));
	}
	if(col==1){
		value=EParent->GetLayersBase()->GetParamGlobal()->GetScanNumberInPhase(row);
	}
}

EditScanPhaseNumber::EditScanPhaseNumber(LayersBase *Base,QWidget *parent) :
    QWidget(parent)
	,ServiceForLayers(Base)
	,aGrid(this)
    ,ui(new Ui::EditScanPhaseNumber)
{
    ui->setupUi(this);
	LangSolverGUILib.SetUI(this);
	aGrid.setParent(ui->frameGrid);
	aGrid.SetColumnCount(2);
	connect(&aGrid,SIGNAL(ChangedValue()),this,SLOT(ChangeValue()));

	SetGrid();
}

EditScanPhaseNumber::~EditScanPhaseNumber()
{
    delete ui;
}

void	EditScanPhaseNumber::SetGrid(void)
{
	aGrid.InitialGrid();
	aGrid.SetRowCount(GetLayersBase()->GetPhaseNumb());
	aGrid.move(0,0);
	aGrid.resize(ui->frameGrid->width(),ui->frameGrid->height());
	for(int r=0;r<GetPhaseNumb();r++){
		WMultiGrid::CellData *L0=aGrid.GetData(r ,0);
		L0->Value	=QVariant(QString(/**/"Phase ")+QString::number(r));
		L0->CType	=WMultiGrid::_CType_Label;
		L0->MaxValue	=9999;
		L0->MinValue	=0;
		L0->Alignment=Qt::AlignVCenter | Qt::AlignRight;

		WMultiGrid::CellData *L1=aGrid.GetData(r ,1);
		L1->Value	=GetParamGlobal()->GetScanNumberInPhase(r);
		L1->CType	=WMultiGrid::_CType_SpinBox;
		L1->MaxValue	=9999999;
		L1->MinValue	=-9999999;
		L1->Alignment=Qt::AlignVCenter | Qt::AlignRight;
	}

	aGrid.SetTopHeader(0, /**/"Phase");
	aGrid.SetTopHeader(1, /**/"Scan number");
	
	for(int r=0;r<GetPhaseNumb();r++){
		aGrid.SetLeftHeader(r,QString::number(r));
	}

	aGrid.ShowGrid();

	aGrid.setColumnWidth(0,70);
	aGrid.setColumnWidth(1,60);
}
void	EditScanPhaseNumber::Show(void)
{
	aGrid.ShowGrid();
	ui->spinBoxScanNumberInPhaseDimNumb->setValue(GetParamGlobal()->GetScanNumberInPhaseDimNumb());
}

void EditScanPhaseNumber::on_pushButtonCancel_clicked()
{
	GeneralDialog	*d=dynamic_cast<GeneralDialog *>(parent());
	if(d!=NULL){
		d->close();
	}
	else{
		close();
	}
}

void EditScanPhaseNumber::on_pushButtonOK_clicked()
{
	GeneralDialog	*d=dynamic_cast<GeneralDialog *>(parent());
	if(d!=NULL){
		d->close();
	}
	else{
		close();
	}
}

void	EditScanPhaseNumber::ChangeValue(void)
{
	emit	ChangedValue();
}
