#include "XEachThresholdCommon.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "CartonMenuForm.h"
#include <QSlider>

extern	const	char	*sRoot;
extern	const	char	*sName;

EachThresholdCommon::EachThresholdCommon(int slaveno ,ButtonSettingThresholdForm *p
										,LayersBase *base,__AreaType areatype, __InspectionType inspectiontype)
	:ServiceForLayers(base)
	,SlaveNo(slaveno)
	,AreaType(areatype)
	,InspectionType(inspectiontype)
	,RepresentativePhase(0)
	,RepresentativePage(0)
	,FreePosition(true)
	,DItem(NULL)
	,PanelResultImage(p,this)
{
	AlgoBase	=(DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	ThreForm	=NULL;
}
EachThresholdCommon::~EachThresholdCommon(void)
{
	delete	DItem;
	DItem=NULL;
}

void	EachThresholdCommon::SetActivePosition(int Phase,int Page ,int GlobalX,int GlobalY,IntList &ItemID)
{
	RepresentativePhase	=Phase;
	RepresentativePage	=Page;
	RepresentativeItemID=ItemID;
	PanelResultImage.SetGlobalPoint(GlobalX,GlobalY);
	if(Phase>=0){
		FreePosition=false;
	}
}

void	EachThresholdCommon::SetThresholdFrame(QFrame *v)
{
	ThreForm	=new SetThresholdLevelForm(GetLayersBase(),false,v);
	ThreForm->setParent(v);
	ThreForm->move(0,30);
	ThreForm->SetCurrentThresholdLevelID(GetLayersBase()->GetThresholdLevelID());
	connect(ThreForm,SIGNAL(SignalChangeThresholdLevelID(int)),this,SLOT(SlotChangeThresholdLevelID(int)));
}

void EachThresholdCommon::SlotChangeThresholdLevelID(int value)
{
	ChangeThresholdLevelID(value);
}

int		EachThresholdCommon::GetThresholdOrder(void)
{
	if(ThreForm!=NULL){
		int	n=ThreForm->GetCurrentThresholdLevelID();
		return GetLayersBase()->GetThresholdParentLevelID(n);
	}
	return -1;
}
int		EachThresholdCommon::GetThresholdLevelID(void)
{
	if(ThreForm!=NULL){
		int	n=ThreForm->GetCurrentThresholdLevelID();
		return n;
	}
	return -1;
}

bool	EachThresholdCommon::GetItemThreshold(int LevelID)
{
	if(FreePosition==true || RepresentativeItemID.GetFirst()==NULL){
		IntegrationReqRepresentative	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckRepresentative	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.AreaType=AreaType;
		RCmd.InspectionType=InspectionType;
		CartonMenuForm	*f=(CartonMenuForm	*)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
		if(f!=NULL){
			QBuffer	Buff;
			if(Buff.open(QIODevice::WriteOnly)==true){
				((ParamBase *)&f->Param)->SaveParam(&Buff);
				RCmd.CartonParam=Buff.buffer();
			}
			if(SlaveNo==0){
				if(f->ParamInMaster.Slave0LibID.GetCount()!=0){
					RCmd.LibIDs.Merge(f->ParamInMaster.Slave0LibID);
				}
				else{
					RCmd.LibIDs.Add(f->Param.DotColorMatchLibPattern1);
					RCmd.LibIDs.Add(f->Param.DotColorMatchLibFlat1);
				}
			}
			else
			if(SlaveNo==1){
				if(f->ParamInMaster.Slave1LibID.GetCount()!=0){
					RCmd.LibIDs.Merge(f->ParamInMaster.Slave1LibID);
				}
				else{
					RCmd.LibIDs.Add(f->Param.DotColorMatchLibPattern1);
					RCmd.LibIDs.Add(f->Param.DotColorMatchLibFlat1);
				}
			}
			else
			if(SlaveNo==2){
				if(f->ParamInMaster.Slave2LibID.GetCount()!=0){
					RCmd.LibIDs.Merge(f->ParamInMaster.Slave2LibID);
				}
				else{
					RCmd.LibIDs.Add(f->Param.DotColorMatchLibPattern1);
					RCmd.LibIDs.Add(f->Param.DotColorMatchLibFlat1);
				}
			}
		}
		if(RCmd.Send(SlaveNo,0,ACmd)==true){
			RepresentativePhase	=ACmd.Phase;
			RepresentativePage	=ACmd.Page;
			RepresentativeItemID.RemoveAll();
			RepresentativeItemID.Add(ACmd.ItemID);
			CmdCreateTempDotColorMatchingItemPacket	Cmd(GetLayersBase());
			if(AlgoBase!=NULL){
				AlgoBase->TransmitDirectly(&Cmd);
				DItem	=Cmd.Point;
				QBuffer	Buff(&ACmd.ItemData);
				Buff.open(QIODevice::ReadOnly);
				if(DItem->Load(&Buff,GetLayersBase())==false){
					delete	DItem;
					DItem=NULL;
					return false;
				}
				if(DItem->GetThresholdW(GetLayersBase(),LevelID)->Load(&Buff)==false){
					delete	DItem;
					DItem=NULL;
					return false;
				}
				return true;
			}
		}
	}
	else{
		IntegrationReqItemData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckItemData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.Phase	=RepresentativePhase;
		RCmd.Page	=RepresentativePage;
		RCmd.ItemID	=RepresentativeItemID.GetFirst()->GetValue();
		if(RCmd.Send(SlaveNo,0,ACmd)==true){

			CmdCreateTempDotColorMatchingItemPacket	Cmd(GetLayersBase());
			if(AlgoBase!=NULL){
				AlgoBase->TransmitDirectly(&Cmd);
				DItem	=Cmd.Point;
				QBuffer	Buff(&ACmd.ItemData);
				Buff.open(QIODevice::ReadOnly);
				if(DItem->Load(&Buff,GetLayersBase())==false){
					delete	DItem;
					DItem=NULL;
					return false;
				}
				if(DItem->GetThresholdW(GetLayersBase(),LevelID)->Load(&Buff)==false){
					delete	DItem;
					DItem=NULL;
					return false;
				}
				return true;
			}
		}
	}
	return false;
}
bool	EachThresholdCommon::GetItemByLibID(int LibID,int LevelID)
{
	if(FreePosition==true || RepresentativeItemID.GetFirst()==NULL){
		IntegrationReqRepresentativeByLib	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckRepresentativeByLib	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.LibID=LibID;
		if(RCmd.Send(SlaveNo,0,ACmd)==true){
			RepresentativePhase	=ACmd.Phase;
			RepresentativePage	=ACmd.Page;
			RepresentativeItemID.RemoveAll();
			RepresentativeItemID.Add(ACmd.ItemID);
			CmdCreateTempDotColorMatchingItemPacket	Cmd(GetLayersBase());
			if(AlgoBase!=NULL){
				AlgoBase->TransmitDirectly(&Cmd);
				DItem	=Cmd.Point;
				QBuffer	Buff(&ACmd.ItemData);
				Buff.open(QIODevice::ReadOnly);
				if(DItem->Load(&Buff,GetLayersBase())==false){
					delete	DItem;
					DItem=NULL;
					return false;
				}
				if(DItem->GetThresholdW(GetLayersBase(),LevelID)->Load(&Buff)==false){
					delete	DItem;
					DItem=NULL;
					return false;
				}
				return true;
			}
		}
	}
	else{
		IntegrationReqItemData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckItemData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.Phase	=RepresentativePhase;
		RCmd.Page	=RepresentativePage;
		RCmd.ItemID	=RepresentativeItemID.GetFirst()->GetValue();
		if(RCmd.Send(SlaveNo,0,ACmd)==true){

			CmdCreateTempDotColorMatchingItemPacket	Cmd(GetLayersBase());
			if(AlgoBase!=NULL){
				AlgoBase->TransmitDirectly(&Cmd);
				DItem	=Cmd.Point;
				QBuffer	Buff(&ACmd.ItemData);
				Buff.open(QIODevice::ReadOnly);
				if(DItem->Load(&Buff,GetLayersBase())==false){
					delete	DItem;
					DItem=NULL;
					return false;
				}
				if(DItem->GetThresholdW(GetLayersBase(),LevelID)->Load(&Buff)==false){
					delete	DItem;
					DItem=NULL;
					return false;
				}
				return true;
			}
		}
	}
	return false;
}
bool	EachThresholdCommon::GetItemByLibIDArea(int Phase,int LibID,int LevelID ,FlexArea &Area)
{
	IntegrationReqItemByAreaLib	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	IntegrationAckItemByAreaLib	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
	RCmd.Phase	=Phase;
	RCmd.LevelID=LevelID;
	RCmd.LibID	=LibID;
	RCmd.Area	=Area;
	if(RCmd.Send(SlaveNo,0,ACmd)==true){
		RepresentativePhase	=Phase;
		RepresentativePage	=ACmd.Page;
		RepresentativeItemID.RemoveAll();
		RepresentativeItemID.Add(ACmd.ItemID);
		CmdCreateTempDotColorMatchingItemPacket	Cmd(GetLayersBase());
		if(AlgoBase!=NULL){
			AlgoBase->TransmitDirectly(&Cmd);
			DItem	=Cmd.Point;
			QBuffer	Buff(&ACmd.ItemData);
			Buff.open(QIODevice::ReadOnly);
			if(DItem->Load(&Buff,GetLayersBase())==false){
				delete	DItem;
				DItem=NULL;
				return false;
			}
			if(DItem->GetThresholdW(GetLayersBase(),LevelID)->Load(&Buff)==false){
				delete	DItem;
				DItem=NULL;
				return false;
			}
			return true;
		}
	}

	return false;
}

void	EachThresholdCommon::MouseLDoubleClick(int gx,int gy ,int LevelID)
{
	IntegrationReqItemID	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	IntegrationAckItemID	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
	RCmd.AreaType=AreaType;
	RCmd.InspectionType=InspectionType;
	RCmd.GlobalX=gx;
	RCmd.GlobalY=gy;
	RCmd.Phase	=RepresentativePhase;
	RCmd.Page	=RepresentativePage;
	CartonMenuForm	*f=(CartonMenuForm	*)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
	if(f!=NULL){
		QBuffer	Buff;
		if(Buff.open(QIODevice::WriteOnly)==true){
			((ParamBase*)&f->Param)->SaveParam(&Buff);
			RCmd.CartonParam=Buff.buffer();
		}
	}
	if(RCmd.Send(SlaveNo,0,ACmd)==true){
		RepresentativeItemID=ACmd.ItemID;
		if(RepresentativeItemID.GetCount()>0){
			IntegrationReqItemData	dRCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationAckItemData	dACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			dRCmd.Phase	=RepresentativePhase;
			dRCmd.Page	=RepresentativePage;
			dRCmd.ItemID=RepresentativeItemID.GetFirst()->GetValue();
			if(dRCmd.Send(SlaveNo,0,dACmd)==true){
				if(DItem!=NULL){
					delete	DItem;
				}
				CmdCreateTempDotColorMatchingItemPacket	Cmd(GetLayersBase());
				if(AlgoBase!=NULL){
					AlgoBase->TransmitDirectly(&Cmd);
					DItem	=Cmd.Point;
					QBuffer	Buff(&dACmd.ItemData);
					Buff.open(QIODevice::ReadOnly);
					if(DItem->Load(&Buff,GetLayersBase())==false){
						delete	DItem;
						DItem=NULL;
						return;
					}
					if(DItem->GetThresholdW(GetLayersBase(),LevelID)->Load(&Buff)==false){
						delete	DItem;
						DItem=NULL;
						return;
					}
				}
			}
		}
	}
}
void	EachThresholdCommon::ReflectAll(int LevelID)
{
	if(DItem!=NULL){
		IntegrationReqReflectThreshold	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.AreaType=AreaType;
		RCmd.InspectionType=InspectionType;
		RCmd.LibID	=DItem->GetLibID();
			
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(DItem->GetThresholdW(GetLayersBase(),LevelID)->Save(&Buff)==false){
			return;
		}
		RCmd.ThresholdData=Buff.buffer();
		RCmd.Send(NULL,SlaveNo,0);
	}
}

void	EachThresholdCommon::ReflectAllOnlySize(int OKDotB ,int OKLengthB ,int OKDotN ,int OKLengthN ,int LevelID ,const FlexArea &SelectedArea)
{
	if(DItem!=NULL){
		IntegrationReqReflectOnlySize	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.AreaType=AreaType;
		RCmd.InspectionType=EachThresholdCommon::_BrightnessInspection;
		RCmd.LibID	=DItem->GetLibID();

		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(DItem->GetThresholdW(GetLayersBase(),LevelID)->Save(&Buff)==false){
			return;
		}
		RCmd.OKDotB		=OKDotB; 
		RCmd.OKLengthB	=OKLengthB;
		RCmd.OKDotN		=OKDotN; 
		RCmd.OKLengthN	=OKLengthN;
		RCmd.SelectedArea=SelectedArea;
		RCmd.Send(NULL,SlaveNo,0);
	}
}
void	EachThresholdCommon::ReflectEnable(bool InspectionEnable	,int LevelID ,const FlexArea &SelectedArea)
{
	if(DItem!=NULL){
		IntegrationReqReflectEnable	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.AreaType=AreaType;
		RCmd.InspectionType=EachThresholdCommon::_InspectionEnable;
		RCmd.LibID	=DItem->GetLibID();

		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(DItem->GetThresholdW(GetLayersBase(),LevelID)->Save(&Buff)==false){
			return;
		}
		RCmd.InspectionEnable	=InspectionEnable; 
		RCmd.SelectedArea		=SelectedArea;
		RCmd.Send(NULL,SlaveNo,0);
	}
}
	
void	EachThresholdCommon::ReflectRedAllOnlySize(int RedOKDot ,int LevelID ,const FlexArea &SelectedArea)
{
	if(DItem!=NULL){
		IntegrationReqReflectOnlySize	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.AreaType=AreaType;
		RCmd.InspectionType=EachThresholdCommon::_RedInspection;
		RCmd.LibID	=DItem->GetLibID();
			
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(DItem->GetThresholdW(GetLayersBase(),LevelID)->Save(&Buff)==false){
			return;
		}
		RCmd.RedOKDot		=RedOKDot;
		RCmd.SelectedArea	=SelectedArea;
		RCmd.Send(NULL,SlaveNo,0);
	}
}
		
void	EachThresholdCommon::ReflectMultiAllOnlySize(int OKDot ,int NGCount ,int LevelID,const FlexArea &SelectedArea)
{
	if(DItem!=NULL){
		IntegrationReqReflectOnlySize	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.AreaType=AreaType;
		RCmd.InspectionType=EachThresholdCommon::_MultiSpotInspection;
		RCmd.LibID	=DItem->GetLibID();
			
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(DItem->GetThresholdW(GetLayersBase(),LevelID)->Save(&Buff)==false){
			return;
		}
		RCmd.MultiOKDot		=OKDot; 
		RCmd.MultiNGCount	=NGCount;
		RCmd.SelectedArea	=SelectedArea;
		RCmd.Send(NULL,SlaveNo,0);
	}
}
		
void	EachThresholdCommon::ReflectOozingAllOnlySize(int Shift ,int LevelID,const FlexArea &SelectedArea)
{
	if(DItem!=NULL){
		IntegrationReqReflectOnlySize	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.AreaType=AreaType;
		RCmd.InspectionType=EachThresholdCommon::_OozingInspection;
		RCmd.LibID	=DItem->GetLibID();
			
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(DItem->GetThresholdW(GetLayersBase(),LevelID)->Save(&Buff)==false){
			return;
		}
		RCmd.SelfSearch		=Shift; 
		RCmd.SelectedArea	=SelectedArea;
		RCmd.Send(NULL,SlaveNo,0);
	}
}
void	EachThresholdCommon::ReflectAreaSearchAllOnlySize(int AreaSearchX,int AreaSearchY,int LevelID ,const FlexArea &SelectedArea)
{
	if(DItem!=NULL){
		IntegrationReqReflectOnlyAreaSearch	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.AreaType=AreaType;
		RCmd.InspectionType=EachThresholdCommon::_OozingInspection;
		RCmd.LibID	=DItem->GetLibID();
			
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(DItem->GetThresholdW(GetLayersBase(),LevelID)->Save(&Buff)==false){
			return;
		}
		RCmd.AreaSearchX		=AreaSearchX;
		RCmd.AreaSearchY		=AreaSearchY; 
		RCmd.SelectedArea	=SelectedArea;
		RCmd.Send(NULL,SlaveNo,0);
	}
}
	
void	EachThresholdCommon::ReflectBrightness(int	AddBrightness ,int AddOffset ,int AddShift,int LevelID,const FlexArea &SelectedArea)
{
	if(DItem!=NULL){
		IntegrationSetBrightnessShift	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.AreaType=AreaType;
		RCmd.InspectionType=InspectionType;
		RCmd.LibID	=DItem->GetLibID();
			
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(DItem->GetThresholdW(GetLayersBase(),LevelID)->Save(&Buff)==false){
			return;
		}
		RCmd.AddBrightness	=AddBrightness;
		RCmd.AddOffset		=AddOffset;
		RCmd.AddShift		=AddShift;
		RCmd.SelectedArea	=SelectedArea;
		RCmd.Send(NULL,SlaveNo,0);
	}
}

static	int	SortDounbleFunc(const void *a ,const void *b)
{
	double	*pa=(double *)a;
	double	*pb=(double *)b;
	if(*pa>*pb)
		return 1;
	if(*pa<*pb)
		return -1;
	return 0;
}

void	EachThresholdCommon::RGBRange2HSVRange(int CR,int CG,int CB
							,int RL,int RH ,int GL ,int GH ,int BL ,int BH
							, double &CH ,double &CS ,double &CV
							, double &HL ,double &HH ,double &SL ,double &SH ,double &VL ,double &VH)
{
	CR=Clipping(CR,0,255);
	CG=Clipping(CG,0,255);
	CB=Clipping(CB,0,255);

	RL=Clipping(RL,0,255);
	RH=Clipping(RH,0,255);
	GL=Clipping(GL,0,255);
	GH=Clipping(GH,0,255);
	BL=Clipping(BL,0,255);
	BH=Clipping(BH,0,255);

	RGB2HSV(CH ,CS ,CV ,CR,CG,CB);
	SL=100;
	SH=0;
	VL=255;
	VH=0;

	double	*HDim=new double[256*256*256];
	int		HDimNumb=0;
	for(int r=RL;r<=RH;r++){
		for(int g=GL;g<=GH;g++){
			for(int b=BL;b<=BH;b++){
				if(r!=255 && g!=255 && b!=255){
					double	tH ,tS ,tV;
					RGB2HSV(tH ,tS ,tV ,r,g,b);
					HDim[HDimNumb]=tH;
					HDimNumb++;
					SL=min(SL,tS);
					SH=max(SH,tS);
					VL=min(VL,tV);
					VH=max(VH,tV);
				}
			}
		}
	}
	if(HDimNumb>0){
		HH=359.9;
		HL=0;
		QSort(HDim,HDimNumb,sizeof(double),SortDounbleFunc);
		if(HDim[0]<=2 && HDim[HDimNumb-1]>=(360-2)){
			for(int i=1;i<HDimNumb;i++){
				if(HDim[i]-HDim[i-1]>3){
					HH=HDim[i];
					break;
				}
			}
			for(int i=HDimNumb-1;i>=1;i--){
				if(HDim[i]-HDim[i-1]>3){
					HL=HDim[i];
					break;
				}
			}
		}
		else{
			HL=HDim[0];
			HH=HDim[HDimNumb-1];
		}
	}
	else{
		HL=HH=0;
	}
	delete	[]HDim;
}

void	EachThresholdCommon::HSVRange2RGBRange(int &CR,int &CG,int &CB
							,int &RL,int &RH ,int &GL ,int &GH ,int &BL ,int &BH
							, double CH ,double CS ,double CV
							, double HL ,double HH ,double SL ,double SH ,double VL ,double VH)
{
	HSV2RGB(CH ,CS ,CV ,CR,CG,CB);

	RL=255;
	RH=0;
	GL=255;
	GH=0;
	BL=255;
	BH=0;

	for(int r=0;r<255;r++){
		for(int g=0;g<255;g++){
			for(int b=0;b<255;b++){
				double	tH ,tS ,tV;
				RGB2HSV(tH ,tS ,tV ,r,g,b);
				if(((HL<=HH) && (HL<=tH && tH<=HH && SL<=tS && tS<=SH && VL<=tV && tV<=VH))
				|| ((HL>HH) && (HH<=tH && tH<=HL && SL<=tS && tS<=SH && VL<=tV && tV<=VH))){
					RL=min(RL,r);
					RH=max(RH,r);
					GL=min(GL,g);
					GH=max(GH,g);
					BL=min(BL,b);
					BH=max(BH,b);
				}
			}
		}
	}
}


void	EachThresholdCommon::AddRGBInThresholdB(int R ,int G ,int B ,int LevelID)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		DotColorMatchingThreshold	*d=DItem->GetThresholdW(GetLayersBase(),LevelID);
		AddRGBInThresholdInside(&d->Broad, R , G , B , LevelID);
	}
}

