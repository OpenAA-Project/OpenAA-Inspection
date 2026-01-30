/*
 * Copyright (C) 2020
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

// EWCLIB [Easy Web Camera LIBrary]
//           version 2.5
// Copyright (C) 2018 I.N.  All rights reserved.

// OS:Windows XP/Vista/7/8/8.1/10
// Compiler:Visual C++ 2008, 2010~2017+[qedit.h]

// 2010/04/15 ver.1.9 EWC_GetLastMessage():Unicode/�}���`�o�C�g�̗��Ή���
// 2010/05/04         �J�n
// 2010/05/06         EWC_Open()/EWC_Close()�d�l�ύX�D
// 2010/05/06         EWC_Run()/EWC_Stop()�ǉ��D
// 2010/05/08         EWC_CloseAll()�ǉ��D
// 2010/05/13 ver.2.0 ����
// 2012/02/28 ver.2.1 �������������̃��������[�N���C��
// 2014/01            �ő��J�������ύX(8->10), @device:sw���ΏۂƂ���
// 2014/01            �����f�o�C�X�g�p�ς݃t���O,EWC_GetFormat()�ǉ�
// 2014/01            EWC_Open():FriendlyName�w��,�f�t�H���g�l�ǉ�
// 2014/01/17 ver.2.2 EWC_Open()�̃o���G�[�V�����ǉ�,EWC_GetDeviceName()�ǉ�
// 2014/01/27         �f�o�C�X�o�̓s���̃t�H�[�}�b�g�w���̋@�\���ǉ�
// 2014/01/27         �t�H�[�}�b�g�ꗗ���擾�����T���v���̏C��
// 2014/01/27         EWC_Open()�����ǉ�,ewc_type,ewc_device_type(EWC_DEVICE_TYPE)�ǉ�
// 2014/01/27 ver.2.3 EWC_GetDeviceSubtype(),EWC_GetSubtype(),EWC_GUIDtoTEXT()���ǉ�
// 2014/04/08         ewc_s[].count�ǉ�,EWC_Pause()�ǉ�,EWC_OneShot()�ǉ�
// 2014/04/22 ver.2.4 EWC_SaveProperty(),EWC_LoadProperty(),EWC_SetManual()�ǉ�
// 2018/05/29 ver.2.5 Visual C++ 2017�Ή�

#pragma once
#define EWCLIB_H

#include <dshow.h>
#pragma include_alias( "dxtrans.h", "qedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__
#include <qedit.h>
#pragma comment(lib,"strmiids.lib")

#include <math.h>	//for floor()
#include "XCriticalFunc.h"
#include <QMutex>

//�摜�t�H�[�}�b�g�i�o�͕����j
#ifndef EWC_TYPE
	#ifdef _CV_H_
		#define EWC_TYPE MEDIASUBTYPE_RGB24
	#else
		#ifdef __OPENCV_CV_H__
			#define EWC_TYPE MEDIASUBTYPE_RGB24
		#else
			#define EWC_TYPE MEDIASUBTYPE_RGB32
		#endif
	#endif
#endif
//�f�t�H���g�l
GUID ewc_type= EWC_TYPE;

//�摜�t�H�[�}�b�g�i�f�o�C�X�o�̓s�������j
#ifndef EWC_DEVICE_TYPE
	#define EWC_DEVICE_TYPE GUID_NULL
#endif
//�f�t�H���g�l
GUID ewc_device_type= EWC_DEVICE_TYPE;

#ifndef EWC_WX
	#define EWC_WX 640
	//#define EWC_WX 1024
#endif
#ifndef EWC_WY
	#define EWC_WY 480
	//#define EWC_WY 768
#endif
#ifndef EWC_FPS
	#define EWC_FPS 30
#endif
//�f�t�H���g�l
int ewc_wx= EWC_WX;
int ewc_wy= EWC_WY;
double ewc_fps= EWC_FPS;

#ifndef min
	#define min(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef max
	#define max(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef EWC_NCAMMAX
#define EWC_NCAMMAX 10	//�J�����̍ő��F����v2.2
#endif

int ewc_cominit= 0;			//COM�������t���O(1�Ȃ��I���������s��)
int ewc_ncam= -1;			//�J�����ڑ���
int ewc_order[EWC_NCAMMAX];	//�����������ԍ��̏���
int ewc_ordercnt= 0;		//ewc_order[]�̂��߂̃J�E���^
HRESULT ewc_hr;
int ewc_used[EWC_NCAMMAX];	//�����f�o�C�X�g�p�ς݃t���O

#define EWC_RUN_TIMEOUT		8000
#define EWC_STOP_TIMEOUT	3000
#define EWC_RETRYTIMES		3

#define EWC_VPAMPMAX	10
#define EWC_CAMCTLMAX	7
#define EWC_ITEMMAX		(EWC_VPAMPMAX+EWC_CAMCTLMAX)
#define	ProductID835		0xa007

#define ewc_release(x) {if(x)x->Release();x=0;}
void EWC_Reallocate(int num ,int DotPerLine, int MaxLines);
void ewc_DeleteMediaType(AM_MEDIA_TYPE *pmt);

//�\���̂̒��`
struct ewc_struct{
	int wx;					//�摜�̕�
	int wy;					//�摜�̍���
	int	AllocatedX;
	int	AllocatedY;
	double fps;				//�t���[�����[�g�i�����w���l�j
	int device;				//�����f�o�C�X�ԍ��i�����w���l�j
	int devn;				//���蓖�Ă��ꂽ�����f�o�C�X�ԍ�v2.2
	char *pdname;			//FriendlyName���r�pv2.2
	char dname[256];		//�擾����FriendlyName v2.2
	GUID mstype;			//�o�͉摜�̃t�H�[�}�b�g
	char mstype_t[80];		//mstype�ɑΉ����镶����v2.3
	GUID dev_mstype;		//�f�o�C�X�o�̓s���̃t�H�[�}�b�gv2.3
	char dev_mstype_t[80];	//dev_mstype�ɑΉ����镶����v2.3
	volatile int init;
	volatile int stop;
	volatile int errcode;
	int *pbuf;				//�摜�̕ۑ���
	int *buffer;			//�����Ŋm�ۂ����t���[���o�b�t�@
	volatile long bufsize;	//�����ꂽ�摜�f�[�^�̃o�C�g��
	volatile double stime;	//�T���v������(s)
	volatile double ftime;	//�t���[������(s)�̎����l
	volatile int count;		//�t���[���擾��v2.4
	int vflag[EWC_ITEMMAX];
	IGraphBuilder			*pGraph;
	IBaseFilter				*pF;
	ISampleGrabber			*pGrab;
	ICaptureGraphBuilder2	*pBuilder;
	IBaseFilter				*pCap;
	IAMVideoProcAmp			*pVPAmp;
	IAMCameraControl		*pCamCtl;
	IMediaControl			*pMediaControl;
	IAMStreamConfig			*pConfig;
	IMoniker				*pMoniker;
	IEnumMoniker			*pEnum;
	ICreateDevEnum			*pDevEnum;
	IAMTimelineGroup		*pTimelineGroup;
	AM_MEDIA_TYPE			*pmt;
	AM_MEDIA_TYPE			mt;
	IPin					*pSrcOut;
	IPin					*pSGrabIn;
	IMediaEvent				*pMediaEvent;
	bool					Captured;
	bool					Initialized;

	ewc_struct(void){
		wx			=0;
		wy			=0;
		AllocatedX	=0;
		AllocatedY	=0;
		count		=0;
		pdname		=NULL;
		pbuf		=NULL;
		buffer		=NULL;

		pGraph		=NULL;
		pF			=NULL;
		pGrab		=NULL;
		pBuilder	=NULL;
		pCap		=NULL;
		pVPAmp		=NULL;
		pCamCtl		=NULL;
		pMediaControl=NULL;
		pConfig		=NULL;
		pMoniker	=NULL;
		pEnum		=NULL;
		pDevEnum	=NULL;
		pTimelineGroup=NULL;
		pmt			=NULL;
		pSrcOut		=NULL;
		pSGrabIn	=NULL;
		pMediaEvent	=NULL;
		Initialized	=NULL;
	}
};

ewc_struct ewc_s[EWC_NCAMMAX];

//�t�H�[�}�b�g�i�[�̂��߂̍\����v2.3
struct ewc_format{
	int width;
	int height;
	int bit;
	REFERENCE_TIME AvgTimePerFrame;
	double fps;
	GUID subtype;
	char subtype_t[80];	//subtype�ɑΉ����镶����v2.3
};


//�R�[���o�b�N�֐�
class	ewc_SampleGrabberCB;
ewc_SampleGrabberCB *ewc_pSampleGrabberCB[EWC_NCAMMAX];
QMutex	ewc_Mutex[EWC_NCAMMAX];

//�R�[���o�b�N�֐��̒��`
class ewc_SampleGrabberCB :public ISampleGrabberCB
{
public:
	
	DWORD	TimeDim[100];
	int		LastTimeIndex;
	DWORD	LastTime;
	bool	OnChanging;
	int		CallBackCount;

	STDMETHODIMP_(ULONG) AddRef()
	{
		return 2;
	}
	STDMETHODIMP_(ULONG) Release()
	{
		return 1;
	}
	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv)
	{
		if(riid==IID_ISampleGrabberCB || riid==IID_IUnknown){
			*ppv= (void *)static_cast<ISampleGrabberCB*>(this);
			return NOERROR;
		}
		return E_NOINTERFACE;
	}
	STDMETHODIMP SampleCB(double SampleTime, IMediaSample *pSample)
	{
		return S_OK;
	}
	//�t���[�����ɌĂ΂����֐�
	STDMETHODIMP BufferCB(double dblSampleTime, BYTE *pBuffer, long lBufferSize)
	{
		if(OnChanging==false && ewc_s[i].wx!=0 && ewc_s[i].wy!=0){
			if(ewc_s[i].Initialized==true){
				DWORD	t=::GetComputerMiliSec();
				TimeDim[LastTimeIndex]=t-LastTime;
				LastTimeIndex++;
				if(LastTimeIndex>=100)
					LastTimeIndex=0;
				LastTime=t;

				if(ewc_s[i].bufsize!= lBufferSize && lBufferSize>0){
					EWC_Reallocate(i ,ewc_s[i].wx, ewc_s[i].wy);
					ewc_s[i].bufsize= lBufferSize;
				}
				int wx= ewc_s[i].wx;
				int wy= ewc_s[i].wy;
				int byte= lBufferSize/wy;
				/*
				//�摜�̏㉺���t�ɂ��ăR�s�[
				for(int y=0; y<wy; y++){
					memcpy((unsigned char *)ewc_s[i].pbuf+(wy-1-y)*byte, pBuffer+y*byte,byte);
				}
				*/
				//for(int y=0; y<wy; y++){
				//	memcpy((unsigned char *)ewc_s[i].pbuf+y*byte, pBuffer+y*byte,byte);
				//}
				//memcpy((unsigned char *)ewc_s[i].pbuf, pBuffer,byte*wy);
				memcpy((unsigned char *)ewc_s[i].pbuf, pBuffer,lBufferSize);
			}
			ewc_s[i].ftime= dblSampleTime - ewc_s[i].stime;
			ewc_s[i].stime= dblSampleTime;
			ewc_s[i].count++;	//�t���[���擾���̍X�Vv2.4
			ewc_s[i].Captured=true;
		}
		else{
			CallBackCount++;
		}
		return S_OK;
	}
	//�R���X�g���N�^	
	ewc_SampleGrabberCB(int num)
	{
		i=num;
		ewc_s[i].pbuf=ewc_s[i].buffer;
		ewc_s[i].bufsize=0;
		tm=ewc_s[i].stime=0.;
		ewc_s[i].Captured=false;
		OnChanging=false;
		LastTimeIndex	=0;
		CallBackCount=0;
	}
	//�f�X�g���N�^
	~ewc_SampleGrabberCB()
	{
	}
	void TimeSet(double *t)
	{
		*t= tm= ewc_s[i].stime;
	}
	int IsCaptured(void)
	{
		if(tm!=ewc_s[i].stime) return 1;
		else return 0;
	}
