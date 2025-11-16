/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Light\LightDLL\LightDLL\LightDLL1.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include<stdio.h>
#include "LightDLL1.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "XLightDLL.h"

//---------------------------------------------------------------------------

/* Error messages display */
#define WD_REGISTER_ERR printf
#define ACTIVE_ADDR_SPACE_NEEDS_INIT 0xFF

LED64ctr	LightDLL1::CLED[LEDBARNUMB];
char	   *LightDLL1::LEDBarIndexFileName="LEDBarIndex.dat";
BYTE		LightDLL1::LEDBrightCondition[LEDConditionNumb][LEDBarNumb][LEDNumbPerLine];
LED64ctr	LightDLL1::SaveCLED[LEDBARNUMB];
BYTE		LightDLL1::SaveLEDBrightCondition[LEDConditionNumb][LEDBarNumb][LEDNumbPerLine];
int			LightDLL1::BarIndexTable[LEDBarNumb];
bool		LightDLL1::ModeOn;


//---------------------------------------------------------------------------

LightDLL1::LightDLL1(LayersBase *base)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	memset(LEDBright    ,0,sizeof(LEDBright     ));
	memset(SaveLEDBright,0,sizeof(SaveLEDBright ));
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++)
			Gain[i][j]=1.0;
	}
	ModeOn=true;
	hDev = NULL;
	//InitialLED();
}

LightDLL1::~LightDLL1(void)
{
}

LightDLL1 &LightDLL1::operator=(LightDLL1 &src)
{
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++)
			LEDBright[i][j]=src.LEDBright[i][j];
	}
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++)
			Gain[i][j]=src.Gain[i][j];
	}
	for(int i=0;i<LEDBARNUMB;i++){
		BarComment[i]=src.BarComment[i];
	}
	return(*this);
}

LightDLL1 &LightDLL1::operator=(LightDLLBase &src)
{
	LightDLL1  *p=dynamic_cast<LightDLL1 *>(&src);
	if(p!=NULL)
		operator=(*p);
	return(*this);
}

bool LightDLL1::operator!=(LightDLLBase &src2)
{
	LightDLL1  *p=dynamic_cast<LightDLL1 *>(&src2);
	if(p!=NULL)
		return(operator!=(*p));
	return(false);
}

bool LightDLL1::operator==(LightDLLBase &src2)
{
	LightDLL1	*s=dynamic_cast<LightDLL1 *>(&src2);

	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++){
			if(LEDBright[i][j]!=s->LEDBright[i][j])
				return(false);
		}
	}
	return(true);
}

bool LightDLL1::operator!=(LightDLL1 &src2)
{
	return(!operator==(src2));
}

void LightDLL1::Clear(void)
{
	memset(LEDBright    ,0,sizeof(    LEDBright));
	memset(SaveLEDBright,0,sizeof(SaveLEDBright));
}

bool LightDLL1::LEDSave(QIODevice &str)
{
	char Buff[50];
	int n=LEDBARNUMB;
	sprintf(Buff,"%d",n);
	if(str.write(Buff,sizeof(Buff))!=sizeof(Buff))
		return(false);

	n=LEDsNumb;
	sprintf(Buff,"%d",n);
	if(str.write(Buff,sizeof(Buff))!=sizeof(Buff))
		return(false);

	n=LEDLevels;
	sprintf(Buff,"%d",n);
	if(str.write(Buff,sizeof(Buff))!=sizeof(Buff))
		return(false);

	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++){
			short	k=LEDBright[i][j];
			sprintf(Buff,"%d",k);
			if(str.write(Buff,sizeof(Buff))!=sizeof(Buff))
				return(false);
		}
	}
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++){
			double	k=Gain[i][j];
			sprintf(Buff,"%.3lf",k);
			if(str.write(Buff,sizeof(Buff))!=sizeof(Buff))
				return(false);
		}
	}
	return(true);
}

