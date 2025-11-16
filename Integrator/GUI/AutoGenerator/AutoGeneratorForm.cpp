#include "AutoGeneratorForm.h"
#include "ui_AutoGeneratorForm.h"
#include "XAutoGenerator.h"
#include "AutoGeneratorButtonForm.h"
#include "XGeneralFunc.h"
#include <QFileDialog>

AutoGeneratorForm::AutoGeneratorForm(LayersBase *base,AutoGeneratorButtonForm *p ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(base)
    ,Parent(p)
    ,ui(new Ui::AutoGeneratorForm)
{
    ui->setupUi(this);

    ShowGrid();
}

AutoGeneratorForm::~AutoGeneratorForm()
{
    delete ui;
}


PushButtonInTable	*SetDataButtonToTable(QTableWidget* W, int col, int row)
{
	QTableWidgetItem *L=W->item ( row, col);
	if(L==NULL || dynamic_cast<QCheckBox *>(L)==NULL){
		PushButtonInTable	*b=new PushButtonInTable(col,row);
		b->setText(/**/"..");
		W->setCellWidget(row,col,b);
		return b;
	}
	else{
		PushButtonInTable	*b=dynamic_cast<PushButtonInTable *>(L);
		if(b!=NULL){
			return b;
		}
	}
	return NULL;
}


void    AutoGeneratorForm::ShowGrid(void)
{
    int N=Parent->ListContainer.GetCount();
    ui->tableWidget->setRowCount(N);
    int Row=0;
    for(ListAutoGenerator *s=Parent->ListContainer.GetFirst();s!=NULL;s=s->GetNext(),Row++){
        ::SetDataToTable(ui->tableWidget, 0, Row, s->Code           , Qt::ItemIsEditable);
        ::SetDataToTable(ui->tableWidget, 1, Row, s->Name           , Qt::ItemIsEditable);
        ::SetDataToTable(ui->tableWidget, 2, Row, s->DXFFileName    , Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidget, 4, Row, s->PDFFileName    , Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidget, 6, Row, s->AlignFileName    , Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidget, 8, Row, s->SpecialFileName    , Qt::ItemIsEditable);
	}
	SetGridButton();
}

void    AutoGeneratorForm::SetGridButton(void)
{
	int	N=ui->tableWidget->rowCount();
	for(int Row=0;Row<N;Row++){
		PushButtonInTable	*DXFButton=::SetDataButtonToTable(ui->tableWidget, 3, Row);
		connect(DXFButton,SIGNAL(SignalClicked(int,int)),this,SLOT(SlotChangeDXFFileName(int,int)));

		PushButtonInTable	*PDFButton=::SetDataButtonToTable(ui->tableWidget, 5, Row);
		connect(PDFButton,SIGNAL(SignalClicked(int,int)),this,SLOT(SlotChangePDFFileName(int,int)));

		PushButtonInTable	*AlignButton=::SetDataButtonToTable(ui->tableWidget, 7, Row);
		connect(AlignButton,SIGNAL(SignalClicked(int,int)),this,SLOT(SlotChangeAlignFileName(int,int)));

		PushButtonInTable	*SpecialButton=::SetDataButtonToTable(ui->tableWidget, 9, Row);
		connect(SpecialButton,SIGNAL(SignalClicked(int,int)),this,SLOT(SlotChangeSpecialFileName(int,int)));
	}
}

void    AutoGeneratorForm::SlotChangeDXFFileName(int column,int row)
{
	QString FileName=QFileDialog::getOpenFileName(nullptr, "DXF file"
												, QString()
												, /**/"DXF(*.dxf);;All files(*.*)");
	if(FileName.isEmpty()==false){
		::SetDataToTable(ui->tableWidget, 2, row, FileName  , Qt::ItemIsEditable);
	}
}
void    AutoGeneratorForm::SlotChangePDFFileName(int column,int row)
{
	QString FileName=QFileDialog::getOpenFileName(nullptr, "PDF file"
												, QString()
												, /**/"PDF(*.pdf);;All files(*.*)");
	if(FileName.isEmpty()==false){
		::SetDataToTable(ui->tableWidget, 4, row, FileName  , Qt::ItemIsEditable);
	}
}
void    AutoGeneratorForm::SlotChangeAlignFileName(int column,int row)
{
	QString FileName=QFileDialog::getOpenFileName(nullptr, "Alignment file"
												, QString()
												, /**/"Alignment(*.aln);;All files(*.*)");
	if(FileName.isEmpty()==false){
		::SetDataToTable(ui->tableWidget, 6, row, FileName  , Qt::ItemIsEditable);
	}
}
void    AutoGeneratorForm::SlotChangeSpecialFileName(int column,int row)
{
	QString FileName=QFileDialog::getOpenFileName(nullptr, "Special setting file"
												, QString()
												, /**/"Special setting(*.spc);;All files(*.*)");
	if(FileName.isEmpty()==false){
		::SetDataToTable(ui->tableWidget, 8, row, FileName  , Qt::ItemIsEditable);
	}
}

void    AutoGeneratorForm::GetDataFromWindow(void)
{
	Parent->ListContainer.RemoveAll();
	int	Count=ui->tableWidget->rowCount();
	for(int row=0;row<Count;row++){
		ListAutoGenerator	*L=new ListAutoGenerator();
		L->Code				=::GetDataToTable(ui->tableWidget, 0, row);
		if(L->Code.isEmpty()==false){
			L->Name				=::GetDataToTable(ui->tableWidget, 1, row);
			L->DXFFileName		=::GetDataToTable(ui->tableWidget, 2, row);
			L->PDFFileName		=::GetDataToTable(ui->tableWidget, 4, row);
			L->AlignFileName	=::GetDataToTable(ui->tableWidget, 6, row);
			L->SpecialFileName	=::GetDataToTable(ui->tableWidget, 8, row);
			Parent->ListContainer.AppendList(L);
		}
		else{
			delete	L;
		}
	}
}

void AutoGeneratorForm::on_pushButtonAddLine_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row>=0){
		ui->tableWidget->insertRow(Row);
	}
	else{
		ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
	}
	SetGridButton();
}