private:
	int i;
	double tm;
};

//IAMVideoProcAmp
#define EWC_BRIGHTNESS				0
#define EWC_CONTRAST				1
#define EWC_HUE						2
#define EWC_SATURATION				3
#define EWC_SHARPNESS				4
#define EWC_GAMMA					5
#define EWC_COLORENABLE				6
#define EWC_WHITEBALANCE			7
#define EWC_BACKLIGHTCOMPENSATION	8
#define EWC_GAIN					9
//IAMCameraControl
#define EWC_PAN						10
#define EWC_TILT					11
#define EWC_ROLL					12
#define EWC_ZOOM					13
#define EWC_EXPOSURE				14
#define EWC_IRIS					15
#define EWC_FOCUS					16

//�J�����ԍ��̃`�F�b�N(�߂��l�F0�Ȃ��J����num�͗L��)
int numCheck(int num)
{
	if(num<0 || num>=EWC_NCAMMAX) return 1;
	if(!ewc_s[num].init) return 2;
	return 0;
}

//�J�����䐔���Ԃ�
int EWC_GetCamera(void)
{
	if(ewc_ncam==-1) return 0;
	return ewc_ncam;
}

//�J����(�ԍ�:num)�̃t���[���o�b�t�@�T�C�Y(�P��:�o�C�g)���Ԃ�
int EWC_GetBufferSize(int num)
{
	if(numCheck(num)) return 0;
	return ewc_s[num].bufsize;
}

//�t�B���^�̃s�����擾����
IPin *ewc_GetPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir)
{
	IEnumPins *pEnum;
	IPin *pPin= 0;

	ewc_hr= pFilter->EnumPins(&pEnum);
	if(ewc_hr!=S_OK) return NULL;

	while(pEnum->Next(1,&pPin,0)==S_OK){
		PIN_DIRECTION PinDirThis;
		pPin->QueryDirection(&PinDirThis);
		if(PinDir==PinDirThis) break;
		pPin->Release();
	}
	pEnum->Release();
	return pPin;
}

//�J����(�ԍ�:num)�̉摜�擾
int EWC_GetImage(int num, void *buffer ,long *BuffSize)
{
	if(numCheck(num)) return 1;

	ewc_Mutex[num].lock();
	memcpy(buffer,ewc_s[num].pbuf,ewc_s[num].bufsize);
	if(BuffSize!=NULL){
		*BuffSize=ewc_s[num].bufsize;
	}
	ewc_Mutex[num].unlock();
	
	return 0;
}

//�o�b�t�@�A�h���X���ύX
int EWC_SetBuffer(int num, void *buffer)
{
	if(numCheck(num)) return 1;
	ewc_s[num].pbuf= (int *)buffer;
	return 0;
}

//���݂̃o�b�t�@�A�h���X���擾
int EWC_GetBuffer(int num, void **buffer)
{
	if(numCheck(num)) return 1;
	*buffer=ewc_s[num].pbuf;
	return 0;
}
bool	EWC_IsCaptured(int num)
{
	if(ewc_s[num].Captured==true){
		ewc_s[num].Captured=false;
		return true;
	}
	return false;
}

//�ݒ��l���ǂ񂾂菑�����肷���֐� v2.4
int ewc_propfunc(int func, int num, int prop, double *value=NULL, int *mode=NULL)
{
	if(numCheck(num)) return 1;
	if(prop<0 || prop>=EWC_ITEMMAX) return 2;
	if(!ewc_s[num].vflag[prop]) return 3;

	long Min, Max, Step, Default, CapsFlags, Flags, Val;   
	if(ewc_s[num].pCap==NULL)
		return 0;

	if(prop<EWC_VPAMPMAX){
		//IAMVideoProcAmp�̎擾 pVPAmp
		ewc_s[num].pCap->QueryInterface(IID_IAMVideoProcAmp,(void **)&ewc_s[num].pVPAmp);
		//IAMVideoProcAmp
		ewc_hr= ewc_s[num].pVPAmp->GetRange(prop,&Min,&Max,&Step,&Default,&CapsFlags);	//�͈͂̎擾
		if(ewc_hr==S_OK){
			ewc_hr= ewc_s[num].pVPAmp->Get(prop,&Val,&Flags);	//���ݒl�̎擾

			switch(func){
				case 0:	//�����l�ɖ߂�
					ewc_hr= ewc_s[num].pVPAmp->Set(prop,Default,Flags);
					break;
				case 1:	//�l���ݒ��C�蓮���[�h�֐ؑ�
					if(Step>0){
						Val= (long)((*value*(Max-Min)/100.0)+Min);
						Val= min(max(Val,Min),Max);
						Val= (Val/Step)*Step;
						ewc_hr= ewc_s[num].pVPAmp->Set(prop,Val,VideoProcAmp_Flags_Manual);
					}
					break;
				case 2:	//�l�̓ǂݏo��
					*value= (Val-Min)*100.0/(double)(Max-Min);
					if(mode) if(Flags & VideoProcAmp_Flags_Auto) *mode=1; else *mode=0;
					break;
				case 3:	//�蓮���[�h�ؑւ̂�
					ewc_hr= ewc_s[num].pVPAmp->Set(prop,Val,VideoProcAmp_Flags_Manual);
					break;
				case 4:	//�������[�h�ؑւ̂�
					ewc_hr= ewc_s[num].pVPAmp->Set(prop,Val,VideoProcAmp_Flags_Auto);
					break;
			}
			ewc_release(ewc_s[num].pVPAmp);
			if(ewc_hr!=S_OK) return 5;
		}else{
			ewc_release(ewc_s[num].pVPAmp);
			return 4;
		}
	}else{
		//IAMCameraControl�̎擾 pCamCtl
		ewc_s[num].pCap->QueryInterface(IID_IAMCameraControl,(void **)&ewc_s[num].pCamCtl);
		//IAMCameraControl
		prop -= EWC_VPAMPMAX;
		ewc_hr= ewc_s[num].pCamCtl->GetRange(prop,&Min,&Max,&Step,&Default,&CapsFlags);	//�͈͂̎擾
		if(ewc_hr==S_OK){
			ewc_hr= ewc_s[num].pCamCtl->Get(prop,&Val,&Flags);	//���ݒl�̎擾

			switch(func){
				case 0:	//�����l�ɖ߂�
					ewc_hr= ewc_s[num].pCamCtl->Set(prop,Default,Flags);
					break;
				case 1:	//�l���ݒ��C�蓮���[�h�֐ؑ�
					if(Step>0){
						Val= (long)((*value*(Max-Min)/100.0)+Min);
						Val= min(max(Val,Min),Max);
						Val= (Val/Step)*Step;
						ewc_hr= ewc_s[num].pCamCtl->Set(prop,Val,CameraControl_Flags_Manual);
					}
					break;
				case 2:	//�l�̓ǂݏo��
					*value= (Val-Min)*100.0/(double)(Max-Min);
					if(mode) if(Flags & CameraControl_Flags_Auto) *mode=1; else *mode=0;
					break;
				case 3:	//�蓮���[�h�ؑւ̂�
					ewc_hr= ewc_s[num].pCamCtl->Set(prop,Val,CameraControl_Flags_Manual);
					break;
				case 4:	//�������[�h�ؑւ̂�
					ewc_hr= ewc_s[num].pCamCtl->Set(prop,Val,CameraControl_Flags_Auto);
					break;
			}
			ewc_release(ewc_s[num].pCamCtl);
			if(ewc_hr!=S_OK) return 5;
		}else{
			ewc_release(ewc_s[num].pCamCtl);
			return 4;
		}
	}
	return 0;
}

