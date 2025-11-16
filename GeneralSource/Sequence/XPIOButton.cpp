/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\XPIOButton.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/
#include <QtGui>
#include "XPIOButton.h"
#include "XPIOInterface.h"
#include "AIP_IO.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XErrorMessage.h"
#include "Regulus64System.h"

/*
int		(*PIOInterface::AIP_IO_GetIOBoardNumb)(void);
int		(*PIOInterface::AIP_IO_GetIOInBitCount)(int boardNumber);
int		(*PIOInterface::AIP_IO_GetIOOutBitCount)(int boardNumber);
bool	(*PIOInterface::AIP_IO_Initial)(void);
bool	(*PIOInterface::AIP_IO_Open)(int boardNumber , char *name ,int maxbuffsize);
BYTE	(*PIOInterface::AIP_IO_GetBit)(int boardNumber , BYTE bitIndex);
BYTE	(*PIOInterface::AIP_IO_GetByte)(int boardNumber , BYTE byteIndex);
void	(*PIOInterface::AIP_IO_SetBit)(int boardNumber , BYTE bitIndex ,BYTE data);
BYTE	(*PIOInterface::AIP_IO_SetByte)(int boardNumber , BYTE byteIndex , BYTE data);
int		(*PIOInterface::AIP_IO_GetOutByte)(int boardNumber , BYTE byteIndex);
bool	(*PIOInterface::AIP_IO_Close)(int boardNumber);
bool	(*PIOInterface::AIP_IO_Release)(void);
QLibrary 	PIOInterface::DllLib;

int     PIOInterface::PIO_BoardNumb   =0;
EachPIOClass    *PIOInterface::PIOBrd =NULL;
volatile    bool    PIOInterface::Changed         =false;
volatile    bool    PIOInterface::Initialized     =false;

*/

//PIOClass    PIO(false);


EachPIOClass::EachPIOClass(void)
	:Parent(NULL)
{
    Name=/**/"";
    PIO_INBITNUMB		=0;
    PIO_OUTBITNUMB		=0;
    OutData				=NULL;
	LastOutData			=NULL;
    InData				=NULL;
	LastOutMilisec		=NULL;
    Initialized			=false;
    Opened				=false;
    BoardNumber			=0;

    DefInName			=NULL;
    DefOutName			=NULL;
    DefaultOutData		=NULL;
	AttrNoLoop			=false;
	Handle				=NULL;
	EnableScanLoopIn	=NULL;
	EnableScanLoopOut	=NULL;
}
int	HeapError;
EachPIOClass::~EachPIOClass(void)
{
    if(Opened==true)
        Close();

    PIO_INBITNUMB =0;
    PIO_OUTBITNUMB=0;

	#ifdef _MSC_VER
	if(_heapchk()!=_HEAPOK){
		HeapError++;
	}
	#endif

    if(OutData!=NULL)
        delete  []OutData;
    OutData=NULL;

	if(LastOutData!=NULL)
		delete	[]LastOutData;
	LastOutData=NULL;

    if(InData!=NULL)
        delete  []InData;
    InData=NULL;

 	if(LastOutMilisec!=NULL)
		delete	[]LastOutMilisec;
	LastOutMilisec=NULL;

	if(DefInName!=NULL)
        delete  []DefInName;
    DefInName=NULL;

    if(DefOutName!=NULL)
        delete  []DefOutName;
    DefOutName=NULL;

    if(DefaultOutData!=NULL)
        delete  []DefaultOutData;
    DefaultOutData=NULL;

	if(EnableScanLoopIn!=NULL)
		delete	[]EnableScanLoopIn;
	EnableScanLoopIn=NULL;

	if(EnableScanLoopOut!=NULL)
		delete	[]EnableScanLoopOut;
	EnableScanLoopOut=NULL;
}


void    EachPIOClass::Initialize(PIOInterface *parent)
{
	Parent=parent;
	if(Handle!=NULL){
		PIO_INBITNUMB   =Parent->GetIOInBitCount (Handle,BoardNumber);
		PIO_OUTBITNUMB  =Parent->GetIOOutBitCount(Handle,BoardNumber);
	}

	if(PIO_INBITNUMB==0 && PIO_OUTBITNUMB==0){
		return;
	}

    if(OutData!=NULL)
	    delete  []OutData;
    OutData=new BYTE[(PIO_OUTBITNUMB+7)/8];
    for(int i=0;i<(PIO_OUTBITNUMB+7)/8;i++)
        OutData[i]=0;

    if(LastOutData!=NULL)
        delete  []LastOutData;
    LastOutData=new BYTE[(PIO_OUTBITNUMB+7)/8];
    for(int i=0;i<(PIO_OUTBITNUMB+7)/8;i++)
        LastOutData[i]=0;

    if(InData!=NULL)
        delete  []InData;
    InData=new BYTE[(PIO_INBITNUMB+7)/8];

    if(LastOutMilisec!=NULL)
        delete  []LastOutMilisec;
    LastOutMilisec=new DWORD[PIO_OUTBITNUMB];
    for(int i=0;i<(PIO_OUTBITNUMB+7)/8;i++){
        LastOutMilisec[i]=0;
	}

	if(DefInName!=NULL){
        delete  []DefInName;
	}
    DefInName   =new QString[PIO_INBITNUMB];
    if(DefOutName!=NULL){
        delete  []DefOutName;
	}
    DefOutName   =new QString[PIO_OUTBITNUMB];

    if(DefaultOutData!=NULL){
        delete  []DefaultOutData;
	}
    DefaultOutData=new bool[PIO_OUTBITNUMB];
    for(int i=0;i<PIO_OUTBITNUMB;i++){
        DefaultOutData[i]=false;
	}

    if(EnableScanLoopIn!=NULL){
        delete  []EnableScanLoopIn;
	}
    EnableScanLoopIn=new bool[PIO_INBITNUMB];
    for(int i=0;i<PIO_INBITNUMB;i++){
        EnableScanLoopIn[i]=true;
	}
	
    if(EnableScanLoopOut!=NULL){
		delete  []EnableScanLoopOut;
	}
    EnableScanLoopOut=new bool[PIO_OUTBITNUMB];
    for(int i=0;i<PIO_OUTBITNUMB;i++){
        EnableScanLoopOut[i]=true;
	}
	
	Initialized=true;
}


bool    EachPIOClass::Open(QWidget *mainW,const QString &Something)
{
    if(Initialized==false)
        Initialize(Parent);

    if(Opened==true)
        return(true);
    char    qName[257];
	Handle=Parent->Open(mainW,BoardNumber , qName ,sizeof(qName)-1,Something);
	if(Handle==NULL){
		return(false);
	}
    if(Initialized==false)
        Initialize(Parent);
    Name=qName;
    Opened=true;
    return(true);
}

bool    EachPIOClass::Close(void)
{
    if(Opened==true){
		if(Parent->Close(Handle,BoardNumber)==false){
			return(false);
		}
        Opened=false;
    }
    return(true);
}

