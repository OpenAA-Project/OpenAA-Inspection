/*
 * Copyright (C) 2025
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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include "swap.h"

#include "sapClassBasic.h"
#include "conio.h"
#include "XMainSchemeMemory.h"

#include "saperaCtrl.h"
#include "featureCtrl.h"
#include <omp.h>
#include "XCriticalFunc.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "CameraXtiumCISVienex.h"

bool	CameraXtiumCISVienex::GetImage(	 ImageBuffer *Buff[]
										,int BufferDimCounts
										,CameraScanInfo *Info)
{
	_nStatus = EN_CTRLSTS_IDLE;

	LockGetImage.lock();

	Buff[0]->Swap(ImageStack[0]);
	Buff[1]->Swap(ImageStack[1]);
	Buff[2]->Swap(ImageStack[2]);

	LockGetImage.unlock();
	
	return true;
}

void	CameraXtiumCISVienex::CaptureImage(void)
{
	ImageBuffer *Buff[3];

	//GSleep(10);
	if(GetLayersBase()->IsReadyOK()==true){
		Buff[0]=&ImageStack[0];
		Buff[1]=&ImageStack[1];
		Buff[2]=&ImageStack[2];
		
		int	BuffWidth	=_Buffers->GetWidth();
		int DstWidth	= Buff[0]->GetWidth();
		int BuffHeight	= _Buffers->GetHeight();
		int DstHeight	= Buff[0]->GetHeight();
		int	StartX		=0;	//Parent->Setting.ImageStart;

		void	*SrcAddress;
		_Buffers->GetAddress(&SrcAddress);

		BYTE	RTable[256];
		BYTE	GTable[256];
		BYTE	BTable[256];
		for(int i=0;i<256;i++){
			RTable[i]=Clipping(((int)Setting.GainRedL*i	)	,0,255);
			GTable[i]=Clipping(((int)Setting.GainGreenL*i)	,0,255);
			BTable[i]=Clipping(((int)Setting.GainBlueL*i)	,0,255);
		}

		int		dyR	=Setting.OffsetYRed;
		int		dyG	=Setting.OffsetYGreen;
		int		dyB	=Setting.OffsetYBlue;

		int		YN=BuffHeight;

		if(DstWidth+StartX>BuffWidth){
			DstWidth=BuffWidth-StartX;
		}

		#pragma omp parallel
		{
			#pragma omp for
			for (int i=0; i< YN; i++) {
				// ruglas64��RGB�o�b�t�@�|�C���^�𓾂�
				int	y=i;
				int	yR=i+dyR;
				int	yG=i+dyG;
				int	yB=i+dyB;
				if(yR<0 || DstHeight<=yR
				|| yG<0 || DstHeight<=yG
				|| yB<0 || DstHeight<=yB){
					continue;
				}
				BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
				BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
				BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

				BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

				for (int j=0; j< DstWidth; j++) {
					*pB++ = BTable[*s	 ];		// blue
					*pG++ = GTable[*(s+1)];		// green
					*pR++ = RTable[*(s+2)];		// red
					s+=4;				// mono
				}
			}
		}
	}		
}