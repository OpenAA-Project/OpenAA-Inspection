/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XHalconInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XHalconInspection.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XPropertyHalconInspectionPacket.h"
#include "XGeneralFunc.h"

QString	HalconFuncString[100]={
	 ""
	,"area_center"
	,"closing_circle"
	,"concat_obj"
	,"connection"
	,"count_obj"
	,"difference"
	,"emphasize"
	,"gen_image1"
	,"gen_image3"
	,"get_region_points"
	,"invert_image"
	,"mean_image"
	,"min_max_gray"
	,"select_obj"
	,"select_shape"
	,"threshold"
	,"tuple_max"
	,"tuple_sum"
};

//area_center
Farea_center::Farea_center(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));
		else if(pArg->AType==Tuple)
			IndexData=TupleList->indexOf(QString(pArg->Arg));

		if(Cnt==0)		RIndex		=IndexData;
		else if(Cnt==1)	AreaIndex	=IndexData;
		else if(Cnt==2)	RowIndex	=IndexData;
		else if(Cnt==3)	ColIndex	=IndexData;
	}
}

void Farea_center::ExecHalconFunc()
{
	GetXHalcon()->Harea_center(RIndex,AreaIndex,RowIndex,ColIndex);
}

//closing_circle
Fclosing_circle::Fclosing_circle(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	double DIndexData;
	bool ok;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));
		else if(pArg->AType==Tuple){
			DIndexData=QString(pArg->Arg).toDouble(&ok);
			if(ok==false)
				DIndexData=TupleList->indexOf(QString(pArg->Arg));
		}

		if(Cnt==0)		RIndex	=IndexData;
		else if(Cnt==1)	RCIndex	=IndexData;
		else if(Cnt==2){
			Radius	=DIndexData;
			IsRadiusNumb=ok;
		}
	}
}

void Fclosing_circle::ExecHalconFunc()
{
	GetXHalcon()->Hclosing_circle(RIndex,RCIndex,Radius,IsRadiusNumb);
}

//concat_obj
Fconcat_obj::Fconcat_obj(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));

		if(Cnt==0)		Index1	=IndexData;
		else if(Cnt==1)	Index2	=IndexData;
		else if(Cnt==2)	CIndex	=IndexData;
	}
}

void Fconcat_obj::ExecHalconFunc()
{
	GetXHalcon()->Hconcat_obj(Index1,Index2,CIndex);
}

//connection
Fconnection::Fconnection(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));

		if(Cnt==0)		RIndex	=IndexData;
		else if(Cnt==1)	CRIndex	=IndexData;
	}
}

void Fconnection::ExecHalconFunc()
{
	GetXHalcon()->Hconnection(RIndex,CRIndex);
}

//count_obj
Fcount_obj::Fcount_obj(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));
		else if(pArg->AType==Tuple){
			bool ok;
			IndexData=QString(pArg->Arg).toInt(&ok);
			if(ok==false)
				IndexData=TupleList->indexOf(QString(pArg->Arg));
		}

		if(Cnt==0)		Index	=IndexData;
		else if(Cnt==1)	Number	=IndexData;
	}
}

void Fcount_obj::ExecHalconFunc()
{
	GetXHalcon()->Hcount_obj(Index,Number);
}

//difference
Fdifference::Fdifference(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));

		if(Cnt==0)		RIndex	=IndexData;
		else if(Cnt==1)	SIndex	=IndexData;
		else if(Cnt==2)	RDIndex	=IndexData;
	}
}

void Fdifference::ExecHalconFunc()
{
	GetXHalcon()->Hdifference(RIndex,SIndex,RDIndex);
}

//emphasize
Femphasize::Femphasize(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));
		else if(pArg->AType==Tuple){
			bool ok;
			IndexData=QString(pArg->Arg).toInt(&ok);
			if(ok==false)
				IndexData=TupleList->indexOf(QString(pArg->Arg));
		}

		if(Cnt==0)		IIndex		=IndexData;
		else if(Cnt==1)	IEIndex		=IndexData;
		else if(Cnt==2)	MaskWidth	=IndexData;
		else if(Cnt==3)	MaskHeight	=IndexData;
		else if(Cnt==4)	Factor		=IndexData;
	}
}

void Femphasize::ExecHalconFunc()
{
	GetXHalcon()->Hemphasize(IIndex,IEIndex,MaskWidth,MaskHeight,Factor);
}

//gen_image1
Fgen_image1::Fgen_image1(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));

		if(Cnt==0)		Index	=IndexData;
	}
}

void Fgen_image1::ExecHalconFunc()
{
	GetXHalcon()->Hgen_image1(Index);
}

//gen_image3
Fgen_image3::Fgen_image3(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));

		if(Cnt==0)		Index	=IndexData;
	}
}

void Fgen_image3::ExecHalconFunc()
{
	GetXHalcon()->Hgen_image3(Index);
}

//get_region_points
Fget_region_points::Fget_region_points(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));
		else if(pArg->AType==Tuple){
			bool ok;
			IndexData=QString(pArg->Arg).toInt(&ok);
			if(ok==false)
				IndexData=TupleList->indexOf(QString(pArg->Arg));
		}

		if(Cnt==0)		Index		=IndexData;
		else if(Cnt==1)	RowIndex	=IndexData;
		else if(Cnt==2)	ColIndex	=IndexData;
	}
}

void Fget_region_points::ExecHalconFunc()
{
	GetXHalcon()->Hget_region_points(Index,RowIndex,ColIndex);
}

