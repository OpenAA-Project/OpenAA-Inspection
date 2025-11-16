#include "LEDControl16D.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XHidCommand.h"
#include "LEDControl16DDialog.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"


void  SetCurrent(long MicroAmpare 
				,int      &Ki
				,unsigned char PGA[4]);

QString	LEDControl16DPanel::DefFileName=/**/"LEDControl16DDef.dat";

void	LEDControl16DPanel::DefUnit::DefBoard::DefLine::Set(int unitNo ,int boardNo ,int lineNo)
{	
	UnitNo		=unitNo;	
	BoardNo		=boardNo;	
	LineNo		=lineNo;	
	ColorType	=0;	
	MaxValue	=100;
	LightID		=0;
	EnableComparatorL	=0;
	EnableComparatorH	=1048575;
	ForceON				=true;
}
bool	LEDControl16DPanel::DefUnit::DefBoard::DefLine::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,UnitNo)==false)
		return false;
	if(::Save(f,BoardNo)==false)
		return false;
	if(::Save(f,LineNo)==false)
		return false;
	if(::Save(f,ColorType)==false)
		return false;
	if(::Save(f,MaxValue)==false)
		return false;
	if(::Save(f,Comment)==false)
		return false;
	if(::Save(f,LightID)==false)
		return false;
	if(::Save(f,EnableComparatorL)==false)
		return false;
	if(::Save(f,EnableComparatorH)==false)
		return false;
	if(::Save(f,ForceON)==false)
		return false;
	return true;
}
bool	LEDControl16DPanel::DefUnit::DefBoard::DefLine::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,UnitNo)==false)
		return false;
	if(::Load(f,BoardNo)==false)
		return false;
	if(::Load(f,LineNo)==false)
		return false;
	if(::Load(f,ColorType)==false)
		return false;
	if(::Load(f,MaxValue)==false)
		return false;
	if(::Load(f,Comment)==false)
		return false;
	if(::Load(f,LightID)==false)
		return false;
	if(::Load(f,EnableComparatorL)==false)
		return false;
	if(::Load(f,EnableComparatorH)==false)
		return false;
	if(::Load(f,ForceON)==false)
		return false;
	return true;
}

