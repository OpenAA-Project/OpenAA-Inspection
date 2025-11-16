#include "XConfirmPacket.h"
#include "ButtonShowConfirm.h"
#include "XGeneralFunc.h"
#include "ConfirmForm.h"
#include "XDisplayImage.h"
#include "StartProcessAgainButton.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "DisplayNGList.h"
#include "XDataAlgorithmList.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//======================================================================

AlgorithmLibTypeWithAttrData::AlgorithmLibTypeWithAttrData(void)
{
	LibType=-1;
	ShowNGItem=true;
	ShowResultItem=false;
}

bool	AlgorithmLibTypeWithAttrData::Save(QIODevice *f)
{
	if(::Save(f,LibType			)==false)	return false;
	if(::Save(f,ShowOnlyNG		)==false)	return false;
	if(::Save(f,ShowNGItem		)==false)	return false;
	if(::Save(f,ShowResultItem	)==false)	return false;
	return true;
}
bool	AlgorithmLibTypeWithAttrData::Load(QIODevice *f)
{
	if(::Load(f,LibType			)==false)	return false;
	if(::Load(f,ShowOnlyNG		)==false)	return false;
	if(::Load(f,ShowNGItem		)==false)	return false;
	if(::Load(f,ShowResultItem	)==false)	return false;
	return true;
}

void	AlgorithmLibTypeWithAttrData::Add(int _typelib	,bool _ShowOnlyNG 
														,bool _ShowNGItem
														,bool _ShowResultItem)
{
	LibType			=_typelib;
	ShowOnlyNG		=_ShowOnlyNG;
	ShowNGItem		=_ShowNGItem;
	ShowResultItem	=_ShowResultItem;
}

AlgorithmLibTypeWithAttrData	&AlgorithmLibTypeWithAttrData::operator=(const AlgorithmLibTypeWithAttrData &src)
{
	LibType			=src.LibType;
	ShowOnlyNG		=src.ShowOnlyNG;
	ShowNGItem		=src.ShowNGItem;
	ShowResultItem	=src.ShowResultItem;
	return *this;
}

