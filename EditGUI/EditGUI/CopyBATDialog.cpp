#include "CopyBATDialog.h"
#include "ui_CopyBATDialog.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "EditGui.h"
#include "XAlgorithmBase.h"
#include "XGUIInterfaceDLL.h"
#include "Regulus64System.h"

CopyBATDialog::CopyBATDialog(EditGUI *eP ,LayersBase *base, QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),EditGUIParent(eP),
    ui(new Ui::CopyBATDialog)
{
    ui->setupUi(this);

	ui->lineEditGlobalDat	->setText(eP->PathToOpenedFile);
	ui->lineEditGUI			->setText(QCoreApplication::applicationDirPath ()+::GetSeparator()+QString(DefGUIPath));
	ui->lineEditAlgorithm	->setText(QCoreApplication::applicationDirPath ()+::GetSeparator()+QString(DefAlgorithmPath));
	ui->lineEditPIOFile				->setText(GetParamGlobal()->IODLL_FileName	);
	QString	CameraFileName	=GetParamGlobal()->CameraDLL_FileName;
	if(GetParamGlobal()->CameraDLL_FileName2.isEmpty()==false){
		if(CameraFileName.isEmpty()==false)
			CameraFileName+=/**/";";
		CameraFileName+=GetParamGlobal()->CameraDLL_FileName2;
	}
	if(GetParamGlobal()->CameraDLL_FileName3.isEmpty()==false){
		if(CameraFileName.isEmpty()==false)
			CameraFileName+=/**/";";
		CameraFileName+=GetParamGlobal()->CameraDLL_FileName3;
	}
	if(GetParamGlobal()->CameraDLL_FileName4.isEmpty()==false){
		if(CameraFileName.isEmpty()==false)
			CameraFileName+=/**/";";
		CameraFileName+=GetParamGlobal()->CameraDLL_FileName4;
	}
	ui->lineEditCameraFile			->setText(CameraFileName		);

	QString	LightFileName	=GetParamGlobal()->LightDLLFileName;
	if(GetParamGlobal()->LightDLLFileName2.isEmpty()==false){
		if(LightFileName.isEmpty()==false)
			LightFileName+=/**/";";
		LightFileName+=GetParamGlobal()->LightDLLFileName2;
	}
	if(GetParamGlobal()->LightDLLFileName3.isEmpty()==false){
		if(LightFileName.isEmpty()==false)
			LightFileName+=/**/";";
		LightFileName+=GetParamGlobal()->LightDLLFileName3;
	}
	if(GetParamGlobal()->LightDLLFileName4.isEmpty()==false){
		if(LightFileName.isEmpty()==false)
			LightFileName+=/**/";";
		LightFileName+=GetParamGlobal()->LightDLLFileName4;
	}
	ui->lineEditLightFile			->setText(LightFileName			);
	//ui->lineEditSequenceFile		->setText(SeqenceDLLFileName	);

	QString	GeneralStockerFileName	=GetParamGlobal()->GeneralStockerFileName1;
	if(GetParamGlobal()->GeneralStockerFileName2.isEmpty()==false){
		if(GeneralStockerFileName.isEmpty()==false)
			GeneralStockerFileName+=/**/";";
		GeneralStockerFileName+=GetParamGlobal()->GeneralStockerFileName2;
	}
	if(GetParamGlobal()->GeneralStockerFileName3.isEmpty()==false){
		if(GeneralStockerFileName.isEmpty()==false)
			GeneralStockerFileName+=/**/";";
		GeneralStockerFileName+=GetParamGlobal()->GeneralStockerFileName3;
	}
	if(GetParamGlobal()->GeneralStockerFileName4.isEmpty()==false){
		if(GeneralStockerFileName.isEmpty()==false)
			GeneralStockerFileName+=/**/";";
		GeneralStockerFileName+=GetParamGlobal()->GeneralStockerFileName4;
	}
	ui->lineEditGeneralStockerFile	->setText(GeneralStockerFileName);
	ui->lineEditFilter				->setText(QCoreApplication::applicationDirPath ()+::GetSeparator()+GetParamGlobal()->FilterDLLPath	);
	ui->lineEditResultFile			->setText(QCoreApplication::applicationDirPath ()+::GetSeparator()+GetParamGlobal()->ResultDLLFileName	);

	ui->tableWidgetAdditional	->setColumnWidth(0,250);
	ui->tableWidgetAdditional	->setColumnWidth(1,100);
}