bool    EachPIOClass::ReadDefFile(FILE *file ,char *buff ,int buffsize,bool DefaultOut)
{
    char    *fp,*gp;

    do{
        fp=buff;
        while(*fp==' ' || *fp=='\t')
            fp++;
        if(strnicmp(fp,"IN",2)==0){
            fp+=2;
            while(*fp==' ' || *fp=='\t')
                fp++;
            int d;
            if(sscanf(fp,"%d",&d)!=1)
                continue;
            if(d<0 || d>=PIO_INBITNUMB)
                continue;
            fp++;
            while(*fp!=' ' && *fp!='\t' && *fp!=0)
                fp++;
            while(*fp==' ' || *fp=='\t')
                fp++;
            if(*fp!='\"'){
                DefInName[d]=/**/"";
                continue;
                }
            gp=strchr(buff,0)-1;
            while(*gp!='\"' && gp>buff)
                gp--;
            if(*gp!='\"'){
                DefInName[d]=/**/"";
                continue;
                }
            if(gp==fp){
                DefInName[d]=/**/"";
                continue;
                }
            fp++;
            *gp=0;
            DefInName[d]=QString(fp);
			fp=gp+1;
            while(*fp==' ' || *fp=='\t')
                fp++;
			if(*fp==',' || *fp==':'){
				fp++;
				if(strnicmp(fp,"NoScan",6)==0){
					EnableScanLoopIn[d]=false;
				}
				fp+=6;
            }
		}
        else if(strnicmp(fp,"OUT",3)==0){
            fp+=3;
            while(*fp==' ' || *fp=='\t')
                fp++;
            int d;
            if(sscanf(fp,"%d",&d)!=1)
                continue;
            if(d<0 || d>=PIO_OUTBITNUMB)
                continue;
            fp++;
            while(*fp!=' ' && *fp!='\t' && *fp!=0)
                fp++;
            while(*fp==' ' || *fp=='\t')
                fp++;
            if(*fp!='\"'){
                DefOutName[d]=/**/"";
                continue;
                }
            gp=strchr(buff,0)-1;
            while(*gp!='\"' && gp>buff)
                gp--;
            if(*gp!='\"'){
                DefOutName[d]=/**/"";
                continue;
                }
            if(gp==fp){
                DefOutName[d]=/**/"";
                continue;
                }
            fp++;
            *gp=0;
            DefOutName[d]=QString(fp);
			fp=gp+1;
            while(*fp==' ' || *fp=='\t')
                fp++;
			if(*fp==',' || *fp==':'){
				fp++;
				if(strnicmp(fp,"NoScan",6)==0){
					EnableScanLoopOut[d]=false;
				}
				fp+=6;
            }
		}
        else if(strnicmp(fp,"Default",7)==0){
            fp+=7;
            while(*fp==' ' || *fp=='\t')
                fp++;
            int d;
            if(sscanf(fp,"%d",&d)!=1)
                continue;
            if(d<0 || d>=PIO_OUTBITNUMB)
                continue;
            fp++;
            while(*fp!=' ' && *fp!='\t' && *fp!=0)
                fp++;
            int m=0;
            if(sscanf(fp,"%d",&m)!=1)
                continue;
            if(m!=0){
				if(0<=d && d<((PIO_OUTBITNUMB+7)/8))
					DefaultOutData[d] =true;
                }
            }
        else if(strnicmp(fp,"NOLOOP",6)==0){
            AttrNoLoop=true;
            }
        else if(strnicmp(fp,"BOARD",5)==0){
            break;
            }
        }while(fgets(buff,buffsize-1,file)!=NULL);

	if(DefaultOut==true){
	    for(int i=0;i<PIO_OUTBITNUMB;i++){
		    if(DefaultOutData[i]==true)
			    SetBit(i/8,i%8  ,1);
	        else
		        SetBit(i/8,i%8  ,0);
		}
	}
    return(true);
}

bool    EachPIOClass::ReadDefFile(QTextStream &file ,QString &StrBuff,int buffsize,bool DefaultOut)
{
    char    *fp,*gp;

    do{
		QString	TxBuff=StrBuff.simplified().trimmed();
		char	buff[500];
		QString2Char(TxBuff,buff ,sizeof(buff)-1);

		fp=buff;
        if(strnicmp(fp,"IN",2)==0){
            fp+=2;
            while(*fp==' ' || *fp=='\t')
                fp++;
            int d;
            if(sscanf(fp,"%d",&d)!=1)
                continue;
            if(d<0 || d>=PIO_INBITNUMB)
                continue;
            fp++;
            while(*fp!=' ' && *fp!='\t' && *fp!=0)
                fp++;
            while(*fp==' ' || *fp=='\t')
                fp++;
            if(*fp!='\"'){
                DefInName[d]=/**/"";
                continue;
                }
            gp=strchr(buff,0)-1;
            while(*gp!='\"' && gp>buff)
                gp--;
            if(*gp!='\"'){
                DefInName[d]=/**/"";
                continue;
                }
            if(gp==fp){
                DefInName[d]=/**/"";
                continue;
                }
            fp++;
            *gp=0;
            DefInName[d]=QString(fp);
            }
        else if(strnicmp(fp,"OUT",3)==0){
            fp+=3;
            while(*fp==' ' || *fp=='\t')
                fp++;
            int d;
            if(sscanf(fp,"%d",&d)!=1)
                continue;
            if(d<0 || d>=PIO_OUTBITNUMB)
                continue;
            fp++;
            while(*fp!=' ' && *fp!='\t' && *fp!=0)
                fp++;
            while(*fp==' ' || *fp=='\t')
                fp++;
            if(*fp!='\"'){
                DefOutName[d]=/**/"";
                continue;
                }
            gp=strchr(buff,0)-1;
            while(*gp!='\"' && gp>buff)
                gp--;
            if(*gp!='\"'){
                DefOutName[d]=/**/"";
                continue;
                }
            if(gp==fp){
                DefOutName[d]=/**/"";
                continue;
                }
            fp++;
            *gp=0;
            DefOutName[d]=QString(fp);
		}
        else if(strnicmp(fp,"Default",7)==0){
            fp+=7;
            while(*fp==' ' || *fp=='\t')
                fp++;
            int d;
            if(sscanf(fp,"%d",&d)!=1)
                continue;
            if(d<0 || d>=PIO_OUTBITNUMB)
                continue;
            fp++;
            while(*fp!=' ' && *fp!='\t' && *fp!=0)
                fp++;
            int m=0;
            if(sscanf(fp,"%d",&m)!=1)
                continue;
            if(m!=0){
				if(0<=d && d<((PIO_OUTBITNUMB+7)/8))
					DefaultOutData[d] =true;
			}
		}
        else if(strnicmp(fp,"NOLOOP",6)==0){
            AttrNoLoop=true;
            }
        else if(strnicmp(fp,"BOARD",5)==0){
            break;
		}
		StrBuff=file.readLine(1000);
	}while(file.atEnd()==false);

	if(DefaultOut==true){
	    for(int i=0;i<PIO_OUTBITNUMB;i++){
		    if(DefaultOutData[i]==true)
			    SetBit(i/8,i%8  ,1);
	        else
		        SetBit(i/8,i%8  ,0);
		}
	}
    return(true);
}