bool	LEDControl16DPanel::DefUnit::DefBoard::Save(QIODevice *f)
{
	if(::Save(f,CountOfLine)==false)
		return false;
	for(int i=0;i<CountOfLine;i++){
		if(DefLineDim[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	LEDControl16DPanel::DefUnit::DefBoard::Load(QIODevice *f)
{
	if(::Load(f,CountOfLine)==false)
		return false;
	for(int i=0;i<CountOfLine && i<sizeof(DefLineDim)/sizeof(DefLineDim[0]);i++){
		if(DefLineDim[i].Load(f)==false)
			return false;
	}
	return true;
}
int		LEDControl16DPanel::DefUnit::DefBoard::GetLineCount(void)
{
	return CountOfLine;
}
		
bool	LEDControl16DPanel::DefUnit::Save(QIODevice *f)
{
	if(::Save(f,CountOfBoard)==false)
		return false;
	for(int i=0;i<CountOfBoard;i++){
		if(DefBoardDim[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	LEDControl16DPanel::DefUnit::Load(QIODevice *f)
{
	if(::Load(f,CountOfBoard)==false)
		return false;
	for(int i=0;i<CountOfBoard && i<sizeof(DefBoardDim)/sizeof(DefBoardDim[0]);i++){
		if(DefBoardDim[i].Load(f)==false)
			return false;
	}
	return true;
}
int		LEDControl16DPanel::DefUnit::GetLineCount(void)
{
	int	N=0;
	for(int i=0;i<CountOfBoard && i<sizeof(DefBoardDim)/sizeof(DefBoardDim[0]);i++){
		N+=DefBoardDim[i].GetLineCount();
	}
	return N;
}

//----------------------------------------------------------------
bool	LEDControl16DPanel::LightPattern::LineValue::Save(QIODevice *f)
{
	if(::Save(f,PointerForDefLine->UnitNo)==false)
		return false;
	if(::Save(f,PointerForDefLine->BoardNo)==false)
		return false;
	if(::Save(f,PointerForDefLine->LineNo)==false)
		return false;
	if(::Save(f,Value)==false)
		return false;
	return true;
}
			
bool	LEDControl16DPanel::LightPattern::LineValue::Load(QIODevice *f,LEDControl16DPanel *panel)
{
	int32	UnitNo;
	int32	BoardNo;
	int32	LineNo;

	if(::Load(f,UnitNo)==false)
		return false;
	if(::Load(f,BoardNo)==false)
		return false;
	if(::Load(f,LineNo)==false)
		return false;
	PointerForDefLine	=&panel->DefUnitDim[UnitNo].DefBoardDim[BoardNo].DefLineDim[LineNo];
	if(::Load(f,Value)==false)
		return false;
	return true;
}


bool	LEDControl16DPanel::LightPattern::Save(QIODevice *f)
{
	if(::Save(f,AllocatedCountOfLines)==false)
		return false;
	for(int i=0;i<AllocatedCountOfLines;i++){
		if(LineValueDim[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	LEDControl16DPanel::LightPattern::Load(QIODevice *f,LEDControl16DPanel *panel)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	if(N!=AllocatedCountOfLines){
		AllocatedCountOfLines=N;
		if(LineValueDim!=NULL){
			delete	[]LineValueDim;
		}
		LineValueDim=new LineValue[AllocatedCountOfLines];
	}
	for(int i=0;i<AllocatedCountOfLines;i++){
		if(LineValueDim[i].Load(f,panel)==false)
			return false;
	}

	return true;
}
void	LEDControl16DPanel::LightPattern::Initial(LEDControl16DPanel *Panel)
{
	int	N=Panel->GetLineCount();

	if(AllocatedCountOfLines!=N){
		AllocatedCountOfLines=N;
		if(LineValueDim!=NULL)
			delete		[]LineValueDim;
		LineValueDim=new LineValue[AllocatedCountOfLines];
		int	Row=0;
		for(int r=0;r<Panel->CountOfUnit;r++){
			for(int b=0;b<Panel->DefUnitDim[r].CountOfBoard;b++){
				for(int L=0;L<Panel->DefUnitDim[r].DefBoardDim[b].CountOfLine;L++,Row++){
					LineValueDim[Row].PointerForDefLine	= &Panel->DefUnitDim[r].DefBoardDim[b].DefLineDim[L];
				}
			}
		}
	}
}
		
bool	LEDControl16DPanel::PatternData::Save(QIODevice *f)
{
	if(::Save(f,UsageLines)==false)
		return false;
	if(::Save(f,Comment)==false)
		return false;
	if(Pattern.Save(f)==false)
		return false;
	
	return true;
}

bool	LEDControl16DPanel::PatternData::Load(QIODevice *f,LEDControl16DPanel *Panel)
{
	if(::Load(f,UsageLines)==false)
		return false;
	if(::Load(f,Comment)==false)
		return false;

	if(Pattern.Load(f,Panel)==false)
		return false;

	return true;
}

//----------------------------------------------------------------
	
bool	LEDControl16DPanel::LoadDef(void)
{
	QFile	DefFile(DefFileName);
	if(DefFile.open(QIODevice::ReadOnly)==true){
		return LoadDef(&DefFile);
	}
	return false;
}
	
bool	LEDControl16DPanel::SaveDef(void)
{
	QFile	DefFile(DefFileName);
	if(DefFile.open(QIODevice::WriteOnly)==true){
		return SaveDef(&DefFile);
	}
	return false;
}

LEDControl16DPanel::LEDControl16DPanel(LayersBase *base ,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	Commander=HidCommand::Create((QWidget *)this);

	Opened=false;
	StopInput	=false;
	LightForm	=NULL;

	Param=LightParamStr;
	CurrentPattern	=0;
	LightDataNumb	=3;
	BoardCount		=0;
	Number			=0;
	ContinuousMode	=10000;
	AddedStartOffset=0;

	LoadDef();
	for(int i=0;i<sizeof(LightData)/sizeof(LightData[0]);i++){
		LightData[i].Pattern.Initial(this);
	}


	InitialEPRom();

	QStringList	List=LightParamStr.split(QRegularExpression("[, ]"));
	int	MaxValue	=1000000;

	if(List.count()>0){
		if(List[0].isNull()==false){
			Number=List[0].toInt();
		}
	}
	if(List.count()>1){
		if(List[1].isNull()==false){
			MaxValue=List[1].toInt();
		}
	}

	BoardData[1].EPROMData[0].UsageLines	=32;
	BoardData[1].EPROMData[0].LineData[0].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[0].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[1].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[1].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[2].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[2].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[3].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[3].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[4].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[4].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[5].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[5].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[6].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[6].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[7].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[7].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[8].ColorType		=1;
	BoardData[1].EPROMData[0].LineData[8].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[9].ColorType		=1;
	BoardData[1].EPROMData[0].LineData[9].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[10].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[10].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[11].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[11].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[12].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[12].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[13].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[13].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[14].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[14].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[15].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[15].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[16].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[16].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[17].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[17].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[18].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[18].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[19].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[19].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[20].ColorType	=0;
	BoardData[1].EPROMData[0].LineData[20].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[21].ColorType	=0;
	BoardData[1].EPROMData[0].LineData[21].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[22].ColorType	=0;
	BoardData[1].EPROMData[0].LineData[22].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[23].ColorType	=0;
	BoardData[1].EPROMData[0].LineData[24].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[24].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[24].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[25].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[25].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[26].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[26].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[27].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[27].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[28].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[28].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[29].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[29].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[30].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[30].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[31].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[31].MaxCurrent	=MaxValue;

	BoardData[0].EPROMData[0].UsageLines	=16;
	BoardData[0].EPROMData[0].LineData[0].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[0].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[1].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[1].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[2].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[2].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[3].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[3].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[4].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[4].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[5].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[5].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[6].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[6].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[7].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[7].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[8].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[8].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[9].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[9].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[10].ColorType	=2;
	BoardData[0].EPROMData[0].LineData[10].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[11].ColorType	=2;
	BoardData[0].EPROMData[0].LineData[11].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[12].ColorType	=2;
	BoardData[0].EPROMData[0].LineData[12].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[13].ColorType	=2;
	BoardData[0].EPROMData[0].LineData[13].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[14].ColorType	=2;
	BoardData[0].EPROMData[0].LineData[14].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[15].ColorType	=2;
	BoardData[0].EPROMData[0].LineData[15].MaxCurrent	=MaxValue;


	if(List.count()>2){
		QString	AllocationFileName;
		AllocationFileName=List[2];
		QFile	File(AllocationFileName);
		if(File.open(QIODevice::ReadOnly)==true){
			LoadAllocationFile(&File);
		}
	}

	BuildDataFromEPRom();


	if(Open()==true){
		GetVersion();
	}
	/*
	TM.setInterval(10);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
	*/
	//SetPatternComparator();
	Transfer(0,NULL);
}
LEDControl16DPanel::~LEDControl16DPanel(void)
{
	delete	Commander;
	Commander=NULL;
}


void	LEDControl16DPanel::InitialEPRom(void)
{
	for(int i=0;i<sizeof(BoardData)/sizeof(BoardData[0]);i++){
		for(int j=0;j<sizeof(BoardData[0].EPROMData)/sizeof(BoardData[0].EPROMData[0]);j++){
			BoardData[i].EPROMData[j].UsageLines	=0;
			for(int k=0;k<sizeof(BoardData[i].EPROMData[j].LineData)/sizeof(BoardData[i].EPROMData[j].LineData[0]);k++){
				BoardData[i].EPROMData[j].LineData[k].ColorType	=0xFF;
				BoardData[i].EPROMData[j].LineData[k].MaxCurrent=0;
			}
		}
	}
}

void	LEDControl16DPanel::BuildDataFromEPRom(void)
{

}

bool	LEDControl16DPanel::Initial(bool OutputMode)
{	
	return true;
}
bool	LEDControl16DPanel::Open(void)
{
	if(Commander->OpenHid(0x1255, 0x000D,Number)==false){
		return false;
	}
	return true;
}
bool	LEDControl16DPanel::Close(void)
{	
	return true;
}

void	LEDControl16DPanel::GetVersion(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		Commander->SendStr((BYTE *)"V",1);
		BYTE	RecData[256];
		int		ReceivedLen;
		GSleep(100);
		if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
			VersionStr=((char *)RecData);
		}
		BYTE	TxBuff[64];

		TxBuff[0]='A';
		TxBuff[1]=DefUnitDim[0].CountOfBoard;
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		
		Commander->SendStr((BYTE *)"a",1);
		GSleep(100);
		if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
			BoardCount=RecData[0];
		}
		Commander->CloseHid();
		GSleep(10);
	}
	AccessHID.unlock();

	int			Ki;
	unsigned char PGA[4];
	SetCurrent(15000
				,Ki
				,PGA);

	ReEntrant=false;
}

void	LEDControl16DPanel::Transfer(int PatternNumber,QProgressBar *Bar)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	int	LEDCountInSheet=0;


	if(Bar!=NULL){
		Bar->setMaximum(LightData[PatternNumber].Pattern.AllocatedCountOfLines);
	}

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	if(Bar!=NULL){
		Bar->setValue(0);
	}

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='B';
		for(int i=0;i<LightData[PatternNumber].Pattern.AllocatedCountOfLines;i++){
			int		BoardNumber	=LightData[PatternNumber].Pattern.LineValueDim[i].PointerForDefLine->BoardNo;
			int		Addr		=LightData[PatternNumber].Pattern.LineValueDim[i].PointerForDefLine->LineNo;
			DWORD	Value		=LightData[PatternNumber].Pattern.LineValueDim[i].Value;
			if(Value!=0 && Value<5000)
				Value=5000;


			int	MaxValue	=LightData[PatternNumber].Pattern.LineValueDim[i].PointerForDefLine->MaxValue;
			if(Value>MaxValue)
				Value=MaxValue;
				
			TxBuff[1]=BoardNumber;
			TxBuff[2]=PatternNumber;
			TxBuff[3]=Addr;
			TxBuff[4]=Value;
			TxBuff[5]=Value>>8;
			TxBuff[6]=Value>>16;
			TxBuff[7]=Value>>24;

			Commander->SendStr(TxBuff,64);
			for(int h=0;h<10;h++){
				GSleep(50);
				Commander->ReceiveStr(RecData,ReceivedLen);
				if(RecData[0]==0x0a){
					break;
				}
			}
			if(Bar!=NULL){
				Bar->setValue(Bar->value()+1);
			}
			GSleep(10);
		}
		
		Commander->CloseHid();
	}
	AccessHID.unlock();

	ReEntrant=false;

	//int		RegData=-1;
	//GetRegisterData(0 ,1 ,2 ,RegData);
}

bool	LEDControl16DPanel::GetRegisterData(int BoardNumber ,int datatype ,int adr ,int &RegData)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='m';
		TxBuff[1]=BoardNumber;
		TxBuff[2]=adr;
		TxBuff[3]=datatype;

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				RegData=RecData[1]+(((unsigned int)RecData[2])<<8);
				break;
			}
		}
		GSleep(10);
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}
void	LEDControl16DPanel::TransmitDirectly(GUIDirectMessage *packet)
{
	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	CmdSendRequestLight	*CmdSendRequestLightVar=dynamic_cast<CmdSendRequestLight *>(packet);
	if(CmdSendRequestLightVar!=NULL){
		AddedStartOffset	=	*((int32 *)CmdSendRequestLightVar->AnyData);
		SetEnableRangeOffset(0,AddedStartOffset);
		return;
	}
}

int		LEDControl16DPanel::GetLineCount(void)
{
	int	N=0;
	for(int u=0;u<CountOfUnit;u++){
		N+=DefUnitDim[u].GetLineCount();
	}
	return N;
}

bool	LEDControl16DPanel::SaveDef(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,CountOfUnit)==false)
		return false;
	int32	N=sizeof(DefUnitDim)/sizeof(DefUnitDim[0]);
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N && i<CountOfUnit;i++){
		if(DefUnitDim[i].Save(f)==false)
			return false;
	}
	return true;
}
	
