/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XHalcon.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#include "HalconCpp.h"
#include "XHalcon.h"

using namespace Halcon;

//---------------------------------------------------------------------------

static Hobject	Hobj[100];
static HTuple	HTup[100];

XHalcon::XHalcon(void)
{
	ImageDataForHalcon[0]=ImageDataForHalcon[1]=ImageDataForHalcon[2]=NULL;
}

//[Regions] óÃàÊ - Features ì¡í•íäèo
void    XHalcon::Harea_center(int Regions,int Area,int Row,int Column)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	area_center(Hobj[Regions],&HTup[Area],&HTup[Row],&HTup[Column]);
}

void    XHalcon::Hcircularity(int Regions,int Circularity)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	circularity(Hobj[Regions],&HTup[Circularity]);
}

void    XHalcon::Hcompactness(int Regions,int Compactness)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	compactness(Hobj[Regions],&HTup[Compactness]);
}

void    XHalcon::Hconnect_and_holes(int Regions,int NumConnected,int NumHoles)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	connect_and_holes(Hobj[Regions],&HTup[NumConnected],&HTup[NumHoles]);
}

void    XHalcon::Hcontlength(int Regions,int ContLength)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	contlength(Hobj[Regions],&HTup[ContLength]);
}

void    XHalcon::Hconvexity(int Regions,int Convexity)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	convexity(Hobj[Regions],&HTup[Convexity]);
}

void    XHalcon::Hdiameter_region(int Regions,int Row1,int Column1,int Row2,int Column2,int Diameter)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	diameter_region(Hobj[Regions],&HTup[Row1],&HTup[Column1],&HTup[Row2],&HTup[Column2],&HTup[Diameter]);
}

void    XHalcon::Heccentricity(int Regions,int Anisometry,int Bulkiness,int StructureFactor)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	eccentricity(Hobj[Regions],&HTup[Anisometry],&HTup[Bulkiness],&HTup[StructureFactor]);
}

void    XHalcon::Helliptic_axis(int Regions,int Ra,int Rb,int Phi)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	elliptic_axis(Hobj[Regions],&HTup[Ra],&HTup[Rb],&HTup[Phi]);
}

void    XHalcon::Heuler_number(int Regions,int EulerNumber)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	euler_number(Hobj[Regions],&HTup[EulerNumber]);
}

void    XHalcon::Hfind_neighbors(int Regions1,int Regions2,int MaxDistance ,int RegionIndex1,int RegionIndex2,bool IsMaxDistanceNumb)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	if(IsMaxDistanceNumb)
		find_neighbors(Hobj[Regions1],Hobj[Regions2],MaxDistance,&HTup[RegionIndex1],&HTup[RegionIndex2]);
	else
		find_neighbors(Hobj[Regions1],Hobj[Regions2],HTup[MaxDistance],&HTup[RegionIndex1],&HTup[RegionIndex2]);
}

void    XHalcon::Hget_region_index(int Regions,int Row,int Column,int Index,bool IsRowNumb,bool IsColumnNumb)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	if(IsRowNumb){
		if(IsColumnNumb)
			get_region_index(Hobj[Regions],Row,Column,&HTup[Index]);
		else
			get_region_index(Hobj[Regions],Row,HTup[Column],&HTup[Index]);
	}
	else{
		if(IsColumnNumb)
			get_region_index(Hobj[Regions],HTup[Row],Column,&HTup[Index]);
		else
			get_region_index(Hobj[Regions],HTup[Row],HTup[Column],&HTup[Index]);
	}
}

void    XHalcon::Hget_region_thickness(int Regions,int Thickness,int Histogramm)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	get_region_thickness(Hobj[Regions],&HTup[Thickness],&HTup[Histogramm]);
}

void    XHalcon::Hhamming_distance(int Regions1,int Regions2,int Distance ,int Similarity)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	hamming_distance(Hobj[Regions1],Hobj[Regions2],&HTup[Distance],&HTup[Similarity]);
}

void    XHalcon::Hhamming_distance_norm(int Regions1,int Regions2,int Norm,int Distance,int Similarity)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	hamming_distance_norm(Hobj[Regions1],Hobj[Regions2],NormList[Norm],&HTup[Distance],&HTup[Similarity]);
}

