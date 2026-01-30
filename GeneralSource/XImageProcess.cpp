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


#include "XTypeDef.h"
#include "XImageProcess.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XDot.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "swap.h"
#include <omp.h>


/*
	BYTE�^�ϐ�mXX�̔z�u

	����   �E��
	m11 m12 m13
	m21 m22 m23
	m31 m32 m33
	����   �E��
*/

void	ProcessEdgeWithBinary(BYTE **bmpdata, BYTE **bitoperation,
                              int xbyte, int XLenDot, int YLenDot,
                              BYTE DUMMY_BINARY_DATA,	//�[�����������ۂ�8�ߖT���������悤�Ƃ����֐�func�Ƀ_�~�[�Ƃ��ēn���e�����^���Ȃ�BYTE�^�ϐ�
                              void (* func)(BYTE &destm22, BYTE &m11, BYTE &m12, BYTE &m13, BYTE &m21, BYTE &m22, BYTE &m23, BYTE &m31, BYTE &m32, BYTE &m33))
{
	BYTE	_m11, _m12, _m13, _m21, _m23, _m31, _m32, _m33;
	_m11=_m12=_m13=_m21=_m23=_m31=_m32=_m33 = DUMMY_BINARY_DATA;

	const int bottom = YLenDot-1;
	const int left = xbyte-1;

	//�p���������[������

	//���[������
	{
		BYTE	*p2=  &bmpdata[0][1];
		BYTE	*p1=  &bitoperation[0][1];
		BYTE	*p1p= &bitoperation[1][1];
		for(int x=8;x<XLenDot-8;x+=8,p2++,p1++,p1p++){
			if((*p1)==0)
				continue;
			(*func)(*(p2), _m11, _m21, _m31, *(p1-1), *(p1), *(p1+1), *(p1p-1), *(p1p), *(p1p+1));
		}
	}
	//���[������
	{
		BYTE	*p2=  &bmpdata[bottom][1];
		BYTE	*p1=  &bitoperation[bottom][1];
		BYTE	*p1m= &bitoperation[bottom-1][1];
		for(int x=8;x<XLenDot-8;x+=8,p2++,p1++,p1m++){
			if((*p1)==0)
				continue;
			(*func)(*(p2), *(p1m-1), *(p1m), *(p1m+1), *(p1-1), *(p1), *(p1+1), _m31, _m32, _m33);
		}
	}
	//���[������
	{
		for(int y=1;y<YLenDot-1;y++){
			BYTE	*p1=  &bitoperation[y][0];
			BYTE	*p2=  &bmpdata[y][0];
			BYTE	*p1p= &bitoperation[y+1][0];
			BYTE	*p1m= &bitoperation[y-1][0];
//			if((*p2)==0)
//				continue;
			(*func)(*(p2), _m11, *(p1m), *(p1m+1), _m21, *(p1), *(p1+1), _m31, *(p1p), *(p1p+1));
		}
	}
	//�E�[������
	{
		for(int y=1;y<YLenDot-1;y++){
			BYTE	*p2=  &bmpdata[y][left];
			BYTE	*p1m= &bitoperation[y-1][left];
			BYTE	*p1=  &bitoperation[y][left];
			BYTE	*p1p= &bitoperation[y+1][left];
//			if((*p2)==0)
//				continue;
			(*func)(*(p2), *(p1m-1), *(p1m), _m13, *(p1-1), *(p1), _m23, *(p1p-1), *(p1p), _m33);
		}
	}

	//�p������
	{
		BYTE	*p1, *p2, *p1p, *p1m;
		//����
		p2=  &bmpdata[0][0];
		p1=  &bitoperation[0][0];
		p1p= &bitoperation[1][0];
		(*func)(*(p2), _m11, _m12, _m13, _m21, *(p1), *(p1+1), _m31, *(p1p), _m33);
		//�E��
		p2=  &bmpdata[0][left];
		p1=  &bitoperation[0][left];
		p1p= &bitoperation[1][left];
		(*func)(*(p2), _m11, _m12, _m13, *(p1-1), *(p1), _m23, _m31, *(p1p), _m33);
		//����
		p2=  &bmpdata[bottom][0];
		p1=  &bitoperation[bottom][0];
		p1m= &bitoperation[bottom-1][0];
		(*func)(*(p2), _m11, *(p1m), _m13, _m21, *(p1), *(p1+1), _m31, _m32, _m33);
		//�E��
		p2=  &bmpdata[bottom][left];
		p1=  &bitoperation[bottom][left];
		p1m= &bitoperation[bottom-1][left];
		(*func)(*(p2), _m11, *(p1m), _m13, *(p1-1), *(p1), _m23, _m31, _m32, _m33);
	}
}

/*

FatArea Function Specification

	* [�T�v] ���l�����ꂽ�摜�f�[�^�̓񎟌��z��bmpdata��1�h�b�g�c���������B
	* [�ڍ�] �c���̃A���S���Y��
	         �����r�b�g�ɂ��āA8�ߖT��1��1�ȏ゠���Ύ��g��1�ɁA���̑���0�ɂ���

ex)
		100      100
		000  ->  110
		000      000		�����i�̃r�b�g�̂ݏ���

arguments)

	BYTE **bmpdata     	���l�����ꂽ�摜�f�[�^�̓������񎟌��z���A[y][x]�̏��Ɋi�[�����Ă���
	                   	����1�o�C�g���ŏ��ʃr�b�g���摜�ł̉E�[�A�ŉ��ʂ͍��[�ɂ�����
	BYTE **bitoperation	�����p�Ɉꎞ�I�Ɋm�ۂ����񎟌��z��
	                   	NULL��������xbyte�~YLenDot�̑傫���̓񎟌��z��
	
	int xbyte          	bmpdata��(�摜�̕�+1+7)>>3�ABYTE�^�̓��i���̓񎟌��z���ɂ����ɂ������ĕK�v�ȉ���
	int YLenDot        	bmpdata�̏c�̒���

	FlexArea ForceZone	�s��

*/

