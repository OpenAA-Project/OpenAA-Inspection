#include "XIOLogThread.h"
#include "XSequence.h"
#include "XPIOButton.h"
#include "XGeneralFunc.h"
#include <string.h>
#include <stdio.h>

RegList::RegList(SeqControl *seq,const QString &RegStr)
{
	Ope=NULL;
	Operand *tOpe=seq->SearchReg(NULL,RegStr);
	LastDataB	=0;
	LastDataN	=0;
	LastDataD	=0;
	Changed		=true;
	if(tOpe!=NULL){
		QString2Char(tOpe->GetName(),StrName,sizeof(StrName));
	}
	Ope=tOpe;
}

bool	RegList::GetAndCompare(void)
{
	bool	DataB;
	int		DataN;
	double	DataD;
	QString	DataS;

	Changed=false;
	if(Ope!=NULL){
		switch(Ope->GetKindCode()){
			case KindCodeIO:
				DataN=Ope->GetNumeric();
				if(DataN!=LastDataN){
					Changed=true;
					LastDataN=DataN;
				}
				break;
			case KindCodeComm:
				DataN=Ope->GetNumeric();
				if(DataN!=LastDataN){
					Changed=true;
					LastDataN=DataN;
				}
				break;
			case KindCodeBit:
				DataB=((Ope->GetNumeric()&1)!=0)?true:false;
				if(DataB!=LastDataB){
					Changed=true;
					LastDataB=DataB;
				}
				break;
			case KindCodeWord:
				DataN=Ope->GetNumeric();
				if(DataN!=LastDataN){
					Changed=true;
					LastDataN=DataN;
				}
				break;
			case KindCodeString:
				DataS=Ope->GetString();
				if(DataS!=LastDataS){
					Changed=true;
					LastDataS=DataS;
				}
				break;
			case KindCodeSpecial:
				DataN=Ope->GetNumeric();
				if(DataN!=LastDataN){
					Changed=true;
					LastDataN=DataN;
				}
				break;
			case KindCodeSpeicalBit:
				DataB=((Ope->GetNumeric()&1)!=0)?true:false;
				if(DataB!=LastDataB){
					Changed=true;
					LastDataB=DataB;
				}
				break;
			case KindCodeSpeicalString:
				DataS=Ope->GetString();
				if(DataS!=LastDataS){
					Changed=true;
					LastDataS=DataS;
				}
				break;
			case KindCodeCharacter:
				DataS=Ope->GetString();
				if(DataS!=LastDataS){
					Changed=true;
					LastDataS=DataS;
				}
				break;
			case KindCodeGroup:
				DataN=Ope->GetNumeric();
				if(DataN!=LastDataN){
					Changed=true;
					LastDataN=DataN;
				}
				break;
			case KindCodeLanvar:
				DataN=Ope->GetNumeric();
				if(DataN!=LastDataN){
					Changed=true;
					LastDataN=DataN;
				}
				break;
			case KindCodeFifo:
				DataN=Ope->GetNumeric();
				if(DataN!=LastDataN){
					Changed=true;
					LastDataN=DataN;
				}
				break;
			case KindCodeFloat:
				DataD=Ope->GetFloat();
				if(DataD!=LastDataD){
					Changed=true;
					LastDataD=DataD;
				}
				break;
			case KindCodeLocalBit:
				DataB=((Ope->GetNumeric()&1)!=0)?true:false;
				if(DataB!=LastDataB){
					Changed=true;
					LastDataB=DataB;
				}
				break;
			case KindCodeLocalWord:
				DataN=Ope->GetNumeric();
				if(DataN!=LastDataN){
					Changed=true;
					LastDataN=DataN;
				}
				break;
			case KindCodeLocalString:
				DataS=Ope->GetString();
				if(DataS!=LastDataS){
					Changed=true;
					LastDataS=DataS;
				}
				break;
			case KindCodeLocalFloat:
				DataD=Ope->GetFloat();
				if(DataD!=LastDataD){
					Changed=true;
					LastDataD=DataD;
				}
				break;
		}
	}
	return Changed;
}

