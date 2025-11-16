/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XHalcon.h
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#ifndef XHALCONH
#define XHALCONH

#include <QString>

//---------------------------------------------------------------------------

class   XHalcon   //HALCONのライブラリを使用する
{
//	Hobject HImage;

  public:
    XHalcon(void);

	unsigned char *ImageDataForHalcon[3];
	int		W,H;

//[Regions] 領域
	//Features 特徴抽出
	void    Harea_center					(int Regions,int Area,int Row,int Column);
	void	Hcircularity					(int Regions,int Circularity);
	void	Hcompactness					(int Regions,int Compactness);
	void	Hconnect_and_holes				(int Regions,int NumConnected,int NumHoles);
	void	Hcontlength						(int Regions,int ContLength);
	void	Hconvexity						(int Regions,int Convexity);
	void	Hdiameter_region				(int Regions,int Row1,int Column1,int Row2,int Column2,int Diameter);
	void	Heccentricity					(int Regions,int Anisometry,int Bulkiness,int StructureFactor);
	void	Helliptic_axis					(int Regions,int Ra,int Rb,int Phi);
	void	Heuler_number					(int Regions,int EulerNumber);
	void	Hfind_neighbors					(int Regions1,int Regions2,int MaxDistance ,int RegionIndex1,int RegionIndex2,bool IsMaxDistanceNumb);
	void	Hget_region_index				(int Regions,int Row,int Column,int Index,bool IsRowNumb,bool IsColumnNumb);
	void	Hget_region_thickness			(int Regions,int Thickness,int Histogramm);
	void	Hhamming_distance				(int Regions1,int Regions2,int Distance ,int Similarity);
	void	Hhamming_distance_norm			(int Regions1,int Regions2,int Norm,int Distance,int Similarity);
	void	Hinner_circle					(int Regions,int Row,int Column,int Radius);
	void	Hinner_rectangle1				(int Regions,int Row1,int Column1,int Row2,int Column2);
	void	Hmoments_region_2nd				(int Regions,int M11,int M20,int M02,int Ia,int Ib);
	void	Hmoments_region_2nd_invar		(int Regions,int M11,int M20,int M02);
	void	Hmoments_region_2nd_rel_invar	(int Regions,int PHI1,int PHI2);
	void	Hmoments_region_3rd				(int Regions,int M21,int M12,int M03,int M30);
	void	Hmoments_region_3rd_invar		(int Regions,int M21,int M12,int M03,int M30);
	void	Hmoments_region_central			(int Regions,int I1,int I2,int I3,int I4);
	void	Hmoments_region_central_invar	(int Regions,int PSI1,int PSI2,int PSI3,int PSI4);
	void	Horientation_region				(int Regions,int Phi);
	void	Hrectangularity					(int Regions,int Rectangularity);
	void	Hroundness						(int Regions,int Distance,int Sigma,int Roundness,int Sides);
	void	Hrunlength_distribution			(int Regions,int Foreground,int Background);
	void	Hrunlength_features				(int Regions,int NumRuns,int KFactor,int LFactor,int MeanLength,int Bytes);
	void	Hselect_region_point			(int Regions,int DestRegions,int Row,int Column,bool IsRowNumb,bool IsColumnNumb);
	void	Hselect_region_spatial			(int Regions1,int Regions2,int Direction,int RegionIndex1,int RegionIndex2);
	void    Hselect_shape					(int Regions,int SelectedRegions,int Features,int Operation,double Min,double Max,bool IsMinNumb,bool IsMaxNumb);
	void    Hselect_shape_proto				(int Regions,int Pattern,int SelectedRegions,int Feature,double Min,double Max,bool IsMinNumb,bool IsMaxNumb);
	void    Hselect_shape_std				(int Regions,int SelectedRegions,int Shape,double Percent,bool IsPercentNumb);
	void	Hsmallest_circle				(int Regions,int Row,int Column,int Radius);
	void	Hsmallest_rectangle1			(int Regions,int Row1,int Column1,int Row2,int Column2);
	void	Hsmallest_rectangle2			(int Regions,int Row,int Column,int Phi,int Length1,int Length2);
	void	Hspatial_relation				(int Regions1,int Regions2,int Percent,int RegionIndex1,int RegionIndex2,int Relation1,int Relation2,bool IsPercentNumb);

	void    Hclosing_circle		(int RIndex,int RCIndex,double Radius,bool IsRadiusNumb);
	void    Hconcat_obj			(int Index1,int Index2,int CIndex);
	void    Hconnection			(int RIndex,int CRIndex);
	void    Hcount_obj			(int Index,int Number);
	void    Hdifference			(int RIndex,int SIndex,int RDIndex);
	void    Hemphasize			(int IIndex,int IEIndex,int MaskWidth,int MaskHeight,int Factor);
	void    Hgen_image1			(int Index);
	void    Hgen_image3			(int Index);
	void    Hget_region_points	(int Index,int RowIndex,int ColIndex);
	void    Hinvert_image		(int IIndex,int IIIndex);
	void    Hmean_image			(int IIndex,int IMIndex,int MaskWidth,int MaskHeight);
	void    Hmin_max_gray		(int RIndex,int IIndex,int Percent,int Min,int Max,int Range);
	void    Hselect_obj			(int Index,int SIndex,int Idx);
	void    Hthreshold			(int IIndex,int RIndex,int MinGray,int MaxGray);
	void    Htuple_max			(int TIndex,int Max);
	void    Htuple_sum			(int Index,int Sum);

	void	GetTupleValue		(int TIndex,int Index,int Value);
	void	GetTupleLength		(int TIndex,int Value);

	void	SetFuturesList		(char **List)	{	FeaturesList	=List;	}
	void	SetOperationList	(char **List)	{	OperationList	=List;	}
	void	SetNormList			(char **List)	{	NormList		=List;	}
	void	SetDirectionList	(char **List)	{	DirectionList	=List;	}
	void	SetFeatureList		(char **List)	{	FeatureList		=List;	}
	void	SetShapeList		(char **List)	{	ShapeList		=List;	}

private:
	char	**FeaturesList;
	char	**OperationList;
	char	**NormList;
	char	**DirectionList;
	char	**FeatureList;
	char	**ShapeList;
};

#endif