void    FatArea(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte, int YLenDot ,FlexArea *ForceZone
				,bool EnableThread)
{
	int	XLenDot=xbyte*8;
	bool	Allocbitoperation=false;
	if(bitoperation==NULL){
		bitoperation=MakeMatrixBuff(xbyte,YLenDot);
		Allocbitoperation=true;
	}

	MatrixBuffCopy(bitoperation				,xbyte ,YLenDot
                  ,(const BYTE **)bmpdata	,xbyte ,YLenDot);

    if(ForceZone==NULL){
		if(XLenDot<64 || YLenDot<32 || EnableThread==false){
			for(int y=1;y<YLenDot-1;y++){
				BYTE	*p2=  &bmpdata[y][1];
				BYTE	*p1=  &bitoperation[y][1];
				BYTE	*p1p= &bitoperation[y+1][1];
				BYTE	*p1m= &bitoperation[y-1][1];
				for(int x=8;x<XLenDot-8;x+=8,p2++,p1++,p1p++,p1m++){
					uchar   m22;
					if((m22= *p1)==0xFF){
						continue;
					}
					BYTE	m11= *(p1m-1);
					BYTE	m12= *(p1m);
					BYTE	m13= *(p1m+1);
					BYTE	m21= *(p1-1);
					BYTE	m23= *(p1+1);
					BYTE	m31= *(p1p-1);
					BYTE	m32= *(p1p);
					BYTE	m33= *(p1p+1);

					if(m22==0
					&& m11==0
					&& m12==0
					&& m13==0
					&& m21==0
					&& m23==0
					&& m31==0
					&& m32==0
					&& m33==0)
						continue;
		
					BYTE    r=m12 | m32;
					BYTE    t=m22 | r;

					*p2 |=  ((r)
						| ((m21 | m11 | m31)<<7)
						| ((t)<<1)) & (~m22) &0x80;

					*p2 |= (r
						| (t>>1)
						| (t<<1)) & 0x7E;

					*p2 |= ((r)
						| ((m23 | m13 | m33)>>7)
						| ((t)>>1))&(~m22) &0x01;
				}
			}
		}
		else{
			#pragma omp parallel
			{
				#pragma omp for
				for(int y=1;y<YLenDot-1;y++){
					BYTE	*p2=  &bmpdata[y][1];
					BYTE	*p1=  &bitoperation[y][1];
					BYTE	*p1p= &bitoperation[y+1][1];
					BYTE	*p1m= &bitoperation[y-1][1];
					for(int x=8;x<XLenDot-8;x+=8,p2++,p1++,p1p++,p1m++){
						uchar   m22;
						if((m22= *p1)==0xFF){
							continue;
						}
						BYTE	m11= *(p1m-1);
						BYTE	m12= *(p1m);
						BYTE	m13= *(p1m+1);
						BYTE	m21= *(p1-1);
						BYTE	m23= *(p1+1);
						BYTE	m31= *(p1p-1);
						BYTE	m32= *(p1p);
						BYTE	m33= *(p1p+1);

					    if(m22==0
						&& m11==0
					    && m12==0
						&& m13==0
					    && m21==0
						&& m23==0
						&& m31==0
						&& m32==0
						&& m33==0){
							continue;
						}
		
						BYTE    r=m12 | m32;
						BYTE    t=m22 | r;

						*p2 |=  ((r)
							| ((m21 | m11 | m31)<<7)
							| ((t)<<1)) & (~m22) &0x80;

						*p2 |= (r
							| (t>>1)
							| (t<<1)) & 0x7E;

						*p2 |= ((r)
							| ((m23 | m13 | m33)>>7)
							| ((t)>>1))&(~m22) &0x01;
					}
				}
			}
        }
	}
    else{
        int BXLenDot=(xbyte<<3)+7;
		int	Len=ForceZone->GetFLineLen();
		if(EnableThread==false){
	        for(int i=0;i<Len;i++){
			    int y=ForceZone->GetFLineAbsY(i);
			    if((y<1) || (y>=YLenDot-2)){
				    continue;
				}
	            int x1=ForceZone->GetFLineLeftX(i);
			    int x2=ForceZone->GetFLineRightX(i);

			    if(x1<8){
				    x1=8;
				}
	            if(x2>=(BXLenDot-9)){
			        x2=BXLenDot-9;
				}
			    if((x2<0) || (x1>(BXLenDot-9))){
				    continue;
				}

	            int xoff=x1/8;
			    BYTE	*p2=  &bmpdata[y][xoff];
			    BYTE	*p1=  &bitoperation[y][xoff];
				BYTE	*p1p= &bitoperation[y+1][xoff];
	            BYTE	*p1m= &bitoperation[y-1][xoff];
			    for(int x=(xoff<<3);x<=x2 && x<BXLenDot-8
			    ;x+=8,p2++,p1++,p1p++,p1m++){
				    BYTE	m22;
					if((m22= *p1)==0xFF)
						continue;
	                BYTE	m11= *(p1m-1);
			        BYTE	m12= *(p1m);
			        BYTE	m13= *(p1m+1);
				    BYTE	m21= *(p1-1);
					BYTE	m23= *(p1+1);
	                BYTE	m31= *(p1p-1);
			        BYTE	m32= *(p1p);
			        BYTE	m33= *(p1p+1);

				    if(m22==0
					&& m11==0
	                && m12==0
			        && m13==0
			        && m21==0
				    && m23==0
					&& m31==0
	                && m32==0
			        && m33==0)
			            continue;
	
			        BYTE    r=m12 | m32;
			        BYTE    t=m22 | r;
			
			        *p2 |=  ((r)
                      | ((m21 | m11 | m31)<<7)
                      | ((t)<<1)) & (~m22) &0x80;

	                *p2 |= (r
                      | (t>>1)
                      | (t<<1)) & 0x7E;
	
			        *p2 |= ((r)
                     | ((m23 | m13 | m33)>>7)
                     | ((t)>>1))&(~m22) &0x01;
				}
            }
        }
		else{
			#pragma omp parallel                             
			{                                                
				#pragma omp for
	            for(int i=0;i<Len;i++){
			        int y=ForceZone->GetFLineAbsY(i);
				    if(y<1 || y>=YLenDot-2)
					    continue;
	                int x1=ForceZone->GetFLineLeftX(i);
			        int x2=ForceZone->GetFLineRightX(i);

				    if(x1<8){
					    x1=8;
					}
	                if(x2>=(BXLenDot-9)){
			            x2=BXLenDot-9;
					}
				    if((x2<0) || (x1>(BXLenDot-9))){
					    continue;
					}

	                int xoff=x1/8;
			        BYTE	*p2=  &bmpdata[y][xoff];
				    BYTE	*p1=  &bitoperation[y][xoff];
					BYTE	*p1p= &bitoperation[y+1][xoff];
	                BYTE	*p1m= &bitoperation[y-1][xoff];
			        for(int x=(xoff<<3);x<=x2 && x<BXLenDot-8
				    ;x+=8,p2++,p1++,p1p++,p1m++){
					    BYTE	m22;
						if((m22= *p1)==0xFF)
							continue;
	                    BYTE	m11= *(p1m-1);
			            BYTE	m12= *(p1m);
				        BYTE	m13= *(p1m+1);
					    BYTE	m21= *(p1-1);
						BYTE	m23= *(p1+1);
	                    BYTE	m31= *(p1p-1);
			            BYTE	m32= *(p1p);
				        BYTE	m33= *(p1p+1);

					    if(m22==0
						&& m11==0
	                    && m12==0
			            && m13==0
				        && m21==0
					    && m23==0
						&& m31==0
	                    && m32==0
			            && m33==0)
				            continue;
	
			            BYTE    r=m12 | m32;
				        BYTE    t=m22 | r;
			
				        *p2 |=  ((r)
                          | ((m21 | m11 | m31)<<7)
                          | ((t)<<1)) & (~m22) &0x80;

	                    *p2 |= (r
                          | (t>>1)
                          | (t<<1)) & 0x7E;
	
			            *p2 |= ((r)
                         | ((m23 | m13 | m33)>>7)
                         | ((t)>>1))&(~m22) &0x01;
					}
                }
            }
		}
    }
	if(Allocbitoperation==true){
		DeleteMatrixBuff(bitoperation,YLenDot);
		bitoperation=NULL;
	}
}

void    FatAreaN(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte, int YLenDot 
				,int Numb
				,FlexArea *ForceZone
				,bool EnableThread)
{
	for(int i=0;i<Numb;i++){
		FatArea(bmpdata
				,bitoperation
				,xbyte, YLenDot 
				,ForceZone
				,EnableThread);
	}
}

void    ThinAreaN(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,FlexArea *ForceZone
				,bool EnableThread)
{
	for(int i=0;i<Numb;i++){
		ThinArea(bmpdata
				,bitoperation
				,xbyte, YLenDot 
				,ForceZone
				,EnableThread);
	}
}

inline void	ErodeBinaryData(BYTE &destm22, BYTE &m11, BYTE &m12, BYTE &m13, BYTE &m21, BYTE &m22, BYTE &m23, BYTE &m31, BYTE &m32, BYTE &m33)
{
    if(m22==0xFF
	&& m11==0xFF
    && m12==0xFF
	&& m13==0xFF
    && m21==0xFF
    && m23==0xFF
	&& m31==0xFF
	&& m32==0xFF
	&& m33==0xFF){
		return;
	}

	destm22 = (m21&m22&m23)&
		(((m22<<1)&(m22>>1))
		|(((m11&m21&m31)>>7)&(m22<<1))
		|(((m13&m23&m33)<<7)&(m22>>1))
		);
}

inline void	ErodeBinaryDataInACrossShape(BYTE &destm22, BYTE &m11, BYTE &m12, BYTE &m13, BYTE &m21, BYTE &m22, BYTE &m23, BYTE &m31, BYTE &m32, BYTE &m33)
{
	if(m22==0)
		return;

	if(m22==0xFF
	   && m12==0xFF
	   && m21==0xFF
	   && m23==0xFF
	   && m32==0xFF
	   ){
		return;
	}

	destm22 = (m12&m22&m32)&(((m22<<1)&(m22>>1))|((m21>>7)&(m22>>1))|((m23<<7)&(m22<<1)));
}

