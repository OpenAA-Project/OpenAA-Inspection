#include "ColorProfileDialog.h"
#include "ui_ColorProfileDialog.h"
#include <QColorDialog>
#include "PropertyRasterForm.h"

ColorProfileColorButton::ColorProfileColorButton(int _Line)
{
	Line=_Line;
}
void	ColorProfileColorButton::SlotClicked()
{
	emit	SignalClicked(Line);
}


ColorProfileColorButton		*FuncCall	SetDataToTableColorButton(QTableWidget *W ,int col ,int row ,const QVariant &value)
{
	//W->model()->setData(W->model()->index(row,col),value);

	QTableWidgetItem *L=W->item ( row, col);
	if(L==NULL || dynamic_cast<ColorProfileColorButton *>(L)==NULL){
		ColorProfileColorButton	*b=new ColorProfileColorButton(row);
		b->setText(value.toString());
		W->setCellWidget(row,col,b);
		return b;
	}
	else{
		ColorProfileColorButton	*b=dynamic_cast<ColorProfileColorButton *>(L);
		if(b!=NULL){
			b->setText(value.toString());
			return b;
		}
	}
	return NULL;
}

QString	ToString(const QColor &s)
{
	return	 QString("(")
			+QString::number(s.red())
			+QString(",")
			+QString::number(s.green())
			+QString(",")
			+QString::number(s.blue())
			+QString(")");
}

ColorProfileDialog::ColorProfileDialog(LayersBase *base
										 ,PropertyRasterForm *p
										, ColorProfileContainerWithTable &_ColorProfiles 
										,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
	,Parent(p)
    ,ui(new Ui::ColorProfileDialog)
{
    ui->setupUi(this);
    ColorProfiles=_ColorProfiles;
	Changed		=false;

	::SetColumnWidthInTable(ui->tableWidget ,0, 43);
	::SetColumnWidthInTable(ui->tableWidget ,1, 43);
	ShowGrid();
}

ColorProfileDialog::~ColorProfileDialog()
{
    delete ui;
}

void    ColorProfileDialog::ShowGrid(void)
{
	ui->tableWidget->setRowCount(ColorProfiles.GetCount());
    int Row=0;
    for(ColorProfile *r=ColorProfiles.GetFirst();r!=NULL;r=r->GetNext(),Row++){
		ColorProfileColorButton	*a=::SetDataToTableColorButton(ui->tableWidget,0,Row,ToString(r->SrcColor));
		a->setColor(r->SrcColor);
		connect(a,SIGNAL(SignalClicked(int)),this,SLOT(SlotImageClicked(int)));
		ColorProfileColorButton	*b=::SetDataToTableColorButton(ui->tableWidget,1,Row,ToString(r->DstColor));
		b->setColor(r->DstColor);
		connect(b,SIGNAL(SignalClicked(int)),this,SLOT(SlotRasterClicked(int)));
    }
}
    
void	ColorProfileDialog::SlotImageClicked(int Line)
{
	ColorProfile *r=ColorProfiles.GetItem(Line);
	if(r==NULL)
		return;
	QColor Col=QColorDialog::getColor(r->SrcColor,nullptr,"元画像の色");
	if(Col.isValid()==true){
		r->SrcColor=Col;
		ColorProfileColorButton	*a=::SetDataToTableColorButton(ui->tableWidget,0,Line,ToString(r->SrcColor));
		a->setColor(Col);
	}
}

void	ColorProfileDialog::SlotRasterClicked(int Line)
{
	ColorProfile *r=ColorProfiles.GetItem(Line);
	if(r==NULL)
		return;
	QColor Col=QColorDialog::getColor(r->DstColor,nullptr,"変換後の色");
	if(Col.isValid()==true){
		r->DstColor=Col;
		ColorProfileColorButton	*a=::SetDataToTableColorButton(ui->tableWidget,1,Line,ToString(r->DstColor));
		a->setColor(Col);
	}
}

void ColorProfileDialog::on_pushButtonOK_clicked()
{
	done(true);
}


void ColorProfileDialog::on_pushButtonSave_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName(NULL
												,"Save ColorProfile data"
												,QString()
												,/**/"dat file(*.dat);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			ColorProfiles.Save(&File);
		}
	}
}


void ColorProfileDialog::on_pushButtonLoad_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(NULL
												,"Load ColorProfile data"
												,QString()
												,/**/"dat file(*.dat);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			ColorProfiles.Load(&File);
			ColorProfiles.MakeTable();
			ShowGrid();
		}
	}
}


void ColorProfileDialog::on_pushButtonClear_clicked()
{
	ColorProfiles.RemoveAll();
	ShowGrid();
	Changed=true;
}


void ColorProfileDialog::on_pushButtonAppend_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(NULL
												,"Append ColorProfile data"
												,QString()
												,/**/"dat file(*.dat);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			ColorProfileContainer		tColorProfiles;
			tColorProfiles.Load(&File);
			ColorProfiles.AddMove(tColorProfiles);
			ColorProfiles.MakeTable();
			ShowGrid();
			Changed=true;
		}
	}
}


void ColorProfileDialog::on_pushButtonSaveDefault_clicked()
{
	RasterBase	*ABase=Parent->GetRasterBase();
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	QFile	File(ABase->DefaultColorProfileFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		ColorProfiles.Save(&File);
	}
}


void ColorProfileDialog::on_pushButtonLoadDefault_clicked()
{
	RasterBase	*ABase=Parent->GetRasterBase();
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	QFile	File(ABase->DefaultColorProfileFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		ColorProfiles.Load(&File);
		ColorProfiles.MakeTable();
		Changed=true;
	}
}

