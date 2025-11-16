#include "ShowSystemVersionDialog.h"
#include "ui_ShowSystemVersionDialog.h"
#include "CheckDLLForm.h"
#include "XAlgorithmInterfaceDLL.h"
#include "XAlgorithmBase.h"
#include "XDataInLayer.h"
#include "XGUIInterfaceDLL.h"
#include "XGUI.h"
#include "XDataInExe.h"
#include "XGeneralFunc.h"
#include "XResultInterfaceDLL.h"
#include "XResultDLLManager.h"
#include "XFilterManager.h"
#include "XCameraInterfaceDLL.h"
#include "XCameraClass.h"
#include "XPIOInterface.h"
#include "XPIOButton.h"
#include "XLightInterfaceDLL.h"
#include "XLightClass.h"
#include "XSequence.h"
#include "testsequencedlldialog.h"
#include "SettingParameterDialog.h"
#include "XExecuteVisualizer.h"
#include "XExecuteVisualizerForLib.h"
#include "XCSV.h"
#include "XExecuteVisualizerInterface.h"
#include "Regulus64System.h"

extern	CameraClassPack		*CameraPack;
extern	PIOClassPack		*PIOPack;
extern	DLLVarPack			*SeqVarPack;
extern	LightClassPack		*LightPack;

ShowSystemVersionDialog::ShowSystemVersionDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::ShowSystemVersionDialog)
{
    ui->setupUi(this);

	QDir::setCurrent(GetLayersBase()->GetSystemPath());
	EVMap=new RunnerMap(GetLayersBase(),true,NULL);
	EVMap->LoadDLL("ExecuteVisualizer");

	int	N	=GetLayersBase()->GetAlgoDLLContPointer()->GetCount()
			+GetLayersBase()->GetGuiInitializer()->GuiDLLPack->GetCount()
			+GetLayersBase()->GetResultDLLBase()->GetCount()
			+GetLayersBase()->GetFilterBank()->GetCount()
			+CameraPack->GetCount()
			+PIOPack->GetCount()
			+SeqVarPack->GetCount()
			+LightPack->GetCount()
			+EVMap->GetCount();
	ui->tableWidget->setRowCount(N);

	ui->tableWidget->setColumnWidth(0,110);
	ui->tableWidget->setColumnWidth(1,310);
	ui->tableWidget->setColumnWidth(2,66);
	ui->tableWidget->setColumnWidth(3,66);
	ui->tableWidget->setColumnWidth(4,66);
	ui->tableWidget->setColumnWidth(5,66);

	int	Row=0;
	for(AlgorithmDLLList *L=GetLayersBase()->GetAlgoDLLContPointer()->GetFirst();L!=NULL;L=L->GetNext()){
		QString	AlgoRoot ,AlgoName;
		L->GetName(AlgoRoot ,AlgoName);
		for(LogicDLL *ap=GetLayersBase()->GetLogicDLLBase()->GetFirst();ap!=NULL;ap=ap->GetNext()){
			if(ap->GetDLLRoot()==AlgoRoot && ap->GetDLLName()==AlgoName){
				ap->GetInstance()->InitialAfterParamLoaded();
			}
		}
		SetDataToTable(ui->tableWidget,0,Row ,"Algorithm");
		SetDataToTable(ui->tableWidget,1,Row ,L->GetFileName());
		const char *cfp=L->GetSystemVersion(Ver_Qt);
		if(cfp!=NULL)
			SetDataToTable(ui->tableWidget,2,Row ,QString::fromLocal8Bit(cfp));

		const char *rfp=L->GetSystemVersion(Ver_Revision);
		if(rfp!=NULL)
			SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(rfp));

		const char *gfp=L->GetSystemVersion(Ver_Regulus);
		if(gfp!=NULL)
			SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(gfp));

		const char *mfp=L->GetSystemVersion(Ver_IsMatched);
		if(mfp!=NULL)
			SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(mfp));
		Row++;

		QStringList		DLLFileNames;
		if(L->GetRelatedDLL(DLLFileNames)==true){
			for(int i=0;i<DLLFileNames.count();i++){
				SetDataToTable(ui->tableWidget,0,Row ,"Algorithm-DLL");
				SetDataToTable(ui->tableWidget,1,Row ,DLLFileNames[i]);

				char	*frevision=L->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Revision);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(frevision));
				}
				char	*fregulus=L->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Regulus);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(fregulus));
				}
				char	*fmatch=L->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_IsMatched);
				if(fmatch!=NULL){
					SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(fmatch));
				}
				Row++;
			}
		}
	}

	for(GuiDLLItem *G=GetLayersBase()->GetGuiInitializer()->GuiDLLPack->GetFirst();G!=NULL;G=G->GetNext()){
		SetDataToTable(ui->tableWidget,0,Row ,DefGUIPath);
		SetDataToTable(ui->tableWidget,1,Row ,G->GetFileName());
		const char *cfp=G->GetSystemVersion(Ver_Qt);
		if(cfp!=NULL)
			SetDataToTable(ui->tableWidget,2,Row ,QString::fromLocal8Bit(cfp));

		const char *rfp=G->GetSystemVersion(Ver_Revision);
		if(rfp!=NULL)
			SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(rfp));

		const char *gfp=G->GetSystemVersion(Ver_Regulus);
		if(gfp!=NULL)
			SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(gfp));

		const char *mfp=G->GetSystemVersion(Ver_IsMatched);
		if(mfp!=NULL)
			SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(mfp));
		Row++;

		QStringList		DLLFileNames;
		if(G->GetRelatedDLL(DLLFileNames)==true){
			for(int i=0;i<DLLFileNames.count();i++){
				SetDataToTable(ui->tableWidget,0,Row ,"GUI-DLL");
				SetDataToTable(ui->tableWidget,1,Row ,DLLFileNames[i]);

				char	*frevision=G->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Revision);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(frevision));
				}
				char	*fregulus=G->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Regulus);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(fregulus));
				}
				char	*fmatch=G->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_IsMatched);
				if(fmatch!=NULL){
					SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(fmatch));
				}
				Row++;
			}
		}
	}

	for(ResultDLL *R=GetLayersBase()->GetResultDLLBase()->GetFirst();R!=NULL;R=R->GetNext()){
		SetDataToTable(ui->tableWidget,0,Row ,"ResultDLL");
		SetDataToTable(ui->tableWidget,1,Row ,R->GetFileName());
		const char *cfp=R->GetInterface()->GetSystemVersion(Ver_Qt);
		if(cfp!=NULL)
			SetDataToTable(ui->tableWidget,2,Row ,QString::fromLocal8Bit(cfp));

		const char *rfp=R->GetInterface()->GetSystemVersion(Ver_Revision);
		if(rfp!=NULL)
			SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(rfp));

		const char *gfp=R->GetInterface()->GetSystemVersion(Ver_Regulus);
		if(gfp!=NULL)
			SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(gfp));

		const char *mfp=R->GetInterface()->GetSystemVersion(Ver_IsMatched);
		if(mfp!=NULL)
			SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(mfp));
		Row++;

		QStringList		DLLFileNames;
		if(R->GetInterface()->GetRelatedDLL(DLLFileNames)==true){
			for(int i=0;i<DLLFileNames.count();i++){
				SetDataToTable(ui->tableWidget,0,Row ,"Result-DLL");
				SetDataToTable(ui->tableWidget,1,Row ,DLLFileNames[i]);

				char	*frevision=R->GetInterface()->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Revision);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(frevision));
				}
				char	*fregulus=R->GetInterface()->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Regulus);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(fregulus));
				}
				char	*fmatch=R->GetInterface()->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_IsMatched);
				if(fmatch!=NULL){
					SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(fmatch));
				}
				Row++;
			}
		}
	}

	for(FilterDLLList *F=GetLayersBase()->GetFilterBank()->GetFirst();F!=NULL;F=F->GetNext()){
		SetDataToTable(ui->tableWidget,0,Row ,"FilterDLL");
		SetDataToTable(ui->tableWidget,1,Row ,F->GetFileName());
		const char *cfp=F->GetSystemVersion(Ver_Qt);
		if(cfp!=NULL)
			SetDataToTable(ui->tableWidget,2,Row ,QString::fromLocal8Bit(cfp));

		const char *rfp=F->GetSystemVersion(Ver_Revision);
		if(rfp!=NULL)
			SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(rfp));

		const char *gfp=F->GetSystemVersion(Ver_Regulus);
		if(gfp!=NULL)
			SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(gfp));

		const char *mfp=F->GetSystemVersion(Ver_IsMatched);
		if(mfp!=NULL)
			SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(mfp));
		Row++;

		QStringList		DLLFileNames;
		if(F->GetRelatedDLL(DLLFileNames)==true){
			for(int i=0;i<DLLFileNames.count();i++){
				SetDataToTable(ui->tableWidget,0,Row ,"Filter-DLL");
				SetDataToTable(ui->tableWidget,1,Row ,DLLFileNames[i]);

				char	*frevision=F->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Revision);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(frevision));
				}
				char	*fregulus=F->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Regulus);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(fregulus));
				}
				char	*fmatch=F->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_IsMatched);
				if(fmatch!=NULL){
					SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(fmatch));
				}
				Row++;
			}
		}
	}

	for(CameraClass *C=CameraPack->GetFirst();C!=NULL;C=C->GetNext()){
		SetDataToTable(ui->tableWidget,0,Row ,"CameraDLL");
		SetDataToTable(ui->tableWidget,1,Row ,C->GetFileName());
		const char *cfp=C->GetInterface()->GetSystemVersion(Ver_Qt);
		if(cfp!=NULL)
			SetDataToTable(ui->tableWidget,2,Row ,QString::fromLocal8Bit(cfp));

		const char *rfp=C->GetInterface()->GetSystemVersion(Ver_Revision);
		if(rfp!=NULL)
			SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(rfp));

		const char *gfp=C->GetInterface()->GetSystemVersion(Ver_Regulus);
		if(gfp!=NULL)
			SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(gfp));

		const char *mfp=C->GetInterface()->GetSystemVersion(Ver_IsMatched);
		if(mfp!=NULL)
			SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(mfp));
		Row++;

		QStringList		DLLFileNames;
		if(C->GetInterface()->GetRelatedDLL(DLLFileNames)==true){
			for(int i=0;i<DLLFileNames.count();i++){
				SetDataToTable(ui->tableWidget,0,Row ,"Camera-DLL");
				SetDataToTable(ui->tableWidget,1,Row ,DLLFileNames[i]);

				char	*frevision=C->GetInterface()->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Revision);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(frevision));
				}
				char	*fregulus=C->GetInterface()->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Regulus);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(fregulus));
				}
				char	*fmatch=C->GetInterface()->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_IsMatched);
				if(fmatch!=NULL){
					SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(fmatch));
				}
				Row++;
			}
		}
	}

	for(PIOClass *I=PIOPack->GetFirst();I!=NULL;I=I->GetNext()){
		SetDataToTable(ui->tableWidget,0,Row ,"PIO-DLL");
		SetDataToTable(ui->tableWidget,1,Row ,I->GetFileName());
		const char *cfp=I->GetSystemVersion(Ver_Qt);
		if(cfp!=NULL)
			SetDataToTable(ui->tableWidget,2,Row ,QString::fromLocal8Bit(cfp));

		const char *rfp=I->GetSystemVersion(Ver_Revision);
		if(rfp!=NULL)
			SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(rfp));

		const char *gfp=I->GetSystemVersion(Ver_Regulus);
		if(gfp!=NULL)
			SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(gfp));

		const char *mfp=I->GetSystemVersion(Ver_IsMatched);
		if(mfp!=NULL)
			SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(mfp));
		Row++;

		QStringList		DLLFileNames;
		if(I->GetRelatedDLL(DLLFileNames)==true){
			for(int i=0;i<DLLFileNames.count();i++){
				SetDataToTable(ui->tableWidget,0,Row ,"PIO-DLL");
				SetDataToTable(ui->tableWidget,1,Row ,DLLFileNames[i]);

				char	*frevision=I->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Revision);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(frevision));
				}
				char	*fregulus=I->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Regulus);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(fregulus));
				}
				char	*fmatch=I->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_IsMatched);
				if(fmatch!=NULL){
					SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(fmatch));
				}
				Row++;
			}
		}
	}

	for(DLLVarOperand *D=SeqVarPack->GetFirst();D!=NULL;D=D->GetNext()){
		SetDataToTable(ui->tableWidget,0,Row ,"Seq-DLL");
		SetDataToTable(ui->tableWidget,1,Row ,D->GetFileName());
		const char *cfp=D->GetSystemVersion(Ver_Qt);
		if(cfp!=NULL)
			SetDataToTable(ui->tableWidget,2,Row ,QString::fromLocal8Bit(cfp));

		const char *rfp=D->GetSystemVersion(Ver_Revision);
		if(rfp!=NULL)
			SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(rfp));

		const char *gfp=D->GetSystemVersion(Ver_Regulus);
		if(gfp!=NULL)
			SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(gfp));

		const char *mfp=D->GetSystemVersion(Ver_IsMatched);
		if(mfp!=NULL)
			SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(mfp));
		Row++;

		QStringList		DLLFileNames;
		if(D->GetRelatedDLL(DLLFileNames)==true){
			for(int i=0;i<DLLFileNames.count();i++){
				SetDataToTable(ui->tableWidget,0,Row ,"Seqeuce-DLL");
				SetDataToTable(ui->tableWidget,1,Row ,DLLFileNames[i]);

				char	*frevision=D->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Revision);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(frevision));
				}
				char	*fregulus=D->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Regulus);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(fregulus));
				}
				char	*fmatch=D->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_IsMatched);
				if(fmatch!=NULL){
					SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(fmatch));
				}
				Row++;
			}
		}
	}

	for(LightAccessList *G=LightPack->GetFirst();G!=NULL;G=G->GetNext()){
		SetDataToTable(ui->tableWidget,0,Row ,"LightDLL");
		SetDataToTable(ui->tableWidget,1,Row ,G->GetFileName());
		const char *cfp=G->GetInterface()->GetSystemVersion(Ver_Qt);
		if(cfp!=NULL)
			SetDataToTable(ui->tableWidget,2,Row ,QString::fromLocal8Bit(cfp));

		const char *rfp=G->GetInterface()->GetSystemVersion(Ver_Revision);
		if(rfp!=NULL)
			SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(rfp));

		const char *gfp=G->GetInterface()->GetSystemVersion(Ver_Regulus);
		if(gfp!=NULL)
			SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(gfp));

		const char *mfp=G->GetInterface()->GetSystemVersion(Ver_IsMatched);
		if(mfp!=NULL)
			SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(mfp));
		Row++;

		QStringList		DLLFileNames;
		if(G->GetInterface()->GetRelatedDLL(DLLFileNames)==true){
			for(int i=0;i<DLLFileNames.count();i++){
				SetDataToTable(ui->tableWidget,0,Row ,"Light-DLL");
				SetDataToTable(ui->tableWidget,1,Row ,DLLFileNames[i]);

				char	*frevision=G->GetInterface()->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Revision);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(frevision));
				}
				char	*fregulus=G->GetInterface()->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Regulus);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(fregulus));
				}
				char	*fmatch=G->GetInterface()->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_IsMatched);
				if(fmatch!=NULL){
					SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(fmatch));
				}
				Row++;
			}
		}
	}

	for(RunnerObjDLL *R=EVMap->GetFirst();R!=NULL;R=R->GetNext()){
		SetDataToTable(ui->tableWidget,0,Row ,"ExecuteVisualizer");
		SetDataToTable(ui->tableWidget,1,Row ,R->GetFileName());
		const char *cfp=R->GetSystemVersion(Ver_Qt);
		if(cfp!=NULL)
			SetDataToTable(ui->tableWidget,2,Row ,QString::fromLocal8Bit(cfp));

		const char *rfp=R->GetSystemVersion(Ver_Revision);
		if(rfp!=NULL)
			SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(rfp));

		const char *gfp=R->GetSystemVersion(Ver_Regulus);
		if(gfp!=NULL)
			SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(gfp));

		const char *mfp=R->GetSystemVersion(Ver_IsMatched);
		if(mfp!=NULL)
			SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(mfp));
		Row++;

		QStringList		DLLFileNames;
		if(R->GetRelatedDLL(DLLFileNames)==true){
			for(int i=0;i<DLLFileNames.count();i++){
				SetDataToTable(ui->tableWidget,0,Row ,"EV-DLL");
				SetDataToTable(ui->tableWidget,1,Row ,DLLFileNames[i]);

				char	*frevision=R->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Revision);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,3,Row ,QString::fromLocal8Bit(frevision));
				}
				char	*fregulus=R->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_Regulus);
				if(frevision!=NULL){
					SetDataToTable(ui->tableWidget,4,Row ,QString::fromLocal8Bit(fregulus));
				}
				char	*fmatch	=R->GetRelatedDLLSystemVersion(DLLFileNames[i] ,Ver_IsMatched);
				if(fmatch!=NULL){
					SetDataToTable(ui->tableWidget,5,Row ,QString::fromLocal8Bit(fmatch));
				}
				Row++;
			}
		}
	}
	GetLayersBase()->CloseInformed();
}

ShowSystemVersionDialog::~ShowSystemVersionDialog()
{
	delete	EVMap;
	EVMap=NULL;

    delete ui;
}

void ShowSystemVersionDialog::on_pushButtonSaveCSV_clicked()
{
	QString FileaName=QFileDialog::getSaveFileName( 0, "Save CSV", QString()
												, "CSV (*.csv);;All files (*.*)");
	if(FileaName.isEmpty()==false){
		QFile	File(FileaName);
		if(File.open(QIODevice::WriteOnly)==true){
			SaveCSV(&File,ui->tableWidget);
		}
	}
}

void ShowSystemVersionDialog::on_pushButtonClose_clicked()
{
	close();
}