bool    EachPIOClass::WriteDefFile(FILE *file)
{
    for(int i=0;i<PIO_INBITNUMB;i++){
		char	MBuff[256];
		QString2Char(DefInName[i] ,MBuff ,sizeof(MBuff));
        fprintf(file,"IN%d\t\"%s\"\n",i,MBuff);
        }
    fprintf(file,"\n");
    for(int i=0;i<PIO_OUTBITNUMB;i++){
		char	MBuff[256];
		QString2Char(DefOutName[i] ,MBuff ,sizeof(MBuff));
        fprintf(file,"OUT%d\t\"%s\"\n",i,MBuff);
        }
    for(int i=0;i<PIO_OUTBITNUMB;i++){
        if(DefaultOutData[i]==true)
            fprintf(file,"Default%d\t1\n",i);
        }
    return(true);
}
void	EachPIOClass::LogOutBit(int portno,int bitno ,BYTE data)
{
	DWORD	t=::GetComputerMiliSec();
	int		k=portno*8+bitno;
	DWORD	Old=LastOutMilisec[k];
	emit	SignalLogOutBit(BoardNumber 
							,portno,bitno 
							,data 
							,t,t-Old);
	LastOutMilisec[k]=t;
}
EachPIOClass  &  EachPIOClass::operator=(const EachPIOClass &src)
{
	if(&src!=this){
		Name    =src.Name;
		PIO_INBITNUMB   =src.PIO_INBITNUMB  ;
		PIO_OUTBITNUMB  =src.PIO_OUTBITNUMB ;
		BoardNumber     =src.BoardNumber    ;
		Initialized     =src.Initialized    ;
		Opened          =src.Opened         ;

		if(OutData!=NULL)
		    delete  []OutData;
		OutData=new BYTE[(PIO_OUTBITNUMB+7)/8];
		memcpy((void *)OutData,(void *)src.OutData,(PIO_OUTBITNUMB+7)/8);

		if(LastOutData!=NULL)
		    delete  []LastOutData;
		LastOutData=new BYTE[(PIO_OUTBITNUMB+7)/8];
		memcpy((void *)LastOutData,(void *)src.LastOutData,(PIO_OUTBITNUMB+7)/8);

		if(InData!=NULL)
		    delete  []InData;
		InData=new BYTE[PIO_INBITNUMB];
		memcpy((void *)InData,(void *)src.InData,(PIO_INBITNUMB+7)/8);

		if(LastOutMilisec!=NULL)
		    delete  []LastOutMilisec;
		LastOutMilisec=new DWORD[PIO_OUTBITNUMB];
		memcpy((void *)LastOutMilisec,(void *)src.LastOutMilisec,PIO_OUTBITNUMB);

		if(DefInName!=NULL)
		    delete  []DefInName;
		DefInName=new QString[PIO_INBITNUMB];
		for(int i=0;i<PIO_INBITNUMB;i++){
		    DefInName[i]=src.DefInName[i];
		    }

		if(DefOutName!=NULL)
		    delete  []DefOutName;
		DefOutName=new QString[PIO_OUTBITNUMB];
		for(int i=0;i<PIO_OUTBITNUMB;i++){
		    DefOutName[i]=src.DefOutName[i];
		    }

		if(DefaultOutData!=NULL)
		    delete  []DefaultOutData;
		DefaultOutData=new bool[(PIO_OUTBITNUMB+7)/8];
		for(int i=0;i<(PIO_OUTBITNUMB+7)/8;i++){
		    DefaultOutData[i]=src.DefaultOutData[i];
		    }
	}
    return(*this);
}


BYTE    EachPIOClass::GetByte(int portno)
{
    if(Initialized==false)
        Initialize(Parent);
    if(Opened==false){
        return(false);
	}
    if(PIO_INBITNUMB<=portno)
        return(0);
	IOAccessMutex.lock();
	BYTE    ret=Parent->IO_GetByte(Handle,BoardNumber , portno);
	InData[portno]=ret;
	IOAccessMutex.unlock();
	return(ret);
}

BYTE    EachPIOClass::GetBufferedOutByte(int portno)
{
	return OutData[portno];
}

 	
int		EachPIOClass::GetIOInBitCount	(void)	const
{
	return Parent->GetIOInBitCount(Handle,BoardNumber);
}

int		EachPIOClass::GetIOOutBitCount	(void)	const
{
	return Parent->GetIOOutBitCount(Handle,BoardNumber);
}

int     EachPIOClass::GetBit(int portno ,int bitno)
{
    if(Initialized==false)
        Initialize(Parent);
    if(Opened==false){
		return(false);
	}
    if(PIO_INBITNUMB<=portno)
        return(0);
	IOAccessMutex.lock();
    BYTE    ret=Parent->IO_GetBit(Handle,BoardNumber,portno*8+bitno);
	if(ret==0)
		InData[portno] &=~(0x01<<bitno);
	else
		InData[portno] |=(0x01<<bitno);
	IOAccessMutex.unlock();

	return(ret);
}
void    EachPIOClass::SetByte(int portno ,BYTE data)
{
    if(Initialized==false)
        Initialize(Parent);
    if(Opened==false){
		return;
	}
    if((PIO_OUTBITNUMB+7)/8<=portno)
        return;

	IOAccessMutex.lock();
    OutData[portno]=data;

	if(OutData[portno]!=LastOutData[portno]){
		OutData[portno]=data;
		Parent->IO_SetByte(Handle,BoardNumber,portno,data);
		for(int i=0;i<8;i++){
			BYTE	Mask=0x01<<i;
			if((LastOutData[portno]&Mask)!=(OutData[portno]&Mask)){
				LogOutBit(portno,i,((OutData[portno]&Mask)!=0)?1:0);
			}
		}
		LastOutData[portno]=OutData[portno];
	}
	IOAccessMutex.unlock();
}
void    EachPIOClass::SetBit(int portno ,int bitno  ,BYTE data)
{
    if(Initialized==false)
        Initialize(Parent);
    if(Opened==false){
		return;
	}
    if((PIO_OUTBITNUMB+7)/8<=portno)
        return;
	IOAccessMutex.lock();
	bool	Ret=Parent->IO_SetBit(Handle,BoardNumber,portno*8+bitno ,data);
	if(Ret==true){
	    if(data==0)
		    OutData[portno] &= ~(0x01<<bitno);
		else
			OutData[portno] |=  (0x01<<bitno);
		BYTE	Mask=0x01<<bitno;
		if((LastOutData[portno]&Mask)!=(OutData[portno]&Mask)){
			LogOutBit(portno,bitno,((OutData[portno]&Mask)!=0)?1:0);
		}
		LastOutData[portno]=OutData[portno];
	}
	else{
	    if(data==0)
		    OutData[portno] &= ~(0x01<<bitno);
	    else
		    OutData[portno] |=  (0x01<<bitno);

		Parent->IO_SetByte(Handle,BoardNumber,portno ,OutData[portno]);
		BYTE	Mask=0x01<<bitno;
		if((LastOutData[portno]&Mask)!=(OutData[portno]&Mask)){
			LogOutBit(portno,bitno,((OutData[portno]&Mask)!=0)?1:0);
		}
		LastOutData[portno]=OutData[portno];
	}
	IOAccessMutex.unlock();
}
void    EachPIOClass::SetBitWithoutLock(int portno ,int bitno  ,BYTE data)
{
    if(Initialized==false)
        Initialize(Parent);
    if(Opened==false){
		return;
	}
    if((PIO_OUTBITNUMB+7)/8<=portno)
        return;
	bool	Ret=Parent->IO_SetBit(Handle,BoardNumber,portno*8+bitno ,data);
	if(Ret==false){
		Ret=Parent->IO_SetByte(Handle,BoardNumber,portno ,OutData[portno]);
	}
	if(Ret==true){
		for(int i=0;i<8;i++){
			BYTE	Mask=0x01<<i;
			if((LastOutData[portno]&Mask)!=(OutData[portno]&Mask)){
				LogOutBit(portno,i,((OutData[portno]&Mask)!=0)?1:0);
			}
		}
		LastOutData[portno]=OutData[portno];
	}
}

BYTE    EachPIOClass::GetOutByte(int portno)
{
    if(Initialized==false)
        Initialize(Parent);
    if(Opened==false){
		return(false);
	}
    if(PIO_INBITNUMB<=portno)
        return(0);
	IOAccessMutex.lock();
	BYTE    ret=Parent->IO_GetOutByte(Handle,BoardNumber , portno);
	InData[portno]=ret;
	IOAccessMutex.unlock();
	return(ret);
}

int     EachPIOClass::GetOutBit(int bitno)
{
    int portno=bitno/8;
    bitno &=0x7;
    if((PIO_OUTBITNUMB+7)/8<=portno)
        return(0);
    if(OutData==NULL)
        return(0);
    if((OutData[portno]&(0x01<<bitno))==0)
        return(0);
    else
        return(1);
}

BYTE    EachPIOClass::GetEchobackOutByte(int portno)
{
    if(PIO_OUTBITNUMB<=portno)
        return(0);
	IOAccessMutex.lock();
	BYTE	ret=Parent->IO_GetOutByte(Handle,BoardNumber,portno);
	IOAccessMutex.unlock();
	return ret;
}
int     EachPIOClass::GetEchobackOutBit(int bitno)
{
	IOAccessMutex.lock();
	BYTE	ret=Parent->IO_GetOutBit(Handle,BoardNumber,bitno);
	IOAccessMutex.unlock();

	/*
	    int portno=bitno/8;
		bitno &=0x7;
	    if(PIO_OUTBITNUMB<=portno)
		    return(0);

		IOAccessMutex.lock();
		int d=Parent->IO_GetOutByte(BoardNumber,portno);
		IOAccessMutex.unlock();
		if((d&(0x01<<bitno))==0)
			return(0);
		else
			return(1);
	*/
	return ret;
}

