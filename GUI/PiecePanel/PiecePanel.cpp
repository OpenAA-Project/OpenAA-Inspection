#include "PiecePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PiecePanel\PiecePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#define _USE_MATH_DEFINES
#include <math.h>
#include "PiecePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "XAlgorithmInterfaceDLL.h"
#include "XAlgorithmBase.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include <QBitmap>
#include "XPiecePacket.h"
#include "XPieceArrange.h"
#include "XPieceArchitect.h"
#include "XGUI.h"
#include "ImagePanelTools.h"
#include "XFileRegistry.h"
#include "XLotInformation.h"
#include "XDisplayImagePacket.h"
#include "swap.h"
#include "XResize.h"
#include <QMessageBox>
#include "XAuthenticationInside.h"
#include "XResult.h"
#include "XWriteResultThread.h"
#include "XLibraryType.h"
#include "XArrangementFromFile.h"
#include "XLogOut.h"
#include "XParamDatabase.h"
#include "XImageStocker.h"
#include "XShadowTree.h"
#include "XFileThread.h"
#include "XLevel.h"
#include <omp.h>

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"PiecePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"PiecePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	PiecePanel	*B=new PiecePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	PiecePanel *InstancePtr=dynamic_cast<PiecePanel *>((PiecePanel *)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		Data[N].Type				  =/**/"QString";
		Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
		Data[N].Pointer				=&((PiecePanel *)Instance)->ImageControlToolsName;
		Data[N+1].Type				  =/**/"QColor";
		Data[N+1].VariableNameWithRoute=/**/"AlgorithmImageColor";
		Data[N+1].Pointer			  =&((PiecePanel *)Instance)->AlgorithmImageColor;
		Data[N+2].Type				  =/**/"int32";
		Data[N+2].VariableNameWithRoute=/**/"AlgorithmImageTransparency";
		Data[N+2].Pointer			  =&((PiecePanel *)Instance)->AlgorithmImageTransparency;
		
		return(N+3);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PiecePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"PieceArrange"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

PiecePanel::PiecePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"PieceArrange",QString(sRoot),QString(sName),__Master,parent)
{
	AlgorithmImageColor			=Qt::blue;
	AlgorithmImageTransparency	=128;
}

void	PiecePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

void	PiecePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImage::TransmitDirectly(packet);
	CmdPieceSetCutPacket	*CmdPieceSetCutPacketVar=dynamic_cast<CmdPieceSetCutPacket *>(packet);
	if(CmdPieceSetCutPacketVar!=NULL){
		SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::yellow);
	}
	CmdPieceSetArrangePacket	*CmdPieceSetArrangePacketVar=dynamic_cast<CmdPieceSetArrangePacket *>(packet);
	if(CmdPieceSetArrangePacketVar!=NULL){
		SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
	}
}

