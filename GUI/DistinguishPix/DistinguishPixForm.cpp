#include "DistinguishPixFormResource.h"
#include "DistinguishPix.h"
#include "DistinguishPixForm.h"
#include "ui_DistinguishPixForm.h"
#include "LoadImageTargetButton.h"
#include <QFileDialog>
#include <QDir>
#include "XGeneralFunc.h"
#include "ButtonLoadBmpJpg.h"
#include "XDataInLayer.h"
#include "XRememberer.h"

//===============================================================

DistinguishPixForm::DistinguishPixForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent)
	,ButtonNG1(NULL)
	,ButtonNG2(NULL)
	,ButtonNG3(NULL)
	,ButtonNG4(NULL)
    ,ui(new Ui::DistinguishPixForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	FileDim		=NULL;
	FileDimNumb	=0;

	NG1Str=/**/"NG 1";
	NG2Str=/**/"NG 2";
	NG3Str=/**/"NG 3";
	NG4Str=/**/"NG 4";

	NG1Color	=Qt::red;
	NG2Color	=Qt::magenta;
	NG3Color	=Qt::darkRed;
	NG4Color	=Qt::darkMagenta;
	PhaseToLoad	=-1;

	ui->lineEditFolderName	->setText(ControlRememberer::GetString(ui->lineEditFolderName));
}

DistinguishPixForm::~DistinguishPixForm()
{
    delete ui;
	if(ButtonNG1!=NULL)
		delete	ButtonNG1;
	if(ButtonNG2!=NULL)
		delete	ButtonNG2;
	if(ButtonNG3!=NULL)
		delete	ButtonNG3;
	if(ButtonNG4!=NULL)
		delete	ButtonNG4;
}

void	DistinguishPixForm::Prepare(void)
{
	if(NG1Str.isEmpty()==false){
		if(ButtonNG1==NULL){
			ButtonNG1=new mtPushButtonColored(NG1Color,this);
			ButtonNG1->setGeometry(ui->pushButtonNG1->geometry());
			connect(ButtonNG1,SIGNAL(clicked()),this,SLOT(on_pushButtonNG1_clicked()));
		}
		ButtonNG1->setText(NG1Str);
		ButtonNG1->show();
	}
	else if(ButtonNG1!=NULL){
		delete	ButtonNG1;
		ButtonNG1=NULL;
	}
	ui->pushButtonNG1->setVisible(false);

	if(NG2Str.isEmpty()==false){
		if(ButtonNG2==NULL){
			ButtonNG2=new mtPushButtonColored(NG2Color,this);
			ButtonNG2->setGeometry(ui->pushButtonNG2->geometry());
			connect(ButtonNG2,SIGNAL(clicked()),this,SLOT(on_pushButtonNG2_clicked()));
		}
		ButtonNG2->setText(NG2Str);
		ButtonNG2->show();
	}
	else if(ButtonNG2!=NULL){
		delete	ButtonNG2;
		ButtonNG2=NULL;
	}
	ui->pushButtonNG2->setVisible(false);

	if(NG3Str.isEmpty()==false){
		if(ButtonNG3==NULL){
			ButtonNG3=new mtPushButtonColored(NG3Color,this);
			ButtonNG3->setGeometry(ui->pushButtonNG3->geometry());
			connect(ButtonNG3,SIGNAL(clicked()),this,SLOT(on_pushButtonNG3_clicked()));
		}
		ButtonNG3->setText(NG3Str);
		ButtonNG3->show();
	}
	else if(ButtonNG3!=NULL){
		delete	ButtonNG3;
		ButtonNG3=NULL;
	}
	ui->pushButtonNG3->setVisible(false);

	if(NG4Str.isEmpty()==false){
		if(ButtonNG4==NULL){
			ButtonNG4=new mtPushButtonColored(NG4Color,this);
			ButtonNG4->setGeometry(ui->pushButtonNG4->geometry());
			connect(ButtonNG4,SIGNAL(clicked()),this,SLOT(on_pushButtonNG4_clicked()));
		}
		ButtonNG4->setText(NG4Str);
		ButtonNG4->show();
	}
	else if(ButtonNG4!=NULL){
		delete	ButtonNG4;
		ButtonNG4=NULL;
	}
	ui->pushButtonNG4->setVisible(false);
}

int	FileListLeafPointerFunc(const void *a ,const void *b)
{
	FileListLeafPointer	*pa=((FileListLeafPointer **)a)[0];
	FileListLeafPointer	*pb=((FileListLeafPointer **)b)[0];

	if(pa->Pointer->FileName>pb->Pointer->FileName)
		return -1;
	if(pa->Pointer->FileName<pb->Pointer->FileName)
		return 1;
	return 0;
}