CopyBATDialog::~CopyBATDialog()
{
    delete ui;
}

void CopyBATDialog::on_pushButtonSelectGlobalDat_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(NULL
												, QString(tr("Load Global.dat"))
												,QCoreApplication::applicationDirPath ()
												, QString(/**/"Global.dat File (Global.dat);;*.dat File (*.dat);;All files (*.*)"));
	if(FileName.isEmpty()==false){
		QFile	F(FileName);
		if(F.open(QIODevice::ReadOnly)==true){
			ui->lineEditGlobalDat->setText(FileName);
			GetLayersBase()->GetParamGlobal()->LoadParam(&F);
			GetLayersBase()->LoadFilterDef();
			ShowParam();
		}
	}
}

void CopyBATDialog::on_pushButtonSelectBATFile_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName(NULL
												, QString(tr("Save BAT file"))
												, QCoreApplication::applicationDirPath ()
												, QString(/**/"Bat File (*.bat);;All files (*.*)"));
	if(FileName.isEmpty()==false){
		ui->lineEditBATFile->setText(FileName);
	}
}

QString	MakeForText(QString &Str)
{
	return Str.replace(/**/"/",/**/"\\");
}

void	MakeCopy(QTextStream &Str,const QString &text,const QString &target)
{
	QStringList	List=text.split(';');
	for(int i=0;i<List.count();i++){
		if(target.isEmpty()==true){
			Str<<QString("copy ")<<MakeForText(List[i])<<"\r\n";
		}
		else{
			Str<<QString("copy ")<<MakeForText(List[i])<<QString(/**/" ")<<target<<"\r\n";
		}
	}
}