void    XHalcon::Hinner_circle(int Regions,int Row,int Column,int Radius)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	inner_circle(Hobj[Regions],&HTup[Row],&HTup[Column],&HTup[Radius]);
}

void    XHalcon::Hinner_rectangle1(int Regions,int Row1,int Column1,int Row2,int Column2)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	inner_rectangle1(Hobj[Regions],&HTup[Row1],&HTup[Column1],&HTup[Row2],&HTup[Column2]);
}

void    XHalcon::Hmoments_region_2nd(int Regions,int M11,int M20,int M02,int Ia,int Ib)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	moments_region_2nd(Hobj[Regions],&HTup[M11],&HTup[M20],&HTup[M02],&HTup[Ia],&HTup[Ib]);
}

void    XHalcon::Hmoments_region_2nd_invar(int Regions,int M11,int M20,int M02)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	moments_region_2nd_invar(Hobj[Regions],&HTup[M11],&HTup[M20],&HTup[M02]);
}

void    XHalcon::Hmoments_region_2nd_rel_invar(int Regions,int PHI1,int PHI2)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	moments_region_2nd_rel_invar(Hobj[Regions],&HTup[PHI1],&HTup[PHI2]);
}

void    XHalcon::Hmoments_region_3rd(int Regions,int M21,int M12,int M03,int M30)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	moments_region_3rd(Hobj[Regions],&HTup[M21],&HTup[M12],&HTup[M03],&HTup[M30]);
}

void    XHalcon::Hmoments_region_3rd_invar(int Regions,int M21,int M12,int M03,int M30)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	moments_region_3rd_invar(Hobj[Regions],&HTup[M21],&HTup[M12],&HTup[M03],&HTup[M30]);
}

void    XHalcon::Hmoments_region_central(int Regions,int I1,int I2,int I3,int I4)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	moments_region_central(Hobj[Regions],&HTup[I1],&HTup[I2],&HTup[I3],&HTup[I4]);
}

void    XHalcon::Hmoments_region_central_invar(int Regions,int PSI1,int PSI2,int PSI3,int PSI4)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	moments_region_central_invar(Hobj[Regions],&HTup[PSI1],&HTup[PSI2],&HTup[PSI3],&HTup[PSI4]);
}

void    XHalcon::Horientation_region(int Regions,int Phi)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	orientation_region(Hobj[Regions],&HTup[Phi]);
}

void    XHalcon::Hrectangularity(int Regions,int Rectangularity)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	rectangularity(Hobj[Regions],&HTup[Rectangularity]);
}

void    XHalcon::Hroundness(int Regions,int Distance,int Sigma,int Roundness,int Sides)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	roundness(Hobj[Regions],&HTup[Distance],&HTup[Sigma],&HTup[Roundness],&HTup[Sides]);
}

void    XHalcon::Hrunlength_distribution(int Regions,int Foreground,int Background)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	runlength_distribution(Hobj[Regions],&HTup[Foreground],&HTup[Background]);
}

void    XHalcon::Hrunlength_features(int Regions,int NumRuns,int KFactor,int LFactor,int MeanLength,int Bytes)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	runlength_features(Hobj[Regions],&HTup[NumRuns],&HTup[KFactor],&HTup[LFactor],&HTup[MeanLength],&HTup[Bytes]);
}

void    XHalcon::Hselect_region_point(int Regions,int DestRegions,int Row,int Column,bool IsRowNumb,bool IsColumnNumb)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	if(IsRowNumb){
		if(IsColumnNumb)
			select_region_point(Hobj[Regions],&Hobj[DestRegions],Row,Column);
		else
			select_region_point(Hobj[Regions],&Hobj[DestRegions],Row,HTup[Column]);
	}
	else{
		if(IsColumnNumb)
			select_region_point(Hobj[Regions],&Hobj[DestRegions],HTup[Row],Column);
		else
			select_region_point(Hobj[Regions],&Hobj[DestRegions],HTup[Row],HTup[Column]);
	}
}

