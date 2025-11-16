#include "ListGenerateChildLibraryResource.h"
#include "ListGenerateChildLibraryForm.h"
#include "ui_ListGenerateChildLibraryForm.h"
#include "XDataInLayer.h"
#include <QMessageBox>
#include "XDatabaseLoader.h"
#include "XSyncGUI.h"
#include <QSqlQuery>
#include "XGeneralDialog.h"

LibFolderTreeForm::LibFolderTreeForm(ListGenerateChildLibraryForm *p ,int libType ,LayersBase *lbase ,QWidget *parent)
	:LibFolderForm(libType ,lbase ,parent),Parent(p)
{
}
void LibFolderTreeForm::mouseDoubleClickEvent ( QMouseEvent * event )
{
	Parent->on_pushButtonSelect_clicked();
}

ListGenerateChildLibraryForm::ListGenerateChildLibraryForm(LayersBase *Base,QWidget *parent) :
	GUIFormBase(Base,parent),
    ui(new Ui::ListGenerateChildLibraryForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	pLibFolderForm=new LibFolderTreeForm(this,-1,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ListGenerateChildLibraryForm::~ListGenerateChildLibraryForm()
{
    delete ui;
}

void	ListGenerateChildLibraryForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
}
void	ListGenerateChildLibraryForm::BuildForShow(void)
{
	if(GetLayersBase()->GetMasterCode()>0){
		QVariant	data;
		if(GetLayersBase()->LoadMasterFieldData(/**/"LIBFOLDERID", data)==true){
			bool ok;
			int	d=data.toInt(&ok);
			if(ok==true){
				int	CurrentLibFolderID=d;

				QString FolderName;
				int		ParentID;
				int		NumberInFolder;
				if(GetLayersBase()->GetDatabaseLoader()->S_LibFolderFindData(GetLayersBase()->GetDatabase(),CurrentLibFolderID ,FolderName ,ParentID ,NumberInFolder)==true){
					pLibFolderForm->SetCurrentLibFolder(CurrentLibFolderID);
					LibFolderID=ParentID;
					ui->lineEditFolderName->setText(FolderName);
					GetLayersBase()->SetLibFolderID(CurrentLibFolderID,-1);
					BroadcastSetupLibFolder(CurrentLibFolderID,-1);
				}
			}
		}
	}
}


void	ListGenerateChildLibraryForm::ResizeAction()
{
	int	LHeight=height();
	int	FrameH=ui->frame->height();
	ui->frame->move(0,LHeight-FrameH);
	ui->frame->resize(width(),ui->frame->height());

	ui->label_2				->resize(ui->frame->width()-2,ui->label_2->height());
	ui->lineEditFolderName	->resize(ui->frame->width()-2,ui->lineEditFolderName->height());

	if((ui->pushButtonGenerate->width()+ui->pushButtonSelect->width()+2)>ui->frame->width()){
		int	W=(ui->frame->width()-2)/2-2;
		ui->pushButtonGenerate->resize(W,ui->pushButtonGenerate->height());
		ui->pushButtonSelect->resize(W,ui->pushButtonGenerate->height());
	}

	ui->pushButtonSelect	->move(ui->frame->width()-ui->pushButtonSelect->width()-1,ui->pushButtonSelect->geometry().top());

	ui->label			->resize(width()-2 ,ui->label->height());
	int	H=height()-ui->frame->height()-ui->label->height()-1;
	ui->frameLibFolder	->resize(width()-2 ,H);
	if(pLibFolderForm!=NULL){
		pLibFolderForm->FitToFrame(ui->frameLibFolder);
	}
}
void	ListGenerateChildLibraryForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CreateUpdateMasterSpecifiedBroadcaster	*CreateUpdateMasterSpecifiedBroadcasterVar=dynamic_cast<CreateUpdateMasterSpecifiedBroadcaster *>(v);
	if(CreateUpdateMasterSpecifiedBroadcasterVar!=NULL){
		if(GetLayersBase()->GetMasterCode()>0){
			QVariant	data(GetLayersBase()->GetMasterCode());
			GetLayersBase()->AddMasterFieldData(/**/"LIBFOLDERID", data);
		}
	}
}
void ListGenerateChildLibraryForm::on_pushButtonGenerate_clicked()
{
	QString FolderName=ui->lineEditFolderName->text();
	if(FolderName.isEmpty()==true){
		QMessageBox::warning(NULL,LangSolver.GetString(ListGenerateChildLibraryForm_LS,LID_0)/*"Error"*/
							,LangSolver.GetString(ListGenerateChildLibraryForm_LS,LID_1)/*"Please input new folder name"*/);
		return;
	}
	if(LibFolderID<0){
		if(QMessageBox::warning(NULL,LangSolver.GetString(ListGenerateChildLibraryForm_LS,LID_2)/*"Alerm"*/
							,LangSolver.GetString(ListGenerateChildLibraryForm_LS,LID_3)/*"Do you create original folder in root?"*/
							,QMessageBox::Yes,QMessageBox::No)==QMessageBox::No){
			return;
		}
	}

	int	CurrentLibFolderID=GetLayersBase()->GetDatabaseLoader()->S_LibFolderCreatenew(GetLayersBase()->GetDatabase());
	if(CurrentLibFolderID<=0){
		QMessageBox::warning(NULL,LangSolver.GetString(ListGenerateChildLibraryForm_LS,LID_4)/*"Error"*/
							,LangSolver.GetString(ListGenerateChildLibraryForm_LS,LID_5)/*"Can not create new LibFolder"*/);
		return;
	}
	GetLayersBase()->SetLibFolderID(CurrentLibFolderID,LibFolderID);
	GetLayersBase()->GetDatabaseLoader()->S_LibFolderUpdate(GetLayersBase()->GetDatabase() ,LibFolderID ,FolderName, CurrentLibFolderID ,-1);

	GetLayersBase()->GetDatabaseLoader()->S_LibCopy(GetLayersBase()->GetDatabase(),LibFolderID,CurrentLibFolderID,-1);
	pLibFolderForm->SetLibType(-1);
	pLibFolderForm->Show();

	BroadcastSetupLibFolder(CurrentLibFolderID,LibFolderID);

	if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		::Save(&Buff,CurrentLibFolderID);
		::Save(&Buff,LibFolderID);
		::Save(&Buff,FolderName);
		TxSync(Buff.buffer());
	}
}

