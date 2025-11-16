#include "LEDControl16F.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XHidCommand.h"
#include "LEDControl16FDialog.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"


void  SetCurrent(long MicroAmpare 
				,int      &Ki
				,unsigned char PGA[4]);

QString	LEDControl16FPanel::DefFileName=/**/"LEDControl16FDef.dat";

void	LEDControl16FPanel::DefUnit::DefBoard::DefLine::Set(int unitNo ,int boardNo ,int lineNo)
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
bool	LEDControl16FPanel::DefUnit::DefBoard::DefLine::Save(QIODevice *f)
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
bool	LEDControl16FPanel::DefUnit::DefBoard::DefLine::Load(QIODevice *f)
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

bool	LEDControl16FPanel::DefUnit::DefBoard::Save(QIODevice *f)
{
	if(::Save(f,CountOfLine)==false)
		return false;
	for(int i=0;i<CountOfLine;i++){
		if(DefLineDim[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	LEDControl16FPanel::DefUnit::DefBoard::Load(QIODevice *f)
{
	if(::Load(f,CountOfLine)==false)
		return false;
	for(int i=0;i<CountOfLine && i<sizeof(DefLineDim)/sizeof(DefLineDim[0]);i++){
		if(DefLineDim[i].Load(f)==false)
			return false;
	}
	return true;
}
int		LEDControl16FPanel::DefUnit::DefBoard::GetLineCount(void)
{
	return CountOfLine;
}
		
bool	LEDControl16FPanel::DefUnit::Save(QIODevice *f)
{
	if(::Save(f,CountOfBoard)==false)
		return false;
	for(int i=0;i<CountOfBoard;i++){
		if(DefBoardDim[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	LEDControl16FPanel::DefUnit::Load(QIODevice *f)
{
	if(::Load(f,CountOfBoard)==false)
		return false;
	for(int i=0;i<CountOfBoard && i<sizeof(DefBoardDim)/sizeof(DefBoardDim[0]);i++){
		if(DefBoardDim[i].Load(f)==false)
			return false;
	}
	return true;
}
int		LEDControl16FPanel::DefUnit::GetLineCount(void)
{
	int	N=0;
	for(int i=0;i<CountOfBoard && i<sizeof(DefBoardDim)/sizeof(DefBoardDim[0]);i++){
		N+=DefBoardDim[i].GetLineCount();
	}
	return N;
}

//----------------------------------------------------------------
bool	LEDControl16FPanel::LightPattern::LineValue::Save(QIODevice *f)
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
			
bool	LEDControl16FPanel::LightPattern::LineValue::Load(QIODevice *f,LEDControl16FPanel *panel)
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


bool	LEDControl16FPanel::LightPattern::Save(QIODevice *f)
{
	if(::Save(f,AllocatedCountOfLines)==false)
		return false;
	for(int i=0;i<AllocatedCountOfLines;i++){
		if(LineValueDim[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	LEDControl16FPanel::LightPattern::Load(QIODevice *f,LEDControl16FPanel *panel)
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
void	LEDControl16FPanel::LightPattern::Initial(LEDControl16FPanel *Panel)
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
		
bool	LEDControl16FPanel::PatternData::Save(QIODevice *f)
{
	if(::Save(f,UsageLines)==false)
		return false;
	if(::Save(f,Comment)==false)
		return false;
	if(Pattern.Save(f)==false)
		return false;
	
	return true;
}

bool	LEDControl16FPanel::PatternData::Load(QIODevice *f,LEDControl16FPanel *Panel)
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
	
bool	LEDControl16FPanel::LoadDef(void)
{
	QFile	DefFile(DefFileName);
	if(DefFile.open(QIODevice::ReadOnly)==true){
		return LoadDef(&DefFile);
	}
	return false;
}
	
bool	LEDControl16FPanel::SaveDef(void)
{
	QFile	DefFile(DefFileName);
	if(DefFile.open(QIODevice::WriteOnly)==true){
		return SaveDef(&DefFile);
	}
	return false;
}

LEDControl16FPanel::LEDControl16FPanel(LayersBase *base ,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base),Sock(base->GetMainWidget())
{
	Opened=false;
	StopInput	=false;
	LightForm	=NULL;

	Param=LightParamStr;
	CurrentPattern	=0;
	LightDataNumb	=3;
	AccessIPAddress			=/**/"Pi";
	AccessPort				=LEDControllerPort;
	ContinuousMode	=10000;
	AddedStartOffset=0;
	CountOfUnit		=1;

	LoadDef();
	for(int i=0;i<sizeof(LightData)/sizeof(LightData[0]);i++){
		LightData[i].Pattern.Initial(this);
	}

	QStringList	List=LightParamStr.split(QRegularExpression("[, ]"));
	int	MaxValue	=1000000;

	if(List.count()>0){
		if(List[0].isNull()==false){
			AccessIPAddress=List[0];
		}
	}
	if(List.count()>1){
		if(List[1].isNull()==false){
			AccessPort=List[1].toInt();
		}
	}
	/*
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
	*/

	if(List.count()>2){
		QString	AllocationFileName;
		AllocationFileName=List[2];
		QFile	File(AllocationFileName);
		if(File.open(QIODevice::ReadOnly)==true){
			LoadAllocationFile(&File);
		}
	}

	bool	Ret=(connect(&Sock,SIGNAL(readyRead()),this,SLOT(SlotReadyRead())))?true:false;


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
LEDControl16FPanel::~LEDControl16FPanel(void)
{
}



bool	LEDControl16FPanel::Initial(bool OutputMode)
{	
	return true;
}
bool	LEDControl16FPanel::Open(void)
{
	Sock.connectToHost(AccessIPAddress,AccessPort);
	Sock.waitForConnected(3000);
	if(Sock.state()==QAbstractSocket::ConnectedState)
		return true;
	return false;
}
bool	LEDControl16FPanel::Close(void)
{	
	return true;
}

void	LEDControl16FPanel::GetVersion(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	AccessHID.lock();
	Received=false;
	if(Sock.state()!=QAbstractSocket::ConnectedState)
		Open();
	if(Sock.state()==QAbstractSocket::ConnectedState){
		BYTE	cmd='V';
		Sock.write((const char *)&cmd,sizeof(cmd));
		GSleep(100);
		Sock.waitForReadyRead(2000);

		cmd='A';
		Sock.write((const char *)&cmd,sizeof(cmd));
		GSleep(100);
		Sock.waitForReadyRead(2000);
		GSleep(10);
	}
	AccessHID.unlock();

	/*
	int			Ki;
	unsigned char PGA[4];
	SetCurrent(15000
				,Ki
				,PGA);
	*/
	ReEntrant=false;
}

void	LEDControl16FPanel::Transfer(int PatternNumber,QProgressBar *Bar)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	int	LEDCountInSheet=0;


	if(Bar!=NULL){
		Bar->setMaximum(DefUnitDim[0].CountOfBoard);
	}

	if(Bar!=NULL){
		Bar->setValue(0);
	}

	AccessHID.lock();
	if(Sock.state()!=QAbstractSocket::ConnectedState)
		Open();
	if(Sock.state()==QAbstractSocket::ConnectedState){		
		for(int Brd=0;Brd<DefUnitDim[0].CountOfBoard;Brd++){
			struct  LightPacketData	LData;
			LData.BoardNo	=Brd;
			LData.PatternNo	=PatternNumber;
			LData.PatternData.DCEnable	=true;

			for(int i=0;i<LightData[PatternNumber].Pattern.AllocatedCountOfLines;i++){
				int		BoardNumber	=LightData[PatternNumber].Pattern.LineValueDim[i].PointerForDefLine->BoardNo;
				if(BoardNumber!=Brd)
					continue;
				int		Addr		=LightData[PatternNumber].Pattern.LineValueDim[i].PointerForDefLine->LineNo;
				DWORD	Value		=LightData[PatternNumber].Pattern.LineValueDim[i].Value;
				bool	ON			=LightData[PatternNumber].Pattern.LineValueDim[i].ON;
				if(Value!=0 && Value<5000)
					Value=5000;


				int	MaxValue	=LightData[PatternNumber].Pattern.LineValueDim[i].PointerForDefLine->MaxValue;
				if(Value>MaxValue)
					Value=MaxValue;
				LData.PatternData.LineData[Addr].MicroAmp	=Value;
				LData.PatternData.LineData[Addr].ON			=ON;
			}

			Received=false;
			BYTE	cmd='B';
			Sock.write((const char *)&cmd,sizeof(cmd));
			Sock.write((const char  *)&LData,sizeof(LData));
			Sock.waitForReadyRead(2000);

			if(Bar!=NULL){
				Bar->setValue(Bar->value()+1);
			}
			GSleep(10);
		}
	}
	AccessHID.unlock();

	ReEntrant=false;

	//int		RegData=-1;
	//GetRegisterData(0 ,1 ,2 ,RegData);
}

void	LEDControl16FPanel::TransmitDirectly(GUIDirectMessage *packet)
{

}

int		LEDControl16FPanel::GetLineCount(void)
{
	int	N=0;
	for(int u=0;u<CountOfUnit;u++){
		N+=DefUnitDim[u].GetLineCount();
	}
	return N;
}

bool	LEDControl16FPanel::SaveDef(QIODevice *f)
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
	
bool	LEDControl16FPanel::LoadDef(QIODevice *f)
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

bool	LEDControl16FPanel::Save(QIODevice *f)
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
bool	LEDControl16FPanel::Load(QIODevice *f)
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

bool	LEDControl16FPanel::SetOnOff(bool OnMode)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Sock.state()!=QAbstractSocket::ConnectedState)
		Open();
	if(Sock.state()==QAbstractSocket::ConnectedState){

		for(int PatternNumber=0;PatternNumber<MaxPatternCount;PatternNumber++){
			for(int i=0;i<LightData[PatternNumber].Pattern.AllocatedCountOfLines;i++){
				int		BoardNumber	=LightData[PatternNumber].Pattern.LineValueDim[i].PointerForDefLine->BoardNo;
				LightData[PatternNumber].Pattern.LineValueDim[i].ON=OnMode;
			}
		}

		TxBuff[0]='I';
		if(OnMode==true)
			TxBuff[1]='1';
		else
			TxBuff[1]='0';

		Sock.write((const char *)TxBuff,2);
		Sock.waitForReadyRead(2000);

		GSleep(10);
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}


/*	
bool	LEDControl16FPanel::GetPatternOnOff		(int UnitNumber ,int BoardNumber)					//Into DefBuffer
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Sock.state()!=QAbstractSocket::ConnectedState)
		Open();
	if(Sock.state()==QAbstractSocket::ConnectedState){

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
bool	LEDControl16FPanel::SetPatternOnOff		(int UnitNumber ,int BoardNumber)					//From DefBuffer
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Sock.state()!=QAbstractSocket::ConnectedState)
		Open();
	if(Sock.state()==QAbstractSocket::ConnectedState){

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
*/

bool	LEDControl16FPanel::ShowSettingDialog(void)
{
	LightForm=new LEDControl16FDialog(this);
	bool	Ret=LightForm->exec();
	delete LightForm;
	LightForm=NULL;

	return Ret;
}

	//Don't call directly
bool	LEDControl16FPanel::InitialPhysical(const QString &Param)
{
	Initial(true);
	return true;
}

bool	LEDControl16FPanel::ReflectPhysical(void)
{
	if(LightForm!=NULL){
		Transfer(0,LightForm->GetBar());
	}
	else{
		Transfer(0,NULL);
	}

	return true;
}
bool	LEDControl16FPanel::ReflectPhysicalTurnOn(bool LightOn)
{
	SetOnOff(LightOn);
	return true;
}

	
void	LEDControl16FPanel::SlotTimeOut()
{
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

void    LEDControl16FPanel::SlotReadyRead()
{
   unsigned char   Cmd;

    if(Sock.read((char *)&Cmd,sizeof(Cmd))!=sizeof(Cmd))
        return;
    if(Cmd=='V'){
        QByteArray  Array=Sock.readAll();

		VersionStr= Array;
		Received=true;
    }
    if(Cmd=='A'){
        BYTE	tBoardCount;
        if(Sock.read((char *)&tBoardCount,sizeof(tBoardCount))!=sizeof(tBoardCount))
        	return;
		DefUnitDim[0].CountOfBoard=tBoardCount;
		for(int b=0;b<tBoardCount;b++){
			DefUnitDim[0].DefBoardDim[b].CountOfLine=16;
		}
        Received=true;
    }
    if(Cmd=='B'){
        Received=true;
    }
}