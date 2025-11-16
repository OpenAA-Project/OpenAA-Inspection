#include "PropertyAutoAlignmentFormResource.h"
#include "EditLibraryAutoAlignment.h"
#include "XAutoAlignment.h"
#include "XDataInLayerCommander.h"
#include "XDisplayImage.h"
#include "XGeneralDialog.h"
#include "XGUIFormBase.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

EditLibraryAutoAlignment::EditLibraryAutoAlignment(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base),ColorSamples(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempAutoAlignmentLibraryPacket	Packet(GetLayersBase());
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
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AutoAlignmentImagePanel" ,/**/"");
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

EditLibraryAutoAlignment::~EditLibraryAutoAlignment()
{

}

AutoAlignmentBase	*EditLibraryAutoAlignment::GetAutoAlignmentBase(void)
{
	return (AutoAlignmentBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
}

void	EditLibraryAutoAlignment::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
	if(BBase!=NULL){
		CmdGetAutoAlignmentLibraryListPacket	Packet(GetLayersBase());
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

void	EditLibraryAutoAlignment::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}

void	EditLibraryAutoAlignment::SlotAddEliminated(void)
{
	ShowThresholdList();
	AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
}
void	EditLibraryAutoAlignment::SlotDelEliminated(void)
{
	ShowThresholdList();
	AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
}
void EditLibraryAutoAlignment::ShowThresholdList(void)
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

void	EditLibraryAutoAlignment::SlotColorSampleBeforeSave()
{
	ColorSamples.CData.Set(ColorThre.Cube);
}
void	EditLibraryAutoAlignment::SlotColorSampleSelectOne()
{
	ColorThre.Cube=*ColorSamples.CData.GetColorLogic();
	ColorThre.InitializedDoneCube();
	ColorThre.Repaint();
	AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
}

void EditLibraryAutoAlignment::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearAutoAlignmentLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

void EditLibraryAutoAlignment::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(EditLibraryAutoAlignment_LS,LID_5)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(EditLibraryAutoAlignment_LS,LID_6)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteAutoAlignmentLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditLibraryAutoAlignment::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, LangSolver.GetString(EditLibraryAutoAlignment_LS,LID_7)/*"Warning"*/
			, LangSolver.GetString(EditLibraryAutoAlignment_LS,LID_8)/*"No Library Name"*/
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertAutoAlignmentLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui.ButtonLibSave	->setEnabled(true);
		ui.ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryAutoAlignment::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, LangSolver.GetString(EditLibraryAutoAlignment_LS,LID_9)/*"Warning"*/
			, LangSolver.GetString(EditLibraryAutoAlignment_LS,LID_10)/*"No Library Name"*/
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertAutoAlignmentLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateAutoAlignmentLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryAutoAlignment::on_pushButton_clicked()
{
	close();
}

void EditLibraryAutoAlignment::on_pushButtonAddPickupColor_clicked()
{
	ColorThre.Cube.Add(PickupColor.rgb(),ui.spinBoxMerginAddPickupColor->value());
	ColorThre.Repaint();
	AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
	ShowThresholdList();
}

void EditLibraryAutoAlignment::on_pushButtonSubPickupColor_clicked()
{
	ColorThre.Cube.Eliminame(PickupColor.rgb(),ui.spinBoxMerginSubPickupColor->value());
	ColorThre.Repaint();
	AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
	ShowThresholdList();
}

void EditLibraryAutoAlignment::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadAutoAlignmentLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(TempLib->GetLibrary());
				ColorThre.Cube=ALib->PickupColor;
				ColorThre.Repaint();
				ShowThresholdList();
				ui.ButtonLibSave	->setEnabled(true);
				ui.ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL, /**/"Library error", LangSolver.GetString(EditLibraryAutoAlignment_LS,LID_11)/*"Not loaded this library record"*/);
			}
		}
	}
}