void CopyBATDialog::on_pushButtonMakeBAT_clicked()
{
	QString	GlobalFileName			=ui->lineEditGlobalDat			->text();
	QString	GUIPath					=ui->lineEditGUI				->text();
	QString	AlgorithmPath			=ui->lineEditAlgorithm			->text();
	QString	PIOFileName				=ui->lineEditPIOFile			->text();
	QString	CameraFileName			=ui->lineEditCameraFile			->text();
	QString	LightFileName			=ui->lineEditLightFile			->text();
	QString	SeqenceDLLFileName		=ui->lineEditSequenceFile		->text();
	QString	GeneralStockerFileName	=ui->lineEditGeneralStockerFile	->text();
	QString	FilterPath				=ui->lineEditFilter				->text();
	QString	ResultFileName			=ui->lineEditResultFile			->text();
	QString	BatFileName				=ui->lineEditBATFile			->text();
	bool	ModeInspectionPlayer	=ui->checkBoxInspectionPlayer	->isChecked();
	bool	ModeInspectionEditor	=ui->checkBoxInspectionEditor	->isChecked();
	bool	ModeRepairGUIMain		=ui->checkBoxRepairGUIMain		->isChecked();

	QString CurrentPath=QCoreApplication::applicationDirPath ();
	//QString	FileName=QFileDialog::getSaveFileName ( NULL, "Make BAT file", QString()
	//											, /**/"Bat (*.bat)");
	QFile	File(BatFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		QTextStream	Str(&File);

		Str<<QString("copy ")<<MakeForText(GlobalFileName)<<"\r\n";
		Str<</**/"md PluginDLL\r\n";
		if(PIOFileName.isEmpty()==false){
			QFileInfo	FInfo(PIOFileName);
			MakeCopy(Str,FInfo.absoluteFilePath()	,DefPluginDLLPath);
		}
		if(CameraFileName.isEmpty()==false){
			QFileInfo	FInfo(CameraFileName);
			MakeCopy(Str,FInfo.absoluteFilePath()	,DefPluginDLLPath);
		}
		if(LightFileName.isEmpty()==false){
			QFileInfo	FInfo(LightFileName);
			MakeCopy(Str,FInfo.absoluteFilePath()	,DefPluginDLLPath);
		}
		if(SeqenceDLLFileName.isEmpty()==false){
			QFileInfo	FInfo(SeqenceDLLFileName);
			MakeCopy(Str,FInfo.absoluteFilePath()	,/**/"");
		}
		if(GeneralStockerFileName.isEmpty()==false){
			QFileInfo	FInfo(GeneralStockerFileName);
			MakeCopy(Str,FInfo.absoluteFilePath()	,/**/"");
		}
		if(ResultFileName.isEmpty()==false){
			QFileInfo	FInfo(ResultFileName);
			MakeCopy(Str,FInfo.absoluteFilePath()	,/**/"");
		}

		Str<</**/"md GUI\r\n";
		for(GUIItemInstance *c=GetLayersBase()->GetEntryPoint()->GetGUIInstancePack()->NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext()){
			if(c->DLLAccess!=NULL){
				QFileInfo	FInfo(c->DLLAccess->FileName);
				QString	GUIFileName=FInfo.absoluteFilePath();
				Str<<QString("copy ")<<MakeForText(GUIFileName)<<" GUI\r\n";
			}
		}

		{
			Str<</**/"md Filter\r\n";
			QFileInfo	FilterInfo(FilterPath);
			QString	s=FilterInfo.absoluteFilePath()+QString("\\*.")+GetDynamicFileExt();
			QString	FilterStr=MakeForText(s);
			Str<<QString("copy ")<<FilterStr<<QString(" Filter\r\n");
		}

		RootNameListContainer AlgoList;
		for(GUIItemInstance *c=GetLayersBase()->GetEntryPoint()->GetGUIInstancePack()->NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext()){
			if(c->DLLAccess!=NULL){
				RootNameListContainer List;
				c->DLLAccess->EntryAlgorithm(List);
				for(RootNameList *a=List.GetFirst();a!=NULL;a=a->GetNext()){
					RootNameList *b;
					for(b=AlgoList.GetFirst();b!=NULL;b=b->GetNext()){
						if(*a==*b){
							goto	PNext;
						}
					}
PNext:;
					if(b==NULL){
						AlgoList.AppendList(new RootNameList(a->DLLRoot, a->DLLName));
					}
				}
			}
		}
		Str<</**/"md Algorithm\r\n";
		for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			for(RootNameList *b=AlgoList.GetFirst();b!=NULL;b=b->GetNext()){
				if(L->GetDLLRoot()==b->DLLRoot && L->GetDLLName()==b->DLLName){
					QFileInfo	FInfo(L->GetFileName());
					QString	AlgoFileName=FInfo.absoluteFilePath();
					Str<<QString("copy ")<<MakeForText(AlgoFileName)<<" Algorithm\r\n";
				}
			}
		}

		{
			const	char	*DLLList[]	={
									"cryptopp.dll"
									,"hidapi.dll"	
									,"libfftw-3.3.dll"	
									,"libfftwf-3.3.dll"	
									,"LibPNGDLL.dll"	
									,"libxl.dll"	
									,"NetworkDrive.dll"	
									,"ServiceForDBLib.dll"	
									,"ShutDownDLL.dll"	
									,"AutoStartList.exe"	
									,"AutoStartPlayer.exe"	
									,"Booter.exe"	
									,"ChangeAttribute.exe"	
									,"ChangeServer.exe"	
									,"CloseProcess.exe"	
									,"ConvertPixImage.exe"	
									,"CopyMultiple.exe"	
									,"Data management.exe"	
									,"DelayExe.exe"	
									,"Delete.exe"	
									,"DiskManager.exe"	
									,"DLLChecker.exe"	
									,"EditAnyDataInLibrary.exe"	
									,"EditGlobalOnMaster.exe"	
									,"EditGUI.exe"	
									,"EditParameter.exe"	
									,"EditSequence.exe"	
									,"EditStatusComment.exe"	
									,"FileRegistryEditor.exe"	
									,"ForceRebooter.exe"	
									,"HaspViewer.exe"	
									,"JDTUnpacker.exe"	
									,"LanguageManager.exe"	
									,"LanguageMergeXLSX.exe"	
									,"MakeMasterReport.exe"	
									,"ManageMasterConnection.exe"	
									,"Messager.exe"	
									,"ReportDisk.exe"	
									,"RemoteLightController.exe"	
									,"RemoteLightExecuter.exe"	
									,"ResultDataManager.exe"	
									,"SlaveIndicator.exe"	
									,"TesterLightDLL.exe"	
									,"XMLExplorer.exe"	
									,"XMLServerV3.exe"	
									,"WatchdogRebooter.exe"	
									,"PIOViewer.exe"	
									,"Datamanagement.lng"	
									,"EditParameter.lng"	
									,"InspectionGeneral.lng"	
									,"LangSolution.lsn"	
									,"Regulus64Local.DDL"	
									,"Regulus64LocalProc.DDL"
									,"ShrinkingTable.dat"
									,NULL
								};

			for(int i=0;DLLList[i]!=NULL;i++){
				QFileInfo	FInfo(DLLList[i]);
				QString	s=FInfo.absoluteFilePath();
				QString	FStr=MakeForText(s);
				Str<<QString("copy ")<<FStr<<QString("\r\n");
			}
		}
		for(AdditionalFile *a=AdditionalFiles.GetFirst();a!=NULL;a=a->GetNext()){
			QFileInfo	FInfo(a->SrcFile);
			QString	s=FInfo.absoluteFilePath();
			QString	FStr=MakeForText(s);
			if(a->Dest.isEmpty()==true){
				Str<<QString("copy ")<<FStr<<QString("\r\n");
			}
			else{
				Str<<QString("copy ")<<FStr<<QString(/**/" ")+a->Dest+QString("\r\n");
			}
		}
		bool	ModeInspectionPlayer	=ui->checkBoxInspectionPlayer	->isChecked();
		bool	ModeInspectionEditor	=ui->checkBoxInspectionEditor	->isChecked();
		bool	ModeRepairGUIMain		=ui->checkBoxRepairGUIMain		->isChecked();
		if(ModeInspectionPlayer==true){
			QFileInfo	FInfo(/**/"InspectionPlayer.exe");
			QString	s=FInfo.absoluteFilePath();
			QString	FStr=MakeForText(s);
			Str<<QString("copy ")<<FStr<<QString("\r\n");
		}
		if(ModeInspectionEditor==true){
			QFileInfo	FInfo(/**/"InspectionEditor.exe");
			QString	s=FInfo.absoluteFilePath();
			QString	FStr=MakeForText(s);
			Str<<QString("copy ")<<FStr<<QString("\r\n");
		}
		if(ModeRepairGUIMain==true){
			QFileInfo	FInfo(/**/"RepairGUIMain.exe");
			QString	s=FInfo.absoluteFilePath();
			QString	FStr=MakeForText(s);
			Str<<QString("copy ")<<FStr<<QString("\r\n");
		}
	}
}

