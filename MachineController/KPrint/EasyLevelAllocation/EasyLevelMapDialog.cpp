#include "EasyLevelAllocationResource.h"
#include "EasyLevelMapDialog.h"
#include "ui_EasyLevelMapDialog.h"
#include "CartonMenuForm.h"
#include "XDentInspection.h"
#include "XDentLibrary.h"
#include "XDataInLayer.h"
#include "XDotColorMatching.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralDialog.h"

EasyLevelMapDialog::SelectLibrary::SelectLibrary(LayersBase *Base)
	:ServiceForLayers(Base)
{
	pLibFolderForm	=NULL;
	LibFolderID		=-1;
	Table			=NULL;
	TempLib	=NULL;
	LibType	=-1;
}
EasyLevelMapDialog::SelectLibrary::~SelectLibrary(void)
{
	if(pLibFolderForm!=NULL){
		delete	pLibFolderForm;
		pLibFolderForm=NULL;
	}
	if(TempLib!=NULL){
		delete	TempLib;
		TempLib=NULL;
	}
}
void	EasyLevelMapDialog::SelectLibrary::SetInitial(AlgorithmBase *ABase ,QWidget *LibFolderParent)
{
	if(ABase!=NULL)	
		LibType=ABase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),LibFolderParent);
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
}

EasyLevelMapDialog::EasyLevelMapDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
	,LibraryListDotColorMatching(Base)
	,LibraryListDentInspection(Base)
    ,ui(new Ui::EasyLevelMapDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	LastLevel	=-1;
	CartonMenuForm	*f=(CartonMenuForm	*)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
	if(f!=NULL){
		for(int i=0;i<10;i++){
			LevelData[i]=f->Param.Level[i];
		}
	}
	LibraryListDotColorMatching.Table	=ui->tableWidgetLibListDotColorMatching;
	LibraryListDentInspection.Table		=ui->tableWidgetLibListDentInspection;
	AlgorithmBase	*ABaseDotColorMatching=GetLayersBase()->GetAlgorithmBase(DefLibTypeDotColorMatchingInspect);
	LibraryListDotColorMatching	.SetInitial(ABaseDotColorMatching,ui->frameLibFolderDotColorMatching);
	
	AlgorithmBase	*ABaseDentInspection=GetLayersBase()->GetAlgorithmBase(DefLibTypeDent);
	LibraryListDentInspection	.SetInitial(ABaseDentInspection,ui->frameLibFolderDentInspection);

	ui->tableWidgetLibListDotColorMatching	->setColumnWidth(0,48);
	ui->tableWidgetLibListDotColorMatching	->setColumnWidth(1,150);
	ui->tableWidgetLibListDentInspection	->setColumnWidth(0,48);
	ui->tableWidgetLibListDentInspection	->setColumnWidth(1,150);

	connect(LibraryListDotColorMatching.pLibFolderForm	,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolderDotColorMatching(int,QString)));
	connect(LibraryListDentInspection.pLibFolderForm	,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolderDentInspction(int,QString)));

	on_toolButtonDotColorMatchLibPattern_clicked();
	on_toolButtonDotColorMatchLibFlat_clicked();
	on_toolButtonDotColorMatchCADLib_clicked();
	on_toolButtonDotColorMatchBladeLib_clicked();
	on_toolButtonDentLib_clicked();

	LastLevel	=ui->horizontalSliderLevel->value();
	ToWindow(LastLevel);
}

EasyLevelMapDialog::~EasyLevelMapDialog()
{
    delete ui;
}

void EasyLevelMapDialog::on_horizontalSliderLevel_valueChanged(int value)
{
	int	Level=ui->horizontalSliderLevel->value();
	ui->label_LevelNumber->setText(QString::number(Level));
	if(LastLevel>=0){
		FromWindow(LastLevel);
	}
	ToWindow(Level);
	ui->toolButtonDotColorMatchLibPattern->setChecked(true);
	on_toolButtonDotColorMatchLibPattern_clicked();
	LastLevel=Level;
}
void EasyLevelMapDialog::FromWindow(int Level)
{
	LevelData[Level].LevelName=ui->lineEditLevelName->text();
}
void EasyLevelMapDialog::ToWindow(int Level)
{
	ui->lineEditLevelName->setText(LevelData[Level].LevelName);
}