AlgorithmLibTypeWithAttrData	*AlgorithmLibTypeWithAttrDataContainer::Create(void)
{
	return new AlgorithmLibTypeWithAttrData();
}
void	AlgorithmLibTypeWithAttrDataContainer::Add(int _typelib ,bool _ShowOnlyNG 
																,bool _ShowNGItem
																,bool _ShowResultItem)
{
	AlgorithmLibTypeWithAttrData	*a=new AlgorithmLibTypeWithAttrData;
	a->Add(_typelib ,_ShowOnlyNG,_ShowNGItem,_ShowResultItem);
	AppendList(a);
}
AlgorithmLibTypeWithAttrDataContainer	&AlgorithmLibTypeWithAttrDataContainer::operator=(const AlgorithmLibTypeWithAttrDataContainer &src)
{
	RemoveAll();
	for(AlgorithmLibTypeWithAttrData *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibTypeWithAttrData *b=new AlgorithmLibTypeWithAttrData();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

//=================================================================================================
IntegrationReqConfirmPanelImage::IntegrationReqConfirmPanelImage(LayersBase *Base
																	 ,const QString &EmitterRoot,const QString &EmitterName
																	 ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqConfirmPanelImage::Load(QIODevice *f)
{
	if(f->read((char *)&ImageStructData,sizeof(ImageStructData))!=sizeof(ImageStructData)){
		return false;
	}
	if(ALgorithmLibTypeContainer.Load(f)==false)	return false;
	return true;
}
bool	IntegrationReqConfirmPanelImage::Save(QIODevice *f)
{
	if(f->write((const char *)&ImageStructData,sizeof(ImageStructData))!=sizeof(ImageStructData)){
		return false;
	}
	if(ALgorithmLibTypeContainer.Save(f)==false)	return false;
	return true;
}

void	IntegrationReqConfirmPanelImage::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckConfirmPanelImage	*SendBack=GetSendBackIntegration(IntegrationAckConfirmPanelImage,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	ButtonShowConfirm	*Form=NULL;
	GUIFormBase *GUIRet[100];
	int	n=GetLayersBase()->EnumGUIInst(sRoot,sName,GUIRet ,100);
	for(int i=0;i<n;i++){
		ButtonShowConfirm	*f=(ButtonShowConfirm	*)GUIRet[i];
		if(f->SlaveNo==slaveNo){
			Form=f;
			break;
		}
	}
	if(Form!=NULL){
		if(Form->TargetImageWithNG.isNull()==true 
		|| Form->TargetImageWithNG.width() !=ImageStructData.ImageW
		|| Form->TargetImageWithNG.height()!=ImageStructData.ImageH){
			Form->TargetImageWithNG	=QImage(ImageStructData.ImageW,ImageStructData.ImageH,QImage::Format_ARGB32);
		}
		if(Form->TargetImageItems.isNull()==true 
		|| Form->TargetImageItems.width() !=ImageStructData.ImageW
		|| Form->TargetImageItems.height()!=ImageStructData.ImageH){
			Form->TargetImageItems	=QImage(ImageStructData.ImageW,ImageStructData.ImageH,QImage::Format_ARGB32);
		}

		QPainter	Pnt(&Form->TargetImageWithNG);
		Form->TargetImageWithNG.fill(Qt::black);
		{
			PageDataInOnePhase	*ph=GetLayersBase()->GetPageDataPhase(ImageStructData.Phase);
			if(ph!=NULL){
				DataInPage	*dp=ph->GetPageData(LocalPage);
				if(dp!=NULL){
					ImagePointerContainer Images;
					if(ImageStructData.MasterImage==true){
						dp->GetMasterImages	(Images);
					}
					else{
						dp->GetTargetImages	(Images);
					}
					Images.MakeImage(Form->TargetImageWithNG,ImageStructData.movx,ImageStructData.movy,ImageStructData.ZoomRate);

					bool	RetNGData;
					GetLayersBase()->MakeImageNGCircle(&Form->TargetImageWithNG,&Pnt
													   ,(int)DisplayImage::__Target
													   ,0,0,ImageStructData.ImageW,ImageStructData.ImageH
													   ,ImageStructData.movx,ImageStructData.movy,ImageStructData.ZoomRate
													   ,LocalPage
													   ,true
													   ,true
													   ,RetNGData);
				}
			}
		}
		{
			Form->TargetImageItems.fill(qRgba(0,0,0,0));
			IntList LayerList;
			for(int Layer=0;Layer<GetLayerNumb(LocalPage);Layer++){
				LayerList.Add(Layer);
			}
			ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
			for(AlgorithmLibTypeWithAttrData *a=ALgorithmLibTypeContainer.GetFirst();a!=NULL;a=a->GetNext()){
				int	LibType=a->LibType;
				AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
				if(ABase!=NULL){
					AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(ImageStructData.Phase);
					if(Ah!=NULL){
						AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
						if(Ap!=NULL){
							ResultInPageRoot *R=Ap->GetResultPointer(Res);
							if(R!=NULL){
								//Ap->DrawResult	  (R,Form->TargetImageItems ,Pnt ,movx,movy,ZoomRate);
								if(a->ShowNGItem==true){
									Ap->DrawResultItem(R,LayerList ,Form->TargetImageItems ,Pnt 
													   ,ImageStructData.movx,ImageStructData.movy,ImageStructData.ZoomRate,a->ShowOnlyNG);
								}
								Ap->DrawItems(Form->TargetImageItems ,Pnt  ,LayerList 
													,ImageStructData.movx,ImageStructData.movy,ImageStructData.ZoomRate,DrawType_Active | DrawType_Selected);
								if(a->ShowResultItem==true){
									Ap->DrawResultItem(NULL
													,Form->TargetImageItems ,Pnt  ,LayerList 
													,ImageStructData.movx,ImageStructData.movy,ImageStructData.ZoomRate,DrawType_Selected);
								}
							}
						}
					}
				}
			}
			Pnt.drawImage(0,0,Form->TargetImageItems);
		}

		if(Form->TargetImageWithNGXLen!=Form->TargetImageWithNG.width()
		   || Form->TargetImageWithNGYLen!=Form->TargetImageWithNG.height()){
			if(Form->TargetImageWithNGBuff!=NULL){
				delete	[]Form->TargetImageWithNGBuff;
			}
			Form->TargetImageWithNGXLen	=Form->TargetImageWithNG.width();
			Form->TargetImageWithNGYLen	=Form->TargetImageWithNG.height();
			Form->TargetImageWithNGBuff=new BYTE[Form->TargetImageWithNGXLen*Form->TargetImageWithNGYLen*4];
		}
		int	dlen=Form->TargetImageWithNGXLen*4;
		for(int y=0;y<Form->TargetImageWithNGYLen;y++){
			BYTE	*s=Form->TargetImageWithNG.scanLine(y);
			BYTE	*d=&Form->TargetImageWithNGBuff[y*dlen];
			memcpy(d,s,dlen);
		}
	}

	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}


IntegrationAckConfirmPanelImage::IntegrationAckConfirmPanelImage(LayersBase *Base
																	 ,const QString &EmitterRoot,const QString &EmitterName
																	 ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

struct IntegrationAckConfirmPanelImageData
{
	int		TargetImageWithNGXLen;
	int		TargetImageWithNGYLen;
};


bool	IntegrationAckConfirmPanelImage::Load(QIODevice *f)
{
	struct IntegrationAckConfirmPanelImageData	Data;
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))	return false;

	ButtonShowConfirm	*Form=NULL;
	GUIFormBase *GUIRet[100];
	int	n=GetLayersBase()->EnumGUIInst(sRoot,sName,GUIRet ,100);
	for(int i=0;i<n;i++){
		ButtonShowConfirm	*f=(ButtonShowConfirm	*)GUIRet[i];
		if(f->SlaveNo==GetSlaveNo()){
			Form=f;
			break;
		}
	}
	if(Form!=NULL){
		int	XYLen=Data.TargetImageWithNGXLen*Data.TargetImageWithNGYLen*4;
		if(Form->TargetImageWithNGXLen	!=Data.TargetImageWithNGXLen
		   || Form->TargetImageWithNGYLen	!=Data.TargetImageWithNGYLen){
			if(Form->TargetImageWithNGBuff!=NULL){
				delete	[]Form->TargetImageWithNGBuff;
			}
			Form->TargetImageWithNGXLen	=Data.TargetImageWithNGXLen;
			Form->TargetImageWithNGYLen	=Data.TargetImageWithNGYLen;
			Form->TargetImageWithNGBuff=new BYTE[XYLen];
			Form->TargetImageWithNG=QImage(Form->TargetImageWithNGXLen,Form->TargetImageWithNGYLen,QImage::Format_ARGB32);
		}
		if(f->read((char *)Form->TargetImageWithNGBuff,XYLen)!=XYLen)	return false;

		int	dlen=Form->TargetImageWithNGXLen*4;
		for(int y=0;y<Form->TargetImageWithNGYLen;y++){
			BYTE	*d=Form->TargetImageWithNG.scanLine(y);
			BYTE	*s=&Form->TargetImageWithNGBuff[y*dlen];
			memcpy(d,s,dlen);
		}
	}

	return true;
}
bool	IntegrationAckConfirmPanelImage::Save(QIODevice *f)
{
	ButtonShowConfirm	*Form=NULL;
	GUIFormBase *GUIRet[100];
	int	n=GetLayersBase()->EnumGUIInst(sRoot,sName,GUIRet ,100);
	for(int i=0;i<n;i++){
		ButtonShowConfirm	*f=(ButtonShowConfirm	*)GUIRet[i];
		if(f->SlaveNo==GetSlaveNo()){
			Form=f;
			break;
		}
	}
	struct IntegrationAckConfirmPanelImageData	Data;
	if(Form!=NULL){
		Data.TargetImageWithNGXLen	=Form->TargetImageWithNGXLen;
		Data.TargetImageWithNGYLen	=Form->TargetImageWithNGYLen;
	}
	else{
		memset(&Data,0,sizeof(Data));
	}
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))	return false;
	if(Form!=NULL){
		int	dlen=Data.TargetImageWithNGXLen*Data.TargetImageWithNGYLen*4;
		if(f->write((const char *)Form->TargetImageWithNGBuff,dlen)!=dlen)	return false;
	}
	return true;
}

