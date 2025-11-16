#include "IntegrationNewMasterResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\IntegrationNewMaster\IntegrationNewMaster.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationNewMaster.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "NewMasterDialog.h"
#include "IntegrationShowName.h"
#include "XMacroFunction.h"
#include "XDisplayImage.h"
#include "XDatabaseLoader.h"

static	const	char	*sRoot=/**/"Integration";
static	const	char	*sName=/**/"NewMaster";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to load master data");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)	=new IntegrationCmdNewMaster		(Base,sRoot,sName);
	(*Base)	=new IntegrationCmdClearAlgorithm	(Base,sRoot,sName);

	(*Base)	=new GUICmdNewMaster	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationNewMaster(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<10)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((IntegrationNewMaster *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationNewMaster *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationNewMaster *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationNewMaster *)Instance)->CFont;
	Data[4].Type				 =/**/"double";
	Data[4].VariableNameWithRoute=/**/"AddedMMX";
	Data[4].Pointer				 =&((IntegrationNewMaster *)Instance)->AddedMMX;
	Data[5].Type				 =/**/"double";
	Data[5].VariableNameWithRoute=/**/"AddedMMY";
	Data[5].Pointer				 =&((IntegrationNewMaster *)Instance)->AddedMMY;
	Data[6].Type				 =/**/"double";
	Data[6].VariableNameWithRoute=/**/"AddedMMZ";
	Data[6].Pointer				 =&((IntegrationNewMaster *)Instance)->AddedMMZ;
	Data[7].Type				 =/**/"double";
	Data[7].VariableNameWithRoute=/**/"MaxWidth";
	Data[7].Pointer				 =&((IntegrationNewMaster *)Instance)->MaxWidth;
	Data[8].Type				 =/**/"double";
	Data[8].VariableNameWithRoute=/**/"MaxLength";
	Data[8].Pointer				 =&((IntegrationNewMaster *)Instance)->MaxLength;

	return(9);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationNewMaster.png")));
}

static	bool	MacroOpenDialog(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroClearAlgorithm(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"OpenDialog";
		Functions[ret].Explain.append(/**/"Open dialog");
		Functions[ret].DLL_ExcuteMacro	=MacroOpenDialog;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ClearAlgorithm";
		Functions[ret].Explain.append(/**/"Clear Algorithm data");
		Functions[ret].DLL_ExcuteMacro	=MacroClearAlgorithm;
		ret++;
	}
	return ret;
}

static bool	MacroOpenDialog(GUIFormBase *Instance ,QStringList &Args)
{
	IntegrationNewMaster	*V=dynamic_cast<IntegrationNewMaster *>(Instance);
	if(V==NULL){
		return false;
	}

	V->OpenDialog();

	return true;
}
static bool	MacroClearAlgorithm(GUIFormBase *Instance ,QStringList &Args)
{
	IntegrationNewMaster	*V=dynamic_cast<IntegrationNewMaster *>(Instance);
	if(V==NULL){
		return false;
	}

	V->ClearAlgorithm();

	return true;
}



//==================================================================================================

IntegrationNewMaster::IntegrationNewMaster(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	LangSolver.SetUI(this);

	Button.setParent(this);
	Button.setObjectName(/**/"IntegrationNewMasterBtn");
	Button.move(0,0);
	Msg=/**/"Clear master data";
	resize(80,25);
	AddedMMX	=0;
	AddedMMY	=0;
	AddedMMZ	=0;
	MaxWidth	=500;
	MaxLength	=900;

	Button.setStyleSheet(/**/"QToolButton {"
						/**/"	border-style: outset;"
						/**/"	border-width: 1px;"
						/**/"	border-radius: 25px;"
						/**/"	border-color: gray;"
						/**/"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));"
						/**/"}"
						/**/"QToolButton:pressed { 	"
						/**/"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));"
						/**/"}"
						);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationNewMaster::~IntegrationNewMaster()
{

}

void	IntegrationNewMaster::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	IntegrationNewMaster::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	IntegrationNewMaster::OpenDialog(void)
{
	SlotClicked();
}
void	IntegrationNewMaster::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdOpenNewMasterDialog	*CmdOpenNewMasterDialogVar=dynamic_cast<CmdOpenNewMasterDialog *>(packet);
	if(CmdOpenNewMasterDialogVar!=NULL){
		SlotClicked();
		return;
	}
}