//invert_image
Finvert_image::Finvert_image(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));

		if(Cnt==0)		IIndex	=IndexData;
		else if(Cnt==1)	IIIndex	=IndexData;
	}
}

void Finvert_image::ExecHalconFunc()
{
	GetXHalcon()->Hinvert_image(IIndex,IIIndex);
}

//mean_image
Fmean_image::Fmean_image(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));
		else if(pArg->AType==Tuple){
			bool ok;
			IndexData=QString(pArg->Arg).toInt(&ok);
			if(ok==false)
				IndexData=TupleList->indexOf(QString(pArg->Arg));
		}

		if(Cnt==0)		IIndex		=IndexData;
		else if(Cnt==1)	IMIndex		=IndexData;
		else if(Cnt==2)	MaskWidth	=IndexData;
		else if(Cnt==2)	MaskHeight	=IndexData;
	}
}

void Fmean_image::ExecHalconFunc()
{
	GetXHalcon()->Hmean_image(IIndex,IMIndex,MaskWidth,MaskHeight);
}

//min_max_gray
Fmin_max_gray::Fmin_max_gray(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));
		else if(pArg->AType==Tuple){
			bool ok;
			IndexData=QString(pArg->Arg).toInt(&ok);
			if(ok==false)
				IndexData=TupleList->indexOf(QString(pArg->Arg));
		}

		if(Cnt==0)		RIndex	=IndexData;
		else if(Cnt==1)	IIndex	=IndexData;
		else if(Cnt==2)	Percent	=IndexData;
		else if(Cnt==3)	Min		=IndexData;
		else if(Cnt==4)	Max		=IndexData;
		else if(Cnt==5)	Range	=IndexData;
	}
}

void Fmin_max_gray::ExecHalconFunc()
{
	GetXHalcon()->Hmin_max_gray(RIndex,IIndex,Percent,Min,Max,Range);
}

//select_obj
Fselect_obj::Fselect_obj(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));
		else if(pArg->AType==Tuple){
			bool ok;
			IndexData=QString(pArg->Arg).toInt(&ok);
			if(ok==false)
				IndexData=TupleList->indexOf(QString(pArg->Arg));
		}

		if(Cnt==0)		Index	=IndexData;
		else if(Cnt==1)	SIndex	=IndexData;
		else if(Cnt==2)	Idx		=IndexData;
	}
}

void Fselect_obj::ExecHalconFunc()
{
	GetXHalcon()->Hselect_obj(Index,SIndex,Idx);
}

//select_shape
Fselect_shape::Fselect_shape(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	int DIndexData;
	bool ok;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));
		else if(pArg->AType==Tuple){
			DIndexData=QString(pArg->Arg).toDouble(&ok);
			if(ok==false)
				DIndexData=TupleList->indexOf(QString(pArg->Arg));
		}

		if(Cnt==0)		RIndex		=IndexData;
		else if(Cnt==1)	SRIndex		=IndexData;
		else if(Cnt==2)	Features	=IndexData;
		else if(Cnt==3)	Operation	=IndexData;
		else if(Cnt==4){
			Min	=DIndexData;
			IsMinNumb=ok;
		}
		else if(Cnt==5){
			Max	=DIndexData;
			IsMaxNumb=ok;
		}
	}
}

void Fselect_shape::ExecHalconFunc()
{
	GetXHalcon()->Hselect_shape(RIndex,SRIndex,Features,Operation,Min,Max,IsMinNumb,IsMaxNumb);
}

//threshold
Fthreshold::Fthreshold(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));
		else if(pArg->AType==Tuple){
			bool ok;
			IndexData=QString(pArg->Arg).toInt(&ok);
			if(ok==false)
				IndexData=TupleList->indexOf(QString(pArg->Arg));
		}

		if(Cnt==0)		IIndex	=IndexData;
		else if(Cnt==1)	RIndex	=IndexData;
		else if(Cnt==2)	MinGray	=IndexData;
		else if(Cnt==3)	MaxGray	=IndexData;
	}
}

void Fthreshold::ExecHalconFunc()
{
	GetXHalcon()->Hthreshold(IIndex,RIndex,MinGray,MaxGray);
}

//tuple_max
Ftuple_max::Ftuple_max(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));
		else if(pArg->AType==Tuple){
			bool ok;
			IndexData=QString(pArg->Arg).toInt(&ok);
			if(ok==false)
				IndexData=TupleList->indexOf(QString(pArg->Arg));
		}

		if(Cnt==0)		TIndex	=IndexData;
		else if(Cnt==1)	Max		=IndexData;
	}
}

void Ftuple_max::ExecHalconFunc()
{
	GetXHalcon()->Htuple_max(TIndex,Max);
}

//tuple_sum
Ftuple_sum::Ftuple_sum(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList)
:HalconFuncListBase(XHalIns,List)
{
	int Cnt=0;
	int IndexData;
	for(HalconArg *pArg=List->ArgList.GetFirst();pArg!=NULL;pArg=pArg->GetNext(),Cnt++){
		if(pArg->AType==Region)
			IndexData=RegionList->indexOf(QString(pArg->Arg));
		else if(pArg->AType==Tuple){
			bool ok;
			IndexData=QString(pArg->Arg).toInt(&ok);
			if(ok==false)
				IndexData=TupleList->indexOf(QString(pArg->Arg));
		}

		if(Cnt==0)		Index	=IndexData;
		else if(Cnt==1)	Sum		=IndexData;
	}
}

void Ftuple_sum::ExecHalconFunc()
{
	GetXHalcon()->Htuple_sum(Index,Sum);
}

