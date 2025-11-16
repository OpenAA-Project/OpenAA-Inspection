#include "ButtonSaveMatrixCellResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSaveMatrixCell\ButtonSaveMatrixCell.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonSaveMatrixCell.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"
#include "MatrixCellListForm.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"

static	const	char	*sRoot=/**/"Review";
static	const	char	*sName=/**/"SaveMatrixCell";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to save MatrixCell file");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqAlgorithmData	(Base,sRoot,sName);
	(*Base)=new GUICmdSendAlgorithmData	(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSaveMatrixCell(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSaveMatrixCell *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSaveMatrixCell *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSaveMatrixCell *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSaveMatrixCell *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"FileName";
	Data[4].Pointer				 =&((ButtonSaveMatrixCell *)Instance)->FileName;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSaveMatrixCell.png")));
}

static	bool	MacroSave(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSaveMatrixCell	*V=dynamic_cast<ButtonSaveMatrixCell *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString FileName=Args[0];

	if(FileName.isEmpty()==false){
		return V->SaveMatrixCell(FileName);
	}
	return true;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Save";
		Functions[ret].ArgName.append(/**/"File path and name");
		Functions[ret].Explain.append(/**/"Save MatrixCell");
		Functions[ret].DLL_ExcuteMacro	=MacroSave;
		ret++;
	}
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonSaveMatrixCell::ButtonSaveMatrixCell(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Save MatrixCell";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonSaveMatrixCell::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSaveMatrixCell::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonSaveMatrixCell::SlotClicked (bool checked)
{
	QString	LFileName;
	if(FileName.isEmpty()==true){
		LFileName=GetLayersBase()->LGetSaveFileName (this
									, LangSolver.GetString(ButtonSaveMatrixCell_LS,LID_0)/*"Save MatrixCell file"*/
									, QString()
									, tr(/**/"MatrixCell File (*.mcf)") );
	}
	else{
		LFileName=FileName;
	}
	SaveMatrixCell(LFileName);
}

bool	ButtonSaveMatrixCell::SaveMatrixCell(QString LFileName)
{
	QFile	F(LFileName);

	if(F.open(QIODevice::WriteOnly)==false)
		return false;

	GUIFormBase *Ret[100];
	int	N=GetLayersBase()->EnumGUIInst(/**/"Review",/**/"MatrixCellList",Ret ,100);
	if(N>0){
		MatrixCellListForm	*M=dynamic_cast<MatrixCellListForm *>(Ret[0]);
		if(M!=NULL){
			CmdSaveMatrixCellFile	RCmd(GetLayersBase());
			RCmd.FL=&F;
			M->TransmitDirectly(&RCmd);
		}
	}
	int32	AlgoCount=GetLayersBase()->GetLogicDLLBase()->GetNumber();
	if(::Save(&F,AlgoCount)==false)
		return false;

	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		GUICmdReqAlgorithmData  **RData=new GUICmdReqAlgorithmData *[GetParamGlobal()->PageNumb];
		GUICmdSendAlgorithmData	**SData=new GUICmdSendAlgorithmData*[GetParamGlobal()->PageNumb];
		int32	N=0;
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			RData[page]=new GUICmdReqAlgorithmData (GetLayersBase(),sRoot,sName,globalPage);
			SData[page]=new GUICmdSendAlgorithmData(GetLayersBase(),sRoot,sName,globalPage);
			RData[page]->AlgorithmRoot	=L->GetDLLRoot();
			RData[page]->AlgorithmName	=L->GetDLLName();
			RData[page]->Send(globalPage,0,*SData[page]);
			if(SData[page]->IsReceived()==true){
				N++;
			}
		}

		if(::Save(&F,L->GetDLLRoot())==false){
			for(int page=0;page<GetParamGlobal()->PageNumb;page++){
				delete	RData[page];
				delete	SData[page];
			}
			delete	[]RData;
			delete	[]SData;
			return false;
		}
		if(::Save(&F,L->GetDLLName())==false){
			for(int page=0;page<GetParamGlobal()->PageNumb;page++){
				delete	RData[page];
				delete	SData[page];
			}
			delete	[]RData;
			delete	[]SData;
			return false;
		}
		if(::Save(&F,N)==false){
			for(int page=0;page<GetParamGlobal()->PageNumb;page++){
				delete	RData[page];
				delete	SData[page];
			}
			delete	[]RData;
			delete	[]SData;
			return false;
		}
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			if(SData[page]->IsReceived()==true){
				int32	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
				if(::Save(&F,globalPage)==false)
					break;
				int32	Len=SData[page]->Data.size();
				if(::Save(&F,Len)==false)
					break;
				F.write(SData[page]->Data.data());
			}
		}
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			delete	RData[page];
			delete	SData[page];
		}
		delete	[]RData;
		delete	[]SData;
	}
	return true;
}

//==================================================================================================
GUICmdReqAlgorithmData::GUICmdReqAlgorithmData(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlgorithmData::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,AlgorithmRoot)==false)
		return false;
	if(::Load(f,AlgorithmName)==false)
		return false;
	return true;
}
bool	GUICmdReqAlgorithmData::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,AlgorithmRoot)==false)
		return false;
	if(::Save(f,AlgorithmName)==false)
		return false;
	return true;
}

void	GUICmdReqAlgorithmData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlgorithmData	*SendBack=GetSendBack(GUICmdSendAlgorithmData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*AL=GetLayersBase()->GetAlgorithmBase(AlgorithmRoot ,AlgorithmName);
	if(AL!=NULL){
		SendBack->GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
		SendBack->Data.open(QIODevice::ReadWrite);
		AL->SaveOnlyBase(&SendBack->Data);
		AlgorithmInPageRoot		*AP=AL->GetPageData(localPage);
		AP->Save(&SendBack->Data);
	}
	SendBack->Data.seek(0);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlgorithmData::GUICmdSendAlgorithmData(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAlgorithmData::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	int64	DataSize;
	if(::Load(f,DataSize)==false)
		return false;
	QByteArray byteArray=f->read(DataSize);
	Data.setData(byteArray);
	return true;
}
bool	GUICmdSendAlgorithmData::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	int64	DataSize=Data.size();
	if(::Save(f,DataSize)==false)
		return false;
	f->write(Data.data());
	return true;
}

void	GUICmdSendAlgorithmData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
