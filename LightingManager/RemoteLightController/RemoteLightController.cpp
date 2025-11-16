#include "RemoteLightControllerResource.h"
#include "RemoteLightController.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "XGeneralFunc.h"
#include "XLightClass.h"
#include "SettingDialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XPassword.h"

extern	int	MachineID;
extern	int		LoadLightDataOnStart;

void	LightItemButton::SlotClicked()
{
	emit	SignalClicked(Item->ID);
}

RemoteLightController::RemoteLightController(LayersBase *Base 
											,const QString &LoadedFile,bool StartON 
											,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,ServiceForLayers(Base)
	,RemoteLightData(Base)
	,FromProgramHost(this)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	if(LoadedFile.isEmpty()==false){
		if(LoadFromFile(LoadedFile)==true){			
		}
	}
	GetLayersBase()->CloseInformed();
	LoadedFileName=LoadedFile;
	PutButtons();

	if(StartON==true){
		for(RemoteLightItem *a=RemoteLightData.GetFirst();a!=NULL;a=a->GetNextD(RemoteLightData)){
			a->SetOnOff(true);
		}
	}
	else{
		for(RemoteLightItem *a=RemoteLightData.GetFirst();a!=NULL;a=a->GetNextD(RemoteLightData)){
			a->SetOnOff(false);
		}
	}

	QString	PosFileName=GetPositionFileName();
	QFile	F(PosFileName);
	if(F.open(QIODevice::ReadOnly)==true){
		int	PosX,PosY,W,H;
		if(::Load(&F,PosX)==true){
			if(::Load(&F,PosY)==true){
				if(::Load(&F,W)==true){
					if(::Load(&F,H)==true){
						//move(PosX,PosY);
						setGeometry(PosX,PosY,W,H);
					}
				}
			}
		}
	}
	setWindowTitle(LoadedFileName);

	ui.tableWidgetLight->setColumnWidth(0,44);
	ui.tableWidgetLight->setColumnWidth(1,190);
	ui.tableWidgetLight->setColumnWidth(2,190);

	CurrentRowOnList	=-1;
	ui.pushButtonUpdate_2	->setEnabled(false);
	ui.pushButtonDelete		->setEnabled(false);
	ShowLightList();
	FromProgramHost.Start();

	TM.setInterval(350);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimerBreak()));
	TM.start();
}

RemoteLightController::~RemoteLightController()
{
}

void	RemoteLightController::SlotTimerBreak()
{
	static	bool	LoadedFirstTime=false;

	if(LoadedFirstTime==false){
		if(LoadLightDataOnStart>=0){
			int	Row=0;
			for(LightList *L=LightListContainer.GetFirst();L!=NULL;L=L->GetNext(),Row++){
				if(L->ID==LoadLightDataOnStart){
					LoadRowData(Row);
				}
			}
		}
		LoadedFirstTime=true;
	}

	if(GetLayersBase()!=NULL){
		if(GetLayersBase()->GetPasswordHolder()->IsPassed()==true){
			GetLayersBase()->GetPasswordHolder()->IsExpired();
			if(ui.toolButtonManagementMode->isChecked()==false){
				ui.toolButtonManagementMode->setChecked(true);
			}
		}
		else{
			if(ui.toolButtonManagementMode->isChecked()==true){
				ui.toolButtonManagementMode->setChecked(false);
			}
		}
	}
	if(ui.toolButtonManagementMode->isChecked()==true){
		QPalette	P=ui.toolButtonManagementMode->palette();
		P.setColor(QPalette::Button,Qt::red);
		ui.toolButtonManagementMode->setPalette(P);
	}
	else{
		QPalette	P=ui.toolButtonManagementMode->palette();
		P.setColor(QPalette::Button,Qt::green);
		ui.toolButtonManagementMode->setPalette(P);
	}
}