bool	HalconSampleList::Save(QIODevice *f)
{
	if(::Save(f,FuncName)==false)
		return false;
	int32	N;
	N=ArgList.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(HalconArg *b=ArgList.GetFirst();b!=NULL;b=b->GetNext()){
		char	*A=b->Arg;
		if(::Save(f,A)==false)
			return false;
		int Type=b->AType;
		if(::Save(f,Type)==false)
			return false;
	}
	return true;
}
	
bool	HalconSampleList::Load(QIODevice *f)
{
	if(::Load(f,FuncName)==false)
		return false;
	int32	N;
	ArgList.RemoveAll();
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		char	A[32];
		int64	Len;
		if(::Load(f,A,Len,32)==false)
			return false;
		int Type;
		if(::Load(f,Type)==false)
			return false;
		HalconArg *b=HalconArg::GetNew(A);
		b->AType=(ArgType)Type;
		ArgList.AppendList(b);
	}
	return true;
}

HalconSampleList	&HalconSampleList::operator=(HalconSampleList &src)
{
//	Name		=src.Name;
//	PickupColor	=src.PickupColor;
	return *this;
}

HalconSampleContainer	&HalconSampleContainer::operator=(HalconSampleContainer &src)
{
	RemoveAll();
//	for(HalconSampleList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
//		HalconSampleList	*d=new HalconSampleList();
//		*d=*s;
//		AppendList(d);
//	}
	return *this;
}

bool	HalconSampleContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(HalconSampleList *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Save(f)==false)
			return false;
	}
	return true;
}

bool	HalconSampleContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		HalconSampleList *s=new HalconSampleList();
		if(s->Load(f)==false)
			return false;
		AppendList(s);
	}
	return true;
}

//=========================================================================================
HalconInspectionLibrary::HalconInspectionLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base),AlgorithmLibrary(LibType)
{
	int i=0;
	HalconFuncString[i++]="";
	HalconFuncString[i++]="area_center";
	HalconFuncString[i++]="closing_circle";
	HalconFuncString[i++]="concat_obj";
	HalconFuncString[i++]="connection";
	HalconFuncString[i++]="count_obj";
	HalconFuncString[i++]="difference";
	HalconFuncString[i++]="emphasize";
	HalconFuncString[i++]="gen_image1";
	HalconFuncString[i++]="gen_image3";
	HalconFuncString[i++]="get_region_points";
	HalconFuncString[i++]="invert_image";
	HalconFuncString[i++]="mean_image";
	HalconFuncString[i++]="min_max_gray";
	HalconFuncString[i++]="select_obj";
	HalconFuncString[i++]="select_shape";
	HalconFuncString[i++]="threshold";
	HalconFuncString[i++]="tuple_max";
	HalconFuncString[i++]="tuple_sum";
	FuncListCount=i;

	i=0;
	FeaturesList[i++]="area";
	FeaturesList[i++]="row";
	FeaturesList[i++]="column";
	FeaturesList[i++]="width";
	FeaturesList[i++]="height";
	FeaturesList[i++]="row1";
	FeaturesList[i++]="column1";
	FeaturesList[i++]="row2";
	FeaturesList[i++]="column2";
	FeaturesList[i++]="circularity";
	FeaturesList[i++]="compactness";
	FeaturesList[i++]="contlength";
	FeaturesList[i++]="convexity";
	FeaturesList[i++]="rectangularity";
	FeaturesList[i++]="ra";
	FeaturesList[i++]="rb";
	FeaturesList[i++]="phi";
	FeaturesList[i++]="anisometry";
	FeaturesList[i++]="bulkiness";
	FeaturesList[i++]="struct_factor";
	FeaturesList[i++]="outer_radius";
	FeaturesList[i++]="inner_radius";
	FeaturesList[i++]="inner_width";
	FeaturesList[i++]="inner_height";
	FeaturesList[i++]="max_diameter";
	FeaturesList[i++]="dist_mean";
	FeaturesList[i++]="dist_deviation";
	FeaturesList[i++]="roundness";
	FeaturesList[i++]="num_sides";
	FeaturesList[i++]="orientation";
	FeaturesList[i++]="connect_num";
	FeaturesList[i++]="holes_num";
	FeaturesList[i++]="euler_number";
	FeaturesList[i++]="rect2_phi";
	FeaturesList[i++]="rect2_len1";
	FeaturesList[i++]="rect2_len2";
	FeaturesList[i++]="moments_m11";
	FeaturesList[i++]="moments_m20";
	FeaturesList[i++]="moments_m02";
	FeaturesList[i++]="moments_ia";
	FeaturesList[i++]="moments_ib";
	FeaturesList[i++]="moments_m11_invar";
	FeaturesList[i++]="moments_m20_invar";
	FeaturesList[i++]="moments_m02_invar";
	FeaturesList[i++]="moments_phi1";
	FeaturesList[i++]="moments_phi2";
	FeaturesList[i++]="moments_m21";
	FeaturesList[i++]="moments_m12";
	FeaturesList[i++]="moments_m03";
	FeaturesList[i++]="moments_m30";
	FeaturesList[i++]="moments_m21_invar";
	FeaturesList[i++]="moments_m12_invar";
	FeaturesList[i++]="moments_m03_invar";
	FeaturesList[i++]="moments_m30_invar";
	FeaturesList[i++]="moments_i1";
	FeaturesList[i++]="moments_i2";
	FeaturesList[i++]="moments_i3";
	FeaturesList[i++]="moments_i4";
	FeaturesList[i++]="moments_psi1";
	FeaturesList[i++]="moments_psi2";
	FeaturesList[i++]="moments_psi3";
	FeaturesList[i++]="moments_psi4";

	i=0;
	OperationList[i++]="and";
	OperationList[i++]="or";

	i=0;
	DirectionList[i++]="left";
	DirectionList[i++]="right";
	DirectionList[i++]="above";
	DirectionList[i++]="below";

	i=0;
	FeatureList[i++]="distance_center";
	FeatureList[i++]="distance_dilate";
	FeatureList[i++]="distance_contour";
	FeatureList[i++]="covers";
	FeatureList[i++]="fits";

	i=0;
	ShapeList[i++]="max_area";
	ShapeList[i++]="rectangle1";
	ShapeList[i++]="rectangle2";
}
HalconInspectionLibrary::~HalconInspectionLibrary(void)
{
}