void	IntegrationNewMaster::SlotClicked ()
{
//	if(GetLayersBase()->GetIntegrationBasePointer()->NowOnUsing()==false){
		NewMasterDialog	D(GetLayersBase(),this);
		if(D.exec()!=true)
			return;

		GetLayersBase()->ShowProcessingForm(LangSolver.GetString(IntegrationNewMaster_LS,LID_0)/*"蛻晄悄蛹紋ｸｭ"*/);
		GetLayersBase()->SetMaxProcessing(6);

		int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		IntegrationCmdPacketBaseContainer	RCmdContainer;
		for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
			IntegrationCmdNewMaster	*p=new IntegrationCmdNewMaster(GetLayersBase(),sRoot,sName,SlaveNo);
			p->CommonData	=D.CommonData;
			p->CommonData.AddedX=AddedMMX;
			p->CommonData.AddedY=AddedMMY;
			p->CommonData.AddedZ=AddedMMZ;
			RCmdContainer.AppendList(p);
		}
		IntegrationMultiAck(RCmdContainer,60*1000*N);

		for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
			if(m!=NULL){
				m->RemoveAllCurrentInspection();
				m->ClearLotContainer();
				m->SetCurrentLot(NULL);
				m->ClearImageBuff();
				m->SetCurrentPhase(0);
			}
		}
		GetLayersBase()->GetIntegrationBasePointer()->SetCommonData(D.CommonData);
		for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
			if(m!=NULL){
				for(int page=0;page<m->GetPageNumb();page++){
					int	YLen=GetParamGlobal()->TransformUnitDistanceToPixel(page,0,D.CommonData.CommonSizeY);
					int	XLen=m->GetDotPerLine(0,page);
					m->ReallocXYPixels(page,XLen ,YLen);
				}
			}
		}
		CmdClearMasterData	ICmd;
		BroadcastSpecifiedDirectly(&ICmd);
		RepaintAll();

		GetLayersBase()->GetIntegrationBasePointer()->MasterRelationCode=-1;
		GetLayersBase()->GetIntegrationBasePointer()->SetCommonData(D.CommonData);

		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ShowName",/**/"");
		if(f!=NULL){
			CmdShowNameInfo	RCmd;
			RCmd.MasterNumber	=D.CommonData.RelationNumber;
			RCmd.MasterName		=D.CommonData.RelationName
								+QString(LangSolver.GetString(IntegrationNewMaster_LS,LID_1)/*"(隕√��繝槭せ繧ｿ繝ｼ繝��繧ｿ菫晏ｭ�"*/);
			RCmd.Remark			=D.CommonData.RelationRemark;
			f->SpecifiedDirectly(&RCmd);
		}

		bool	NowOnIdle;
		do{
			NowOnIdle=true;
			for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
				int	SlaveNo=m->GetIntegrationSlaveNo();
				if(GetLayersBase()->GetIntegrationBasePointer()->CheckOnProcessing(SlaveNo)==false){
					NowOnIdle=false;
				}
			}
		}while(NowOnIdle==false);

		CreateNewMasterSpecifiedBroadcaster	BCmd;
		BroadcastSpecifiedDirectly(&BCmd);
		BroadcastStartInitial();

		GetLayersBase()->CloseProcessingForm();
//	}
}
void	IntegrationNewMaster::ClearAlgorithm(void)
{
	int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
		IntegrationCmdClearAlgorithm	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.SendReqAck(NULL,SlaveNo,0);
	}
}

