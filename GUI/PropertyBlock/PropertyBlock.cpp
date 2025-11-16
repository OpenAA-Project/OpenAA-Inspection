/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyBlock\PropertyBlock.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyBlock.h"
#include "PropertyBlockForm.h"
#include "XDisplayImage.h"
#include "PropertyBlockFormResource.h"
#include "XDisplayImagePacket.h"
#include "XMacroFunction.h"
#include "XDisplaySimPanel.h"
#include "XPropertyBlockPacket.h"
#include "XGUIPacketGeneral.h"

static	bool	MacroClearLibList(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetLib(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroGenerateBlocks(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetOutlineInLib(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetNGSizeInBlock(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetSearchDotInBlock(GUIFormBase *Instance ,QStringList &Args);

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyBlockForm";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for Block Inspection");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	//new GUICmdAddLimitedMask(QString(sRoot),QString(sName));
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSendAddManualBlock			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendModifySelectedBlock		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqSelectedBlockItemAttr	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendSelectedBlockItemAttr	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqBlockInfoList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendBlockInfoList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqBlockFromList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckBlockFromList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdPickupTestList				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdGenerateBlocks				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAreaHistgramInMaster		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAreaHistgramInMaster	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdTestClear					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReleaseSelectImagePanel		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqSetButtonMode			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqShrinkArea				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqShrinkHalf				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqExpandHalf				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetNGSizeInBlock			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetSearchDotInBlock			(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdUpdateBlockCommon			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdGenerateBlockCommon			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqRemoveAllOriginal		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdChangeBlocksThreshold		(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdReqDSimPanelImage	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckDSimPanelImage	(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	AlgorithmBase	*BBase=Base->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(BBase!=NULL){
		new GUICmdSelectByLibs	(BBase, QString(sRoot), QString(sName));
	}

	return(new PropertyBlockForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PropertyBlock.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"BlockInspection"));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ClearLibList";
		Functions[ret].Explain.append(/**/"Clear all LibID in current list");
		Functions[ret].DLL_ExcuteMacro	=MacroClearLibList;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetLib";
		Functions[ret].ArgName.append(/**/"LibID");
		Functions[ret].Explain.append(/**/"Set LibID in current list");
		Functions[ret].DLL_ExcuteMacro	=MacroSetLib;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Generate";
		Functions[ret].Explain.append(/**/"Generate blocks");
		Functions[ret].DLL_ExcuteMacro	=MacroGenerateBlocks;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetOutlineInLib";
		Functions[ret].ArgName.append(/**/"LibID");
		Functions[ret].ArgName.append(/**/"Gap pixel");
		Functions[ret].Explain.append(/**/"Set space in outline(mergin) in LibID");
		Functions[ret].DLL_ExcuteMacro	=MacroSetOutlineInLib;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetNGSizeInBlock";
		Functions[ret].ArgName.append(/**/"LibID");
		Functions[ret].ArgName.append(/**/"Type 1:B-Dark 2:B-Light 3:N-Dark 4:N-Light");
		Functions[ret].ArgName.append(/**/"NG Pixels");
		Functions[ret].Explain.append(/**/"Set space in outline(mergin) in LibID");
		Functions[ret].DLL_ExcuteMacro	=MacroSetNGSizeInBlock;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetSearchDotInBlock";
		Functions[ret].ArgName.append(/**/"LibID");
		Functions[ret].ArgName.append(/**/"Search dot");
		Functions[ret].Explain.append(/**/"Set space in outline(mergin) in LibID");
		Functions[ret].DLL_ExcuteMacro	=MacroSetSearchDotInBlock;
		ret++;
	}
	return ret;
}


static	bool	MacroClearLibList(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyBlockForm	*V=dynamic_cast<PropertyBlockForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ClearLibList();

	return true;
}

static	bool	MacroSetLib(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyBlockForm	*V=dynamic_cast<PropertyBlockForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	LibID=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->SetLib(LibID);

	return true;
}

static	bool	MacroGenerateBlocks(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyBlockForm	*V=dynamic_cast<PropertyBlockForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->GenerateBlocks();

	return true;
}
static	bool	MacroSetOutlineInLib(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyBlockForm	*V=dynamic_cast<PropertyBlockForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok;
	int	LibID=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	OutlineDot=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->CommandSetOutlineInLib(LibID,OutlineDot);

	return true;
}
static	bool	MacroSetNGSizeInBlock(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyBlockForm	*V=dynamic_cast<PropertyBlockForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<3){
		return false;
	}
	bool	ok;
	int	LibID=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	BlockType=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	NGSize=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->CommandSetNGSizeInBlock(LibID,BlockType,NGSize);

	return true;
}
static	bool	MacroSetSearchDotInBlock(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyBlockForm	*V=dynamic_cast<PropertyBlockForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok;
	int	LibID=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	SearchDot=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->CommandSetSearchDotInBlock(LibID,SearchDot);

	return true;
}