bool	HalconInspectionLibrary::SaveBlob(QIODevice *f)
{
	if(SampleLists.Save(f)==false)
		return false;
	return true;
}
bool	HalconInspectionLibrary::LoadBlob(QIODevice *f)
{
	if(SampleLists.Load(f)==false)
		return false;
	return true;
}
HalconInspectionLibrary	&HalconInspectionLibrary::operator=(AlgorithmLibrary &src)
{
	SampleLists=((HalconInspectionLibrary *)&src)->SampleLists;
	return *this;
}

HalconInspectionLibraryContainer::HalconInspectionLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}

HalconInspectionLibraryContainer::~HalconInspectionLibraryContainer(void)
{
}

//=========================================================================================
HalconInspectionThreshold::HalconInspectionThreshold(HalconInspectionItem *parent)
:AlgorithmThreshold(parent)
{
}

void	HalconInspectionThreshold::CopyFrom(AlgorithmThreshold &src)
{
	//AlgorithmThreshold::CopyFrom(src);
//	SelAreaID=((HalconInspectionThreshold *)&src)->SelAreaID;
//	Effective=((HalconInspectionThreshold *)&src)->Effective;
}
bool	HalconInspectionThreshold::Save(QIODevice *file)
{
	WORD	Ver=2;

	if(::Save(file,Ver)==false)
		return(false);
	return(true);
}
bool	HalconInspectionThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	return(true);
}

//================================================================================

bool	ResultClusterOnItem::Save(QIODevice *f)
{
	int32	N=List.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(PureFlexAreaList *L=List.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false)
			return false;
	}
	return true;
}
	
bool	ResultClusterOnItem::Load(QIODevice *f)
{
	List.RemoveAll();

	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		PureFlexAreaList	*a=new PureFlexAreaList();
		if(a->Load(f)==false)
			return false;
		List.AppendList(a);
	}
	return true;
}

//===========================================

HalconInspectionItem::HalconInspectionItem(void)
{
	NGBitmap=NULL;
	XByte=YLen=0;
}
HalconInspectionItem::~HalconInspectionItem(void)
{
	if(NGBitmap!=NULL){
		DeleteMatrixBuff(NGBitmap,YLen);
		NGBitmap=NULL;
	}
}

AlgorithmItemPI	&HalconInspectionItem::operator=(AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	return *this;
}

bool    HalconInspectionItem::Save(QIODevice *f)
{
	WORD	Ver=3;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPI::Save(f)==false)
		return false;
	return true;
}
bool    HalconInspectionItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	return true;
}

void	HalconInspectionItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
}

void	HalconInspectionItem::DrawResult    (ResultInItemRoot &Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)
{
	if(Res.GetAddedDataType()==ResultHalconInspectionOnItemType && Res.GetAddedData()!=NULL){
		HalconInspectionBase	*LBase=dynamic_cast<HalconInspectionBase *>(GetParentBase());
		ResultClusterOnItem	*r=(ResultClusterOnItem	*)Res.GetAddedData();
		for(PureFlexAreaList *a=r->List.GetFirst();a!=NULL;a=a->GetNext()){
			a->Draw(0,0 ,&IData ,LBase->ColorNG.rgba()
				,ZoomRate ,MovX ,MovY);
		}
	}
}

bool	HalconInspectionItem::ExecuteInitialAfterEdit	(int ThreadNo,ResultInItemRoot *Res ,EntryPointBase *pInspectionData)
{
	AlgorithmItemPI::ExecuteInitialAfterEdit(ThreadNo,Res ,pInspectionData);

	if(NGBitmap!=NULL){
		if(XByte!=((GetDotPerLine()+7)/8) || YLen!=GetMaxLines()){
			DeleteMatrixBuff(NGBitmap,YLen);
			NGBitmap=NULL;
		}
	}
	if(NGBitmap==NULL){
		XByte	=(GetDotPerLine()+7)/8;
		YLen	=GetMaxLines();
		NGBitmap=MakeMatrixBuff(XByte,YLen);
	}

	for(int i=0;i<GetLayerNumb();i++){
		if(XHal.ImageDataForHalcon[i]!=NULL)
			delete []XHal.ImageDataForHalcon[i];
		XHal.ImageDataForHalcon[i]=new unsigned char[GetDotPerLine()*GetMaxLines()];
	}

	XHal.W	=GetDotPerLine();
	XHal.H	=GetMaxLines();

	MakeExecuteProcess();

	return true;
}

bool	HalconInspectionItem::ExecutePreProcessing(int ThreadNo,ResultInItemRoot *Res ,EntryPointBase *pInspectionData)
{
	AlgorithmItemPI::ExecutePreProcessing(ThreadNo,Res ,pInspectionData);

	if(NGBitmap==NULL){
		XByte	=(GetDotPerLine()+7)/8;
		YLen	=GetMaxLines();
		NGBitmap=MakeMatrixBuff(XByte,YLen);
	}
	MatrixBuffClear(NGBitmap,0,XByte,YLen);

	return true;
}

