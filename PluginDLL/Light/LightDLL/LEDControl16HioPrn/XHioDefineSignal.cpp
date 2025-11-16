#include "XHioDefineSignal.h"
#include "XGeneralFunc.h"

QString	HioPortDefinition::GetTypeName(int PortType,int BitNo)
{
	switch(PortType){
	case DefPortPIOAIN	:	return QString(/**/"PIOAIN ")+ QString::number(BitNo);
	case DefPortPIOBIN	:	return QString(/**/"PIOBIN ")+ QString::number(BitNo);
	case DefPortPIOCIN	:	return QString(/**/"PIOCIN ")+ QString::number(BitNo);
	case DefPortPIODIN	:	return QString(/**/"PIODIN ")+ QString::number(BitNo);
	case DefPortPIOAOUT	:	return QString(/**/"PIOAOUT ")+ QString::number(BitNo);
	case DefPortPIOBOUT	:	return QString(/**/"PIOBOUT ")+ QString::number(BitNo);
	case DefPortPIOCOUT	:	return QString(/**/"PIOCOUT ")+ QString::number(BitNo);
	case DefPortPIODOUT	:	return QString(/**/"PIODOUT ")+ QString::number(BitNo);
	case DefPortGIN		:	return QString(/**/"GIN ")+ QString::number(BitNo);
	case DefPortGOUT	:	return QString(/**/"GOUT ")+ QString::number(BitNo);
	case DefPortTRGIN	:	return QString(/**/"TRGIN ")+ QString::number(BitNo);
	case DefPortOuterSW	:	return QString(/**/"OuterSW");
	case DefPortExtDirect:	return QString(/**/"ExtDirect");
	}
	return "";
}

QString	HioPortDefinition::GetString(int PortType ,int BitNo)
{
	switch(PortType){
	case DefPortPIOAIN	:	return StrPIOAIN[BitNo];
	case DefPortPIOBIN	:	return StrPIOBIN[BitNo];
	case DefPortPIOCIN	:	return StrPIOCIN[BitNo];
	case DefPortPIODIN	:	return StrPIODIN[BitNo];
	case DefPortPIOAOUT	:	return StrPIOAOUT[BitNo];
	case DefPortPIOBOUT	:	return StrPIOBOUT[BitNo];
	case DefPortPIOCOUT	:	return StrPIOCOUT[BitNo];
	case DefPortPIODOUT	:	return StrPIODOUT[BitNo];
	case DefPortGIN		:	return StrGIN[BitNo];
	case DefPortGOUT	:	return StrGOUT[BitNo];
	case DefPortTRGIN	:	return StrTRGIN[BitNo];
	case DefPortOuterSW	:	return StrOuterSW;
	case DefPortExtDirect:	return StrExtDirect;
	}
	return "";
}

void	HioPortDefinition::SetString(int PortType ,int BitNo ,const QString &s)
{
	switch(PortType){
	case DefPortPIOAIN	:	StrPIOAIN[BitNo]	=s;	break;
	case DefPortPIOBIN	:	StrPIOBIN[BitNo]	=s;	break;
	case DefPortPIOCIN	:	StrPIOCIN[BitNo]	=s;	break;
	case DefPortPIODIN	:	StrPIODIN[BitNo]	=s;	break;
	case DefPortPIOAOUT	:	StrPIOAOUT[BitNo]	=s;	break;
	case DefPortPIOBOUT	:	StrPIOBOUT[BitNo]	=s;	break;
	case DefPortPIOCOUT	:	StrPIOCOUT[BitNo]	=s;	break;
	case DefPortPIODOUT	:	StrPIODOUT[BitNo]	=s;	break;
	case DefPortGIN		:	StrGIN[BitNo]		=s;	break;
	case DefPortGOUT	:	StrGOUT[BitNo]		=s;	break;
	case DefPortTRGIN	:	StrTRGIN[BitNo]		=s;	break;
	case DefPortOuterSW	:	StrOuterSW			=s;	break;
	case DefPortExtDirect:	StrExtDirect		=s;	break;
	}
}