void	RemoteLightController::ShowLightList(void)
{
	LightListContainer.RemoveAll();
	QString	S=QString(/**/"SELECT LIGHTID,NAME,REMARK FROM LIGHT where MACHINEID=")
		+ QString::number(MachineID)
		+ QString(/**/" order by LIGHTID");
	QSqlQuery query(S ,*GetLayersBase()->GetDataBase());
	while(query.next ()==true){
		int		LightID		=query.value(query.record().indexOf(/**/"LIGHTID"	)).toInt();
		QString	LightName	=query.value(query.record().indexOf(/**/"NAME"		)).toString();
		QString	LightRemark	=query.value(query.record().indexOf(/**/"REMARK"	)).toString();
		LightList	*L=new LightList(LightID, LightName ,LightRemark);
		LightListContainer.AppendList(L);
	}

	ui.tableWidgetLight->setRowCount(LightListContainer.GetCount());
	int	Row=0;
	for(LightList *L=LightListContainer.GetFirst();L!=NULL;L=L->GetNext()){
		SetDataToTable(ui.tableWidgetLight ,0,Row,QString::number(L->ID));
		SetDataToTable(ui.tableWidgetLight ,1,Row,L->Name);
		SetDataToTable(ui.tableWidgetLight ,2,Row,L->Remark);
		Row++;
	}
}

void	RemoteLightController::PutButtons(void)
{
	Buttons.RemoveAll();
	for(RemoteLightItem *a=RemoteLightData.GetFirst();a!=NULL;a=a->GetNextD(RemoteLightData)){
		LightItemButton	*w=new LightItemButton(a,ui.frameButtons);
		Buttons.AppendList(w);
		connect(w,SIGNAL(clicked()),w,SLOT(SlotClicked()));
		connect(w,SIGNAL(SignalClicked(int)),this,SLOT(SlotClicked(int)));
	}
	int	Y=0;
	for(LightItemButton *s=Buttons.GetFirst();s!=NULL;s=s->GetNext()){
		s->setGeometry(0,Y,ui.frameButtons->width(),30);
		s->setText(s->GetItem()->RegName);
		s->show();
		Y+=30;
	}
}

void RemoteLightController::on_pushButtonSetting_clicked()
{
	if(GetLayersBase()->GetPasswordHolder()->PasswordCheck()==false)
		return;

	RemoteLightContainer	TmpData(GetLayersBase());
	TmpData=RemoteLightData;
	SettingDialog	D(GetLayersBase(),TmpData);
	D.exec();
	RemoteLightData.CloseDLL();
	RemoteLightData.MoveFrom(D.RemoteLightData);
	RemoteLightData.OpenDLL(this);
	GetLayersBase()->CloseInformed();
	RemoteLightData.ReflectLight();

	/*
	if(LoadedFileName.isEmpty()==true){
		return;
	}
	QFile	File(LoadedFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		RemoteLightData.Save(&File);
	}
	*/
	PutButtons();
	on_pushButtonUpdate_clicked();
}

void RemoteLightController::on_toolButtonOnOff_clicked()
{
	for(RemoteLightItem *a=RemoteLightData.GetFirst();a!=NULL;a=a->GetNextD(RemoteLightData)){
		a->SetOnOff(ui.toolButtonOnOff->isChecked());
	}
}

void RemoteLightController::on_pushButtonSaveAll_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName(NULL
												,LangSolver.GetString(RemoteLightController_LS,LID_0)/*"Save file"*/
												,QString()
												,QString(/**/"*.dat"));

	if(FileName.isEmpty()==true){
		return;
	}
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==true){
		SaveToFile(File);
	}
}

bool RemoteLightController::SaveToFile(QIODevice &File)
{
	int32	N=RemoteLightData.GetCount();
	if(::Save(&File,N)==false)
		return false;
	for(RemoteLightItem *a=RemoteLightData.GetFirst();a!=NULL;a=a->GetNextD(RemoteLightData)){
		if(::Save(&File,a->RegName)==false)
			return false;
		if(::Save(&File,a->DLLFileName)==false)
			return false;
		if(a->Save(&File)==false)
			return false;
		if(a->SaveLightSetting(&File)==false)
			return false;
	}
	return true;
}