//=================================================================================================
IntegrationConfirmRetry::IntegrationConfirmRetry(LayersBase *Base 
												,const QString &EmitterRoot,const QString &EmitterName
												,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

void	IntegrationConfirmRetry::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{

	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Action",/**/"StartProcessAgainButton",/**/"");
	if(f!=NULL){
		CmdReqPush	Cmd(GetLayersBase());
		f->TransmitDirectly(&Cmd);
	}
	SendAck(slaveNo);
}

//=================================================================================================

IntegrationSetSelectedArea::IntegrationSetSelectedArea(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationSetSelectedArea::Load(QIODevice *f)
{
	if(SelectedArea.Load(f)==false)	return false;
	return true;
}
bool	IntegrationSetSelectedArea::Save(QIODevice *f)
{
	if(SelectedArea.Save(f)==false)	return false;
	return true;
}

void	IntegrationSetSelectedArea::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	if(LocalPage==0){
		ButtonShowConfirm	*Form=NULL;
		GUIFormBase *GUIRet[100];
		int	n=GetLayersBase()->EnumGUIInst(sRoot,sName,GUIRet ,100);
		for(int i=0;i<n;i++){
			ButtonShowConfirm	*f=(ButtonShowConfirm	*)GUIRet[i];
			if(f->SlaveNo==GetSlaveNo()){
				Form=f;
				break;
			}
		}
		if(Form!=NULL && Form->GetWindow()!=NULL){
			Form->GetWindow()->SetSelectedArea(SelectedArea);
		}
	}
}

//=================================================================================================

IntegrationSetActivateItem::IntegrationSetActivateItem(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationSetActivateItem::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,localX	)==false)	return false;
	if(::Load(f,localY	)==false)	return false;
	if(::Load(f,LibType	)==false)	return false;
	if(LayerList.Load(f)==false)	return false;
	return true;
}
bool	IntegrationSetActivateItem::Save(QIODevice *f)
{
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,localX	)==false)	return false;
	if(::Save(f,localY	)==false)	return false;
	if(::Save(f,LibType	)==false)	return false;
	if(LayerList.Save(f)==false)	return false;
	return true;
}

void	IntegrationSetActivateItem::Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				ListLayerAndIDPack RetItem;
				Ap->Activate(localX,localY,LayerList ,RetItem);
			}
		}
	}
}

//=================================================================================================

IntegrationReqThresholdLibID::IntegrationReqThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
	FilterLibType=-1;
}

bool	IntegrationReqThresholdLibID::Load(QIODevice *f)
{
	if(::Load(f,FilterLibType)	==false)	return false;
	if(Area.Load(f)		==false)			return false;
	if(::Load(f,Phase)	==false)			return false;
	return true;
}
bool	IntegrationReqThresholdLibID::Save(QIODevice *f)
{
	if(::Save(f,FilterLibType)	==false)	return false;
	if(Area.Save(f)		==false)			return false;
	if(::Save(f,Phase)	==false)			return false;
	return true;
}

