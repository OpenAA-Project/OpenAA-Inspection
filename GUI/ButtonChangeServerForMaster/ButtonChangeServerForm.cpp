#include "ButtonChangeServerFormResource.h"
#include "ButtonChangeServerForm.h"
#include "ui_ButtonChangeServerForm.h"
#include "ChangeServerForMasterDialog.h"
#include "XParamGlobal.h"
#include "XSyncGUI.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

ButtonChangeServerForm::ButtonChangeServerForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ButtonChangeServerForm)
{
    ui->setupUi(this);

	Msg=/**/"Change server";
	resize(60,25);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonChangeServerForm::~ButtonChangeServerForm()
{
    delete ui;
}

void ButtonChangeServerForm::on_pushButton_clicked()
{
	ChangeServerForMasterDialog	D(GetLayersBase());
	if(D.exec()==true){
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
			if(QMessageBox::question(NULL,LangSolver.GetString(ButtonChangeServerForm_LS,LID_0)/*"Synchronized"*/
										,LangSolver.GetString(ButtonChangeServerForm_LS,LID_1)/*"Synchronize other ?"*/
										,QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				int	Cmd=1;
				::Save(&Buff,Cmd);
				D.Selected->Save(&Buff);

				TxSync(Buff.buffer());
			}
		}

		if(GetParamComm()->GetConnectedPCNumb()!=0){
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdChangeServer	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
				RCmd.ServerData	=*D.Selected;
				RCmd.Send(NULL,GlobalPage ,0);
			}
		}
		ExeChangeServer(D.Selected);
	}
}

void	ButtonChangeServerForm::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdChangeServer	*GUICmdChangeServerVar=dynamic_cast<GUICmdChangeServer *>(packet);
	if(GUICmdChangeServerVar!=NULL){
		ExeChangeServer(&GUICmdChangeServerVar->ServerData);
		return;
	}
}

bool	ButtonChangeServerForm::ExeChangeServer(ChangeServerInfo *d)
{
	QString	FileName	=GetLayersBase()->GetUserPath()
						+GetSeparator()
						+GetParamGlobal()->GetSavedFileName();

	QFile	FRGeneral(FileName);
	if(FRGeneral.open(QIODevice::ReadOnly)==true){

		ParamGlobal	TmpParam(GetLayersBase());
		if(TmpParam.LoadParam(&FRGeneral)==false)
			return false;

		TmpParam.LocalDatabase_HostName	=d->DBIPAddress;
		TmpParam.LocalDatabase_FileName	=d->DBFileName;
		TmpParam.LocalDatabase_Port		=d->DBPort;
		TmpParam.ImageFilePath			=d->ImagePath;

		FRGeneral.close();

		QFile	FWGeneral(FileName);

		FWGeneral.setPermissions(QFile::WriteUser | QFile::ReadUser);

		if(FWGeneral.open(QIODevice::WriteOnly)==true){
			if(TmpParam.SaveParam(&FWGeneral)==false){
				return false;
			}
		}
		FWGeneral.close();
		FWGeneral.setPermissions(QFile::ReadUser);

		GetLayersBase()->CloseOne();
		QCoreApplication::quit();

		return true;
	}
	return false;
}

void	ButtonChangeServerForm::Prepare(void)
{
	ui->pushButton->setText(Msg);
	ui->pushButton->setFont (CFont);
	ResizeAction();
}

void	ButtonChangeServerForm::ResizeAction()
{
	ui->pushButton->resize(width(),height());
}

void	ButtonChangeServerForm::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);
	int			Ver;
	if(::Load(&Buff,Ver)==false)
		return;
	ChangeServerInfo	ServerData;

	if(ServerData.Load(&Buff)==false)
		return;

	if(GetParamComm()->GetConnectedPCNumb()!=0){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdChangeServer	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
			RCmd.ServerData	=ServerData;
			RCmd.Send(NULL,GlobalPage ,0);
		}
	}
	ExeChangeServer(&ServerData);
}

//========================================================================================================
GUICmdChangeServer::GUICmdChangeServer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdChangeServer::Load(QIODevice *f)
{
	if(ServerData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdChangeServer::Save(QIODevice *f)
{
	if(ServerData.Save(f)==false)
		return false;
	return true;
}

void	GUICmdChangeServer::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*a=GetLayersBase()->FindByName(sRoot,sName,/**/"");
	if(a!=NULL){
		ButtonChangeServerForm	*f=dynamic_cast<ButtonChangeServerForm *>(a);
		if(f!=NULL){
			f->TransmitDirectly(this);
		}
	}
}