bool	LEDControl16DPanel::LoadDef(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,CountOfUnit)==false)
		return false;
	int32	tN=sizeof(DefUnitDim)/sizeof(DefUnitDim[0]);
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N && i<tN && i<CountOfUnit;i++){
		if(DefUnitDim[i].Load(f)==false)
			return false;
	}
	return true;
}

bool	LEDControl16DPanel::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,LightDataNumb)==false)
		return false;
	int32	N=sizeof(LightData)/sizeof(LightData[0]);
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(LightData[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	LEDControl16DPanel::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,LightDataNumb)==false)
		return false;
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N && i<sizeof(LightData)/sizeof(LightData[0]);i++){
		if(LightData[i].Load(f,this)==false)
			return false;
	}
	return true;
}

bool	LEDControl16DPanel::SetOnOff(bool OnMode)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='I';
		if(OnMode==true)
			TxBuff[1]='1';
		else
			TxBuff[1]='0';

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		GSleep(10);
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}

bool	LEDControl16DPanel::SetTemporaryON(int32 ContinuousCount)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='O';
		TxBuff[1]=ContinuousCount;
		TxBuff[2]=ContinuousCount>>8;
		TxBuff[3]=ContinuousCount>>16;
		TxBuff[4]=ContinuousCount>>24;

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		GSleep(10);
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}