int ewc_GetRange(int num, int prop, long &Min, long &Max, long &Step, long &Default, long &CapsFlags)
{
	if(numCheck(num)) return 1;
	if(prop<0 || prop>=EWC_ITEMMAX) return 2;
	if(!ewc_s[num].vflag[prop]) return 3;
	if(ewc_s[num].pCap==NULL)
		return 3;
	if(prop<EWC_VPAMPMAX){
		//IAMVideoProcAmp�̎擾 pVPAmp
		ewc_s[num].pCap->QueryInterface(IID_IAMVideoProcAmp,(void **)&ewc_s[num].pVPAmp);
		//IAMVideoProcAmp
		ewc_hr= ewc_s[num].pVPAmp->GetRange(prop,&Min,&Max,&Step,&Default,&CapsFlags);	//�͈͂̎擾
		if(ewc_hr!=S_OK){
			ewc_release(ewc_s[num].pVPAmp);
			return 4;
		}
	}else{
		//IAMCameraControl�̎擾 pCamCtl
		ewc_s[num].pCap->QueryInterface(IID_IAMCameraControl,(void **)&ewc_s[num].pCamCtl);
		//IAMCameraControl
		prop -= EWC_VPAMPMAX;
		ewc_hr= ewc_s[num].pCamCtl->GetRange(prop,&Min,&Max,&Step,&Default,&CapsFlags);	//�͈͂̎擾
		if(ewc_hr!=S_OK){
			ewc_release(ewc_s[num].pCamCtl);
			return 4;
		}
	}
	return 0;
}

long ewc_GetValueDirect(int num, int prop, long &CapsFlags)
{
	if(numCheck(num)) return 1;
	if(prop<0 || prop>=EWC_ITEMMAX) return 2;
	if(!ewc_s[num].vflag[prop]) return 3;

	long Min, Max, Step, Default, Val, Flags;   
	if(ewc_s[num].pCap==NULL)	return 3;

	if(prop<EWC_VPAMPMAX){
		//IAMVideoProcAmp�̎擾 pVPAmp
		ewc_s[num].pCap->QueryInterface(IID_IAMVideoProcAmp,(void **)&ewc_s[num].pVPAmp);
		//IAMVideoProcAmp
		ewc_hr= ewc_s[num].pVPAmp->GetRange(prop,&Min,&Max,&Step,&Default,&CapsFlags);	//�͈͂̎擾
		if(ewc_hr==S_OK){
			ewc_hr= ewc_s[num].pVPAmp->Get(prop,&Val,&Flags);	//���ݒl�̎擾
			ewc_release(ewc_s[num].pVPAmp);
			if(ewc_hr!=S_OK) return 99999999;
		}else{
			ewc_release(ewc_s[num].pVPAmp);
			return 99999999;
		}
	}else{
		//IAMCameraControl�̎擾 pCamCtl
		ewc_s[num].pCap->QueryInterface(IID_IAMCameraControl,(void **)&ewc_s[num].pCamCtl);
		//IAMCameraControl
		prop -= EWC_VPAMPMAX;
		ewc_hr= ewc_s[num].pCamCtl->GetRange(prop,&Min,&Max,&Step,&Default,&CapsFlags);	//�͈͂̎擾
		if(ewc_hr==S_OK){
			ewc_hr= ewc_s[num].pCamCtl->Get(prop,&Val,&Flags);	//���ݒl�̎擾
			ewc_release(ewc_s[num].pCamCtl);
			if(ewc_hr!=S_OK) return 99999999;
		}else{
			ewc_release(ewc_s[num].pCamCtl);
			return 99999999;
		}
	}
	return Val;
}

int ewc_SetValueDirect(int num, int prop, long Val)
{
	if(numCheck(num)) return 1;
	if(prop<0 || prop>=EWC_ITEMMAX) return 2;
	if(!ewc_s[num].vflag[prop]) return 3;

	long Min, Max, Step, Default, CapsFlags, Flags;   

	if(ewc_s[num].pCap!=NULL){
		if(prop<EWC_VPAMPMAX){
			//IAMVideoProcAmp�̎擾 pVPAmp
			ewc_s[num].pCap->QueryInterface(IID_IAMVideoProcAmp,(void **)&ewc_s[num].pVPAmp);
			//IAMVideoProcAmp
			ewc_hr= ewc_s[num].pVPAmp->GetRange(prop,&Min,&Max,&Step,&Default,&CapsFlags);	//�͈͂̎擾
			if(ewc_hr==S_OK){
				long tVal;
				ewc_hr= ewc_s[num].pVPAmp->Get(prop,&tVal,&Flags);	//���ݒl�̎擾
				ewc_hr= ewc_s[num].pVPAmp->Set(prop,Val,VideoProcAmp_Flags_Manual);
				ewc_release(ewc_s[num].pVPAmp);
				if(ewc_hr!=S_OK) return 5;
			}else{
				ewc_release(ewc_s[num].pVPAmp);
				return 4;
			}
		}else{
			//IAMCameraControl�̎擾 pCamCtl
			ewc_s[num].pCap->QueryInterface(IID_IAMCameraControl,(void **)&ewc_s[num].pCamCtl);
			//IAMCameraControl
			prop -= EWC_VPAMPMAX;
			ewc_hr= ewc_s[num].pCamCtl->GetRange(prop,&Min,&Max,&Step,&Default,&CapsFlags);	//�͈͂̎擾
			if(ewc_hr==S_OK){
				long tVal;
				ewc_hr= ewc_s[num].pCamCtl->Get(prop,&tVal,&Flags);	//���ݒl�̎擾
				ewc_hr= ewc_s[num].pCamCtl->Set(prop,Val,CameraControl_Flags_Manual);
				ewc_release(ewc_s[num].pCamCtl);
				if(ewc_hr!=S_OK) return 5;
			}else{
				ewc_release(ewc_s[num].pCamCtl);
				return 4;
			}
		}
	}
 	return 0;
}


//�ݒ��l���ǂݏo��
//  �I�v�V�����Fmode�ɂ�0(manual)�܂���1(auto)���i�[������
double EWC_GetValue(int num, int prop, int *mode=NULL)
{
	double v;
	if(mode) *mode=0;
	int r= ewc_propfunc(2, num, prop, &v, mode);
	if(r) return -1.0;
	else return v;
}

//�������蓮���[�h�ɐ؂��ւ��� v2.4
int EWC_SetManual(int num, int prop)
{
	return ewc_propfunc(3, num, prop);
}

//�ݒ��l���ύX����(v2.4����ewc_propfunc()���Ăяo���`�ɕύX)
int EWC_SetValue(int num, int prop, double value)
{
	return ewc_propfunc(1, num, prop, &value);
}

//�ݒ��������l�ɖ߂�(v2.4����ewc_propfunc()���Ăяo���`�ɕύX)
int EWC_SetDefault(int num, int prop)
{
	return ewc_propfunc(0, num, prop);
}

//�������������[�h�ɂ���(v2.4����ewc_propfunc()���Ăяo���`�ɕύX)
int EWC_SetAuto(int num, int prop)
{
	return ewc_propfunc(4, num, prop);
}

#pragma comment(lib,"Quartz.lib")

//�Ō��̃G���[���b�Z�[�W���擾����
//s:�������i�[��  size:�̈�s�̃T�C�Y
void EWC_GetLastMessage(char *s, int size)
{
	wchar_t w[MAX_ERROR_TEXT_LEN];
	AMGetErrorTextW(ewc_hr,w,MAX_ERROR_TEXT_LEN);	//1.9
	WideCharToMultiByte(CP_ACP,0,w,-1,s,size,NULL,NULL);
}

//�L���v�`���̒��~
int EWC_Stop(int num)
{
	if(numCheck(num)) return 1;

	//stop
	ewc_hr= ewc_s[num].pGraph->QueryInterface(IID_IMediaControl,(void **)&ewc_s[num].pMediaControl);
	if(ewc_hr==S_OK) ewc_s[num].pMediaControl->Stop(); else return 2;
	ewc_release(ewc_s[num].pMediaControl);

	long evCode;
	ewc_hr= ewc_s[num].pMediaEvent->WaitForCompletion(EWC_STOP_TIMEOUT,&evCode);
	if(ewc_hr!=S_OK){
		if(ewc_hr==E_ABORT) return 3;
	}
	return 0;
}

//�L���v�`���̍ĊJ
int EWC_Run(int num)
{
	if(numCheck(num)) return 1;

	//run
	ewc_hr= ewc_s[num].pGraph->QueryInterface(IID_IMediaControl,(void **)&ewc_s[num].pMediaControl);
	if(ewc_hr==S_OK) ewc_hr= ewc_s[num].pMediaControl->Run(); else return 2;
	ewc_release(ewc_s[num].pMediaControl);

	long evCode;
	ewc_hr= ewc_s[num].pMediaEvent->WaitForCompletion(EWC_RUN_TIMEOUT,&evCode);
	if(ewc_hr!=S_OK){
		if(ewc_hr==E_ABORT) return 3;
	}
	return 0;
}

//�L���v�`����Pause v2.4
int EWC_Pause(int num)
{
	if(numCheck(num)) return 1;

	//pause
	ewc_hr= ewc_s[num].pGraph->QueryInterface(IID_IMediaControl,(void **)&ewc_s[num].pMediaControl);
	if(ewc_hr==S_OK) ewc_hr= ewc_s[num].pMediaControl->Pause(); else return 2;
	ewc_release(ewc_s[num].pMediaControl);

	long evCode;
	ewc_hr= ewc_s[num].pMediaEvent->WaitForCompletion(EWC_RUN_TIMEOUT,&evCode);
	if(ewc_hr!=S_OK){
		if(ewc_hr==E_ABORT) return 3;
	}
	return 0;
}

//�����V���b�g v2.4
int EWC_OneShot(int num)
{
	if(numCheck(num)) return 1;

	int c1,c2,c3;

	c1= ewc_s[num].count;
	EWC_Run(num);

	while((c2= ewc_s[num].count) == c1) Sleep(1);	//�P�t���[���̂Ă�
	while((c3= ewc_s[num].count) == c2) Sleep(1);
	EWC_Pause(num);

	return 0;
}

