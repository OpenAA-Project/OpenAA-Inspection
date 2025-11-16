/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadBmpJpg\ButtonLoadBmpJpg.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonLoadBmpJpgResource.h"
#include "ButtonLoadBmpJpg.h"
#include <stdio.h>
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"
#include <setjmp.h>
#include "swap.h"
#include "XCriticalFunc.h"

extern	"C"
{
extern	jmp_buf err_jmpbuf;
};

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ButtonLoadBmpJpg";


bool	read_jpeg_stream(FILE *fp,ImageBuffer *Buff[] ,int LayerNumb);
bool	read_jpeg_stream(FILE *fp,QImage &Img);

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to load BMP/JPG file");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqLoadBmpJpg(Base,QString(sRoot),QString(sName));

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
	return(new ButtonLoadBmpJpg(Base,parent));
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
	Data[0].Pointer				 =&((ButtonLoadBmpJpg *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLoadBmpJpg *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLoadBmpJpg *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLoadBmpJpg *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ToMaster";
	Data[4].Pointer				 =&((ButtonLoadBmpJpg *)Instance)->ToMaster;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"LoadedPage";
	Data[5].Pointer				 =&((ButtonLoadBmpJpg *)Instance)->LoadedPage;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonLoadBmpJpg.png")));
}

static	bool	MacroLoad(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonLoadBmpJpg	*V=dynamic_cast<ButtonLoadBmpJpg *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	QString FileName=Args[0];

	if(FileName.isEmpty()==false){
		if(QString::compare(Args[1],/**/"Master",Qt::CaseInsensitive)==0){
			V->LoadFile(FileName,true);
			return true;
		}
		else if(QString::compare(Args[1],/**/"Target",Qt::CaseInsensitive)==0){
			V->LoadFile(FileName,false);
			return true;
		}
	}
	return false;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Load";
		Functions[ret].ArgName.append(/**/"File path and name");
		Functions[ret].ArgName.append(/**/"Master/Target");
		Functions[ret].Explain.append(/**/"Load Bmp/Jpg");
		Functions[ret].DLL_ExcuteMacro	=MacroLoad;
		ret++;
	}
	return ret;
}

//==================================================================================================
ButtonLoadBmpJpg::ButtonLoadBmpJpg(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"ButtonLoadBmpJpgBtn");
	Button.move(0,0);
	Msg			=/**/"Load BMP/Jpg";
	CharColor	=Qt::black;
	BackColor	=Qt::lightGray;
	ToMaster=true;
	LoadedPage=0;
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonLoadBmpJpg::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonLoadBmpJpg::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLoadBmpJpgPacket	*CmdLoadBmpJpgPacketVar=dynamic_cast<CmdLoadBmpJpgPacket *>(packet);
	if(CmdLoadBmpJpgPacketVar!=NULL){
		CmdLoadBmpJpgPacketVar->Success	=LoadFile(CmdLoadBmpJpgPacketVar->FileName,ToMaster);
		BroadcastShowInEdit();
		return;
	}
	CmdLoadBmpJpgPacketMaster	*CmdLoadBmpJpgPacketMasterVar=dynamic_cast<CmdLoadBmpJpgPacketMaster *>(packet);
	if(CmdLoadBmpJpgPacketMasterVar!=NULL){
		CmdLoadBmpJpgPacketMasterVar->Success	=LoadFile(CmdLoadBmpJpgPacketMasterVar->FileName,true);
		BroadcastShowInEdit();
		return;
	}
	CmdLoadBmpJpgPacketTarget	*CmdLoadBmpJpgPacketTargetVar=dynamic_cast<CmdLoadBmpJpgPacketTarget *>(packet);
	if(CmdLoadBmpJpgPacketTargetVar!=NULL){
		CmdLoadBmpJpgPacketTargetVar->Success	=LoadFile(CmdLoadBmpJpgPacketTargetVar->FileName,false);
		BroadcastShowInEdit();
		return;
	}
	CmdLoadBmpJpgWithDialogPacket	*CmdLoadBmpJpgWithDialogPacketar=dynamic_cast<CmdLoadBmpJpgWithDialogPacket *>(packet);
	if(CmdLoadBmpJpgWithDialogPacketar!=NULL){
		QString	FileName=LoadFileWithDialog();
		if(FileName.isEmpty()==false){
			CmdLoadBmpJpgWithDialogPacketar->FileName=FileName;
			CmdLoadBmpJpgWithDialogPacketar->Success=true;
		}
		else{
			CmdLoadBmpJpgWithDialogPacketar->Success=false;
		}
		BroadcastShowInEdit();
		return;
	}
	CmdLoadBmpJpgPacketQImage	*CmdLoadBmpJpgPacketQImageVar=dynamic_cast<CmdLoadBmpJpgPacketQImage *>(packet);
	if(CmdLoadBmpJpgPacketQImageVar!=NULL){
		CmdLoadBmpJpgPacketQImageVar->Success	=LoadFile(CmdLoadBmpJpgPacketQImageVar->FileName,CmdLoadBmpJpgPacketQImageVar->Image);
		return;
	}
}
void	ButtonLoadBmpJpg::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonLoadBmpJpg::SlotClicked (bool checked)
{
	LoadFileWithDialog();
}
QString	ButtonLoadBmpJpg::LoadFileWithDialog(void)
{
	QString	FileName=GetLayersBase()->LGetOpenFileName (this, LangSolver.GetString(ButtonLoadBmpJpg_LS,LID_0)/*"Load BMP/JPG file"*/
														, QString()
														, tr(/**/"Image Files (*.png *.jpg *.bmp)") );
	if(FileName.isEmpty()==false){
		if(LoadFile(FileName,ToMaster)==false)
			return /**/"";
		return FileName;
	}
	return /**/"";
}
bool	LoadBitmapImage(QIODevice *f ,ImageBuffer *Buff[] ,int LayerNumb);
bool	LoadBitmapImage(QIODevice *f ,QImage &Img);