void EasyLevelMapDialog::on_toolButtonDotColorMatchLibPattern_clicked()
{
	if(ui->toolButtonDotColorMatchLibPattern->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(0);
		int	Level=ui->horizontalSliderLevel->value();
		CartonMenuForm	*f=(CartonMenuForm	*)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
		if(f!=NULL){
			int	ID=-1;
			switch(Level){
			case 0:	ID=f->Param.DotColorMatchLibPattern1;	break;
			case 1:	ID=f->Param.DotColorMatchLibPattern2;	break;
			case 2:	ID=f->Param.DotColorMatchLibPattern3;	break;
			case 3:	ID=f->Param.DotColorMatchLibPattern4;	break;
			case 4:	ID=f->Param.DotColorMatchLibPattern5;	break;
			}
			if(ID>=0){
				ShowID(LibraryListDotColorMatching.LibType,ID,LibraryListDotColorMatching);
			}
		}
	}
}

void EasyLevelMapDialog::on_toolButtonDotColorMatchLibFlat_clicked()
{
	if(ui->toolButtonDotColorMatchLibFlat->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(0);
		int	Level=ui->horizontalSliderLevel->value();
		CartonMenuForm	*f=(CartonMenuForm	*)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
		if(f!=NULL){
			int	ID=-1;
			switch(Level){
			case 0:	ID=f->Param.DotColorMatchLibFlat1;	break;
			case 1:	ID=f->Param.DotColorMatchLibFlat2;	break;
			case 2:	ID=f->Param.DotColorMatchLibFlat3;	break;
			case 3:	ID=f->Param.DotColorMatchLibFlat4;	break;
			case 4:	ID=f->Param.DotColorMatchLibFlat5;	break;
			}
			if(ID>=0){
				ShowID(LibraryListDotColorMatching.LibType,ID,LibraryListDotColorMatching);
			}
		}
	}
}

void EasyLevelMapDialog::on_toolButtonDotColorMatchCADLib_clicked()
{
	if(ui->toolButtonDotColorMatchCADLib->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(0);
		int	Level=ui->horizontalSliderLevel->value();
		CartonMenuForm	*f=(CartonMenuForm	*)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
		if(f!=NULL){
			int	ID=-1;
			switch(Level){
			case 0:	ID=f->Param.DotColorMatchCADLib1;	break;
			case 1:	ID=f->Param.DotColorMatchCADLib2;	break;
			case 2:	ID=f->Param.DotColorMatchCADLib3;	break;
			case 3:	ID=f->Param.DotColorMatchCADLib4;	break;
			case 4:	ID=f->Param.DotColorMatchCADLib5;	break;
			}
			if(ID>=0){
				ShowID(LibraryListDotColorMatching.LibType,ID,LibraryListDotColorMatching);
			}
		}
	}
}

void EasyLevelMapDialog::on_toolButtonDotColorMatchBladeLib_clicked()
{
	if(ui->toolButtonDotColorMatchBladeLib->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(0);
		int	Level=ui->horizontalSliderLevel->value();
		CartonMenuForm	*f=(CartonMenuForm	*)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
		if(f!=NULL){
			int	ID=-1;
			switch(Level){
			case 0:	ID=f->Param.DotColorMatchBladeLib1;	break;
			case 1:	ID=f->Param.DotColorMatchBladeLib2;	break;
			case 2:	ID=f->Param.DotColorMatchBladeLib3;	break;
			case 3:	ID=f->Param.DotColorMatchBladeLib4;	break;
			case 4:	ID=f->Param.DotColorMatchBladeLib5;	break;
			}
			if(ID>=0){
				ShowID(LibraryListDotColorMatching.LibType,ID,LibraryListDotColorMatching);
			}
		}
	}
}

