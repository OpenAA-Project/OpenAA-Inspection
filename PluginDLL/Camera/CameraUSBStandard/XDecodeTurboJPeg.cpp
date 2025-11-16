#include "CameraUSBStandard.h"
#include "jpeglib.h"
#include "turbojpeg.h"
#include "XGeneralFunc.h"
#include "XDLLType.h"
#include "XCameraDLL.h"
#include "XMainSchemeMemory.h"
#include "swap.h"
#include "XCriticalFunc.h"
#include <mfapi.h>
#include "XLibWMF.h"
#include "LibWMFCamera.h"
#define JPEG_INTERNALS

void	SetTimeSpan(DWORD tt1);

//#define	DecodeOpenMP

//void	MakeMJPeg(USBStandardData &CamData,long BuffSize ,int Xn ,int Yn ,ImageBuffer *Buff[]
//				,bool MirrorX ,bool MirrorY
//				,int RotationAngle)
void TransformImage_MJPG(
	LibWMFCamera *Cam
	,ImageBuffer *Buff[]
	,const BYTE* aSrc
	,LONG        aSrcStride
	,DWORD       aWidthInPixels
	,DWORD       aHeightInPixels
	,DWORD		SrcTotalBuffByte
	,bool		MirrorX
	,bool		MirrorY
	,int		RotationAngle
	)
{
	int	width;
	int	height;
	int jpegSubsamp;
	int	jpegColorspace;

	DWORD	tt1=::GetComputerMiliSec();
	int n1=tjDecompressHeader3(Cam->DecHndle
		,aSrc,SrcTotalBuffByte
		,&width
        ,&height
		,&jpegSubsamp
        ,&jpegColorspace);

	if((width==Buff[0]->GetWidth() && height==Buff[0]->GetHeight() && (RotationAngle==0 || RotationAngle==180))
	|| (width==Buff[0]->GetHeight() && height==Buff[0]->GetWidth() && (RotationAngle==90 || RotationAngle==270))){

		int	n2=tjDecompress2(Cam->DecHndle
			,aSrc,SrcTotalBuffByte
	        ,Cam->GetMJPegTmpBuff()
			,width,0,height
			,TJPF_RGB,	  TJFLAG_FORCESSE3 
						| TJFLAG_NOREALLOC
						| TJFLAG_FORCEMMX
						| TJFLAG_FORCESSE
						| TJFLAG_FORCESSE2
						| TJFLAG_FASTDCT
						);	//TJFLAG_FASTDCT);
	
		SetTimeSpan(tt1);
	
		/*
		static	bool	PSwotch=false;
		if(PSwotch==true){
			QFile	File("TestMJPG.jpg");
			File.open(QIODevice::WriteOnly);
			File.write((char *)CamData.Buffer,BuffSize);
		}
		*/
		if(n1==0 && n2==0){
			BYTE	*buffer = Cam->GetMJPegTmpBuff();
			JSAMPROW rowp = buffer;
	
			int	XByte3=width*3;
			if(MirrorX==false && MirrorY==false && RotationAngle==0){
				int	MinXLen=min(width,Buff[0]->GetWidth());
				int	MinYLen=min(height,Buff[0]->GetHeight());
				int	YN=MinYLen;	//&0xFFE0;
	
	#if defined(DecodeOpenMP)
				#pragma omp parallel                             
				{                                                
					#pragma omp for
	#endif
					for (int y = 0; y < YN; y++) {
						JSAMPROW row = &buffer[y*XByte3];
						//JSAMPROW row=rowp;
						//rowp+=XByte3;
	
						BYTE	*d0=Buff[0]->GetY(y);
						BYTE	*d1=Buff[1]->GetY(y);
						BYTE	*d2=Buff[2]->GetY(y);
						for (int x = 0; x < MinXLen; x++){
							*d0 = *(row  );
							*d1 = *(row+1);
							*d2 = *(row+2);
							row+=3;
							d0++;
							d1++;
							d2++;
						}
					}
	#if defined(DecodeOpenMP)
				}
	#endif
			}
			else
			if(MirrorX==false && MirrorY==false && RotationAngle==90){
				int	MinXLen=min(width,Buff[0]->GetHeight());
				int	MinYLen=min(height,Buff[0]->GetWidth());
				int	YN=MinYLen;	//&0xFFE0;
				if(Buff[0]->IsDepended()==true){
	
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							int	Y=YN-y-1;
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3;
							for (int x = 0; x < MinXLen; x++){
								BYTE	*d0=Buff[0]->GetY(x);
								BYTE	*d1=Buff[1]->GetY(x);
								BYTE	*d2=Buff[2]->GetY(x);
								d0[Y] = *(row  );
								d1[Y] = *(row+1);
								d2[Y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
				else{
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							int	Y=YN-y-1;
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3;
							for (int x = 0; x < MinXLen; x++){
								BYTE	*d0=Buff[0]->GetYWithoutDepended(x);
								BYTE	*d1=Buff[1]->GetYWithoutDepended(x);
								BYTE	*d2=Buff[2]->GetYWithoutDepended(x);
								d0[Y] = *(row  );
								d1[Y] = *(row+1);
								d2[Y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
			}
			else
			if(MirrorX==false && MirrorY==false && RotationAngle==180){
				int	MinXLen=min(width,Buff[0]->GetWidth());
				int	MinYLen=min(height,Buff[0]->GetHeight());
				int	YN=MinYLen;	//&0xFFE0;
	#if defined(DecodeOpenMP)
				#pragma omp parallel                             
				{                                                
					#pragma omp for
	#endif
					for (int y = 0; y < YN; y++) {
						JSAMPROW row = &buffer[y*XByte3];
						//JSAMPROW row=rowp;
						//rowp+=XByte3;
						BYTE	*d0=&Buff[0]->GetY(YN-y-1)[MinXLen-1];
						BYTE	*d1=&Buff[1]->GetY(YN-y-1)[MinXLen-1];
						BYTE	*d2=&Buff[2]->GetY(YN-y-1)[MinXLen-1];
						for (int x = 0; x < MinXLen; x++){
							*d0 = *(row  );
							*d1 = *(row+1);
							*d2 = *(row+2);
							row+=3;
							d0--;
							d1--;
							d2--;
						}
					}
	#if defined(DecodeOpenMP)
				}
	#endif
			}
			else
			if(MirrorX==false && MirrorY==false && RotationAngle==270){
				int	MinXLen=min(width,Buff[0]->GetHeight());
				int	MinYLen=min(height,Buff[0]->GetWidth());
				int	YN=MinYLen;	//&0xFFE0;
				if(Buff[0]->IsDepended()==true){
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3;
							int	X=MinXLen-1;
							for (int x = 0; x < MinXLen; x++,X--){
								BYTE	*d0=Buff[0]->GetY(X);
								BYTE	*d1=Buff[1]->GetY(X);
								BYTE	*d2=Buff[2]->GetY(X);
								d0[y] = *(row  );
								d1[y] = *(row+1);
								d2[y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
				else{
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3;
							int	X=MinXLen-1;
							for (int x = 0; x < MinXLen; x++,X--){
								BYTE	*d0=Buff[0]->GetYWithoutDepended(X);
								BYTE	*d1=Buff[1]->GetYWithoutDepended(X);
								BYTE	*d2=Buff[2]->GetYWithoutDepended(X);
								d0[y] = *(row  );
								d1[y] = *(row+1);
								d2[y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
			}
	
			else
			if(MirrorX==true && MirrorY==false && RotationAngle==0){
				int	MinXLen=min(width,Buff[0]->GetWidth());
				int	MinYLen=min(height,Buff[0]->GetHeight());
				int	YN=MinYLen;	//&0xFFE0;
	#if defined(DecodeOpenMP)
				#pragma omp parallel                             
				{                                                
					#pragma omp for
	#endif
					for (int y = 0; y < YN; y++) {
						JSAMPROW row = &buffer[y*XByte3];
						//JSAMPROW row=rowp;
						//rowp+=XByte3;
						BYTE	*d0=&Buff[0]->GetY(y)[MinXLen-1];
						BYTE	*d1=&Buff[1]->GetY(y)[MinXLen-1];
						BYTE	*d2=&Buff[2]->GetY(y)[MinXLen-1];
						for (int x = 0; x < MinXLen; x++){
							*d0 = *(row  );
							*d1 = *(row+1);
							*d2 = *(row+2);
							row+=3;
							d0--;
							d1--;
							d2--;
						}
					}
	#if defined(DecodeOpenMP)
				}
	#endif
			}
			else
			if(MirrorX==true && MirrorY==false && RotationAngle==90){
				int	MinXLen=min(width,Buff[0]->GetHeight());
				int	MinYLen=min(height,Buff[0]->GetWidth());
				int	YN=MinYLen;	//&0xFFE0;
				if(Buff[0]->IsDepended()==true){
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							int	Y=YN-y-1;
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3;
	
							int	X=MinXLen-1;
							for (int x = 0; x < MinXLen; x++,X--){
								BYTE	*d0=Buff[0]->GetY(X);
								BYTE	*d1=Buff[1]->GetY(X);
								BYTE	*d2=Buff[2]->GetY(X);
								d0[Y] = *(row  );
								d1[Y] = *(row+1);
								d2[Y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
				else{
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							int	Y=YN-y-1;
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3;
							int	X=MinXLen-1;
							for (int x = 0; x < MinXLen; x++,X--){
								BYTE	*d0=Buff[0]->GetYWithoutDepended(X);
								BYTE	*d1=Buff[1]->GetYWithoutDepended(X);
								BYTE	*d2=Buff[2]->GetYWithoutDepended(X);
								d0[Y] = *(row  );
								d1[Y] = *(row+1);
								d2[Y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
			}
			else
			if(MirrorX==true && MirrorY==false && RotationAngle==180){
				int	MinXLen=min(width,Buff[0]->GetWidth());
				int	MinYLen=min(height,Buff[0]->GetHeight());
				int	YN=MinYLen;	//&0xFFE0;
	#if defined(DecodeOpenMP)
				#pragma omp parallel                             
				{                                                
					#pragma omp for
	#endif
					for (int y = 0; y < YN; y++) {
						JSAMPROW row = &buffer[y*XByte3];
						//JSAMPROW row=rowp;
						//rowp+=XByte3;
						BYTE	*d0=Buff[0]->GetY(YN-y-1);
						BYTE	*d1=Buff[1]->GetY(YN-y-1);
						BYTE	*d2=Buff[2]->GetY(YN-y-1);
						for (int x = 0; x < MinXLen; x++){
							*d0 = *(row  );
							*d1 = *(row+1);
							*d2 = *(row+2);
							row+=3;
							d0++;
							d1++;
							d2++;
						}
					}
	#if defined(DecodeOpenMP)
				}
	#endif
			}
			else
			if(MirrorX==true && MirrorY==false && RotationAngle==270){
				int	MinXLen=min(width,Buff[0]->GetHeight());
				int	MinYLen=min(height,Buff[0]->GetWidth());
				int	YN=MinYLen;	//&0xFFE0;
				if(Buff[0]->IsDepended()==true){
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3;
							for (int x = 0; x < MinXLen; x++){
								BYTE	*d0=Buff[0]->GetY(x);
								BYTE	*d1=Buff[1]->GetY(x);
								BYTE	*d2=Buff[2]->GetY(x);
								d0[y] = *(row  );
								d1[y] = *(row+1);
								d2[y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
				else{
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3;
							for (int x = 0; x < MinXLen; x++){
								BYTE	*d0=Buff[0]->GetYWithoutDepended(x);
								BYTE	*d1=Buff[1]->GetYWithoutDepended(x);
								BYTE	*d2=Buff[2]->GetYWithoutDepended(x);
								d0[y] = *(row  );
								d1[y] = *(row+1);
								d2[y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
			}
	
			else
			if(MirrorX==false && MirrorY==true && RotationAngle==0){
				int	MinXLen=min(width,Buff[0]->GetWidth());
				int	MinYLen=min(height,Buff[0]->GetHeight());
				int	YN=MinYLen;	//&0xFFE0;
	#if defined(DecodeOpenMP)
				#pragma omp parallel                             
				{                                                
					#pragma omp for
	#endif
					for (int y = 0; y < YN; y++) {
						JSAMPROW row = &buffer[y*XByte3];
						//JSAMPROW row=rowp;
						//rowp+=XByte3;
						BYTE	*d0=Buff[0]->GetY(YN-y-1);
						BYTE	*d1=Buff[1]->GetY(YN-y-1);
						BYTE	*d2=Buff[2]->GetY(YN-y-1);
						for (int x = 0; x < MinXLen; x++){
							*d0 = *(row  );
							*d1 = *(row+1);
							*d2 = *(row+2);
							row+=3;
							d0++;
							d1++;
							d2++;
						}
					}
	#if defined(DecodeOpenMP)
				}
	#endif
			}
			else
			if(MirrorX==false && MirrorY==true && RotationAngle==90){
				int	MinXLen=min(width,Buff[0]->GetHeight());
				int	MinYLen=min(height,Buff[0]->GetWidth());
				int	YN=MinYLen;	//&0xFFE0;
				if(Buff[0]->IsDepended()==true){
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							//int	Y=YN-y-1;
							int	Y=y;
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3;
							int	X=0;
							for (int x = 0; x < MinXLen; x++,X++){
								BYTE	*d0=Buff[0]->GetY(X);
								BYTE	*d1=Buff[1]->GetY(X);
								BYTE	*d2=Buff[2]->GetY(X);
								d0[Y] = *(row  );
								d1[Y] = *(row+1);
								d2[Y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
				else{
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							//int	Y=YN-y-1;
							int	Y=y;
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3; 
							int	X=0;
							for (int x = 0; x < MinXLen; x++,X++){
								BYTE	*d0=Buff[0]->GetYWithoutDepended(X);
								BYTE	*d1=Buff[1]->GetYWithoutDepended(X);
								BYTE	*d2=Buff[2]->GetYWithoutDepended(X);
								d0[Y] = *(row  );
								d1[Y] = *(row+1);
								d2[Y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
			}
			else
			if(MirrorX==false && MirrorY==true && RotationAngle==180){
				int	MinXLen=min(width,Buff[0]->GetWidth());
				int	MinYLen=min(height,Buff[0]->GetHeight());
				int	YN=MinYLen;	//&0xFFE0;
	#if defined(DecodeOpenMP)
				#pragma omp parallel                             
				{                                                
					#pragma omp for
	#endif
					for (int y = 0; y < YN; y++) {
						JSAMPROW row = &buffer[y*XByte3];
						//JSAMPROW row=rowp;
						//rowp+=XByte3;
						BYTE	*d0=&Buff[0]->GetY(y)[MinXLen-1];
						BYTE	*d1=&Buff[1]->GetY(y)[MinXLen-1];
						BYTE	*d2=&Buff[2]->GetY(y)[MinXLen-1];
						for (int x = 0; x < MinXLen; x++){
							*d0 = *(row  );
							*d1 = *(row+1);
							*d2 = *(row+2);
							row+=3;
							d0--;
							d1--;
							d2--;
						}
					}
	#if defined(DecodeOpenMP)
				}
	#endif
			}
			else
			if(MirrorX==false && MirrorY==true && RotationAngle==270){
				int	MinXLen=min(width,Buff[0]->GetHeight());
				int	MinYLen=min(height,Buff[0]->GetWidth());
				int	YN=MinYLen;	//&0xFFE0;
				if(Buff[0]->IsDepended()==true){
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							int	Y=YN-y-1;
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3;
							int	X=MinXLen-1;
							for (int x = 0; x < MinXLen; x++,X--){
								BYTE	*d0=Buff[0]->GetY(X);
								BYTE	*d1=Buff[1]->GetY(X);
								BYTE	*d2=Buff[2]->GetY(X);
								d0[Y] = *(row  );
								d1[Y] = *(row+1);
								d2[Y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
				else{
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							int	Y=YN-y-1;
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3;
							int	X=MinXLen-1;
							for (int x = 0; x < MinXLen; x++,X--){
								BYTE	*d0=Buff[0]->GetYWithoutDepended(X);
								BYTE	*d1=Buff[1]->GetYWithoutDepended(X);
								BYTE	*d2=Buff[2]->GetYWithoutDepended(X);
								d0[Y] = *(row  );
								d1[Y] = *(row+1);
								d2[Y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
			}
	
			else
			if(MirrorX==true && MirrorY==true && RotationAngle==0){
				int	MinXLen=min(width,Buff[0]->GetWidth());
				int	MinYLen=min(height,Buff[0]->GetHeight());
				int	YN=MinYLen;	//&0xFFE0;
	#if defined(DecodeOpenMP)
				#pragma omp parallel                             
				{                                                
					#pragma omp for
	#endif
					for (int y = 0; y < YN; y++) {
						JSAMPROW row = &buffer[y*XByte3];
						//JSAMPROW row=rowp;
						//rowp+=XByte3;
						BYTE	*d0=&Buff[0]->GetY(YN-y-1)[MinXLen-1];
						BYTE	*d1=&Buff[1]->GetY(YN-y-1)[MinXLen-1];
						BYTE	*d2=&Buff[2]->GetY(YN-y-1)[MinXLen-1];
						for (int x = 0; x < MinXLen; x++){
							*d0 = *(row  );
							*d1 = *(row+1);
							*d2 = *(row+2);
							row+=3;
							d0--;
							d1--;
							d2--;
						}
					}
	#if defined(DecodeOpenMP)
				}
	#endif
			}
			else
			if(MirrorX==true && MirrorY==true && RotationAngle==90){
				int	MinXLen=min(width,Buff[0]->GetHeight());
				int	MinYLen=min(height,Buff[0]->GetWidth());
				int	YN=MinYLen;	//&0xFFE0;
				if(Buff[0]->IsDepended()==true){
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3;
							int	X=MinXLen-1;
							for (int x = 0; x < MinXLen; x++,X--){
								BYTE	*d0=Buff[0]->GetY(X);
								BYTE	*d1=Buff[1]->GetY(X);
								BYTE	*d2=Buff[2]->GetY(X);
								d0[y] = *(row  );
								d1[y] = *(row+1);
								d2[y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
				else{
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3;
							int	X=MinXLen-1;
							for (int x = 0; x < MinXLen; x++,X--){
								BYTE	*d0=Buff[0]->GetYWithoutDepended(X);
								BYTE	*d1=Buff[1]->GetYWithoutDepended(X);
								BYTE	*d2=Buff[2]->GetYWithoutDepended(X);
								d0[y] = *(row  );
								d1[y] = *(row+1);
								d2[y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
			}
			else
			if(MirrorX==true && MirrorY==true && RotationAngle==180){
				int	MinXLen=min(width,Buff[0]->GetWidth());
				int	MinYLen=min(height,Buff[0]->GetHeight());
				int	YN=MinYLen;	//&0xFFE0;
	#if defined(DecodeOpenMP)
				#pragma omp parallel                             
				{                                                
					#pragma omp for
	#endif
					for (int y = 0; y < YN; y++) {
						JSAMPROW row = &buffer[y*XByte3];
						//JSAMPROW row=rowp;
						//rowp+=XByte3;
						BYTE	*d0=Buff[0]->GetY(y);
						BYTE	*d1=Buff[1]->GetY(y);
						BYTE	*d2=Buff[2]->GetY(y);
						for (int x = 0; x < MinXLen; x++){
							*d0 = *(row  );
							*d1 = *(row+1);
							*d2 = *(row+2);
							row+=3;
							d0++;
							d1++;
							d2++;
						}
					}
	#if defined(DecodeOpenMP)
				}
	#endif
			}
			else
			if(MirrorX==true && MirrorY==true && RotationAngle==270){
				int	MinXLen=min(width,Buff[0]->GetHeight());
				int	MinYLen=min(height,Buff[0]->GetWidth());
				int	YN=MinYLen;	//&0xFFE0;
				if(Buff[0]->IsDepended()==true){
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							int	Y=YN-y-1;
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3;
							for (int x = 0; x < MinXLen; x++){
								BYTE	*d0=Buff[0]->GetY(x);
								BYTE	*d1=Buff[1]->GetY(x);
								BYTE	*d2=Buff[2]->GetY(x);
								d0[Y] = *(row  );
								d1[Y] = *(row+1);
								d2[Y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
				else{
	#if defined(DecodeOpenMP)
					#pragma omp parallel                             
					{                                                
						#pragma omp for
	#endif
						for (int y = 0; y < YN; y++) {
							int	Y=YN-y-1;
							JSAMPROW row = &buffer[y*XByte3];
							//JSAMPROW row=rowp;
							//rowp+=XByte3;
							for (int x = 0; x < MinXLen; x++){
								BYTE	*d0=Buff[0]->GetYWithoutDepended(x);
								BYTE	*d1=Buff[1]->GetYWithoutDepended(x);
								BYTE	*d2=Buff[2]->GetYWithoutDepended(x);
								d0[Y] = *(row  );
								d1[Y] = *(row+1);
								d2[Y] = *(row+2);
								row+=3;
							}
						}
	#if defined(DecodeOpenMP)
					}
	#endif
				}
			}
		}
	}
}