bool	HalconInspectionItem::ExecuteProcessing(int ThreadNo,ResultInItemRoot *Res ,EntryPointBase *pInspectionData)
{
	int	HalconObj[100];
	int	HalconTup[100];

	//初期化
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<100;i++){
			HalconObj[i]=HalconTup[i]=i;
		}
	}

	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();

	ImageBuffer *TargetImageList[100];

	//Converet from ImageBuffer to Halcon image data
	ImageBufferToHalcon(TargetImageList);

//-------HALCON-------
	for(HalconFuncListBase *Base=HalconFuncList.GetFirst();Base!=NULL;Base=Base->GetNext()){
		Base->ExecHalconFunc();
	}
/*
//-------HALCON-------
	int		Min1,Max1,Range1;
	int		Min,Max,Range;
	int		Area,Row,Column;
	int		MaxArea;
	int		Number1;
	int		Sum1;
	double	Result1;
	int		Min5,Max5,Range5;
	int		Min3,Max3,Range3;
	int		Number;
	int		MaxArea1;
	int		Number2;
	int		Sum2;
	double	Result2;
	int		Min6,Max6,Range6;
	int		Number3,Number4,Number5,Number6;
	int		Result;

	//選別輝度加算値
	int		H1 = 5;
	//大きな不良面積閾値
	double	A1 = 0.001;
	int		A2 = 40;
	//大きな不良輝度閾値
	int		B1 = 9;
	//大きな不良形状閾値
	double	F1 = 1.33;
	//小さな不良形状閾値
	double	C1 = 3.4;
	//小さな不良面積閾値
	double	D1 = 0.001;
	int		D2 = 243;
	//小さな不良輝度閾値
	int		E1 = 10;
	//画像圧縮度合
	double	G1 = 1.5;

	//Converet from ImageBuffer to Halcon image data
	ImageBufferToHalcon	(HalconObj[0],TargetImageList,LNumb);

	//平滑化
	XHal.Hmean_image	(HalconObj[0],HalconObj[1],3,3);

	//画像強調
	XHal.Hemphasize		(HalconObj[1],HalconObj[2],3,3,1);

	//白黒反転
	XHal.Hinvert_image	(HalconObj[2],HalconObj[3]);
	XHal.Hmin_max_gray	(HalconObj[3],HalconObj[3],1,Min1,Max1,Range1);
	Min1 += H1;
	XHal.Hthreshold		(HalconObj[3],HalconObj[4],0,Min1);
	XHal.Hthreshold		(HalconObj[3],HalconObj[5],0,0.75*Min1);
	XHal.Hdifference	(HalconObj[4],HalconObj[5],HalconObj[6]);

	//Region5の検査
	XHal.Hmin_max_gray	(HalconObj[5],HalconObj[0],2,Min,Max,Range);
	XHal.Hclosing_circle(HalconObj[5],HalconObj[6],6);
	XHal.Hconnection	(HalconObj[6],HalconObj[7]);
	XHal.Hselect_shape	(HalconObj[7],HalconObj[8],"anisometry","and",F1,60);
	XHal.Harea_center	(HalconObj[7],HalconTup[0],HalconTup[1],HalconTup[2]);
	XHal.Htuple_max		(HalconTup[0],MaxArea);
	//大きな不良　面積閾値
	XHal.Hselect_shape	(HalconObj[8],HalconObj[9],"area","and",A1*MaxArea,999999);
	XHal.Hselect_shape	(HalconObj[9],HalconObj[10],"area","and",A2,99999);
	XHal.Hmin_max_gray	(HalconObj[10],HalconObj[0],7,HalconTup[3],HalconTup[4],HalconTup[5],true);
	XHal.Hcount_obj		(HalconObj[10],Number1);
	if(Number1>1){
		XHal.Htuple_sum	(HalconTup[4],Sum1);
		//大きな不良　輝度閾値
		Result1 = B1+((double)Sum1/Number1);
		for(int s=1;s<=Number1;s++){
			XHal.Hselect_obj	(HalconObj[10],HalconObj[11],s);
			XHal.Hmin_max_gray	(HalconObj[11],HalconObj[0],7,Min5,Max5,Range5);
			if(Max5>Result1)
				XHal.Hconcat_obj(HalconObj[12],HalconObj[11],HalconObj[12]);
		}
	}
	else
		XHal.Hconcat_obj(HalconObj[13],HalconObj[10],HalconObj[13]);

	//RegionDifferenceの検査
	XHal.Hclosing_circle(HalconObj[6],HalconObj[14],5.5);
	XHal.Hmin_max_gray	(HalconObj[14],HalconObj[0],2,Min3,Max3,Range3);
	XHal.Hconnection	(HalconObj[14],HalconObj[15]);
	//小さな不良　形状による絞込み
	XHal.Hselect_shape	(HalconObj[15],HalconObj[16],"anisometry","and",C1,60);
	XHal.Harea_center	(HalconObj[16],HalconTup[6],HalconTup[7],HalconTup[8]);
	XHal.Hcount_obj		(HalconObj[16],Number);
	if(Number>0){
		XHal.Htuple_max	(HalconTup[6],MaxArea1);
		//小さな不良　面積閾値
		XHal.Hselect_shape	(HalconObj[16],HalconObj[17],"area","and",D1*MaxArea1,99999);
		XHal.Hselect_shape	(HalconObj[17],HalconObj[18],"area","and",D2,99999);
		XHal.Hmin_max_gray	(HalconObj[18],HalconObj[0],7,HalconTup[9],HalconTup[10],HalconTup[11],true);
		XHal.Hcount_obj		(HalconObj[18],Number2);
		if(Number2>1){
			XHal.Htuple_sum	(HalconTup[10],Sum2);
			//小さな不良　輝度閾値
			Result2 = ((double)Sum2/Number2)+E1;
			for (int t=1;t<=Number2;t++){
				XHal.Hselect_obj	(HalconObj[18],HalconObj[19],t);
				XHal.Hmin_max_gray	(HalconObj[19],HalconObj[0],7,Min6,Max6,Range6);
				if(Max6>Result2)
		            XHal.Hconcat_obj(HalconObj[20],HalconObj[19],HalconObj[20]);
			}
		}
		else
			XHal.Hconcat_obj(HalconObj[21],HalconObj[18],HalconObj[21]);
	}
	XHal.Hcount_obj(HalconObj[12],Number3);
	XHal.Hcount_obj(HalconObj[20],Number4);
	XHal.Hcount_obj(HalconObj[13],Number5);
	XHal.Hcount_obj(HalconObj[21],Number6);
	Result=Number3+Number4+Number5+Number6;

	//NG箇所の中心座標を求める
	if(Number3>1){
		XHal.Harea_center(HalconObj[12],HalconTup[12],HalconTup[13],HalconTup[14]);
		for(int i=1;i<=Number3;i++){
			int Len,Row,Column;
//			int Row1,Column1;
//			XHal.GetTupleValue		(HalconTup[13],i-1,Row1);
//			XHal.GetTupleValue		(HalconTup[14],i-1,Column1);
			XHal.Hselect_obj		(HalconObj[12],HalconObj[22],i);
			XHal.Hget_region_points	(HalconObj[22],HalconTup[24],HalconTup[25]);
			XHal.GetTupleLength		(HalconTup[24],Len);
			for(int j=0;j<Len;j++){
				XHal.GetTupleValue	(HalconTup[24],j,Row);
				XHal.GetTupleValue	(HalconTup[25],j,Column);
				NGBitmap[Row][Column>>3] |= (0x80>>(Column&7));
			}
		}
	}
	if(Number4>1){
		XHal.Harea_center(HalconObj[20],HalconTup[15],HalconTup[16],HalconTup[17]);
		for(int i=1;i<=Number4;i++){
			int Len,Row,Column;
			XHal.Hselect_obj		(HalconObj[20],HalconObj[22],i);
			XHal.Hget_region_points	(HalconObj[22],HalconTup[24],HalconTup[25]);
			XHal.GetTupleLength		(HalconTup[24],Len);
			for(int j=0;j<Len;j++){
				XHal.GetTupleValue	(HalconTup[24],j,Row);
				XHal.GetTupleValue	(HalconTup[25],j,Column);
				NGBitmap[Row][Column>>3] |= (0x80>>(Column&7));
			}
		}
	}
	if(Number5>1){
		XHal.Harea_center(HalconObj[13],HalconTup[18],HalconTup[19],HalconTup[20]);
		for(int i=1;i<Number5;i++){
			int Len,Row,Column;
			XHal.Hselect_obj		(HalconObj[13],HalconObj[22],i);
			XHal.Hget_region_points	(HalconObj[22],HalconTup[24],HalconTup[25]);
			XHal.GetTupleLength		(HalconTup[24],Len);
			for(int j=0;j<Len;j++){
				XHal.GetTupleValue	(HalconTup[24],j,Row);
				XHal.GetTupleValue	(HalconTup[25],j,Column);
				NGBitmap[Row][Column>>3] |= (0x80>>(Column&7));
			}
		}
	}
	if(Number6>1){
		XHal.Harea_center(HalconObj[21],HalconTup[21],HalconTup[22],HalconTup[23]);
		for(int i=1;i<Number6;i++){
			int Len,Row,Column;
			XHal.Hselect_obj		(HalconObj[21],HalconObj[22],i);
			XHal.Hget_region_points	(HalconObj[22],HalconTup[24],HalconTup[25]);
			XHal.GetTupleLength		(HalconTup[24],Len);
			for(int j=0;j<Len;j++){
				XHal.GetTupleValue	(HalconTup[24],j,Row);
				XHal.GetTupleValue	(HalconTup[25],j,Column);
				NGBitmap[Row][Column>>3] |= (0x80>>(Column&7));
			}
		}
	}
*/
//	HalconInspectionInPage *PData=(HalconInspectionInPage *)GetParentInPage();

	PureFlexAreaListContainer FPack;
	PickupFlexArea(NGBitmap,XByte ,XNumb,YLen ,FPack);

	if(Res->GetAddedData()==NULL){
		Res->SetAddedData(new ResultClusterOnItem(),ResultHalconInspectionOnItemType);
	}
	else{
		Res->GetAddedData()->Clear();
	}
	int	NGNumb=0;
	PureFlexAreaList *f;
	while((f=FPack.GetFirst())!=NULL){
		FPack.RemoveList(f);
		f->Regulate();
		((ResultClusterOnItem *)Res->GetAddedData())->List.AppendList(f);
		NGNumb++;
	}
	if(NGNumb==0){
		Res->SetError(1);
	}
	else{
		Res->SetError(2);
	}
	Res->SetResult1(NGNumb);
	Res->SetAlignedXY(0,0);
    Res->SetItemSearchedXY(0,0);

	return true;
}