void	DistinguishPixForm::ShowList(QString &FolderName)
{
	if(FileDim!=NULL){
		delete	[]FileDim;
	}
	int	N=FileData.GetCount();
	FileDim=new FileListLeafPointer *[N];
	FileDimNumb=0;
	QString	UFolderName=FolderName.toUpper();
	for(FileListLeaf *a=FileData.GetFirst();a!=NULL;a=a->GetNext()){
		if(UFolderName==a->UFolderName){
			FileDim[FileDimNumb]=new FileListLeafPointer(a);
			FileDimNumb++;
		}
	}
	QSort(FileDim,FileDimNumb,sizeof(FileListLeafPointer *),FileListLeafPointerFunc);

	ui->listWidget	->clear();
	for(int i=0;i<FileDimNumb;i++){
		ui->listWidget	->addItem(FileDim[i]->Pointer->FileName);
	}
	for(int i=0;i<FileDimNumb;i++){
		QListWidgetItem	*Item=ui->listWidget->item(i);
		if(FileDim[i]->Pointer->Judgement==0)
			Item->setBackground(QBrush(Qt::white));
		else if(FileDim[i]->Pointer->Judgement==1)
			Item->setBackground(QBrush(Qt::green));
		else if(FileDim[i]->Pointer->Judgement==2)
			Item->setBackground(QBrush(NG1Color));
		else if(FileDim[i]->Pointer->Judgement==3)
			Item->setBackground(QBrush(NG2Color));
		else if(FileDim[i]->Pointer->Judgement==4)
			Item->setBackground(QBrush(NG3Color));
		else if(FileDim[i]->Pointer->Judgement==5)
			Item->setBackground(QBrush(NG4Color));
	}
}

QString	DistinguishPixForm::GetJudgeStr(int d)
{
	switch(d){
		case 0 : return /**/"";
		case 1 : return ui->pushButtonOK->text();
		case 2 : return (ButtonNG1!=NULL)?ButtonNG1->text():/**/"";
		case 3 : return (ButtonNG2!=NULL)?ButtonNG2->text():/**/"";
		case 4 : return (ButtonNG3!=NULL)?ButtonNG3->text():/**/"";
		case 5 : return (ButtonNG4!=NULL)?ButtonNG4->text():/**/"";
		default: return /**/"";
	}
}

void	DistinguishPixForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqFileListContainer	*CmdReqFileListContainerVar=dynamic_cast<CmdReqFileListContainer *>(packet);
	if(CmdReqFileListContainerVar!=NULL){
		for(FileListLeaf *a=FileData.GetFirst();a!=NULL;a=a->GetNext()){
			a->JudgeStr	=GetJudgeStr(a->Judgement);
		}

		CmdReqFileListContainerVar->Container	=&FileData;
		return;
	}
	CmdReqLoadImageIntoTarget	*CmdReqLoadImageIntoTargetVar=dynamic_cast<CmdReqLoadImageIntoTarget *>(packet);
	if(CmdReqLoadImageIntoTargetVar!=NULL){
		CmdReqLoadImageIntoTargetVar->Success=LoadImageData(CmdReqLoadImageIntoTargetVar->Pointer->UFolderName
															+::GetSeparator()
															+CmdReqLoadImageIntoTargetVar->Pointer->FileName);
		return;
	}
}

void DistinguishPixForm::on_pushButtonOK_clicked()
{
	int	Row=ui->listWidget->currentRow();
	if(Row<0)
		return;
	FileDim[Row]->Pointer->Judgement=1;
	QListWidgetItem	*Item=ui->listWidget->item(Row);
	Item->setBackground(QBrush(Qt::green));

	QString	FolderName=ui->lineEditFolderName->text();
	JudgeTargetBroadcaster	Cmd;
	Cmd.FolderName	=FolderName;
	Cmd.FileName	=FileDim[Row]->Pointer->FileName;
	Cmd.Judgement	=1;
	BroadcastSpecifiedDirectly(&Cmd);
}

void DistinguishPixForm::on_pushButtonSaveList_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName(NULL,LangSolver.GetString(DistinguishPixForm_LS,LID_7)/*"Save judgement list"*/
														,QString(/**/"")
														,/**/"Lst(*.lst);;All file(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			FileData.Save(&File);
		}
	}
}