void	IntegrationReqThresholdLibID::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckThresholdLibID	*SendBack=GetSendBackIntegration(IntegrationAckThresholdLibID,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	PageDataInOnePhase	*ph=GetLayersBase()->GetPageDataPhase(Phase);
	if(ph!=NULL){
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(Area,PageList);
		for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
			int	page=c->GetValue();
			DataInPage	*dp=ph->GetPageData(page);
			if(dp!=NULL){
				GUICmdReqThresholdLibID	RCmd(GetLayersBase(),EmitterRoot,EmitterName,page);
				RCmd.FilterLibType=FilterLibType;
				RCmd.Area=Area;
				RCmd.Area.MoveToNoClip(-dp->GetOutlineOffset()->x,-dp->GetOutlineOffset()->y);
				RCmd.Phase		=Phase;
				GUICmdAckThresholdLibID	ACmd(GetLayersBase(),EmitterRoot,EmitterName,page);
				if(RCmd.Send(page,0,ACmd)==true){
					SendBack->Libs.Merge(ACmd.Libs);
				}
			}
		}
	}
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckThresholdLibID::IntegrationAckThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckThresholdLibID::Load(QIODevice *f)
{
	if(Libs.Load(f)==false)	return false;
	return true;
}
bool	IntegrationAckThresholdLibID::Save(QIODevice *f)
{
	if(Libs.Save(f)==false)	return false;
	return true;
}

GUICmdReqThresholdLibID::GUICmdReqThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),GlobanPage)
{
}
bool	GUICmdReqThresholdLibID::Load(QIODevice *f)
{
	if(::Load(f,FilterLibType)	==false)	return false;
	if(Area.Load(f)		==false)	return false;
	if(::Load(f,Phase)	==false)	return false;
	return true;
}
bool	GUICmdReqThresholdLibID::Save(QIODevice *f)
{
	if(::Save(f,FilterLibType)	==false)	return false;
	if(Area.Save(f)		==false)	return false;
	if(::Save(f,Phase)	==false)	return false;
	return true;
}

class SelectByItemsAlgorithm
{
public:
	FlexArea	Area;
	int			Layer;

	SelectByItemsAlgorithm(){	Layer=0;	}
	~SelectByItemsAlgorithm(){}
};

bool SelectByItemsAlgorithmFunc(void *caller,AlgorithmItemRoot *item)
{
	SelectByItemsAlgorithm	*p=(SelectByItemsAlgorithm *)caller;
	if(item->GetLayer()!=p->Layer)
		return false;
	if(item->GetArea().CheckOverlap(&p->Area)==true){
		return true;
	}
	return false;
}

void	GUICmdReqThresholdLibID::Receive(int32 localPage,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckThresholdLibID	*SendBack=GetSendBack(GUICmdAckThresholdLibID,GetLayersBase(),EmitterRoot,EmitterName,localPage);

	SelectByItemsAlgorithm	Selector;
	Selector.Area=Area;
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*A=L->GetInstance();
		if(A!=NULL
		   && A->GetLibType()>0
		   && A->GetLogicDLL()!=NULL
		   && A->GetLogicDLL()->IsProcessAlgorithm()==true){
			AlgorithmInPageRoot		*PData=A->GetPageData(localPage);
			if(PData!=NULL){
				for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
					Selector.Layer=Layer;
					AlgorithmItemPointerListContainer Items;
					PData->EnumItems(&Selector,Items , SelectByItemsAlgorithmFunc);
					for(AlgorithmItemPointerList *p=Items.GetFirst();p!=NULL;p=p->GetNext()){
						if(FilterLibType==-1 || FilterLibType==A->GetLibType()){
							SendBack->Libs.Merge(GetLayersBase(),A->GetLibType(),p->GetItem()->GetLibID());
						}
					}
				}
			}
		}
	}
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckThresholdLibID::GUICmdAckThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),GlobanPage)
{
}