void CopyBATDialog::on_pushButtonCancel_clicked()
{
	close();
}

void CopyBATDialog::ShowParam(void)
{
	ui->lineEditGUI			->setText(DefGUIPath);
	ui->lineEditAlgorithm	->setText(DefAlgorithmPath);
}

void CopyBATDialog::on_pushButtonSelecGUIFolder_clicked()
{
	QString	Path=QFileDialog::getExistingDirectory (0
									, QString(tr("GUI path"))
									, QCoreApplication::applicationDirPath ()+::GetSeparator()+QString(DefGUIPath)
									);
	if(Path.isEmpty()==false){
		ui->lineEditGUI->setText(Path);
	}
}

void CopyBATDialog::on_pushButtonSelectAlgorithmFolder_clicked()
{
	QString	Path=QFileDialog::getExistingDirectory (0
									, QString(tr("Algorithm path"))
									, QCoreApplication::applicationDirPath ()+::GetSeparator()+QString(DefGUIPath)
									);
	if(Path.isEmpty()==false){
		ui->lineEditAlgorithm->setText(Path);
	}
}

void CopyBATDialog::on_pushButtonSelectPIOFile_clicked()
{
	QStringList	List=QFileDialog::getOpenFileNames ( 0
							, QString(tr("PIO files"))
							,QCoreApplication::applicationDirPath ()+::GetSeparator()+QString(DefPluginDLLPath)
							, "DLL (*.dll *.so)");
	if(List.count()!=0){
		QString	Str;
		for(int i=0;i<List.count();i++){
			Str+=List[i];
			if(i<List.count()-1)
				Str+=/**/";";
		}
		ui->lineEditPIOFile->setText(Str);
	}
}

