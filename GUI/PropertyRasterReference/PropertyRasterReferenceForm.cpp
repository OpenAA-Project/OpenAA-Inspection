#include "PropertyRasterReferenceForm.h"
#include "ui_PropertyRasterReferenceForm.h"
#include <QColorDialog>
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

const	char	*AlgoRoot=/**/"Basic";
const	char	*AlgoName=/**/"Raster";

PropertyRasterReferenceForm::PropertyRasterReferenceForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyRasterReferenceForm)
{
    ui->setupUi(this);

	::SetColumnWidthInTable(ui->tableWidgetReferenceList ,0, 15);
	::SetColumnWidthInTable(ui->tableWidgetReferenceList ,1, 15);
	::SetColumnWidthInTable(ui->tableWidgetReferenceList ,2, 25);
	::SetColumnWidthInTable(ui->tableWidgetReferenceList ,3, 35);

	ui->spinBoxShrinkSize	->setValue	(ControlRememberer::GetInt(ui->spinBoxShrinkSize));
	ui->spinBoxColorRange	->setValue	(ControlRememberer::GetInt(ui->spinBoxColorRange));
	ui->spinBoxMinSize		->setValue	(ControlRememberer::GetInt(ui->spinBoxMinSize	));
}

PropertyRasterReferenceForm::~PropertyRasterReferenceForm()
{
    delete ui;
}

RasterBase	    *PropertyRasterReferenceForm::GetRasterBase(void)
{
	RasterBase	*Base=(RasterBase *)GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	return Base;
}
void	PropertyRasterReferenceForm::BuildForShow(void)
{
	ShowGrid();
}
void	PropertyRasterReferenceForm::StartPage	(void)
{
	ShowGrid();
}
void	PropertyRasterReferenceForm::RepaintImage(void)
{
	GUIFormBase	*GForm=GetImagePanel();
	if(GForm!=NULL){
		GForm->repaint();
	}
}

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

void	PropertyRasterReferenceForm::ShowGrid(void)
{
	ColorProfiler.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqRasterReference	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckRasterReference	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){			
			ColorProfiler.MergeBySource(ACmd.ColorProfiler);
		}
	}
	RasterBase	    *ABase=GetRasterBase();
	ColorProfiler.MergeBySource(ABase->ColorProfiles);

	int	N=ColorProfiler.GetCount();
	ui->tableWidgetReferenceList->setRowCount(N);
	ui->tableWidgetReferenceList->setUpdatesEnabled(false);
	ColorProfile	*r=ColorProfiler.GetFirst();
	for(int Row=0;Row<N && r!=NULL;Row++,r=r->GetNext()){
		ColorProfileColorButton	*a=::SetDataToTableColorButton(ui->tableWidgetReferenceList,0,Row,ToString(r->SrcColor));
		a->setColor(r->SrcColor);
		connect(a,SIGNAL(SignalClicked(int)),this,SLOT(SlotImageClicked(int)));
		ColorProfileColorButton	*b=::SetDataToTableColorButton(ui->tableWidgetReferenceList,1,Row,ToString(r->DstColor));
		b->setColor(r->DstColor);
		connect(b,SIGNAL(SignalClicked(int)),this,SLOT(SlotRasterClicked(int)));
	}
	ui->tableWidgetReferenceList->setUpdatesEnabled(true);
}

void	PropertyRasterReferenceForm::SlotImageClicked(int Line)
{
	ColorProfile *r=ColorProfiler.GetItem(Line);
	if(r==NULL)
		return;
	QColor Col=QColorDialog::getColor(r->SrcColor,nullptr,"元画像の色");
	if(Col.isValid()==true){
		r->SrcColor=Col;
		ColorProfileColorButton	*a=::SetDataToTableColorButton(ui->tableWidgetReferenceList,0,Line,ToString(r->SrcColor));
		a->setColor(Col);
	}
}

void	PropertyRasterReferenceForm::SlotRasterClicked(int Line)
{
	ColorProfile *r=ColorProfiler.GetItem(Line);
	if(r==NULL)
		return;
	QColor Col=QColorDialog::getColor(r->DstColor,nullptr,"変換後の色");
	if(Col.isValid()==true){
		r->DstColor=Col;
		ColorProfileColorButton	*a=::SetDataToTableColorButton(ui->tableWidgetReferenceList,1,Line,ToString(r->DstColor));
		a->setColor(Col);
	}
}
DisplayImageWithAlgorithm	*PropertyRasterReferenceForm::GetImagePanel(void)
{
	DisplayImageWithAlgorithm	*GForm=(DisplayImageWithAlgorithm *)GetLayersBase()->FindByName(/**/"Inspection",/**/"RasterReferenceImagePanel",/**/"");
	return GForm;

}

void PropertyRasterReferenceForm::on_toolButtonModeShowPDF_clicked()
{
	RepaintImage();
}


void PropertyRasterReferenceForm::on_toolButtonModeShowReference_clicked()
{
	RepaintImage();
}

void	PropertyRasterReferenceForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdRasterGetDrawAttr	*CmdGetDrawAttrVar=dynamic_cast<CmdRasterGetDrawAttr *>(packet);
	if(CmdGetDrawAttrVar!=NULL){
		CmdGetDrawAttrVar->ShowPDF				=ui->toolButtonModeShowPDF		->isChecked();
		CmdGetDrawAttrVar->ShowReferenceItems	=ui->toolButtonModeShowReference->isChecked();
		CmdGetDrawAttrVar->ReferenceID			=ui->tableWidgetReferenceList	->currentRow();
		return;
	}
	CmdRasterDrawEnd	*CmdRasterDrawEndVar=dynamic_cast<CmdRasterDrawEnd *>(packet);
	if(CmdRasterDrawEndVar!=NULL){
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(CmdRasterDrawEndVar->Area,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			int	page=P->GetValue();
			DataInPage	*pdata=GetLayersBase()->GetPageData(page);
			FlexArea	A=CmdRasterDrawEndVar->Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdMakeRasterReferenceItem	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
				RCmd.LocalArea	=A;
				RCmd.Send(NULL,GlobalPage,0);
			}
		}
		return;
	}
}

void PropertyRasterReferenceForm::on_pushButtonAutoPickUp_clicked()
{
	int	ColorMergin	=ControlRememberer::SetValue(ui->spinBoxColorRange	);
	int	MinItemArea	=ControlRememberer::SetValue(ui->spinBoxMinSize		);
	int	ShrinkSize	=ControlRememberer::SetValue(ui->spinBoxShrinkSize	);
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeAutoRasterReference	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.ColorMergin=ColorMergin;
		RCmd.MinItemArea=MinItemArea;
		RCmd.ShrinkSize	=ShrinkSize;
		RCmd.Send(NULL,GlobalPage,0);			
	}
	RepaintImage();
	ShowGrid();
}


void PropertyRasterReferenceForm::on_pushButtonSaveColorProfile_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName(NULL
												,"Save color profile"
												,QString()
												,/**/"dat(*.dat);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			ColorProfileContainerWithTable		ColorProfilerW;
			ColorProfilerW=ColorProfiler;
			ColorProfilerW.Save(&File);
		}
	}
}

void PropertyRasterReferenceForm::on_pushButtonSaveDefaultColorProfile_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSaveDefaultColorProfile	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.ColorProfiler=ColorProfiler;
		RCmd.Send(NULL,GlobalPage,0);			
	}
}