bool	LEDControl16DPanel::LoadInputData(int BoardNumber)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='j';
		TxBuff[1]=BoardNumber;

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				BoardData[BoardNumber].InputData[0]=RecData[1];
				BoardData[BoardNumber].InputData[1]=RecData[2];
				BoardData[BoardNumber].InputData[2]=RecData[3];
				BoardData[BoardNumber].InputData[3]=RecData[4];
				break;
			}
		}
		GSleep(10);
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}

bool	LEDControl16DPanel::SetTestLED(bool ONMode)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		for(int BoardNo=0;BoardNo<16;BoardNo++){
			TxBuff[0]='N';
			TxBuff[1]=BoardNo;					//Board number
			TxBuff[2]=(ONMode==true)?1:0;

			Commander->SendStr(TxBuff,64);
			for(int i=0;i<10;i++){
				GSleep(10);
				Commander->ReceiveStr(RecData,ReceivedLen);
				if(RecData[0]==0x0a){
					break;
				}
			}
			GSleep(10);
		}
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}
bool	LEDControl16DPanel::SetEncoderMode(bool ON)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		for(int BoardNo=0;BoardNo<16;BoardNo++){
			TxBuff[0]='C';
			TxBuff[1]=BoardNo;					//Board number
			TxBuff[2]=(ON==true)?1:0;

			Commander->SendStr(TxBuff,64);
			for(int i=0;i<10;i++){
				GSleep(10);
				Commander->ReceiveStr(RecData,ReceivedLen);
				if(RecData[0]==0x0a){
					break;
				}
			}
			GSleep(10);
		}
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}