BYTE    EachPIOClass::GetBufferedInByte(int portno)
{
    if(PIO_INBITNUMB<=portno)
        return(0);
    if(InData==NULL)
        return(0);
    return(InData[portno]);
}

void    EachPIOClass::InitialOutput(void)
{
	for(int i=0;i<PIO_OUTBITNUMB/8;i++){
		LastOutData[i]=OutData[i]=GetEchobackOutByte(i);
	}
}

void    EachPIOClass::LoopIO(void)
{
	if(AttrNoLoop==false){
		for(int i=0;i<PIO_INBITNUMB/8;i++){
			GetByte(i);
		}
		IOAccessMutex.lock();
		for(int i=0;i<PIO_OUTBITNUMB;i++){
			if(EnableScanLoopOut[i]==true && DefOutName[i].isEmpty()==false){
				SetBitWithoutLock(i>>3,i&7,(OutData[i>>3]>>(i&7))&1);
			}
		}
		IOAccessMutex.unlock();
	}
}
void	EachPIOClass::LoopOnIdle(void)
{
	Parent->LoopOnIdle(Handle,BoardNumber);
}
//------------------------------------------------------------------------

PIOInterface::PIOInterface(LayersBase *base,bool psu)
	:ServiceForLayers(base)
{
	Loaded					=false;

	DLL_GetDLLType			=NULL;
	DLL_GetName				=NULL;
	DLL_GetExplain			=NULL;
	DLL_GetVersion			=NULL;
	DLL_CheckCopyright		=NULL;

	AIP_IO_GetIOBoardNumb	=NULL;
	AIP_IO_GetIOInBitCount	=NULL;
	AIP_IO_GetIOOutBitCount	=NULL;
	AIP_IO_Initial			=NULL;
	AIP_IO_Open				=NULL;
	AIP_IO_GetBit			=NULL;
	AIP_IO_GetByte			=NULL;
	AIP_IO_SetBit			=NULL;
	AIP_IO_SetByte			=NULL;
	AIP_IO_GetOutByte		=NULL;
	AIP_IO_GetOutBit		=NULL;
	AIP_IO_Close			=NULL;
	AIP_IO_Release			=NULL;
	AIP_IO_LoopOnIdle		=NULL;

	PIO_BoardNumb=0;
	PIOBrd =NULL;
	Initialized     =false;
    Psu=psu;
    if(psu==false)
        Changed=false;
}
PIOInterface::~PIOInterface(void)
{
    if(PIOBrd!=NULL){
        for(int i=0;i<PIO_BoardNumb;i++){
            PIOBrd[i].Close();
            }
        }
    PIO_BoardNumb=0;
    if(PIOBrd!=NULL){
        delete  []PIOBrd;
        }
    PIOBrd=NULL;

	if(AIP_IO_Release!=NULL)
		AIP_IO_Release();
}

bool	PIOInterface::LoadDLL(const QString &filename,bool OutputErrorMessage)
{
	if(Loaded==true){
		return true;
	}
	if(GetLayersBase()!=NULL){
		GetLayersBase()->TestLoadDLL(filename);
	}
	DllLib.setFileName(filename);
	if(DllLib.load()==false){
		if(OutputErrorMessage==true){
			::SendErrorMessage(QString(/**/"Can not load PIO : ")+filename);
		}
		return false;
	}

	PIOFileName=filename;

	DLL_GetDLLType		=(WORD (*)(void))DllLib.resolve("DLL_GetDLLType");
	DLL_GetName			=(bool (*)(QString &str))DllLib.resolve("DLL_GetName");
	DLL_GetExplain		=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");
	DLL_GetVersion		=(WORD	(*)(void))DllLib.resolve("DLL_GetVersion");
	DLL_CheckCopyright	=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");
	if(DLLManager::LoadDLL(DllLib)==false){
		return false;
	}
	AIP_IO_GetIOBoardNumb		=(int (*)(void))DllLib.resolve("AIP_IO_GetIOBoardNumb");
	AIP_IO_GetIOInBitCount		=(int (*)(void *handle ,int boardNumber))DllLib.resolve("AIP_IO_GetIOInBitCount");
	AIP_IO_GetIOOutBitCount		=(int (*)(void *handle ,int boardNumber))DllLib.resolve("AIP_IO_GetIOOutBitCount");
	AIP_IO_Initial				=(bool	(*)(const QStringList &NameList))DllLib.resolve("AIP_IO_Initial");
	AIP_IO_Open					=(void	*(*)(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something))DllLib.resolve("AIP_IO_Open");
	AIP_IO_GetBit				=(BYTE	(*)(void *handle ,int boardNumber , BYTE bitIndex))DllLib.resolve				("AIP_IO_GetBit");
	AIP_IO_GetByte				=(BYTE	(*)(void *handle ,int boardNumber , BYTE byteIndex))DllLib.resolve				("AIP_IO_GetByte");
	AIP_IO_SetBit				=(void	(*)(void *handle ,int boardNumber , BYTE bitIndex ,BYTE data))DllLib.resolve	("AIP_IO_SetBit");
	AIP_IO_SetByte				=(BYTE	(*)(void *handle ,int boardNumber , BYTE byteIndex , BYTE data))DllLib.resolve	("AIP_IO_SetByte");
	AIP_IO_GetOutByte			=(int	(*)(void *handle ,int boardNumber , BYTE byteIndex))DllLib.resolve				("AIP_IO_GetOutByte");
	AIP_IO_GetOutBit			=(int	(*)(void *handle ,int boardNumber , BYTE bitIndex))DllLib.resolve				("AIP_IO_GetOutBit");
	AIP_IO_Close				=(bool	(*)(void *handle ,int boardNumber))DllLib.resolve								("AIP_IO_Close");
	AIP_IO_Release				=(bool	(*)(void))DllLib.resolve("AIP_IO_Release");
	AIP_IO_LoopOnIdle			=(void	(*)(void *handle,int boardNumber))DllLib.resolve								("AIP_IO_LoopOnIdle");

	if(GetLayersBase()!=NULL){
		GetLayersBase()->InformToLoadDLL(filename);
	}
	Loaded=true;
	return true;
}
bool	PIOInterface::IsPIODLL(void)	const
{
	if(DLL_GetVersion!=NULL){
		int	d=DLL_GetDLLType();
		if((d&DLLModeMask)==DLLPIOMode){
			return(true);
		}
	}
	return(false);
}

QString	PIOInterface::GetName(void)	const
{
	if(DLL_GetName!=NULL){
		QString	Str;
		if(DLL_GetName(Str)==true){
			return Str;
		}
	}
	return QString(/**/"");
}

WORD	PIOInterface::GetVersion(void)	const
{
	if(DLL_GetVersion!=NULL){
		return DLL_GetVersion();
	}
	return 0;
}

WORD	PIOInterface::GetDLLType(void)	const
{
	if(DLL_GetDLLType!=NULL){
		return DLL_GetDLLType();
	}
	return 0;
}
QString	PIOInterface::GetCopyright(void)	const
{
	QString	Copyright;
	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			return Copyright;
		}
	}
	return QString(/**/"");
}

const QString	PIOInterface::GetExplain(void)	const
{
	if(DLL_GetExplain!=NULL){
		const char	*c=DLL_GetExplain();
		if(c!=NULL){
			return QString::fromLocal8Bit(c);
		}
	}
	return /**/"";
}
void	PIOInterface::LoopOnIdle(void *handle ,int boardNumber)
{
	if(AIP_IO_LoopOnIdle!=NULL){
		AIP_IO_LoopOnIdle(handle,boardNumber);
	}
}

