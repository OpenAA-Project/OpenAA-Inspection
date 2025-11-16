#include "ButtonToSetFilterResource.h"
#include "ButtonToSetFilterForm.h"
#include "ui_ButtonToSetFilterForm.h"
#include "ShowFilterListDialog.h"
#include "SelectOnePage.h"
#include "XFilterInstance.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ButtonToSetFilterForm::ButtonToSetFilterForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ButtonToSetFilterForm)
{
    ui->setupUi(this);

	DefaultPushed	=false;
	ui->pushButtonFilter->move(0,0);
	Msg=/**/"Set Filter";
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonToSetFilterForm::~ButtonToSetFilterForm()
{
    delete ui;
}

void	ButtonToSetFilterForm::Prepare(void)
{
	ui->pushButtonFilter->setText(Msg);
	ui->pushButtonFilter->setFont (CFont);
	ResizeAction();
}

void	ButtonToSetFilterForm::ResizeAction()
{
	ui->pushButtonFilter->resize(width(),height());
}

void ButtonToSetFilterForm::on_pushButtonFilter_clicked()
{
	SelectOnePage	D(GetLayersBase());
	if(D.exec()==(int)true){
		int	Page=D.SelectedPage;
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Page);
		GUICmdReqFilterList	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		GUICmdAckFilterList	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			ShowFilterListDialog	FialogFilterList(GetLayersBase());
			FialogFilterList.Init(GlobalPage,ACmd.FList);
			FialogFilterList.exec();
		}
	}
}



//===============================================================================

bool	GUIFilterList::Save(QIODevice *f)
{
	if(::Save(f,Line)==false)
		return false;
	if(::Save(f,FilterName)==false)
		return false;
	return true;
}

bool	GUIFilterList::Load(QIODevice *f)
{
	if(::Load(f,Line)==false)
		return false;
	if(::Load(f,FilterName)==false)
		return false;
	return true;
}

//===============================================================================
GUICmdReqFilterList::GUICmdReqFilterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqFilterList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckFilterList	*SendBack=GetSendBack(GUICmdAckFilterList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	PageDataInOnePhase	*Ph=GetLayersBase()->GetCurrentPageDataPhase();
	FilterInstanceContainer	*Pc=Ph->GetFilterContainer(localPage);
	if(Pc!=NULL){
		int	Line=0;
		for(FilterInstanceList *a=Pc->GetFirst();a!=NULL;a=a->GetNext()){
			GUIFilterList	*k=new GUIFilterList();
			k->Line=Line;
			k->FilterName=a->GetFilterName();
			SendBack->FList.AppendList(k);
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckFilterList::GUICmdAckFilterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckFilterList::Load(QIODevice *f)
{
	if(FList.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAckFilterList::Save(QIODevice *f)
{
	if(FList.Save(f)==false)
		return false;
	return true;
}

