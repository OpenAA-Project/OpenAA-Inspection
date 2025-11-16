#include "CompressImageIndicatorResource.h"
#include "CompressImageIndicatorForm.h"
#include "ui_CompressImageIndicatorForm.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

CompressImageIndicatorForm::CompressImageIndicatorForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::CompressImageIndicatorForm)
{
    ui->setupUi(this);
}

CompressImageIndicatorForm::~CompressImageIndicatorForm()
{
    delete ui;
}


bool CompressImageIndicatorForm::OnIdle(void)
{
	static	int	Counter=0;

	Counter++;

	if((Counter&0x0f)!=0)
		return true;

	int	CurrentMax=0;
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdSendCountOfCompressImage		BmpReceiver	(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdReqCountOfCompressImage		BmpRequester(GetLayersBase(),sRoot,sName,globalPage);
		if(BmpRequester.Send(BmpRequester.GetGlobalPage(),0,BmpReceiver)==true){
			CurrentMax=max(CurrentMax,BmpReceiver.Count);
			
		}
	}
	ui->progressBar->setMaximum(GetParamGlobal()->NGCacheNumb);
	ui->progressBar->setValue(CurrentMax);
	return true;
}

//-----------------------------------------------------------------------------------------------------------

GUICmdReqCountOfCompressImage::GUICmdReqCountOfCompressImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}

void	GUICmdReqCountOfCompressImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendCountOfCompressImage	*SendBack=GetSendBack(GUICmdSendCountOfCompressImage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	SendBack->Count=GetLayersBase()->GetCountOfCompressing();

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendCountOfCompressImage::GUICmdSendCountOfCompressImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}

bool	GUICmdSendCountOfCompressImage::Load(QIODevice *f)
{
	if(::Load(f,Count)==false)
		return false;
	return true;
}
bool	GUICmdSendCountOfCompressImage::Save(QIODevice *f)
{
	if(::Save(f,Count)==false)
		return false;
	return true;
}