void CopyBATDialog::on_pushButtonSelectCameraFile_clicked()
{
	QStringList	List=QFileDialog::getOpenFileNames ( 0
							, QString(tr("Camera files"))
							,QCoreApplication::applicationDirPath ()+::GetSeparator()+QString(DefPluginDLLPath)
							, "DLL (*.dll *.so)");
	if(List.count()!=0){
		QString	Str;
		for(int i=0;i<List.count();i++){
			Str+=List[i];
			if(i<List.count()-1)
				Str+=/**/";";
		}
		ui->lineEditCameraFile->setText(Str);
	}
}

void CopyBATDialog::on_pushButtonSelectLightFile_clicked()
{
	QStringList	List=QFileDialog::getOpenFileNames ( 0
							, QString(tr("Light files"))
							,QCoreApplication::applicationDirPath ()+::GetSeparator()+QString(DefPluginDLLPath)
							, "DLL (*.dll *.so)");
	if(List.count()!=0){
		QString	Str;
		for(int i=0;i<List.count();i++){
			Str+=List[i];
			if(i<List.count()-1)
				Str+=/**/";";
		}
		ui->lineEditLightFile->setText(Str);
	}
}

void CopyBATDialog::on_pushButtonSelectSequenceDLL_clicked()
{
	QStringList	List=QFileDialog::getOpenFileNames ( 0
							, QString(tr("SequenceDLL files"))
							,QCoreApplication::applicationDirPath ()
							, "DLL (*.dll *.so)");
	if(List.count()!=0){
		QString	Str;
		for(int i=0;i<List.count();i++){
			Str+=List[i];
			if(i<List.count()-1)
				Str+=/**/";";
		}
		ui->lineEditSequenceFile->setText(Str);
	}
}

void CopyBATDialog::on_pushButtonSelectGeneralStockers_clicked()
{
	QStringList	List=QFileDialog::getOpenFileNames ( 0
							, QString(tr("GeneralStocker files"))
							,QCoreApplication::applicationDirPath ()
							, "DLL (*.dll *.so)");
	if(List.count()!=0){
		QString	Str;
		for(int i=0;i<List.count();i++){
			Str+=List[i];
			if(i<List.count()-1)
				Str+=/**/";";
		}
		ui->lineEditGeneralStockerFile->setText(Str);
	}
}

void CopyBATDialog::on_pushButtonSelectFilterPath_clicked()
{
	QString	Path=QFileDialog::getExistingDirectory (0
									, QString(tr("Filter path"))
									, QCoreApplication::applicationDirPath ()+::GetSeparator()+GetParamGlobal()->FilterDLLPath
									);
	if(Path.isEmpty()==false){
		ui->lineEditFilter->setText(Path);
	}
}

void CopyBATDialog::on_pushButtonSelectResultDLL_clicked()
{
	QStringList	List=QFileDialog::getOpenFileNames ( 0
							, QString(tr("ResultDLL files"))
							,QCoreApplication::applicationDirPath ()
							, "DLL (*.dll *.so)");
	if(List.count()!=0){
		QString	Str;
		for(int i=0;i<List.count();i++){
			Str+=List[i];
			if(i<List.count()-1)
				Str+=/**/";";
		}
		ui->lineEditResultFile->setText(Str);
	}
}

