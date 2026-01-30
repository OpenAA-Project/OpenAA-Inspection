/*
 * Copyright (C) 2024
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

#include "ShrinkedInspection.h"
#include "XGUI.h"
#include "XPassword.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationBase.h"
#include "XLogOut.h"
#include "XStatusController.h"


void	ShrinkedInspection::CopyFilterdCopy(ImageBuffer &DstImage ,ImageBuffer &SrcImage,int Skip)
{
	int	XNumb=DstImage.GetWidth();
	int	YNumb=DstImage.GetHeight();
	int	DArea=Skip*Skip;
	int	DArea2=DArea>>1;
	int	MArea=16384/DArea;

	if(DstImage.IsDepended()==false
	&& SrcImage.IsDepended()==false){
		#pragma omp parallel
		{
			#pragma omp for	
			for(int y=0;y<YNumb;y++){
				int	sY=y*Skip;
				BYTE	*d=DstImage.GetYWithoutDepended(y);
				int	sX=0;
				for(int x=0;x<XNumb;x++,sX+=Skip){
					int	D=DArea2;
					for(int ky=0;ky<Skip;ky++){
						BYTE	*s=SrcImage.GetYWithoutDepended(sY+ky)+sX;
						for(int kx=0;kx<Skip;kx++){
							D+=s[kx];
						}
					}
					d[x]=((D)*MArea)>>14;
				}
			}
		}
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for	
			for(int y=0;y<YNumb;y++){
				int	sY=y*Skip;
				BYTE	*d=DstImage.GetY(y);
				int	sX=0;
				for(int x=0;x<XNumb;x++,sX+=Skip){
					int	D=DArea2;
					for(int ky=0;ky<Skip;ky++){
						BYTE	*s=SrcImage.GetY(sY+ky)+sX;
						for(int kx=0;kx<Skip;kx++){
							D+=s[kx];
						}
					}
					d[x]=((D)*MArea)>>14;
				}
			}
		}
	}
}