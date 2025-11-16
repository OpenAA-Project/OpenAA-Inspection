#include "XEachThresholdCommon.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "CartonMenuForm.h"
#include "ButtonSettingThresholdForm.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//=================================================================================================
	
IntegrationReqRepresentative::IntegrationReqRepresentative(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqRepresentative::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false)	return false;
	AreaType=(EachThresholdCommon::__AreaType)d;
	BYTE	e;
	if(::Load(f,e)==false)	return false;
	InspectionType=(EachThresholdCommon::__InspectionType)e;
	if(::Load(f,CartonParam)==false)	return false;
	if(LibIDs.Load(f)==false)		return false;
	return true;
}
bool	IntegrationReqRepresentative::Save(QIODevice *f)
{
	BYTE	d=(BYTE)AreaType;
	if(::Save(f,d)==false)	return false;
	BYTE	e=(BYTE)InspectionType;
	if(::Save(f,e)==false)	return false;
	if(::Save(f,CartonParam)==false)	return false;
	if(LibIDs.Save(f)==false)		return false;
	return true;
}
void	IntegrationReqRepresentative::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckRepresentative	*SendBack=GetSendBackIntegration(IntegrationAckRepresentative,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	//IntList	LibFlatList;
	//IntList	LibPatternList;
	IntList	LibList;
	IntList	LibBladeList;
	CartonMenuForm	*f=(CartonMenuForm	*)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
	if(f!=NULL){
		QBuffer	Buff(&CartonParam);
		if(Buff.open(QIODevice::ReadOnly)==true){
			((ParamBase*)&f->Param)->LoadParam(&Buff);

			//LibFlatList.Add(f->Param.DotColorMatchLibFlat1);
			//LibFlatList.Add(f->Param.DotColorMatchLibFlat2);
			//LibFlatList.Add(f->Param.DotColorMatchLibFlat3);
			//LibFlatList.Add(f->Param.DotColorMatchLibFlat4);
			//LibFlatList.Add(f->Param.DotColorMatchLibFlat5);
			//LibPatternList.Add(f->Param.DotColorMatchLibPattern1);
			//LibPatternList.Add(f->Param.DotColorMatchLibPattern2);
			//LibPatternList.Add(f->Param.DotColorMatchLibPattern3);
			//LibPatternList.Add(f->Param.DotColorMatchLibPattern4);
			//LibPatternList.Add(f->Param.DotColorMatchLibPattern5);

			LibBladeList.Add(f->Param.DotColorMatchBladeLib1);
			LibBladeList.Add(f->Param.DotColorMatchBladeLib2);
			LibBladeList.Add(f->Param.DotColorMatchBladeLib3);
			LibBladeList.Add(f->Param.DotColorMatchBladeLib4);
			LibBladeList.Add(f->Param.DotColorMatchBladeLib5);
		}
	}
		
	IntList LibIDList;
	AlgorithmLibraryLevelContainer	**Lib=NULL;
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(ABase!=NULL){
		AlgorithmLibraryContainer	*LibContainer=ABase->GetLibraryContainer();
		if(LibContainer!=NULL){
			for(SendBack->Phase=0;SendBack->Phase<GetPhaseNumb();SendBack->Phase++){
				AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(SendBack->Phase);
				if(Ah!=NULL){
					for(SendBack->Page=0;SendBack->Page<GetPageNumb();SendBack->Page++){
						AlgorithmInPagePI		*Ap=(AlgorithmInPagePI *)Ah->GetPageData(SendBack->Page);
						if(Ap!=NULL){
							if(Lib!=NULL){
								for(int i=0;i<LibIDList.GetCount();i++){
									delete	Lib[i];
								}
								delete	[]Lib;
							}
							Ap->EnumLibID(LibIDList);
							Lib=new AlgorithmLibraryLevelContainer*[LibIDList.GetCount()];
							int	n=0;
							for(IntClass *c=LibIDList.GetFirst();c!=NULL;c=c->GetNext(),n++){
								int	LibID=c->GetValue();
								Lib[n]=new AlgorithmLibraryLevelContainer(ABase);
								LibContainer->GetLibrary(LibID,*Lib[n]);
							}
							for(AlgorithmItemPI	*a=Ap->GetFirstData();a!=NULL;a=a->GetNext()){
								DotColorMatchingItem	*d=dynamic_cast<DotColorMatchingItem *>(a);
								if(d!=NULL){
									if(AreaType==EachThresholdCommon::_Mono && d->MasterPattern!=NULL
									&& d->MasterPattern[0].FlatPattern==true
									//&& LibPatternList.IsInclude(d->GetLibID())==true){
									&& LibIDs.IsInclude(d->GetLibID())==true){
										SendBack->ItemID=d->GetID();
										QBuffer	Buff;
										Buff.open(QIODevice::ReadWrite);
										d->Save(&Buff);
										d->GetThresholdW()->Save(&Buff);
										SendBack->ItemData=Buff.buffer();
										goto	Found;
									}
									if(AreaType==EachThresholdCommon::_Gradation && d->MasterPattern!=NULL
									&& d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==true
									//&& LibPatternList.IsInclude(d->GetLibID())==true){
									&& LibIDs.IsInclude(d->GetLibID())==true){
										SendBack->ItemID=d->GetID();
										QBuffer	Buff;
										Buff.open(QIODevice::ReadWrite);
										d->Save(&Buff);
										d->GetThresholdW()->Save(&Buff);
										SendBack->ItemData=Buff.buffer();
										goto	Found;
									}
									if(AreaType==EachThresholdCommon::_Character && d->MasterPattern!=NULL
									&& d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==false
									//&& LibPatternList.IsInclude(d->GetLibID())==true){
									&& LibIDs.IsInclude(d->GetLibID())==true){
										SendBack->ItemID=d->GetID();
										QBuffer	Buff;
										Buff.open(QIODevice::ReadWrite);
										d->Save(&Buff);
										d->GetThresholdW()->Save(&Buff);
										SendBack->ItemData=Buff.buffer();
										goto	Found;
									}
									//if(AreaType==EachThresholdCommon::_NoPrint && d->MasterPattern!=NULL
									//&& LibFlatList.IsInclude(d->GetLibID())==true){
									//	SendBack->ItemID=d->GetID();
									//	QBuffer	Buff;
									//	Buff.open(QIODevice::ReadWrite);
									//	d->Save(&Buff);
									//	d->GetThresholdW()->Save(&Buff);
									//	SendBack->ItemData=Buff.buffer();
									//	goto	Found;
									//}
									if(AreaType==EachThresholdCommon::_AreaBlade && d->MasterPattern!=NULL
									&& LibBladeList.IsInclude(d->GetLibID())==true){
										SendBack->ItemID=d->GetID();
										QBuffer	Buff;
										Buff.open(QIODevice::ReadWrite);
										d->Save(&Buff);
										d->GetThresholdW()->Save(&Buff);
										SendBack->ItemData=Buff.buffer();
										goto	Found;
									}
									if(AreaType==EachThresholdCommon::_AreaCADLine && d->MasterPattern!=NULL){
										SendBack->ItemID=d->GetID();
										QBuffer	Buff;
										Buff.open(QIODevice::ReadWrite);
										d->Save(&Buff);
										d->GetThresholdW()->Save(&Buff);
										SendBack->ItemData=Buff.buffer();
										goto	Found;
									}
									if(AreaType==EachThresholdCommon::_AreaTypeNothing && d->MasterPattern!=NULL
									&& LibIDs.IsInclude(d->GetLibID())==true){
										SendBack->ItemID=d->GetID();
										QBuffer	Buff;
										Buff.open(QIODevice::ReadWrite);
										d->Save(&Buff);
										d->GetThresholdW()->Save(&Buff);
										SendBack->ItemData=Buff.buffer();
										goto	Found;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	Found:;
	if(Lib!=NULL){
		for(int i=0;i<LibIDList.GetCount();i++){
			delete	Lib[i];
		}
		delete	[]Lib;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckRepresentative::IntegrationAckRepresentative(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckRepresentative::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)		return false;
	if(::Load(f,Page)==false)		return false;
	if(::Load(f,ItemID)==false)		return false;
	if(::Load(f,ItemData)==false)	return false;
	return true;
}
bool	IntegrationAckRepresentative::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)		return false;
	if(::Save(f,Page)==false)		return false;
	if(::Save(f,ItemID)==false)		return false;
	if(::Save(f,ItemData)==false)	return false;
	return true;
}

//=================================================================================================
	
IntegrationReqRepresentativeByLib::IntegrationReqRepresentativeByLib(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqRepresentativeByLib::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)		return false;
	return true;
}
bool	IntegrationReqRepresentativeByLib::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)		return false;
	return true;
}
void	IntegrationReqRepresentativeByLib::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckRepresentativeByLib	*SendBack=GetSendBackIntegration(IntegrationAckRepresentativeByLib,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(ABase!=NULL){
		for(SendBack->Phase=0;SendBack->Phase<GetPhaseNumb();SendBack->Phase++){
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(SendBack->Phase);
			if(Ah!=NULL){
				for(SendBack->Page=0;SendBack->Page<GetPageNumb();SendBack->Page++){
					AlgorithmInPagePI		*Ap=(AlgorithmInPagePI *)Ah->GetPageData(SendBack->Page);
					if(Ap!=NULL){
						for(AlgorithmItemPI	*a=Ap->GetFirstData();a!=NULL;a=a->GetNext()){
							DotColorMatchingItem	*d=dynamic_cast<DotColorMatchingItem *>(a);
							if(d!=NULL && d->GetLibID()==LibID){
								SendBack->ItemID=d->GetID();
								QBuffer	Buff;
								Buff.open(QIODevice::ReadWrite);
								d->Save(&Buff);
								d->GetThresholdW()->Save(&Buff);
								SendBack->ItemData=Buff.buffer();
								goto	Found;
							}
						}
					}
				}
			}
		}
	}
	Found:;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckRepresentativeByLib::IntegrationAckRepresentativeByLib(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckRepresentativeByLib::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)		return false;
	if(::Load(f,Page)==false)		return false;
	if(::Load(f,ItemID)==false)		return false;
	if(::Load(f,ItemData)==false)	return false;
	return true;
}
bool	IntegrationAckRepresentativeByLib::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)		return false;
	if(::Save(f,Page)==false)		return false;
	if(::Save(f,ItemID)==false)		return false;
	if(::Save(f,ItemData)==false)	return false;
	return true;
}
//=================================================================================================

IntegrationReqItemByAreaLib::IntegrationReqItemByAreaLib(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqItemByAreaLib::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)		return false;
	if(::Load(f,LevelID)==false)	return false;
	if(::Load(f,LibID)==false)		return false;
	if(Area.Load(f)==false)			return false;
	return true;
}
bool	IntegrationReqItemByAreaLib::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)		return false;
	if(::Save(f,LevelID)==false)	return false;
	if(::Save(f,LibID)==false)		return false;
	if(Area.Save(f)==false)			return false;
	return true;
}