bool	LEDControl16DPanel::ReadEPRom(int BoardNumber ,int PortNumber ,struct LightUnit &Data)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){

		//Read EPROM data to buffer
		TxBuff[0]='M';
		TxBuff[1]=BoardNumber;					//Board number
		TxBuff[2]=PortNumber;
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(100);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		for(int k=0;k<sizeof(Data.LineData)/sizeof(Data.LineData[0]);k++){
			TxBuff[0]='k';
			TxBuff[1]=BoardNumber;					//Board number
			TxBuff[2]=PortNumber;
			TxBuff[3]=k;
			Commander->SendStr(TxBuff,64);
			for(int i=0;i<10;i++){
				GSleep(10);
				Commander->ReceiveStr(RecData,ReceivedLen);
				if(RecData[0]==0x0a){
					Data.UsageLines				=RecData[1];
					Data.LineData[k].ColorType  =RecData[2];
					Data.LineData[k].MaxCurrent	=RecData[3] + (RecData[4]<<8);
					break;
				}
			}
			GSleep(10);
		}

		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}

bool	LEDControl16DPanel::WriteEPRom(int BoardNumber ,int PortNumber ,struct LightUnit &Data)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){

		for(int k=0;k<sizeof(Data.LineData)/sizeof(Data.LineData[0]);k++){
			TxBuff[0]='K';
			TxBuff[1]=BoardNumber;					//Board number
			TxBuff[2]=PortNumber;
			TxBuff[3]=Data.UsageLines;
			TxBuff[4]=k;
			TxBuff[5]=Data.LineData[k].ColorType;
			TxBuff[6]=Data.LineData[k].MaxCurrent & 0xFF;
			TxBuff[7]=(Data.LineData[k].MaxCurrent>>8) & 0xFF;
			Commander->SendStr(TxBuff,64);
			for(int i=0;i<10;i++){
				GSleep(10);
				Commander->ReceiveStr(RecData,ReceivedLen);
				if(RecData[0]==0x0a){
					break;
				}
			}
			GSleep(10);
		}

		//Write EPROM data to buffer
		TxBuff[0]='L';
		TxBuff[1]=BoardNumber;					//Board number
		TxBuff[2]=PortNumber;
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(100);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		GSleep(10);
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}