void	PIOInterface::GetExportFunctions(QStringList &Str)
{
	if(DLL_GetDLLType!=NULL){
		Str.append("DLL_GetDLLType");
	}
	if(DLL_GetName!=NULL){
		Str.append("DLL_GetName");
	}
	if(DLL_GetExplain!=NULL){
		Str.append("DLL_GetExplain");
	}
	if(DLL_GetVersion!=NULL){
		Str.append("DLL_GetVersion");
	}
	if(DLL_CheckCopyright!=NULL){
		Str.append("DLL_CheckCopyright");
	}
	if(AIP_IO_GetIOBoardNumb!=NULL){
		Str.append("AIP_IO_GetIOBoardNumb");
	}
	if(AIP_IO_GetIOInBitCount!=NULL){
		Str.append("AIP_IO_GetIOInBitCount");
	}
	if(AIP_IO_GetIOOutBitCount!=NULL){
		Str.append("AIP_IO_GetIOOutBitCount");
	}
	if(AIP_IO_Initial!=NULL){
		Str.append("AIP_IO_Initial");
	}
	if(AIP_IO_Open!=NULL){
		Str.append("AIP_IO_Open");
	}
	if(AIP_IO_GetBit!=NULL){
		Str.append("AIP_IO_GetBit");
	}
	if(AIP_IO_GetByte!=NULL){
		Str.append("AIP_IO_GetByte");
	}
	if(AIP_IO_SetBit!=NULL){
		Str.append("AIP_IO_SetBit");
	}
	if(AIP_IO_SetByte!=NULL){
		Str.append("AIP_IO_SetByte");
	}
	if(AIP_IO_GetOutByte!=NULL){
		Str.append("AIP_IO_GetOutByte");
	}
	if(AIP_IO_GetOutBit!=NULL){
		Str.append("AIP_IO_GetOutBit");
	}
	if(AIP_IO_Close!=NULL){
		Str.append("AIP_IO_Close");
	}
	if(AIP_IO_Release!=NULL){
		Str.append("AIP_IO_Release");
	}
	if(AIP_IO_Release!=NULL){
		Str.append("AIP_IO_LoopOnIdle");
	}
	DLLManager::GetExportFunctions(Str);
}

EachPIOClass    *PIOInterface::GetPIOBrd(int brdnumb)	const
{
	if(0<=brdnumb && brdnumb<PIO_BoardNumb){
		return &PIOBrd[brdnumb];
	}
	return NULL;
}

bool    PIOInterface::Initialize(QWidget *mainW,const QString &IODLLFileName,bool InitialOutput,const QString &Something)
{
    if(Initialized==true)
        return(true);

	QFileInfo fi(IODLLFileName);
	if(fi.suffix().isEmpty()==true){
		QString	SearchFile=IODLLFileName+QString(".")+GetDynamicFileExt();
		if(LoadDLL(SearchFile,true)==false){
			return false;
		}
	}
	else{
		if(LoadDLL(IODLLFileName,true)==false){
			return false;
		}
	}

	QStringList	List;
	int	MaxBrdNo=0;
	for(PIOBrdNameList *c=BrdNameListContainer.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->BrdNo>MaxBrdNo){
			MaxBrdNo=c->BrdNo;
		}
	}
	for(int i=0;i<=MaxBrdNo;i++){
		List.append(/**/"");
	}
	for(PIOBrdNameList *c=BrdNameListContainer.GetFirst();c!=NULL;c=c->GetNext()){
		List[c->BrdNo]=c->BrdName;
	}

	if(AIP_IO_Initial!=NULL){
		if(AIP_IO_Initial(List)==false){
			return(false);
		}
	}

	if(PIOBrd!=NULL)
        delete  []PIOBrd;
	if(AIP_IO_GetIOBoardNumb!=NULL){
		PIO_BoardNumb=AIP_IO_GetIOBoardNumb();
	}
    if(PIO_BoardNumb==0)
        return(true);
    PIOBrd=new EachPIOClass[PIO_BoardNumb];
    for(int i=0;i<PIO_BoardNumb;i++){
        PIOBrd[i].Initialize(this);
        PIOBrd[i].SetBoardNumber(i);
        }
    for(int i=0;i<PIO_BoardNumb;i++){
		QString	TmpSomething=Something;
		for(PIOBrdSomethingList *c=BrdSomethingListContainer.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->BrdNo==i){
				TmpSomething=c->Something;
				break;
			}
		}
		PIOBrd[i].Open(mainW,TmpSomething);
	}

	if(InitialOutput==false){
	    for(int k=0;k<PIO_BoardNumb;k++){
			PIOBrd[k].InitialOutput();
		}
	}

    Initialized=true;
	return(true);
}

BYTE    PIOInterface::GetByteInvolved(int brdnumb ,int portno)
{
    if(brdnumb>=0 && brdnumb<PIO_BoardNumb){
        return(PIOBrd[brdnumb].GetByte(portno));
        }
    return(0);
}

int		PIOInterface::GetIOInBitCount	(int brdnumb)
{
	if(brdnumb>=0 && brdnumb<PIO_BoardNumb){
		return PIOBrd[brdnumb].GetIOInBitCount();
	}
	return 0;
}

int		PIOInterface::GetIOOutBitCount	(int brdnumb)
{
	if(brdnumb>=0 && brdnumb<PIO_BoardNumb){
		return PIOBrd[brdnumb].GetIOOutBitCount();
	}
	return 0;
}


BYTE    PIOInterface::GetByte(int brdnumb ,int portno)
{
    if(Psu==false){
        BYTE    ret=0;
        if(brdnumb>=0 && brdnumb<PIO_BoardNumb)
            ret=PIOBrd[brdnumb].GetByte(portno);
        return(ret);
        }
    else{
        if(brdnumb>=0 && brdnumb<PIO_BoardNumb)
            return(PIOBrd[brdnumb].GetBufferedInByte(portno));
        return(0);
        }
}
int     PIOInterface::GetBit(int brdnumb ,int portno ,int bitno)
{
    if(Psu==false){
        int     ret=0;
        if(brdnumb>=0 && brdnumb<PIO_BoardNumb)
            ret=PIOBrd[brdnumb].GetBit(portno,bitno);
        return(ret);
        }
    else{
        if(brdnumb>=0 && brdnumb<PIO_BoardNumb){
            if((PIOBrd[brdnumb].GetBufferedInByte(portno)&(0x01<<bitno))!=0)
                return(1);
            }
        return(0);
        }
}

void	EachPIOClass::PutByteData(int portno,BYTE data)
{
	if(portno<PIO_OUTBITNUMB/8){
		OutData[portno]=data;
	}
}

void	EachPIOClass::PutBitData(int portno,int bitno ,BYTE data)
{
	if(portno<PIO_OUTBITNUMB/8){
		if(data==0){
			OutData[portno] &= ~(0x01<<bitno);
		}
		else{
			OutData[portno] |=  (0x01<<bitno);
		}
	}
}
void    PIOInterface::SetByte(int brdnumb ,int portno ,BYTE data)
{
    if(Psu==false){
        if(brdnumb>=0 && brdnumb<PIO_BoardNumb)
            PIOBrd[brdnumb].SetByte(portno,data);
        }
    else{
        if(brdnumb>=0 && brdnumb<PIO_BoardNumb && portno>=0){
			PIOBrd[brdnumb].PutByteData(portno,data);
		}
        Changed=false;
        while(Changed==false)
            GSleep(10);
        }
}

void     PIOInterface::SetBit(int brdnumb ,int portno ,int bitno  ,BYTE data)
{
    if(Psu==false){
        if(brdnumb>=0 && brdnumb<PIO_BoardNumb)
            PIOBrd[brdnumb].SetBit(portno,bitno,data);
        return;
        }
    else{
        if(brdnumb>=0 && brdnumb<PIO_BoardNumb && portno>=0){
			PIOBrd[brdnumb].PutBitData(portno,bitno ,data);
		}
        Changed=false;
        while(Changed==false)
            GSleep(10);
        }
}
	