bool LightDLL1::LEDLoad(QIODevice &str)
{
	char nBuff[50];
	int n=LEDBARNUMB;
	sprintf(nBuff,"%d",n);
	if(str.read(nBuff,sizeof(nBuff))!=sizeof(nBuff))
		return(false);
	n=atoi(nBuff);

	char mBuff[50];
	int m=LEDsNumb;
	sprintf(mBuff,"%d",m);
	if(str.read(mBuff,sizeof(mBuff))!=sizeof(mBuff))
		return(false);
	m=atoi(mBuff);

	char tBuff[50];
	int t=LEDLevels;
	sprintf(tBuff,"%d",t);
	if(str.read(tBuff,sizeof(tBuff))!=sizeof(tBuff))
		return(false);
	t=atoi(tBuff);

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			short	k;
			char kBuff[50];
			if(str.read(kBuff,sizeof(kBuff))!=sizeof(kBuff))
				return(false);
			k=atoi(kBuff);
			if(i<LEDBARNUMB && j<LEDsNumb)
				LEDBright[i][j]=k;
		}
	}
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++){
			short	k=LEDBright[i][j];
			double	d;
			char dBuff[50];
			if(str.read(dBuff,sizeof(dBuff))!=sizeof(dBuff))
				return(false);
			d=atof(dBuff);
			Gain[i][j]=d;
		}
	}
	return(true);
}

void *LightDLL1::InitialLED()
{
	QString Param;
	if(InitialPhysical(Param)==false){
		return NULL;
	}

	for(int i=0;i<LEDBARNUMB;i++){
		CLED[i].SetDevice(hDev);
		CLED[i].SetID((short)i);
		CLED[i].SetAddress(dwAddrSpace);
		CLED[i].Initial(LEDsNumb);
	}

	for(int i=0;i<sizeof(BarIndexTable)/sizeof(BarIndexTable[0]);i++)
		BarIndexTable[i]=i;

	FILE    *LEDBarIndexFile=fopen(LEDBarIndexFileName,"rt");
	if(LEDBarIndexFile!=NULL){
		char    buff[100];
		while(fgets(buff,sizeof(buff),LEDBarIndexFile)!=NULL){
			char    *fp=buff;
			while(*fp==' ' || *fp=='\t')
				fp++;
			int d;
			if(sscanf(fp,"%d",&d)==1){
				fp=strstr(fp,"->");
				if(fp!=NULL){
					fp++;
					while(*fp==' ' || *fp=='\t')
						fp++;
					int n;
					if(sscanf(fp,"%d",&n)==1)
						BarIndexTable[d]=n;
				}
			}
		}
		fclose(LEDBarIndexFile);
	}
//	LoadBarComment();
	return hDev;
}

//void LightDLL1::TransferLED(TProgressBar *PBar)
void LightDLL1::TransferLED()
{
//	if(PBar!=NULL)
//		PBar->Max=LEDBARNUMB*LEDsNumb;

  #if !defined(FLATLED)
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++){
			CLED[BarIndexTable[i]].Change(j,LEDBright[i][j]);
			CLED[BarIndexTable[i]].OutData(j,Gain[i][j]);
//			if(PBar!=NULL)
//				PBar->StepIt();
		}
	}
	CLED[0].OutNullForHasp();
  #else
	for(int i=0;i<4;i++){
		CLED[BarIndexTable[i]].Change(0,LEDBright[i][0]);
		CLED[BarIndexTable[i]].OutData(i,Gain[i][0]);
//		if(PBar!=NULL)
//			PBar->StepIt();
	}
	CLED[0].OutNullForHasp();
  #endif
	//LatestLight=*this;
}

bool LightDLL1::LEDConditionSave(QIODevice &str)
{
//	if(str.write(LEDBrightCondition,sizeof(LEDBrightCondition))!=sizeof(LEDBrightCondition))
	for(int i=0;i<LEDConditionNumb;i++){
		for(int j=0;j<LEDBarNumb;j++){
			if(str.write((const char *)LEDBrightCondition[i][j],sizeof(LEDBrightCondition[i][j]))!=sizeof(LEDBrightCondition[i][j]))
				return(false);
			return(true);
		}
	}
	return(true);
}