void DistinguishPixForm::on_pushButtonLoadList_clicked()
{
	QString	FolderName=ui->lineEditFolderName->text();

	QString	FileName=QFileDialog::getOpenFileName(NULL,LangSolver.GetString(DistinguishPixForm_LS,LID_10)/*"Load judgement list"*/
														,QString(/**/"")
														,/**/"Lst(*.lst);;All file(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			FileData.Load(&File);
			ShowList(FolderName);
		}
	}
}

void DistinguishPixForm::on_pushButtonClearList_clicked()
{
	FileData.RemoveAll();
	on_pushButtonScanFolder_clicked();
	QString	FolderName=ui->lineEditFolderName->text();
	ShowList(FolderName);
}

void DistinguishPixForm::on_pushButtonScanFolder_clicked()
{
	QString	FolderName=ui->lineEditFolderName->text();
	QString	UFolderName=FolderName.toUpper();
	QDir	Dir(FolderName);

	QStringList		FilterList;
	FilterList.append(/**/"*.pix");
	FilterList.append(/**/"*.jpg");
	FilterList.append(/**/"*.bmp");
	FilterList.append(/**/"*.png");
	QFileInfoList	List=Dir.entryInfoList(FilterList,QDir::Files);
	for(int i=0;i<List.count();i++){
		FileListLeaf	*a=FileData.Find(UFolderName,List[i].fileName());
		if(a==NULL){
			FileListLeaf	*b=new FileListLeaf();
			b->UFolderName	=UFolderName;
			b->FileName		=List[i].fileName();
			FileData.AppendList(b);
		}
	}
	ShowList(FolderName);

	ControlRememberer::SetValue(ui->lineEditFolderName);
}

void DistinguishPixForm::on_pushButtonSearchFolder_clicked()
{
	QString	FolderName=QFileDialog::getExistingDirectory(NULL,/**/"List folder",AbsScanPath);
	if(FolderName.isEmpty()==false){
		ui->lineEditFolderName->setText(FolderName);
		AbsScanPath=FolderName;
		on_pushButtonScanFolder_clicked();
	}
}

void DistinguishPixForm::on_pushButtonNG1_clicked()
{
	int	Row=ui->listWidget->currentRow();
	if(Row<0)
		return;
	FileDim[Row]->Pointer->Judgement=2;
	QListWidgetItem	*Item=ui->listWidget->item(Row);
	Item->setBackground(QBrush(NG1Color));

	QString	FolderName=ui->lineEditFolderName->text();
	JudgeTargetBroadcaster	Cmd;
	Cmd.FolderName	=FolderName;
	Cmd.FileName	=FileDim[Row]->Pointer->FileName;
	Cmd.Judgement	=FileDim[Row]->Pointer->Judgement;
	BroadcastSpecifiedDirectly(&Cmd);
}

void DistinguishPixForm::on_pushButtonNG2_clicked()
{
	int	Row=ui->listWidget->currentRow();
	if(Row<0)
		return;
	FileDim[Row]->Pointer->Judgement=3;
	QListWidgetItem	*Item=ui->listWidget->item(Row);
	Item->setBackground(QBrush(NG2Color));

	QString	FolderName=ui->lineEditFolderName->text();
	JudgeTargetBroadcaster	Cmd;
	Cmd.FolderName	=FolderName;
	Cmd.FileName	=FileDim[Row]->Pointer->FileName;
	Cmd.Judgement	=FileDim[Row]->Pointer->Judgement;
	BroadcastSpecifiedDirectly(&Cmd);
}

void DistinguishPixForm::on_pushButtonNG3_clicked()
{
	int	Row=ui->listWidget->currentRow();
	if(Row<0)
		return;
	FileDim[Row]->Pointer->Judgement=4;
	QListWidgetItem	*Item=ui->listWidget->item(Row);
	Item->setBackground(QBrush(NG3Color));

	QString	FolderName=ui->lineEditFolderName->text();
	JudgeTargetBroadcaster	Cmd;
	Cmd.FolderName	=FolderName;
	Cmd.FileName	=FileDim[Row]->Pointer->FileName;
	Cmd.Judgement	=FileDim[Row]->Pointer->Judgement;
	BroadcastSpecifiedDirectly(&Cmd);
}