void AutoGeneratorForm::on_pushButtonDelLine_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row>=0){
		ui->tableWidget->removeRow(Row);
	}
}


void AutoGeneratorForm::on_pushButtonClearAll_clicked()
{
	ui->tableWidget->setRowCount(0);
	ui->tableWidget->setRowCount(1);
	SetGridButton();
}


void AutoGeneratorForm::on_pushButtonSaveList_clicked()
{
	QString FileName=QFileDialog::getSaveFileName(nullptr, "File name to save list"
												, QString()
												, /**/"AutoGen(*.AutoGen);;All files(*.*)");
	if(FileName.isEmpty()==false){
		GetDataFromWindow();
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			Parent->ListContainer.Save(&File);
		}
	}
}

void AutoGeneratorForm::on_pushButtonLoadList_clicked()
{
	QString FileName=QFileDialog::getOpenFileName(nullptr, "File name to load list"
												, QString()
												, /**/"AutoGen(*.AutoGen);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			if(Parent->ListContainer.Load(&File)==true){
				ShowGrid();
			}
		}
	}
}

void    AutoGeneratorForm::closeEvent(QCloseEvent *event)
{
	GetDataFromWindow();
	Parent->SaveListContainer();
}

void    AutoGeneratorForm::resizeEvent(QResizeEvent *)
{
	ui->tableWidget->resize(width()-20,height()-ui->frame->height()-10);

	::SetColumnWidthInTable(ui->tableWidget ,0, 8);
	::SetColumnWidthInTable(ui->tableWidget ,1, 8);
	::SetColumnWidthInTable(ui->tableWidget ,2, 16);
	::SetColumnWidthInTable(ui->tableWidget ,3, 3);
	::SetColumnWidthInTable(ui->tableWidget ,4, 16);
	::SetColumnWidthInTable(ui->tableWidget ,5, 3);
	::SetColumnWidthInTable(ui->tableWidget ,6, 16);
	::SetColumnWidthInTable(ui->tableWidget ,7, 3);
	::SetColumnWidthInTable(ui->tableWidget ,8, 16);
	::SetColumnWidthInTable(ui->tableWidget ,9, 3);

}