//�v���p�e�B�y�[�W���\��������
int EWC_PropertyPage(int num)
{
	if(numCheck(num)) return 1;

	ISpecifyPropertyPages *pProp=0;

	ewc_hr= ewc_s[num].pCap->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pProp);
	if(ewc_hr!=S_OK) return 2;

	CAUUID caGUID;
	pProp->GetPages(&caGUID);
	ewc_release(pProp);

	FILTER_INFO FilterInfo;
	ewc_hr= ewc_s[num].pCap->QueryFilterInfo(&FilterInfo); 
	if(ewc_hr!=S_OK) return 3;

	IUnknown *pFilterUnk=0;
	ewc_hr= ewc_s[num].pCap->QueryInterface(IID_IUnknown,(void **)&pFilterUnk);
	if(ewc_hr!=S_OK){
		ewc_release(FilterInfo.pGraph);
		return 4;
	}

	OleCreatePropertyFrame(
		HWND_DESKTOP,		// Parent window
		0,0,				// Reserved
		FilterInfo.achName,	// Caption for the dialog box
		1,					// Number of objects (just the filter)
		&pFilterUnk,		// Array of object pointers. 
		caGUID.cElems,		// Number of property pages
		caGUID.pElems,		// Array of property page CLSIDs
		0,					// Locale identifier
		0, NULL				// Reserved
	);

	ewc_release(pFilterUnk);
	ewc_release(FilterInfo.pGraph);
	CoTaskMemFree(caGUID.pElems);
	return 0;
}

//�V�����摜�������������ǂ���
//  num:�J�����ԍ�  t:�擾����(�b)
/*
int EWC_IsCaptured(int num, double *t=NULL)
{
	if(numCheck(num)) return 0;

	if(ewc_pSampleGrabberCB[num]->IsCaptured()){
		double tt;
		if(!t) t= &tt;
		ewc_pSampleGrabberCB[num]->TimeSet(t);
		return 1;
	}
	return 0;
}
*/

//�摜�ϊ�(32�r�b�g->24�r�b�g)
void EWC_Cnv32to24(unsigned char *dst, unsigned int *src, int pxl)
{
	unsigned char R,G,B;
	unsigned int ui;

	for(int n=0; n<pxl; n++){
		ui= *src++;
		B= ui;
		G= ui>>8;
		R= ui>>16;
		*(dst+0)= B;
		*(dst+1)= G;
		*(dst+2)= R;
		dst += 3;
	}
}

//�摜�ϊ�(24�r�b�g->32�r�b�g)
void EWC_Cnv24to32(unsigned int *dst, unsigned char *src, int pxl)
{
	unsigned char R,G,B;

	for(int n=0; n<pxl; n++){
		B = *(src+0);
		G = *(src+1);
		R = *(src+2);
		src += 3;
		*dst++ = (R<<16) | (G<<8) | B;
	}
}

//���f�B�A�T�u�^�C�v��GUID�l�ɑΉ������������𓾂� v2.3
#include <wmsdkidl.h>
int EWC_GUIDtoTEXT(GUID guid, char *s, int size)
{
		 if(guid == MEDIASUBTYPE_YUY2) strcpy_s(s,size,"YUY2");
	else if(guid == MEDIASUBTYPE_MJPG) strcpy_s(s,size,"MJPG");
	else if(guid == MEDIASUBTYPE_H264) strcpy_s(s,size,"H264");
	else if(guid == MEDIASUBTYPE_IYUV) strcpy_s(s,size,"IYUV");
	else if(guid == MEDIASUBTYPE_RGB24) strcpy_s(s,size,"RGB24");
	else if(guid == MEDIASUBTYPE_RGB32) strcpy_s(s,size,"RGB32");
	else if(guid == WMMEDIASUBTYPE_I420) strcpy_s(s,size,"I420");
	else if(guid == MEDIASUBTYPE_RGB555) strcpy_s(s,size,"RGB555");
	else{
		char ss[80];
		sprintf_s(ss,sizeof(ss),"%X",guid.Data1);
		strcpy_s(s,size,ss);
		return 1;
	}
	return 0;
}

//���������� v2.2
void ewc_freememory(int num)
{
	if(ewc_s[num].devn!=-1) ewc_used[ewc_s[num].devn]=0;	//v2.2
	ewc_release(ewc_s[num].pMediaEvent);
	ewc_release(ewc_s[num].pMediaControl);
	ewc_release(ewc_s[num].pCamCtl);
	ewc_release(ewc_s[num].pVPAmp);
	ewc_release(ewc_s[num].pGrab);
	ewc_release(ewc_s[num].pF);
	ewc_release(ewc_s[num].pBuilder);
	ewc_release(ewc_s[num].pCap);
	if(ewc_s[num].buffer){
		delete[] ewc_s[num].buffer;
		ewc_s[num].buffer= 0;
	}
	ewc_release(ewc_s[num].pGraph);
	if(ewc_pSampleGrabberCB[num]){	//v2.1
		delete ewc_pSampleGrabberCB[num];
		ewc_pSampleGrabberCB[num]= 0;
	}
}

int	StrHexToInt(char c)
{
	switch(c){
	case '0':	return 0;
	case '1':	return 1;
	case '2':	return 2;
	case '3':	return 3;
	case '4':	return 4;
	case '5':	return 5;
	case '6':	return 6;
	case '7':	return 7;
	case '8':	return 8;
	case '9':	return 9;
	case 'A':	return 0x0a;
	case 'a':	return 0x0a;
	case 'B':	return 0x0b;
	case 'b':	return 0x0b;
	case 'C':	return 0x0c;
	case 'c':	return 0x0c;
	case 'D':	return 0x0d;
	case 'd':	return 0x0d;
	case 'E':	return 0x0e;
	case 'e':	return 0x0e;
	case 'F':	return 0x0f;
	case 'f':	return 0x0f;
	default:	return -1;
	}
}

bool ewc_EnumCameras(int &CameraCount ,int RetVendorID[] ,int RetProductID[])
{
	int errcode;
	ewc_struct	ewc;
	ewc.devn= -1;
	int t0= 0;
	int n= 0;		//�f�o�C�X���̃J�E���g�p

	errcode= 0;

	//�t�B���^�O���t�}�l�[�W���쐬 pGraph
	ewc_hr= CoCreateInstance(CLSID_FilterGraph,0,CLSCTX_INPROC_SERVER,IID_IGraphBuilder,(void **)&ewc.pGraph);
	if(ewc_hr!=S_OK){errcode=(int)ewc_hr; return false;}

	//�V�X�e���f�o�C�X�񋓎q�̍쐬
	ewc_hr= CoCreateInstance(CLSID_SystemDeviceEnum,0,CLSCTX_INPROC_SERVER,IID_ICreateDevEnum,(void **)&ewc.pDevEnum);
	if(ewc_hr!=S_OK){errcode=4; return false;}

	//�񋓎q�̎擾
	ewc_hr= ewc.pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&ewc.pEnum,0);
	if(ewc_hr!=S_OK){
		//ESP_Printf("No driver\n");
		errcode=5; return false;
	}

	//���j�J�̎擾
	ULONG cFetched;
	wchar_t SrcName[32];
	ewc_used[n]=0;

	for(int i=0; i<EWC_NCAMMAX; i++){
		if(ewc.pEnum->Next(1,&ewc.pMoniker,&cFetched)==S_OK){
		
			//DisplayName�̎擾
			LPOLESTR strMonikerName=0;
			ewc_hr= ewc.pMoniker->GetDisplayName(NULL,NULL,&strMonikerName);
			if(ewc_hr==S_OK){

				//char displayname[1024];
				//WideCharToMultiByte(CP_ACP,0,strMonikerName,-1,displayname,sizeof(displayname),0,0);
				//ESP_Printf("displayname(%d):%s\n",i,displayname);

				int cntflag= 0;		//�f�o�C�X�Ƃ��ăJ�E���g���ׂ���
				if(wcsstr(strMonikerName,L"@device:pnp")!=NULL) cntflag= 1;	//DisplayName��'@device:pnp'������
				if(wcsstr(strMonikerName,L"@device:sw" )!=NULL) cntflag= 1;	//DisplayName��'@device:sw'������

				if(cntflag){
					char devname[256];	//FriendlyName�i�[�p

					//FriendlyName�̎擾
					IPropertyBag *pBag= 0;
					ewc.pMoniker->BindToStorage(0,0,IID_IPropertyBag,(void **)&pBag);
					VARIANT var;
					VariantInit(&var);
					var.vt= VT_BSTR;
					pBag->Read(L"FriendlyName",&var,0);
					WideCharToMultiByte(CP_ACP,0,var.bstrVal,-1,devname,sizeof(devname),0,0);
					VariantClear(&var);

					char DevicePathName[1024];
					VARIANT dvar;
					VariantInit(&dvar);
					dvar.vt= VT_BSTR;
					pBag->Read(L"DevicePath",&dvar,0);
					WideCharToMultiByte(CP_ACP,0,dvar.bstrVal,-1,DevicePathName,sizeof(DevicePathName),0,0);
					VariantClear(&dvar);
					int	VendorID=0;
					int	ProductID=0;
					char	*vid=strstr(DevicePathName,"vid_");
					if(vid!=NULL){
						vid+=4;
						for(int i=0;i<4;i++){
							int	dn=StrHexToInt(*vid);
							vid++;
							if(dn<0)
								break;
							VendorID*=16;
							VendorID+=dn;
						}
					}
					RetVendorID[n]=VendorID;
					char	*pid=strstr(DevicePathName,"pid_");
					if(pid!=NULL){
						pid+=4;
						for(int i=0;i<4;i++){
							int	dn=StrHexToInt(*pid);
							pid++;
							if(dn<0)
								break;
							ProductID*=16;
							ProductID+=dn;
						}
					}
					RetProductID[n]=ProductID;

					ewc_release(pBag);

					//�I�u�W�F�N�g������ pCap
					ewc.pMoniker->BindToObject(0,0,IID_IBaseFilter,(void **)&ewc.pCap);
						//�O���t�Ƀt�B���^���ǉ�
					swprintf_s(SrcName,32,L"Video Capture %d",i);
					ewc_hr= ewc.pGraph->AddFilter(ewc.pCap, SrcName);
					if(ewc_hr!=S_OK){errcode=7; goto fin;}

					n++;

					fin:;
				}
				ewc_release(ewc.pMoniker);
			}
		}
	}
	CameraCount=n;

	return true;
}