void	EachThresholdCommon::AddRGBInThresholdN(int R ,int G ,int B ,int LevelID)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		DotColorMatchingThreshold	*d=DItem->GetThresholdW(GetLayersBase(),LevelID);
		AddRGBInThresholdInside(&d->Narrow, R , G , B , LevelID);
	}
}

void	EachThresholdCommon::AddRGBInThresholdInside(DotColorMatchingThreshold::MThreshold *d,int R ,int G ,int B ,int LevelID)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		if(AreaType==_Mono || AreaType==_NoPrint){
			while(R<DItem->CenterBrightR-(APage->BrightWidthTableFlat[MaxThreOffset+d->RThrOffsetL][d->BrightWidthRL])[DItem->CenterBrightR]
			&& d->BrightWidthRL<1000){
				d->BrightWidthRL++;
			}
			while(DItem->CenterBrightR+(APage->BrightWidthTableFlat[MaxThreOffset+d->RThrOffsetH][d->BrightWidthRH])[DItem->CenterBrightR]<R
			&& d->BrightWidthRH<1000){
				d->BrightWidthRH++;
			}
			while(G<DItem->CenterBrightG-(APage->BrightWidthTableFlat[MaxThreOffset+d->GThrOffsetL][d->BrightWidthGL])[DItem->CenterBrightG]
			&& d->BrightWidthGL<1000){
				d->BrightWidthGL++;
			}
			while(DItem->CenterBrightG+(APage->BrightWidthTableFlat[MaxThreOffset+d->GThrOffsetH][d->BrightWidthGH])[DItem->CenterBrightG]<G
			&& d->BrightWidthGH<1000){
				d->BrightWidthGH++;
			}
			while(B<DItem->CenterBrightB-(APage->BrightWidthTableFlat[MaxThreOffset+d->BThrOffsetL][d->BrightWidthBL])[DItem->CenterBrightB]
			&& d->BrightWidthBL<1000){
				d->BrightWidthBL++;
			}
			while(DItem->CenterBrightB+(APage->BrightWidthTableFlat[MaxThreOffset+d->BThrOffsetH][d->BrightWidthBH])[DItem->CenterBrightB]<B
			&& d->BrightWidthBH<1000){
				d->BrightWidthBH++;
			}
		}
		else{
			while(R<DItem->CenterBrightR-(APage->BrightWidthTableComp[MaxThreOffset+d->RThrOffsetL][d->BrightWidthRL])[DItem->CenterBrightR]
			&& d->BrightWidthRL<1000){
				d->BrightWidthRL++;
			}
			while(DItem->CenterBrightR+(APage->BrightWidthTableComp[MaxThreOffset+d->RThrOffsetH][d->BrightWidthRH])[DItem->CenterBrightR]<R
			&& d->BrightWidthRH<1000){
				d->BrightWidthRH++;
			}
			while(G<DItem->CenterBrightG-(APage->BrightWidthTableComp[MaxThreOffset+d->GThrOffsetL][d->BrightWidthGL])[DItem->CenterBrightG]
			&& d->BrightWidthGL<1000){
				d->BrightWidthGL++;
			}
			while(DItem->CenterBrightG+(APage->BrightWidthTableComp[MaxThreOffset+d->GThrOffsetH][d->BrightWidthGH])[DItem->CenterBrightG]<G
			&& d->BrightWidthGH<1000){
				d->BrightWidthGH++;
			}
			while(B<DItem->CenterBrightB-(APage->BrightWidthTableComp[MaxThreOffset+d->BThrOffsetL][d->BrightWidthBL])[DItem->CenterBrightB]
			&& d->BrightWidthBL<1000){
				d->BrightWidthBL++;
			}
			while(DItem->CenterBrightB+(APage->BrightWidthTableComp[MaxThreOffset+d->BThrOffsetH][d->BrightWidthBH])[DItem->CenterBrightB]<B
			&& d->BrightWidthBH<1000){
				d->BrightWidthBH++;
			}
		}
	}
}
void	EachThresholdCommon::SubRGBInThresholdB(int R ,int G ,int B ,int LevelID)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		DotColorMatchingThreshold	*d=DItem->GetThresholdW(GetLayersBase(),LevelID);
		SubRGBInThresholdInside(&d->Broad,R ,G ,B ,LevelID);
	}
}