class ReqItemByAreaLibClass
{
public:
	FlexArea	Area;
	int			LibID;

	ReqItemByAreaLibClass(){}
};

static	bool ReqItemByAreaLibFunc(void *caller,AlgorithmItemRoot *item)
{
	ReqItemByAreaLibClass	*a=(ReqItemByAreaLibClass *)caller;
	if(item->GetLibID()==a->LibID
	&& item->GetArea().CheckOverlap(&a->Area)==true){
		return true;
	}
	return false;
}

void	IntegrationReqItemByAreaLib::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckItemByAreaLib	*SendBack=GetSendBackIntegration(IntegrationAckItemByAreaLib,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			IntList	PageList;
			GetLayersBase()->GetLocalPageFromArea(Area,PageList);
			if(PageList.GetFirst()!=NULL){
				SendBack->Page=PageList.GetFirst()->GetValue();
				FlexArea	LocalArea=Area;
				DataInPage	*Dp=GetLayersBase()->GetPageData(SendBack->Page);
				Dp->ClipMoveAreaFromGlobal(LocalArea);

				AlgorithmInPagePI		*Ap=(AlgorithmInPagePI *)Ah->GetPageData(SendBack->Page);
				if(Ap!=NULL){
					AlgorithmItemPointerListContainer	Items;
					ReqItemByAreaLibClass	Caller;
					Caller.LibID=LibID;
					Caller.Area	=LocalArea;
					Ap->EnumItems(&Caller,Items , ReqItemByAreaLibFunc);
					if(Items.GetCount()!=0){
						DotColorMatchingItem	*d=dynamic_cast<DotColorMatchingItem *>(Items.GetFirst()->GetItem());
						if(d!=NULL && d->GetLibID()==LibID){
							SendBack->ItemID=d->GetID();
							QBuffer	Buff;
							Buff.open(QIODevice::ReadWrite);
							d->Save(&Buff);
							d->GetThresholdW()->Save(&Buff);
							SendBack->ItemData=Buff.buffer();
							goto	Found;
						}
					}
				}
			}
		}
	}
	Found:;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}
	
IntegrationAckItemByAreaLib::IntegrationAckItemByAreaLib(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckItemByAreaLib::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)		return false;
	if(::Load(f,ItemID)==false)		return false;
	if(::Load(f,ItemData)==false)	return false;
	return true;

}
bool	IntegrationAckItemByAreaLib::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)		return false;
	if(::Save(f,ItemID)==false)		return false;
	if(::Save(f,ItemData)==false)	return false;
	return true;

}

//=================================================================================================
IntegrationReqTryInspection::IntegrationReqTryInspection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqTryInspection::Load(QIODevice *f)
{
	if(::Load(f,Phase		)==false)	return false;
	if(::Load(f,Page		)==false)	return false;
	if(ItemID.Load(f		)==false)	return false;
	if(::Load(f,ItemThreshold)==false)	return false;
	if(::Load(f,ZoomRate	)==false)	return false;
	if(::Load(f,movx		)==false)	return false;
	if(::Load(f,movy		)==false)	return false;
	if(::Load(f,ImageW		)==false)	return false;
	if(::Load(f,ImageH		)==false)	return false;
	if(::Load(f,OverlapNG	)==false)	return false;
	if(::Load(f,DrawMode	)==false)	return false;
	if(::Load(f,DrawGx		)==false)	return false;
	if(::Load(f,DrawGy		)==false)	return false;
	if(::Load(f,DrawColor	)==false)	return false;
	return true;
}
bool	IntegrationReqTryInspection::Save(QIODevice *f)
{
	if(::Save(f,Phase		)==false)	return false;
	if(::Save(f,Page		)==false)	return false;
	if(ItemID.Save(f		)==false)	return false;
	if(::Save(f,ItemThreshold)==false)	return false;
	if(::Save(f,ZoomRate	)==false)	return false;
	if(::Save(f,movx		)==false)	return false;
	if(::Save(f,movy		)==false)	return false;
	if(::Save(f,ImageW		)==false)	return false;
	if(::Save(f,ImageH		)==false)	return false;
	if(::Save(f,OverlapNG	)==false)	return false;
	if(::Save(f,DrawMode	)==false)	return false;
	if(::Save(f,DrawGx		)==false)	return false;
	if(::Save(f,DrawGy		)==false)	return false;
	if(::Save(f,DrawColor	)==false)	return false;
	return true;
}