//�g�p�J�n(EWC_Open()�����Ă΂���) v2.3
bool ewc_Open(int num ,int &VendorID ,int &ProductID)
{
	int errcode, retryflag, retrytime= EWC_RETRYTIMES;
	ewc_s[num].devn= -1;
	int t0= 0;
	VIDEOINFOHEADER *vh= NULL;
	int regflag= 0;	//�o�^������

cont:
	int n= 0;		//�f�o�C�X���̃J�E���g�p
	retryflag= 0;
	errcode= 0;

	//�t�B���^�O���t�}�l�[�W���쐬 pGraph
	ewc_hr= CoCreateInstance(CLSID_FilterGraph,0,CLSCTX_INPROC_SERVER,IID_IGraphBuilder,(void **)&ewc_s[num].pGraph);
	if(ewc_hr!=S_OK){errcode=(int)ewc_hr; goto fin;}

	//�V�X�e���f�o�C�X�񋓎q�̍쐬
	ewc_hr= CoCreateInstance(CLSID_SystemDeviceEnum,0,CLSCTX_INPROC_SERVER,IID_ICreateDevEnum,(void **)&ewc_s[num].pDevEnum);
	if(ewc_hr!=S_OK){errcode=4; goto fin;}

	//�񋓎q�̎擾
	ewc_hr= ewc_s[num].pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&ewc_s[num].pEnum,0);
	if(ewc_hr!=S_OK){
		//ESP_Printf("No driver\n");
		errcode=5; goto fin;
	}

	//���j�J�̎擾
	ULONG cFetched;
	wchar_t SrcName[32];
	ewc_used[n]=0;

	for(int i=0; i<EWC_NCAMMAX; i++){
		if(ewc_s[num].pEnum->Next(1,&ewc_s[num].pMoniker,&cFetched)==S_OK){
			if(n!=num){
				n++;
				continue;
			}
			
			//DisplayName�̎擾
			LPOLESTR strMonikerName=0;
			ewc_hr= ewc_s[num].pMoniker->GetDisplayName(NULL,NULL,&strMonikerName);
			if(ewc_hr!=S_OK){errcode=6; goto fin;}

			//char displayname[1024];
			//WideCharToMultiByte(CP_ACP,0,strMonikerName,-1,displayname,sizeof(displayname),0,0);
			//ESP_Printf("displayname(%d):%s\n",i,displayname);

			int cntflag= 0;		//�f�o�C�X�Ƃ��ăJ�E���g���ׂ���
			if(wcsstr(strMonikerName,L"@device:pnp")!=NULL) cntflag= 1;	//DisplayName��'@device:pnp'������
			if(wcsstr(strMonikerName,L"@device:sw" )!=NULL) cntflag= 1;	//DisplayName��'@device:sw'������

			if(cntflag){
				char devname[256];	//FriendlyName�i�[�p

				//FriendlyName�̎擾
				IPropertyBag *pBag= 0;
				ewc_s[num].pMoniker->BindToStorage(0,0,IID_IPropertyBag,(void **)&pBag);
				VARIANT var;
				VariantInit(&var);
				var.vt= VT_BSTR;
				if(pBag->Read(L"FriendlyName",&var,0)!=S_OK){errcode=9; goto fin;}
				WideCharToMultiByte(CP_ACP,0,var.bstrVal,-1,devname,sizeof(devname),0,0);
				VariantClear(&var);

				char DevicePathName[1024];
				VARIANT dvar;
				VariantInit(&dvar);
				dvar.vt= VT_BSTR;
				if(pBag->Read(L"DevicePath",&dvar,0)!=S_OK){errcode=9; goto fin;}
				WideCharToMultiByte(CP_ACP,0,dvar.bstrVal,-1,DevicePathName,sizeof(DevicePathName),0,0);
				VariantClear(&dvar);
				VendorID=0;
				ProductID=0;
				char	*vid=strstr(DevicePathName,"vid_");
				if(vid!=NULL){
					vid+=4;
					for(int i=0;i<4;i++){
						int	dn=StrHexToInt(*vid);
						vid++;
						if(dn<0)
							break;
						VendorID*=16;
						VendorID+=dn;
					}
				}
				char	*pid=strstr(DevicePathName,"pid_");
				if(pid!=NULL){
					pid+=4;
					for(int i=0;i<4;i++){
						int	dn=StrHexToInt(*pid);
						pid++;
						if(dn<0)
							break;
						ProductID*=16;
						ProductID+=dn;
					}
				}

				ewc_release(pBag);

				int match= 0;	//�o�^�����ɍ��v������
				if(ewc_s[num].pdname){
					//�f�C�o�X���w���̏ꍇ
					if(strstr(devname,ewc_s[num].pdname)) match=1;		//FriendlyName�ƍ�
				}else{
					//�f�C�o�X�ԍ��w���܂��͏ȗ���
					match=1;
				}
				//�����������Γo�^
				if(!regflag && !ewc_used[n] && match){
					//�I�u�W�F�N�g������ pCap
					ewc_s[num].pMoniker->BindToObject(0,0,IID_IBaseFilter,(void **)&ewc_s[num].pCap);
					//�O���t�Ƀt�B���^���ǉ�
					swprintf_s(SrcName,32,L"Video Capture %d",num);
					ewc_hr= ewc_s[num].pGraph->AddFilter(ewc_s[num].pCap, SrcName);
					if(ewc_hr!=S_OK){errcode=7; goto fin;}
					regflag++;
					ewc_s[num].devn= n;
					strcpy_s(ewc_s[num].dname, sizeof(ewc_s[num].dname), devname);	//FriendlyName�ۑ�
					ewc_used[n]= 1; 
				}
				n++;
			}
			ewc_release(ewc_s[num].pMoniker);
		}
	}

	if(ewc_ncam==-1) ewc_ncam= n;	//�J�������̓o�^

	ewc_release(ewc_s[num].pEnum);
	ewc_release(ewc_s[num].pDevEnum);

	if(!ewc_ncam){errcode=8; goto fin;}	//�J�������Ȃ�
	if(!regflag){errcode=9; goto fin;}	//�o�^�������̂��Ȃ�����

	//ESP_Printf("camera=%d\n",ewc_ncam);

	//�L���v�`���r���_�̍쐬 pBuilder
	CoCreateInstance(CLSID_CaptureGraphBuilder2,0,CLSCTX_INPROC_SERVER,
		IID_ICaptureGraphBuilder2,(void **)&ewc_s[num].pBuilder);
	ewc_hr= ewc_s[num].pBuilder->SetFiltergraph(ewc_s[num].pGraph);
	if(ewc_hr!=S_OK){errcode=10; goto fin;}
	
	//IAMStreamConfig�C���^�t�F�[�X�̎擾
	ewc_hr= ewc_s[num].pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Video,
		ewc_s[num].pCap,IID_IAMStreamConfig,(void**)&ewc_s[num].pConfig);
	if(ewc_hr!=S_OK){errcode=11; goto fin;}

	int	size;
	int	count;
	ewc_hr=  ewc_s[num].pConfig->GetNumberOfCapabilities(&count,&size);

	int	m=0;
	ewc_format fmt[100];
	for(int i=0; i<count; i++){
		VIDEO_STREAM_CONFIG_CAPS scc;
		AM_MEDIA_TYPE *pmt;
		ewc_hr=  ewc_s[num].pConfig->GetStreamCaps(i,&pmt,reinterpret_cast<BYTE*>(&scc)); 
		if(ewc_hr==S_OK && (pmt->formattype==FORMAT_VideoInfo)){	// || pmt->formattype==FORMAT_VideoInfo2)){
			VIDEOINFOHEADER *vh= reinterpret_cast<VIDEOINFOHEADER*>(pmt->pbFormat);
			fmt[m].width= vh->bmiHeader.biWidth;
			fmt[m].height= vh->bmiHeader.biHeight;
			fmt[m].bit= vh->bmiHeader.biBitCount;
			fmt[m].AvgTimePerFrame= vh->AvgTimePerFrame;
			fmt[m].fps= 10000000./vh->AvgTimePerFrame;
			fmt[m].subtype= pmt->subtype;
			EWC_GUIDtoTEXT(fmt[m].subtype, fmt[m].subtype_t, sizeof(fmt[m].subtype_t));	//v2.3
			ewc_DeleteMediaType(pmt);
			m++;
			if(m >= 100) break;
		} 
	}
	bool	Found=false;
	for(int h=0;h<m;h++){
		if(ewc_wx==fmt[h].width && ewc_wy==fmt[h].height){
			Found=true;
			break;
		}
	}
	if(Found==false){
		ewc_wx=fmt[0].width;
		ewc_wy=fmt[0].height;
	}
	else if(VendorID!=0xa007){
		ewc_wx=fmt[0].width;
		ewc_wy=fmt[0].height;
	}

	//�摜�T�C�Y�C�t���[�����[�g�̐ݒ�
	ewc_hr= ewc_s[num].pConfig->GetFormat(&ewc_s[num].pmt);
	vh= (VIDEOINFOHEADER*)ewc_s[num].pmt->pbFormat;
	//if(ewc_s[num].wx==0) ewc_s[num].wx= (ProductID==ProductID835 && ewc_wx==EWC_WX)?640:ewc_wx;		//�f�t�H���g�l�̓K�p
	//if(ewc_s[num].wy==0) ewc_s[num].wy= (ProductID==ProductID835 && ewc_wy==EWC_WY)?480:ewc_wy;		//�f�t�H���g�l�̓K�p
	if(ewc_s[num].wx==0) ewc_s[num].wx= ewc_wx;		//�f�t�H���g�l�̓K�p
	if(ewc_s[num].wy==0) ewc_s[num].wy= ewc_wy;		//�f�t�H���g�l�̓K�p
	if(ewc_s[num].fps==0) ewc_s[num].fps= ewc_fps;	//�f�t�H���g�l�̓K�p
	
	ewc_wx= ewc_s[num].wx;		//�f�t�H���g�l�̍X�V
	ewc_wy= ewc_s[num].wy;		//�f�t�H���g�l�̍X�V
	ewc_fps= ewc_s[num].fps;	//�f�t�H���g�l�̍X�V
	vh->bmiHeader.biWidth = ewc_s[num].wx;
	vh->bmiHeader.biHeight= ewc_s[num].wy; 
	vh->AvgTimePerFrame= (LONGLONG)floor((10000000.0/ewc_s[num].fps+0.5));

	//�f�o�C�X�o�̓s���̃t�H�[�}�b�g�w��v2.3
	if(ewc_s[num].dev_mstype!=GUID_NULL){
		ewc_s[num].pmt->subtype= ewc_s[num].dev_mstype;
	}
	ewc_s[num].dev_mstype= ewc_s[num].pmt->subtype;
	/*
	int	MaxFPS=0;
	for(int h=0;h<m;h++){
		if(ewc_wx==fmt[h].width && ewc_wy==fmt[h].height){
			if(MaxFPS<fmt[h].fps){
				ewc_s[num].dev_mstype=fmt[h].subtype;
				MaxFPS=fmt[h].fps;
			}
		}
	}
	*/

	//�t�H�[�}�b�g�ɑΉ����镶�����̐ݒ�v2.3
	EWC_GUIDtoTEXT(ewc_s[num].mstype, ewc_s[num].mstype_t, sizeof(ewc_s[num].mstype_t));
	EWC_GUIDtoTEXT(ewc_s[num].dev_mstype, ewc_s[num].dev_mstype_t, sizeof(ewc_s[num].dev_mstype_t));

	ewc_hr= ewc_s[num].pConfig->SetFormat(ewc_s[num].pmt);
	if(ewc_hr!=S_OK){errcode=12; goto fin;}
	ewc_release(ewc_s[num].pConfig);

	//�T���v���O���o�̐��� pF,pGrab
	CoCreateInstance(CLSID_SampleGrabber,0,CLSCTX_INPROC_SERVER,IID_IBaseFilter,(LPVOID *)&ewc_s[num].pF);
	ewc_hr= ewc_s[num].pF->QueryInterface(IID_ISampleGrabber,(void **)&ewc_s[num].pGrab);
	if(ewc_hr!=S_OK){errcode=13; goto fin;}

	//���f�B�A�^�C�v�̐ݒ�
	ZeroMemory(&ewc_s[num].mt,sizeof(AM_MEDIA_TYPE));
	ewc_s[num].mt.majortype= MEDIATYPE_Video;
	ewc_s[num].mt.subtype= ewc_s[num].mstype;
	ewc_type= ewc_s[num].mstype;	//�f�t�H���g�l�̍X�V
	ewc_s[num].mt.formattype= FORMAT_VideoInfo;
	ewc_hr= ewc_s[num].pGrab->SetMediaType(&ewc_s[num].mt);
	if(ewc_hr!=S_OK){errcode=14; goto fin;}
	//�t�B���^�O���t�ւ̒ǉ�
	wchar_t GrabName[32];
	swprintf_s(GrabName,32,L"Grabber %d",num);
	ewc_hr= ewc_s[num].pGraph->AddFilter(ewc_s[num].pF, GrabName);
	if(ewc_hr!=S_OK){errcode=15; goto fin;}

	//�T���v���O���o�̐ڑ�
	// �s���̎擾
	ewc_s[num].pSrcOut= ewc_GetPin(ewc_s[num].pCap,PINDIR_OUTPUT);
	ewc_s[num].pSGrabIn= ewc_GetPin(ewc_s[num].pF,PINDIR_INPUT);
	// �s���̐ڑ�
	ewc_hr= ewc_s[num].pGraph->Connect(ewc_s[num].pSrcOut, ewc_s[num].pSGrabIn);
	if(ewc_hr!=S_OK){errcode=16; goto fin;}

	ewc_release(ewc_s[num].pSrcOut);
	ewc_release(ewc_s[num].pSGrabIn);

	//�O���o�̃��[�h�ݒ�
	ewc_hr= ewc_s[num].pGrab->SetBufferSamples(FALSE);
	if(ewc_hr!=S_OK){errcode=17; goto fin;}
	ewc_hr= ewc_s[num].pGrab->SetOneShot(FALSE);
	if(ewc_hr!=S_OK){errcode=18; goto fin;}

	//�o�b�t�@�̊m�ہC�R�[���o�b�N�֐��̓o�^ buffer,ewc_pSampleGrabberCB[]
	ewc_s[num].bufsize=0;
	ewc_s[num].buffer= (int *)new int[ewc_s[num].wx*ewc_s[num].wy];
	ewc_s[num].AllocatedX=ewc_s[num].wx;
	ewc_s[num].AllocatedY=ewc_s[num].wy;
	ewc_pSampleGrabberCB[num]= new ewc_SampleGrabberCB(num);
	ewc_hr= ewc_s[num].pGrab->SetCallback(ewc_pSampleGrabberCB[num],1);
	if(ewc_hr!=S_OK){errcode=19; goto fin;}

	//IAMVideoProcAmp�̎擾 pVPAmp
	ewc_hr= ewc_s[num].pCap->QueryInterface(IID_IAMVideoProcAmp,(void **)&ewc_s[num].pVPAmp);
	if(ewc_hr!=S_OK){
		//IAMVideoProcAmp���擾�ł��Ȃ����΁C�T�|�[�g���ĂȂ��Ƃ݂Ȃ��D
		for(int j=0;j<EWC_VPAMPMAX;j++){
			//not supported
			ewc_s[num].vflag[j]= 0;
		}
	}else{
		for(int j=0;j<EWC_VPAMPMAX;j++){
			long Min, Max, Step, Default, Flags;   
			ewc_hr= ewc_s[num].pVPAmp->GetRange(j,&Min,&Max,&Step,&Default,&Flags);
			if(ewc_hr==S_OK){
				ewc_s[num].vflag[j]= 1;
			}else{
				//not supported
				ewc_s[num].vflag[j]= 0;
			}
		}
	}
	ewc_release(ewc_s[num].pVPAmp);

	//IAMCameraControl�̎擾 pCamCtl
	ewc_hr= ewc_s[num].pCap->QueryInterface(IID_IAMCameraControl,(void **)&ewc_s[num].pCamCtl);
	if(ewc_hr!=S_OK){
		//IAMCameraControl���擾�ł��Ȃ����΁C�T�|�[�g���ĂȂ��Ƃ݂Ȃ��D
		for(int j=0;j<EWC_CAMCTLMAX;j++){
			//not supported
			ewc_s[num].vflag[j+EWC_VPAMPMAX]= 0;
		}
	}else{
		for(int j=0;j<EWC_CAMCTLMAX;j++){
			long Min, Max, Step, Default, Flags;   
			ewc_hr= ewc_s[num].pCamCtl->GetRange(j,&Min,&Max,&Step,&Default,&Flags);
			if(ewc_hr==S_OK){
				ewc_s[num].vflag[j+EWC_VPAMPMAX]= 1;
			}else{
				//not supported
				ewc_s[num].vflag[j+EWC_VPAMPMAX]= 0;
			}
		}
	}
	ewc_release(ewc_s[num].pCamCtl);

	//IMediaEvent�̎擾 pMediaEvent
	ewc_hr= ewc_s[num].pGraph->QueryInterface(IID_IMediaEvent,(LPVOID *)&ewc_s[num].pMediaEvent);
	if(ewc_hr!=S_OK){errcode=20; goto fin;}

	//�L���v�`���J�n pMediaControl
	ewc_hr= ewc_s[num].pGraph->QueryInterface(IID_IMediaControl,(void **)&ewc_s[num].pMediaControl);
	if(ewc_hr!=S_OK){errcode=21; goto fin;}
	ewc_hr= ewc_s[num].pMediaControl->Run();
	if(ewc_hr!=S_OK){	errcode=22;
						OAFilterState pfs;
						HRESULT Ret=ewc_s[num].pMediaControl->GetState(1000,&pfs);
						retryflag=1; 
						goto fin;}
	ewc_release(ewc_s[num].pMediaControl);

	//�P���ȏ��T���v���������܂őҋ@
	long evCode;
	ewc_s[num].pMediaEvent->WaitForCompletion(EWC_RUN_TIMEOUT,&evCode);
	if(ewc_hr!=S_OK){
		if(ewc_hr==E_ABORT){errcode=23; retryflag=1; goto fin;}
	}
	t0= GetTickCount();
	do{
		if((GetTickCount()-t0)>EWC_RUN_TIMEOUT){errcode=24; retryflag=1; goto fin;}
	}while(ewc_s[num].count==0);