void	PiecePanel::DrawBtnDown()
{
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

AlgorithmDrawAttr	*PiecePanel::CreateDrawAttrPointer(void)
{	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PieceArrange");
	if(Ab!=NULL){
		PieceArrangeBase	*M=(PieceArrangeBase *)Ab;
		PieceDrawAttr	*mattr=new PieceDrawAttr(GetLayersBase()
								  ,M->ColorPiece		,M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel);
		
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PiecePropertyForm" ,/**/"");
		CmdPieceSelectedAlgorithm	Da(GetLayersBase());
		if(GProp!=NULL){
			GProp->TransmitDirectly(&Da);
			mattr->DLLRoot=Da.DLLRoot;
			mattr->DLLName=Da.DLLName;
			mattr->SelectedLines=Da.SelectedLines;
		}

		return mattr;
	}
	return new PieceDrawAttr(GetLayersBase());
}

void	PiecePanel::DrawEndAfterOperation(FlexArea &area)
{
	LayersBase	*LBase=GetLayersBase();
	AlgorithmBase	*Ab=LBase->GetAlgorithmBase(/**/"Basic",/**/"PieceArrange");
	if(Ab==NULL)
		return;
	PieceArrangeBase	*MBase=dynamic_cast<PieceArrangeBase *>(Ab);
	if(MBase==NULL)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PiecePropertyForm" ,/**/"");
	CmdCheckPiecePropertyButtonPacket	Da(GetLayersBase());
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
		if(Da.Mode==CmdCheckPiecePropertyButtonPacket::ModeCutArea){
			QString ParamFileName;
			QString PixFileName;
			CmdPieceCreateTempFiles		PMa(GetLayersBase());
			MBase->TransmitDirectly(&PMa);
			ParamFileName	=PMa.ParamFileName;
			PixFileName		=PMa.PixFileName;

			QFile	createdGlobalParam(ParamFileName);
			if(createdGlobalParam.open(QIODevice::ReadWrite)==false){
				QString	Msg=ParamFileName
							+QString(" : Can not create temporary file");
				QMessageBox::critical (NULL, "Error", Msg );
				return;
			}
			QFile	createdPix(PixFileName);
			if(createdPix.open(QIODevice::ReadWrite)==false){
				QString	Msg=PixFileName
							+QString(" : Can not create Pix file");
				QMessageBox::critical (NULL, "Error", Msg );
				return;
			}
			bool	ret=LBase->CreatePartialData(area.GetMinX(),area.GetMinY(),area.GetMaxX(), area.GetMaxY()
							,&createdGlobalParam ,&createdPix);
			if(ret==false)
				return;
			createdGlobalParam.close();
			createdPix.close();

			QString	GUIFileName=MBase->PieceGUIFile;
			if(GUIFileName.isEmpty()==true){
				GUIFileName=LBase->GetGUIFileName();
			}
			//QString	ProgFile=QCoreApplication::applicationFilePath ();
			QString	ProgFile=MBase->EditorPathFile;
			if(ProgFile.isEmpty()==true){
				ProgFile=QCoreApplication::applicationFilePath ();
			}
			QDir::setCurrent(GetLayersBase()->GetSystemPath());

			QStringList Arguments;
			Arguments.append(QString(/**/"A")+LBase->GetSystemPath());
			Arguments.append(QString(/**/"G")+GUIFileName);
			Arguments.append(QString(/**/"S")+ParamFileName);
			Arguments.append(QString(/**/"W")+QString::number(LBase->GetWorkerID()));
			Arguments.append(QString(/**/"P")+PixFileName);
			Arguments.append(QString(/**/"B")+QString::number(LBase->GetBootingLevel()+1));
			Arguments.append(QString(/**/"Duplicate"));
			Arguments.append(QString(/**/"NoCamDevice"));
			Arguments.append(QString(/**/"NoSequence"));
			Arguments.append(QString(/**/"NDM"));
			Arguments.append(QString(/**/"-R"));
			Arguments.append(QString(/**/"SetNumThreads1"));
			QProcess::startDetached( ProgFile, Arguments) ;
		}
		else if(Da.Mode==CmdCheckPiecePropertyButtonPacket::ModeArrange){
			CmdCreatePiecePacket	Cp(GetLayersBase());
			Cp.Area=area;
			GProp->TransmitDirectly(&Cp);
			//BroadcastDirectly(GUIFormBase::_BC_Show,GetLayersBase()->GetCurrentInspectIDForDisplay());
			BroadcastShowInEdit();
		}
	}
}