void	IntegrationReqTryInspection::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckTryInspection	*SendBack=GetSendBackIntegration(IntegrationAckTryInspection,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	ButtonSettingThresholdForm	*Form=NULL;
	GUIFormBase *GUIRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"SettingThreshold",GUIRet ,100);
	for(int i=0;i<n;i++){
		ButtonSettingThresholdForm	*f=(ButtonSettingThresholdForm	*)GUIRet[i];
		if(f->SlaveNo==slaveNo){
			Form=f;
			break;
		}
	}
	if(Form!=NULL){
		SendBack->Error=0;
		SendBack->NGSizeB	=0;
		SendBack->NGLengthB	=0;
		SendBack->NGSizeN	=0;
		SendBack->NGLengthN	=0;
		SendBack->NGCount	=0;
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
		if(ABase!=NULL){
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				AlgorithmInPageRoot		*Ap=Ah->GetPageData(Page);
				if(Ap!=NULL){
					if(Form->TargetImageWithNG.isNull()==true 
					|| Form->TargetImageWithNG.width()!=ImageW
					|| Form->TargetImageWithNG.height()!=ImageH){
						Form->TargetImageWithNG	=QImage(ImageW,ImageH,QImage::Format_RGB32);
					}
					Form->TargetImageWithNG.fill(Qt::black);
					ImageBuffer *ImageList[100];
					Ap->GetTargetBuffList(ImageList);
					ImageBuffer	*BuffR=ImageList[0];
					ImageBuffer	*BuffG=ImageList[1];
					ImageBuffer	*BuffB=ImageList[2];
					double	Z=1.0/ZoomRate;
	
					int	StartX	=-movx;
					int	EndX	=ImageW*Z-movx;
					int	x1=0;
					int	x2=ImageW;
					if(StartX<0){
						x1=movx*ZoomRate;
						StartX=0;
					}
					if(EndX>=Ap->GetDotPerLine()){
						x2=(Ap->GetDotPerLine()+movx)*ZoomRate;
						if((x2-1)*Z-movx>=Ap->GetDotPerLine()){
							x2--;
						}
					}
	
					for(int y=0;y<ImageH;y++){
						QRgb	*d=(QRgb *)Form->TargetImageWithNG.scanLine(y);
						int	Y=y*Z-movy;
						if(0<=Y && Y<Ap->GetMaxLines()){
							BYTE	*sR=BuffR->GetY(Y);
							BYTE	*sG=BuffG->GetY(Y);
							BYTE	*sB=BuffB->GetY(Y);
							double	Xm=StartX;
							for(int x=x1;x<x2;x++,Xm+=Z){
								int	X=Xm;
								d[x]=qRgb(sR[X],sG[X],sB[X]);
							}
						}
					}
					if(DrawMode==true){
						int	Lx1=(DrawGx-16+movx)*ZoomRate;
						int	Ly1=(DrawGy-16+movy)*ZoomRate;
						int	Lx2=(DrawGx+16+movx)*ZoomRate;
						int	Ly2=(DrawGy+16+movy)*ZoomRate;
						Lx1=max(Lx1,0);
						Ly1=max(Ly1,0);
						Lx2=min(Lx2,ImageW);
						Ly2=min(Ly2,ImageH);
						QRgb	col=DrawColor.rgb();
						for(int y=Ly1;y<Ly2;y++){
							QRgb	*d=(QRgb *)Form->TargetImageWithNG.scanLine(y);
							for(int x=Lx1;x<Lx2;x++){
								d[x]=col;
							}
						}
					}
	
	
					int	MinX=99999999;
					int	MinY=99999999;
					int	MaxX=-99999999;
					int	MaxY=-99999999;
					QPainter	Pnt(&Form->TargetImageWithNG);
					bool	ShownMessage=false;
					for(IntClass *c=ItemID.GetFirst();c!=NULL;c=c->GetNext()){
						CmdTryInspection	Cmd(GetLayersBase());
						Cmd.ItemID=c->GetValue();
						Cmd.ThresholdData	=ItemThreshold;
						Ap->TransmitDirectly(&Cmd);
						if(Cmd.RetRes!=NULL){	
							for(ResultPosList *r=Cmd.RetRes->GetPosList().GetFirst();r!=NULL;r=r->GetNext()){
								if(OverlapNG==true){
									r->DrawResultDetail(Cmd.RetRes ,Form->TargetImageWithNG ,Pnt
														,movx ,movy,ZoomRate 
														,5
														,qRgb(255,128,0)
														,2,false);
								}
							
								if(Cmd.RetRes->GetError()==2){
									SendBack->Error=2;
									if(r->result ==0x10000)
										SendBack->NGSizeB	=max(SendBack->NGSizeB ,(int)r->GetResult1());
									else
									if(r->result ==0x10002)
										SendBack->NGLengthB	=max(SendBack->NGLengthB ,(int)r->GetResult1());
	
									SendBack->NGCount	=max(SendBack->NGCount,(int)Cmd.RetRes->GetResult1());
								}
								if(SendBack->Error==0 && Cmd.RetRes->GetError()==3){
									SendBack->Error=3;
									if(r->result ==0x10000)
										SendBack->NGSizeB	=max(SendBack->NGSizeB,(int)r->GetResult1());
									else
									if(r->result ==0x10002)
										SendBack->NGLengthB	=max(SendBack->NGLengthB ,(int)r->GetResult1());
									
									SendBack->NGCount	=max(SendBack->NGCount,(int)Cmd.RetRes->GetResult1());
								}
							}
	
							int	x1,y1,x2,y2;
							Cmd.RetItem->GetXY(x1,y1,x2,y2);
							x1+=Cmd.RetRes->GetTotalShiftedX();
							y1+=Cmd.RetRes->GetTotalShiftedY();
							x2+=Cmd.RetRes->GetTotalShiftedX();
							y2+=Cmd.RetRes->GetTotalShiftedY();
							MinX=min(MinX,x1);
							MinY=min(MinY,y1);
							MaxX=max(MaxX,x2);
							MaxY=max(MaxY,y2);
	
							if(ShownMessage==false){
								ShownMessage=true;
								if(Cmd.RetRes->GetError()==2 && Cmd.RetRes->GetPosList().GetCount()!=0){
									int	X,Y;
									Cmd.RetRes->GetPosList().GetFirst()->GetPosInTarget(Cmd.RetRes,X,Y);
									Pnt.setPen(Qt::red);
									Pnt.setBrush(Qt::red);
									Pnt.drawText((X+movx)*ZoomRate,(Y+movy)*ZoomRate
										,QString("Pixel:")+QString::number(Cmd.RetRes->GetResult2()));
								}
								else
								if(Cmd.RetRes->GetError()==3 && Cmd.RetRes->GetPosList().GetCount()!=0){
									int	X,Y;
									Cmd.RetRes->GetPosList().GetFirst()->GetPosInTarget(Cmd.RetRes,X,Y);
									Pnt.setPen(Qt::red);
									Pnt.setBrush(Qt::red);
									Pnt.drawText((X+movx)*ZoomRate,(Y+movy)*ZoomRate
										,QString("MultiSpot"));
									Pnt.drawText((X+movx)*ZoomRate,(Y+movy)*ZoomRate+16
										,QString("Count:")+QString::number(Cmd.RetRes->GetResult1()));
									Pnt.drawText((X+movx)*ZoomRate,(Y+movy)*ZoomRate+16
										,QString("MinDot:")+QString::number(Cmd.RetRes->GetResult2()));
								}
							}
						}
					}
					if(MinX<MaxX && MinY<MaxY){
						Pnt.setPen(Qt::green);
						int	gx1=(MinX+movx)*ZoomRate;
						int	gy1=(MinY+movy)*ZoomRate;
						int	gx2=(MaxX+movx)*ZoomRate;
						int	gy2=(MaxY+movy)*ZoomRate;
						Pnt.drawLine(gx1,gy1,gx2,gy1);
						Pnt.drawLine(gx2,gy1,gx2,gy2);
						Pnt.drawLine(gx2,gy2,gx1,gy2);
						Pnt.drawLine(gx1,gy2,gx1,gy1);
					}
				}
			}
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
	SendBack->SlaveNo=slaveNo;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

	
IntegrationAckTryInspection::IntegrationAckTryInspection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

struct IntegrationAckTryInspectionData
{
	int32	SlaveNo;
	int		TargetImageWithNGXLen;
	int		TargetImageWithNGYLen;
	int		Error;
	int		NGCount;
	int		NGSizeB;
	int		NGLengthB;
	int		NGSizeN;
	int		NGLengthN;
};

bool	IntegrationAckTryInspection::Load(QIODevice *f)
{
	struct IntegrationAckTryInspectionData	Data;
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))	return false;
	
	ButtonSettingThresholdForm	*Form=NULL;
	GUIFormBase *GUIRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"SettingThreshold",GUIRet ,100);
	for(int i=0;i<n;i++){
		ButtonSettingThresholdForm	*f=(ButtonSettingThresholdForm	*)GUIRet[i];
		if(f->SlaveNo==Data.SlaveNo){
			Form=f;
			break;
		}
	}
	SlaveNo		=Data.SlaveNo;
	Error		=Data.Error;
	NGSizeB		=Data.NGSizeB;
	NGLengthB	=Data.NGLengthB;
	NGSizeN		=Data.NGSizeN;
	NGLengthN	=Data.NGLengthN;	

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
			Form->TargetImageWithNG=QImage(Form->TargetImageWithNGXLen,Form->TargetImageWithNGYLen,QImage::Format_RGB32);
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
bool	IntegrationAckTryInspection::Save(QIODevice *f)
{
	//if(::Save(f,TargetImageWithNG)==false)	return false;

	ButtonSettingThresholdForm	*Form=NULL;
	GUIFormBase *GUIRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"SettingThreshold",GUIRet ,100);
	for(int i=0;i<n;i++){
		ButtonSettingThresholdForm	*f=(ButtonSettingThresholdForm	*)GUIRet[i];
		if(f->SlaveNo==SlaveNo){
			Form=f;
			break;
		}
	}
	struct IntegrationAckTryInspectionData	Data;
	if(Form!=NULL){
		Data.SlaveNo	=SlaveNo;
		Data.TargetImageWithNGXLen	=Form->TargetImageWithNGXLen;
		Data.TargetImageWithNGYLen	=Form->TargetImageWithNGYLen;
		Data.Error		=Error;
		Data.NGSizeB	=NGSizeB;
		Data.NGLengthB	=NGLengthB;
		Data.NGSizeN	=NGSizeN;
		Data.NGLengthN	=NGLengthN;
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

IntegrationReqItemID::IntegrationReqItemID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqItemID::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false)	return false;
	AreaType=(EachThresholdCommon::__AreaType)d;
	BYTE	e;
	if(::Load(f,e)==false)	return false;
	InspectionType=(EachThresholdCommon::__InspectionType)e;

	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,GlobalX	)==false)	return false;
	if(::Load(f,GlobalY	)==false)	return false;
	if(::Load(f,CartonParam	)==false)	return false;
	return true;
}
bool	IntegrationReqItemID::Save(QIODevice *f)
{
	BYTE	d=(BYTE)AreaType;
	if(::Save(f,d)==false)	return false;
	BYTE	e=(BYTE)InspectionType;
	if(::Save(f,e)==false)	return false;

	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,Page	)==false)	return false;
	if(::Save(f,GlobalX	)==false)	return false;
	if(::Save(f,GlobalY	)==false)	return false;
	if(::Save(f,CartonParam	)==false)	return false;
	return true;
}
void	IntegrationReqItemID::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)	
{
	IntegrationAckItemID	*SendBack=GetSendBackIntegration(IntegrationAckItemID,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	IntList	LibFlatList;
	IntList	LibPatternList;
	IntList	LibBladeList;
	CartonMenuForm	*f=(CartonMenuForm	*)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
	if(f!=NULL){
		QBuffer	Buff(&CartonParam);
		if(Buff.open(QIODevice::ReadOnly)==true){
			((ParamBase*)&f->Param)->LoadParam(&Buff);
			LibFlatList.Add(f->Param.DotColorMatchLibFlat1);
			LibFlatList.Add(f->Param.DotColorMatchLibFlat2);
			LibFlatList.Add(f->Param.DotColorMatchLibFlat3);
			LibFlatList.Add(f->Param.DotColorMatchLibFlat4);
			LibFlatList.Add(f->Param.DotColorMatchLibFlat5);
			LibPatternList.Add(f->Param.DotColorMatchLibPattern1);
			LibPatternList.Add(f->Param.DotColorMatchLibPattern2);
			LibPatternList.Add(f->Param.DotColorMatchLibPattern3);
			LibPatternList.Add(f->Param.DotColorMatchLibPattern4);
			LibPatternList.Add(f->Param.DotColorMatchLibPattern5);
			LibBladeList.Add(f->Param.DotColorMatchBladeLib1);
			LibBladeList.Add(f->Param.DotColorMatchBladeLib2);
			LibBladeList.Add(f->Param.DotColorMatchBladeLib3);
			LibBladeList.Add(f->Param.DotColorMatchBladeLib4);
			LibBladeList.Add(f->Param.DotColorMatchBladeLib5);
		}
	}
	IntList LibIDList;
	AlgorithmLibraryLevelContainer	**Lib=NULL;
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(ABase!=NULL){
		AlgorithmLibraryContainer	*LibContainer=ABase->GetLibraryContainer();
		if(LibContainer!=NULL){
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				int	LocalX,LocalY;
				if(GetLayersBase()->GetLocalMatrixFromGlobal(GlobalX,GlobalY,LocalX,LocalY)>=0){
					AlgorithmInPagePI		*Ap=(AlgorithmInPagePI *)Ah->GetPageData(Page);
					if(Ap!=NULL){
						if(Lib!=NULL){
							for(int i=0;i<LibIDList.GetCount();i++){
								delete	Lib[i];
							}
							delete	[]Lib;
						}
						Ap->EnumLibID(LibIDList);
						Lib=new AlgorithmLibraryLevelContainer*[LibIDList.GetCount()];
						int	n=0;
						for(IntClass *c=LibIDList.GetFirst();c!=NULL;c=c->GetNext(),n++){
							int	LibID=c->GetValue();
							Lib[n]=new AlgorithmLibraryLevelContainer(ABase);
							LibContainer->GetLibrary(LibID,*Lib[n]);
						}
						for(AlgorithmItemPI	*a=Ap->GetFirstData();a!=NULL;a=a->GetNext()){
							DotColorMatchingItem	*d=dynamic_cast<DotColorMatchingItem *>(a);
							if(d!=NULL && d->IsInclude(LocalX,LocalY)==true){
								if(AreaType==EachThresholdCommon::_Mono && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==true
								&& LibPatternList.IsInclude(d->GetLibID())==true){
									for(int i=0;i<n;i++){
										if(Lib[i]->GetLibID()==d->GetLibID()){
											DotColorMatchingLibrary	*ALib=dynamic_cast<DotColorMatchingLibrary *>(Lib[i]->GetLibrary());
											if(ALib->AreaType==3)
												goto	Excluded;
										}
									}
									SendBack->ItemID.Add(d->GetID());
								}
								if(AreaType==EachThresholdCommon::_Gradation && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==true
								&& LibPatternList.IsInclude(d->GetLibID())==true){
									for(int i=0;i<n;i++){
										if(Lib[i]->GetLibID()==d->GetLibID()){
											DotColorMatchingLibrary	*ALib=dynamic_cast<DotColorMatchingLibrary *>(Lib[i]->GetLibrary());
											if(ALib->AreaType==3)
												goto	Excluded;
										}
									}
									SendBack->ItemID.Add(d->GetID());
								}
								if(AreaType==EachThresholdCommon::_Character && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==false
								&& LibPatternList.IsInclude(d->GetLibID())==true){
									for(int i=0;i<n;i++){
										if(Lib[i]->GetLibID()==d->GetLibID()){
											DotColorMatchingLibrary	*ALib=dynamic_cast<DotColorMatchingLibrary *>(Lib[i]->GetLibrary());
											if(ALib->AreaType==3)
												goto	Excluded;
										}
									}
									SendBack->ItemID.Add(d->GetID());
								}
								if(AreaType==EachThresholdCommon::_NoPrint && d->MasterPattern!=NULL
								&& LibFlatList.IsInclude(d->GetLibID())==true){
									for(int i=0;i<n;i++){
										if(Lib[i]->GetLibID()==d->GetLibID()){
											DotColorMatchingLibrary	*ALib=dynamic_cast<DotColorMatchingLibrary *>(Lib[i]->GetLibrary());
											if(ALib->AreaType!=3)
												goto	Excluded;
										}
									}
									SendBack->ItemID.Add(d->GetID());
								}
								if(AreaType==EachThresholdCommon::_AreaBlade && d->MasterPattern!=NULL
								&& LibBladeList.IsInclude(d->GetLibID())==true){
									for(int i=0;i<n;i++){
										if(Lib[i]->GetLibID()==d->GetLibID()){
											DotColorMatchingLibrary	*ALib=dynamic_cast<DotColorMatchingLibrary *>(Lib[i]->GetLibrary());
											if(ALib->AreaType!=3)
												goto	Excluded;
										}
									}
									SendBack->ItemID.Add(d->GetID());
								}
Excluded:;
							}
						}
					}
				}
			}
		}
	}

	if(Lib!=NULL){
		for(int i=0;i<LibIDList.GetCount();i++){
			delete	Lib[i];
		}
		delete	[]Lib;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckItemID::IntegrationAckItemID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckItemID::Load(QIODevice *f)
{
	if(ItemID.Load(f)==false)	return false;
	return true;
}
bool	IntegrationAckItemID::Save(QIODevice *f)
{
	if(ItemID.Save(f)==false)	return false;
	return true;
}

//=================================================================================================

IntegrationReqItemData::IntegrationReqItemData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqItemData::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)		return false;
	if(::Load(f,Page)==false)		return false;
	if(::Load(f,ItemID)==false)		return false;
	return true;
}
bool	IntegrationReqItemData::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)		return false;
	if(::Save(f,Page)==false)		return false;
	if(::Save(f,ItemID)==false)		return false;
	return true;
}

