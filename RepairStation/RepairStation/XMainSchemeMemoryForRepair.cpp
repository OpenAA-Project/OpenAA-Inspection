/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


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
//					#pragma omp parallel	//������openMP�ɂ����Ƃ������Ēx���Ȃ�
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