void CopyBATDialog::on_pushButtonSaveSetting_clicked()
{
	QString FileName=QFileDialog::getSaveFileName ( NULL
									, QString(tr("Save setting"))
									,QCoreApplication::applicationDirPath ()
									,"Conf (*.conf);;All files (*.*)");

	if(FileName.isEmpty()==false){
		QFile	F(FileName);
		if(F.open(QIODevice::WriteOnly)==true){
			SaveSetting(&F);
		}
	}
}

void CopyBATDialog::GetAdditionalFilesFromWindow(void)
{
	AdditionalFiles.RemoveAll();
	for(int row=0;row<ui->tableWidgetAdditional->rowCount();row++){
		QString	s=::GetDataToTable(ui->tableWidgetAdditional,0,row);
		QString	d=::GetDataToTable(ui->tableWidgetAdditional,1,row);
		if(s.isEmpty()==false){
			AdditionalFiles.AppendList(new AdditionalFile(s,d));
		}
	}
}

void CopyBATDialog::SetAdditionalFilesToWindow(void)
{
	ui->tableWidgetAdditional->setRowCount(AdditionalFiles.GetCount());
	int	Row=0;
	for(AdditionalFile *a=AdditionalFiles.GetFirst();a!=NULL;a=a->GetNext()){
		::SetDataToTable(ui->tableWidgetAdditional ,0,Row ,a->SrcFile);
		::SetDataToTable(ui->tableWidgetAdditional ,1,Row ,a->Dest,Qt::ItemIsEditable);
		Row++;
	}
}

bool CopyBATDialog::SaveSetting(QIODevice *f)
{
	int32	Ver=2;
	if(::Save(f,Ver)==false)
		return false;
	QString	GlobalFileName			=ui->lineEditGlobalDat			->text();
	QString	GUIPath					=ui->lineEditGUI				->text();
	QString	AlgorithmPath			=ui->lineEditAlgorithm			->text();
	QString	PIOFileName				=ui->lineEditPIOFile			->text();
	QString	CameraFileName			=ui->lineEditCameraFile			->text();
	QString	LightFileName			=ui->lineEditLightFile			->text();
	QString	SeqenceDLLFileName		=ui->lineEditSequenceFile		->text();
	QString	GeneralStockerFileName	=ui->lineEditGeneralStockerFile	->text();
	QString	FilterPath				=ui->lineEditFilter				->text();
	QString	ResultFileName			=ui->lineEditResultFile			->text();
	QString	BatFileName				=ui->lineEditBATFile			->text();
	bool	ModeInspectionPlayer	=ui->checkBoxInspectionPlayer	->isChecked();
	bool	ModeInspectionEditor	=ui->checkBoxInspectionEditor	->isChecked();
	bool	ModeRepairGUIMain		=ui->checkBoxRepairGUIMain		->isChecked();

	if(::Save(f,GlobalFileName)==false)
		return false;
	if(::Save(f,GUIPath)==false)
		return false;
	if(::Save(f,AlgorithmPath)==false)
		return false;
	if(::Save(f,PIOFileName)==false)
		return false;
	if(::Save(f,CameraFileName)==false)
		return false;
	if(::Save(f,LightFileName)==false)
		return false;
	if(::Save(f,SeqenceDLLFileName)==false)
		return false;
	if(::Save(f,GeneralStockerFileName)==false)
		return false;
	if(::Save(f,FilterPath)==false)
		return false;
	if(::Save(f,ResultFileName)==false)
		return false;
	if(::Save(f,BatFileName)==false)
		return false;

	GetAdditionalFilesFromWindow();
	if(AdditionalFiles.Save(f)==false)
		return false;

	if(::Save(f,ModeInspectionPlayer)==false)
		return false;
	if(::Save(f,ModeInspectionEditor)==false)
		return false;
	if(::Save(f,ModeRepairGUIMain)==false)
		return false;

	return true;
}