void	IntegrationReqItemData::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckItemData	*SendBack=GetSendBackIntegration(IntegrationAckItemData,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPagePI		*Ap=(AlgorithmInPagePI *)Ah->GetPageData(Page);
			if(Ap!=NULL){
				DotColorMatchingItem	*d=dynamic_cast<DotColorMatchingItem *>(Ap->SearchIDItem(ItemID));
				if(d!=NULL){
					QBuffer	Buff;
					Buff.open(QIODevice::ReadWrite);
					d->Save(&Buff);
					d->GetThresholdW()->Save(&Buff);
					SendBack->ItemData=Buff.buffer();
				}
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckItemData::IntegrationAckItemData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckItemData::Load(QIODevice *f)
{
	if(::Load(f,ItemData)==false)	return false;
	return true;
}
bool	IntegrationAckItemData::Save(QIODevice *f)
{
	if(::Save(f,ItemData)==false)	return false;
	return true;
}

//=================================================================================================

IntegrationReqReflectThreshold::IntegrationReqReflectThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqReflectThreshold::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false)	return false;
	AreaType=(EachThresholdCommon::__AreaType)d;
	BYTE	e;
	if(::Load(f,e)==false)	return false;
	InspectionType=(EachThresholdCommon::__InspectionType)e;
	if(::Load(f,LibID)==false)	return false;
	if(::Load(f,ThresholdData)==false)	return false;
	return true;
}
bool	IntegrationReqReflectThreshold::Save(QIODevice *f)
{
	BYTE	d=(BYTE)AreaType;
	if(::Save(f,d)==false)	return false;
	BYTE	e=(BYTE)InspectionType;
	if(::Save(f,e)==false)	return false;
	if(::Save(f,LibID)==false)	return false;
	if(::Save(f,ThresholdData)==false)	return false;
	return true;
}