int		LEDControl16DPanel::ReadEPRomStatus(int BoardNumber ,int PortNumber)
{
	static	bool	ReEntrant=false;
	int	Ret=0;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='l';
		TxBuff[1]=BoardNumber;
		TxBuff[2]=PortNumber;

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				Ret=RecData[1];
				break;
			}
		}
		GSleep(10);
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return Ret;
}
	
bool	LEDControl16DPanel::GetPatternComparator(int UnitNumber ,int BoardNumber,int LineNumber)	//Into DefBuffer
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='r';
		TxBuff[1]=BoardNumber;
		TxBuff[2]=LineNumber;

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				DefUnitDim[UnitNumber].DefBoardDim[BoardNumber].DefLineDim[LineNumber].EnableComparatorL=RecData[1]+(((unsigned int)RecData[2])<<8)-AddedStartOffset;
				DefUnitDim[UnitNumber].DefBoardDim[BoardNumber].DefLineDim[LineNumber].EnableComparatorH=RecData[3]+(((unsigned int)RecData[4])<<8)-AddedStartOffset;
				DefUnitDim[UnitNumber].DefBoardDim[BoardNumber].DefLineDim[LineNumber].ForceON			=((RecData[5+(LineNumber/8)]&(0x01<<(LineNumber&7)))!=0)?true:false;
				break;
			}
		}
		GSleep(10);
		
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}
bool	LEDControl16DPanel::SetPatternComparator(void)	//From DefBuffer
{
	for(int	U=0;U<CountOfUnit;U++){;
		for(int B=0;B<DefUnitDim[U].CountOfBoard;B++){
			for(int L=0;L<DefUnitDim[U].DefBoardDim[B].CountOfLine;L++){
				if(SetPatternComparator(U,B ,L)==false)
					return false;
			}
			if(SetPatternOnOff(U,B)==false)
					return false;
		}
	}
	return true;
}
bool	LEDControl16DPanel::SetPatternComparator(int UnitNumber ,int BoardNumber ,int LineNumber)	//From DefBuffer
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='R';
		TxBuff[1]=BoardNumber;
		TxBuff[2]=LineNumber;
		TxBuff[3]=(  DefUnitDim[UnitNumber].DefBoardDim[BoardNumber].DefLineDim[LineNumber].EnableComparatorL+AddedStartOffset)&0xFF;
		TxBuff[4]=(((DefUnitDim[UnitNumber].DefBoardDim[BoardNumber].DefLineDim[LineNumber].EnableComparatorL+AddedStartOffset))>>8 )&0xFF;
		TxBuff[5]=(  DefUnitDim[UnitNumber].DefBoardDim[BoardNumber].DefLineDim[LineNumber].EnableComparatorH+AddedStartOffset)&0xFF;
		TxBuff[6]=(((DefUnitDim[UnitNumber].DefBoardDim[BoardNumber].DefLineDim[LineNumber].EnableComparatorH+AddedStartOffset))>>8 )&0xFF;
		TxBuff[7]=0;
		TxBuff[8]=0;
		for(int i=0;i<16;i++){
			TxBuff[7+(i/8)]|=(DefUnitDim[UnitNumber].DefBoardDim[BoardNumber].DefLineDim[i].ForceON==true)?(0x01<<(i&0x7)):0;
		}
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		GSleep(10);
		
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}
	