bool	HalconInspectionItem::GetHalconInspectionLibrary(GUIDirectMessage *CmdPacket)
{
	AlgorithmBase	*MBase=GetLayersBase()->GetAlgorithmBase("Basic","HalconInspection");
	if(MBase!=NULL){
		CmdGetHalconInspectionLibraryListPacket	*Packet=dynamic_cast<CmdGetHalconInspectionLibraryListPacket *>(CmdPacket);
		if(Packet!=NULL){
			Packet->LibFolderID=-1;
			MBase->TransmitDirectly(Packet);
			return true;
		}
	}
	return false;
}

void	HalconInspectionItem::ImageBufferToHalcon(ImageBuffer *Buff[])
{
	int iDotPerLine	=GetDotPerLine();
	int iMaxLines	=GetMaxLines();
	int	LNumb		=GetTargetBuffList(Buff);

	for(int L=0;L<LNumb;L++){
		for(int Y=0;Y<iMaxLines;Y++){
			BYTE *pBuff=Buff[L]->GetY(Y);
			for(int X=0;X<iDotPerLine;X++)
				XHal.ImageDataForHalcon[L][Y*iDotPerLine+X]=pBuff[X];
		}
	}
}

void	HalconInspectionItem::MakeExecuteProcess(void)
{
	//HALCONライブラリを取得して反映
	int	DefaultLibID=((HalconInspectionBase *)GetParentBase())->DefaultLibraryID;
	CmdGetHalconInspectionLibraryListPacket	packet;
	AlgorithmLibraryList *p=NULL;
	if(GetHalconInspectionLibrary(&packet)==true){
		for(p=packet.AList.GetFirst();p!=NULL;p=p->GetNext()){
			if(p->GetLibID()==DefaultLibID)
				break;
		}
	}
	if(p!=NULL){
		HalconInspectionLibrary ALib(GetLibraryContainer()->GetLibType(),GetLayersBase());
		if(GetLibraryContainer()->GetLibrary(p->GetLibID(),ALib)==true){
			//文字列リストを渡す
			SetStringList(&ALib);
			//Region,Tupleのインデックスを求める
			ArgRegionList.clear();
			ArgTupleList.clear();
			for(HalconSampleList *s=ALib.SampleLists.GetFirst();s!=NULL;s=s->GetNext()){
				for(HalconArg *HArg=s->ArgList.GetFirst();HArg!=NULL;HArg=HArg->GetNext()){
					if(HArg->AType==Region){
						if(ArgRegionList.contains(QString(HArg->Arg))==false)
							ArgRegionList.append(QString(HArg->Arg));
					}
					else if(HArg->AType==Tuple && IsNumb(HArg->Arg)==false){
						if(ArgTupleList.contains(QString(HArg->Arg))==false)
							ArgTupleList.append(QString(HArg->Arg));
					}
				}
			}
			for(HalconSampleList *s=ALib.SampleLists.GetFirst();s!=NULL;s=s->GetNext()){
				CreateHalconFunc(s);
			}
		}
	}
}

