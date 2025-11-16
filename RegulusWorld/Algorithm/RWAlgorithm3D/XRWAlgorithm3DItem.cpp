/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\RWAlgorithm3D\XRWAlgorithm3D.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XRWAlgorithm3D.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//===========================================================================================

RWAlgorithm3DItem::RWAlgorithm3DItem(RW3DInPageRoot *p)
	:RW3DItemRoot(p)
{
}

RWAlgorithm3DItem::~RWAlgorithm3DItem(void)
{
}
RW3DItemRoot	*RWAlgorithm3DItem::Clone(void)
{
	RWAlgorithm3DItem	*d=new RWAlgorithm3DItem(GetParentInPage());
	*d=*this;
	return d;
}
RWAlgorithm3DItem &RWAlgorithm3DItem::operator=(const RW3DItemRoot &src)
{
	RW3DItemRoot::operator=(src);

	const RWAlgorithm3DItem	*s=dynamic_cast<const RWAlgorithm3DItem *>(&src);
	if(s!=NULL){
		Items=s->Items;
	}
	return *this;
}


void	RWAlgorithm3DItem::Draw(QImage &pnt, CameraView &CamView,AlgorithmDrawAttr *Attr)
{
	RWAlgorithm3DDrawAttr	*BAttr=dynamic_cast<RWAlgorithm3DDrawAttr *>(Attr);
	RWAlgorithm3DInPage	*Ap=(RWAlgorithm3DInPage *)GetParentInPage();

	Vector3D	Xn(1.0,0,0);
	Vector3D	Yn(0,1.0,0);
	Vector3D	Zn(0,0,1.0);

	float	CosX=cos(CamView.Radian.GetVx());
	float	SinX=sin(CamView.Radian.GetVx());
	float	CosY=cos(CamView.Radian.GetVy());
	float	SinY=sin(CamView.Radian.GetVy());
	float	CosZ=cos(CamView.Radian.GetVz());
	float	SinZ=sin(CamView.Radian.GetVz());

	PointVector3D	Ray;
	Ray.Point	=CamView.Point;
	for(int y=0;y<CamView.ViewYLen;y++){
		QRgb	*s=(QRgb *)pnt.scanLine(y);
		for(int x=0;x<CamView.ViewXLen;x++,s++){
			Vector3D	V(CamView.Length,y-CamView.ViewYLen/2.0,x-CamView.ViewXLen/2.0);
			Vector3D	Rx=V*CosX+Xn*(1-CosX)*V.InnerProduct(Xn)+(Xn*V)*SinX;
			Vector3D	Ry=Rx*CosY+Yn*(1-CosY)*Rx.InnerProduct(Yn)+(Yn*Rx)*SinY;
			Ray.Vector	  =Ry*CosZ+Zn*(1-CosZ)*Ry.InnerProduct(Zn)+(Zn*Ry)*SinZ;
			CrossCluster CrossSides;
			if(Items.GetCrossPoint(Ray,CrossSides)==true && CrossSides.GetCount()){
				for(CrossVolume	*v=CrossSides.GetFirst();v!=NULL;v=v->GetNext()){
					if(v->NearSide.CrossT>0){
						QColor	Col=CrossSides.GetSurface()->GetSurfaceColor(Ap,Ray,v->NearSide);
						*s=Col.rgba();
						break;
					}
				}
			}
		}
	}
}

bool	RWAlgorithm3DItem::GetArea(Point3D &MinPoint ,Point3D &MaxPoint)
{
	return Items.GetArea(MinPoint ,MaxPoint);
}