void    ThinArea(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot ,FlexArea *ForceZone
				,bool EnableThread)
{
	bool	Allocbitoperation=false;
	if(bitoperation==NULL){
		bitoperation=MakeMatrixBuff(xbyte,YLenDot);
		Allocbitoperation=true;
	}

    MatrixBuffCopy(bitoperation				,xbyte,YLenDot
                  ,(const BYTE **)bmpdata	,xbyte,YLenDot);

    
    
    if(ForceZone==NULL){
		if(xbyte<64 || YLenDot<32 || EnableThread==false){
			for(int y=1;y<YLenDot-2;y++){
				BYTE	*p2=  &bmpdata[y][1];
				BYTE	*p1=  &bitoperation[y][1];
				BYTE	*p1p= &bitoperation[y+1][1];
				BYTE	*p1m= &bitoperation[y-1][1];
				//for(int x=8;x<XLenDot-9;x+=8,p2++,p1++,p1p++,p1m++){
				for(int x=1;x<xbyte-1;x++,p2++,p1++,p1p++,p1m++){
					uchar   m22;
					if((m22= *p1)==0){
						continue;
					}

					BYTE	m11= *(p1m-1);
					BYTE	m12= *(p1m);
					BYTE	m13= *(p1m+1);
					BYTE	m21= *(p1-1);
					BYTE	m23= *(p1+1);
					BYTE	m31= *(p1p-1);
					BYTE	m32= *(p1p);
					BYTE	m33= *(p1p+1);

					if(m22==0xFF
					&& m11==0xFF
					&& m12==0xFF
					&& m13==0xFF
					&& m21==0xFF
					&& m23==0xFF
					&& m31==0xFF
					&& m32==0xFF
					&& m33==0xFF){
						continue;
					}

					BYTE    r=m12 & m32;
					BYTE    t=m22 & r;
					*p2 = *p2 & ((r
							& ((m21 & m11 & m31)<<7)
							& ((t)<<1)) | 0x7F);


					*p2 &= 0x81 |( r
								& (t>>1)
								& (t<<1) );

					*p2 = *p2 & ((r
							& ((m23 & m13 & m33)>>7)
							& ((t)>>1)) | 0xFE);
				}
			}
		}
		else{
			#pragma omp parallel
			{
				#pragma omp for
			    for(int y=1;y<YLenDot-2;y++){
				    BYTE	*p2=  &bmpdata[y][1];
					BYTE	*p1=  &bitoperation[y][1];
					BYTE	*p1p= &bitoperation[y+1][1];
					BYTE	*p1m= &bitoperation[y-1][1];
					//for(int x=8;x<XLenDot-9;x+=8,p2++,p1++,p1p++,p1m++){
					for(int x=1;x<xbyte-1;x++,p2++,p1++,p1p++,p1m++){
						uchar   m22;
						if((m22= *p1)==0){
							continue;
						}

						BYTE	m11= *(p1m-1);
						BYTE	m12= *(p1m);
						BYTE	m13= *(p1m+1);
						BYTE	m21= *(p1-1);
						BYTE	m23= *(p1+1);
						BYTE	m31= *(p1p-1);
						BYTE	m32= *(p1p);
						BYTE	m33= *(p1p+1);

						if(m22==0xFF
						&& m11==0xFF
						&& m12==0xFF
						&& m13==0xFF
						&& m21==0xFF
						&& m23==0xFF
						&& m31==0xFF
						&& m32==0xFF
						&& m33==0xFF){
							continue;
						}

						BYTE    r=m12 & m32;
						BYTE    t=m22 & r;
						*p2 = *p2 & ((r
								& ((m21 & m11 & m31)<<7)
								& ((t)<<1)) | 0x7F);


						*p2 &= 0x81 |( r
									& (t>>1)
									& (t<<1) );

						*p2 = *p2 & ((r
								& ((m23 & m13 & m33)>>7)
								& ((t)>>1)) | 0xFE);
					}
				}
            }
        }
	    memset(bmpdata[0],0,xbyte);
		memset(bmpdata[YLenDot-1],0,xbyte);

		if(xbyte>=3){
			for(int y=1;y<YLenDot-2;y++){
				bmpdata[y][0] &= 0x7f;
				bmpdata[y][xbyte-1] &= 0xfe;

				if((bitoperation[y  ][0]&0xe0)!=0xe0
				|| (bitoperation[y-1][0]&0xe0)!=0xe0
				|| (bitoperation[y+1][0]&0xe0)!=0xe0)
					bmpdata[y][0] &= 0xbf;
				if((bitoperation[y  ][0]&0x70)!=0x70
				|| (bitoperation[y-1][0]&0x70)!=0x70
				|| (bitoperation[y+1][0]&0x70)!=0x70)
					bmpdata[y][0] &= 0xdf;
				if((bitoperation[y  ][0]&0x38)!=0x38
				|| (bitoperation[y-1][0]&0x38)!=0x38
				|| (bitoperation[y+1][0]&0x38)!=0x38)
					bmpdata[y][0] &= 0xef;
				if((bitoperation[y  ][0]&0x1c)!=0x1c
				|| (bitoperation[y-1][0]&0x1c)!=0x1c
				|| (bitoperation[y+1][0]&0x1c)!=0x1c)
					bmpdata[y][0] &= 0xf8;
				if((bitoperation[y  ][0]&0x0e)!=0x0e
				|| (bitoperation[y-1][0]&0x0e)!=0x0e
				|| (bitoperation[y+1][0]&0x0e)!=0x0e)
					bmpdata[y][0] &= 0xfb;
				if((bitoperation[y  ][0]&0x07)!=0x07
				|| (bitoperation[y-1][0]&0x07)!=0x07
				|| (bitoperation[y+1][0]&0x07)!=0x07)
					bmpdata[y][0] &= 0xfd;
				if((bitoperation[y  ][0]&0x03)!=0x03 || (bitoperation[y  ][1]&0x80)!=0x80
				|| (bitoperation[y-1][0]&0x03)!=0x03 || (bitoperation[y-1][1]&0x80)!=0x80
				|| (bitoperation[y+1][0]&0x03)!=0x03 || (bitoperation[y+1][1]&0x80)!=0x80)
					bmpdata[y][0] &= 0xfe;

				if((bitoperation[y  ][xbyte-1]&0x07)!=0x07
				|| (bitoperation[y-1][xbyte-1]&0x07)!=0x07
				|| (bitoperation[y+1][xbyte-1]&0x07)!=0x07)
					bmpdata[y][xbyte-1] &= 0xfd;
				if((bitoperation[y  ][xbyte-1]&0x0e)!=0x0e
				|| (bitoperation[y-1][xbyte-1]&0x0e)!=0x0e
				|| (bitoperation[y+1][xbyte-1]&0x0e)!=0x0e)
					bmpdata[y][xbyte-1] &= 0xfb;
				if((bitoperation[y  ][xbyte-1]&0x1c)!=0x1c
				|| (bitoperation[y-1][xbyte-1]&0x1c)!=0x1c
				|| (bitoperation[y+1][xbyte-1]&0x1c)!=0x1c)
					bmpdata[y][xbyte-1] &= 0xf7;
				if((bitoperation[y  ][xbyte-1]&0x38)!=0x38
				|| (bitoperation[y-1][xbyte-1]&0x38)!=0x38
				|| (bitoperation[y+1][xbyte-1]&0x38)!=0x38)
					bmpdata[y][xbyte-1] &= 0xef;
				if((bitoperation[y  ][xbyte-1]&0x70)!=0x70
				|| (bitoperation[y-1][xbyte-1]&0x70)!=0x70
				|| (bitoperation[y+1][xbyte-1]&0x70)!=0x70)
					bmpdata[y][xbyte-1] &= 0xdf;
				if((bitoperation[y  ][xbyte-1]&0xe0)!=0xe0
				|| (bitoperation[y-1][xbyte-1]&0xe0)!=0xe0
				|| (bitoperation[y+1][xbyte-1]&0xe0)!=0xe0)
					bmpdata[y][xbyte-1] &= 0xbf;
				if((bitoperation[y  ][xbyte-1]&0xc0)!=0xc0 || (bitoperation[y  ][xbyte-2]&0x01)!=0x01
				|| (bitoperation[y-1][xbyte-1]&0xc0)!=0xc0 || (bitoperation[y-1][xbyte-2]&0x01)!=0x01
				|| (bitoperation[y+1][xbyte-1]&0xc0)!=0xc0 || (bitoperation[y+1][xbyte-2]&0x01)!=0x01)
					bmpdata[y][xbyte-1] &= 0x7f;
			}
		}
    }
    else{
        int XLenDot=(xbyte<<3)+7;
		int	Len=ForceZone->GetFLineLen();
		if(EnableThread==false){
			for(int i=0;i<Len;i++){
		        int y=ForceZone->GetFLineAbsY(i);
				if(y<1 || y>=YLenDot-2){
				    continue;
				}
	            int x1=ForceZone->GetFLineLeftX(i);
		        int x2=ForceZone->GetFLineRightX(i);

				if(x1<8){
				    x1=8;
				}
				if(x2>=(XLenDot-9)){
		            x2=XLenDot-9;
				}
				if(x2<0 || (x1>XLenDot-9)){
				    continue;
				}

	            int xoff=x1/8;
		        BYTE	*p2=  &bmpdata[y][xoff];
			    BYTE	*p1=  &bitoperation[y][xoff];
				BYTE	*p1p= &bitoperation[y+1][xoff];
	            BYTE	*p1m= &bitoperation[y-1][xoff];
		        for(int x=(xoff<<3);x<=x2 && x<XLenDot-9
			    ;x+=8,p2++,p1++,p1p++,p1m++){
				    uchar   m22;
					if((m22= *p1)==0){
						continue;
					}

	                BYTE	m11= *(p1m-1);
		            BYTE	m12= *(p1m);
			        BYTE	m13= *(p1m+1);
				    BYTE	m21= *(p1-1);
					BYTE	m23= *(p1+1);
	                BYTE	m31= *(p1p-1);
		            BYTE	m32= *(p1p);
			        BYTE	m33= *(p1p+1);

				    if(m22==0xFF
					&& m11==0xFF
	                && m12==0xFF
		            && m13==0xFF
			        && m21==0xFF
				    && m23==0xFF
					&& m31==0xFF
	                && m32==0xFF
					&& m33==0xFF){
			            continue;
					}

				    BYTE    r=m12 & m32;
					BYTE    t=m22 & r;
	                *p2 = *p2 & ((r
		                      & ((m21 & m11 & m31)<<7)
			                  & ((t)<<1)) | 0x7F);


				    *p2 &= 0x81 |( r
					             & (t>>1)
						         & (t<<1) );

	                *p2 = *p2 & ((r
		                      & ((m23 & m13 & m33)>>7)
			                  & ((t)>>1)) | 0xFE);

				}
			}
		}
		else{
			#pragma omp parallel                             
			{                                                
				#pragma omp for
	            for(int i=0;i<Len;i++){
			        int y=ForceZone->GetFLineAbsY(i);
					if(y<1 || y>=YLenDot-2){
					    continue;
					}
	                int x1=ForceZone->GetFLineLeftX(i);
			        int x2=ForceZone->GetFLineRightX(i);

					if(x1<8){
					    x1=8;
					}
					if(x2>=XLenDot-9){
			            x2=XLenDot-9;
					}
					if(x2<0 || x1>XLenDot-9){
					    continue;
					}

	                int xoff=x1/8;
			        BYTE	*p2=  &bmpdata[y][xoff];
				    BYTE	*p1=  &bitoperation[y][xoff];
					BYTE	*p1p= &bitoperation[y+1][xoff];
	                BYTE	*p1m= &bitoperation[y-1][xoff];
			        for(int x=(xoff<<3);x<=x2 && x<XLenDot-9
				    ;x+=8,p2++,p1++,p1p++,p1m++){
					    uchar   m22;
						if((m22= *p1)==0){
							continue;
						}

	                    BYTE	m11= *(p1m-1);
			            BYTE	m12= *(p1m);
				        BYTE	m13= *(p1m+1);
					    BYTE	m21= *(p1-1);
						BYTE	m23= *(p1+1);
	                    BYTE	m31= *(p1p-1);
			            BYTE	m32= *(p1p);
				        BYTE	m33= *(p1p+1);

					    if(m22==0xFF
						&& m11==0xFF
	                    && m12==0xFF
			            && m13==0xFF
				        && m21==0xFF
					    && m23==0xFF
						&& m31==0xFF
	                    && m32==0xFF
						&& m33==0xFF){
				            continue;
						}

					    BYTE    r=m12 & m32;
						BYTE    t=m22 & r;
	                    *p2 = *p2 & ((r
			                      & ((m21 & m11 & m31)<<7)
				                  & ((t)<<1)) | 0x7F);


					    *p2 &= 0x81 |( r
						             & (t>>1)
							         & (t<<1) );

	                    *p2 = *p2 & ((r
			                      & ((m23 & m13 & m33)>>7)
				                  & ((t)>>1)) | 0xFE);

					}
				}
			}
		}
	}

	if(Allocbitoperation==true){
		DeleteMatrixBuff(bitoperation,YLenDot);
	}
}

