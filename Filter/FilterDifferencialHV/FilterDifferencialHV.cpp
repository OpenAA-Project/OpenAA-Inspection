/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterHorizontalBand\FilterHorizontalBand.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "FilterDifferencialHV.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingDialog.h"
#include "swap.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XFFT1d.h"

bool		DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="FilterDifferencialHV";
	return(true);
}

WORD		DLL_GetVersion(void)
//	return Filter DLL version
{
	return(2);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Differencial HV";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterDifferencialHV(base);
}

bool		DLL_Load(FilterClassBase *handle ,QIODevice &str)
//	Load filter attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	return handle->Load(&str);
}

bool		DLL_Save(FilterClassBase *handle ,QIODevice &str)
//	Save filter attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	return handle->Save(&str);
}
bool		DLL_ShowSetting(FilterClassBase *handle, QWidget *parent)
//	This function shows dialog to set filter(handle) information
//	if dialog can't be shown, it returns false
{

	SettingDialog		D(handle->GetLayersBase()
										,((FilterDifferencialHV *)handle)->Gain
										,((FilterDifferencialHV *)handle)->Length
										,((FilterDifferencialHV *)handle)->Layers
										,((FilterDifferencialHV *)handle)->Vertical
										,((FilterDifferencialHV *)handle)->BPF
										,((FilterDifferencialHV *)handle)->PassWidth
										 ,parent);
	if(D.exec()==(int)true){
		((FilterDifferencialHV *)handle)->Gain			=D.Gain;
		((FilterDifferencialHV *)handle)->Length		=D.Length;
		((FilterDifferencialHV *)handle)->Layers		=D.Layers;
		((FilterDifferencialHV *)handle)->Vertical		=D.Vertical;
		((FilterDifferencialHV *)handle)->BPF			=D.BPF;
		((FilterDifferencialHV *)handle)->PassWidth		=D.PassWidth;

	}
	return true;
}
bool		DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterDifferencialHV::FilterDifferencialHV(LayersBase *base)
:FilterClassBase(base)
{	
	Gain		=1.0;
	Length		=3;
	Vertical	=false;
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int layer=0;layer<GetLayerNumb(LayerNumb);layer++){
		Layers.Add(true);
	}
	MutBPF=NULL;
	BPF	=false;
	PassWidth	=0;
}

FilterDifferencialHV::~FilterDifferencialHV(void)
{
	if(MutBPF!=NULL){
		delete	[]MutBPF;
		MutBPF=NULL;
	}
}

bool	FilterDifferencialHV::Save(QIODevice *f)
{
	if(::Save(f,Gain)==false)
		return false;
	if(::Save(f,Length)==false)
		return false;
	if(::Save(f,Vertical)==false)
		return false;
	if(Layers.Save(f)==false)
		return false;
	if(::Save(f,BPF)==false)
		return false;
	if(::Save(f,PassWidth)==false)
		return false;

	return true;
}
bool	FilterDifferencialHV::Load(QIODevice *f)
{
	if(::Load(f,Gain)==false)
		return false;
	if(::Load(f,Length)==false)
		return false;
	if(::Load(f,Vertical)==false)
		return false;
	if(Layers.Load(f)==false)
		return false;
	if(GetLoadedDLLVersion()>=2){
		if(::Load(f,BPF)==false)
			return false;
		if(::Load(f,PassWidth)==false)
			return false;
	}
	return true;
}

bool	FilterDifferencialHV::Initial(void)
{
	if(BPF==true){
		if(MutBPF!=NULL){
			delete	[]MutBPF;
		}
		MutBPF=new double[Length];
		
		/*
		int	CenterPos=Length/2;
		int	i=0;
		for(i=0;i<CenterPos;i++){
			MutBPF[i]=-1;
		}
		for(;i<Length;i++){
			MutBPF[i]=1;
		}
		A=0;
		AA=0;
		for(int i=0;i<Length;i++){
			A+=MutBPF[i];
			AA+=MutBPF[i]*MutBPF[i];
		}
		*/

		
		double	Z=1.0/PassWidth;
		for(int i=0;i<Length;i++){
			double	C=(double)Length/2.0;
			double	X=(i-C)*Z;
			double	E=exp(-X);
			MutBPF[i]=E*(E-1)/((1+E)*(1+E)*(1+E));
		}
		int	N2=Length/2-PassWidth*2;
		double	P2=MutBPF[N2];
		for(int i=0;i<N2;i++){
			MutBPF[i]=P2;
		}
		int	N3=Length/2+PassWidth*2;
		double	P3=MutBPF[N3];
		for(int i=N3;i<Length;i++){
			MutBPF[i]=P3;
		}

		A=0;
		AA=0;
		for(int i=0;i<Length;i++){
			A+=MutBPF[i];
			AA+=MutBPF[i]*MutBPF[i];
		}
		


		/*
		int	CenterPos=Length/2;
		int	L2=PassWidth/2;
		if(L2<=0)
			L2=1;
		int	i=0;
		for(i=0;i<=L2 && i<CenterPos;i++){
			MutBPF[CenterPos+i]= 2.0*65536.0/L2*i;
			MutBPF[CenterPos-i]=-2.0*65536.0/L2*i;
		}
		for(i=L2+1;i<PassWidth && i<CenterPos;i++){
			MutBPF[CenterPos+i]=-2.0*65536.0/(L2+1)*(i-L2)+2*65536.0;
			MutBPF[CenterPos-i]= 2.0*65536.0/(L2+1)*(i-L2)-2*65536.0;
		}
		for(int k=i;(CenterPos-k)>=0;k++){
			MutBPF[CenterPos-k]=-65536.0/(CenterPos-L2)*(k-;
		}
		for(int k=i;(CenterPos+k)<Length ;k++){
			MutBPF[CenterPos+k]=65536.0;
		}
		*/
	}

	return true;
}
bool	FilterDifferencialHV::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	if(0<=Length && Length<NewDotPerLine)
		return false;
	return FilterClassBase::ReallocXYPixels(NewDotPerLine ,NewMaxLines);
}