bool	GUICmdAckThresholdLibID::Load(QIODevice *f)
{
	if(Libs.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckThresholdLibID::Save(QIODevice *f)
{
	if(Libs.Save(f)==false)	return false;
	return true;
}

//=================================================================================================

IntegrationReqSelectItems::IntegrationReqSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
	Mode=-1;
}

bool	IntegrationReqSelectItems::Load(QIODevice *f)
{
	if(SelectedLib.Load(f)	==false)	return false;
	if(GlobalArea.Load(f)	==false)	return false;
	if(::Load(f,Phase)		==false)	return false;
	if(::Load(f,GlobalX)	==false)	return false;
	if(::Load(f,GlobalY)	==false)	return false;
	if(::Load(f,Mode)		==false)	return false;
	return true;
}
bool	IntegrationReqSelectItems::Save(QIODevice *f)
{
	if(SelectedLib.Save(f)	==false)	return false;
	if(GlobalArea.Save(f)	==false)	return false;
	if(::Save(f,Phase)		==false)	return false;
	if(::Save(f,GlobalX)	==false)	return false;
	if(::Save(f,GlobalY)	==false)	return false;
	if(::Save(f,Mode)		==false)	return false;
	return true;
}

void	IntegrationReqSelectItems::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckSelectItems	*SendBack=GetSendBackIntegration(IntegrationAckSelectItems,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	PageDataInOnePhase	*ph=GetLayersBase()->GetPageDataPhase(Phase);
	if(ph!=NULL){
		if(Mode==0){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(GlobalArea,PageList);
			for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
				int	page=c->GetValue();
				DataInPage	*dp=ph->GetPageData(page);
				if(dp!=NULL){
					GUICmdReqSelectItems	RCmd(GetLayersBase(),EmitterRoot,EmitterName,page);
					RCmd.SelectedLib=SelectedLib;
					RCmd.LocalArea=GlobalArea;
					dp->ClipMoveAreaFromGlobal(RCmd.LocalArea);
					RCmd.Phase		=Phase;
					RCmd.Mode=Mode;
					GUICmdAckSelectItems	ACmd(GetLayersBase(),EmitterRoot,EmitterName,page);
					if(RCmd.Send(page,0,ACmd)==true){
						SendBack->Items.Merge(ACmd.Items);
					}
				}
			}
		}
		else if(Mode==1){
			IntList PageList;
			GetLayersBase()->GetGlobalPage(GlobalX ,GlobalY,PageList);
			for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
				int	page=c->GetValue();
				DataInPage	*dp=ph->GetPageData(page);
				if(dp!=NULL){
					GUICmdReqSelectItems	RCmd(GetLayersBase(),EmitterRoot,EmitterName,page);
					RCmd.SelectedLib=SelectedLib;
					dp->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,RCmd.LocalX ,RCmd.LocalY);
					RCmd.Phase		=Phase;
					RCmd.Mode=Mode;
					GUICmdAckSelectItems	ACmd(GetLayersBase(),EmitterRoot,EmitterName,page);
					if(RCmd.Send(page,0,ACmd)==true){
						SendBack->Items.Merge(ACmd.Items);
					}
				}
			}
		}
		else if(Mode==2){
			for(int page=0;page<GetPageNumb();page++){
				GUICmdReqSelectItems	RCmd(GetLayersBase(),EmitterRoot,EmitterName,page);
				RCmd.SelectedLib=SelectedLib;
				RCmd.Phase		=Phase;
				RCmd.Mode=Mode;
				GUICmdAckSelectItems	ACmd(GetLayersBase(),EmitterRoot,EmitterName,page);
				if(RCmd.Send(page,0,ACmd)==true){
					SendBack->Items.Merge(ACmd.Items);
				}
			}
		}
	}
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckSelectItems::IntegrationAckSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckSelectItems::Load(QIODevice *f)
{
	if(Items.Load(f)==false)	return false;
	return true;
}
bool	IntegrationAckSelectItems::Save(QIODevice *f)
{
	if(Items.Save(f)==false)	return false;
	return true;
}

GUICmdReqSelectItems::GUICmdReqSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),GlobanPage)
{
	Mode=-1;
}
bool	GUICmdReqSelectItems::Load(QIODevice *f)
{
	if(SelectedLib.Load(f)	==false)	return false;
	if(LocalArea.Load(f)	==false)	return false;
	if(::Load(f,Phase)		==false)	return false;
	if(::Load(f,LocalX)		==false)	return false;
	if(::Load(f,LocalY)		==false)	return false;
	if(::Load(f,Mode)		==false)	return false;
	return true;
}
bool	GUICmdReqSelectItems::Save(QIODevice *f)
{
	if(SelectedLib.Save(f)	==false)	return false;
	if(LocalArea.Save(f)	==false)	return false;
	if(::Save(f,Phase)		==false)	return false;
	if(::Save(f,LocalX)		==false)	return false;
	if(::Save(f,LocalY)		==false)	return false;
	if(::Save(f,Mode)		==false)	return false;
	return true;
}

void	GUICmdReqSelectItems::Receive(int32 localPage,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckSelectItems	*SendBack=GetSendBack(GUICmdAckSelectItems,GetLayersBase(),EmitterRoot,EmitterName,localPage);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(SelectedLib.GetLibType());
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				AlgorithmItemPointerListContainer ItemPointers;
				if(SelectedLib.GetLibID()>=0){
					IntList LibIDs;
					LibIDs.Add(SelectedLib.GetLibID());
					Ap->EnumItemsByLib(LibIDs ,ItemPointers);
				}
				else{
					Ap->EnumAllItems(ItemPointers);
				}
				int		GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
				if(Mode==0){
					for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
						AlgorithmItemRoot	*Item=a->GetItem();
						if(Item->IsCrossed(&LocalArea)==true){
							SendBack->Items.Add(Phase,GlobalPage,Item->GetLayer(),Item->GetID());
						}
					}
				}
				else if(Mode==1){
					for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
						AlgorithmItemRoot	*Item=a->GetItem();
						if(Item->IsInclude(LocalX,LocalY)==true
						|| (Item->GetVector()!=NULL && Item->GetVector()->GetDistance(LocalX,LocalY)<10)){
							SendBack->Items.Add(Phase,GlobalPage,Item->GetLayer(),Item->GetID());
						}
					}
				}
				else if(Mode==3){
					for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
						AlgorithmItemRoot	*Item=a->GetItem();
						SendBack->Items.Add(Phase,GlobalPage,Item->GetLayer(),Item->GetID());
					}
				}
			}
		}
	}

	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckSelectItems::GUICmdAckSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),GlobanPage)
{
}

