#include "ListCacherResource.h"
#include "ListCacher.h"
#include "XGeneralFunc.h"
#include "XCacheTargetImage.h"
#include "XDataAlgorithm.h"
#include "XDataAlgorithm.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ListCacher::ListCacher(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
}

ListCacher::~ListCacher()
{

}

CacheTargetImageBase	*ListCacher::GetCacheTargetImageBase(void)
{
	return (CacheTargetImageBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CacheTargetImage");
}

void	ListCacher::ShowInPlayer(int64 shownInspectionID)
{
	CacheTargetImageBase	*ABase=GetCacheTargetImageBase();
	if(ABase!=NULL){
		if(ui.listWidget->count()!=ABase->BufferCount){
			ui.listWidget->clear();
			for(int i=0;i<ABase->BufferCount;i++){
				if((i+1)==ABase->BufferCount){
					ui.listWidget->addItem(LangSolver.GetString(ListCacher_LS,LID_0)/*"Latest"*/);
				}
				else{
					ui.listWidget->addItem(QString::number(ABase->BufferCount-i));
				}
			}
		}
	}

}

void ListCacher::on_pushButtonSetToTarget_clicked()
{	
	int	RNumber=ui.listWidget->currentRow();
	if(RNumber<0)
		return;

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdSetToTarget	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.Number=RNumber;
		RCmd.Send(NULL,globalPage,0);
	}
	BroadcastShowInEdit();
}

void ListCacher::on_pushButtonSavePix_clicked()
{
	int	RNumber=ui.listWidget->currentRow();
	if(RNumber<0)
		return;

	QString	FileName;
	FileName=GetLayersBase()->LGetSaveFileName (this
												,LangSolver.GetString(ListCacher_LS,LID_1)/*"Save Target Image file"*/
												,QString()
												,QString(/**/"ImageFile(*.pix);;AllFile(*.*)")) ;
	if(FileName.isEmpty()==true)
		return;
	SaveImage(RNumber,FileName);
}

bool ListCacher::SaveImage(int RNumber,const QString &FileName)
{
	QFile	WFile(FileName);
	if(WFile.open(QIODevice::WriteOnly)==false)
		return false;

	int	Ver=1;
	if(::Save(&WFile,Ver)==false)
		return false;
	if(::Save(&WFile,(int)GetPageNumb())==false)
		return false;
	if(::Save(&WFile,(int)GetLayerNumb(0))==false)
		return false;
	if(::Save(&WFile,(int)GetDotPerLine(0))==false)
		return false;
	if(::Save(&WFile,(int)GetMaxLines(0))==false)
		return false;
	if(::Save(&WFile,(int)100)==false)
		return false;

	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(ListCacher_LS,LID_2)/*"Save cach image"*/);
	GetLayersBase()->SetMaxProcessing(1);
	for(int page=0;page<GetPageNumb();page++){
		int	YCount=100;
		for(int TopY=0;TopY<GetMaxLines(0);TopY+=YCount){
			if(TopY+YCount>GetMaxLines(0))
				YCount=GetMaxLines(0)-TopY;
			for(int Layer=0;Layer<GetLayerNumb(0);Layer++){
				GUICmdReqSaveCacheImage	RCmd(GetLayersBase() ,sRoot,sName,page);
				RCmd.Layer	=Layer;
				RCmd.TopY	=TopY;
				RCmd.YCount	=YCount;
				RCmd.Number=RNumber;
				GUICmdSendSaveCacheImage	SCmd(GetLayersBase() ,sRoot,sName,page);
				if(RCmd.Send(page ,0,SCmd)==true){
					WFile.write(SCmd.Data);
				}
			}
		}
		GetLayersBase()->StepProcessing(page);
	}
	GetLayersBase()->CloseProcessingForm ();
	return true;
}
//========================================================================================================
GUICmdSetToTarget::GUICmdSetToTarget(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetToTarget::Load(QIODevice *f)
{
	if(::Load(f,Number)==false)
		return false;
	return true;
}
bool	GUICmdSetToTarget::Save(QIODevice *f)
{
	if(::Save(f,Number)==false)
		return false;
	return true;
}

void	GUICmdSetToTarget::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CacheTargetImage");	
	if(ABase!=NULL){
		AlgorithmInPageRoot	*APage=ABase->GetPageData(localPage);
		PacketSetToTarget	Cmd(this);
		Cmd.Number=Number;
		APage->TransmitDirectly(&Cmd);
	}
}

GUICmdReqSaveCacheImage::GUICmdReqSaveCacheImage(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSaveCacheImage::Load(QIODevice *f)
{
	if(::Load(f,TopY)==false)
		return false;
	if(::Load(f,YCount)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Number)==false)
		return false;
	return true;
}
bool	GUICmdReqSaveCacheImage::Save(QIODevice *f)
{
	if(::Save(f,TopY)==false)
		return false;
	if(::Save(f,YCount)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Number)==false)
		return false;
	return true;
}

void	GUICmdReqSaveCacheImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSaveCacheImage	*SendBack=GetSendBack(GUICmdSendSaveCacheImage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CacheTargetImage");	
	if(ABase!=NULL){
		AlgorithmInPagePLI		*APage=(AlgorithmInPagePLI *)ABase->GetPageData(localPage);
		AlgorithmInLayerRoot	*ALayer=APage->GetLayerData(Layer);
		PacketGetImageBuffer	Cmd(this);
		Cmd.Number=Number;
		ALayer->TransmitDirectly(&Cmd);

		SendBack->Data.resize(YCount*APage->GetDotPerLine());
		BYTE	*Dest=(BYTE *)SendBack->Data.data();
		for(int y=TopY;y<TopY+YCount;y++){
			memcpy(Dest,Cmd.Img->GetY(y),APage->GetDotPerLine());
			Dest+=APage->GetDotPerLine();
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendSaveCacheImage::GUICmdSendSaveCacheImage(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendSaveCacheImage::Load(QIODevice *f)
{
	Data=f->readAll();
	return true;
}
bool	GUICmdSendSaveCacheImage::Save(QIODevice *f)
{
	f->write(Data);
	return true;
}

void	GUICmdSendSaveCacheImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