bool	PIOInterface::SetBit(const QString &OutBitName,BYTE data)
{
	for(int i=0;i<PIO_BoardNumb;i++){
		int	N=PIOBrd[i].GetIOOutBitCount();
		for(int k=0;k<N;k++){
			if(PIOBrd[i].GetOutBitName(k)==OutBitName){
				PIOBrd[i].SetBit(k>>3,k&7,data);
				return true;
			}
		}
	}
	return false;
}

bool	PIOInterface::GetBit(const QString &InBitName,BYTE &data)
{
	for(int i=0;i<PIO_BoardNumb;i++){
		int	N=PIOBrd[i].GetIOInBitCount();
		for(int k=0;k<N;k++){
			if(PIOBrd[i].GetInBitName(k)==InBitName){
				data=PIOBrd[i].GetBit(k>>3,k&7);
				return true;
			}
		}
	}
	return false;
}

bool	PIOInterface::GetEchobackBit(const QString &OutBitName,BYTE &data)
{
	for(int i=0;i<PIO_BoardNumb;i++){
		int	N=PIOBrd[i].GetIOOutBitCount();
		for(int k=0;k<N;k++){
			if(PIOBrd[i].GetOutBitName(k)==OutBitName){
				data=PIOBrd[i].GetEchobackOutBit(k);
				return true;
			}
		}
	}
	return false;
}

BYTE    PIOInterface::GetOutByte(int brdnumb ,int portno)
{
    if(brdnumb>=0 && brdnumb<PIO_BoardNumb)
        return(PIOBrd[brdnumb].GetOutByte(portno));
    return(0);
}

int     PIOInterface::GetEchobackOutBit(int brdnumb ,int bitno)
{
   if(brdnumb>=0 && brdnumb<PIO_BoardNumb)
        return(PIOBrd[brdnumb].GetEchobackOutBit(bitno));
    return(0);
}

BYTE    PIOInterface::GetEchobackOutByte(int brdnumb ,int portno)
{
   if(brdnumb>=0 && brdnumb<PIO_BoardNumb)
        return(PIOBrd[brdnumb].GetEchobackOutByte(portno));
    return(0);
}

int     PIOInterface::GetOutBit(int brdnumb ,int bitno)
{
    if(brdnumb>=0 && brdnumb<PIO_BoardNumb)
        return(PIOBrd[brdnumb].GetOutBit(bitno));
    return(0);
}

BYTE    PIOInterface::GetBufferedInByte(int brdnumb ,int portno)
{
    if(brdnumb>=0 && brdnumb<PIO_BoardNumb)
        return(PIOBrd[brdnumb].GetBufferedInByte(portno));
    return(0);
}

BYTE    PIOInterface::GetBufferedOutByte(int brdnumb ,int portno)
{
    if(brdnumb>=0 && brdnumb<PIO_BoardNumb)
        return(PIOBrd[brdnumb].GetBufferedOutByte(portno));
    return(0);
}

void    PIOInterface::LoopIO(void)
{
    for(int k=0;k<PIO_BoardNumb;k++){
		PIOBrd[k].LoopIO();
        }
    Changed=true;
}
void    PIOInterface::LoopOnIdle(void)
{
    for(int k=0;k<PIO_BoardNumb;k++){
		PIOBrd[k].LoopOnIdle();
    }
}



bool    PIOInterface::ReadDefFile(const QString &FileName,bool DefaultOut)

{
    FILE    *file;
    char    *fp;
	char	FileNameBuff[257];

	QFileInfo fi(FileName);
	if(fi.suffix().isEmpty()==true){
		QString	F=FileName+QString(".")+GetDynamicFileExt();
		QString2Char(F ,FileNameBuff,sizeof(FileNameBuff));
	}
	else{
		QString2Char(FileName ,FileNameBuff,sizeof(FileNameBuff));
	}

    if((file=fopen(FileNameBuff,"rt"))==NULL)
        return(false);
    char    buff[256];
    int     N=0;
	QTextStream	TxtStream(file);
	//while(TxtStream.atEnd()==false){

    while(fgets(buff, sizeof(buff)-1, file)!=NULL){
        NextBoard:;
        fp=buff;
        while(*fp==' ' || *fp=='\t')
            fp++;
        if(strnicmp(fp,"BOARD",5)==0){
            if(N>=PIO_BoardNumb)
                continue;
            fp+=5;
            while(*fp==' ' || *fp=='\t')
                fp++;
            int d;
            if(sscanf(fp,"%d",&d)!=1)
                continue;
            if(d>=0 && d<PIO_BoardNumb){
                PIOBrd[N].SetBoardNumber(d);
                }
            buff[0]=0;
            if(PIOBrd[N].ReadDefFile(file,buff,sizeof(buff),DefaultOut)==false)
                break;
            N++;
            goto    NextBoard;
            }
        else
        if(N==0 && *fp!='\n'){
            if(N>=PIO_BoardNumb)
                continue;
            PIOBrd[N].SetBoardNumber(0);
            if(PIOBrd[N].ReadDefFile(file,buff,sizeof(buff),DefaultOut)==false)
                break;
            N++;
            goto    NextBoard;
            }
        }
    for(int i=0;i<PIO_BoardNumb-1;i++){
        if(PIOBrd[i].GetBoardNumber()>PIOBrd[i+1].GetBoardNumber()){
            EachPIOClass    TmpD;
			TmpD=PIOBrd[i];
            PIOBrd[i]=PIOBrd[i+1];
            PIOBrd[i]=TmpD;
            }
        }
    fclose(file);

    return(true);
}

bool    PIOInterface::ReadDefFileOfBoardName(const QString &FileName)
{
    FILE    *file;
    char    *fp;
	char	FileNameBuff[257];

	QFileInfo fi(FileName);
	if(fi.suffix().isEmpty()==true){
		QString	F=FileName+QString(".")+GetDynamicFileExt();
		QString2Char(F ,FileNameBuff,sizeof(FileNameBuff));
	}
	else{
		QString2Char(FileName ,FileNameBuff,sizeof(FileNameBuff));
	}

    if((file=fopen(FileNameBuff,"rt"))==NULL)
        return(false);
    char    buff[256];
    while(fgets(buff, sizeof(buff)-1, file)!=NULL){
        fp=buff;
        while(*fp==' ' || *fp=='\t')
            fp++;
        if(strnicmp(fp,"BOARD",5)==0){
            fp+=5;
            while(*fp==' ' || *fp=='\t')
                fp++;
            int d;
            if(sscanf(fp,"%d",&d)!=1)
                continue;
			fp=strchr(fp,',');
			if(fp!=NULL){
				fp++;
	            while(*fp==' ' || *fp=='\t')
		            fp++;
				char *gp=strpbrk(fp," \t\n");
				if(gp!=NULL){
					char	HBuff[200];
					int		Len=gp-fp;
					memcpy(HBuff,fp,Len);
					HBuff[Len]=0;
					SetBoardName(d,HBuff);
				}
			}
        }
        if(strnicmp(fp,"BRDINFO",7)==0){
            fp+=7;
            while(*fp==' ' || *fp=='\t')
                fp++;
            int d;
            if(sscanf(fp,"%d",&d)!=1)
                continue;
			fp=strchr(fp,',');
			if(fp!=NULL){
				fp++;
	            while(*fp==' ' || *fp=='\t')
		            fp++;
				char *gp=strpbrk(fp," \t\n");
				if(gp==NULL)
					gp=strchr(fp,0);
				if(gp!=NULL){
					char	HBuff[200];
					int		Len=gp-fp;
					memcpy(HBuff,fp,Len);
					HBuff[Len]=0;
					SetSomething(d,HBuff);
				}
			}
		}
	}
    fclose(file);
    return(true);
}