void	RegList::MakeStr(char Buff[])
{
	if(Ope!=NULL){
		strcpy(Buff,StrName);
		strcat(Buff,"=");
		char	*fp=strchr(Buff,0);
		switch(Ope->GetKindCode()){
			case KindCodeIO:
				I2Str(fp,LastDataN);
				break;
			case KindCodeComm:        
				I2Str(fp,LastDataN);
				break;
			case KindCodeBit:
				B2Str(fp,LastDataB);
				break;
			case KindCodeWord:
				I2Str(fp,LastDataN);
				break;
			case KindCodeString:
				QString2Char(LastDataS,fp,50);
				break;
			case KindCodeSpecial:
				I2Str(fp,LastDataN);
				break;
			case KindCodeSpeicalBit:
				B2Str(fp,LastDataB);
				break;
			case KindCodeSpeicalString:
				QString2Char(LastDataS,fp,50);
				break;
			case KindCodeCharacter:
				QString2Char(LastDataS,fp,50);
				break;
			case KindCodeGroup:
				I2Str(fp,LastDataN);
				break;
			case KindCodeLanvar:
				I2Str(fp,LastDataN);
				break;
			case KindCodeFifo:
				I2Str(fp,LastDataN);
				break;
			case KindCodeFloat:
				sprintf(fp,"%lf",LastDataD);
				break;
			case KindCodeLocalBit:
				B2Str(fp,LastDataB);
				break;
			case KindCodeLocalWord:
				I2Str(fp,LastDataN);
				break;
			case KindCodeLocalString:
				QString2Char(LastDataS,fp,50);
				break;
			case KindCodeLocalFloat:
				sprintf(fp,"%lf",LastDataD);
				break;
		}
	}
}

void	RegList::I2Str(char *s,int n)
{
	if(n<0){
		*s='-';
		s++;
		n=-n;
	}
	if(n==0){
		*s='0';
		s++;
		*s=0;
		return;
	}
	int	d=1;
	int	DimN;
	for(DimN=0;DimN<10;DimN++){
		if(d>n){
			break;
		}
		d*=10;
	}
	d/=10;
	for(int i=0;i<DimN;i++){
		int	k=n/d;
		n=n%d;
		*s=(char)('0'+k);
		d/=10;
		s++;
	}
	*s=0;
}
void	RegList::B2Str(char *s,bool n)
{
	if(n==true)
		strcpy(s,"1");
	else
		strcpy(s,"0");
}



ThreadIOLogger::ThreadIOLogger(SeqControl *seq)
{
	Seq=seq;
	PIOBoardNumber=Seq->PIO->GetBoardCount();

	if(PIOBoardNumber!=0){
		IBitCount=Seq->PIO->GetIOInBitCount(0);
		OBitCount=Seq->PIO->GetIOOutBitCount(0);
	}
}