void RemoteLightController::on_pushButtonLoadAll_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(NULL
												,LangSolver.GetString(RemoteLightController_LS,LID_1)/*"Open file"*/
												,QString()
												,QString(/**/"*.dat"));

	if(FileName.isEmpty()==true){
		return;
	}
	if(LoadFromFile(FileName)==true){
		LoadedFileName=FileName;
		setWindowTitle(LoadedFileName);
	}
	GetLayersBase()->CloseInformed();
}
bool RemoteLightController::LoadFromFile(const QString &FileName)
{
	bool	Ret=true;
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		Ret=LoadFromFile(File);
	}
	return Ret;
}

bool RemoteLightController::LoadFromFile(QIODevice &File)
{
	int32	N;
	if(::Load(&File,N)==false)
		return false;
	for(int i=0;i<N;i++){
		QString	iRegName;
		QString	iDLLFileName;
		if(::Load(&File,iRegName)==false)
			return false;
		if(::Load(&File,iDLLFileName)==false)
			return false;
		bool	Found=false;
		for(RemoteLightItem *a=RemoteLightData.GetFirst();a!=NULL;a=a->GetNextD(RemoteLightData)){
			if(a->RegName==iRegName && a->DLLFileName==iDLLFileName){
				if(a->Load(&File)==false)
					return false;
				if(a->LoadLightSetting(&File)==false)
					return false;
				a->SlotReflectDataInDialog();
				Found=true;
			}
		}
		if(Found==false){
			RemoteLightItem *a=new RemoteLightItem(GetLayersBase(),&RemoteLightData);
			if(a->Load(&File)==false)
				return false;
			a->OpenDLL(this);
			if(a->LoadLightSetting(&File)==false)
				return false;
			RemoteLightData.AppendList(a);
			a->SlotReflectDataInDialog();
		}
	}
	return true;
}

void RemoteLightController::on_pushButtonClose_clicked()
{
	close();
}

void	RemoteLightController::SlotClicked(int ID)
{
	if(GetLayersBase()->GetPasswordHolder()->PasswordCheck()==false)
		return;

	for(RemoteLightItem *a=RemoteLightData.GetFirst();a!=NULL;a=a->GetNextD(RemoteLightData)){
		if(a->ID==ID){
			a->ShowSetting(NULL);
		}
	}
}

void RemoteLightController::moveEvent ( QMoveEvent * event )
{
	SavePosition();
}
void RemoteLightController::resizeEvent ( QResizeEvent * event )
{
	SavePosition();

	int	YLen=height()-ui.frameController->height();
	ui.frameButtons->resize(ui.frameButtons->width(),YLen-50);
	ui.frameController->move(ui.frameController->geometry().x(),YLen);

	int	OpeYLen=height()-ui.frameOperation->height();
	ui.tableWidgetLight->resize(ui.tableWidgetLight->width(),OpeYLen);
	ui.frameOperation->move(0,OpeYLen);
}

void RemoteLightController::SavePosition(void)
{
	QString	FileName=GetPositionFileName();
	QFile	F(FileName);
	if(F.open(QIODevice::WriteOnly)==true){
		int32	PosX=geometry().left();
		int32	PosY=geometry().top();
		int32	W=geometry().width();
		int32	H=geometry().height();
		if(::Save(&F,PosX)==false){
			return;
		}
		if(::Save(&F,PosY)==false){
			return;
		}
		if(::Save(&F,W)==false){
			return;
		}
		if(::Save(&F,H)==false){
			return;
		}
	}
}