void	EachThresholdCommon::SubRGBInThresholdN(int R ,int G ,int B ,int LevelID)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		DotColorMatchingThreshold	*d=DItem->GetThresholdW(GetLayersBase(),LevelID);
		SubRGBInThresholdInside(&d->Narrow,R ,G ,B ,LevelID);
	}
}

void	EachThresholdCommon::SubRGBInThresholdInside(DotColorMatchingThreshold::MThreshold *d,int R ,int G ,int B ,int LevelID)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		if(AreaType==_Mono || AreaType==_NoPrint){
			while(DItem->CenterBrightR-(APage->BrightWidthTableFlat[MaxThreOffset+d->RThrOffsetL][d->BrightWidthRL])[DItem->CenterBrightR]<=R
			&& d->BrightWidthRL>0){
				d->BrightWidthRL--;
			}
			while(R<=DItem->CenterBrightR+(APage->BrightWidthTableFlat[MaxThreOffset+d->RThrOffsetH][d->BrightWidthRH])[DItem->CenterBrightR]
			&& d->BrightWidthRH>0){
				d->BrightWidthRH--;
			}
			while(DItem->CenterBrightG-(APage->BrightWidthTableFlat[MaxThreOffset+d->GThrOffsetL][d->BrightWidthGL])[DItem->CenterBrightG]<=G
			&& d->BrightWidthGL>0){
				d->BrightWidthGL--;
			}
			while(G<=DItem->CenterBrightG+(APage->BrightWidthTableFlat[MaxThreOffset+d->GThrOffsetH][d->BrightWidthGH])[DItem->CenterBrightG]
			&& d->BrightWidthGH>0){
				d->BrightWidthGH--;
			}
			while(DItem->CenterBrightB-(APage->BrightWidthTableFlat[MaxThreOffset+d->BThrOffsetL][d->BrightWidthBL])[DItem->CenterBrightB]<=B
			&& d->BrightWidthBL>0){
				d->BrightWidthBL--;
			}
			while(B<=DItem->CenterBrightB+(APage->BrightWidthTableFlat[MaxThreOffset+d->BThrOffsetH][d->BrightWidthBH])[DItem->CenterBrightB]
			&& d->BrightWidthBH>0){
				d->BrightWidthBH--;
			}
		}
		else{
			while(DItem->CenterBrightR-(APage->BrightWidthTableComp[MaxThreOffset+d->RThrOffsetL][d->BrightWidthRL])[DItem->CenterBrightR]<=R
			&& d->BrightWidthRL>0){
				d->BrightWidthRL--;
			}
			while(R<=DItem->CenterBrightR+(APage->BrightWidthTableComp[MaxThreOffset+d->RThrOffsetH][d->BrightWidthRH])[DItem->CenterBrightR]
			&& d->BrightWidthRH>0){
				d->BrightWidthRH--;
			}
			while(DItem->CenterBrightG-(APage->BrightWidthTableComp[MaxThreOffset+d->GThrOffsetL][d->BrightWidthGL])[DItem->CenterBrightG]<=G
			&& d->BrightWidthGL>0){
				d->BrightWidthGL--;
			}
			while(G<=DItem->CenterBrightG+(APage->BrightWidthTableComp[MaxThreOffset+d->GThrOffsetH][d->BrightWidthGH])[DItem->CenterBrightG]
			&& d->BrightWidthGH>0){
				d->BrightWidthGH--;
			}
			while(DItem->CenterBrightB-(APage->BrightWidthTableComp[MaxThreOffset+d->BThrOffsetL][d->BrightWidthBL])[DItem->CenterBrightB]<=B
			&& d->BrightWidthBL>0){
				d->BrightWidthBL--;
			}
			while(B<=DItem->CenterBrightB+(APage->BrightWidthTableComp[MaxThreOffset+d->BThrOffsetH][d->BrightWidthBH])[DItem->CenterBrightB]
			&& d->BrightWidthBH>0){
				d->BrightWidthBH--;
			}
		}
	}
}
bool	EachThresholdCommon::CheckNG(int BRL,int BRH ,int BGL, int BGH ,int BBL ,int BBH
									,int NRL,int NRH ,int NGL, int NGH ,int NBL ,int NBH
									,int Mergin
									,int &Error
									,int &NGSizeB ,int &NGLengthB
									,int &NGSizeN ,int &NGLengthN
									,int LevelID)
{
	bool	Ret=false;
	if(DItem!=NULL){
		QBuffer	TmpBuff;
		TmpBuff.open(QIODevice::ReadWrite);
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);
		W->Save(&TmpBuff);
		TmpBuff.seek(0);

		W->Broad.OKDot=0;
		W->Narrow.OKDot=0;
		SubRGBInThresholdB(BRL-Mergin ,BGL-Mergin ,BBL-Mergin,LevelID);
		SubRGBInThresholdB(BRH+Mergin ,BGH+Mergin ,BBH+Mergin,LevelID);				
		SubRGBInThresholdN(NRL-Mergin ,NGL-Mergin ,NBL-Mergin,LevelID);
		SubRGBInThresholdN(NRH+Mergin ,NGH+Mergin ,NBH+Mergin,LevelID);				
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		W->Save(&Buff);
		IntegrationReqTryInspection	tRCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckTryInspection	tACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		tRCmd.Phase		=RepresentativePhase;
		tRCmd.Page		=RepresentativePage;
		tRCmd.ItemID	=RepresentativeItemID;
		tRCmd.ItemThreshold	=Buff.buffer();
		tRCmd.ZoomRate	=1;
		tRCmd.movx		=0;
		tRCmd.movy		=0;
		tRCmd.ImageW	=50;
		tRCmd.ImageH	=50;
		tRCmd.OverlapNG	=false;
		if(tRCmd.Send(SlaveNo,0,tACmd)==true){
			Error=tACmd.Error;
			NGSizeB		=tACmd.NGSizeB;
			NGLengthB	=tACmd.NGLengthB;
			NGSizeN		=tACmd.NGSizeN;
			NGLengthN	=tACmd.NGLengthN;
			Ret=true;
		}
		W->Load(&TmpBuff);
	}
	return Ret;
}