bool	LEDControl16DPanel::GetPatternOnOff		(int UnitNumber ,int BoardNumber)					//Into DefBuffer
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='u';
		TxBuff[1]=BoardNumber;

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				for(int LineNumber=0;LineNumber<16;LineNumber++){
					DefUnitDim[UnitNumber].DefBoardDim[BoardNumber].DefLineDim[LineNumber].ForceON			=((RecData[1+(LineNumber/8)]&(0x01<<(LineNumber&7)))!=0)?true:false;
				}
				break;
			}
		}
		GSleep(10);
		
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}
bool	LEDControl16DPanel::SetPatternOnOff		(int UnitNumber ,int BoardNumber)					//From DefBuffer
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='U';
		TxBuff[1]=BoardNumber;
		TxBuff[2]=0;
		TxBuff[3]=0;
		for(int i=0;i<16;i++){
			TxBuff[2+(i/8)]|=(DefUnitDim[UnitNumber].DefBoardDim[BoardNumber].DefLineDim[i].ForceON==true)?(0x01<<(i&0x7)):0;
		}
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		GSleep(10);
		
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}
bool	LEDControl16DPanel::SetEnableRangeOffset(int UnitNumber ,int AddedOffset)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return false;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='W';
		TxBuff[1]=  (AddedOffset+2000) & 0xFF;
		TxBuff[2]= ((AddedOffset+2000)>>8) & 0xFF;

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		GSleep(10);
		
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}
bool	LEDControl16DPanel::SetMotorCounter(int UnitNumber ,int BoardNumber ,int N)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return false;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='S';
		TxBuff[1]=BoardNumber;
		TxBuff[2]= N & 0xFF;
		TxBuff[3]= (N>>8) & 0xFF;

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		GSleep(10);
		
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}
int		LEDControl16DPanel::GetMotorCounter(int UnitNumber ,int BoardNumber)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return 0;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;
	int		Ret=0;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='s';
		TxBuff[1]=BoardNumber;

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				Ret=RecData[1]+(((unsigned int)RecData[2])<<8);

				break;
			}
		}
		GSleep(10);
		
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return Ret;
}	
bool	LEDControl16DPanel::SetRelay(bool ON)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='T';
		TxBuff[1]=(ON==true)?1:0;
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		GSleep(10);
		
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}

int		LEDControl16DPanel::GetCameraResolution(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return 0;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;
	int		Ret=0;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='q';

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				Ret=RecData[1];
				break;
			}
		}
		GSleep(10);
		
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return Ret;
}	
bool	LEDControl16DPanel::SetCameraResolution(int n)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;
	int		Ret=0;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='Q';
		TxBuff[1]=n;

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		GSleep(10);
		
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}	

bool	LEDControl16DPanel::ShowSettingDialog(void)
{
	LightForm=new LEDControl16DDialog(this);
	bool	Ret=LightForm->exec();
	delete LightForm;
	LightForm=NULL;

	return Ret;
}

	//Don't call directly
bool	LEDControl16DPanel::InitialPhysical(const QString &Param)
{
	Initial(true);
	return true;
}

