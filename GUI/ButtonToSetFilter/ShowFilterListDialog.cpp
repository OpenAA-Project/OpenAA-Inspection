#include "ButtonToSetFilterResource.h"
#include "ShowFilterListDialog.h"
#include "ui_ShowFilterListDialog.h"
#include "XFilterInstance.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowFilterListDialog::ShowFilterListDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base)
    ,ui(new Ui::ShowFilterListDialog)
{
    ui->setupUi(this);
	InstallOperationLog(this);
}

ShowFilterListDialog::~ShowFilterListDialog()
{
    delete ui;
}

void	ShowFilterListDialog::Init(int globalPage ,GUIFilterListContainer &_FList)
{
	GlobalPage=globalPage;
	FList=_FList;
	ui->listWidget->clear();
	for(GUIFilterList *L=FList.GetFirst();L!=NULL;L=L->GetNext()){
		ui->listWidget->addItem(L->FilterName);
	}
}

void ShowFilterListDialog::on_pushButtonClose_clicked()
{
	close();
}

void ShowFilterListDialog::on_listWidget_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->listWidget->currentRow();
	GUICmdReqFilterData	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
	GUICmdAckFilterData	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
	RCmd.Line=Row;
	if(RCmd.Send(GlobalPage,0,ACmd)==true){
		FilterInstanceContainer	FContainer(GetLayersBase()->GetCurrentPhase(),GlobalPage,GetLayersBase());
		FilterInstanceList	LInst(&FContainer,GetLayersBase());
		int32	ErrorCode;
		LInst.CreateInstance(FList[Row]->FilterName,ErrorCode);
		QBuffer	Buff(&ACmd.Data);
		Buff.open(QIODevice::ReadOnly);
		LInst.Load(&Buff);
		if(LInst.ShowSetting(this)==true){
			GUICmdSetFilterData	SCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			QBuffer	MBuff;
			MBuff.open(QIODevice::WriteOnly);
			LInst.Save(&MBuff);
			SCmd.Data=MBuff.buffer();
			SCmd.Send(NULL,GlobalPage,0);
		}
	}
}

//================================================================================
GUICmdReqFilterData::GUICmdReqFilterData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Line=-1;
}

bool	GUICmdReqFilterData::Load(QIODevice *f)
{
	if(::Load(f,Line)==false)
		return false;
	return true;
}
bool	GUICmdReqFilterData::Save(QIODevice *f)
{
	if(::Save(f,Line)==false)
		return false;
	return true;
}

void	GUICmdReqFilterData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckFilterData	*SendBack=GetSendBack(GUICmdAckFilterData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	PageDataInOnePhase	*Ph=GetLayersBase()->GetCurrentPageDataPhase();
	FilterInstanceContainer	*Pc=Ph->GetFilterContainer(localPage);
	if(Pc!=NULL){
		int	Line=0;
		FilterInstanceList *a=Pc->GetItem(Line);
		if(a!=NULL){
			QBuffer	Buff;
			Buff.open(QIODevice::WriteOnly);
			a->Save(&Buff);
			SendBack->Data=Buff.buffer();
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckFilterData::GUICmdAckFilterData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckFilterData::Load(QIODevice *f)
{
	if(::Load(f,Data)==false)
		return false;
	return true;
}

bool	GUICmdAckFilterData::Save(QIODevice *f)
{
	if(::Save(f,Data)==false)
		return false;
	return true;
}

GUICmdSetFilterData::GUICmdSetFilterData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Line=-1;
}

bool	GUICmdSetFilterData::Load(QIODevice *f)
{
	if(::Load(f,Line)==false)
		return false;
	if(::Load(f,Data)==false)
		return false;
	return true;
}
bool	GUICmdSetFilterData::Save(QIODevice *f)
{
	if(::Save(f,Line)==false)
		return false;
	if(::Save(f,Data)==false)
		return false;
	return true;
}

void	GUICmdSetFilterData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	PageDataInOnePhase	*Ph=GetLayersBase()->GetCurrentPageDataPhase();
	FilterInstanceContainer	*Pc=Ph->GetFilterContainer(localPage);
	if(Pc!=NULL){
		int	Line=0;
		FilterInstanceList *a=Pc->GetItem(Line);
		if(a!=NULL){
			QBuffer	Buff(&Data);
			Buff.open(QIODevice::ReadOnly);
			a->Load(&Buff);

			GetLayersBase()->SaveFilterDef();
		}
	}
	SendAck(localPage);
}