bool	ButtonLoadBmpJpg::LoadFile(QString &FileName ,bool iToMaster)
{
	LoadedFileName=FileName;
	int	Page=(LoadedPage<GetPageNumb())?LoadedPage:GetPageNumb()-1;
	GUICmdReqLoadBmpJpg	RCmd(GetLayersBase(),sRoot,sName,Page);

	//if(RCmd.Img.load(LoadedFileName)==true){
	//	RCmd.ToMaster=iToMaster;
	//	RCmd.Send(NULL,Page,0);
	//	return true;
	//}
	//else{
		QFile	File(LoadedFileName);
		ImagePointerContainer Images;
		if(iToMaster==true)
			GetLayersBase()->GetPageData(Page)->GetMasterImages(Images);
		else
			GetLayersBase()->GetPageData(Page)->GetTargetImages(Images);
		int	LayerNumb=GetLayerNumb(Page);
		ImageBuffer	*Buff[LayerNumb];
		for(int L=0;L<LayerNumb;L++){
			Buff[L]=Images[L];
		}
		QFileInfo	Info(LoadedFileName);
		QString	Suf=Info.completeSuffix().toUpper();
		if(Suf==/**/"BMP" || Suf==/**/"BITMAP"){
			if(File.open(QIODevice::ReadOnly)==true){
				return LoadBitmapImage(&File,Buff,LayerNumb);
			}
		}
		else 
		if(Suf==/**/"JPG" || Suf==/**/"JPEG"){
			DWORD	t=::GetComputerMiliSec();
			char	NameBuff[1024];
			QString2Char(LoadedFileName ,NameBuff,sizeof(NameBuff));

			FILE	*file=fopen(NameBuff,"rb");
			if(file!=NULL){
				int c = setjmp(err_jmpbuf);
				if (c == 0) {
					bool	Ret=read_jpeg_stream(file,Buff ,min(3,LayerNumb));
					fclose(file);
					DWORD	LoadingMilisec=::GetComputerMiliSec()-t;
					return Ret;
				}
				fclose(file);
			}
		}
		else 
		if(Suf==/**/"PNG"){
			QImage	Img;
			Img.load(LoadedFileName);
			ImageBufferListContainer	BList;
			BList.FromImage(Img,LayerNumb);
			for(int L=0;L<LayerNumb && L<BList.GetCount();L++){
				*Buff[L]=*BList[L];
			}
		}
	//}
	return false;
}

bool	ButtonLoadBmpJpg::LoadFile(QString &FileName ,QImage &Img)
{
	LoadedFileName=FileName;

	if(Img.load(LoadedFileName)==true){
		return true;
	}
	else{
		QFile		File(LoadedFileName);
		QFileInfo	Info(LoadedFileName);
		QString	Suf=Info.completeSuffix().toUpper();
		if(Suf==/**/"BMP" || Suf==/**/"BITMAP"){
			if(File.open(QIODevice::ReadOnly)==true){
				return LoadBitmapImage(&File,Img);
			}
		}
		else 
		if(Suf==/**/"JPG" || Suf==/**/"JPEG"){
			char	NameBuff[256];
			QString2Char(LoadedFileName ,NameBuff,sizeof(NameBuff));

			FILE	*file=fopen(NameBuff,"rb");
			if(file!=NULL){
				int c = setjmp(err_jmpbuf);
				if (c == 0) {
					bool	Ret=read_jpeg_stream(file,Img);
					fclose(file);
					return Ret;
				}
				fclose(file);
			}
		}
	}
	return false;
}

void	ButtonLoadBmpJpg::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonLoadBmpJpg_LS,LID_1)/*"FILE"*/,LangSolver.GetString(ButtonLoadBmpJpg_LS,LID_2)/*"Load bitmap/Jpeg"*/,this);
	p->SetMenuNumber(1001);
	Info.AppendList(p);
}
void	ButtonLoadBmpJpg::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
//==========================================================================================
GUICmdReqLoadBmpJpg::GUICmdReqLoadBmpJpg(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqLoadBmpJpg::Load(QIODevice *f)
{
	if(::Load(f,ToMaster)==false)
		return false;
	Img.load(f,/**/"bmp");
	return true;
}
bool	GUICmdReqLoadBmpJpg::Save(QIODevice *f)
{
	if(::Save(f,ToMaster)==false)
		return false;
	int32	Fmt=(int32)Img.format();
	if(::Save(f,Fmt)==false)
		return false;
	Img.save(f,/**/"bmp");
	return true;
}

void	GUICmdReqLoadBmpJpg::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetPageData(localPage)->CopyFrom(Img,ToMaster);
}