inline void	DilateBinaryDataInACrossShape(BYTE &destm22, BYTE &m11, BYTE &m12, BYTE &m13, BYTE &m21, BYTE &m22, BYTE &m23, BYTE &m31, BYTE &m32, BYTE &m33)
{
	if(m22==0xFF)
		return;

	destm22 |=
	//1-8�r�b�g��
	  //�㉺
	     m12 | m32
	  //���E
	    |(m22<<1) | (m22>>1)
	//1,8�r�b�g��
	  //1�r�b�g��
	    |(m23<<7)
	  //8�r�b�g��
	    |(m21>>7);
}

/*

FatAreaInACrossShape Function Specification

	* ���l�����ꂽ�摜�f�[�^�̓񎟌��z��bmpdata��1�h�b�g�c��������
	* �c���̃A���S���Y��
	  �����r�b�g�ɂ��āA4�ߖT��1�����ł������Ύ��g��1�ɁA���̑���0�ɂ���

	ex)
		000      000
		100  ->  111		
		001      001		�����i�̃r�b�g�̂ݏ���

	BYTE **bmpdata		���l�����ꂽ�摜�f�[�^�̓������񎟌��z���A[y][x]�̏��Ɋi�[�����Ă���
						����1�o�C�g���ŏ��ʃr�b�g���摜�ł̉E�[�A�ŉ��ʂ͍��[�ɂ�����
	BYTE **bitoperation	�����p�Ɉꎞ�I�Ɋm�ۂ����񎟌��z��
	                    	NULL��������xbyte�~YLenDot�̑傫���̓񎟌��z��
	
	int xbyte		(�摜�̕�+1+7)>>3�ABYTE�^�̓��i���̓񎟌��z���ɂ����ɂ������ĕK�v�ȉ���
	int YLenDot		bmpdata�̏c�̒���
*/

void    FatAreaInACrossShape(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte, int YLenDot)
{
	int	XLenDot=xbyte*8;
	bool	Allocbitoperation=false;
	if(bitoperation==NULL){
		bitoperation=MakeMatrixBuff(xbyte,YLenDot);
		Allocbitoperation=true;
	}

	MatrixBuffCopy(bitoperation				,xbyte ,YLenDot
                  ,(const BYTE **)bmpdata	,xbyte ,YLenDot);

	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=1;y<YLenDot-1;y++){
		    BYTE	*p2=  &bmpdata[y][1];
			BYTE	*p1=  &bitoperation[y][1];
			BYTE	*p1p= &bitoperation[y+1][1];
		    BYTE	*p1m= &bitoperation[y-1][1];
			for(int x=8;x<XLenDot-8;x+=8,p2++,p1++,p1p++,p1m++){
				DilateBinaryDataInACrossShape(*(p2), *(p1m-1), *(p1m), *(p1m+1), *(p1-1), *(p1), *(p1+1), *(p1p-1), *(p1p), *(p1p+1));
			}
		}
	}

	ProcessEdgeWithBinary(bmpdata, bitoperation, xbyte, XLenDot, YLenDot, 0, DilateBinaryDataInACrossShape);

	if(Allocbitoperation==true){
		DeleteMatrixBuff(bitoperation,YLenDot);
	}
}

/*

ThinAreaInACrossShape Function Specification

	* ���l�����ꂽ�摜�f�[�^�̓񎟌��z��bmpdata��1�h�b�g���k�������B
	* ���k�̃A���S���Y��
	  �����r�b�g�ɂ��āA4�ߖT�Ǝ��g�����ׂ�1�ł����Ύ��g��1�ɁA�����ȊO��0�ɂ���

	ex)
		1100      1100
		1111  ->  0100		
		0100      0100		�����i�̃r�b�g�̂ݏ���

	BYTE **bmpdata		���l�����ꂽ�摜�f�[�^�̓������񎟌��z���A[y][x]�̏��Ɋi�[�����Ă���
						����1�o�C�g���ŏ��ʃr�b�g���摜�ł̉E�[�A�ŉ��ʂ͍��[�ɂ�����
	BYTE **bitoperation	�����p�Ɉꎞ�I�Ɋm�ۂ����񎟌��z��
	                    	NULL��������xbyte�~YLenDot�̑傫���̓񎟌��z��
	
	int xbyte			bmpdata��(�摜�̕�+1+7)>>3�ABYTE�^�̓��i���̓񎟌��z���ɂ����ɂ������ĕK�v�ȉ���
	int YLenDot		bmpdata�̏c�̒���
*/

void    ThinAreaInACrossShape(BYTE **bmpdata
							,BYTE **bitoperation
							,int xbyte ,int YLenDot)
{
	int	XLenDot=xbyte*8;
	bool	Allocbitoperation=false;
	if(bitoperation==NULL){
		bitoperation=MakeMatrixBuff(xbyte,YLenDot);
		Allocbitoperation=true;
	}

    MatrixBuffCopy(bitoperation				,xbyte,YLenDot
                  ,(const BYTE **)bmpdata	,xbyte,YLenDot);

	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=1;y<YLenDot-1;y++){
		    BYTE	*p2=  &bmpdata[y][1];
			BYTE	*p1=  &bitoperation[y][1];
			BYTE	*p1p= &bitoperation[y+1][1];
		    BYTE	*p1m= &bitoperation[y-1][1];
			for(int x=8;x<XLenDot-8;x+=8,p2++,p1++,p1p++,p1m++){
				ErodeBinaryDataInACrossShape(*(p2), *(p1m-1), *(p1m), *(p1m+1), *(p1-1), *(p1), *(p1+1), *(p1p-1), *(p1p), *(p1p+1));
			}
		}
	}

	ProcessEdgeWithBinary(bmpdata, bitoperation, xbyte, XLenDot, YLenDot, 0xFF, ErodeBinaryDataInACrossShape);

	if(Allocbitoperation==true){
		DeleteMatrixBuff(bitoperation,YLenDot);
	}
}