bool	LEDControl16DPanel::ReflectPhysical(void)
{
	if(LightForm!=NULL){
		Transfer(0,LightForm->GetBar());
	}
	else{
		Transfer(0,NULL);
	}

	return true;
}
bool	LEDControl16DPanel::ReflectPhysicalTurnOn(bool LightOn)
{
	SetOnOff(LightOn);
	return true;
}

	
void	LEDControl16DPanel::SlotTimeOut()
{
}


bool	LEDControl16DPanel::SetTestSignal(int n)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;
	int		Ret=0;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='X';
		TxBuff[1]=n;

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		GSleep(10);
		
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}

void  SetCurrent(long MicroAmpare 
				,int      &Ki
				,unsigned char PGA[4])
{
    long    L;
    int     A1,B1,C1;
    int     A2,B2,C2;
    int     A,B,C,D;
    int     G1,G2,H1,H2;
    unsigned long long  K;
    unsigned int  TmpMask;
    
    if(MicroAmpare<100)
        MicroAmpare=100;
    if(MicroAmpare>1200000L)
        return;
                
    L=16000000L/MicroAmpare;     //D=1
    L-=10L;
    if(L>5000L)
        C1=1;
    else
        C1=0;
    if(L-(10000L*C1)>300){
        B1=1;
    }
    else{
        B1=0;
    }
    if(L-(10000L*C1)-(1000L*B1)>30L){
        A1=1;
    }
    else{
        A1=0;
    }
    
    L=8000000L/MicroAmpare;     //D=0
    L-=10L;
    if(L>5000L)
        C2=1;
    else
        C2=0;
    if(L-(10000L*C2)>300L){
        B2=1;
    }
    else{
        B2=0;
    }
    if(L-(10000L*C2)-(1000L*B2)>30L){
        A2=1;
    }
    else{
        A2=0;
    }

    G1=((long long)MicroAmpare)*((long long)(100+100000*C1+10000*B1+1000*A1+100))/1000000ULL;
    G2=((long long)MicroAmpare)*((long long)(100+200000*C2+20000*B2+2000*A2+200))/1000000ULL;

    H1=G1*2;
    H2=G2*2;
    if(H2>420)
        H2=-1;
    if(H1>420)
        H1=-1;
    if(H1<0 && H2<0){
        L=8000000L/MicroAmpare;     //D=1
        L-=10L;
        if(L>5000L)
            C1=1;
        else
            C1=0;
        if(L-(10000L*C1)>300){
            B1=1;
        }
        else{
            B1=0;
        }
        if(L-(10000L*C1)-(1000L*B1)>30L){
            A1=1;
        }
        else{
            A1=0;
        }

        L=4000000L/MicroAmpare;     //D=0
        L-=10L;
        if(L>5000L)
            C2=1;
        else
            C2=0;
        if(L-(10000L*C2)>300L){
            B2=1;
        }
        else{
            B2=0;
        }
        if(L-(10000L*C2)-(1000L*B2)>30L){
            A2=1;
        }
        else{
            A2=0;
        }

        G1=((long long)MicroAmpare)*((long long)(100+100000*C1+10000*B1+1000*A1+100))/1000000ULL;
        G2=((long long)MicroAmpare)*((long long)(100+200000*C2+20000*B2+2000*A2+200))/1000000ULL;

        H1=G1*2;
        H2=G2*2;
        if(H2>420)
            H2=-1;
        if(H1>420)
            H1=-1;
        if(H1<0 && H2<0){
            return;
        }
    }
    if(H2<0){
        A=A1;
        B=B1;
        C=C1;
        D=1;
    }
    else{
        A=A2;
        B=B2;
        C=C2;
        D=0;
    }
    K=1638400000ULL*(1+D)/(((unsigned long long)MicroAmpare)*((unsigned long long)(3+D+2000*C+200*B+20*A)));
    if(K>4095ULL)
        K=4095;
    Ki=K;
    
    PGA[0]=A;
    PGA[1]=B;
    PGA[2]=C;
    PGA[3]=D;
}