void	IntegrationReqReflectThreshold::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	QBuffer	Buff(&ThresholdData);
	Buff.open(QIODevice::ReadWrite);
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(ABase!=NULL){
		for(int Phase=0;Phase<GetPhaseNumb();Phase++){
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				for(int Page=0;Page<GetPageNumb();Page++){
					AlgorithmInPagePI		*Ap=(AlgorithmInPagePI *)Ah->GetPageData(Page);
					if(Ap!=NULL){
						for(AlgorithmItemPI	*a=Ap->GetFirstData();a!=NULL;a=a->GetNext()){
							DotColorMatchingItem	*d=dynamic_cast<DotColorMatchingItem *>(a);
							if(d!=NULL && d->GetLibID()==LibID){
								DotColorMatchingThreshold	*TmpThre=(DotColorMatchingThreshold *)d->CreateThresholdInstance();

								if(AreaType==EachThresholdCommon::_Mono && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==true){
									Buff.seek(0);
									TmpThre->Load(&Buff);
									CopyThreshold(d->GetThresholdW(),TmpThre,InspectionType);
								}
								else
								if(AreaType==EachThresholdCommon::_Gradation && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==true){
									Buff.seek(0);
									TmpThre->Load(&Buff);
									CopyThreshold(d->GetThresholdW(),TmpThre,InspectionType);
								}
								else
								if(AreaType==EachThresholdCommon::_Character && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==false){
									Buff.seek(0);
									TmpThre->Load(&Buff);
									CopyThreshold(d->GetThresholdW(),TmpThre,InspectionType);
								}
								else
								if(AreaType==EachThresholdCommon::_NoPrint && d->MasterPattern!=NULL){
									Buff.seek(0);
									TmpThre->Load(&Buff);
									CopyThreshold(d->GetThresholdW(),TmpThre,InspectionType);
								}
								else
								if(AreaType==EachThresholdCommon::_NoPrint && d->MasterPattern!=NULL){
									Buff.seek(0);
									TmpThre->Load(&Buff);
									CopyThreshold(d->GetThresholdW(),TmpThre,InspectionType);
								}
								else
								if(AreaType==EachThresholdCommon::_AreaCADLine && d->MasterPattern!=NULL){
									Buff.seek(0);
									TmpThre->Load(&Buff);
									CopyThreshold(d->GetThresholdW(),TmpThre,InspectionType);
								}
								else
								if(AreaType==EachThresholdCommon::_AreaBlade && d->MasterPattern!=NULL){
									Buff.seek(0);
									TmpThre->Load(&Buff);
									CopyThreshold(d->GetThresholdW(),TmpThre,InspectionType);
								}
								delete	TmpThre;
							}
						}
					}
				}
			}
		}
	}
}