void    FatAreaRectangle(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte, int YLenDot 
				,int minx ,int miny ,int maxx ,int maxy)
{
	int	XLenDot=xbyte*8;
	bool	Allocbitoperation=false;
	if(bitoperation==NULL){
		bitoperation=MakeMatrixBuff(xbyte,YLenDot);
		Allocbitoperation=true;
	}

	if(miny<1)
		miny=1;
	if(maxy>=YLenDot-2)
		maxy=YLenDot-2;
	if(minx<8)
		minx=8;
	if(maxx<XLenDot-9)
		maxx=XLenDot-9;
	int	minxbyte=(minx>>3)-1;
	int	maxxbyte=((maxx+7)>>3)+1;
	if(maxxbyte>=xbyte)
		maxxbyte=xbyte-1;
	if(minxbyte<=1)
		minxbyte=1;

	//MatrixBuffCopy(bitoperation ,xbyte ,YLenDot
    //              ,bmpdata      ,xbyte ,YLenDot);
	MatrixBuffBlockCopy(bitoperation			,xbyte ,YLenDot
		               ,(const BYTE **)bmpdata	,xbyte ,YLenDot
                       ,minxbyte, miny ,maxxbyte ,maxy);

	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=miny;y<maxy;y++){
		    BYTE	*p2=  &bmpdata[y][1]		+minxbyte;
			BYTE	*p1=  &bitoperation[y][1]	+minxbyte;
			BYTE	*p1p= &bitoperation[y+1][1]	+minxbyte;
		    BYTE	*p1m= &bitoperation[y-1][1]	+minxbyte;
			//for(int x=8;x<XLenDot-9;x+=8,p2++,p1++,p1p++,p1m++){
			for(int i=minxbyte;i<maxxbyte;i++,p2++,p1++,p1p++,p1m++){
				uchar   m22;
			    if((m22= *p1)==0xFF)
				    continue;
				BYTE	m11= *(p1m-1);
	            BYTE	m12= *(p1m);
		        BYTE	m13= *(p1m+1);
			    BYTE	m21= *(p1-1);
				BYTE	m23= *(p1+1);
	            BYTE	m31= *(p1p-1);
		        BYTE	m32= *(p1p);
			    BYTE	m33= *(p1p+1);

			    if(m22==0
				&& m11==0
			    && m12==0
				&& m13==0
		        && m21==0
			    && m23==0
				&& m31==0
				&& m32==0
	            && m33==0)
		            continue;
		
		        BYTE    r=m12 | m32;
			    BYTE    t=m22 | r;

	            *p2 |=  ((r)
		              | ((m21 | m11 | m31)<<7)
			          | ((t)<<1)) & (~m22) &0x80;
				*p2 |= (r
					  | (t>>1)
					  | (t<<1)) & 0x7E;

		        *p2 |= ((r)
			         | ((m23 | m13 | m33)>>7)
				     | ((t)>>1))&(~m22) &0x01;

			}
		}
	}
	if(Allocbitoperation==true){
		DeleteMatrixBuff(bitoperation,YLenDot);
	}
}

void    ThinAreaRectangle(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int minx ,int miny ,int maxx ,int maxy)
{
	int	XLenDot=xbyte*8;
	bool	Allocbitoperation=false;
	if(bitoperation==NULL){
		bitoperation=MakeMatrixBuff(xbyte,YLenDot);
		Allocbitoperation=true;
	}

	if(miny<1)
		miny=1;
	if(maxy>=YLenDot-2)
		maxy=YLenDot-2;
	if(minx<8)
		minx=8;
	if(maxx<XLenDot-9)
		maxx=XLenDot-9;
	int	minxbyte=(minx>>3)-1;
	int	maxxbyte=((maxx+7)>>3)+1;
	if(maxxbyte>=xbyte)
		maxxbyte=xbyte-1;
	if(minxbyte<=1)
		minxbyte=1;

	//MatrixBuffCopy(bitoperation ,xbyte ,YLenDot
    //              ,bmpdata      ,xbyte ,YLenDot);
	MatrixBuffBlockCopy(bitoperation			,xbyte ,YLenDot
		               ,(const BYTE **)bmpdata	,xbyte ,YLenDot
                       ,minxbyte, miny ,maxxbyte ,maxy);    
    
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=miny;y<maxy;y++){
		    BYTE	*p2=  &bmpdata[y][1]		+minxbyte;
			BYTE	*p1=  &bitoperation[y][1]	+minxbyte;
			BYTE	*p1p= &bitoperation[y+1][1]	+minxbyte;
		    BYTE	*p1m= &bitoperation[y-1][1]	+minxbyte;
			for(int i=minxbyte;i<maxxbyte;i++,p2++,p1++,p1p++,p1m++){
			//for(int x=8;x<XLenDot-9;x+=8,p2++,p1++,p1p++,p1m++){
				uchar   m22;
			    if((m22= *p1)==0)
				    continue;

				BYTE	m11= *(p1m-1);
	            BYTE	m12= *(p1m);
		        BYTE	m13= *(p1m+1);
			    BYTE	m21= *(p1-1);
				BYTE	m23= *(p1+1);
	            BYTE	m31= *(p1p-1);
		        BYTE	m32= *(p1p);
			    BYTE	m33= *(p1p+1);
			    if(m22==0xFF
				&& m11==0xFF
			    && m12==0xFF
				&& m13==0xFF
		        && m21==0xFF
			    && m23==0xFF
				&& m31==0xFF
				&& m32==0xFF
	            && m33==0xFF)
		            continue;

				BYTE    r=m12 & m32;
				BYTE    t=m22 & r;
		        *p2 = *p2 & ((r
			              & ((m21 & m11 & m31)<<7)
				          & ((t)<<1)) | 0x7F);

			    *p2 &= 0x81 |( r
				             & (t>>1)
					         & (t<<1) );
	            *p2 = *p2 & ((r
		                  & ((m23 & m13 & m33)>>7)
			              & ((t)>>1)) | 0xFE);
			}           
        }
    }
	if(Allocbitoperation==true){
		DeleteMatrixBuff(bitoperation,YLenDot);
	}
}


void    AndArea(BYTE **Dest
				,BYTE **Src
				,int xbyte ,int YLenDot)
{

	int	XNumbInt =xbyte/sizeof(unsigned int);
	int	XNumbLeft=xbyte%sizeof(unsigned int);
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YLenDot;y++){
			unsigned int	*D=(unsigned int *)Dest[y];
			unsigned int	*S=(unsigned int *)Src[y];
			for(int x=0;x<XNumbInt;x++ ,S++,D++){
				*D &= *S;
			}
			BYTE	*d=(BYTE *)D;
			BYTE	*s=(BYTE *)S;
			for(int x=0;x<XNumbLeft;x++,d++,s++){
				*d &= *s;
			}
		}
	}

}

#define MaxNestLevel    655360	//10240
#define MaxNestLevel2   65536	//4096
#define MaxXYBlockSize  256

class  PickupStructUnlimited : public NPList<PickupStructUnlimited>
{
  public:
    BYTE	**TBuff;
    BYTE	**SBuff;
    int     XLen;
    int     YLen;
    int     MinX;
    int     MaxX;
    int     MinY;
    int     MaxY;
	int		ClusterMaxSize;
    int     xbyte;
    int     x;
    int     y;
    int     py1;
    int     plen;
    int     DotCount;
	int		NestLevel;
    NPListPack<PickupStructUnlimited>   EndStack;

    PickupStructUnlimited(void);

    PickupStructUnlimited &operator=(const PickupStructUnlimited &src);

};

/*----------------------------------------------------------------------------*/
//
//  1.���{�ꖼ
//
//  2.�p�����^����
//    PData
//    xbyte
//    x
//    y
//
//  3.�T�v
//
//  4.�@�\����
//
//  5.�߂��l
//
//  6.���l
//
/*----------------------------------------------------------------------------*/
void  AutoRegPutPick(struct PickupStruct &PData,int xbyte,int x,int y)
{
    //static  uchar   mask;
    //static  int     px;
    uchar   mask;
    int     px;

    px=(xbyte<<3)+x;
    if(y-PData.py1<0 || y-PData.py1>=PData.plen || px<0){
        return;
	}
	if(PData.MaxBlockXY!=0){
		if(PData.MaxX-PData.MinX>=PData.MaxBlockXY || PData.MaxY-PData.MinY>=PData.MaxBlockXY){
			return;
		}
	}
    //L=(y-PData.py1)*PData.XLen+xbyte;
    PData.NestLevel++;
    if(PData.NestLevel>MaxNestLevel){
        PData.NestLevel--;
        return;
        }
    mask=(uchar)(0x80>>x);
    if((PData.TBuff[y-PData.py1][xbyte] & mask)==0){
        PData.NestLevel--;
        return;
        }
    if((PData.SBuff[y-PData.py1][xbyte] & mask)!=0){
        PData.NestLevel--;
        return;
        }

    PData.SBuff[y-PData.py1][xbyte] |= mask;
    PData.DotCount++;
    if(PData.MinX>px){
        PData.MinX=px;
        if(PData.MaxX-px>=MaxXYBlockSize){
            return;
		}
    }
    if(PData.MaxX<px){
        PData.MaxX=px;
        if(px-PData.MinX>=MaxXYBlockSize){
            return;
        }
	}
    if(PData.MinY>y){
        PData.MinY=y;
        if(PData.MaxY-y>=MaxXYBlockSize){
            return;
        }
	}
    if(PData.MaxY<y){
        PData.MaxY=y;
        if(y-PData.MinY>=MaxXYBlockSize){
            return;
        }
	}

    if(x==0){
        if(xbyte>0){
                AutoRegPutPick(PData,xbyte-1, 7, y);
            if(y>0){
                AutoRegPutPick(PData,xbyte-1, 7, y-1);
                }
            if(y+1<PData.YLen){
                AutoRegPutPick(PData,xbyte-1, 7, y+1);
                }
            }
        }
    else{
        AutoRegPutPick(PData,xbyte, x-1, y);
        if(y>0){
            AutoRegPutPick(PData,xbyte, x-1, y-1);
            }
        if(y+1<PData.YLen){
            AutoRegPutPick(PData,xbyte, x-1, y+1);
            }
        }
    if(x==7){
        if(xbyte+1<PData.XLen){
            AutoRegPutPick(PData,xbyte+1, 0, y);

            if(y>0){
                AutoRegPutPick(PData,xbyte+1, 0, y-1);
                }
            if(y+1<PData.YLen){
                AutoRegPutPick(PData,xbyte+1, 0, y+1);
                }
            }
        }
    else{
        AutoRegPutPick(PData,xbyte, x+1, y);
        if(y>0){
            AutoRegPutPick(PData,xbyte, x+1, y-1);
            }
        if(y+1<PData.YLen){
            AutoRegPutPick(PData,xbyte, x+1, y+1);
            }
        }
    if(y>0){
        AutoRegPutPick(PData ,xbyte, x, y-1);
        }
    if(y+1<PData.YLen){
        AutoRegPutPick(PData ,xbyte, x, y+1);
        }

    PData.NestLevel--;
    return;
}

