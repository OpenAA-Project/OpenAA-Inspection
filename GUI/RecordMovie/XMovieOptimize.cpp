#include "RecordMovie.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "swap.h"
//#include <Windows.h>
//#include <vfw.h>
#include <QMutex>
#include <QMessageBox>
#include "ShowMemoryForm.h"
#include "XMovieThread.h"



bool	BmpClass::AddImage(void)
{
	if(BmpData==NULL){
		return false;
	}
	AddedMiliSec	=::GetComputerMiliSec();
	if (Parent->FPS > 0) {
		int page = RecordParent->GetTargetPage();
		if (page < 0)
			page = 0;
		if (page >= GetPageNumb())
			page = GetPageNumb();
		DataInPage* P = GetLayersBase()->GetPageData(page);

		if(Parent->GetAVFormat()==FormatMPeg1){
			AddImageYUV(P);
		}
		else
		if(Parent->GetAVFormat()==FormatMPeg4){
			AddImageYUV(P);
		}
		else
		if(Parent->GetAVFormat()==FormatMotionJPeg){
			AddImageRGB(P);
		}
		return true;
	}
}

void	BmpClass::AddImageYUV(DataInPage* P)
{
	double	Z=1.0/Parent->ZoomRate;
	int	image_height	=Parent->image_height;
	int	image_width		=Parent->image_width;
	int	image_width2	=image_width/2;
	int	*XPosDim=Parent->XPosDim;
	
	GetLayersBase()->LockRChangingDataStructure();
	if (P->GetLayerNumb() >= 3) {
		ImageBuffer& R = P->GetLayerData(0)->GetTargetBuff();
		ImageBuffer& G = P->GetLayerData(1)->GetTargetBuff();
		ImageBuffer& B = P->GetLayerData(2)->GetTargetBuff();
		int	DotPerLine	=R.GetWidth();
		int	MaxLines	=R.GetHeight();
		av_frame_make_writable(picture);

		#pragma omp parallel                             
		{                  
			/* Y */
			#pragma omp for
			for(int y=0;y<image_height;y++) {
				int	Y = y*Z;	//(image_height - y - 1)*Z;
				if(Y<MaxLines){
					BYTE* sR = R.GetYWithoutDepended(Y);
					BYTE* sG = G.GetYWithoutDepended(Y);
					BYTE* sB = B.GetYWithoutDepended(Y);
					uint8_t	*EY=&picture->data[0][y * picture->linesize[0]];
					if((y&1)==0){
						int	my=y/2;
						uint8_t	*ECb=&picture->data[1][my * picture->linesize[1]];
						uint8_t	*ECr=&picture->data[2][my * picture->linesize[2]];
						int	XLen=image_width;
						if(XLen*Z>=DotPerLine){
							XLen=DotPerLine*Parent->ZoomRate;
						}
						for(int x=0;x<XLen;x++) {
							int	X=XPosDim[x];
							//EY[x] = Clipping(((int)(0.257f*sR[X] + 0.504f*sG[X] + 0.098f*sB[X]))+16,0,255);
							EY[x] = Clipping(((16842*sR[X] + 33030*sG[X] + 6422*sB[X]+1048576)>>16),0,255);
						}
						for(int x=XLen;x<image_width;x++){
							EY[x] =Clipping(((1048576)>>16),0,255);
						}
						int	XLen2=image_width2;
						if(XLen2*Z*2>=DotPerLine){
							XLen2=DotPerLine*Parent->ZoomRate/2;
						}
						for(int x=0;x<XLen2;x++) {
							int	X=XPosDim[x]<<1;
						    //ECb[x] = Clipping(((int)(-0.148f*sR[X] - 0.291f*sG[X] + 0.439f*sB[X])) + 128,0,255);
						    //ECr[x] = Clipping(((int)( 0.439f*sR[X] - 0.368f*sG[X] - 0.071f*sB[X])) + 128,0,255);
						    ECb[x] = Clipping(((-9699 *sR[X] - 19070*sG[X] + 28770*sB[X]+8388608)>>16),0,255);
						    ECr[x] = Clipping((( 28770*sR[X] - 24117*sG[X] - 4653 *sB[X]+8388608)>>16),0,255);
						}
						for(int x=XLen2;x<image_width2;x++){
							ECb[x] =Clipping(((8388608)>>16),0,255);
							ECr[x] =Clipping(((8388608)>>16),0,255);
						}
					}
					else{
						int	XLen=image_width;
						if(XLen*Z>=DotPerLine){
							XLen=DotPerLine*Parent->ZoomRate;
						}
						for(int x=0;x<XLen;x++) {
							int	X=XPosDim[x];
							//EY[x] = Clipping(((int)(0.257f*sR[X] + 0.504f*sG[X] + 0.098f*sB[X])) + 16,0,255);
							EY[x] = Clipping(((16842*sR[X] + 33030*sG[X] + 6422*sB[X]+1048576)>>16),0,255);
						}
						for(int x=XLen;x<image_width;x++){
							EY[x] =Clipping(((1048576)>>16),0,255);
						}
					}
				}
				else{
					uint8_t	*EY=&picture->data[0][y * picture->linesize[0]];
					for(int x=0;x<image_width;x++) {
						EY[x] = Clipping(((1048576)>>16),0,255);
					}
					if((y&1)==0){
						int	my=y/2;
						uint8_t	*ECb=&picture->data[1][my * picture->linesize[1]];
						uint8_t	*ECr=&picture->data[2][my * picture->linesize[2]];
						for(int x=0;x<image_width2;x++) {
							ECb[x] =Clipping(((8388608)>>16),0,255);
							ECr[x] =Clipping(((8388608)>>16),0,255);
						}
					}
				}
			}
		}
	}
	GetLayersBase()->UnlockChangingDataStructure();
}