int		PIOInterface::GetIOInBitCount(void *handle ,int boardNumber)
{
	if(AIP_IO_GetIOInBitCount!=NULL){
		return AIP_IO_GetIOInBitCount (handle ,boardNumber);
	}
	return 0;
}
int		PIOInterface::GetIOOutBitCount(void *handle ,int boardNumber)
{
	if(AIP_IO_GetIOOutBitCount!=NULL){
		return AIP_IO_GetIOOutBitCount(handle ,boardNumber);
	}
	return 0;
}
void	*PIOInterface::Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize ,const QString &Something)
{
	if(AIP_IO_Open!=NULL){
		void	*Handle=AIP_IO_Open(mainW,boardNumber , name ,maxbuffsize,Something);
		if(Handle!=NULL){
			return Handle;
		}
		::SendErrorMessage(/**/"PIO::Open(AIP_IO_Open) returns NULL, Can not get handle");
	}
	else{
		::SendErrorMessage(/**/"PIO : No AIP_IO_Ope function is loaded");
	}
	
	return NULL;
}
bool	PIOInterface::Close(void *handle ,int boardNumber)
{
	if(AIP_IO_Close!=NULL){
		if(AIP_IO_Close(handle ,boardNumber)==false){
			return(false);
		}
		return true;
	}
	return false;
}
BYTE	PIOInterface::IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex)
{
	if(AIP_IO_GetBit!=NULL){
		return AIP_IO_GetBit(handle ,boardNumber , bitIndex);
	}
	return 0;
}
BYTE	PIOInterface::IO_GetByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	if(AIP_IO_GetByte!=NULL){
		return AIP_IO_GetByte(handle ,boardNumber , byteIndex);
	}
	return 0;
}

bool	PIOInterface::IO_SetBit(void *handle ,int boardNumber , BYTE bitIndex , BYTE data)
{
	if(AIP_IO_SetBit!=NULL){
		AIP_IO_SetBit(handle ,boardNumber , bitIndex , data);
		return true;
	}
	return false;
}

bool	PIOInterface::IO_SetByte(void *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	if(AIP_IO_SetByte!=NULL){
		AIP_IO_SetByte(handle ,boardNumber , byteIndex , data);
		return true;
	}
	return false;
}

int		PIOInterface::IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	if(AIP_IO_GetOutByte!=NULL){
		return AIP_IO_GetOutByte(handle ,boardNumber ,byteIndex);
	}
	return 0;
}
int		PIOInterface::IO_GetOutBit(void *handle ,int boardNumber , BYTE bitIndex)
{
	if(AIP_IO_GetOutBit!=NULL){
		return AIP_IO_GetOutBit(handle ,boardNumber ,bitIndex);
	}
	else{
		if(AIP_IO_GetOutByte!=NULL){
			int	d=AIP_IO_GetOutByte(handle ,boardNumber ,bitIndex>>3);
			if((d & (1<<(bitIndex&7)))!=0)
				return 1;
			return 0;
		}
	}
	return 0;
}


bool    PIOInterface::WriteDefFile(const QString &FileName)
{
    FILE    *file;
	char	FileNameBuff[257];

	QString2Char(FileName ,FileNameBuff,sizeof(FileNameBuff));
    if((file=fopen(FileNameBuff,"wt"))==NULL)
        return(false);

    for(int b=0;b<PIO_BoardNumb;b++){
        fprintf(file,"BOARD %d\n",b);
        if(PIOBrd[b].WriteDefFile(file)==false){
            fclose(file);
            return(false);
            }
        }
    fclose(file);
    return(true);
}

void	PIOInterface::SetBoardName(int brdNo,const QString &BrdName)
{
	BrdNameListContainer.AppendList(new PIOBrdNameList(brdNo,BrdName));
}

void	PIOInterface::SetSomething(int brdNo,const QString &Something)
{
	BrdSomethingListContainer.AppendList(new PIOBrdSomethingList(brdNo,Something));
}
QString	PIOInterface::GetBoardName(int brdNo)	const
{
	PIOBrdNameList	*s=BrdNameListContainer.GetItem(brdNo);
	if(s!=NULL){
		return s->BrdName;
	}
	return QString(/**/"");
}
//===========================================================================
PIOClass::PIOClass(LayersBase *base,bool psu)
:ServiceForLayers(base)
{
	Interface=new PIOInterface(base,psu);
}
PIOClass::~PIOClass(void)
{
	delete	Interface;
	Interface=NULL;
}

bool	PIOClass::IsPIODLL(void)	const
{
	return Interface->IsPIODLL();
}
bool	PIOClass::LoadDLL(const QString &filename,bool OutputErrorMessage)
{
	return Interface->LoadDLL(filename,OutputErrorMessage);
}

bool    PIOClass::Initialize(QWidget *mainW,const QString &IODLLFileName,bool InitialOutput ,const QString &Something)
{
	if(Interface->Initialize(mainW,IODLLFileName,InitialOutput ,Something)==false){
		return false;
	}
	bool	Ret=true;
	for(int i=0;i<GetBoardCount();i++){
		EachPIOClass    *e=GetPIOBrd(i);
		bool	R=connect(e,SIGNAL(SignalLogOutBit(int ,int ,int ,int ,unsigned int ,int))
				,this,SLOT(SlotLogOutBit(int ,int,int,int ,unsigned int ,int))
				,Qt::QueuedConnection);
		if(R==false){
			Ret=false;
		}
	}
	return Ret;
}

void	PIOClass::SlotLogOutBit(int BoardNumber 
								,int portno,int bitno ,int data 
								,unsigned int MiliSec
								,int SepTime)
{
	QString	FilePath=GetLayersBase()->GetUserPath()
					+QDir::separator()
					+QString(/**/"PIOLog");
	QDate	NowDate=QDate::currentDate();
	static	QDate	CheckedDate;
	if(NowDate!=CheckedDate){
		CheckedDate=NowDate;
		QDir	FDir(FilePath);
		if(FDir.exists()==false){
			FDir.mkpath(FilePath);
		}

		QStringList NameFilters;
		NameFilters.append(/**/"IOLog_*.log");
		QFileInfoList	FInfo=FDir.entryInfoList(NameFilters,QDir::Files);
		for(int i=0;i<FInfo.count();i++){
			QString	s=FInfo[i].baseName();
			QString	DateStr=s.mid(6);
			QDate	d=QDate::fromString(DateStr,/**/"yyyyMMdd");
			if(d.daysTo(NowDate)>7){
				QFile::remove(FInfo[i].absoluteFilePath());
			}
		}
	}
	QString	FileName=FilePath
					+QDir::separator()
					+QString(/**/"IOLog_")
					+NowDate.toString(/**/"yyyyMMdd")
					+QString(/**/".log");
	QFile	File(FileName);
	if(File.open(QIODevice::Append)==true){
		QTextStream	Txt(&File);
		QDateTime	CDTime=QDateTime::currentDateTime();
		QString	s=CDTime.toString("dd-hh:mm:ss")
				+ QString(",")
				+ QString::number(SepTime)
				+ QString(" : ")
				+ QString::number(BoardNumber)
				+ QString(",")
				+ QString::number(portno)
				+ QString(",")
				+ QString::number(bitno)
				+ QString(" = ")
				+ ((data==0)?QString("0"):QString("1"))
				+ QString("\n");
		Txt<<s;
	}
}

void	PIOClass::GetExportFunctions(QStringList &Str)
{
	return Interface->GetExportFunctions(Str);
}
QString	PIOClass::GetFileName(void)	const
{
	return Interface->GetFileName();
}

QString	PIOClass::GetCopyright(void)	const
{
	return Interface->GetCopyright();
}
QString	PIOClass::GetName(void)	const
{
	return Interface->GetName();
}
WORD	PIOClass::GetVersion(void)	const
{
	return Interface->GetVersion();
}
WORD	PIOClass::GetDLLType(void)	const
{
	return Interface->GetDLLType();
}
QString	PIOClass::GetExplain(void)	const
{
	return Interface->GetExplain();
}