fin:
	ewc_s[num].init=0;
	if(errcode){
		//ESP_Printf("errcode=%d\n",errcode);
		ewc_release(ewc_s[num].pDevEnum);
		ewc_release(ewc_s[num].pEnum);
		ewc_release(ewc_s[num].pMoniker);
		ewc_release(ewc_s[num].pConfig);
		ewc_freememory(num);

		//�����ɐڑ��������܂Ń��g���C
		if(retryflag) if(--retrytime) goto cont;
	}else{
		ewc_s[num].init= 1;
		ewc_order[ewc_ordercnt++]= num;
	}

	ewc_s[num].errcode= errcode;
	if(errcode)
		return false;
	return true;
}

void	SetFrameRate(double FPS)
{
	IAMTimelineObj* obj;
	IAMTimeline* tline;
	
	CoCreateInstance(CLSID_AMTimeline, NULL, CLSCTX_INPROC_SERVER,
	IID_IAMTimeline, (void**)&tline);
	tline->CreateEmptyNode( &obj, TIMELINE_MAJOR_TYPE_GROUP );
	
	IAMTimelineGroup* group;
	obj->QueryInterface(IID_IAMTimelineGroup, (void**)&group);
	double dTmp;
	
	group->SetOutputFPS( FPS ); //�����悭�������ĂȂ��̂Ő��l�͓K���ł�
	tline->AddGroup( obj );
	
	///���������̂�1��1�̑Ή��őS�ĉ��������Y���Ȃ�(DirectX(��COM�H)�֘A�̃C���^�[�t�F�[�X��Release�֐��ŉ����Ƃ����̂������ł��B)///
	obj->Release();
	tline->Release();
	group->Release();
	
	
	///CoInitialize���Ăяo�������A������CoUninitialize�����̂����Y���Ȃ�///
	CoUninitialize();
}


