#include "PropertyLineEnhancerResource.h"
#include "EditLibraryColor.h"
#include "XLineEnhancer.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XGUIFormBase.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditLibraryColor::EditLibraryColor(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base),ColorSamples(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	LineEnhancerBase	*BBase=GetLineEnhancerBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempLineEnhancerLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);


	ColorThre		.setParent(ui.frameThreshold);
	ColorThre		.Fit(ui.frameThreshold);

	connect(&ColorThre,SIGNAL(AddEliminated(void)),this,SLOT(SlotAddEliminated(void)));
	connect(&ColorThre,SIGNAL(DelEliminated(void)),this,SLOT(SlotDelEliminated(void)));

	ColorSamples.setParent(ui.frameColorSample);
	ColorSamples.move(0,0);
	RGBPanel.setParent(ui.frameShowColorSmples);
	RGBPanel.Fit(ui.frameShowColorSmples);
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"LineEnhancerImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*Display=dynamic_cast<DisplayImage *>(GProp);
		if(Display!=NULL){
			PickupColor=Display->GetPickedColor();
			PickupColorFrame.setParent(ui.framePickupColor);
			PickupColorFrame.move(0,0);
			PickupColorFrame.resize(ui.framePickupColor->width(),ui.framePickupColor->height());
			PickupColorFrame.SetColor(PickupColor);
			RGBPanel.Cube=Display->GetRGBStock();
			RGBPanel.InitializedDoneCube();
		}
	}

	connect(&ColorSamples,SIGNAL(SignalBeforeSave ()),this,SLOT(SlotColorSampleBeforeSave()));
	connect(&ColorSamples,SIGNAL(SignalSelectCData()),this,SLOT(SlotColorSampleSelectOne()));
	InstallOperationLog(this);
}

EditLibraryColor::~EditLibraryColor()
{

}

LineEnhancerBase	*EditLibraryColor::GetLineEnhancerBase(void)
{
	return (LineEnhancerBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LineEnhancer");
}


void	EditLibraryColor::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	LineEnhancerBase	*BBase=GetLineEnhancerBase();
	if(BBase!=NULL){
		CmdGetLineEnhancerLibraryListPacket	Packet(GetLayersBase());
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

void	EditLibraryColor::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}

void EditLibraryColor::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadLineEnhancerLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancerBase	*BBase=GetLineEnhancerBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(TempLib->GetLibrary());
				ColorThre.Cube=ALib->PickupColor;
				ColorThre.Repaint();
				ShowThresholdList();
				ui.ButtonLibSave	->setEnabled(true);
				ui.ButtonLibDelete	->setEnabled(true);			}
			else{
				QMessageBox::critical(NULL	,/**/"Library error"
											,/**/"Not loaded this library record");
			}
		}
	}
}
void	EditLibraryColor::SlotAddEliminated(void)
{
	ShowThresholdList();
	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
}
void	EditLibraryColor::SlotDelEliminated(void)
{
	ShowThresholdList();
	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
}

void	EditLibraryColor::SlotColorSampleBeforeSave()
{
	ColorSamples.CData.Set(ColorThre.Cube);
}
void	EditLibraryColor::SlotColorSampleSelectOne()
{
	ColorThre.Cube=*ColorSamples.CData.GetColorLogic();
	ColorThre.InitializedDoneCube();
	ColorThre.Repaint();
	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
}

void EditLibraryColor::on_pushButtonAddColorArea_clicked()
{
	ColorSampleList	Sample;
	Sample.Set(RGBPanel.Cube,RGBPanel.Ext);
	ColorThre.Cube.Add(*Sample.GetColorLogic(),0);

	ColorThre.Repaint();
	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
	ShowThresholdList();
}

void EditLibraryColor::on_pushButtonEliminateColorArea_clicked()
{
	ColorSampleList	Sample;
	Sample.Set(RGBPanel.Cube);
	ColorThre.Cube.Eliminate(*Sample.GetColorLogic(),0);

	ColorThre.Repaint();
	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
	ShowThresholdList();
}

void EditLibraryColor::on_pushButtonAddPickupColor_clicked()
{
	ColorThre.Cube.Add(PickupColor.rgb(),ui.spinBoxMerginAddPickupColor->value());
	ColorThre.Repaint();
	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
	ShowThresholdList();
}

void EditLibraryColor::on_pushButtonSubPickupColor_clicked()
{
	ColorThre.Cube.Eliminame(PickupColor.rgb(),ui.spinBoxMerginSubPickupColor->value());
	ColorThre.Repaint();
	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
	ShowThresholdList();
}

void EditLibraryColor::on_pushButtonAddColor_clicked()
{
	ColorThre.Cube.Add(*ColorSamples.CData.GetColorLogic());
	ColorThre.Repaint();
	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
	ShowThresholdList();
}

