/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SaveImageMasterButton\SaveImageMasterButton.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "AutoSaveImageMasterButtonResource.h"
#include "AutoSaveImageMasterButton.h"
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include <QMessageBox>


static	char	*sRoot=/**/"Inspection";
static	char	*sName=/**/"AutoSaveImageMasterButton";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Auto Save Master Image");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqSaveMasterImage (Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendSaveMasterImage(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new AutoSaveImageMasterButton(Base,parent));
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
	Data[0].Pointer				 =&((AutoSaveImageMasterButton *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((AutoSaveImageMasterButton *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((AutoSaveImageMasterButton *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((AutoSaveImageMasterButton *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"DirectoryNameForSaving";
	Data[4].Pointer				 =&((AutoSaveImageMasterButton *)Instance)->DirectoryNameForSaving;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/AutoSaveImageMasterButton.png")));
}

static	bool	MacroSave(GUIFormBase *Instance ,QStringList &Args)
{
	AutoSaveImageMasterButton	*V=dynamic_cast<AutoSaveImageMasterButton *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString FileName=Args[0];

	if(FileName.isEmpty()==false){
		return V->SaveImage(FileName);
	}
	return true;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Save";
		Functions[ret].ArgName.append(/**/"File path and name");
		Functions[ret].Explain.append(/**/"Save PIX from Master");
		Functions[ret].DLL_ExcuteMacro	=MacroSave;
		ret++;
	}
	return ret;
}

//==================================================================================================
AutoSaveImageMasterButton::AutoSaveImageMasterButton(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"AutoSaveMaster");
	ButtonObjectName=/**/"";
	Msg=/**/"Auto Save Master";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

AutoSaveImageMasterButton::~AutoSaveImageMasterButton(void)
{
}

void	AutoSaveImageMasterButton::Prepare(void)
{
	if(GetName().isEmpty()==false){
		Button.setObjectName(GetName());
	}
	ButtonObjectName=/**/"_" + Button.objectName() + /**/".pix";
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	AutoSaveImageMasterButton::ResizeAction()
{
	Button.resize(width(),height());
}

void AutoSaveImageMasterButton::SlotClicked (bool checked)
{
	QString	FileName;

	if(DirectoryNameForSaving.isEmpty()==true){
		FileName=GetLayersBase()->LGetSaveFileName (this
													, LangSolver.GetString(AutoSaveImageMasterButton_LS,LID_0)/*"Save Master Image file"*/
													,QString()
													,QString(/**/"ImageFile(*.pix);;AllFile(*.*)")) ;
	}
	else{
		QString DirNameForSaving=DirectoryNameForSaving + QDir::separator() + QDate::currentDate().toString(/**/"yyyyMMdd");
		if(QDir(DirNameForSaving).exists()==false){
			QDir dir;
			if(dir.mkpath(DirNameForSaving)==false){
				QFont font1;
				font1.setPointSize(12);
				font1.setBold(true);
				font1.setWeight(75);
				QMessageBox MsgBox;
				MsgBox.setFont	(font1);
				MsgBox.setText	(LangSolver.GetString(AutoSaveImageMasterButton_LS,LID_1)/*"pixファイルの保存ディレクトリを作成できませんでした。"*/);
				MsgBox.addButton(LangSolver.GetString(AutoSaveImageMasterButton_LS,LID_2)/*"閉じる"*/	,QMessageBox::AcceptRole);
				MsgBox.setWindowFlags(Qt::WindowStaysOnTopHint);	//常に前面に表示
				MsgBox.exec();
				return;
			}
		}
		FileName=DirNameForSaving + QDir::separator() + QTime::currentTime().toString(/**/"hhmmss") + ButtonObjectName;
	}
	if(SaveImage(FileName)==false){
		QFont font1;
		font1.setPointSize(12);
		font1.setBold(true);
		font1.setWeight(75);
		QMessageBox MsgBox;
		MsgBox.setFont	(font1);
		MsgBox.setText	(LangSolver.GetString(AutoSaveImageMasterButton_LS,LID_3)/*"pixファイルの保存に失敗しました。"*/);
		MsgBox.addButton(LangSolver.GetString(AutoSaveImageMasterButton_LS,LID_4)/*"閉じる"*/	,QMessageBox::AcceptRole);
		MsgBox.setWindowFlags(Qt::WindowStaysOnTopHint);	//常に前面に表示
		MsgBox.exec();
		return;
	}
}

bool AutoSaveImageMasterButton::SaveImage(QString FileName)
{
	QFile	WFile(FileName);
	if(WFile.open(QIODevice::WriteOnly)==false)
		return false;

	int	Ver=1;
	if(::Save(&WFile,Ver)==false)
		return false;
	if(::Save(&WFile,(int)GetPageNumb())==false)
		return false;
	if(::Save(&WFile,(int)GetLayerNumb())==false)
		return false;
	if(::Save(&WFile,(int)GetDotPerLine())==false)
		return false;
	if(::Save(&WFile,(int)GetMaxLines())==false)
		return false;
	if(::Save(&WFile,(int)100)==false)
		return false;

	GetLayersBase()->ShowProcessingForm ("Save image from master buffer");

	for(int page=0;page<GetPageNumb();page++){
		GetLayersBase()->AddMaxProcessing(page,1);
		int	YCount=100;
		for(int TopY=0;TopY<GetMaxLines();TopY+=YCount){
			if(TopY+YCount>GetMaxLines())
				YCount=GetMaxLines()-TopY;
			for(int Layer=0;Layer<GetLayerNumb();Layer++){
				GUICmdReqSaveMasterImage	RCmd(GetLayersBase() ,sRoot,sName,page);
				RCmd.Layer	=Layer;
				RCmd.TopY	=TopY;
				RCmd.YCount	=YCount;
				GUICmdSendSaveMasterImage	SCmd(GetLayersBase() ,sRoot,sName,page);
				if(RCmd.Send(page ,0,SCmd)==true){
					if(WFile.write(SCmd.Data)!=SCmd.Data.size()){
						return false;
					}
				}
			}
		}
		GetLayersBase()->StepProcessing(page);
	}
	GetLayersBase()->CloseProcessingForm ();
	return true;
}
void	AutoSaveImageMasterButton::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(AutoSaveImageMasterButton_LS,LID_5)/*"FILE"*/,LangSolver.GetString(AutoSaveImageMasterButton_LS,LID_6)/*"Save MasterImage(PIX)"*/,this);
	p->SetMenuNumber(5010);
	Info.AppendList(p);
}
void	AutoSaveImageMasterButton::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
GUICmdReqSaveMasterImage::GUICmdReqSaveMasterImage(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSaveMasterImage::Load(QIODevice *f)
{
	if(::Load(f,TopY)==false)
		return false;
	if(::Load(f,YCount)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}
bool	GUICmdReqSaveMasterImage::Save(QIODevice *f)
{
	if(::Save(f,TopY)==false)
		return false;
	if(::Save(f,YCount)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

void	GUICmdReqSaveMasterImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSaveMasterImage	*SendBack=GetSendBack(GUICmdSendSaveMasterImage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	DataInLayer	*L=GetLayersBase()->GetPageData(localPage)->GetLayerData(Layer);
	if(L!=NULL){
		SendBack->Data.resize(YCount*GetDotPerLine(localPage));
		BYTE	*Dest=(BYTE *)SendBack->Data.data();
		for(int y=TopY;y<TopY+YCount;y++){
			memcpy(Dest,L->GetMasterBuff().GetY(y),GetDotPerLine(localPage));
			Dest+=GetDotPerLine(localPage);
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendSaveMasterImage::GUICmdSendSaveMasterImage(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendSaveMasterImage::Load(QIODevice *f)
{
	Data=f->readAll();
	return true;
}
bool	GUICmdSendSaveMasterImage::Save(QIODevice *f)
{
	f->write(Data);
	return true;
}

void	GUICmdSendSaveMasterImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