void EasyLevelMapDialog::on_toolButtonDentLib_clicked()
{
	if(ui->toolButtonDentLib->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(1);
		int	Level=ui->horizontalSliderLevel->value();
		CartonMenuForm	*f=(CartonMenuForm	*)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
		if(f!=NULL){
			int	ID=-1;
			switch(Level){
			case 0:	ID=f->Param.DentLib1;	break;
			case 1:	ID=f->Param.DentLib2;	break;
			case 2:	ID=f->Param.DentLib3;	break;
			case 3:	ID=f->Param.DentLib4;	break;
			case 4:	ID=f->Param.DentLib5;	break;
			}
			if(ID>=0){
				ShowID(LibraryListDentInspection.LibType,ID,LibraryListDentInspection);
			}
		}
	}

}

void EasyLevelMapDialog::on_pushButtonSettingLibIDDotColorMatching_clicked()
{
	int	Level=ui->horizontalSliderLevel->value();
	CartonMenuForm	*f=(CartonMenuForm	*)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
	if(f!=NULL){
		if(ui->toolButtonDotColorMatchLibPattern->isChecked()==true){
			int	Row=ui->tableWidgetLibListDotColorMatching->currentRow();
			if(Row>=0){
				AlgorithmLibraryList	*AL=LibraryListDotColorMatching.LibList[Row];
				int	ID=-1;
				if(AL!=NULL){
					ID=AL->GetLibID();
					switch(Level){
					case 0:	f->Param.DotColorMatchLibPattern1	=ID;	break;
					case 1:	f->Param.DotColorMatchLibPattern2	=ID;	break;
					case 2:	f->Param.DotColorMatchLibPattern3	=ID;	break;
					case 3:	f->Param.DotColorMatchLibPattern4	=ID;	break;
					case 4:	f->Param.DotColorMatchLibPattern5	=ID;	break;
					}
				}
			}
		}
		else
		if(ui->toolButtonDotColorMatchLibFlat->isChecked()==true){
			int	Row=ui->tableWidgetLibListDotColorMatching->currentRow();
			if(Row>=0){
				AlgorithmLibraryList	*AL=LibraryListDotColorMatching.LibList[Row];
				int	ID=-1;
				if(AL!=NULL){
					ID=AL->GetLibID();
					switch(Level){
					case 0:	f->Param.DotColorMatchLibFlat1	=ID;	break;
					case 1:	f->Param.DotColorMatchLibFlat2	=ID;	break;
					case 2:	f->Param.DotColorMatchLibFlat3	=ID;	break;
					case 3:	f->Param.DotColorMatchLibFlat4	=ID;	break;
					case 4:	f->Param.DotColorMatchLibFlat5	=ID;	break;
					}
				}
			}
		}
		else
		if(ui->toolButtonDotColorMatchCADLib->isChecked()==true){
			int	Row=ui->tableWidgetLibListDotColorMatching->currentRow();
			if(Row>=0){
				AlgorithmLibraryList	*AL=LibraryListDotColorMatching.LibList[Row];
				int	ID=-1;
				if(AL!=NULL){
					ID=AL->GetLibID();
					switch(Level){
					case 0:	f->Param.DotColorMatchCADLib1	=ID;	break;
					case 1:	f->Param.DotColorMatchCADLib2	=ID;	break;
					case 2:	f->Param.DotColorMatchCADLib3	=ID;	break;
					case 3:	f->Param.DotColorMatchCADLib4	=ID;	break;
					case 4:	f->Param.DotColorMatchCADLib5	=ID;	break;
					}
				}
			}
		}
		else
		if(ui->toolButtonDotColorMatchBladeLib->isChecked()==true){
			int	Row=ui->tableWidgetLibListDotColorMatching->currentRow();
			if(Row>=0){
				AlgorithmLibraryList	*AL=LibraryListDotColorMatching.LibList[Row];
				int	ID=-1;
				if(AL!=NULL){
					ID=AL->GetLibID();
					switch(Level){
					case 0:	f->Param.DotColorMatchBladeLib1	=ID;	break;
					case 1:	f->Param.DotColorMatchBladeLib2	=ID;	break;
					case 2:	f->Param.DotColorMatchBladeLib3	=ID;	break;
					case 3:	f->Param.DotColorMatchBladeLib4	=ID;	break;
					case 4:	f->Param.DotColorMatchBladeLib5	=ID;	break;
					}
				}
			}
		}
	}
}