void DistinguishPixForm::on_pushButtonNG4_clicked()
{
	int	Row=ui->listWidget->currentRow();
	if(Row<0)
		return;
	FileDim[Row]->Pointer->Judgement=5;
	QListWidgetItem	*Item=ui->listWidget->item(Row);
	Item->setBackground(QBrush(NG4Color));

	QString	FolderName=ui->lineEditFolderName->text();
	JudgeTargetBroadcaster	Cmd;
	Cmd.FolderName	=FolderName;
	Cmd.FileName	=FileDim[Row]->Pointer->FileName;
	Cmd.Judgement	=FileDim[Row]->Pointer->Judgement;
	BroadcastSpecifiedDirectly(&Cmd);
}

void DistinguishPixForm::on_pushButtonOKForNone_clicked()
{
	QString	FolderName=ui->lineEditFolderName->text();
	for(int i=0;i<FileDimNumb;i++){
		if(FileDim[i]->Pointer->Judgement==0){
			FileDim[i]->Pointer->Judgement=1;
		}
	}
	ShowList(FolderName);
}

void DistinguishPixForm::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
	int	Row=ui->listWidget->currentRow();
	if(Row<0)
		return;
	LoadImageData(FileDim[Row]->Pointer->UFolderName
				+::GetSeparator()
				+FileDim[Row]->Pointer->FileName);
}

void DistinguishPixForm::on_pushButtonReleaseOne_clicked()
{
	int	Row=ui->listWidget->currentRow();
	if(Row<0)
		return;
	FileDim[Row]->Pointer->Judgement=0;
	QListWidgetItem	*Item=ui->listWidget->item(Row);
	Item->setBackground(QBrush(Qt::white));

	QString	FolderName=ui->lineEditFolderName->text();
	JudgeTargetBroadcaster	Cmd;
	Cmd.FolderName	=FolderName;
	Cmd.FileName	=FileDim[Row]->Pointer->FileName;
	Cmd.Judgement	=FileDim[Row]->Pointer->Judgement;
	BroadcastSpecifiedDirectly(&Cmd);
}

bool DistinguishPixForm::LoadImageData(const QString &FileName)
{
	QFileInfo	Info(FileName);
	if(Info.suffix().toUpper()==QString(/**/"PIX")){
		int	CurrentPhase=GetLayersBase()->GetCurrentPhase();
		if(PhaseToLoad==-1){
			bool	Ret=false;
			for(int phase=0;phase<GetPhaseNumb();phase++){
				GetLayersBase()->SetCurrentPhase(phase);
				CmdReqLoadImage	Cmd(GetLayersBase());
				Cmd.FileName=FileName;
				GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Inspection",/**/"LoadImageTargetButton",/**/"");
				if(f!=NULL){
					f->TransmitDirectly(&Cmd);
					Ret=Cmd.Success;
				}
			}
			GetLayersBase()->SetCurrentPhase(CurrentPhase);
			BroadcastShowInEdit();
			return Ret;
		}
		else if(0<=PhaseToLoad && PhaseToLoad<GetPhaseNumb()){
			GetLayersBase()->SetCurrentPhase(PhaseToLoad);
			CmdLoadBmpJpgPacket	Cmd(GetLayersBase());
			Cmd.FileName=FileName;
			GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Inspection",/**/"LoadImageTargetButton",/**/"");
			if(f!=NULL){
				f->TransmitDirectly(&Cmd);
				GetLayersBase()->SetCurrentPhase(CurrentPhase);
				BroadcastShowInEdit();
				return Cmd.Success;
			}
		}

	}
	else{
		int	CurrentPhase=GetLayersBase()->GetCurrentPhase();
		if(PhaseToLoad==-1){
			bool	Ret=false;
			for(int phase=0;phase<GetPhaseNumb();phase++){
				GetLayersBase()->SetCurrentPhase(phase);
				CmdLoadBmpJpgPacketTarget	Cmd(GetLayersBase());
				Cmd.FileName=FileName;
				GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ButtonLoadBmpJpg",/**/"");
				if(f!=NULL){
					f->TransmitDirectly(&Cmd);
					Ret=Cmd.Success;
				}
			}
			GetLayersBase()->SetCurrentPhase(CurrentPhase);
			BroadcastShowInEdit();
			return Ret;
		}
		else if(0<=PhaseToLoad && PhaseToLoad<GetPhaseNumb()){
			GetLayersBase()->SetCurrentPhase(PhaseToLoad);
			CmdLoadBmpJpgPacketTarget	Cmd(GetLayersBase());
			Cmd.FileName=FileName;
			GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ButtonLoadBmpJpg",/**/"");
			if(f!=NULL){
				f->TransmitDirectly(&Cmd);
				GetLayersBase()->SetCurrentPhase(CurrentPhase);
				BroadcastShowInEdit();
				return Cmd.Success;
			}
		}

	}
	return false;
}