//EWC_Open()�ōŏ��ɌĂ΂����T�u�֐�
void _ewc_open_pre(void)
{
	//COM�̏�����
	if(!ewc_cominit && ewc_ncam==-1){
		ewc_hr= CoInitializeEx(NULL,COINIT_MULTITHREADED);
		if(ewc_hr==S_OK) ewc_cominit=1;	//�����������t���O�𗧂Ă�
	}
	//�\���̂̏�����
	/*
	if(ewc_ncam==-1){
		for(int i=0; i<EWC_NCAMMAX; i++){
			ZeroMemory(&ewc_s[i],sizeof(ewc_struct));
		}
	}
	*/
}

//�g�p�J�n[1]�i�f�o�C�X�ԍ��w���jv2.3
int EWC_Open(int num, int wx=0, int wy=0, double fps=0, int device=-1, GUID mstype=ewc_type, GUID dev_mstype=ewc_device_type)
{
	if(num<0 || num>=EWC_NCAMMAX) return 1;

	_ewc_open_pre();

	if(ewc_s[num].init) return 2;

	ewc_s[num].wx= wx;
	ewc_s[num].wy= wy;
	ewc_s[num].fps= fps;
	ewc_s[num].device= device;
	ewc_s[num].pdname= NULL;
	ewc_s[num].mstype= mstype;
	ewc_s[num].dev_mstype= dev_mstype;
	ewc_s[num].errcode= -1;
	int VendorID;
	int ProductID;
	ewc_Open(num,VendorID ,ProductID);

	return ewc_s[num].errcode;
}

//�g�p�J�n[2]�i�f�o�C�X���w���jv2.3
int EWC_Open(int num, int wx, int wy, double fps, char *devicename, GUID mstype=ewc_type, GUID dev_mstype=ewc_device_type)
{
	if(num<0 || num>=EWC_NCAMMAX) return 1;

	_ewc_open_pre();

	if(ewc_s[num].init) return 2;

	ewc_s[num].wx= wx;
	ewc_s[num].wy= wy;
	ewc_s[num].fps= fps;
	ewc_s[num].device= -1;
	ewc_s[num].pdname= devicename;
	ewc_s[num].mstype= mstype;
	ewc_s[num].dev_mstype= dev_mstype;
	ewc_s[num].errcode= -1;
	int VendorID;
	int ProductID;
	ewc_Open(num,VendorID ,ProductID);

	return ewc_s[num].errcode;
}

//�g�p�J�n[3]�i�f�o�C�X���w���Cwx/wy/fps�ȗ��jv2.2
int EWC_Open(int num, char *devicename, GUID mstype=ewc_type, GUID dev_mstype=ewc_device_type)
{
	if(num<0 || num>=EWC_NCAMMAX) return 1;

	_ewc_open_pre();

	if(ewc_s[num].init) return 2;

	ewc_s[num].wx= 0;
	ewc_s[num].wy= 0;
	ewc_s[num].fps= 0;
	ewc_s[num].pdname= devicename;
	ewc_s[num].mstype= mstype;
	ewc_s[num].dev_mstype= dev_mstype;
	ewc_s[num].errcode= -1;
	int VendorID;
	int ProductID;
	ewc_Open(num,VendorID ,ProductID);

	return ewc_s[num].errcode;
}

//�I������
int EWC_Close(int num)
{
	if(numCheck(num)) return 1;

	//�L���v�`�����~
	int r= EWC_Stop(num);
	if(r) return 2;

	//����������
	ewc_freememory(num);
	ewc_s[num].init= 0;

	if(ewc_ordercnt){
		if(ewc_order[ewc_ordercnt-1]==num){
			ewc_ordercnt--;
		}
	}

	//���ׂďI���Ȃ�COM�I��
	int c=0;
	for(int i=0; i<EWC_NCAMMAX; i++){
		c += ewc_s[i].init;
	}
	if(c==0){
		if(ewc_cominit){
			CoUninitialize();
			ewc_cominit= 0;
		}
		ewc_ncam= -1;
	}
	return 0;
}

//�I�������i���ׂāj
int EWC_CloseAll(void)
{
	int r=0;
	while(ewc_ordercnt>0){
		r += EWC_Close(ewc_order[--ewc_ordercnt]);
	}
	return r;
}

int EWC_GetErrorCode(int num)
{
	return ewc_s[num].errcode;
}
bool	EWC_ReOpen(int SourceNo ,int XLen ,int YLen)
{
	ewc_Mutex[SourceNo].lock();
	if(ewc_pSampleGrabberCB[SourceNo]!=NULL){
		ewc_pSampleGrabberCB[SourceNo]->OnChanging=true;
	}
	GSleep(100);

	/*
	if(EWC_Close(SourceNo)!=0){
		ewc_Mutex[SourceNo].unlock();
		if(ewc_pSampleGrabberCB[SourceNo]!=NULL){
			ewc_pSampleGrabberCB[SourceNo]->OnChanging=false;
		}
		return false;
	}
	*/
	EWC_Close(SourceNo);

	GSleep(1000);
	ewc_freememory(SourceNo);
	if(EWC_Open(SourceNo, XLen, YLen)!=0){
		GSleep(2000);
		if(EWC_Open(SourceNo, XLen, YLen)!=0){
			ewc_Mutex[SourceNo].unlock();
			if(ewc_pSampleGrabberCB[SourceNo]!=NULL){
				ewc_pSampleGrabberCB[SourceNo]->OnChanging=false;
			}
			return false;
		}
	}
	ewc_Mutex[SourceNo].unlock();
	ewc_pSampleGrabberCB[SourceNo]->OnChanging=false;
	return true;
}

void EWC_Reallocate(int num ,int DotPerLine, int MaxLines)
{
	if(DotPerLine!=ewc_s[num].AllocatedX || MaxLines!=ewc_s[num].AllocatedY || ewc_s[num].buffer==NULL){
		int *B=(int *)new int[DotPerLine*MaxLines];
		int	*t=ewc_s[num].buffer;

		ewc_s[num].wx	=DotPerLine;
		ewc_s[num].wy	=MaxLines;
		ewc_s[num].buffer	=B;
		ewc_s[num].pbuf		=B;
		ewc_s[num].AllocatedX=DotPerLine;
		ewc_s[num].AllocatedY=MaxLines;

		//ewc_s[num].bufsize	=sizeof(int)*DotPerLine*MaxLines;
		ewc_s[num].bufsize	=0;
		if(t!=NULL){
			delete	[]t;
		}
	}
}


void ewc_FreeMediaType(AM_MEDIA_TYPE& mt)
{
	if(mt.cbFormat){
		CoTaskMemFree((PVOID)mt.pbFormat);
		mt.cbFormat= 0;
		mt.pbFormat= NULL;
	}
	if(mt.pUnk){
		ewc_release(mt.pUnk);
	}
}

void ewc_DeleteMediaType(AM_MEDIA_TYPE *pmt)
{
	if(pmt){
        ewc_FreeMediaType(*pmt); 
        CoTaskMemFree(pmt);
    }
}