void	ListGenerateChildLibraryForm::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);
	int	CurrentLibFolderID;
	QString FolderName;

	if(::Load(&Buff,CurrentLibFolderID)==false)
		return;
	if(::Load(&Buff,LibFolderID)==false)
		return;
	if(::Load(&Buff,FolderName)==false)
		return;

	pLibFolderForm->Show();
	pLibFolderForm->SetCurrentLibFolder(CurrentLibFolderID);
	ui->lineEditFolderName->setText(FolderName);
	GetLayersBase()->SetLibFolderID(CurrentLibFolderID,LibFolderID);
	BroadcastSetupLibFolder(CurrentLibFolderID,LibFolderID);

}
void ListGenerateChildLibraryForm::on_pushButtonSelect_clicked()
{
	int	CurrentLibFolderID=LibFolderID;
	if(CurrentLibFolderID<=0){
		QMessageBox::warning(NULL,LangSolver.GetString(ListGenerateChildLibraryForm_LS,LID_6)/*"Error"*/
							,LangSolver.GetString(ListGenerateChildLibraryForm_LS,LID_7)/*"Can not create new LibFolder"*/);
		return;
	}
	GetLayersBase()->SetLibFolderID(CurrentLibFolderID,-1);

	BroadcastSetupLibFolder(CurrentLibFolderID,-1);

	if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		::Save(&Buff,CurrentLibFolderID);
		::Save(&Buff,LibFolderID);
		::Save(&Buff,/**/"");
		TxSync(Buff.buffer());
	}
}