EachPIOClass    *PIOClass::GetPIOBrd(int brdnumb)
{
	return Interface->GetPIOBrd(brdnumb);
}

BYTE    PIOClass::GetByteInvolved	(int brdnumb ,int portno)
{
	return Interface->GetByteInvolved(brdnumb,portno);
}
BYTE    PIOClass::GetByte			(int brdnumb ,int portno)
{
	return Interface->GetByte(brdnumb,portno);
}
int     PIOClass::GetBit			(int brdnumb ,int portno ,int bitno)
{
	return Interface->GetBit(brdnumb,portno,bitno);
}
void    PIOClass::SetByte			(int brdnumb ,int portno ,BYTE data)
{
	return Interface->SetByte(brdnumb,portno,data);
}
void    PIOClass::SetBit			(int brdnumb ,int portno ,int bitno  ,BYTE data)
{
	return Interface->SetBit(brdnumb ,portno ,bitno  ,data);
}

BYTE    PIOClass::GetOutByte			(int brdnumb ,int portno)
{
	return Interface->GetOutByte(brdnumb,portno);
}
int     PIOClass::GetOutBit			(int brdnumb ,int bitno)
{
	return Interface->GetOutBit(brdnumb,bitno);
}
BYTE    PIOClass::GetBufferedInByte	(int brdnumb ,int portno)
{
	return Interface->GetBufferedInByte(brdnumb,portno);
}
BYTE    PIOClass::GetBufferedOutByte	(int brdnumb ,int portno)
{
	return Interface->GetBufferedOutByte(brdnumb,portno);
}
int		PIOClass::GetIOInBitCount		(int brdnumb)
{
	return Interface->GetIOInBitCount(brdnumb);
}
int		PIOClass::GetIOOutBitCount	(int brdnumb)
{
	return Interface->GetIOOutBitCount(brdnumb);
}

bool	PIOClass::SetBit(const QString &OutBitName,BYTE data)
{
	return Interface->SetBit(OutBitName,data);
}
bool	PIOClass::GetBit(const QString &InBitName ,BYTE &data)
{
	return Interface->GetBit(InBitName,data);
}
bool	PIOClass::GetEchobackBit(const QString &OutBitName ,BYTE &data)
{
	return Interface->GetEchobackBit(OutBitName,data);
}

int		PIOClass::GetIOInBitCount		(void *handle ,int boardNumber)
{
	return Interface->GetIOInBitCount(handle,boardNumber);
}
int		PIOClass::GetIOOutBitCount	(void *handle ,int boardNumber)
{
	return Interface->GetIOOutBitCount(handle,boardNumber);
}
void	*PIOClass::Open				(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	return Interface->Open(mainW,boardNumber , name ,maxbuffsize,Something);
}
bool	PIOClass::Close				(void *handle ,int boardNumber)
{
	return Interface->Close(handle,boardNumber);
}

BYTE	PIOClass::IO_GetBit		(void *handle ,int boardNumber , BYTE bitIndex)
{
	return Interface->IO_GetBit(handle,boardNumber,bitIndex);
}
BYTE	PIOClass::IO_GetByte		(void *handle ,int boardNumber , BYTE byteIndex)
{
	return Interface->IO_GetByte(handle,boardNumber,byteIndex);
}
bool	PIOClass::IO_SetBit		(void *handle ,int boardNumber , BYTE bitIndex , BYTE data)
{
	return Interface->IO_SetBit(handle,boardNumber,bitIndex,data);
}
bool	PIOClass::IO_SetByte		(void *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	return Interface->IO_SetByte(handle,boardNumber,byteIndex,data);
}
int		PIOClass::IO_GetOutByte	(void *handle ,int boardNumber , BYTE byteIndex)
{
	return Interface->IO_GetOutByte(handle,boardNumber,byteIndex);
}
int		PIOClass::IO_GetOutBit	(void *handle ,int boardNumber , BYTE bitIndex)
{
	return Interface->IO_GetOutBit(handle,boardNumber,bitIndex);
}
int     PIOClass::GetEchobackOutBit(int boardNumber , int bitno)
{
	return Interface->GetEchobackOutBit(boardNumber,bitno);
}
BYTE    PIOClass::GetEchobackOutByte(int boardNumber , int portno)
{
	return Interface->GetEchobackOutByte(boardNumber,portno);
}

void	PIOClass::LoopIO(void)
{
	Interface->LoopIO();
}

int		PIOClass::GetBoardCount(void)	const
{
	return Interface->GetBoardCount();
}
void	PIOClass::SetBoardName(int brdNo,const QString &BrdName)
{
	Interface->SetBoardName(brdNo,BrdName);
}
void	PIOClass::SetSomething(int brdNo,const QString &Something)
{
	Interface->SetSomething(brdNo,Something);
}
QString	PIOClass::GetBoardName(int brdNo)	const
{
	return Interface->GetBoardName(brdNo);
}
void	PIOClass::LoopOnIdle(void *handle ,int boardNumber)
{
	return Interface->LoopOnIdle(handle,boardNumber);
}
void	PIOClass::LoopOnIdle(void)
{
	Interface->LoopOnIdle();
}

bool    PIOClass::ReadDefFile (const QString &FileName,bool DefaultOut)
{
	return Interface->ReadDefFile(FileName,DefaultOut);
}
bool    PIOClass::WriteDefFile(const QString &FileName)
{
	return Interface->WriteDefFile(FileName);
}
bool    PIOClass::ReadDefFileOfBoardName(const QString &FileName)
{
	return Interface->ReadDefFileOfBoardName(FileName);
}

const QString	&PIOClass::GetInBitName(int brdNo ,int bitNo)	const
{
	return Interface->GetInBitName(brdNo,bitNo);
}
const QString	&PIOClass::GetOutBitName(int brdNo ,int bitNo)	const
{
	return Interface->GetOutBitName(brdNo,bitNo);
}

bool	PIOClass::GetRelatedDLL(QStringList &DLLFileNames)
{
	return Interface->GetRelatedDLL(DLLFileNames);
}
char	*PIOClass::GetRelatedDLLSystemVersion(const QString &DLLFileName ,VersionType vtype)
{
	return Interface->GetRelatedDLLSystemVersion(DLLFileName ,vtype);
}
const char	*PIOClass::GetSystemVersion(VersionType vtype)
{
	return Interface->GetSystemVersion(vtype);
}

bool	PIOClass::CheckSystemVersionFunc(QStringList &Str 
						   ,const QString &DLLType 
						   ,const QString &DLLRoot 
						   ,const QString &DLLName)
{
	return Interface->CheckSystemVersionFunc(Str 
											,DLLType 
											,DLLRoot 
											,DLLName);
}

//===========================================================================

int	PIOClassPack::SearchAddDLL(int32 &ErrorCode,bool OutputErrorMessage)
{
	int	Ret=0;
	RemoveAll();

	QString	Path=GetLayersBase()->GetSystemPath();
	if(Path.right(1)!="\\" && Path.right(1)!="/"){
		Path=Path+GetSeparator();
	}
	Path=Path+DefPluginDLLPath;

	QDir	Dir;
	if(Dir.cd(Path)==true){
		QString	SearchFile=QString("*.")+GetDynamicFileExt();
		QStringList nameFilters(SearchFile);
		QStringList List=Dir.entryList ( nameFilters, QDir::Files, QDir::NoSort );

		for(int i=0;i<List.size();i++){
			QString	FileName=Path+GetSeparator()+List[i];
			if(FileName.isEmpty()==false){
				PIOClass	*a=new PIOClass(GetLayersBase(),false);
				if(a->LoadDLL(FileName,OutputErrorMessage)==true && a->IsPIODLL()==true){
					AppendList(a);
					Ret++;
				}
				else{
					delete	a;
				}
			}
		}
	}
	return Ret;
}