void RemoteLightController::on_pushButtonUpdate_clicked()
{
	if(GetLayersBase()->GetPasswordHolder()->PasswordCheck()==false)
		return;

	if(LoadedFileName.isEmpty()==true){
		return;
	}
	QFile	File(LoadedFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		int32	N=RemoteLightData.GetCount();
		::Save(&File,N);
		for(RemoteLightItem *a=RemoteLightData.GetFirst();a!=NULL;a=a->GetNextD(RemoteLightData)){
			::Save(&File,a->RegName);
			::Save(&File,a->DLLFileName);
			a->Save(&File);
			a->SaveLightSetting(&File);
		}
	}
}

void RemoteLightController::on_tableWidgetLight_doubleClicked(const QModelIndex &index)
{
	int	Row=ui.tableWidgetLight->currentRow();
	if(Row<0)
		return;
	LoadRowData(Row);
}
void RemoteLightController::LoadRowData(int Row)
{
	LightList	*L=LightListContainer.GetItem(Row);
	if(L==NULL)
		return;
	CurrentRowOnList=Row;

	QString	S=QString(/**/"SELECT LIGHTID,NAME,REMARK,LIGHTDATA FROM LIGHT where MACHINEID=")
		+ QString::number(MachineID)
		+ QString(/**/" and LIGHTID=")
		+ QString::number(L->ID);
	QSqlQuery query(S ,*GetLayersBase()->GetDataBase());
	if(query.next ()==true){
		int		LightID		=query.value(query.record().indexOf(/**/"LIGHTID"	)).toInt();
		QString	LightName	=query.value(query.record().indexOf(/**/"NAME"		)).toString();
		QString	LightRemark	=query.value(query.record().indexOf(/**/"REMARK"	)).toString();
		QByteArray	Ld		=query.value(query.record().indexOf(/**/"LIGHTDATA"	)).toByteArray();
		ui.lineEditID		->setText(QString::number(LightID));
		ui.lineEditName		->setText(LightName);
		ui.lineEditRemark	->setText(LightRemark);
		setWindowTitle(QString::number(LightID)+QString(/**/" : ")+LightName);
		LastCurrentLightID	=LightID;

		QBuffer	Buff(&Ld);
		Buff.open(QIODevice::ReadOnly);
		if(LoadFromFile(Buff)==true){
			PutButtons();
			ui.pushButtonUpdate_2	->setEnabled(true);
			ui.pushButtonDelete		->setEnabled(true);
			on_toolButtonOnOff_clicked();
		}
		else{
			ui.pushButtonDelete		->setEnabled(true);
		}
		GetLayersBase()->CloseInformed();
	}
}

void RemoteLightController::on_pushButtonCreateNew_clicked()
{
	if(GetLayersBase()->GetPasswordHolder()->PasswordCheck()==false)
		return;

	bool	ok;
	int	LightID	=ui.lineEditID		->text().toInt(&ok);
	if(ok==false)
		return;
	QString	LightName	=ui.lineEditName	->text();
	QString	LightRemark	=ui.lineEditRemark	->text();

	QBuffer	Buff;
	Buff.open(QIODevice::WriteOnly);
	if(SaveToFile(Buff)==false)
		return;

	QSqlQuery queryInsrt(*GetLayersBase()->GetDataBase());
	queryInsrt.prepare(/**/"INSERT INTO LIGHT(MACHINEID,LIGHTID,LIGHTDATA,DLLIDNAME,NAME,REMARK,UPDATETIME) "
		/**/"VALUES(:MACHINEID,:LIGHTID,:LIGHTDATA,:DLLIDNAME,:NAME,:REMARK,:UPDATETIME);");
	queryInsrt.bindValue(0	, MachineID);
	queryInsrt.bindValue(1	, LightID);
	queryInsrt.bindValue(2	, Buff.buffer());
	queryInsrt.bindValue(3	, /**/"RemoteLightController");
	queryInsrt.bindValue(4	, LightName);
	queryInsrt.bindValue(5	, LightRemark);
	XDateTime	UpdateTime	=XDateTime::currentDateTime();
	queryInsrt.bindValue(6	, UpdateTime.GetQDateTime());
	if(queryInsrt.exec()==false){
		return;
	}

	ShowLightList();
}