void CopyBATDialog::on_pushButtonLoadSetting_clicked()
{
	QString FileName=QFileDialog::getOpenFileName ( NULL
									, QString(tr("Save setting"))
									,QCoreApplication::applicationDirPath ()
									,"Conf (*.conf);;All files (*.*)");

	if(FileName.isEmpty()==false){
		QFile	F(FileName);
		if(F.open(QIODevice::ReadOnly)==true){
			LoadSetting(&F);
		}
	}
}

bool CopyBATDialog::LoadSetting(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	QString	GlobalFileName			;
	QString	GUIPath					;
	QString	AlgorithmPath			;
	QString	PIOFileName				;
	QString	CameraFileName			;
	QString	LightFileName			;
	QString	SeqenceDLLFileName		;
	QString	GeneralStockerFileName	;
	QString	FilterPath				;
	QString	ResultFileName			;
	QString	BatFileName				;

	if(::Load(f,GlobalFileName)==false)
		return false;
	if(::Load(f,GUIPath)==false)
		return false;
	if(::Load(f,AlgorithmPath)==false)
		return false;
	if(::Load(f,PIOFileName)==false)
		return false;
	if(::Load(f,CameraFileName)==false)
		return false;
	if(::Load(f,LightFileName)==false)
		return false;
	if(::Load(f,SeqenceDLLFileName)==false)
		return false;
	if(::Load(f,GeneralStockerFileName)==false)
		return false;
	if(::Load(f,FilterPath)==false)
		return false;
	if(::Load(f,ResultFileName)==false)
		return false;
	if(::Load(f,BatFileName)==false)
		return false;

	if(AdditionalFiles.Load(f)==false)
		return false;

	ui->lineEditGlobalDat			->setText(GlobalFileName		);
	ui->lineEditGUI					->setText(GUIPath				);
	ui->lineEditAlgorithm			->setText(AlgorithmPath			);
	ui->lineEditPIOFile				->setText(PIOFileName			);
	ui->lineEditCameraFile			->setText(CameraFileName		);
	ui->lineEditLightFile			->setText(LightFileName			);
	ui->lineEditSequenceFile		->setText(SeqenceDLLFileName	);
	ui->lineEditGeneralStockerFile	->setText(GeneralStockerFileName);
	ui->lineEditFilter				->setText(FilterPath			);
	ui->lineEditResultFile			->setText(ResultFileName		);
	ui->lineEditBATFile				->setText(BatFileName			);

	SetAdditionalFilesToWindow();

	if(Ver>=2){
		bool	ModeInspectionPlayer;
		bool	ModeInspectionEditor;
		bool	ModeRepairGUIMain	;
		if(::Load(f,ModeInspectionPlayer)==false)
			return false;
		if(::Load(f,ModeInspectionEditor)==false)
			return false;
		if(::Load(f,ModeRepairGUIMain)==false)
			return false;
		ui->checkBoxInspectionPlayer	->setChecked(ModeInspectionPlayer);
		ui->checkBoxInspectionEditor	->setChecked(ModeInspectionEditor);
		ui->checkBoxRepairGUIMain		->setChecked(ModeRepairGUIMain	);
	}
	return true;
}
void CopyBATDialog::on_pushButtonPlus_clicked()
{
	QStringList List=QFileDialog::getOpenFileNames (NULL, "Additional files", QString()
								, /**/"dll (*.dll);;dat (*.dat);;GUI (*.gui);;all files (*.*)");
	int	CurrentRow=ui->tableWidgetAdditional->rowCount();
	ui->tableWidgetAdditional->setRowCount(CurrentRow+List.count());

	for(int i=0;i<List.count();i++){
		QFileInfo	FInfo(List[i]);
		::SetDataToTable(ui->tableWidgetAdditional ,0 ,CurrentRow ,List[i]);
		::SetDataToTable(ui->tableWidgetAdditional ,1,CurrentRow ,/**/"",Qt::ItemIsEditable);
		CurrentRow++;
	}
}

void CopyBATDialog::on_pushButtonMinus_clicked()
{
	int	Row=ui->tableWidgetAdditional->currentRow();
	if(Row<0)
		return;
	ui->tableWidgetAdditional->removeRow (Row);
}