void	PiecePanel::DrawAfterImage(QPainter &pnt ,QImage &PntImage)
{
	DisplayImageWithAlgorithm::DrawAfterImage(pnt ,PntImage);

	//AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PieceArrange");
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PiecePropertyForm" ,/**/"");
	if(GProp!=NULL){
		GetCountPacket	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);
		if(Da.EnabledCountMode==true){
			if(Da.CountX!=0 && Da.CountY!=0){
				double	ZoomRate=GetZoomRate();
				int		MovX	=GetMovx();
				int		MovY	=GetMovy();

				int		X1=GetRawSDataPoint()->UData.RectangleData.x1;
				int		Y1=GetRawSDataPoint()->UData.RectangleData.y1;
				int		X2=GetRawSDataPoint()->UData.RectangleData.x2;
				int		Y2=GetRawSDataPoint()->UData.RectangleData.y2;

				if(X1>X2)
					swap(X1,X2);
				if(Y1>Y2)
					swap(Y1,Y2);

				int	CellX=(X2-X1)/Da.CountX;
				int	CellY=(Y2-Y1)/Da.CountY;
				pnt.setPen(Qt::magenta);
				for(int i=1;i<Da.CountX;i++){
					pnt.drawLine((X1+CellX*i+MovX)*ZoomRate,(Y1+MovY)*ZoomRate,(X1+CellX*i+MovX)*ZoomRate,(Y2+MovY)*ZoomRate);
				}
				for(int i=1;i<Da.CountY;i++){
					pnt.drawLine((X1+MovX)*ZoomRate,(Y1+CellY*i+MovY)*ZoomRate,(X2+MovX)*ZoomRate,(Y1+CellY*i+MovY)*ZoomRate);
				}
				for(int y=0;y<Da.CountY;y++){
					for(int x=0;x<Da.CountX;x++){
						QRect	rect((X1+CellX*x+MovX)*ZoomRate,(Y1+CellY*y+MovY)*ZoomRate
									,CellX*ZoomRate,CellY*ZoomRate);
						QString	Str=QString::number(x+1)+QString(/**/",")+QString::number(y+1);
						pnt.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter
									,Str);
					}
				}
			}
		}
	}
}
void	PiecePanel::SlotCancelDraw()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PiecePropertyForm" ,/**/"");
	if(GProp!=NULL){
		CancelCountPacket	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);
		Repaint();
	}
}
void	PiecePanel::DrawInsideExpandedPaste( QPainter &pnt ,double movx,double movy,double ZoomRate
										    ,int SrcX ,int SrcY
											,int Dx,int Dy
											,int Page, int Layer, int ItemID
											,int ItemWidth ,int ItemHeight)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PieceArrange");
	if(Ab==NULL)
		return;
	PieceArrangeBase	*MBase=dynamic_cast<PieceArrangeBase *>(Ab);
	if(MBase==NULL)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PiecePropertyForm" ,/**/"");
	if(GProp!=NULL){
		CmdPieceSelectedAlgorithm	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);
		/*
		IntList	MasterIDList;
		MBase->ListupMasterID(MasterIDList);
		GetLayersBase()->PieceStock->PrepareImage
		*/

		GUICmdReqPieceItemMasterCode	RCmd(GetLayersBase(),sRoot,sName,Page);
		GUICmdSendPieceItemMasterCode	SCmd(GetLayersBase(),sRoot,sName,Page);
		RCmd.ItemID=ItemID;
		RCmd.Send(Page,0,SCmd);

		IntList	LayerList;
		GetActiveLayerList(LayerList);
		QString ErrorMessageOfFalse;
		QImage	*P=GetLayersBase()->GetPieceStock()->GetAlgorithmImage(Page,SCmd.MasterCode
																	,LayerList ,Da.DLLRoot,Da.DLLName ,ZoomRate 
																	,AlgorithmImageColor ,AlgorithmImageTransparency
																	,ErrorMessageOfFalse);
		if(P!=NULL){
			pnt.drawImage((SrcX+Dx+movx)*ZoomRate, (SrcY+Dy+movy)*ZoomRate,*P);
		}
		else{
			if(ErrorMessageOfFalse.isEmpty()==false){
				QMessageBox::critical(NULL,"Load masterdata Error",ErrorMessageOfFalse);
			}
		}
	}	
}

