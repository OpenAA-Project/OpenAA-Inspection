#include "CameraUSBStandard.h"
#include "XGeneralFunc.h"
#include "XDLLType.h"
#include "XCameraDLL.h"
#include "XMainSchemeMemory.h"
#include "swap.h"
#define JPEG_INTERNALS
#include "jinclude.h"
#include "jpeglib.h"

void	MakeMJPeg(USBStandardData &CamData,long BuffSize ,int Xn ,int Yn ,ImageBuffer *Buff[]
				,bool MirrorX ,bool MirrorY
				,int RotationAngle)
{
	jpeg_mem_src(&CamData.jpegd, CamData.Buffer,BuffSize);

	/*
	static	bool	PSwotch=false;
	if(PSwotch==true){
		QFile	File("TestMJPG.jpg");
		File.open(QIODevice::WriteOnly);
		File.write((char *)CamData.Buffer,BuffSize);
	}
	*/

	if (jpeg_read_header(&CamData.jpegd, TRUE) == JPEG_HEADER_OK) {
		if(jpeg_start_decompress(&CamData.jpegd)==true){
			if (CamData.jpegd.out_color_space == JCS_RGB) {
				//int stride = sizeof(JSAMPLE) * CamData.jpegd.output_width * CamData.jpegd.output_components;
				BYTE	*buffer = CamData.MJPegTmpBuff;
							
				//jpeg_read_scanlines(&CamData.jpegd, &buffer, YN);
				int	Xp=0;
				int	XByte3=CamData.jpegd.output_width*3;
				for (int y = 0; y < CamData.jpegd.output_height; y++) {
					BYTE	*B=&buffer[Xp];
					jpeg_read_scanlines(&CamData.jpegd, &B, 1);
					Xp+=XByte3;
				}

				if(MirrorX==false && MirrorY==false && RotationAngle==0){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetWidth());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetHeight());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];

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
					}
				}
				else
				if(MirrorX==false && MirrorY==false && RotationAngle==90){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetHeight());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetWidth());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];
							for (int x = 0; x < MinXLen; x++){
								BYTE	*d0=Buff[0]->GetY(x);
								BYTE	*d1=Buff[1]->GetY(x);
								BYTE	*d2=Buff[2]->GetY(x);
								d0[YN-y-1] = *(row  );
								d1[YN-y-1] = *(row+1);
								d2[YN-y-1] = *(row+2);
								row+=3;
							}
						}
					}
				}
				else
				if(MirrorX==false && MirrorY==false && RotationAngle==180){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetWidth());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetHeight());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];

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
					}
				}
				else
				if(MirrorX==false && MirrorY==false && RotationAngle==270){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetHeight());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetWidth());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];
							for (int x = 0; x < MinXLen; x++){
								BYTE	*d0=Buff[0]->GetY(MinXLen-x-1);
								BYTE	*d1=Buff[1]->GetY(MinXLen-x-1);
								BYTE	*d2=Buff[2]->GetY(MinXLen-x-1);
								d0[y] = *(row  );
								d1[y] = *(row+1);
								d2[y] = *(row+2);
								row+=3;
							}
						}
					}
				}

				else
				if(MirrorX==true && MirrorY==false && RotationAngle==0){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetWidth());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetHeight());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];

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
					}
				}
				else
				if(MirrorX==true && MirrorY==false && RotationAngle==90){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetHeight());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetWidth());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];
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
					}
				}
				else
				if(MirrorX==true && MirrorY==false && RotationAngle==180){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetWidth());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetHeight());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];

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
					}
				}
				else
				if(MirrorX==true && MirrorY==false && RotationAngle==270){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetHeight());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetWidth());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];
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
					}
				}

				else
				if(MirrorX==false && MirrorY==true && RotationAngle==0){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetWidth());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetHeight());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];

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
					}
				}
				else
				if(MirrorX==false && MirrorY==true && RotationAngle==90){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetHeight());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetWidth());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];
							for (int x = 0; x < MinXLen; x++){
								BYTE	*d0=Buff[0]->GetY(MinXLen-x-1);
								BYTE	*d1=Buff[1]->GetY(MinXLen-x-1);
								BYTE	*d2=Buff[2]->GetY(MinXLen-x-1);
								d0[YN-y-1] = *(row  );
								d1[YN-y-1] = *(row+1);
								d2[YN-y-1] = *(row+2);
								row+=3;
							}
						}
					}
				}
				else
				if(MirrorX==false && MirrorY==true && RotationAngle==180){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetWidth());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetHeight());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];

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
					}
				}
				else
				if(MirrorX==false && MirrorY==true && RotationAngle==270){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetHeight());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetWidth());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];
							for (int x = 0; x < MinXLen; x++){
								BYTE	*d0=Buff[0]->GetY(MinXLen-x-1);
								BYTE	*d1=Buff[1]->GetY(MinXLen-x-1);
								BYTE	*d2=Buff[2]->GetY(MinXLen-x-1);
								d0[YN-y-1] = *(row  );
								d1[YN-y-1] = *(row+1);
								d2[YN-y-1] = *(row+2);
								row+=3;
							}
						}
					}
				}

				else
				if(MirrorX==true && MirrorY==true && RotationAngle==0){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetWidth());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetHeight());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];

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
					}
				}
				else
				if(MirrorX==true && MirrorY==true && RotationAngle==90){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetHeight());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetWidth());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];
							for (int x = 0; x < MinXLen; x++){
								BYTE	*d0=Buff[0]->GetY(MinXLen-x-1);
								BYTE	*d1=Buff[1]->GetY(MinXLen-x-1);
								BYTE	*d2=Buff[2]->GetY(MinXLen-x-1);
								d0[y] = *(row  );
								d1[y] = *(row+1);
								d2[y] = *(row+2);
								row+=3;
							}
						}
					}
				}
				else
				if(MirrorX==true && MirrorY==true && RotationAngle==180){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetWidth());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetHeight());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];

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
					}
				}
				else
				if(MirrorX==true && MirrorY==true && RotationAngle==270){
					int	MinXLen=min((int)CamData.jpegd.output_width,Buff[0]->GetHeight());
					int	MinYLen=min((int)CamData.jpegd.output_height,Buff[0]->GetWidth());
					int	YN=MinYLen&0xFFE0;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for (int y = 0; y < YN; y++) {
							JSAMPROW row = &buffer[y*XByte3];
							for (int x = 0; x < MinXLen; x++){
								BYTE	*d0=Buff[0]->GetY(x);
								BYTE	*d1=Buff[1]->GetY(x);
								BYTE	*d2=Buff[2]->GetY(x);
								d0[YN-y-1] = *(row  );
								d1[YN-y-1] = *(row+1);
								d2[YN-y-1] = *(row+2);
								row+=3;
							}
						}
					}
				}				//for(int y=YN;y<CamData.jpegd.output_height;y++){
				//	jpeg_read_scanlines(&CamData.jpegd, &buffer, 1);
				//}
			}
			jpeg_finish_decompress(&CamData.jpegd);
		}
	}
}


