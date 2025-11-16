/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\InsertTelop\InsertTelop.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "InsertTelop.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XExecuteInspectBase.h"
#include "XCameraClass.h"
#include "swap.h"
#include "XMacroFunction.h"
#include "XEntryPoint.h"

static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"InsertTelop";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show minimize/Maximize button");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new InsertTelop(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<9)
		return(-1);
	Data[0].Type				 =/**/"LeftTop,LeftBottom,RightTop,RightBottom";
	Data[0].VariableNameWithRoute=/**/"Position";
	Data[0].Pointer				 =&((InsertTelop *)Instance)->Position;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"ShowDate";
	Data[1].Pointer				 =&((InsertTelop *)Instance)->ShowDate;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ShowTime";
	Data[2].Pointer				 =&((InsertTelop *)Instance)->ShowTime;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"SubtitleColor";
	Data[3].Pointer				 =&((InsertTelop *)Instance)->SubtitleColor;
	Data[4].Type				 =/**/"QFont";
	Data[4].VariableNameWithRoute=/**/"SubtitleFont";
	Data[4].Pointer				 =&((InsertTelop *)Instance)->SubtitleFont;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"ShowOnMaster";
	Data[5].Pointer				 =&((InsertTelop *)Instance)->ShowOnMaster;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"ShowOnTarget";
	Data[6].Pointer				 =&((InsertTelop *)Instance)->ShowOnTarget;
	Data[7].Type				 =/**/"int32";
	Data[7].VariableNameWithRoute=/**/"Phase";
	Data[7].Pointer				 =&((InsertTelop *)Instance)->Phase;
	Data[8].Type				 =/**/"int32";
	Data[8].VariableNameWithRoute=/**/"Page";
	Data[8].Pointer				 =&((InsertTelop *)Instance)->Page;

	return(9);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/InsertTelop.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

static	bool	MacroInsertText(GUIFormBase *Instance ,QStringList &Args)
{
	InsertTelop	*V=dynamic_cast<InsertTelop *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<3){
		return false;
	}
	int	Phase	=Args[0].toInt();
	int	Page	=Args[1].toInt();
	QString	s	=Args[2];

	V->InsertText(Phase,Page,s);
	return true;
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"InsertText";
		Functions[ret].ArgName.append(/**/"Phase");
		Functions[ret].ArgName.append(/**/"Page");
		Functions[ret].Explain.append(/**/"Text message");
		Functions[ret].DLL_ExcuteMacro	=MacroInsertText;
		ret++;
	}
	return ret;
}

//==================================================================================================
InsertTelop::InsertTelop(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Position	=/**/"RightBottom";
	ShowDate	=true;
	ShowTime	=true;
	SubtitleColor	=Qt::red;
	ShowOnMaster	=false;
	ShowOnTarget	=true;
	Visible			=true;
	Phase			=0;
	Page			=0;

	WImage	=&Img1;
	RImage	=&Img2;
	ImgNumber=0;


	TM.setInterval(200);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
	TM.start();
}
void	InsertTelop::ReadyParam(void)
{
	int	N=0;
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		for(int cam=0;cam<GetParamGlobal()->TotalCameraNumb;cam++){
			CameraClass		*C=GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetCamera(cam);
			if(C!=NULL){
				ListFuncElement<InsertTelop>	*FuncPointer=new ListFuncElement<InsertTelop>(this,&InsertTelop::SlotCaptured);
				C->AddFuncCaptured(FuncPointer);
				N++;
			}
		}
	}
}

void	InsertTelop::SlotTimeout()
{
	QDateTime	C=QDateTime::currentDateTime();
	if(NowTime.time().second()!=C.time().second()){
		NowTime=C;
		MakeImage(AddedMessage);
	}
}

void	InsertTelop::MakeImage(const QString &s)
{
	QStringList	MessageList;
	if(ShowDate==true)
		MessageList.append(NowTime.toString(/**/"yy/MM/dd"));
	if(ShowTime==true)
		MessageList.append(NowTime.toString(/**/"hh:mm:ss"));
	if(s.isEmpty()==false)
		MessageList.append(s);
	int	LineNumb=MessageList.count();
	if(LineNumb>0){
		int	TextWidth	=0;
		int	TextHeight	=0;
		QFontMetrics fm(SubtitleFont);
		for(int i=0;i<LineNumb;i++){
			QString	s=MessageList[i]+QString(/**/"W");
			int	iTextWidth	=fm.boundingRect(s).width();
			int	iTextHeight	=fm.height();
			TextWidth	=max(TextWidth ,iTextWidth );
			TextHeight	=max(TextHeight,iTextHeight);
		}
		TextWidth+=32;
		int	LineMergin=15;
		int	TextMergin=10;
		int	XLen=TextWidth+TextMergin*2;
		int	YLen=TextHeight*LineNumb+(LineNumb+1)*LineMergin;
		QImage	*RImg=GetWPoint();

		if(RImg->width()!=XLen || RImg->height()!=YLen){
			MutexChangeImageSize.lock();
			Img1=QImage(XLen,YLen,QImage::Format_RGB32);
			Img2=QImage(XLen,YLen,QImage::Format_RGB32);
			MutexChangeImageSize.unlock();
		}
		RImg->fill(0);
		QPainter	Pnt(RImg);
		Pnt.setBrush(SubtitleColor);
		Pnt.setPen	(SubtitleColor);
		Pnt.setFont	(SubtitleFont);
		int	H=LineMergin+TextHeight;
		for(int i=0;i<LineNumb;i++){
			QString	s=MessageList[i];
			Pnt.drawText(TextMergin,H,s);
			H+=LineMergin+TextHeight;
		}
		ImgNumber++;
	}
}