void EditLibraryColor::on_pushButtonEliminateColor_clicked()
{
	ColorThre.Cube.Eliminate(*ColorSamples.CData.GetColorLogic());
	ColorThre.Repaint();
	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
	ShowThresholdList();
}

void EditLibraryColor::on_listWidgetBaseColor_doubleClicked(QModelIndex)
{
	int	row=ui.listWidgetBaseColor->currentRow();
	if(row<0)
		return;
	ColorSpace	*c=ColorThre.Cube.GetBase(row);
	if(c!=NULL){
		ColorThre.Cube.RemoveBase(c);
		delete	c;
		if(TempLib!=NULL){
			LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(TempLib->GetLibrary());
			ALib->PickupColor=ColorThre.Cube;
		}
	}
	ColorThre.Repaint();
	ShowThresholdList();
}

void EditLibraryColor::on_listWidgetEliminatedColor_doubleClicked(QModelIndex)
{
	int	row=ui.listWidgetEliminatedColor->currentRow();
	if(row<0)
		return;
	ColorSpace	*c=ColorThre.Cube.GetEliminated(row);
	if(c!=NULL){
		ColorThre.Cube.RemoveEliminated(c);
		delete	c;
		if(TempLib!=NULL){
			LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(TempLib->GetLibrary());
			ALib->PickupColor=ColorThre.Cube;
		}
	}
	ColorThre.Repaint();
	ShowThresholdList();
}

void EditLibraryColor::on_pushButtonAddAllColor_clicked()
{
	ColorThre.Cube.Add(qRgb(128,128,128),222);
	ColorThre.Repaint();
	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
	ShowThresholdList();
}

void EditLibraryColor::ShowThresholdList(void)
{
	ui.listWidgetBaseColor->clear();
	ui.listWidgetEliminatedColor->clear();
	int	N=1;
	for(ColorSpace *c=ColorThre.Cube.GetFirstBase();c!=NULL;c=c->GetNext(),N++){
		ui.listWidgetBaseColor->addItem(QString::number(N));
	}
	N=1;
	for(ColorSpace *c=ColorThre.Cube.GetFirstEliminated();c!=NULL;c=c->GetNext(),N++){
		ui.listWidgetEliminatedColor->addItem(QString::number(N));
	}
}

void EditLibraryColor::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearLineEnhancerLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	LineEnhancerBase	*BBase=GetLineEnhancerBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

void EditLibraryColor::on_ButtonLibDelete_clicked()
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
		CmdDeleteLineEnhancerLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancerBase	*BBase=GetLineEnhancerBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditLibraryColor::on_ButtonLibSaveNew_clicked()
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
	CmdInsertLineEnhancerLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	LineEnhancerBase	*BBase=GetLineEnhancerBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui.ButtonLibSave	->setEnabled(true);
		ui.ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryColor::on_ButtonLibSave_clicked()
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

		CmdInsertLineEnhancerLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancerBase	*BBase=GetLineEnhancerBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateLineEnhancerLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancerBase	*BBase=GetLineEnhancerBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryColor::on_pushButton_clicked()
{
	close();
}
void	EditLibraryColor::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(data.GetLibrary());
	ui.EditMinDot			->setValue(ALib->MinDot);
	ui.EditMaxDot			->setValue(ALib->MaxDot);
	ui.EditMinSize			->setValue(ALib->MinSize);
	ui.EditMaxSize			->setValue(ALib->MaxSize);
	ui.EditLimitDot			->setValue(ALib->LimitDot);
	ui.EditShrinkDot		->setValue(ALib->ShrinkDot);
	ui.doubleSpinBoxEmphasizeRate	->setValue(ALib->EmphasizeRate);
	ui.EditPriority			->setValue(ALib->Priority);
	ui.EditMaxLineWidth		->setValue(ALib->MaxLineWidth);
	ui.EditStepDot			->setValue(ALib->StepDot);
	ui.EditSearchBlockWidth	->setValue(ALib->SearchBlockWidth);
	ui.EditSelfSearch		->setValue(ALib->SelfSearch);
}

void	EditLibraryColor::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(data.GetLibrary());
	ALib->MinDot			=ui.EditMinDot			->value();
	ALib->MaxDot			=ui.EditMaxDot			->value();
	ALib->MinSize			=ui.EditMinSize			->value();
	ALib->MaxSize			=ui.EditMaxSize			->value();
	ALib->LimitDot			=ui.EditLimitDot		->value();
	ALib->ShrinkDot			=ui.EditShrinkDot		->value();
	ALib->EmphasizeRate		=ui.doubleSpinBoxEmphasizeRate	->value();
	ALib->Priority			=ui.EditPriority		->value();
	ALib->MaxLineWidth		=ui.EditMaxLineWidth	->value();
	ALib->StepDot			=ui.EditStepDot			->value();
	ALib->SearchBlockWidth	=ui.EditSearchBlockWidth->value();
	ALib->SelfSearch		=ui.EditSelfSearch		->value();
}