bool LightDLL1::LEDConditionLoad(QIODevice &str)
{
//	if(str.Read(LEDBrightCondition,sizeof(LEDBrightCondition))!=sizeof(LEDBrightCondition))
	for(int i=0;i<LEDConditionNumb;i++){
		for(int j=0;j<LEDBarNumb;j++){
			if(str.read((char *)LEDBrightCondition[i][j],sizeof(LEDBrightCondition[i][j]))!=sizeof(LEDBrightCondition[i][j]))
				return(false);
			return(true);
		}
	}
	return(true);
}

bool LightDLL1::IsEnabled(void)
{
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++){
			if(LEDBright[i][j]!=0)
				return(true);
		}
	}
	return(false);
}

bool    LightDLL1::GetLighting(void)
{
	return(ModeOn);
}

void    LightDLL1::SetLighting(bool mode)
{
	ModeOn=mode;
	CLED[0].SetAllMode(ModeOn);
}

int     LightDLL1::GetBarCount(void)
{
	int LDNumb[100];

	for(int i=0;i<sizeof(LDNumb)/sizeof(LDNumb[0]) && i<LEDBarNumb;i++){
		LDNumb[i]=0;
	}

	for(int i=0;i<LEDBarNumb;i++){
		if(LightLineCounter[i]>=0 && LightLineCounter[i]<sizeof(LDNumb)/sizeof(LDNumb[0])
		&& LightLineCounter[i]<LEDBarNumb){
			LDNumb[LightLineCounter[i]]++;
		}
	}
	int ret=0;
	for(int i=0;i<sizeof(LDNumb)/sizeof(LDNumb[0]) && i<LEDBarNumb;i++){
		if(LDNumb[i]!=0)
            ret++;
	}
	return(ret);
}

void LightDLL1::SetLEDBarBright(int d,int brightness)
{
	for(int i=0;i<LEDBarNumb;i++){
		if(LightLineCounter[i]==d){
			for(int j=0;j<LEDNumbPerLine;j++)
				LEDBright[i/2][j+(i&1)*LEDNumbPerLine]=(short)brightness;
		}
	}
}

int LightDLL1::GetBarComment(int BarID,char *Buff)
{
/*	for(int i=0;i<LEDBarNumb;i++){
		if(LightLineCounter[i]==BarID)
			return(GetBarCommentBase(i,Buff));
	}
*/
	return(0);
}

void LightDLL1::SetPowerRate(int BarID,double rate)
{
	for(int i=0;i<LEDBarNumb;i++){
		if(LightLineCounter[i]==BarID){
			for(int j=0;j<LEDNumbPerLine;j++)
				Gain[i/2][j+(i&1)*LEDNumbPerLine]=rate;
		}
	}
}

double LightDLL1::GetPowerRate(int BarID)
{
	for(int i=0;i<LEDBarNumb;i++){
		if(LightLineCounter[i]==BarID)
			return(Gain[i/2][(i&1)*LEDNumbPerLine]);
	}
	return(0.0);
}

void LightDLL1::ResetPowerRate(void)
{
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++)
			Gain[i][j]=1.0;
	}
}

void LightDLL1::GetNowLEDBarAveragedLevel(int BarLevel[100])
{
	memset(BarLevel,0,sizeof(int)*100);
	for(int k=0;k<LEDBarNumb;k++){
		int D=0;
		int N=0;
		for(int i=0;i<LEDBarNumb;i++){
			if(LightLineCounter[i]==k){
				for(int j=0;j<LEDNumbPerLine;j++,N++)
					D+=LEDBright[i/2][j+(i&1)*LEDNumbPerLine];
			}
		}
		if(N==0)
			BarLevel[k]=0;
		else
			BarLevel[k]=D/N;
	}
}