void	InsertTelop::InsertText(int tPhase,int tPage,const QString &s)
{
	MakeImage(s);

	ImageBuffer	*Buffer[3];
	int		BuffNumb=0;

	PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(tPhase);
	if(Ph!=NULL){
		DataInPage *Pg=Ph->GetPageData(tPage);
		if(Pg!=NULL){
			for(int layer=0;layer<Pg->GetLayerNumb() && layer<3;layer++){
				if(ShowOnTarget==true){
					Buffer[layer]=Pg->GetLayerData(layer)->GetTargetBuffPointer();
					BuffNumb++;
				}
				else
				if(ShowOnMaster==true){
					Buffer[layer]=Pg->GetLayerData(layer)->GetMasterBuffPointer();
					BuffNumb++;
				}
			}
		}
	}

	if(BuffNumb>0){
		PasteImage(Buffer,BuffNumb);
	}
}

void	InsertTelop::SlotCaptured(ImageBuffer *Buffer[] ,int BufferDimCounts,bool &XReverse ,bool &YReverse)
{
	if(Visible==true){
		//bool	TargetMode=false;
		//bool	MasterMode=false;
		//for(int phase=0;phase<GetPhaseNumb();phase++){
		//	PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		//	for(int page=0;page<GetPageNumb();page++){
		//		DataInPage *Pg=Ph->GetPageData(page);
		//		for(int layer=0;layer<GetLayerNumb();layer++){
		//			DataInLayer	*Ly=Pg->GetLayerData(layer);
		//			if(Ly->GetMasterBuffPointer()==Buffer[0])
		//				MasterMode=true;
		//			if(Ly->GetTargetBuffPointer()==Buffer[0])
		//				TargetMode=true;
		//		}
		//	}
		//}

		if(BufferDimCounts>0){
			PasteImage(Buffer,BufferDimCounts);
		}
	}
}

QImage	*InsertTelop::GetWPoint(void)
{
	if((ImgNumber&1)==0)
		return &Img1;
	else
		return &Img2;
}

QImage	*InsertTelop::GetRPoint(void)
{
	if((ImgNumber&1)==0)
		return &Img2;
	else
		return &Img1;
}

void	InsertTelop::PasteImage(ImageBuffer *Buffer[] ,int DimCounts)
{
	if(GetLayersBase()->TryLockRChangingDataStructure()==false){
		return;
	}
	MutexChangeImageSize.lock();
	int	X,Y;
	QImage	*RImg=GetRPoint();
	int	XLen=RImg->width();
	int	YLen=RImg->height();
	if(Position==/**/"LeftTop"){
		X=0;
		Y=0;
	}
	else
	if(Position==/**/"LeftBottom"){
		X=0;
		Y=Buffer[0]->GetHeight()-YLen;
	}
	else
	if(Position==/**/"RightTop"){
		X=Buffer[0]->GetWidth()-XLen;
		Y=0;
	}
	else
	if(Position==/**/"RightBottom"){
		X=Buffer[0]->GetWidth ()-XLen;
		Y=Buffer[0]->GetHeight()-YLen;
	}
	if(DimCounts>=3){
		for(int y=0;y<YLen;y++){
			QRgb	*s=(QRgb *)RImg->scanLine(y);
			BYTE	*d0=Buffer[0]->GetY(Y+y)+X;
			BYTE	*d1=Buffer[1]->GetY(Y+y)+X;
			BYTE	*d2=Buffer[2]->GetY(Y+y)+X;
			for(int x=0;x<XLen;x++){
				BYTE	r=qRed(*s);
				BYTE	g=qGreen(*s);
				BYTE	b=qBlue(*s);
				if(r!=0 || g!=0 || b!=0){
					*d0=r;
					*d1=g;
					*d2=b;
				}
				s++;
				d0++;
				d1++;
				d2++;
			}
		}
	}
	MutexChangeImageSize.unlock();
	GetLayersBase()->UnlockChangingDataStructure();
}

void	InsertTelop::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSetTelopInfoPacket	*CmdSetTelopInfoPacketVar=dynamic_cast<CmdSetTelopInfoPacket *>(packet);
	if(CmdSetTelopInfoPacketVar!=NULL){
		Position		=CmdSetTelopInfoPacketVar->Position		;
		ShowDate		=CmdSetTelopInfoPacketVar->ShowDate		;
		ShowTime		=CmdSetTelopInfoPacketVar->ShowTime		;
		SubtitleColor	=CmdSetTelopInfoPacketVar->SubtitleColor;
		SubtitleFont	=CmdSetTelopInfoPacketVar->SubtitleFont	;
		return;
	}
	CmdSetMessagePacket	*CmdSetMessagePacketVar=dynamic_cast<CmdSetMessagePacket *>(packet);
	if(CmdSetMessagePacketVar!=NULL){
		AddedMessage	=CmdSetMessagePacketVar->AddedMessage;
		return;
	}
	CmdSetVisiblePacket	*CmdSetVisiblePacketVar=dynamic_cast<CmdSetVisiblePacket *>(packet);
	if(CmdSetVisiblePacketVar!=NULL){
		Visible=CmdSetVisiblePacketVar->Visible;
		return;
	}
}