void EasyLevelMapDialog::on_pushButtonSettingLibIDDentInspection_clicked()
{
	int	Level=ui->horizontalSliderLevel->value();
	CartonMenuForm	*f=(CartonMenuForm	*)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
	if(f!=NULL){
		if(ui->toolButtonDentLib->isChecked()==true){
			int	Row=ui->tableWidgetLibListDentInspection->currentRow();
			if(Row>=0){
				AlgorithmLibraryList	*AL=LibraryListDotColorMatching.LibList[Row];
				int	ID=-1;
				if(AL!=NULL){
					ID=AL->GetLibID();
					switch(Level){
					case 0:	f->Param.DentLib1	=ID;	break;
					case 1:	f->Param.DentLib2	=ID;	break;
					case 2:	f->Param.DentLib3	=ID;	break;
					case 3:	f->Param.DentLib4	=ID;	break;
					case 4:	f->Param.DentLib5	=ID;	break;
					}
				}
			}
		}
	}
}
DotColorMatchingBase	*EasyLevelMapDialog::GetDotColorMatchingBase(void)
{
	return (DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
}

DentBase				*EasyLevelMapDialog::GetDentBase(void)
{
	return (DentBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DentInspection");
}

void	EasyLevelMapDialog::SlotSelectLibFolderDotColorMatching	(int libFolderID ,QString FolderName)
{
	LibraryListDotColorMatching.LibFolderID=libFolderID;
	//ui->tableWidgetLibList->clear();
	ui->tableWidgetLibListDotColorMatching->setRowCount(0);
	DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
	if(BBase!=NULL){
		CmdGetDotColorMatchingLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=libFolderID;
		BBase->TransmitDirectly(&Packet);
		LibraryListDotColorMatching.LibList	=Packet.AList;
		int	row=0;
		ui->tableWidgetLibListDotColorMatching->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui->tableWidgetLibListDotColorMatching->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibListDotColorMatching->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui->tableWidgetLibListDotColorMatching->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibListDotColorMatching->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}

void	EasyLevelMapDialog::SlotSelectLibFolderDentInspction	(int libFolderID ,QString FolderName)
{
	LibraryListDentInspection.LibFolderID=libFolderID;
	//ui->tableWidgetLibList->clear();
	ui->tableWidgetLibListDentInspection->setRowCount(0);
	DentBase	*BBase=GetDentBase();
	if(BBase!=NULL){
		CmdGetDentLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=libFolderID;
		BBase->TransmitDirectly(&Packet);
		LibraryListDentInspection.LibList	=Packet.AList;
		int	row=0;
		ui->tableWidgetLibListDentInspection->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui->tableWidgetLibListDentInspection->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibListDentInspection->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui->tableWidgetLibListDentInspection->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibListDentInspection->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}

void	EasyLevelMapDialog::ShowID(int LibType, int LibID,SelectLibrary &SLib)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmLibraryLevelContainer	SrcLib(ABase);
		if(ABase->GetLibraryContainer()->GetLibrary(LibID,SrcLib)==true){
			SLib.pLibFolderForm->SetCurrentLibFolder(SrcLib.GetLibFolderID());
			int	Row=0;
			for(AlgorithmLibraryList *a=SLib.LibList.GetFirst();a!=NULL;a=a->GetNext(),Row++){
				if(a->GetLibID()==LibID){
					break;
				}
			}
			::SetCurrentRow(SLib.Table,Row);
		}
	}
}


void EasyLevelMapDialog::on_pushButtonOK_clicked()
{
	if(LastLevel>=0){
		FromWindow(LastLevel);
	}
	CartonMenuForm	*f=(CartonMenuForm	*)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
	if(f!=NULL){
		for(int i=0;i<10;i++){
			f->Param.Level[i]=LevelData[i];
		}
	}
	done(true);
}