void	PiecePanel::ExpandedPasteExecute(ExpandedItemPosContainer &ExpandedItems)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PieceArrange");
	if(Ab==NULL)
		return;
	PieceArrangeBase	*MBase=dynamic_cast<PieceArrangeBase *>(Ab);
	if(MBase==NULL)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PiecePropertyForm" ,/**/"");
	if(GProp!=NULL){
		CmdPieceSelectedMaster	DMaster(GetLayersBase());
		GProp->TransmitDirectly(&DMaster);
		if(DMaster.MasterCode>=0){
			for(DisplayImage::ExpandedItemPos *c=ExpandedItems.GetFirst();c!=NULL;c=c->GetNext()){
				double	Rx,Ry;
				c->GetCenter(Rx,Ry);
				double	W=c->GetWidth();
				double	H=c->GetHeight();
				IntList PageList;
				GetLayersBase()->GetGlobalPage((int)(Rx-W/2) ,(int)(Ry-H/2),(int)(Rx+W/2) ,(int)(Ry+H/2),PageList);
				for(IntClass *D=PageList.GetFirst();D!=NULL;D=D->GetNext()){
					DataInPage	*P=GetLayersBase()->GetPageData(D->GetValue());
					int Lx1,Lx2,Lx3,Lx4;
					int Ly1,Ly2,Ly3,Ly4;
					P->GetLocalMatrixFromGlobalInMaster(c->Pos[0].X,c->Pos[0].Y ,Lx1,Ly1);
					P->GetLocalMatrixFromGlobalInMaster(c->Pos[1].X,c->Pos[1].Y ,Lx2,Ly2);
					P->GetLocalMatrixFromGlobalInMaster(c->Pos[2].X,c->Pos[2].Y ,Lx3,Ly3);
					P->GetLocalMatrixFromGlobalInMaster(c->Pos[3].X,c->Pos[3].Y ,Lx4,Ly4);
					CmdPieceAdd		CmdPAdd(GetLayersBase());
					CmdPAdd.X1	=Lx1;
					CmdPAdd.Y1	=Ly1;
					CmdPAdd.X2	=Lx2;
					CmdPAdd.Y2	=Ly2;
					CmdPAdd.X3	=Lx3;
					CmdPAdd.Y3	=Ly3;
					CmdPAdd.X4	=Lx4;
					CmdPAdd.Y4	=Ly4;
					CmdPAdd.MasterCode	=DMaster.MasterCode;
					CmdPAdd.GlobalPage	=D->GetValue();
					MBase->TransmitDirectly(&CmdPAdd);
				}
			}
		}			
	}
}
void	PiecePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}


GUIInitializer::GUIInitializer(LayersBase *base)
:ServiceForLayers(base)
{
	CommRootNumb=0;
	for(int i=0;i<sizeof(CommRoot)/sizeof(CommRoot[0]);i++){
		CommRoot[i]=NULL;

	}
	GuiDLLPack	=NULL;
	IntegrationComm				=NULL;
	//IntegrationPageDirectlyComm	=NULL;	
}
GUIInitializer::~GUIInitializer(void)
{
}

QTcpSocket	*GUIInitializer::GetSocket(int ComNo)
{
	return NULL;
}
QTcpSocket	*GUIInitializer::GetIntegrationSocket(int slaveNo)
{
	return NULL;
}

bool	GUIInitializer::TxData(int32 globalPage 
							   ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
							   ,int CommID ,QBuffer *f
							   ,ErrorCodeList &ErrorData)
{
	return false;
}
bool	GUIInitializer::TxData(int32 globalPage 
							   ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
							   ,int CommID ,QByteArray *f
							   ,ErrorCodeList &ErrorData)
{
	return false;
}

bool	GUIInitializer::TxIntegrationData(int32 slaveNo 
										  ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
										  ,QBuffer *f
										  ,ErrorCodeList &ErrorData)
{
	return false;
}