bool	GUICmdAckSelectItems::Load(QIODevice *f)
{
	if(Items.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckSelectItems::Save(QIODevice *f)
{
	if(Items.Save(f)==false)	return false;
	return true;
}

IntegrationReqSelectItemsByGroupID::IntegrationReqSelectItemsByGroupID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqSelectItemsByGroupID::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)		return false;
	if(::Load(f,Phase)==false)			return false;
	if(::Load(f,ErrorGroupID)==false)	return false;
	return true;
}
bool	IntegrationReqSelectItemsByGroupID::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)		return false;
	if(::Save(f,Phase)==false)			return false;
	if(::Save(f,ErrorGroupID)==false)	return false;
	return true;
}

void	IntegrationReqSelectItemsByGroupID::Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckSelectItemsByGroupID	*SendBack=GetSendBackIntegration(IntegrationAckSelectItemsByGroupID,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	ResultInspection	*RBase=GetLayersBase()->GetCurrentResultForDraw();
	if(RBase!=NULL){
		ResultBaseForAlgorithmRoot	*R=RBase->GetResultBaseForAlgorithm(LibType);
		if(R!=NULL){
			ResultBasePhase		*Rh=R->GetPageDataPhase(Phase);
			if(Rh!=NULL){
				ResultInPageRoot	*Rp=Rh->GetPageData(LocalPage);
				if(Rp!=NULL){
					NPListPack<ResultInItemRootPointerList> ResultItemList;
					Rp->GetItemListByErrorGroupID(ResultItemList ,ErrorGroupID);
					for(ResultInItemRootPointerList *r=ResultItemList.GetFirst();r!=NULL;r=r->GetNext()){
						SendBack->Items.Add(Phase,globalPage,r->Pointer->GetLayer(),r->Pointer->GetItemID());
					}
				}
			}
		}
	}

	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);						
}


IntegrationAckSelectItemsByGroupID::IntegrationAckSelectItemsByGroupID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckSelectItemsByGroupID::Load(QIODevice *f)
{
	if(Items.Load(f)==false)	return false;
	return true;
}
bool	IntegrationAckSelectItemsByGroupID::Save(QIODevice *f)
{
	if(Items.Save(f)==false)	return false;
	return true;
}
//=================================================================================================

IntegrationReqItemThresholdData::IntegrationReqItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqItemThresholdData::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)	return false;
	if(ItemIndex.Load(f)==false)	return false;
	return true;
}
bool	IntegrationReqItemThresholdData::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)	return false;
	if(ItemIndex.Save(f)==false)	return false;
	return true;
}
void	IntegrationReqItemThresholdData::Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckItemThresholdData	*SendBack=GetSendBackIntegration(IntegrationAckItemThresholdData,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(ItemIndex.Data.Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				AlgorithmItemRoot	*Item=Ap->GetItemData(ItemIndex.Data.Layer,ItemIndex.Data.ItemID);
				if(Item!=NULL){
					const AlgorithmThreshold	*R=Item->GetThresholdBaseReadable();
					QBuffer	Buff;
					Buff.open(QIODevice::ReadWrite);
					if(((AlgorithmThreshold	*)R)->Save(&Buff)==true){
						SendBack->ItemClass=Item->GetItemClassType();
						SendBack->ThresholdData=Buff.buffer();
						SendBack->LibID		=Item->GetLibID();
					}
				}
			}
		}
	}
	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckItemThresholdData::IntegrationAckItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckItemThresholdData::Load(QIODevice *f)
{
	if(::Load(f,ItemClass		)==false)	return false;
	if(::Load(f,ThresholdData	)==false)	return false;
	if(::Load(f,LibID			)==false)	return false;
	return true;
}
bool	IntegrationAckItemThresholdData::Save(QIODevice *f)
{
	if(::Save(f,ItemClass		)==false)	return false;
	if(::Save(f,ThresholdData	)==false)	return false;
	if(::Save(f,LibID			)==false)	return false;
	return true;
}

IntegrationSetItemThresholdData::IntegrationSetItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationSetItemThresholdData::Load(QIODevice *f)
{
	if(::Load(f,LibType			)==false)	return false;
	if(::Load(f,ThresholdData	)==false)	return false;
	if(ItemIndex.Load(f)==false)	return false;
	return true;
}
bool	IntegrationSetItemThresholdData::Save(QIODevice *f)
{
	if(::Save(f,LibType			)==false)	return false;
	if(::Save(f,ThresholdData	)==false)	return false;
	if(ItemIndex.Save(f)==false)	return false;
	return true;
}

void	IntegrationSetItemThresholdData::Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(ItemIndex.Data.Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				AlgorithmItemRoot	*Item=Ap->GetItemData(ItemIndex.Data.Layer,ItemIndex.Data.ItemID);
				if(Item!=NULL){
					AlgorithmThreshold	*W=Item->GetThresholdBaseWritable();
					QBuffer	Buff(&ThresholdData);
					Buff.open(QIODevice::ReadWrite);
					W->Load(&Buff);
				}
			}
		}
	}
}

//=================================================================================================

IntegrationSetSelectItems::IntegrationSetSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationSetSelectItems::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)	return false;
	if(Items.Load(f)==false)	return false;
	return true;
}
bool	IntegrationSetSelectItems::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)	return false;
	if(Items.Save(f)==false)	return false;
	return true;
}