void RemoteLightController::on_pushButtonUpdate_2_clicked()
{
	if(GetLayersBase()->GetPasswordHolder()->PasswordCheck()==false)
		return;

	bool	ok;
	int	LightID	=ui.lineEditID		->text().toInt(&ok);
	if(ok==false)
		return;
	QString	LightName	=ui.lineEditName	->text();
	QString	LightRemark	=ui.lineEditRemark	->text();

	QBuffer	Buff;
	Buff.open(QIODevice::WriteOnly);
	if(SaveToFile(Buff)==false)
		return;

	QSqlQuery queryUpdate(*GetLayersBase()->GetDataBase());
	queryUpdate.prepare(/**/"UPDATE LIGHT "
						/**/"SET LIGHTID=:LIGHTID1"
						/**/", NAME=:NAME"
						/**/", REMARK=:REMARK "
						/**/", LIGHTDATA=:LIGHTDATA "
						/**/"WHERE MACHINEID=:MACHINEID and LIGHTID=:LIGHTID2;");

	queryUpdate.bindValue(0, LightID);
	queryUpdate.bindValue(1, LightName);
	queryUpdate.bindValue(2, LightRemark);
	queryUpdate.bindValue(3, Buff.buffer());
	queryUpdate.bindValue(4, MachineID);
	queryUpdate.bindValue(5, LastCurrentLightID);
	bool	ret=queryUpdate.exec();
	if(ret==true){
		ui.pushButtonUpdate_2	->setEnabled(false);
		ui.pushButtonDelete		->setEnabled(false);
	}
	ShowLightList();
}

void RemoteLightController::on_pushButtonDelete_clicked()
{
	if(GetLayersBase()->GetPasswordHolder()->PasswordCheck()==false)
		return;

	QSqlQuery queryDelete(*GetLayersBase()->GetDataBase());
	queryDelete.prepare(/**/"delete from LIGHT "
						/**/" WHERE MACHINEID=:MACHINEID and LIGHTID=:LIGHTID;");

	queryDelete.bindValue(0, MachineID);
	queryDelete.bindValue(1, LastCurrentLightID);
	bool	ret=queryDelete.exec();
	if(ret==true){
		ui.pushButtonUpdate_2	->setEnabled(false);
		ui.pushButtonDelete		->setEnabled(false);
	}

	ShowLightList();
}

void	RemoteLightController::SetLightID(int lightID)
{
	int	Row=0;
	for(LightList *L=LightListContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->ID==lightID){
			break;
		}
		Row++;
	}
	if(LightListContainer.GetCount()>Row){
		ui.tableWidgetLight->setCurrentCell(Row,0);
		QModelIndex	Index;
		on_tableWidgetLight_doubleClicked(Index);
	}
}

void	RemoteLightController::SetLightRequest(BYTE *ReqData,int ReqDataLength)
{
	CmdSendRequestLight	RCmd(GetLayersBase(),ReqData,ReqDataLength);
	for(LightItemButton *L=Buttons.GetFirst();L!=NULL;L=L->GetNext()){
		L->GetItem()->SendCommand(ReqData ,ReqDataLength);
	}
}

void	RemoteLightController::SetLightOn(bool lightOn)
{
	ui.toolButtonOnOff->setChecked(lightOn);
	on_toolButtonOnOff_clicked();
}
void RemoteLightController::on_toolButtonManagementMode_clicked()
{
	if(ui.toolButtonManagementMode->isChecked()==true)
		GetLayersBase()->GetPasswordHolder()->PasswordCheck();
	else
		GetLayersBase()->GetPasswordHolder()->EnablePasswordAgain();
}