void    XHalcon::Hselect_region_spatial(int Regions1,int Regions2,int Direction,int RegionIndex1,int RegionIndex2)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	select_region_spatial(Hobj[Regions1],Hobj[Regions2],DirectionList[Direction],&HTup[RegionIndex1],&HTup[RegionIndex2]);
}

void    XHalcon::Hselect_shape(int Regions,int SelectedRegions,int Features,int Operation,double Min,double Max,bool IsMinNumb,bool IsMaxNumb)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	if(IsMinNumb){
		if(IsMaxNumb)
			select_shape(Hobj[Regions],&Hobj[SelectedRegions],FeaturesList[Features],OperationList[Operation],Min,Max);
		else{
			select_shape(Hobj[Regions],&Hobj[SelectedRegions],FeaturesList[Features],OperationList[Operation],Min,HTup[(int)Max]);
		}
	}
	else{
		if(IsMaxNumb)
			select_shape(Hobj[Regions],&Hobj[SelectedRegions],FeaturesList[Features],OperationList[Operation],HTup[(int)Min],Max);
		else
			select_shape(Hobj[Regions],&Hobj[SelectedRegions],FeaturesList[Features],OperationList[Operation],HTup[(int)Min],HTup[(int)Max]);
	}
}

void    XHalcon::Hselect_shape_proto(int Regions,int Pattern,int SelectedRegions,int Feature,double Min,double Max,bool IsMinNumb,bool IsMaxNumb)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	if(IsMinNumb){
		if(IsMaxNumb)
			select_shape_proto(Hobj[Regions],Hobj[Pattern],&Hobj[SelectedRegions],FeatureList[Feature],Min,Max);
		else
			select_shape_proto(Hobj[Regions],Hobj[Pattern],&Hobj[SelectedRegions],FeatureList[Feature],Min,HTup[(int)Max]);
	}
	else{
		if(IsMaxNumb)
			select_shape_proto(Hobj[Regions],Hobj[Pattern],&Hobj[SelectedRegions],FeatureList[Feature],HTup[(int)Min],Max);
		else
			select_shape_proto(Hobj[Regions],Hobj[Pattern],&Hobj[SelectedRegions],FeatureList[Feature],HTup[(int)Min],HTup[(int)Max]);
	}
}

void    XHalcon::Hselect_shape_std(int Regions,int SelectedRegions,int Shape,double Percent,bool IsPercentNumb)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	if(IsPercentNumb)
		select_shape_std(Hobj[Regions],&Hobj[SelectedRegions],ShapeList[Shape],Percent);
	else
		select_shape_std(Hobj[Regions],&Hobj[SelectedRegions],ShapeList[Shape],HTup[(int)Percent]);
}

void    XHalcon::Hsmallest_circle(int Regions,int Row,int Column,int Radius)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	smallest_circle(Hobj[Regions],&HTup[Row],&HTup[Column],&HTup[Radius]);
}

void    XHalcon::Hsmallest_rectangle1(int Regions,int Row1,int Column1,int Row2,int Column2)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	smallest_rectangle1(Hobj[Regions],&HTup[Row1],&HTup[Column1],&HTup[Row2],&HTup[Column2]);
}

void    XHalcon::Hsmallest_rectangle2(int Regions,int Row,int Column,int Phi,int Length1,int Length2)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	smallest_rectangle2(Hobj[Regions],&HTup[Row],&HTup[Column],&HTup[Phi],&HTup[Length1],&HTup[Length2]);
}

void    XHalcon::Hspatial_relation(int Regions1,int Regions2,int Percent,int RegionIndex1,int RegionIndex2,int Relation1,int Relation2,bool IsPercentNumb)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	if(IsPercentNumb)
		spatial_relation(Hobj[Regions1],Hobj[Regions2],Percent,&HTup[RegionIndex1],&HTup[RegionIndex2],&HTup[Relation1],&HTup[Relation2]);
	else
		spatial_relation(Hobj[Regions1],Hobj[Regions2],HTup[Percent],&HTup[RegionIndex1],&HTup[RegionIndex2],&HTup[Relation1],&HTup[Relation2]);
}