void	BmpClass::AddImageRGB(DataInPage* P)
{
	double	Z=1.0/Parent->ZoomRate;
	int	image_height	=Parent->image_height;
	int	image_width		=Parent->image_width;
	int	image_width2	=image_width/2;
	int	*XPosDim=Parent->XPosDim;
	
	GetLayersBase()->LockRChangingDataStructure();
	if (P->GetLayerNumb() >= 3) {
		ImageBuffer& R = P->GetLayerData(0)->GetTargetBuff();
		ImageBuffer& G = P->GetLayerData(1)->GetTargetBuff();
		ImageBuffer& B = P->GetLayerData(2)->GetTargetBuff();
		int	DotPerLine	=R.GetWidth();
		int	MaxLines	=R.GetHeight();
		int32	AddedInt=(int)(Z*65536);
		int	MaxX=min(R.GetWidth(),(int)(image_width*Z));
		#pragma omp parallel                             
		{                  
			/* Y */
			#pragma omp for
			for(int y=0;y<image_height;y++) {
				int	Y = y*Z;	//(image_height - y - 1)*Z;
				if(Y<MaxLines){
					BYTE* sR = R.GetYWithoutDepended(MaxLines-Y-1);
					BYTE* sG = G.GetYWithoutDepended(MaxLines-Y-1);
					BYTE* sB = B.GetYWithoutDepended(MaxLines-Y-1);
					BYTE	*d=&BmpData[y*image_width*3];
					int32	XAddedInt=0;
					for(int x=0;x<image_width;x++) {
						int	X=(XAddedInt)>>16;
						*(d+0)=sB[X];
						*(d+1)=sG[X];
						*(d+2)=sR[X];
						d+=3;
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
		int	MaxX=min(R.GetWidth(),(int)(image_width*Z));
		#pragma omp parallel                             
		{                  
			/* Y */
			#pragma omp for
			for(int y=0;y<image_height;y++) {
				int	Y = y*Z;	//(image_height - y - 1)*Z;
				if(Y<MaxLines){
					BYTE* sR = R.GetYWithoutDepended(MaxLines-Y-1);
					BYTE	*d=&BmpData[y*image_width*3];
					int32	XAddedInt=0;
					for(int x=0;x<image_width;x++) {
						int	X=(XAddedInt)>>16;
						*(d+0)=sR[X];
						*(d+1)=sR[X];
						*(d+2)=sR[X];
						d+=3;
						XAddedInt+=AddedInt;
					}
				}
			}
		}
	}
	GetLayersBase()->UnlockChangingDataStructure();
}