void  AutoRegPutPickUnlimited2(PickupStructUnlimited &PData,int xbyte,int x,int y);



//static  PickupStructUnlimited *__fastcall AutoRegPutPickUnlimitedInnerDelete(PickupStructUnlimited *k
static  PickupStructUnlimited * AutoRegPutPickUnlimitedInnerDelete(PickupStructUnlimited *k,PickupStructUnlimited &PData)
{
    PData.DotCount=k->DotCount;
    PData.MinX=k->MinX;
    PData.MinY=k->MinY;
    PData.MaxX=k->MaxX;
    PData.MaxY=k->MaxY;
    PickupStructUnlimited *NextK=k->GetNext();
    PData.EndStack.RemoveList(k);
    delete  k;
    return(NextK);
}

void  AutoRegPutPickUnlimited(PickupStructUnlimited &PData,int xbyte,int x,int y)
{
    //static  uchar   mask;
    //static  int     px;
    uchar   mask;
    int     px;

    px=(xbyte<<3)+x;
	if(PData.MaxX-min(px,PData.MinX)>PData.ClusterMaxSize){
        goto    FencEnd;
	}
	if(max(px,PData.MaxX)-PData.MinX>PData.ClusterMaxSize){
        goto    FencEnd;
	}
	if(PData.MaxY-min(y,PData.MinY)>PData.ClusterMaxSize){
        goto    FencEnd;
	}
	if(max(y,PData.MaxY)-PData.MinY>PData.ClusterMaxSize){
        goto    FencEnd;
	}

    if(y-PData.py1<0 || y-PData.py1>=PData.plen || px<0){
        goto    FencEnd;
	}
    //L=(y-PData.py1)*PData.XLen+xbyte;
    PData.NestLevel++;
    mask=(uchar)(0x80>>x);
    if((PData.TBuff[y-PData.py1][xbyte] & mask)==0){
        PData.NestLevel--;
        goto    FencEnd;
        }
    if((PData.SBuff[y-PData.py1][xbyte] & mask)!=0){
        PData.NestLevel--;
        goto    FencEnd;
        }
    PData.SBuff[y-PData.py1][xbyte] |= mask;
    PData.DotCount++;
    if(PData.MinX>px){
        PData.MinX=px;
        }
    if(PData.MaxX<px){
        PData.MaxX=px;
        }
    if(PData.MinY>y){
        PData.MinY=y;
        }
    if(PData.MaxY<y){
        PData.MaxY=y;
        }

    if(PData.NestLevel>MaxNestLevel2){
        PData.NestLevel--;
        return;
        }

    if(x==0){
        if(xbyte>0){
            AutoRegPutPickUnlimited(PData,xbyte-1, 7, y);
            if(y>0){
                AutoRegPutPickUnlimited(PData,xbyte-1, 7, y-1);
                }
            if(y+1<PData.YLen){
                AutoRegPutPickUnlimited(PData,xbyte-1, 7, y+1);
                }
            }
        }
    else{
        AutoRegPutPickUnlimited(PData,xbyte, x-1, y);
        if(y>0){
            AutoRegPutPickUnlimited(PData,xbyte, x-1, y-1);
            }
        if(y+1<PData.YLen){
            AutoRegPutPickUnlimited(PData,xbyte, x-1, y+1);
            }
        }
    if(x==7){
        if(xbyte+1<PData.XLen){
            AutoRegPutPickUnlimited(PData,xbyte+1, 0, y);

            if(y>0){
                AutoRegPutPickUnlimited(PData,xbyte+1, 0, y-1);
                }
            if(y+1<PData.YLen){
                AutoRegPutPickUnlimited(PData,xbyte+1, 0, y+1);
                }
            }
        }
    else{
        AutoRegPutPickUnlimited(PData,xbyte, x+1, y);
        if(y>0){
            AutoRegPutPickUnlimited(PData,xbyte, x+1, y-1);
            }
        if(y+1<PData.YLen){
            AutoRegPutPickUnlimited(PData,xbyte, x+1, y+1);
            }
        }
    if(y>0){
        AutoRegPutPickUnlimited(PData ,xbyte, x, y-1);
        }
    if(y+1<PData.YLen){
        AutoRegPutPickUnlimited(PData ,xbyte, x, y+1);
        }


    PData.NestLevel--;

    FencEnd:;
    if(PData.NestLevel<MaxNestLevel2/2){
        for(PickupStructUnlimited *k=PData.EndStack.GetFirst();k!=NULL;){
            k->DotCount=PData.DotCount;
            k->MinX=PData.MinX;
            k->MinY=PData.MinY;
            k->MaxX=PData.MaxX;
            k->MaxY=PData.MaxY;
            AutoRegPutPickUnlimited2(*k,k->xbyte,k->x,k->y);

            k=AutoRegPutPickUnlimitedInnerDelete(k,PData);
            }
        }
    return;
}

void  AutoRegPutPickUnlimited2(PickupStructUnlimited &PData,int xbyte,int x,int y)
{
    //static  uchar   mask;
    //static  int     px;

    int     px;

    px=(xbyte<<3)+x;
	if(PData.MaxX-min(px,PData.MinX)>PData.ClusterMaxSize){
        goto    FencEnd;
	}
	if(max(px,PData.MaxX)-PData.MinX>PData.ClusterMaxSize){
        goto    FencEnd;
	}
	if(PData.MaxY-min(y,PData.MinY)>PData.ClusterMaxSize){
        goto    FencEnd;
	}
	if(max(y,PData.MaxY)-PData.MinY>PData.ClusterMaxSize){
        goto    FencEnd;
	}
    if(y-PData.py1<0 || y-PData.py1>=PData.plen || px<0){
        goto    FencEnd;
	}
    PData.NestLevel++;

    if(PData.MinX>px){
        PData.MinX=px;
        }
    if(PData.MaxX<px){
        PData.MaxX=px;
        }
    if(PData.MinY>y){
        PData.MinY=y;
        }
    if(PData.MaxY<y){
        PData.MaxY=y;
        }

    if(x==0){
        if(xbyte>0){
            AutoRegPutPickUnlimited(PData,xbyte-1, 7, y);
            if(y>0){
                AutoRegPutPickUnlimited(PData,xbyte-1, 7, y-1);
                }
            if(y+1<PData.YLen){
                AutoRegPutPickUnlimited(PData,xbyte-1, 7, y+1);
                }
            }
        }
    else{
        AutoRegPutPickUnlimited(PData,xbyte, x-1, y);
        if(y>0){
            AutoRegPutPickUnlimited(PData,xbyte, x-1, y-1);
            }
        if(y+1<PData.YLen){
            AutoRegPutPickUnlimited(PData,xbyte, x-1, y+1);
            }
        }
    if(x==7){
        if(xbyte+1<PData.XLen){
            AutoRegPutPickUnlimited(PData,xbyte+1, 0, y);

            if(y>0){
                AutoRegPutPickUnlimited(PData,xbyte+1, 0, y-1);
                }
            if(y+1<PData.YLen){
                AutoRegPutPickUnlimited(PData,xbyte+1, 0, y+1);
                }
            }
        }
    else{
        AutoRegPutPickUnlimited(PData,xbyte, x+1, y);
        if(y>0){
            AutoRegPutPickUnlimited(PData,xbyte, x+1, y-1);
            }
        if(y+1<PData.YLen){
            AutoRegPutPickUnlimited(PData,xbyte, x+1, y+1);
            }
        }
    if(y>0){
        AutoRegPutPickUnlimited(PData ,xbyte, x, y-1);
        }
    if(y+1<PData.YLen){
        AutoRegPutPickUnlimited(PData ,xbyte, x, y+1);
        }


    PData.NestLevel--;
    FencEnd:;
    if(PData.NestLevel<MaxNestLevel2/2){
        for(PickupStructUnlimited *k=PData.EndStack.GetFirst();k!=NULL;){
            k->DotCount=PData.DotCount;
            k->MinX=PData.MinX;
            k->MinY=PData.MinY;
            k->MaxX=PData.MaxX;
            k->MaxY=PData.MaxY;
            if(k->y==4356 && k->xbyte==136 && k->x==3){
                k->x=3;
			}
            AutoRegPutPickUnlimited2(*k,k->xbyte,k->x,k->y);

            k=AutoRegPutPickUnlimitedInnerDelete(k,PData);
        }
    }
    return;
}