void	IntegrationSetSelectItems::Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		IntList	PhaseList;
		Items.GetPhaseList(PhaseList);
		for(IntClass *p=PhaseList.GetFirst();p!=NULL;p=p->GetNext()){
			int	Phase=p->GetValue();
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
				if(Ap!=NULL){
					Ap->ReleaseAllSelectedItem();
					int		GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
					ListLayerAndIDPack SelectedItem;
					for(ListPhasePageLayerItem *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
						if(a->Data.Phase==Phase && a->Data.Page==GlobalPage){
							SelectedItem.AppendList(new ListLayerAndID(a->Data.Layer,a->Data.ItemID));
						}
					}
					Ap->SelectItemByID(SelectedItem);
				}
			}
		}
	}
}

//=================================================================================================

IntegrationClearSelectItems::IntegrationClearSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationClearSelectItems::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)	return false;
	return true;
}
bool	IntegrationClearSelectItems::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)	return false;
	return true;
}
void	IntegrationClearSelectItems::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		for(int Phase=0;Phase<GetPhaseNumb();Phase++){
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
				if(Ap!=NULL){
					Ap->ReleaseAllSelectedItem();
				}
			}
		}
	}
}

//=================================================================================================

bool	ResultForConfirmList::Save(QIODevice *f)
{
	if(f->write((const char *)&NGInfoData,sizeof(NGInfoData))!=sizeof(NGInfoData)){
		return false;
	}
	if(::Save(f,Name	)==false)	return false;
	if(::Save(f,Cause	)==false)	return false;
	if(::Save(f,Message	)==false)	return false;
	return true;
}
bool	ResultForConfirmList::Load(QIODevice *f)
{
	if(f->read((char *)&NGInfoData,sizeof(NGInfoData))!=sizeof(NGInfoData)){
		return false;
	}
	if(::Load(f,Name	)==false)	return false;
	if(::Load(f,Cause	)==false)	return false;
	if(::Load(f,Message	)==false)	return false;
	return true;
}
	
ResultForConfirmList	&ResultForConfirmList::operator=(const ResultForConfirmList &src)
{
	NGInfoData=src.NGInfoData;
	Name	=src.Name	;
	Cause	=src.Cause	;
	Message	=src.Message;	
	return *this;
}