//EWC_GetFormat()�����Ă΂���
int ewc_GetFormat(int device, char *pdname, ewc_format *fmt, int *nmax)
{
	IGraphBuilder *pGraph= 0;
	ICreateDevEnum *pDevEnum= 0;
	IEnumMoniker *pEnum= 0;
	ICaptureGraphBuilder2 *pBuilder= 0;
	IBaseFilter *pCap= 0;
	IAMStreamConfig *pConfig= 0;
	IMoniker *pMoniker= 0;

	int ewc_cominit_gf= 0;
	int errcode= 0;

	int count= 0, size= 0;
	int m= 0;	//�ŏI�I�ȃt�H�[�}�b�g��
				
	int n= 0;		//�f�o�C�X���̃J�E���g�p
	int regflag= 0;	//�o�^������
	
	//COM�̏�����
	if(!ewc_cominit){
		ewc_hr= CoInitializeEx(NULL,COINIT_MULTITHREADED);
		if(ewc_hr==S_OK) ewc_cominit_gf= 1;	//�����������t���O�𗧂Ă�
	}

	//�t�B���^�O���t�}�l�[�W���쐬 pGraph
	ewc_hr= CoCreateInstance(CLSID_FilterGraph,0,CLSCTX_INPROC_SERVER,IID_IGraphBuilder,(void **)&pGraph);
	if(ewc_hr!=S_OK){errcode=3; goto fin_gf;}

	//�V�X�e���f�o�C�X�񋓎q�̍쐬
	ewc_hr= CoCreateInstance(CLSID_SystemDeviceEnum,0,CLSCTX_INPROC_SERVER,IID_ICreateDevEnum,(void **)&pDevEnum);
	if(ewc_hr!=S_OK){errcode=4; goto fin_gf;}

	//�񋓎q�̎擾
	ewc_hr= pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&pEnum,0);
	if(ewc_hr!=S_OK){errcode=5; goto fin_gf;}

	//���j�J�̎擾
	ULONG cFetched;
	wchar_t SrcName[32];

	for(int i=0; i<EWC_NCAMMAX; i++){
		if(pEnum->Next(1,&pMoniker,&cFetched)==S_OK){
			
			//DisplayName�̎擾
			LPOLESTR strMonikerName=0;
			ewc_hr= pMoniker->GetDisplayName(NULL,NULL,&strMonikerName);
			if(ewc_hr!=S_OK){errcode=6; goto fin_gf;}

			int cntflag=0;		//�f�o�C�X�Ƃ��ăJ�E���g���ׂ���
			if(wcsstr(strMonikerName,L"@device:pnp")!=NULL) cntflag=1;	//DisplayName��'@device:pnp'������
			if(wcsstr(strMonikerName,L"@device:sw" )!=NULL) cntflag=1;	//DisplayName��'@device:sw'������

			if(cntflag){
				char devname[256];	//FriendlyName�i�[�p

				//FriendlyName�̎擾
				IPropertyBag *pBag= 0;
				pMoniker->BindToStorage(0,0,IID_IPropertyBag,(void **)&pBag);
				VARIANT var;
				VariantInit(&var);
				var.vt= VT_BSTR;
				pBag->Read(L"FriendlyName",&var,0);
				WideCharToMultiByte(CP_ACP,0,var.bstrVal,-1,devname,sizeof(devname),0,0);
				VariantClear(&var);
				ewc_release(pBag);

				int match= 0;	//�o�^�����ɍ��v������
				if(pdname){
					//�f�C�o�X���w���̏ꍇ
					if(strstr(devname,pdname)) match= 1;		//FriendlyName�ƍ�
				}else{
					//�f�C�o�X�ԍ��w���܂��͏ȗ���
					if(n==device) match= 1;
				}
				//�����������Γo�^
				if(!regflag && match){
					//�I�u�W�F�N�g������ pCap
					pMoniker->BindToObject(0,0,IID_IBaseFilter,(void **)&pCap);
					//�O���t�Ƀt�B���^���ǉ�
					swprintf_s(SrcName,32,L"Video Capture %d",i);
					ewc_hr= pGraph->AddFilter(pCap, SrcName);
					if(ewc_hr!=S_OK){errcode=7; goto fin_gf;}
					regflag++;
				}
				n++;
			}
			ewc_release(pMoniker);
		}
	}

	ewc_release(pEnum);
	ewc_release(pDevEnum);

	if(!regflag){errcode=9; goto fin_gf;}	//�o�^�������̂��Ȃ�����

	//�L���v�`���r���_�̍쐬 pBuilder
	CoCreateInstance(CLSID_CaptureGraphBuilder2,0,CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2,(void **)&pBuilder);
	ewc_hr= pBuilder->SetFiltergraph(pGraph);
	if(ewc_hr!=S_OK){errcode=10; goto fin_gf;}
	
	//IAMStreamConfig�C���^�t�F�[�X�̎擾
	ewc_hr= pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Video, pCap,IID_IAMStreamConfig,(void**)&pConfig);
	if(ewc_hr!=S_OK){errcode=11; goto fin_gf;}

	//-----���̎擾-----
	ewc_hr= pConfig->GetNumberOfCapabilities(&count,&size);
	if(ewc_hr!=S_OK){errcode=12; goto fin_gf;}

	//ESP_Printf("count=%d\n",count);

	//-----�t�H�[�}�b�g�̎擾-----
	if(size==sizeof(VIDEO_STREAM_CONFIG_CAPS)){
		for(int i=0; i<count; i++){
			VIDEO_STREAM_CONFIG_CAPS scc;
			AM_MEDIA_TYPE *pmt;
			ewc_hr= pConfig->GetStreamCaps(i,&pmt,reinterpret_cast<BYTE*>(&scc)); 
			if(ewc_hr==S_OK && (pmt->formattype==FORMAT_VideoInfo)){	// || pmt->formattype==FORMAT_VideoInfo2)){
				VIDEOINFOHEADER *vh= reinterpret_cast<VIDEOINFOHEADER*>(pmt->pbFormat);
				fmt[m].width= vh->bmiHeader.biWidth;
				fmt[m].height= vh->bmiHeader.biHeight;
				fmt[m].bit= vh->bmiHeader.biBitCount;
				fmt[m].AvgTimePerFrame= vh->AvgTimePerFrame;
				fmt[m].fps= 10000000./vh->AvgTimePerFrame;
				fmt[m].subtype= pmt->subtype;
				EWC_GUIDtoTEXT(fmt[m].subtype, fmt[m].subtype_t, sizeof(fmt[m].subtype_t));	//v2.3
				ewc_DeleteMediaType(pmt);
				m++;
				if(m >= *nmax) break;
			} 
		}
	}
	//���̍X�V
	*nmax= m;

fin_gf:
	ewc_release(pConfig);
	ewc_release(pBuilder);
	ewc_release(pCap);
	ewc_release(pGraph);

	if(ewc_cominit_gf){
		CoUninitialize();
		ewc_cominit_gf= 0;
	}
	return errcode;
}

//�Ή��t�H�[�}�b�g���擾�����i�f�o�C�X�ԍ��jv2.2
int EWC_GetFormat(int devn, ewc_format *fmt, int *nmax)
{
	if(devn<0 || devn>=EWC_NCAMMAX) return 1;

	return ewc_GetFormat(devn, 0, fmt, nmax);
}

//�Ή��t�H�[�}�b�g���擾�����i�f�o�C�X���jv2.2
int EWC_GetFormat(char *devicename, ewc_format *fmt, int *nmax)
{
	return ewc_GetFormat(0, devicename, fmt, nmax);
}

//�g�p�J�n���ꂽ�J�����̃f�o�C�X�����擾 v2.2
char *EWC_GetDeviceName(int num)
{
	if(numCheck(num)) return NULL;
	
	return ewc_s[num].dname;
}

//�g�p�J�n���ꂽ�J�����̏o�̓s���̃��f�B�A�T�u�^�C�v���������擾 v2.3
char *EWC_GetDeviceSubtype(int num)
{
	if(numCheck(num)) return NULL;
	
	return ewc_s[num].dev_mstype_t;
}

//�g�p�J�n���ꂽ�J�����̏o�͉摜�̃��f�B�A�T�u�^�C�v���������擾 v2.3
char *EWC_GetSubtype(int num)
{
	if(numCheck(num)) return NULL;
	
	return ewc_s[num].mstype_t;
}

const char *ewc_propstr[EWC_ITEMMAX]={
	"BRIGHTNESS","CONTRAST","HUE","SATURATION","SHARPNESS","GAMMA","COLORENABLE","WHITEBALANCE","BACKLIGHTCOMPENSATION","GAIN",
	"PAN","TILT","ROLL","ZOOM","EXPOSURE","IRIS","FOCUS"
};

//�ݒ����t�@�C���֕ۑ����� v2.4
int EWC_SaveProperty(int num, char *filename=NULL)
{
	if(numCheck(num)) return 1;

	FILE *fp;
	double val;
	int mode;
	char buf[256];

	char fname[MAX_PATH];
	if(!filename){
		//�t�@�C�����ȗ����̓f�o�C�X��.txt���g��
		strcpy_s(fname,sizeof(fname),EWC_GetDeviceName(num));
		strcat_s(fname,sizeof(fname),".txt");
	}else{
		strcpy_s(fname,sizeof(fname),filename);
	}

	fopen_s(&fp,fname,"w");
	if(fp==NULL) return 2;

	for(int i=0;i<EWC_ITEMMAX;i++){
		val= EWC_GetValue(num, i, &mode);
		char ss[64];
		_gcvt_s(ss,sizeof(ss),val,18);
		if(mode){
			sprintf_s(buf,sizeof(buf),"%-21s = %s, AUTO\n",ewc_propstr[i],ss);
		}else{
			sprintf_s(buf,sizeof(buf),"%-21s = %s\n",ewc_propstr[i],ss);
		}
		fputs(buf,fp);		
	}

	fclose(fp);

	return 0;
}

//������s����prop���������������C�ԍ�[0-(EWC_ITEMMAX-1)]���Ԃ�
//�Ȃ�����-1���Ԃ�
//�܂��CAUTO�������΁Cmode=1�ɂ����D','�͏I�[�ɂ����D
int find_propstr(char *s, int size, int *mode)
{
	for(int i=0;i<EWC_ITEMMAX;i++){
		_strupr_s(s,size);
		if(strstr(s,ewc_propstr[i])){
			char *p1,*p2;
			p1=strstr(s,",");
			p2=strstr(s,"AUTO");
			if(p1 && p2){
				*mode=1;
				*p1='\0';
			}else{
				*mode=0;
			}
			return i;
		}
	}
	return -1;
}

//�ݒ����t�@�C�������ǂݍ��� v2.4
int EWC_LoadProperty(int num, char *filename=NULL)
{
	if(numCheck(num)) return 1;

	FILE *fp;

	char fname[MAX_PATH];
	if(!filename){
		//�t�@�C�����ȗ����̓f�o�C�X��.txt���g��
		strcpy_s(fname,sizeof(fname),EWC_GetDeviceName(num));
		strcat_s(fname,sizeof(fname),".txt");
	}else{
		strcpy_s(fname,sizeof(fname),filename);
	}

	fopen_s(&fp,fname,"r");
	if(fp==NULL) return 2;

	for(;;){
		char buf[256];
		if(fgets(buf,sizeof(buf),fp)==NULL) break;

		int mode=0;
		int i=find_propstr(buf,sizeof(buf),&mode);
		if(i<0) continue;
		
		char *p;
		p=strstr(buf,"=");
		if(!p) continue;
		p++;
		double val=atof(p);
		
		EWC_SetValue(num, i, val);
		if(mode) EWC_SetAuto(num, i);
	}

	fclose(fp);

	return 0;
}

//End of ewclib.h