PickupStructUnlimited::PickupStructUnlimited(void)
{
    TBuff=NULL;
    SBuff=NULL;
}

PickupStructUnlimited &PickupStructUnlimited::operator=(const PickupStructUnlimited &src)
{
	TBuff=src.TBuff;
	SBuff=src.SBuff;
	XLen =src.XLen;
	YLen =src.YLen;
	MinX =src.MinX;
	MaxX =src.MaxX;
	MinY =src.MinY;
	MaxY =src.MaxY;
	ClusterMaxSize	=src.ClusterMaxSize;
	xbyte=src.xbyte;
	x    =src.x;
	y    =src.y;
	py1  =src.py1;
	plen =src.plen;
	DotCount=src.DotCount;
	//NestLevel=src.NestLevel;

    return(*this);
}

void    BitmapClusterSized(BYTE **bmpdata ,int xbyte ,int YLen 
						   ,int XYMaxSize ,int XYMinSize ,int AreaMaxSize ,int AreaMinSize
						   ,int DotPerLine, int MaxLines
						   ,int ClusterMaxSize
						   ,void (*FoundOneCluster)(BYTE **MapData,int xbyte,int ylen,int minX,int minY,int maxX,int maxY,void *anydata)
						   ,void *anydata)
{
    uchar   **tmpdata=MakeMatrixBuff(xbyte,YLen);
    uchar   **SBuff  =MakeMatrixBuff(xbyte,YLen);

	BitmapClusterSized(bmpdata ,xbyte ,YLen 
						   ,tmpdata ,SBuff 
						   ,XYMaxSize ,XYMinSize ,AreaMaxSize ,AreaMinSize
						   ,DotPerLine, MaxLines
						   ,ClusterMaxSize
						   ,FoundOneCluster,anydata);

    DeleteMatrixBuff(SBuff,YLen);
    DeleteMatrixBuff(tmpdata,YLen);
}

void    BitmapClusterSized(BYTE **bmpdata ,int xbyte ,int YLen 
						   ,uchar   **tmpdata ,uchar   **SBuff 
						   ,int XYMaxSize ,int XYMinSize ,int AreaMaxSize ,int AreaMinSize
						   ,int DotPerLine, int MaxLines
						   ,int ClusterMaxSize
						   ,void (*FoundOneCluster)(BYTE **MapData,int xbyte,int ylen,int minX,int minY,int maxX,int maxY,void *anydata)
						   ,void *anydata)
{
    PickupStructUnlimited   PData;

    MatrixBuffCopy(  tmpdata				,xbyte,YLen
                    ,(const BYTE **)bmpdata	,xbyte,YLen);

    int x;
    BYTE    mask;

    PData.TBuff=tmpdata;
    PData.SBuff=SBuff;
    PData.XLen =xbyte;
    PData.YLen =YLen;
    PData.py1  =0;
    PData.plen =YLen;
    MatrixBuffClear(SBuff,0,xbyte,YLen);
    for(int y=1;y<YLen && y<YLen-1;y++){
        uchar   *q=tmpdata[y];
        for(int b=0;b<xbyte;b++,q++){
            if(*q==0){
                continue;
			}
            for(x=0,mask=0x80;x<8;x++,mask>>=1){
                if((*q&mask)!=0){
                    break;
				}
			}
            PData.MinX =(b<<3)+x;
            PData.MaxX =PData.MinX;
            PData.MinY =y;
            PData.MaxY =y;
			PData.ClusterMaxSize=ClusterMaxSize;
            PData.DotCount=0;
            PData.NestLevel=0;
            AutoRegPutPickUnlimited(PData ,b,x,y);
            //int dx=PData.MaxX-PData.MinX+1;
            //int dy=PData.MaxY-PData.MinY+1;

            int mx1=PData.MinX>>3;
            int mx2=(PData.MaxX+7)>>3;
            if(mx1<0){
                mx1=0;
			}
            if(mx2>DotPerLine-1){
                mx2=DotPerLine-1;
			}

            if(PData.DotCount<AreaMinSize || AreaMaxSize<PData.DotCount
			|| min(PData.MaxX-PData.MinX,PData.MaxY-PData.MinY)<XYMinSize || XYMaxSize<max(PData.MaxX-PData.MinX,PData.MaxY-PData.MinY) ){
                for(int ty=PData.MinY;ty<=PData.MaxY;ty++){
                    if(ty<0 || ty>=YLen){
                        continue;
					}
                    int pmx=((mx2+1)<xbyte)?(mx2+1):xbyte;
                    for(int tx=mx1;tx<pmx;tx++){
                        bmpdata[ty][tx] &= (uchar)~SBuff[ty][tx];
					}
				}
			}
			else{
				if(FoundOneCluster!=NULL){
					FoundOneCluster(SBuff,xbyte,YLen
						,PData.MinX,PData.MinY,PData.MaxX,PData.MaxY,anydata);
				}
			}

            for(int ty=PData.MinY;ty<=PData.MaxY;ty++){
                if(ty<0 || ty>=YLen){
                    continue;
				}
                int pmx=((mx2+1)<xbyte)?(mx2+1):xbyte;
                for(int tx=mx1;tx<pmx;tx++){
                    tmpdata[ty][tx] &= (uchar)~SBuff[ty][tx];
                    SBuff[ty][tx]=0;
				}
			}
		}
	}
}

int GetBmpMode(int X,int Y,int xlen,int ylen ,uchar **bmpdata ,int xbyte)
//  ���`�̈��Ƀr�b�g���S���Ȃ��Ƃ��O
//  ���`�̈悪�S�ăr�b�g�ŕ������Ă����Ƃ�  �Q
//  ���`�̈��Ƀr�b�g���U�݂����Ƃ�          �P

{
    int b=0;
    int w=0;

    for(int y=0;y<ylen;y++){
        uchar   *p=bmpdata[Y+y];
        for(int x=0;x<xlen;x++){
            if((p[((X+x)>>3)]&(0x80>>((X+x)&0x07)))!=0){
                b++;
			}
            else{
                w++;
            }
        }
	}
    if(b==0){
        return(0);
	}
    if(w==0){
        return(2);
	}
    return(1);
}

void    Binarize(BYTE **bmpdata
				,int xbyte ,int YLenDot ,ImageBuffer &Src
				,int LBright ,int HBright
				,int XSep,int YSep)
{
	int	XLen=xbyte*8;
	if(Src.GetWidth()/XSep<XLen){
		XLen=Src.GetWidth()/XSep;
	}
	int	YLen=YLenDot;
	if(Src.GetHeight()/YSep<YLen){
		YLen=Src.GetHeight()/YSep;
	}
	int	XLen8=XLen/8;
	int	XLenS=XLen%8;
	#pragma omp parallel
	{                                                
		#pragma omp for
		for(int y=0;y<YLen;y++){
			BYTE	*s=Src.GetY(y*YSep);
			BYTE	*d=bmpdata[y];
			for(int x=0;x<XLen8;x++){
				BYTE	Mask=0;
				for(int i=0;i<8;i++){
					Mask<<=1;
					if(LBright<=*s && *s<=HBright){
						Mask |= 1;
					}
					s+=XSep;
				}
				d[x] = Mask;
			}
			for(int x=0;x<XLenS;x++){
				if(LBright<=*s && *s<=HBright){
					d[XLen8+(x>>3)] |= 0x80>>(x&7);
				}
				s+=XSep;
			}
		}
	}
}


class	PickupFlexAreaStruct;
class	PickupFlexAreaList;
class	PickFlexAreaPointerList : public NPList<PickFlexAreaPointerList>
{
public:
	PickupFlexAreaList *Point;

	PickFlexAreaPointerList(PickupFlexAreaList *point):Point(point){}
};

class   PickupFlexAreaList : public NPList<PickupFlexAreaList> ,public FlexArea
{
  public:
	NPListPack<PickFlexAreaPointerList>	PointerList;
	PickupFlexAreaStruct			*Parent;
	struct{
		bool						Mark:1;
		bool						Counter:1;
	};
	PickupFlexAreaList(PickupFlexAreaStruct *parent):Parent(parent){	Mark=false;	Counter=false;	}
};


class  PickupFlexAreaStruct
{
public:
    uchar   **TBuff;
    uchar   **SBuff;
    int     XLen;
    int     YLen;
    int     MinX;
    int     MaxX;
    int     MinY;
    int     MaxY;
    int     xbyte;
    int     DotCount;
	int		AMinX,AMinY;
	int		AMaxX,AMaxY;
	NPListPack<PickupFlexAreaList> FPack;
};