bool	IntegrationNewMaster::CheckDupInMaster(  const QString &ResultName
												,const QString &ResultNumber
												,const QString &ResultRemark)
{
	IntList		RelationMasterCodes;
	if(GetLayersBase()->GetDatabaseLoader()->G_FindMasterRelation(GetLayersBase()->GetDatabase()
																,ResultName
																,ResultNumber
																,ResultRemark
																,RelationMasterCodes)==false){
		return false;
	}
	if(RelationMasterCodes.GetCount()!=0)
		return false;
	return true;
}

//==================================================================================================
IntegrationCmdNewMaster::IntegrationCmdNewMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdNewMaster::Load(QIODevice *f)
{
	if(CommonData.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationCmdNewMaster::Save(QIODevice *f)
{
	if(CommonData.Save(f)==false)
		return false;
	return true;
}
void	IntegrationCmdNewMaster::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdNewMaster	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.DistanceX	=0;
		RCmd.DistanceY	=CommonData.CommonSizeY+CommonData.AddedY;
		RCmd.Send(NULL,GlobalPage,0);
	}


	//int	YLen=GetParamGlobal()->TransformUnitDistanceToPixel(0,(CommonData.CommonSizeY+CommonData.AddedY));
	//YLen &=0x8FFFFFF0;
	//GetLayersBase()->Reallocate(1);
	//GetLayersBase()->ReallocXYPixels(GetDotPerLine(-1),YLen);
	//GetLayersBase()->WriteAllSettingFiles();

	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ClearMasterInfo",/**/"");
	if(f!=NULL){
		QStringList Args;
		bool ExeReturn;
		f->ExecuteMacro(/**/"ClearPhase", Args, ExeReturn);
		f->ExecuteMacro(/**/"Clear", Args, ExeReturn);
	}
	GUIFormBase *Ret[1000];
	int	N=GetLayersBase()->EnumGUI(Ret ,1000);
	for(int i=0;i<N;i++){
		DisplayImage	*p=dynamic_cast<DisplayImage *>(Ret[i]);
		if(p!=NULL){
			QStringList Args;
			bool ExeReturn;
			p->ExecuteMacro(/**/"ClearTargetImage", Args, ExeReturn);
			break;
		}
	}
	IntegrationNewMaster	*Fn=(IntegrationNewMaster	*)GetLayersBase()->FindByName(sRoot,sName,/**/"");
	if(Fn!=NULL){
		Fn->BroadcastStartInitial();
		Fn->BroadcastBuildForShow();
	}
	SendAck(slaveNo);
}

IntegrationCmdClearAlgorithm::IntegrationCmdClearAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	IntegrationCmdClearAlgorithm::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase *Ret[1000];
	int	N=GetLayersBase()->EnumGUI(Ret ,1000);
	for(int i=0;i<N;i++){
		DisplayImage	*p=dynamic_cast<DisplayImage *>(Ret[i]);
		if(p!=NULL){
			QStringList Args;
			bool ExeReturn;
			p->ExecuteMacro(/**/"SelectAllItems", Args, ExeReturn);
		}
		if(p!=NULL){
			QStringList Args;
			bool ExeReturn;
			p->ExecuteMacro(/**/"DeleteItems", Args, ExeReturn);
		}
	}
}

//========================================================================
	
GUICmdNewMaster::GUICmdNewMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdNewMaster::Load(QIODevice *f)
{
	if(::Load(f,DistanceX)==false)	return false;
	if(::Load(f,DistanceY)==false)	return false;
	return true;
}
bool	GUICmdNewMaster::Save(QIODevice *f)
{
	if(::Save(f,DistanceX)==false)	return false;
	if(::Save(f,DistanceY)==false)	return false;
	return true;
}

void	GUICmdNewMaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int	YLen=GetParamGlobal()->TransformUnitDistanceToPixel(localPage,DistanceX,DistanceY);
	YLen &=0x8FFFFFF0;

	//GetLayersBase()->Reallocate(1);
	GetLayersBase()->ReallocXYPixelsPage(0,localPage,GetDotPerLine(-1),YLen);
	GetLayersBase()->WriteAllSettingFiles();
}