bool LightDLL1::LEDSaveDefault(void)
{
/*
//	TFileStream *file=new TFileStream(QFileName,fmCreate);
	QIODevice file(QFileName);
	LEDSave(file);
//	delete  file;
*/
	return(true);
}

bool LightDLL1::LEDLoadDefault(void)
{
/*
	if(FileExists(QFileName)==true){
		TFileStream *pfile=new TFileStream(QFileName,fmOpenRead);
		LEDLoad(*pfile);
		delete  pfile;
	}
*/
	return(true);
}

int LightDLL1::GetOneBrightDirectly(int sheet ,int row, int col)
{
	return(LEDBright[row][col+(row&1)*LEDNumbPerLine]);
}

void LightDLL1::SetOneBrightDirectly(int sheet ,int row, int col ,int b)
{
	LEDBright[row][col+(row&1)*LEDNumbPerLine]=b;
}

void LightDLL1::SetWaitTime(int WaitTime)
{
	LED64ctr::LEDWaitTime=WaitTime;
}

bool LightDLL1::LightOn()
{
//	//セット
//	for(int i=0;i<LEDBarNumb;i++){
//		for(int j=0;j<LEDNumbPerLine;j++)
//			LEDBright[i/2][j+(i&1)*LEDNumbPerLine]=(short)ui.sbBrightness->value();
//	}
	//点灯
	SetLighting(true);
//	for(int i=0;i<LEDBARNUMB;i++){
//		for(int j=0;j<LEDsNumb;j++){
//			CLED[i].Change(j,LEDBright[i][j]);
//			CLED[i].OutData(j,Gain[i][j]);
//		}
//	}
	return true;
}

bool LightDLL1::LightOff()
{
	//消灯
	SetLighting(false);
//	for(int i=0;i<LEDBARNUMB;i++){
//		for(int j=0;j<LEDsNumb;j++){
//			CLED[i].Change(j,0);
//			CLED[i].OutData(j,Gain[i][j]);
//		}
//	}
	return true;
}

bool	LightDLL1::Save(QIODevice *f)
{
	return LEDSave(*f);
}
bool	LightDLL1::Load(QIODevice *f)
{
	return LEDLoad(*f);
}
bool	LightDLL1::ShowSettingDialog(void)
	//Don't call directly
{
	return DLL_ShowSetting(this, NULL);
}
bool	LightDLL1::InitialPhysical(const QString &Param)
{
//	LED64ctr::InitialOnly();

	//WinDriver
	//hDev = NULL;

	// Initialize the WD_REGISTER library
	dwStatus = WD_REGISTER_LibInit();
	if (WD_STATUS_SUCCESS != dwStatus){
		WD_REGISTER_ERR("wd_register_diag: Failed to initialize the WD_REGISTER library: %s",
			WD_REGISTER_GetLastErr());
		return false;
	}

	// Open a handle to the device
	hDev = WD_REGISTER_DeviceOpen();
	if (!hDev){
		WD_REGISTER_ERR("wd_register_diag: Failed opening a handle to the device: %s",
			WD_REGISTER_GetLastErr());
		return false;
	}

	/* Find the first active address space */
	dwAddrSpace = ACTIVE_ADDR_SPACE_NEEDS_INIT;
	mode = WDC_MODE_8;
	for (dwAddrSpace = 0; dwAddrSpace < WD_REGISTER_ADDR_SPACES_NUM; dwAddrSpace++){
		if (WDC_AddrSpaceIsActive(hDev, dwAddrSpace))
			break;
	}
	dwAddrSpace=0;
	return true;
}
bool	LightDLL1::ReflectPhysical(void)
{
	TransferLED();
	return true;
}
bool	LightDLL1::ReflectPhysicalTurnOn(bool LightOn)
{
	SetLighting(LightOn);
	return true;
}