static	void	PickupFlexAreaIn(PickupFlexAreaStruct &PData ,int x ,int y)
{
	if((PData.TBuff[y][x>>3]&(0x80>>(x&7)))==0){
		return;
	}
	PData.TBuff[y][x>>3]&=~(0x80>>(x&7));
	PData.SBuff[y-PData.MinY][(x-PData.MinX)>>3] |= 0x80>>((x-PData.MinX)&7);
	
    PData.DotCount++;
    if(PData.AMinX>x){
        PData.AMinX=x;
        }
    if(PData.AMaxX<x){
        PData.AMaxX=x;
        }
    if(PData.AMinY>y){
        PData.AMinY=y;
        }
    if(PData.AMaxY<y){
        PData.AMaxY=y;
        }

    if(x==PData.MinX){
		PickupFlexAreaIn(PData ,x+1 ,y);
		if(y<PData.MaxY-1){
			PickupFlexAreaIn(PData ,x+1,y+1);
			PickupFlexAreaIn(PData ,x  ,y+1);
		}
		if(y>PData.MinY){
			PickupFlexAreaIn(PData ,x+1,y-1);
			PickupFlexAreaIn(PData ,x  ,y-1);
		}
	}
    else if(x<PData.MaxX-1){
		PickupFlexAreaIn(PData ,x+1 ,y);
		if(y<PData.MaxY-1){
			PickupFlexAreaIn(PData ,x+1,y+1);
			PickupFlexAreaIn(PData ,x  ,y+1);
			PickupFlexAreaIn(PData ,x-1,y+1);
		}
		if(y>PData.MinY){
			PickupFlexAreaIn(PData ,x+1,y-1);
			PickupFlexAreaIn(PData ,x  ,y-1);
			PickupFlexAreaIn(PData ,x-1,y-1);
		}
		PickupFlexAreaIn(PData ,x-1 ,y);
	}
	else if(x==PData.MaxX-1){
		if(y<PData.MaxY-1){
			PickupFlexAreaIn(PData ,x  ,y+1);
			PickupFlexAreaIn(PData ,x-1,y+1);
		}
		if(y>PData.MinY){
			PickupFlexAreaIn(PData ,x  ,y-1);
			PickupFlexAreaIn(PData ,x-1,y-1);
		}
		PickupFlexAreaIn(PData ,x-1 ,y);
	}
    return;
}

static	void	PickupFlexAreaIn(PickupFlexAreaStruct &PData)
{
	int	SXLen=PData.MaxX-PData.MinX;
	int	SYLen=PData.MaxY-PData.MinY;
	int	SXByte=(SXLen+7)>>3;
	BYTE	**TmpBmp=NULL;
	BYTE	SXBuff1[2000];
	BYTE	*SXBuff2[500];
	if((SXByte*SYLen)<sizeof(SXBuff1)/sizeof(SXBuff1[0]) && SYLen<sizeof(SXBuff2)/sizeof(SXBuff2[0])){
		TmpBmp=SXBuff2;
		for(int y=0;y<SYLen;y++){
			TmpBmp[y]= &SXBuff1[y*SXByte];
		}
	}
	else{
		TmpBmp=MakeMatrixBuff(SXByte,SYLen);
	}
	MatrixBuffClear(TmpBmp ,0,SXByte,SYLen);
	PData.SBuff	=TmpBmp;

	for(int y=PData.MinY;y<PData.MaxY;y++){
		BYTE	*s=PData.TBuff[y];
		for(int x=PData.MinX;x<PData.MaxX;x++){
			if(((s[x>>3])&(0x80>>(x&7)))!=0){
				PData.AMinX=  99999999;
				PData.AMinY=  99999999;
				PData.AMaxX= -99999999;
				PData.AMaxY= -99999999;
				PickupFlexAreaIn(PData,x,y);
				if(PData.AMinX<=PData.AMaxX && PData.AMinY<=PData.AMaxY){
					PickupFlexAreaList	*f=new PickupFlexAreaList(&PData);
					f->BuildFromRaster(PData.SBuff,SXByte,SYLen
			                                ,PData.MinX,PData.MinY
											,PData.AMinX-PData.MinX	 ,PData.AMinY-PData.MinY
											,min(PData.AMaxX-PData.MinX+1,SXLen),min(PData.AMaxY-PData.MinY+1,SYLen)
											,PData.XLen,PData.YLen);
					MatrixBuffBlockClear(PData.SBuff,SXByte,SYLen
		                        ,(PData.AMinX-PData.MinX)>>3	 ,PData.AMinY-PData.MinY
								,min(((PData.AMaxX-PData.MinX+1)>>3)+1,SXByte),min(PData.AMaxY-PData.MinY+1,SYLen));
					PData.FPack.AppendList(f);
				}
			}
		}
	}
	if(TmpBmp!=SXBuff2){
		DeleteMatrixBuff(TmpBmp,SYLen);
	}
}

static	void	PickupFLineLenList(int &Dest ,PickupFlexAreaList *f)
{
	if(f->Counter==false){
		Dest+=f->GetFLineLen();
		f->Counter=true;
		for(PickFlexAreaPointerList *a=f->PointerList.GetFirst();a!=NULL;a=a->GetNext()){
			PickupFLineLenList(Dest ,a->Point);
		}
	}
}
static	void	PickupAddFLineList(struct FlexLine *S ,int &Current,PickupFlexAreaList *f)
{
	if(f->Mark==false){
		memcpy(&S[Current],f->GetFLinePoint(),sizeof(S[0])*f->GetFLineLen());
		Current+=f->GetFLineLen();
		f->Mark=true;
		for(PickFlexAreaPointerList *a=f->PointerList.GetFirst();a!=NULL;a=a->GetNext()){
			PickupAddFLineList(S ,Current,a->Point);
		}
	}
}



struct	FatThinAreaStruct
{
	int		AddedY;
	int		AddedXByte;
	BYTE	StartMask;
	int32	Len;
	BYTE	EndMask;	//�O�̎��A��������

};

void    FatArea(BYTE **Dest
				,BYTE **Src
				,int _xbyte, int XLenDot ,int YLenDot ,int Length)
{
	struct	FatThinAreaStruct	*PBitData[8];
	for(int i=0;i<8;i++){
		PBitData[i]=new struct FatThinAreaStruct[Length*2+1];
	}
	{
		int	n=0;
		for(int y= -Length;y<=Length;y++,n++){
			int	x1= -sqrt((double)(Length*Length - y*y));
			int	x2= -x1;
			for(int CurrentBit=0;CurrentBit<8;CurrentBit++){
				struct FatThinAreaStruct	*h= &PBitData[CurrentBit][n];
				h->AddedY=y;
				h->AddedXByte	=(x1+CurrentBit)>>3;
				h->StartMask	=0xFF>>((x1+CurrentBit)&7);
				int	EndXByte	=(x2+CurrentBit)>>3;
				if(h->AddedXByte==EndXByte){
					h->StartMask &= 0xFF00>>((x2+CurrentBit)&7);
					h->EndMask=0;
					h->Len=0;
				}
				else{
					h->EndMask=0xFF00>>((x2+CurrentBit)&7);
					h->Len=EndXByte - h->AddedXByte-1;
				}
			}
		}
	}

	int	N=YLenDot-Length*2;
	#pragma omp parallel              
	{                                                
		#pragma omp for
		for(int i=0;i<N;i++){
			int	y=i+Length;
			BYTE	*DestBmp=Dest[y];
			for(int x=Length;x<XLenDot-Length;x++){
				int	xbit=x&7;
				int	xbyte=x>>3;
				int	n=0;
				for(int ys= -Length;ys<=Length;ys++,n++){
					struct FatThinAreaStruct	*h= &PBitData[xbit][n];
					BYTE	*s=Src[y+h->AddedY]+xbyte+h->AddedXByte;
					if((*s&h->StartMask)!=0){
						DestBmp[xbyte] |= 0x80>>xbit;
						goto	ExistBit;
					}
					s++;
					for(int j=0;j<h->Len;j++){
						if(*s!=0){
							DestBmp[xbyte] |= 0x80>>xbit;
							goto	ExistBit;
						}
						s++;
					}
					if(h->EndMask!=0){
						if((*s&h->EndMask)!=0){
							DestBmp[xbyte] |= 0x80>>xbit;
							goto	ExistBit;
						}
					}
				}
				DestBmp[xbyte] &= ~(0x80>>xbit);
ExistBit:;
			}
		}
	}
	for(int i=0;i<8;i++){
		delete	[]PBitData[i];
	}
}

void	ReductionImage(BYTE **DestBmp ,int DestXLen,int DestYLen
					  ,BYTE **SrcBmp  ,int SrcXLen ,int SrcYLen
					  ,int Rate)
/*
	Rate���̂P�Ƀr�b�g���Ԉ���
*/
{
	#pragma omp parallel              
	{                                                
		#pragma omp for
		for(int yd=0;yd<DestYLen;yd++){
			int	y1=yd*Rate;
			int	y2=(yd+1)*Rate;
			BYTE	*d=DestBmp[yd];
			for(int y=y1;y<y2 && y<SrcYLen;y++){
				BYTE	*s=SrcBmp[y];
				for(int x=0;x<SrcXLen;x++){
					if((s[x>>3]&(0x80>>(x&7)))!=0){
						int	L=x/Rate;
						d[L>>3] |= 0x80>>(L&7);
					}
				}
			}
		}
	}
}