ResultForConfirmListContainer	&ResultForConfirmListContainer::operator+=(const ResultForConfirmListContainer &src)
{
	for(ResultForConfirmList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ResultForConfirmList	*b=new ResultForConfirmList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

ResultForConfirmListContainer	&ResultForConfirmListContainer::operator=(const ResultForConfirmListContainer &src)
{
	RemoveAll();
	operator+=(src);
	return *this;
}

IntegrationReqCurrentResult::IntegrationReqCurrentResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

void	IntegrationReqCurrentResult::Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	LayersBase	*LBase=GetLayersBase();
	int	globalPage=LBase->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckCurrentResult	*SendBack=GetSendBackIntegration(IntegrationAckCurrentResult,LBase,EmitterRoot,EmitterName,slaveNo);

	DisplayNGList	*f=dynamic_cast<DisplayNGList *>(LBase->FindByName(/**/"Inspection",/**/"DisplayNGList",/**/""));
	if(f!=NULL){
		ResultInspection *Res=LBase->GetCurrentResultForDraw();
		if(Res!=NULL){
			for(int phase=0;phase<f->PhaseNumb;phase++){
				for(int page=0;page<GetPageNumb();page++){
					if(f->ErrorGroupData[phase][page]!=NULL){
						int	GlobalPage=LBase->GetGlobalPageFromLocal(page);
						for(ErrorGroup *e=f->ErrorGroupData[phase][page]->GetFirst();e!=NULL;e=e->GetNext()){
							ResultForConfirmList	*L=new ResultForConfirmList();
							e->GetCenter(L->NGInfoData.cx, L->NGInfoData.cy);
							L->NGInfoData.NGErrorGroupID=e->GetErrorGroupID();
							L->NGInfoData.NGPhase		=phase;
							L->NGInfoData.NGGlobalPage	=GlobalPage;
							L->NGInfoData.NGLibType		=e->GetRepresentativeItem()->LibType;
							L->NGInfoData.NGLayer		=e->GetRepresentativeItem()->Layer;
							L->NGInfoData.NGItemID		=e->GetRepresentativeItem()->ItemID;
							L->Cause		=e->GetCause();
							L->Name			=e->GetName();
							L->Message		=e->GetMessageStr();

							if(e->HasRepresentativeItem()==true){
								ResultBaseForAlgorithmRoot	*ResBase=Res->GetResultBaseForAlgorithm(L->NGInfoData.NGLibType);
								if(ResBase!=NULL){
									ResultBasePhase	*ResH=ResBase->GetPageDataPhase(L->NGInfoData.NGPhase);
									if(ResH!=NULL){
										ResultInPageRoot	*ResP=ResH->GetPageData(page);
										if(ResP!=NULL){
											ResultInItemRoot	*ResItem=ResP->FindResultInItem(L->NGInfoData.NGLayer ,L->NGInfoData.NGItemID);
											if(ResItem!=NULL){
												AlgorithmBase		*ABase=ResBase->GetAlgorithm();
												if(ABase!=NULL){
													DetailResultInfoListContainer RetList;
													ResultPosList	*PosList=ResItem->GetPosListFirst();
													if(ResItem->GetAlgorithmItem()!=NULL && PosList!=NULL){
														ABase->GetDrawResultDetail(ResItem->GetAlgorithmItem() ,PosList ,RetList);
														DetailResultInfoList	*RL=RetList.NPListPack<DetailResultInfoList>::GetFirst();
														if(L!=NULL){
															DetailResultValueList	*f=RL->ResultValueContainer.GetFirst();
															if(f!=NULL){
																L->Message=f->GetResultValue();
															}
														}
													}
												}
											}
										}
									}
								}
							}
							SendBack->ResultContainer.AppendList(L);
						}
					}
				}
			}
		}
	}

	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckCurrentResult::IntegrationAckCurrentResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckCurrentResult::Load(QIODevice *f)
{
	if(ResultContainer.Load(f)==false)	return false;
	return true;
}
bool	IntegrationAckCurrentResult::Save(QIODevice *f)
{
	if(ResultContainer.Save(f)==false)	return false;
	return true;
}

//=================================================================================================

IntegrationReqCurrentProcessTime::IntegrationReqCurrentProcessTime(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

void	IntegrationReqCurrentProcessTime::Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	LayersBase	*LBase=GetLayersBase();
	int	globalPage=LBase->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckCurrentProcessTime	*SendBack=GetSendBackIntegration(IntegrationAckCurrentProcessTime,LBase,EmitterRoot,EmitterName,slaveNo);

	ResultInspection	*Res=GetLayersBase()->GetCurrentResultForDraw();
	if(Res!=NULL){
		SendBack->MiliSec	=Res->ExecTime.TM_ExecutePreAlignment
							+Res->ExecTime.TM_ExecuteAlignment
							+Res->ExecTime.TM_ExecutePreProcessing
							+Res->ExecTime.TM_ExecuteProcessing
							+Res->ExecTime.TM_ExecuteProcessingRevived
							+Res->ExecTime.TM_ExecutePostProcessing;
	}
	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckCurrentProcessTime::IntegrationAckCurrentProcessTime(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckCurrentProcessTime::Load(QIODevice *f)
{
	if(::Load(f,MiliSec)==false)
		return false;
	return true;
}
bool	IntegrationAckCurrentProcessTime::Save(QIODevice *f)
{
	if(::Save(f,MiliSec)==false)
		return false;
	return true;
}

//=================================================================================================
IntegrationCmdReqConfirmItemList::IntegrationCmdReqConfirmItemList(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdReqConfirmItemList::Load(QIODevice *f)
{
	if(::Load(f,AlgorithmRoot)==false)	return false;
	if(::Load(f,AlgorithmName)==false)	return false;
	return true;
}
bool	IntegrationCmdReqConfirmItemList::Save(QIODevice *f)
{
	if(::Save(f,AlgorithmRoot)==false)	return false;
	if(::Save(f,AlgorithmName)==false)	return false;
	return true;
}
void	IntegrationCmdReqConfirmItemList::Receive(int32 SlaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckConfirmItemList	*SendBack=GetSendBackIntegration(IntegrationCmdAckConfirmItemList,GetLayersBase(),EmitterRoot,EmitterName,SlaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(AlgorithmRoot,AlgorithmName);
	for(int page=0;page<GetPageNumb();page++){
		ConfirmItemListContainer	RetItemList;
		ABase->ReqConfirmItemList(page,RetItemList);
		SendBack->ItemList.AddMove(RetItemList);
	}
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(SlaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationCmdAckConfirmItemList::IntegrationCmdAckConfirmItemList(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckConfirmItemList::Load(QIODevice *f)
{
	if(ItemList.Load(f)==false)	return false;
	return true;
}
bool	IntegrationCmdAckConfirmItemList::Save(QIODevice *f)
{
	if(ItemList.Save(f)==false)	return false;
	return true;
}
//=================================================================================================

IntegrationReqConfirmItemInfo::IntegrationReqConfirmItemInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqConfirmItemInfo::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)	return false;
	if(ItemIndex.Load(f)==false)	return false;
	return true;
}
bool	IntegrationReqConfirmItemInfo::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)	return false;
	if(ItemIndex.Save(f)==false)	return false;
	return true;
}
void	IntegrationReqConfirmItemInfo::Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckConfirmItemInfo	*SendBack=GetSendBackIntegration(IntegrationAckConfirmItemInfo,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(ItemIndex.Data.Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				AlgorithmItemRoot	*Item=Ap->GetItemData(ItemIndex.Data.Layer,ItemIndex.Data.ItemID);
				if(Item!=NULL){
					int	x1,y1,x2,y2;
					Item->GetXY(x1,y1,x2,y2);
					SendBack->Data.x1=x1;
					SendBack->Data.y1=y1;
					SendBack->Data.x2=x2;
					SendBack->Data.y2=y2;
					SendBack->Data.LibID=Item->GetLibID();
				}
			}
		}
	}
	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckConfirmItemInfo::IntegrationAckConfirmItemInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo )
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckConfirmItemInfo::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
bool	IntegrationAckConfirmItemInfo::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}