void	HalconInspectionItem::CreateHalconFunc(HalconSampleList *List)
{
	HalconFuncListBase *HalconFunc=NULL;
	if(List->FuncName=="area_center"){
		HalconFunc=new Farea_center(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="closing_circle"){
		HalconFunc=new Fclosing_circle(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="concat_obj"){
		HalconFunc=new Fconcat_obj(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="connection"){
		HalconFunc=new Fconnection(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="count_obj"){
		HalconFunc=new Fcount_obj(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="difference"){
		HalconFunc=new Fdifference(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="emphasize"){
		HalconFunc=new Femphasize(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="gen_image1"){
		HalconFunc=new Fgen_image1(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="gen_image3"){
		HalconFunc=new Fgen_image3(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="get_region_points"){
		HalconFunc=new Fget_region_points(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="invert_image"){
		HalconFunc=new Finvert_image(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="mean_image"){
		HalconFunc=new Fmean_image(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="min_max_gray"){
		HalconFunc=new Fmin_max_gray(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="select_obj"){
		HalconFunc=new Fselect_obj(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="select_shape"){
		HalconFunc=new Fselect_shape(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="threshold"){
		HalconFunc=new Fthreshold(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="tuple_max"){
		HalconFunc=new Ftuple_max(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else if(List->FuncName=="tuple_sum"){
		HalconFunc=new Ftuple_sum(&XHal,List,&ArgRegionList,&ArgTupleList);
	}
	else{
	}
	if(HalconFunc!=NULL)
		HalconFuncList.AppendList(HalconFunc);
}

bool	HalconInspectionItem::IsNumb(char Arg[])
{
	bool ok;
	QString(Arg).toDouble(&ok);
	return ok;
}

void	HalconInspectionItem::SetStringList(HalconInspectionLibrary *p)
{
	XHal.SetFuturesList		(p->FeaturesList);
	XHal.SetOperationList	(p->OperationList);
	XHal.SetNormList		(p->NormList);
	XHal.SetDirectionList	(p->DirectionList);
	XHal.SetFeatureList		(p->FeatureList);
	XHal.SetShapeList		(p->ShapeList);
}

//===========================================

HalconInspectionInPage::HalconInspectionInPage(AlgorithmBase *parent)
:AlgorithmInPagePI(parent)
{
}

HalconInspectionInPage::~HalconInspectionInPage(void)
{
}

void	HalconInspectionInPage::Initial(LayersBase *Base)
{
	AlgorithmInPagePI::Initial(Base);
	AppendItem(CreateItem(-1,0));
};

void	HalconInspectionInPage::TransmitDirectly(GUIDirectMessage *packet)
{
/*	AddHalconInspectionAreaPacket	*AddMArea=dynamic_cast<AddHalconInspectionAreaPacket *>(packet);
	if(AddMArea!=NULL){
		for(IntClass *d=AddMArea->LayerList.GetFirst();d!=NULL;d=d->GetNext()){
			HalconInspectionInLayer	*L=(HalconInspectionInLayer *)GetLayerData(d->d);
			HalconInspectionItem	*MData=(HalconInspectionItem	*)L->NewChild(0);
			MData->GetThresholdW()->Effective	=AddMArea->Effective;
			MData->SetArea(AddMArea->Area);
			MData->GetThresholdW()->SelAreaID	=AddMArea->LimitedLib;
			MData->SetManualCreated(true);
			L->AppendItem(MData);
		}
		return;
	}
*/
}

//===========================================
HalconInspectionBase::HalconInspectionBase(void)
{
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorMask	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	ColorNG			=Qt::red;
	TransparentLevel=80;
	DefaultLibraryID=-1;

//	ColorEffective			=Qt::yellow;
//	ColorEffectiveLimited	=Qt::green;
//	ColorIneffective		=Qt::cyan;
//	ColorIneffectiveLimited	=Qt::magenta;

	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,"Color for Selected Mask");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,"Color for Active Mask");
	SetParam(&NegColorMask		, /**/"Color" ,/**/"NegColorMask"		,"Color for Negative Mask");
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,"Color for Selected Negative Mask");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for Transparent display level");
	SetParam(&ColorNG			, /**/"Color" ,/**/"ColorNG"			,"NG circle color");

//	SetParam(&ColorEffective			, "ItemColor"	,"ColorEffective"			,"Effective button color"			);
//	SetParam(&ColorEffectiveLimited		, "ItemColor"	,"ColorEffectiveLimited"	,"Limited Effective button color"	);
//	SetParam(&ColorIneffective			, "ItemColor"	,"ColorIneffective"			,"Ineffective button color"			);
//	SetParam(&ColorIneffectiveLimited	, "ItemColor"	,"ColorIneffectiveLimited"	,"Limited Ineffective button color"	);

	SetParam(&DefaultLibraryID	, /**/"Setting"	,/**/"DefaultLibraryID"	,"Default LibraryID");
}

bool	HalconInspectionBase::SaveOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::SaveOnlyBase(f)==false)
		return false;
	return true;
}
bool	HalconInspectionBase::LoadOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::LoadOnlyBase(f)==false)
		return false;
	return true;
}

void	HalconInspectionBase::TransmitDirectly(GUIDirectMessage *packet)
{
	if(dynamic_cast<CmdAddItem *>(packet)!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			GetPageData(page)->TransmitDirectly(packet);
		}
	}
	CmdCreateNGListPacket	*CmdCreateNGListPacketVar=dynamic_cast<CmdCreateNGListPacket *>(packet);
	if(CmdCreateNGListPacketVar!=NULL){
		if(CmdCreateNGListPacketVar->Res!=NULL){
			ResultBaseForAlgorithmRoot	*AR=CmdCreateNGListPacketVar->Res->GetResultBaseForAlgorithm(this);
			if(AR!=NULL){
				for(int page=0;page<GetPageNumb();page++){
					ResultInPageRoot	*RP=AR->GetPageData(page);
					ResultInPagePI	*RPI=dynamic_cast<ResultInPagePI *>(RP);
					for(int i=0;i<RP->GetNGCount();i++){
						ResultInItemPI		*RI=RPI->GetItem(i);
						if(RI->GetAddedDataType()==ResultHalconInspectionOnItemType && RI->GetAddedData()!=NULL){
							ResultClusterOnItem	*Ro=(ResultClusterOnItem *)RI->GetAddedData();
							for(PureFlexAreaList *p=Ro->List.GetFirst();p!=NULL;p=p->GetNext()){
								HalconNGDataList	*a=new HalconNGDataList();
								a->Page=page;
								p->GetCenter(a->CenterX,a->CenterY);
								a->LibID=RI->GetAlgorithmItemRoot()->GetLibID();
								a->Area=p->GetPatternByte();
								CmdCreateNGListPacketVar->Point->AppendList(a);
							}
						}
					}
				}
			}
		}
	}
	CmdCreateTempHalconInspectionLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempHalconInspectionLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new HalconInspectionLibrary(GetLibType(),GetLayersBase());
		return;
	}
	CmdGetHalconInspectionLibraryListPacket	*AListPacket=dynamic_cast<CmdGetHalconInspectionLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(AListPacket->LibFolderID==-1)
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->AList);
		else
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID,AListPacket->AList);
		return;
	}
//	CmdGetHalconInspectionLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetHalconInspectionLibraryNamePacket *>(packet);
//	if(ANamePacket!=NULL){
//		GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
//		return;
//	}
	CmdInsertHalconInspectionLibraryPacket	*BInsLib=dynamic_cast<CmdInsertHalconInspectionLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		BInsLib->Point->SetDataVersion(HalconInspectionVersion);
		GetLibraryContainer()->SaveNew(*BInsLib->Point);
		return;
	}
	CmdUpdateHalconInspectionLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateHalconInspectionLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		BUpdLib->Point->SetDataVersion(HalconInspectionVersion);
		GetLibraryContainer()->Update(*BUpdLib->Point);
		return;
	}
	CmdLoadHalconInspectionLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadHalconInspectionLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		GetLibraryContainer()->Load(*BLoadLib->Point);
		return;
	}
	CmdDeleteHalconInspectionLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteHalconInspectionLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		return;
	}
}