bool	FilterDifferencialHV::Reallocate(int newLayerNumb)
{
	if(Layers.GetCount()==newLayerNumb){
		return false;
	}
	if(Layers.GetCount()>newLayerNumb){
		while(Layers.GetCount()>newLayerNumb){
			BoolClass	*v=Layers.GetLast();
			Layers.RemoveList(v);
			delete	v;
		}
		return true;
	}
	return FilterClassBase::Reallocate(newLayerNumb);
}
bool	FilterDifferencialHV::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	if(BPF==false){
		if(Vertical==false){
			for(int L=0;L<BufferDimCounts;L++){
				if(Layers[L]==false)
					continue;
				int YNumb=GetMaxLines();
				int	LP=Length/2-1;
				if(LP==0)
					LP=1;
				int	XNumb=GetDotPerLine()-LP;
				#pragma omp parallel
				{
					#pragma omp for
					for(int y=0;y<YNumb;y++){
						BYTE	LineBuff[16384];
						BYTE	*s=Buff[L]->GetY(y);
						memcpy(LineBuff,s,GetDotPerLine());
							
						for(int	x=LP;x<XNumb;x++){
							int	AddX1=0;
							int	AddX2=0;
							for(int i=0;i<LP;i++){
								AddX1+=LineBuff[x+i];
								AddX2+=LineBuff[x+Length-LP+i];
							}

							int	V=LineBuff[x]+((double)(AddX1-AddX2)/(double)LP)*Gain;
							if(V<0)
								V=0;
							if(V>255)
								V=255;
							s[x]=V;
						}
					}
				}
			}
		}
		else{
			for(int L=0;L<BufferDimCounts;L++){
				if(Layers[L]==false)
					continue;
				int XNumb=GetDotPerLine();
				int	LP=Length/2-1;
				if(LP==0)
					LP=1;
				int	YNumb=GetMaxLines()-LP;
				ImageBuffer	*SBuff=Buff[L];
				#pragma omp parallel
				{
					#pragma omp for
					for(int x=0;x<XNumb;x++){
						BYTE	LineBuff[1024*1024];
						for(int y=0;y<GetMaxLines();y++){
							LineBuff[y]=SBuff->GetY(y)[x];
						}

						for(int y=LP;y<YNumb;y++){
							int	AddY1=0;
							int	AddY2=0;
							for(int i=0;i<LP;i++){
								AddY1+=LineBuff[y+i];
								AddY2+=LineBuff[y+Length-LP+i];
							}

							int	V=LineBuff[y]+((double)(AddY1-AddY2)/(double)LP)*Gain;
							if(V<0)
								V=0;
							if(V>255)
								V=255;
							SBuff->GetY(y)[x]=V;
						}
					}
				}
			}
		}
	}
	else{
		if(Vertical==false && MutBPF!=NULL){
			for(int L=0;L<BufferDimCounts;L++){
				if(Layers[L]==false)
					continue;
				int YNumb=GetMaxLines();
				int	LP=Length/2-1;
				if(LP==0)
					LP=1;
				int	XNumb=GetDotPerLine()-LP;
				#pragma omp parallel
				{
					#pragma omp for
					for(int y=0;y<YNumb;y++){
						BYTE	LineBuff[16384];
						BYTE	*s=Buff[L]->GetY(y);
						memcpy(LineBuff,s,GetDotPerLine());
							
						for(int	x=LP;x<XNumb;x++){
							/*
							double	AddX1=0;
							int		AddedN=0;
							for(int i=0;i<Length;i++){
								AddedN+=LineBuff[x-LP+i];
							}
							double	Avr=((double)AddedN)/((double)Length);
							for(int i=0;i<Length;i++){
								AddX1 +=(LineBuff[x-LP+i]-Avr)*MutBPF[i];
							}
							int	V=LineBuff[x]+(double)(AddX1*Gain);
							*/

							int	B=0;
							int	BB=0;
							double	AB=0;
							for(int i=0;i<Length;i++){
								int	c=LineBuff[x-LP+i];
								B+=c;
								BB+=c*c;
								AB+=c*MutBPF[i];
							}
							double	AvrS=((double)A)/(double)Length;
							double	AvrD=((double)B)/(double)Length;

							double	Pa=((double)AA-Length*AvrS*AvrS);
							double	Pb=((double)BB-Length*AvrD*AvrD);
							double	M=Pa*Pb;
							if(M>0){
								M=sqrt(M);
								double	K=(double)AB-Length*AvrS*AvrD;
								double	H=(K/M);

								int	V=LineBuff[x]+(double)(H*H*H*H*sqrt(Pb)*Gain);
								if(V<0)
									V=0;
								if(V>255)
									V=255;
								s[x]=V;
							}
						}
					}
				}
			}
		}	
	}


	return true;
}

