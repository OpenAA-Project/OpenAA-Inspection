#include "ButtonLoadMatrixCellResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadMatrixCell\ButtonLoadMatrixCell.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonLoadMatrixCell.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"
#include "MatrixCellListForm.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"

static	const	char	*sRoot=/**/"Review";
static	const	char	*sName=/**/"LoadMatrixCell";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to load MatrixCell file");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdWriteMatrixData(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonLoadMatrixCell(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonLoadMatrixCell *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLoadMatrixCell *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLoadMatrixCell *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLoadMatrixCell *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"FileName";
	Data[4].Pointer				 =&((ButtonLoadMatrixCell *)Instance)->FileName;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonLoadMatrixCell.png")));
}

static	bool	MacroLoad(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonLoadMatrixCell	*V=dynamic_cast<ButtonLoadMatrixCell *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString FileName=Args[0];

	if(FileName.isEmpty()==false){
		return V->LoadMatrixCell(FileName);
	}
	return true;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Load";
		Functions[ret].ArgName.append(/**/"File path and name");
		Functions[ret].Explain.append(/**/"Load MatrixCell");
		Functions[ret].DLL_ExcuteMacro	=MacroLoad;
		ret++;
	}
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonLoadMatrixCell::ButtonLoadMatrixCell(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Load MatrixCell";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonLoadMatrixCell::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonLoadMatrixCell::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonLoadMatrixCell::SlotClicked (bool checked)
{
	QString	LFileName;
	if(FileName.isEmpty()==true){
		LFileName=GetLayersBase()->LGetOpenFileName (this
								, LangSolver.GetString(ButtonLoadMatrixCell_LS,LID_0)/*"Load MatrixCell file"*/
								, QString()
								, tr(/**/"MatrixCell File (*.mcf)") );
	}
	else{
		LFileName=FileName;
	}
	LoadMatrixCell(LFileName);
}

void	ButtonLoadMatrixCell::TransmitDirectly(GUIDirectMessage *packet)
{
	ExecuteLoadMatrix	*ExecuteLoadMatrixVar=dynamic_cast<ExecuteLoadMatrix *>(packet);
	if(ExecuteLoadMatrixVar!=NULL){
		LoadMatrixCell(ExecuteLoadMatrixVar->FileName);
		return;
	}
}

bool	ButtonLoadMatrixCell::LoadMatrixCell(QString LFileName)
{
	QFile	F(LFileName);

	if(F.open(QIODevice::ReadOnly)==false)
		return false;

	GUIFormBase *Ret[100];
	int	N=GetLayersBase()->EnumGUIInst(/**/"Review",/**/"MatrixCellList",Ret ,100);
	if(N>0){
		MatrixCellListForm	*M=dynamic_cast<MatrixCellListForm *>(Ret[0]);
		if(M!=NULL){
			CmdLoadMatrixCellFile	RCmd(GetLayersBase());
			RCmd.FL=&F;
			M->TransmitDirectly(&RCmd);
		}
	}
	int32	AlgoCount;
	if(::Load(&F,AlgoCount)==false)
		return false;
	for(int n=0;n<AlgoCount;n++){
		QString	iAlgorithmRoot;
		QString	iAlgorithmName;
		if(::Load(&F,iAlgorithmRoot)==false)
			return false;
		if(::Load(&F,iAlgorithmName)==false)
			return false;
		if(::Load(&F,N)==false)
			return false;

		for(int i=0;i<N;i++){
			int32	globalPage;
			if(::Load(&F,globalPage)==false)
				return false;
			int32	Len;
			if(::Load(&F,Len)==false)
				return false;
			GUICmdWriteMatrixData	RData(GetLayersBase(),sRoot,sName,globalPage);
			RData.AlgorithmRoot	=iAlgorithmRoot;
			RData.AlgorithmName	=iAlgorithmName;
			RData.Data.close();
			QByteArray	M=F.read(Len);
			RData.Data.setData(M);
			RData.Data.open(QIODevice::ReadWrite);
			RData.SendOnly(globalPage,0);
		}
	}
	
	if(N>0){
		MatrixCellListForm	*M=dynamic_cast<MatrixCellListForm *>(Ret[0]);
		if(M!=NULL){
			CmdCreateMatrixCell	RCmd(GetLayersBase());
			M->TransmitDirectly(&RCmd);
		}
	}

	BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
	ViewRefreshInEdit();
	return true;
}

//==================================================================================================

GUICmdWriteMatrixData::GUICmdWriteMatrixData(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdWriteMatrixData::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,AlgorithmRoot)==false)
		return false;
	if(::Load(f,AlgorithmName)==false)
		return false;
	int64	DataSize;
	if(::Load(f,DataSize)==false)
		return false;
	QByteArray byteArray=f->read(DataSize);
	Data.setData(byteArray);
	return true;
}
bool	GUICmdWriteMatrixData::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,AlgorithmRoot)==false)
		return false;
	if(::Save(f,AlgorithmName)==false)
		return false;
	int64	DataSize=Data.size();
	if(::Save(f,DataSize)==false)
		return false;
	f->write(Data.data());
	return true;
}

void	GUICmdWriteMatrixData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AL=GetLayersBase()->GetAlgorithmBase(AlgorithmRoot ,AlgorithmName);
	if(AL!=NULL){
		Data.open(QIODevice::ReadWrite);
		if(Data.seek(0)==true){
			if(AL->LoadOnlyBase(&Data)==false)
				return;
			AlgorithmInPageRoot	*AP=AL->GetPageData(localPage);
			if(AP->Load(&Data)==false)
				return;
		}
		Data.close();
	}
	if(GetParamComm()->Mastered==true){
		if(localPage==GetPageNumb()-1){
		ExecuteInitialAfterEditInfo EInfo;
		EInfo.CalledInLoadMaster=true;
		GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
		}
	}
	else{
		ExecuteInitialAfterEditInfo EInfo;
		EInfo.CalledInLoadMaster=true;
		GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
	}

	SendAck(localPage);
}