void	IntegrationReqReflectThreshold::CopyThreshold(DotColorMatchingThreshold *Dst 
													 ,DotColorMatchingThreshold *Src
													,EachThresholdCommon::__InspectionType IType)
{
	if(IType==EachThresholdCommon::_BrightnessInspection){
		Dst->Broad	=Src->Broad;
		Dst->Narrow	=Src->Narrow;
	}
	else
	if(IType==EachThresholdCommon::_RedInspection){
		Dst->RedHighRate		=Src->RedHighRate		;	//G,B‚É”ä‚×‚ÄR‚Ì‹P“x’l‚Ì‘’lŠ„‡(%)
		Dst->RedMinBrightness	=Src->RedMinBrightness	;
		Dst->RedGBMerginRate	=Src->RedGBMerginRate	;
		Dst->RedGBMerginOffset	=Src->RedGBMerginOffset	;
		Dst->RedOKDot			=Src->RedOKDot			;
	}
	else
	if(IType==EachThresholdCommon::_OozingInspection){
		Dst->Broad	=Src->Broad;
		Dst->Narrow	=Src->Narrow;
	}
	else
	if(IType==EachThresholdCommon::_MultiSpotInspection){
		Dst->MultiSpotDot	=Src->MultiSpotDot	;
		Dst->MultiSpotCount	=Src->MultiSpotCount;
	}
	else
	if(IType==EachThresholdCommon::_CADLine){
		Dst->Broad	=Src->Broad;
		Dst->Narrow	=Src->Narrow;
	}
	else
	if(IType==EachThresholdCommon::_Blade){
	}
}

//=================================================================================================

IntegrationReqReflectOnlySize::IntegrationReqReflectOnlySize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqReflectOnlySize::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false)	return false;
	AreaType=(EachThresholdCommon::__AreaType)d;
	BYTE	e;
	if(::Load(f,e)==false)			return false;
	InspectionType=(EachThresholdCommon::__InspectionType)e;
	if(::Load(f,LibID)==false)		return false;
	if(::Load(f,OKDotB)==false)		return false;
	if(::Load(f,OKLengthB)==false)	return false;
	if(::Load(f,OKDotN)==false)		return false;
	if(::Load(f,OKLengthN)==false)	return false;

	if(::Load(f,RedOKDot)==false)		return false;
	if(::Load(f,MultiOKDot)==false)		return false;
	if(::Load(f,MultiNGCount)==false)	return false;
	if(::Load(f,SelfSearch)==false)		return false;
	if(SelectedArea.Load(f)==false)		return false;
	return true;
}
bool	IntegrationReqReflectOnlySize::Save(QIODevice *f)
{
	BYTE	d=(BYTE)AreaType;
	if(::Save(f,d)==false)	return false;
	BYTE	e=(BYTE)InspectionType;
	if(::Save(f,e)==false)			return false;
	if(::Save(f,LibID)==false)		return false;
	if(::Save(f,OKDotB)==false)		return false;
	if(::Save(f,OKLengthB)==false)	return false;
	if(::Save(f,OKDotN)==false)		return false;
	if(::Save(f,OKLengthN)==false)	return false;

	if(::Save(f,RedOKDot)==false)		return false;
	if(::Save(f,MultiOKDot)==false)		return false;
	if(::Save(f,MultiNGCount)==false)	return false;
	if(::Save(f,SelfSearch)==false)		return false;
	if(SelectedArea.Save(f)==false)		return false;
	return true;
}

void	IntegrationReqReflectOnlySize::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(ABase!=NULL){
		for(int Phase=0;Phase<GetPhaseNumb();Phase++){
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				for(int Page=0;Page<GetPageNumb();Page++){
					AlgorithmInPagePI		*Ap=(AlgorithmInPagePI *)Ah->GetPageData(Page);
					if(Ap!=NULL){
						for(AlgorithmItemPI	*a=Ap->GetFirstData();a!=NULL;a=a->GetNext()){
							DotColorMatchingItem	*d=dynamic_cast<DotColorMatchingItem *>(a);
							if(d!=NULL && d->GetLibID()==LibID
							&& (SelectedArea.IsNull()==true || d->IsCrossed(&SelectedArea)==true)){
								DotColorMatchingThreshold	*m=d->GetThresholdW();
								if(AreaType==EachThresholdCommon::_Mono && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==true){
									SetSize(m);
								}
								else
								if(AreaType==EachThresholdCommon::_Gradation && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==true){
									SetSize(m);
								}
								else
								if(AreaType==EachThresholdCommon::_Character && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==false){
									SetSize(m);
								}
								else
								if(AreaType==EachThresholdCommon::_NoPrint && d->MasterPattern!=NULL){
									SetSize(m);
								}
								else
								if(AreaType==EachThresholdCommon::_AreaCADLine && d->MasterPattern!=NULL){
									SetSize(m);
								}
								else
								if(AreaType==EachThresholdCommon::_AreaBlade && d->MasterPattern!=NULL){
									SetSize(m);
								}
								else
								if(AreaType==EachThresholdCommon::_AreaTypeNothing && d->MasterPattern!=NULL){
									SetSize(m);
								}
							}
						}
					}
				}
			}
		}
	}
}
void	IntegrationReqReflectOnlySize::SetSize(DotColorMatchingThreshold *Dst)
{
	switch(InspectionType){
	case EachThresholdCommon::_BrightnessInspection:
		Dst->Broad.OKDot	=OKDotB;
		Dst->Broad.OKLength	=OKLengthB;
		Dst->Narrow.OKDot	=OKDotN;
		Dst->Narrow.OKLength=OKLengthN;
		break;
	case EachThresholdCommon::_RedInspection:
		Dst->RedOKDot	=RedOKDot;
		break;
	case EachThresholdCommon::_OozingInspection:
		Dst->SelfSearch	=SelfSearch;
		break;
	case EachThresholdCommon::_MultiSpotInspection:
		Dst->MultiSpotDot	=MultiOKDot;
		Dst->MultiSpotCount	=MultiNGCount;
		break;
	case EachThresholdCommon::_CADLine:
		Dst->Broad.OKDot	=OKDotB;
		Dst->Broad.OKLength	=OKLengthB;
		Dst->Narrow.OKDot	=OKDotN;
		Dst->Narrow.OKLength=OKLengthN;
		Dst->SelfSearch		=SelfSearch;
		break;
	case EachThresholdCommon::_Blade:
		break;
	}
}

//=================================================================================================

IntegrationReqReflectOnlyAreaSearch::IntegrationReqReflectOnlyAreaSearch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqReflectOnlyAreaSearch::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false)	return false;
	AreaType=(EachThresholdCommon::__AreaType)d;
	BYTE	e;
	if(::Load(f,e)==false)			return false;
	InspectionType=(EachThresholdCommon::__InspectionType)e;
	if(::Load(f,LibID)==false)		return false;
	if(::Load(f,AreaSearchX)==false)	return false;
	if(::Load(f,AreaSearchY)==false)	return false;

	if(SelectedArea.Load(f)==false)		return false;
	return true;
}
bool	IntegrationReqReflectOnlyAreaSearch::Save(QIODevice *f)
{
	BYTE	d=(BYTE)AreaType;
	if(::Save(f,d)==false)	return false;
	BYTE	e=(BYTE)InspectionType;
	if(::Save(f,e)==false)			return false;
	if(::Save(f,LibID)==false)		return false;
	if(::Save(f,AreaSearchX)==false)	return false;
	if(::Save(f,AreaSearchY)==false)	return false;
	if(SelectedArea.Save(f)==false)		return false;
	return true;
}