GUICmdReqPieceItemMasterCode::GUICmdReqPieceItemMasterCode(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqPieceItemMasterCode::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	GUICmdReqPieceItemMasterCode::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdReqPieceItemMasterCode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendPieceItemMasterCode	*SendBack=GetSendBack(GUICmdSendPieceItemMasterCode,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PieceArrange");
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		GetPieceItemInfoPacket	Cmd(this);
		Cmd.ItemID=ItemID;
		Ap->TransmitDirectly(&Cmd);
		SendBack->MasterCode=Cmd.MasterCode;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdSendPieceItemMasterCode::GUICmdSendPieceItemMasterCode(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendPieceItemMasterCode::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false)
		return false;
	return true;
}
bool	GUICmdSendPieceItemMasterCode::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false)
		return false;
	return true;
}

void	GUICmdSendPieceItemMasterCode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}



LayersBase::LayersBase(EntryPointBase *pEntryPoint,bool StartThreadWriteMode)
:AuthenticationInComponent(this)
,ShadowTree(-1,this)
,OnTerminating(false)
,EntryPoint(pEntryPoint)
,TopView(256,256,QImage::Format_RGB32)
,UndoDataStocker(this),RedoDataStocker(this)
,Parent(NULL)
,ChangingDataStructure(QReadWriteLock::Recursive)
,SystemResultContainer(this)
{
	ReadyOK					=false;
	GuiInitializerData		=NULL;
	GUIInstancePackData		=NULL;
	InstShowLoadingDLLForm	=NULL;
	ShadowNumber			=-1;
	CurrentShadowNumber		=-1;
	ReturnCode				=0;
    FastBoot				=false;
    StartThreadWriteMode	=false;
	#pragma omp parallel                             
	{             
		NumThreads=omp_get_num_threads();
	}
	LibType					=new LibTypeListContainer();
	InstalledLibType		=new LibTypeListContainer();
	ResultHistryData		=new ResultHistryContainer(this);
	ArrangementDLLStock		=new ArrangementDLLBase(this);
	LogCreater				=new LogOutClass("C:/LogFile.txt");
	ResultInspectionPointerStocker	=new ResultInspectionPointerStock();
	
	OnChanging				=false;
	MilisecExecuteFilter	=0;
	InsideLearningEditor	=false;
	QString	CurPath			=QDir::currentPath();
	FRegistry				=new FileRegistry(CurPath+QString(/**/"/MachineInfo.dat"));
	int	LanguageCode=GetFRegistry()->LoadRegInt(/**/"Language",0);
	LanguagePackageData		=new LanguagePackage();
	//LoadLanguageSolution(GetLanguageSolutionFileName());
	LanguagePackageData->SetLanguage(LanguageCode);
	UseDynamicMasking		=false;

	ParamGlobalData			=new ParamGlobal(this);
	ParamCommData			=new ParamComm	(this);
	ParamGUIData			=new ParamGUI	();
	AllocatedBufferInfoCount=0;
	BufferInfoListDim		=NULL;
	RCmdBase				=new NPListPack<ReceiverList>;
	GlobalOffset			=NULL;
	SendingData				=NULL;
	GlobalPageNumb			=0;
	CurrentLevel			=NULL;
	EnableFilter			=true;
	EnableProcess			=true;

	RIntegrationCmdBase		=new NPListPack<ReceiverList>;;
	IntegrationSendingData	=NULL;
	
	DefaultArrangeMode		=false;
	RootDBase				=NULL;
	OriginalRootDBase		=true;
	CurrentStrategicNumber	=0;
	CurrentStrategicNumberForSeq	=0;
	CurrentStrategicNumberForCalc	=0;
	CurrentStrategicNumberInExe		=0;
	StopCommSender			=false;
	MasterCode				= -1;
	PageData				=NULL;
	PageDataPhase			=NULL;
	DrawPageIndex			=NULL;
	CurrentPhase			=0;
	//AllocatedPageNumb		=0;
	AllocatedPhaseNumb		=0;
	//MachineID				=0;
	RegTime					=XDateTime::currentDateTime();
	WorkerID				= -1;
	Version					=RegulusVersion;
	LoadedVersion			=RegulusVersion;
	LastEditTime			=RegTime;
	StartInspectionTime		=RegTime;
	CategoryID				= -1;
	_CurrentInspectID		=0;
	_LastInspectID			=0;
	InspectionRemark		=0;
	LotInfo					=new LotBase(this);
	ExecuterDim				=NULL;
	AllocExecuterDim		=0;
	CurrentCalcPoint		=0;
	CurrentDrawPoint		=0;
	LastCurrentCalcPoint	=0;
	AlgoDLLContPointer		=new AlgorithmDLLContainer(this);
	LogicDLLBase			=new LogicDLLBaseClass(this);
	ResultDLLBase			=NULL;
	SequenceInstance		=NULL;
	InspectionTimeMilisec	=0;
	DBLoader				=NULL;
	MasterType				=0;		//0:MasterData 1:PieceData
	PieceStock				=new PieceStocker(this);
	BootingLevel			=0;
	OnProcessing			=NULL;
	ErrorOccurs				=0;
	AckFlag					=NULL;
	AllocatedAckFlag		=0;
	DirectCommBase			=NULL;
	ProcessingReEntrant		=0;
	LightBase				=NULL;
	ForceChangedInspectID	=false;
	LanguageCode			=0;
	MTransfer				=NULL;
	MainWidget				=NULL;
	LocalParamStocker		=new ParamDatabase(/**/"LocalData.dat");
	AppPointer	=(QApplication *)QCoreApplication::instance();
	ShouldWriteResult		=true;
	FilterBank				=NULL;
	OutlineOffsetWriter		=NULL;
	LogoStockerInstance		=NULL;
	AnyData					=NULL;
	GeneralStockerData		=NULL;
	ErrorContainer			=new ErrorCodeListContainer();
	LatchedInspectionNumber	=0;
	InsideReEntrant			=0;
	ResultWrittenID			=0;
	PasswordHolder			=NULL;
	SyncGUIData				=NULL;
	StatusControllerData	=NULL;
	LearningRegisterData	=NULL;
	EventPriority			=0;

	RCmdDirectCommBase		=new NPListPack<DirectCommReceiverList>; 
	LearningRegData			=new LearningRegListContainer();
	TmpHidingProcessingForm	=false;
	ListOfQImageStockerData	=new ListOfQImageStocker();

	MachineID				=FRegistry->LoadRegInt(/**/"MachineID",0);
	MachineIDFromMaster		=MachineID;
	CurrentScanPhaseNumber	=0;

	DataOfShareMasterContainer	=NULL;
	MainThread					=QThread::currentThreadId();
	PasteListMatrixContainerBase=NULL;
	OperationLoggerData			=NULL;
	PrinterClassPackData		=NULL;
	ShrinkingPackContainerInstance	=NULL;
	ModeInspectionPlayer		=false;
	LensWindow					=NULL;
	ZoneWindow					=NULL;
	CurrentZoneWindowComponent	=NULL;
	ResultFromAlgorithm			=0;
	IntegrationBaseData			=NULL;
	ResizeData					=new WidgetGeometry();
	ResultAnalizerDLLPack		=NULL;
	ResultAnalizerItemBasePack	=NULL;	
	ResultThread				=new WriteResultThread(this,StartThreadWriteMode);
	ViewRefreshCounter			=0;
	ThresholdLevelParentID		=0;
	ThresholdLevelID			=0;
	CurrentLibFolderID			=-1;
	AuthenticationInst			=NULL;
	FileThreadListContainerInst	=new FileThreadListContainer(this);
	EditPasswordMode			=false;
	LevelFolderContainerInst	=new LevelFolderContainer(this);
	
	EnableLoopOnIdle	=true;
	PossibleToUpdateDisplay		=true;
}