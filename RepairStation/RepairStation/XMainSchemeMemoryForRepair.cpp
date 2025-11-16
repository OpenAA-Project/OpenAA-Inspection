/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\XMainSchemeMemoryForRepair.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include<QIODevice>
#include"XMainSchemeMemoryForRepair.h"
#include "XPointer.h"
#include "swap.h"
#include "XGeneralFunc.h"
#include "omp.h"

ImageBufferForRepair::ImageBufferForRepair(int idcode)
{
}
ImageBufferForRepair::ImageBufferForRepair(int idcode ,int xlen ,int ylen ,bool noRelease)
{
}
ImageBufferForRepair::ImageBufferForRepair(BYTE **data,int idcode ,int xlen ,int ylen ,bool noRelease)
{
}

ImageBufferForRepair::~ImageBufferForRepair(void)
{
}

bool    ImageBufferForRepair::Load(QIODevice *f)
{
    int iMaxX,iMaxY,iMemoryType;
    int iPage;
	int	Ver;

    if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
        return(false);
	
	if(Ver==2){
	    if(f->read((char *)&iPage,sizeof(iPage))!=sizeof(iPage))
		    return(false);
	    if(f->read((char *)&iMemoryType,sizeof(iMemoryType))!=sizeof(iMemoryType))
		    return(false);
	    if(f->read((char *)&iMaxX,sizeof(iMaxX))!=sizeof(iMaxX))
		    return(false);
	    if(f->read((char *)&iMaxY,sizeof(iMaxY))!=sizeof(iMaxY))
		    return(false);
		Page=iPage;
		if(IsNull()==false){
		    if(iMaxX!=(MaxX<<Resolution) || iMaxY!=(MaxY<<Resolution)){
			    Free();
				Set(iPage,iMemoryType,iMaxX>>Resolution,iMaxY>>Resolution);
			}
//		    for(int y=0;y<MaxY;y++){
//			    if(f->read((char *)GetY(y),MaxX)!=MaxX)
			int OriginalMaxX=MaxX<<Resolution;
			int OriginalMaxY=MaxY<<Resolution;
			int Bit=(0x01<<Resolution)-1;
			BYTE	*CopyWork=new BYTE[OriginalMaxX];
			BYTE	*CopyBuff=new BYTE[MaxX];
		    for(int y=0,CntY=0;CntY<OriginalMaxY;CntY++){
			    if(f->read((char *)CopyWork,OriginalMaxX)!=OriginalMaxX)
				    return(false);
				if((CntY&Bit)==0){
//					#pragma omp parallel	//‚±‚±‚ðopenMP‚É‚·‚é‚Æ‚©‚¦‚Á‚Ä’x‚­‚È‚é
//					{
//						#pragma omp for
						for(int x=0;x<OriginalMaxX;x++){
							if((x&Bit)==0)
								CopyBuff[x>>Resolution]=CopyWork[x];
						}
//					}
//					memcpy((void *)GetY(y++),(void *)CopyWork,MaxX);
					memcpy(GetY(y++),CopyBuff,MaxX);
				}
			}
		}
		else{
			BYTE	*Dummy=new BYTE[MaxX];
		    for(int y=0;y<MaxY;y++){
				if(f->read((char *)Dummy,MaxX)!=MaxX){
					delete	[]Dummy;
					return(false);
				}
			}
		}
	}
    return(true);
}
