/*
 * Copyright (C) 2026
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

#include "RecordMovie.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "swap.h"
#include <QMutex>
#include <QDir>
#include "XEntryPoint.h"
#include "ShowCycleTime.h"


bool	RecordMovie::AddImage(void)
{
	if(Running==true && SharedMemForMovie!=NULL && Semaphore!=NULL){
		double	Z=1.0/ZoomRate;
		DataInPage* P = GetLayersBase()->GetPageData(UsePage);
		if(LastTime==0){
			StartTime	=::GetComputerMiliSec();
			LastTime	=StartTime;
		}

		void	*BuffTop=SharedMemForMovie->data();
		struct RecordHeaderStruct	*H=(struct RecordHeaderStruct *)BuffTop;
		BYTE *pData = ((BYTE *)BuffTop)+sizeof(struct RecordHeaderStruct);
		DWORD	CurrentTime=::GetComputerMiliSec();
		H->CurrentTime	=CurrentTime-StartTime;
		H->Duration		=CurrentTime-LastTime;
		SharedMemForMovie->lock();

		GetLayersBase()->LockRChangingDataStructure();
		if (P->GetLayerNumb() >= 3) {
			ImageBuffer& R = P->GetLayerData(0)->GetTargetBuff();
			ImageBuffer& G = P->GetLayerData(1)->GetTargetBuff();
			ImageBuffer& B = P->GetLayerData(2)->GetTargetBuff();
			int	DotPerLine	=R.GetWidth();
			int	MaxLines	=R.GetHeight();
			int32	AddedInt=(int)(Z*65536);
			//int	MaxX=min(R.GetWidth(),(int)(image_width*Z));
			#pragma omp parallel                             
			{                  
				/* Y */
				#pragma omp for
				for(int y=0;y<MovieYSize;y++) {
					int	Y = y*Z;	//(image_height - y - 1)*Z;
					if(Y<MaxLines){
						BYTE* sR = R.GetYWithoutDepended(Y);
						BYTE* sG = G.GetYWithoutDepended(Y);
						BYTE* sB = B.GetYWithoutDepended(Y);
						BYTE	*d=&pData[y*MovieXSize*4];
						int32	XAddedInt=0;
						for(int x=0;x<MovieXSize;x++) {
							int	X=(XAddedInt)>>16;
							*(d+0)=sB[X];
							*(d+1)=sG[X];
							*(d+2)=sR[X];
							*(d+3)=0;
							d+=4;
							XAddedInt+=AddedInt;
						}
					}
				}
			}
		}
		else
		if (P->GetLayerNumb()==1) {
			ImageBuffer& R = P->GetLayerData(0)->GetTargetBuff();
			int	DotPerLine	=R.GetWidth();
			int	MaxLines	=R.GetHeight();
			int32	AddedInt=(int)(Z*65536);
			//int	MaxX=min(R.GetWidth(),(int)(image_width*Z));
			#pragma omp parallel                             
			{                  
				/* Y */
				#pragma omp for
				for(int y=0;y<MovieYSize;y++) {
					int	Y = y*Z;	//(image_height - y - 1)*Z;
					if(Y<MaxLines){
						BYTE* sR = R.GetYWithoutDepended(Y);
						BYTE	*d=&pData[y*MovieXSize*4];
						int32	XAddedInt=0;
						for(int x=0;x<MovieXSize;x++) {
							int	X=(XAddedInt)>>16;
							*(d+0)=sR[X];
							*(d+1)=sR[X];
							*(d+2)=sR[X];
							*(d+3)=0;
							d+=4;
							XAddedInt+=AddedInt;
						}
					}
				}
			}
		}
		GetLayersBase()->UnlockChangingDataStructure();
		SharedMemForMovie->unlock();
	
		Semaphore->release(1);
		LastTime=CurrentTime;
		QThread::msleep(1);
	}
}