void	EditLibraryAutoAlignment::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(data.GetLibrary());
	ui.EditExpandForPickup		->setValue	(ALib->ExpandForPickup);
	ui.EditPicoShift			->setValue	(ALib->PicoShift);
	ui.checkBoxStartupExecute	->setChecked(ALib->StartupExecute);
	ui.EditPriority				->setValue	(ALib->Priority);
	ui.EditPickupExpansion		->setValue	(ALib->PickupExpansion);
	ui.EditNoiseShrink			->setValue	(ALib->NoiseShrink);
	ui.EditMinDot				->setValue	(ALib->MinDot);
	ui.EditFringeWidth			->setValue	(ALib->FringeWidth);
	ui.doubleSpinBoxAdptedMatchingRate		->setValue(ALib->AdptedMatchingRate);
	ui.doubleSpinBoxCompletelyMatchingRate	->setValue(ALib->CompletelyMatchingRate);
}

void	EditLibraryAutoAlignment::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(data.GetLibrary());
	ALib->ExpandForPickup		=ui.EditExpandForPickup		->value();
	ALib->PicoShift				=ui.EditPicoShift			->value();
	ALib->StartupExecute		=ui.checkBoxStartupExecute	->isChecked();
	ALib->Priority				=ui.EditPriority			->value();
	ALib->PickupExpansion		=ui.EditPickupExpansion		->value();
	ALib->NoiseShrink			=ui.EditNoiseShrink			->value();
	ALib->MinDot				=ui.EditMinDot				->value();
	ALib->FringeWidth			=ui.EditFringeWidth			->value();
	ALib->AdptedMatchingRate	=ui.doubleSpinBoxAdptedMatchingRate		->value();
	ALib->CompletelyMatchingRate=ui.doubleSpinBoxCompletelyMatchingRate	->value();
}

void EditLibraryAutoAlignment::on_pushButtonAddColor_clicked()
{
	ColorThre.Cube.Add(*ColorSamples.CData.GetColorLogic());
	ColorThre.Repaint();
	AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
	ShowThresholdList();
}

void EditLibraryAutoAlignment::on_pushButtonEliminateColor_clicked()
{
	ColorThre.Cube.Eliminate(*ColorSamples.CData.GetColorLogic());
	ColorThre.Repaint();
	AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
	ShowThresholdList();
}

void EditLibraryAutoAlignment::on_pushButtonAddAllColor_clicked()
{
	ColorThre.Cube.Add(qRgb(128,128,128),222);
	ColorThre.Repaint();
	AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
	ShowThresholdList();
	
}

void EditLibraryAutoAlignment::on_pushButtonAddColorArea_clicked()
{
	ColorSampleList	Sample;
	Sample.Set(RGBPanel.Cube,RGBPanel.Ext);
	ColorThre.Cube.Add(*Sample.GetColorLogic(),0);

	ColorThre.Repaint();
	AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
	ShowThresholdList();
}

void EditLibraryAutoAlignment::on_pushButtonEliminateColorArea_clicked()
{
	ColorSampleList	Sample;
	Sample.Set(RGBPanel.Cube);
	ColorThre.Cube.Eliminate(*Sample.GetColorLogic(),0);

	ColorThre.Repaint();
	AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(TempLib->GetLibrary());
	ALib->PickupColor=ColorThre.Cube;
	ShowThresholdList();
}

void EditLibraryAutoAlignment::on_listWidgetBaseColor_doubleClicked(QModelIndex)
{
	int	row=ui.listWidgetBaseColor->currentRow();
	if(row<0)
		return;
	ColorSpace	*c=ColorThre.Cube.GetBase(row);
	if(c!=NULL){
		ColorThre.Cube.RemoveBase(c);
		delete	c;
		if(TempLib!=NULL){
			AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(TempLib->GetLibrary());
			ALib->PickupColor=ColorThre.Cube;
		}
	}
	ColorThre.Repaint();
	ShowThresholdList();
}

void EditLibraryAutoAlignment::on_listWidgetEliminatedColor_doubleClicked(QModelIndex)
{
	int	row=ui.listWidgetEliminatedColor->currentRow();
	if(row<0)
		return;
	ColorSpace	*c=ColorThre.Cube.GetEliminated(row);
	if(c!=NULL){
		ColorThre.Cube.RemoveEliminated(c);
		delete	c;
		if(TempLib!=NULL){
			AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(TempLib->GetLibrary());
			ALib->PickupColor=ColorThre.Cube;
		}
	}
	ColorThre.Repaint();
	ShowThresholdList();
}