void	IntegrationReqReflectOnlyAreaSearch::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(ABase!=NULL){
		for(int Phase=0;Phase<GetPhaseNumb();Phase++){
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				for(int Page=0;Page<GetPageNumb();Page++){
					AlgorithmInPagePI		*Ap=(AlgorithmInPagePI *)Ah->GetPageData(Page);
					if(Ap!=NULL){
						for(AlgorithmItemPI	*a=Ap->GetFirstData();a!=NULL;a=a->GetNext()){
							DotColorMatchingItem	*d=dynamic_cast<DotColorMatchingItem *>(a);
							if(d!=NULL && d->GetLibID()==LibID
							&& (SelectedArea.IsNull()==true || d->IsCrossed(&SelectedArea)==true)){
								DotColorMatchingThreshold	*m=d->GetThresholdW();
								if(AreaType==EachThresholdCommon::_Mono && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==true){
									Set(m);
								}
								else
								if(AreaType==EachThresholdCommon::_Gradation && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==true){
									Set(m);
								}
								else
								if(AreaType==EachThresholdCommon::_Character && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==false){
									Set(m);
								}
								else
								if(AreaType==EachThresholdCommon::_NoPrint && d->MasterPattern!=NULL){
									Set(m);
								}
								else
								if(AreaType==EachThresholdCommon::_AreaCADLine && d->MasterPattern!=NULL){
									Set(m);
								}
								else
								if(AreaType==EachThresholdCommon::_AreaBlade && d->MasterPattern!=NULL){
									Set(m);
								}
								else
								if(AreaType==EachThresholdCommon::_AreaTypeNothing && d->MasterPattern!=NULL){
									Set(m);
								}
							}
						}
					}
				}
			}
		}
	}
}
void	IntegrationReqReflectOnlyAreaSearch::Set(DotColorMatchingThreshold *Dst)
{
	Dst->AreaSearchX	=AreaSearchX;
	Dst->AreaSearchY	=AreaSearchY;
}
//=================================================================================================

IntegrationReqReflectEnable::IntegrationReqReflectEnable(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqReflectEnable::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false)	return false;
	AreaType=(EachThresholdCommon::__AreaType)d;
	BYTE	e;
	if(::Load(f,e)==false)			return false;
	InspectionType=(EachThresholdCommon::__InspectionType)e;
	if(::Load(f,LibID)==false)		return false;
	if(::Load(f,InspectionEnable)==false)		return false;
	if(SelectedArea.Load(f)==false)		return false;
	return true;
}
bool	IntegrationReqReflectEnable::Save(QIODevice *f)
{
	BYTE	d=(BYTE)AreaType;
	if(::Save(f,d)==false)	return false;
	BYTE	e=(BYTE)InspectionType;
	if(::Save(f,e)==false)			return false;
	if(::Save(f,LibID)==false)		return false;
	if(::Save(f,InspectionEnable)==false)		return false;
	if(SelectedArea.Save(f)==false)		return false;
	return true;
}

void	IntegrationReqReflectEnable::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(ABase!=NULL){
		for(int Phase=0;Phase<GetPhaseNumb();Phase++){
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				for(int Page=0;Page<GetPageNumb();Page++){
					AlgorithmInPagePI		*Ap=(AlgorithmInPagePI *)Ah->GetPageData(Page);
					if(Ap!=NULL){
						for(AlgorithmItemPI	*a=Ap->GetFirstData();a!=NULL;a=a->GetNext()){
							DotColorMatchingItem	*d=dynamic_cast<DotColorMatchingItem *>(a);
							if(d!=NULL && d->GetLibID()==LibID
							&& (SelectedArea.IsNull()==true || d->IsCrossed(&SelectedArea)==true)){
								DotColorMatchingThreshold	*m=d->GetThresholdW();
								if(AreaType==EachThresholdCommon::_Mono && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==true){
									SetEnable(m);
								}
								else
								if(AreaType==EachThresholdCommon::_Gradation && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==true){
									SetEnable(m);
								}
								else
								if(AreaType==EachThresholdCommon::_Character && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==false){
									SetEnable(m);
								}
								else
								if(AreaType==EachThresholdCommon::_NoPrint && d->MasterPattern!=NULL){
									SetEnable(m);
								}
								else
								if(AreaType==EachThresholdCommon::_AreaCADLine && d->MasterPattern!=NULL){
									SetEnable(m);
								}
								else
								if(AreaType==EachThresholdCommon::_AreaBlade && d->MasterPattern!=NULL){
									SetEnable(m);
								}
								else
								if(AreaType==EachThresholdCommon::_AreaTypeNothing && d->MasterPattern!=NULL){
									SetEnable(m);
								}
							}
						}
					}
				}
			}
		}
	}
}
void	IntegrationReqReflectEnable::SetEnable(DotColorMatchingThreshold *Dst)
{
	Dst->EnableT2M=InspectionEnable;
	Dst->EnableM2T=InspectionEnable;
}
//=================================================================================================