void    XHalcon::Hclosing_circle(int RIndex,int RCIndex,double Radius,bool IsRadiusNumb)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	if(IsRadiusNumb)
		closing_circle(Hobj[RIndex],&Hobj[RCIndex],Radius);
	else
		closing_circle(Hobj[RIndex],&Hobj[RCIndex],HTup[(int)Radius]);
}

void    XHalcon::Hconcat_obj(int Index1,int Index2,int CIndex)
{
	extern Hobject	Hobj[100];
	concat_obj(Hobj[Index1],Hobj[Index2],&Hobj[CIndex]);
}

void    XHalcon::Hconnection(int RIndex,int CRIndex)
{
	extern Hobject	Hobj[100];
	connection(Hobj[RIndex],&Hobj[CRIndex]);
}

void    XHalcon::Hcount_obj(int Index,int Number)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	count_obj(Hobj[Index],&HTup[Number]);
}

void    XHalcon::Hdifference(int RIndex,int SIndex,int RDIndex)
{
	extern Hobject	Hobj[100];
	difference(Hobj[RIndex],Hobj[SIndex],&Hobj[RDIndex]);
}

void    XHalcon::Hemphasize(int IIndex,int IEIndex,int MaskWidth,int MaskHeight,int Factor)
{
	extern Hobject	Hobj[100];
	emphasize(Hobj[IIndex],&Hobj[IEIndex],MaskWidth,MaskHeight,Factor);
}

void    XHalcon::Hgen_image1(int Index)
{
	extern Hobject	Hobj[100];
	gen_image1(&Hobj[Index],"byte",W,H,(long)ImageDataForHalcon[0]);
}

void    XHalcon::Hgen_image3(int Index)
{
	extern Hobject	Hobj[100];
	gen_image3(&Hobj[Index],"byte",W,H,(long)ImageDataForHalcon[0],(long)ImageDataForHalcon[1],(long)ImageDataForHalcon[2]);
}

void    XHalcon::Hget_region_points(int Index,int RowIndex,int ColIndex)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	get_region_points(Hobj[Index],&HTup[RowIndex],&HTup[ColIndex]);
}

void    XHalcon::Hinvert_image(int IIndex,int IIIndex)
{
	extern Hobject	Hobj[100];
	invert_image(Hobj[IIndex],&Hobj[IIIndex]);
}

void    XHalcon::Hmean_image(int IIndex,int IMIndex,int MaskWidth,int MaskHeight)
{
	extern Hobject	Hobj[100];
	mean_image(Hobj[IIndex],&Hobj[IMIndex],MaskWidth,MaskHeight);
}

void    XHalcon::Hmin_max_gray(int RIndex,int IIndex,int Percent,int Min,int Max,int Range)
{
	extern Hobject	Hobj[100];
	extern HTuple	HTup[100];
	min_max_gray(Hobj[RIndex],Hobj[IIndex],Percent,&HTup[Min],&HTup[Max],&HTup[Range]);
}

void    XHalcon::Hselect_obj(int Index,int SIndex,int Idx)
{
	extern Hobject	Hobj[100];
	select_obj(Hobj[Index],&Hobj[SIndex],Idx);
}

void    XHalcon::Hthreshold(int IIndex,int RIndex,int MinGray,int MaxGray)
{
	extern Hobject	Hobj[100];
	threshold(Hobj[IIndex],&Hobj[RIndex],MinGray,MaxGray);
}

void    XHalcon::Htuple_max(int TIndex,int Max)
{
	extern HTuple	HTup[100];
	tuple_max(HTup[TIndex],&HTup[Max]);
}

void    XHalcon::Htuple_sum(int Index,int Sum)
{
	extern HTuple	HTup[100];
	tuple_sum(HTup[Index],&HTup[Sum]);
}

void    XHalcon::GetTupleValue(int TIndex,int Index,int Value)
{
	extern HTuple	HTup[100];
	tuple_int(HTup[TIndex][Index],&HTup[Value]);
}

void    XHalcon::GetTupleLength(int TIndex,int Value)
{
	extern HTuple	HTup[100];
	tuple_length(HTup[TIndex],&HTup[Value]);
}