void ThreadIOLogger::run()
{
	FILE	*f=fopen(FileName,"w+t");
	if(f!=NULL){
		char	buff[100];
		QString	A=XDateTime::currentDateTime().toString("yy/MM/dd hh:mm:ss.z");
		fprintf(f,"yy/MM/dd hh:mm:ss.z  IN:");
		for(int i=0;i<IBitCount/8;i++){
			fprintf(f,"01234567 ");
		}
		fprintf(f," OUT:");
		for(int i=0;i<OBitCount/8;i++){
			fprintf(f,"01234567 ");
		}
		fprintf(f,"\n");
		fclose(f);
	}
	for(;;){
		msleep(10);
		

		char	buff[200];
		BYTE	InByte[100];
		BYTE	OutByte[100];
		bool	Changed=false;

		for(int i=0;i<IBitCount/8;i++){
			InByte[i]=Seq->PIO->GetBufferedInByte(0,i);
		}
		for(int i=0;i<OBitCount/8;i++){
			OutByte[i]=Seq->PIO->GetBufferedOutByte(0,i);
		}
		for(RegList *L=RegDatas.GetFirst();L!=NULL;L=L->GetNext()){
			if(L->GetAndCompare()==true){
				Changed=true;
			}
		}

		for(int i=0;i<IBitCount/8;i++){
			if(InByte[i]!=LastInByte[i]){
				Changed=true;
			}
		}
		if(Changed==false){
			for(int i=0;i<OBitCount/8;i++){
				if(OutByte[i]!=LastOutByte[i]){
					Changed=true;
				}
			}
		}
		MutexMessage.lock();
		int	MesssageCount=PushedMesssages.count();
		MutexMessage.unlock();
		if(MesssageCount!=0){
			Changed=true;
		}

		if(Changed==true){
			f=fopen(FileName,"a+t");
			if(f!=NULL){
				QString	A=XDateTime::currentDateTime().toString("yy/MM/dd hh:mm:ss.zzz");
				::QString2Char(A,buff ,sizeof(buff));
				if(IBitCount/8!=0 || OBitCount/8!=0){
					strcat(buff," IN:");
					for(int i=0;i<IBitCount/8;i++){
						for(int b=0;b<8;b++){
							if((InByte[i] &(0x01<<b))!=0)
								strcat(buff,"1");
							else
								strcat(buff,"0");
						}
						strcat(buff," ");
						LastInByte[i]=InByte[i];
					}
					strcat(buff,"OUT:");
					for(int i=0;i<OBitCount/8;i++){
						for(int b=0;b<8;b++){
							if((OutByte[i] &(0x01<<b))!=0)
								strcat(buff,"1");
							else
								strcat(buff,"0");
						}
						strcat(buff," ");
						LastOutByte[i]=OutByte[i];
					}
				}
				strcat(buff,"\n");
				fputs(buff,f);

				if(RegDatas.GetFirst()!=NULL || MesssageCount!=0){
					strcpy(buff,"\t\t");
					for(RegList *L=RegDatas.GetFirst();L!=NULL;L=L->GetNext()){
						char	*fp=strchr(buff,0);
						L->MakeStr(fp);
						strcat(buff," ");
					}

					for(int i=0;i<MesssageCount;i++){
						MutexMessage.lock();
						QString A=PushedMesssages.first();
						PushedMesssages.removeFirst ();
						MutexMessage.unlock();
						char	Str[100];
						QString2Char(A,Str,sizeof(Str));
						strcat(buff,Str);
						strcat(buff," ");
					}
					strcat(buff,"\n");
					fputs(buff,f);
				}

				for(Sequence *s=Seq->Seq.GetFirst();s!=NULL;s=s->GetNext()){
					strcpy(buff,"\t\t");
					char	Str[100];
					QString2Char(s->GetSeqName(),Str,sizeof(Str));
					strcat(buff,Str);
					strcat(buff,"=");

					s->Lock();
					int	SLineIndex=s->GetSLineIndex(s->GetNowLine());
					SeqLine	*SL=s->GetSLine(s->GetNowLine());
					s->Unlock();

					if(SL==NULL){
						continue;
					}
					sprintf(Str,"%d",SLineIndex);
					strcat(buff,Str);
					strcat(buff,":");

					QString2Char(SL->GetName(),Str,sizeof(Str));
					strcat(buff,Str);
					if(SL->GetOpCount()!=0){
						strcat(buff,"\t");
					}
					for(int i=0;i<SL->GetOpCount();i++){
						QString2Char(SL->GetOpe(i)->GetName(),Str,sizeof(Str));
						strcat(buff,Str);
						strcat(buff,"(");
						QString2Char(SL->GetOpe(i)->GetString(),Str,sizeof(Str));
						strcat(buff,Str);
						strcat(buff,")");

						if(i<SL->GetOpCount()-1){
							strcat(buff,",");
						}
					}

					strcat(buff,"\n");
					fputs(buff,f);
				}

				fclose(f);
			}
		}
	}
}

void	ThreadIOLogger::AddReg(const QString &RegStr)
{
	RegDatas.AppendList(new RegList(Seq,RegStr));
}

void	ThreadIOLogger::AddMessage(const QString &Str)
{
	MutexMessage.lock();
	PushedMesssages.append(Str);
	MutexMessage.unlock();
}