bool	HioPortDefinition::GetSignal(int PortType ,int BitNo ,struct  TimingData &d)
{
	switch(PortType){
	case DefPortPIOAIN	:
		if(BitNo==0)	return d.RealData.PIOAIN0;
		if(BitNo==1)	return d.RealData.PIOAIN1;
		if(BitNo==2)	return d.RealData.PIOAIN2;
		if(BitNo==3)	return d.RealData.PIOAIN3;
		break;
	case DefPortPIOBIN	:
		if(BitNo==0)	return d.RealData.PIOBIN0;
		if(BitNo==1)	return d.RealData.PIOBIN1;
		if(BitNo==2)	return d.RealData.PIOBIN2;
		if(BitNo==3)	return d.RealData.PIOBIN3;
		break;
	case DefPortPIOCIN	:
		if(BitNo==0)	return d.RealData.PIOCIN0;
		if(BitNo==1)	return d.RealData.PIOCIN1;
		if(BitNo==2)	return d.RealData.PIOCIN2;
		if(BitNo==3)	return d.RealData.PIOCIN3;
		break;
	case DefPortPIODIN	:
		if(BitNo==0)	return d.RealData.PIODIN0;
		if(BitNo==1)	return d.RealData.PIODIN1;
		if(BitNo==2)	return d.RealData.PIODIN2;
		if(BitNo==3)	return d.RealData.PIODIN3;
		break;
	case DefPortPIOAOUT	:
		if(BitNo==0)	return d.RealData.PIOAOUT0;
		if(BitNo==1)	return d.RealData.PIOAOUT1;
		if(BitNo==2)	return d.RealData.PIOAOUT2;
		if(BitNo==3)	return d.RealData.PIOAOUT3;
		break;
	case DefPortPIOBOUT	:
		if(BitNo==0)	return d.RealData.PIOBOUT0;
		if(BitNo==1)	return d.RealData.PIOBOUT1;
		if(BitNo==2)	return d.RealData.PIOBOUT2;
		if(BitNo==3)	return d.RealData.PIOBOUT3;
		break;
	case DefPortPIOCOUT	:
		if(BitNo==0)	return d.RealData.PIOCOUT0;
		if(BitNo==1)	return d.RealData.PIOCOUT1;
		if(BitNo==2)	return d.RealData.PIOCOUT2;
		if(BitNo==3)	return d.RealData.PIOCOUT3;
		break;
	case DefPortPIODOUT	:
		if(BitNo==0)	return d.RealData.PIODOUT0;
		if(BitNo==1)	return d.RealData.PIODOUT1;
		if(BitNo==2)	return d.RealData.PIODOUT2;
		if(BitNo==3)	return d.RealData.PIODOUT3;
		break;
	case DefPortGIN		:
		if(BitNo==0)	return d.RealData.GIN0;
		if(BitNo==1)	return d.RealData.GIN1;
		if(BitNo==2)	return d.RealData.GIN2;
		if(BitNo==3)	return d.RealData.GIN3;
		break;
	case DefPortGOUT	:
		if(BitNo==0)	return d.RealData.GOUT0;
		if(BitNo==1)	return d.RealData.GOUT1;
		if(BitNo==2)	return d.RealData.GOUT2;
		if(BitNo==3)	return d.RealData.GOUT3;
		break;
	case DefPortTRGIN	:
		if(BitNo==0)	return d.RealData.TRGIN0;
		if(BitNo==1)	return d.RealData.TRGIN1;
		if(BitNo==2)	return d.RealData.TRGIN2;
		if(BitNo==3)	return d.RealData.TRGIN3;
		break;
	case DefPortOuterSW	:	return d.RealData.OuterSW;
	case DefPortExtDirect:	return d.RealData.ExtDirect;
	}
	return false;
}

bool    HioPortDefinition::Save(QIODevice *f)
{
	int32	Ver=1;
    if(::Save(f,Ver)==false){
        return false;
	}
	for(int i=0;i<4;i++){
		if(::Save(f,StrPIOAIN[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Save(f,StrPIOBIN[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Save(f,StrPIOCIN[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Save(f,StrPIODIN[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Save(f,StrPIOAOUT[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Save(f,StrPIOBOUT[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Save(f,StrPIOCOUT[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Save(f,StrPIODOUT[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Save(f,StrGIN[i])==false)	return false;
	}
	for(int i=0;i<8;i++){
		if(::Save(f,StrGOUT[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Save(f,StrTRGIN[i])==false)	return false;
	}
	if(::Save(f,StrOuterSW)==false)		return false;
	if(::Save(f,StrExtDirect)==false)	return false;
	return true;
}
bool    HioPortDefinition::Load(QIODevice *f)
{
	int32	Ver;
    if(::Load(f,Ver)==false){
        return false;
	}
	for(int i=0;i<4;i++){
		if(::Load(f,StrPIOAIN[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Load(f,StrPIOBIN[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Load(f,StrPIOCIN[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Load(f,StrPIODIN[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Load(f,StrPIOAOUT[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Load(f,StrPIOBOUT[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Load(f,StrPIOCOUT[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Load(f,StrPIODOUT[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Load(f,StrGIN[i])==false)	return false;
	}
	for(int i=0;i<8;i++){
		if(::Load(f,StrGOUT[i])==false)	return false;
	}
	for(int i=0;i<4;i++){
		if(::Load(f,StrTRGIN[i])==false)	return false;
	}
	if(::Load(f,StrOuterSW)==false)		return false;
	if(::Load(f,StrExtDirect)==false)	return false;
	return true;
}