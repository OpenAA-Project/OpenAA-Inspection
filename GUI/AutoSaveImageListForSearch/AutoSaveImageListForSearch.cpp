#include "AutoSaveImageListForSearchResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AutoSaveImageListForSearch\AutoSaveImageListForSearch.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "AutoSaveImageListForSearch.h"
#include "XGeneralDialog.h"
//#include "XGUI.h"
#include "LoadAutoSaveImageDialog.h"
#include "XGeneralFunc.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"AutoSaveImageListForSearch";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Search AutoSaveImageList");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdLoadAutoSaveImageFile(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new AutoSaveImageListForSearch(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((AutoSaveImageListForSearch *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((AutoSaveImageListForSearch *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((AutoSaveImageListForSearch *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((AutoSaveImageListForSearch *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/AutoSaveImageListForSearch.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoSaveImage"));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
AutoSaveImageListForSearch::AutoSaveImageListForSearch(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"AutoSaveImageList For Search";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

AutoSaveImageListForSearch::~AutoSaveImageListForSearch(void)
{
}

void	AutoSaveImageListForSearch::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	AutoSaveImageListForSearch::ResizeAction()
{
	Button.resize(width(),height());
}

void	AutoSaveImageListForSearch::ShowInPlayer(int64 shownInspectionID)
{
}

QString	FindFile(QStringList &FileNames ,int page,int layer)
{
	for(int i=0;i<FileNames.count();i++){
		bool	ok;
		QFileInfo	FInfo(FileNames[i]);
		QString	FileName=FInfo.fileName();
		int	FileMin		=FileName.mid(0,2).toInt(&ok);	if(ok==false)	continue;
		int	FileSec		=FileName.mid(2,2).toInt(&ok);	if(ok==false)	continue;
		int	FilePage	=FileName.mid(5,2).toInt(&ok);	if(ok==false)	continue;
		int	FileLayer	=FileName.mid(8,2).toInt(&ok);	if(ok==false)	continue;
		if(FilePage==page && FileLayer==layer){
			return FileNames[i];
		}
	}
	return /**/"";
}

void AutoSaveImageListForSearch::SlotClicked (bool checked)
{
	LoadAutoSaveImageDialog	D(GetLayersBase());
	if(D.exec()==(int)true){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdLoadAutoSaveImageFile	PushRequester(GetLayersBase(),sRoot,sName);
			for(int layer=0;layer<GetLayerNumb(page);layer++){
				QString	FileName=FindFile(D.Selected->EachFileNames,page,layer);
				PushRequester.AutoSaveImageFileNames.append(FileName);
			}
			PushRequester.Send(NULL,GlobalPage,0);
		}
	}
}


void	AutoSaveImageListForSearch::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(105,LangSolver.GetString(AutoSaveImageListForSearch_LS,LID_0)/*"File"*/,LangSolver.GetString(AutoSaveImageListForSearch_LS,LID_1)/*"Image List for Search"*/,this);
	p->SetMenuNumber(105);
	Info.AppendList(p);
}
void	AutoSaveImageListForSearch::ExecuteMenu(int ID)
{
	if(ID==105){
		SlotClicked(true);
	}
}


//=============================================================================
GUICmdLoadAutoSaveImageFile::GUICmdLoadAutoSaveImageFile(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdLoadAutoSaveImageFile::Load(QIODevice *f)
{
	if(::Load(f,AutoSaveImageFileNames)==false)
		return false;
	return true;
}

bool	GUICmdLoadAutoSaveImageFile::Save(QIODevice *f)
{
	if(::Save(f,AutoSaveImageFileNames)==false)
		return false;
	return true;
}

void	GUICmdLoadAutoSaveImageFile::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Algo=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoSaveImage");
	if(Algo!=NULL){
		CmdLoadBandList	RCmd(GetLayersBase());
		for(int layer=0;layer<GetLayerNumb(localPage);layer++){
			RCmd.Buff[layer]=&GetLayersBase()->GetPageData(localPage)->GetLayerData(layer)->GetTargetBuff();
		}

		RCmd.FileNames=AutoSaveImageFileNames;
		RCmd.BufferDimCounts	=GetLayerNumb(localPage);
		Algo->GetPageData(localPage)->TransmitDirectly(&RCmd);
	}
}