IntegrationReqColor::IntegrationReqColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqColor::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)		return false;
	if(::Load(f,GlobalX)==false)	return false;
	if(::Load(f,GlobalY)==false)	return false;
	if(::Load(f,AreaSize)==false)	return false;
	return true;
}
bool	IntegrationReqColor::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)		return false;
	if(::Save(f,GlobalX)==false)	return false;
	if(::Save(f,GlobalY)==false)	return false;
	if(::Save(f,AreaSize)==false)	return false;
	return true;
}
void	IntegrationReqColor::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckColor	*SendBack=GetSendBackIntegration(IntegrationAckColor,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	SendBack->BRL=255;
	SendBack->BRH=0;
	SendBack->BGL=255;
	SendBack->BGH=0;
	SendBack->BBL=255;
	SendBack->BBH=0;

	SendBack->NRL=255;
	SendBack->NRH=0;
	SendBack->NGL=255;
	SendBack->NGH=0;
	SendBack->NBL=255;
	SendBack->NBH=0;
	int	LocalX,LocalY;
	int	GlobalPage=GetLayersBase()->GetLocalMatrixFromGlobal(GlobalX,GlobalY,LocalX,LocalY);
	if(GlobalPage>=0){
		DataInPage	*Dp=GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(GlobalPage);
		if(Dp!=NULL){
			for(int	y=0;y<AreaSize;y++){
				int	Y=LocalY+y-AreaSize/2;
				if(0<=Y && Y<Dp->GetMaxLines()){
					for(int x=0;x<AreaSize;x++){
						int X=LocalX+x-AreaSize/2;
						if(0<=X && X<Dp->GetDotPerLine()){
							if(Dp->GetLayerNumb()>=1){
								ImageBuffer	&Buff=Dp->GetLayerData(0)->GetTargetBuff();
								int	r=Buff.GetY(Y)[X];
								SendBack->BRL=min(SendBack->BRL,r);
								SendBack->BRH=max(SendBack->BRH,r);
								SendBack->NRL=min(SendBack->NRL,r);
								SendBack->NRH=max(SendBack->NRH,r);
							}
							if(Dp->GetLayerNumb()>=2){
								ImageBuffer	&Buff=Dp->GetLayerData(1)->GetTargetBuff();
								int	g=Buff.GetY(Y)[X];
								SendBack->BGL=min(SendBack->BGL,g);
								SendBack->BGH=max(SendBack->BGH,g);
								SendBack->NGL=min(SendBack->NGL,g);
								SendBack->NGH=max(SendBack->NGH,g);
							}
							if(Dp->GetLayerNumb()>=3){
								ImageBuffer	&Buff=Dp->GetLayerData(2)->GetTargetBuff();
								int	b=Buff.GetY(Y)[X];
								SendBack->BBL=min(SendBack->BBL,b);
								SendBack->BBH=max(SendBack->BBH,b);
								SendBack->NBL=min(SendBack->NBL,b);
								SendBack->NBH=max(SendBack->NBH,b);
							}
						}
					}
				}
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckColor::IntegrationAckColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckColor::Load(QIODevice *f)
{
	if(::Load(f,BRL)==false)	return false;
	if(::Load(f,BRH)==false)	return false;
	if(::Load(f,BGL)==false)	return false;
	if(::Load(f,BGH)==false)	return false;
	if(::Load(f,BBL)==false)	return false;
	if(::Load(f,BBH)==false)	return false;

	if(::Load(f,NRL)==false)	return false;
	if(::Load(f,NRH)==false)	return false;
	if(::Load(f,NGL)==false)	return false;
	if(::Load(f,NGH)==false)	return false;
	if(::Load(f,NBL)==false)	return false;
	if(::Load(f,NBH)==false)	return false;

	return true;
}
bool	IntegrationAckColor::Save(QIODevice *f)
{
	if(::Save(f,BRL)==false)	return false;
	if(::Save(f,BRH)==false)	return false;
	if(::Save(f,BGL)==false)	return false;
	if(::Save(f,BGH)==false)	return false;
	if(::Save(f,BBL)==false)	return false;
	if(::Save(f,BBH)==false)	return false;

	if(::Save(f,NRL)==false)	return false;
	if(::Save(f,NRH)==false)	return false;
	if(::Save(f,NGL)==false)	return false;
	if(::Save(f,NGH)==false)	return false;
	if(::Save(f,NBL)==false)	return false;
	if(::Save(f,NBH)==false)	return false;

	return true;
}

//=================================================================================================

IntegrationReqAreaType::IntegrationReqAreaType(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqAreaType::Load(QIODevice *f)
{
	if(ItemID.Load(f)==false)		return false;
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	return true;
}
bool	IntegrationReqAreaType::Save(QIODevice *f)
{
	if(ItemID.Save(f)==false)		return false;
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,Page	)==false)	return false;
	return true;
}
void	IntegrationReqAreaType::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckAreaType	*SendBack=GetSendBackIntegration(IntegrationAckAreaType,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(ABase!=NULL){
		AlgorithmLibraryContainer	*LibContainer=ABase->GetLibraryContainer();
		int	LocalPage	=GetLayersBase()->GetLocalPageFromGlobal(Page);
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPagePI		*Ap=(AlgorithmInPagePI *)Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				for(IntClass *c=ItemID.GetFirst();c!=NULL;c=c->GetNext()){
					AlgorithmItemRoot	*a=Ap->SearchIDItem(c->GetValue());
					if(a!=NULL){
						DotColorMatchingItem	*d=dynamic_cast<DotColorMatchingItem *>(a);
						if(d!=NULL){
							AlgorithmLibraryLevelContainer	Lib(ABase);
							if(LibContainer->GetLibrary(d->GetLibID(),Lib)==true){
								DotColorMatchingLibrary	*ALib=dynamic_cast<DotColorMatchingLibrary *>(Lib.GetLibrary());
								if(d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==true){
								//&& ALib->AreaType!=3){
									SendBack->AreaType=EachThresholdCommon::_Mono;
								}
								else
								if(d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==true){
								//&& ALib->AreaType!=3){
									SendBack->AreaType=EachThresholdCommon::_Gradation;
								}
								else
								if(d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==false){
								//&& ALib->AreaType!=3){
									SendBack->AreaType=EachThresholdCommon::_Character;
								}
								else
								if(d->MasterPattern!=NULL){
								//&& ALib->AreaType==3){
									SendBack->AreaType=EachThresholdCommon::_NoPrint;
								}
								if(SendBack->AreaType!=EachThresholdCommon::_AreaTypeNothing){
									int	cx,cy;
									d->GetCenter(cx,cy);
									GetLayersBase()->GetGlobalMatrixFromLocal(LocalPage,cx,cy,SendBack->GlobalX,SendBack->GlobalY);
									goto	Found;
								}
							}
						}
					}
				}
			}
		}
	}
Found:;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckAreaType::IntegrationAckAreaType(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	AreaType=EachThresholdCommon::_AreaTypeNothing;
}

bool	IntegrationAckAreaType::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false)	return false;
	AreaType=(EachThresholdCommon::__AreaType)d;
	if(::Load(f,GlobalX	)==false)	return false;
	if(::Load(f,GlobalY	)==false)	return false;
	return true;
}
bool	IntegrationAckAreaType::Save(QIODevice *f)
{
	BYTE	d=(BYTE)AreaType;
	if(::Save(f,d)==false)	return false;
	if(::Save(f,GlobalX	)==false)	return false;
	if(::Save(f,GlobalY	)==false)	return false;
	return true;
}

//=================================================================================================

IntegrationSetBrightnessShift::IntegrationSetBrightnessShift(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationSetBrightnessShift::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false)	return false;
	AreaType=(EachThresholdCommon::__AreaType)d;
	BYTE	e;
	if(::Load(f,e)==false)			return false;
	InspectionType=(EachThresholdCommon::__InspectionType)e;
	if(::Load(f,LibID)==false)		return false;
	if(::Load(f,AddBrightness	)==false)	return false;
	if(::Load(f,AddOffset		)==false)	return false;
	if(::Load(f,AddShift		)==false)	return false;
	if(SelectedArea.Load(f)==false)		return false;
	return true;
}
bool	IntegrationSetBrightnessShift::Save(QIODevice *f)
{
	BYTE	d=(BYTE)AreaType;
	if(::Save(f,d)==false)	return false;
	BYTE	e=(BYTE)InspectionType;
	if(::Save(f,e)==false)			return false;
	if(::Save(f,LibID)==false)		return false;
	if(::Save(f,AddBrightness	)==false)	return false;
	if(::Save(f,AddOffset		)==false)	return false;
	if(::Save(f,AddShift		)==false)	return false;
	if(SelectedArea.Save(f)==false)		return false;
	return true;
}
void	IntegrationSetBrightnessShift::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(ABase!=NULL){
		for(int Phase=0;Phase<GetPhaseNumb();Phase++){
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				CmdDotColorMatchingSetAdded	RCmd(GetLayersBase());

				for(int Page=0;Page<GetPageNumb();Page++){
					AlgorithmInPagePI		*Ap=(AlgorithmInPagePI *)Ah->GetPageData(Page);
					if(Ap!=NULL){
						for(AlgorithmItemPI	*a=Ap->GetFirstData();a!=NULL;a=a->GetNext()){
							DotColorMatchingItem	*d=dynamic_cast<DotColorMatchingItem *>(a);
							if(d!=NULL && d->GetLibID()==LibID
							&& (SelectedArea.IsNull()==true || d->IsCrossed(&SelectedArea)==true)){
								if((AreaType==EachThresholdCommon::_Mono && d->MasterPattern!=NULL
								 && d->MasterPattern[0].FlatPattern==true)
								|| (AreaType==EachThresholdCommon::_Gradation && d->MasterPattern!=NULL
								 && d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==true)
								|| (AreaType==EachThresholdCommon::_Character && d->MasterPattern!=NULL
								&& d->MasterPattern[0].FlatPattern==false && d->MasterPattern[0].DivArea.IsEmpty()==false)
								|| (AreaType==EachThresholdCommon::_NoPrint && d->MasterPattern!=NULL)
								|| (AreaType==EachThresholdCommon::_AreaCADLine && d->MasterPattern!=NULL)
								|| (AreaType==EachThresholdCommon::_AreaBlade && d->MasterPattern!=NULL)){

									RCmd.Items.Add(Page,0,a->GetID());
								}
								else
								if(AreaType==EachThresholdCommon::_AreaTypeNothing
								&& InspectionType==EachThresholdCommon::_InspectionTypeNothing){
									RCmd.Items.Add(Page,0,a->GetID());
								}
							}
						}
					}
				}
				RCmd.AddBrightness	=AddBrightness;
				RCmd.AddOffset		=AddOffset;
				RCmd.AddShift		=AddShift;
				ABase->TransmitDirectly(&RCmd);
			}
		}
	}
}