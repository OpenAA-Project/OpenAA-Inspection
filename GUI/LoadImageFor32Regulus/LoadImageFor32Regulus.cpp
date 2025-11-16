#include "LoadImageFor32RegulusResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LoadImageFor32Regulus\LoadImageFor32Regulus.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "LoadImageFor32Regulus.h"
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"LoadImageFor32Regulus";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Load 32 bit regulus Image");
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
	return(new LoadImageFor32Regulus(Base,parent));
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
	Data[0].Pointer				 =&((LoadImageFor32Regulus *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((LoadImageFor32Regulus *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((LoadImageFor32Regulus *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((LoadImageFor32Regulus *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/LoadImageFor32Regulus.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
LoadImageFor32Regulus::LoadImageFor32Regulus(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Load PIX Image";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

LoadImageFor32Regulus::~LoadImageFor32Regulus(void)
{
}

void	LoadImageFor32Regulus::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	LoadImageFor32Regulus::ResizeAction()
{
	Button.resize(width(),height());
}

void LoadImageFor32Regulus::SlotClicked (bool checked)
{
	QString	FileName1=GetLayersBase()->LGetOpenFileName (this
										, LangSolver.GetString(LoadImageFor32Regulus_LS,LID_0)/*"Load Master Image file for Page1"*/
										, QString()
										,QString(/**/"ImageFile(*.pix);;AllFile(*.*)")) ;
	if(FileName1.isEmpty()==true)
		return;

	char	buff[256];
    QString2Char(FileName1,buff ,sizeof(buff));    
	FILE    *file=fopen(buff,/**/"rb");
	if(file!=NULL){
		LoadImageToMaster(file);
		fclose(file);
	}
}

bool LoadImageFor32Regulus::LoadImageToMaster(FILE *file)
{
	int32	mMaxScans;
	int32	mDotPerLine;
	int32	mMaxLines;
	int32 ID;
	fread(&ID     ,sizeof(ID     ),1,file);
	if(ID==0xA55AE00E){
		if(fread(&mMaxScans     ,sizeof(mMaxScans),1,file)!=1)
			return false;
		if(fread(&mDotPerLine   ,sizeof(mDotPerLine),1,file)!=1)
			return false;
		if(fread(&mMaxLines     ,sizeof(mMaxLines     ),1,file)!=1)
			return false;
		for(int page=0;page<mMaxScans && page<GetPageNumb();page++){
			ImageBuffer	*Img=&GetLayersBase()->GetPageData(page)->GetLayerData(0)->GetMasterBuff();
			int y;
			for(y=0;y<mMaxLines && y<GetMaxLines(page);y++){
				int Len=min(GetDotPerLine(page),mDotPerLine);
				BYTE    *dp=Img->GetY(y);
				fread(dp,Len,1,file);
				if(mDotPerLine>Len){
					int d=mDotPerLine-Len;
					while(d>0){
						if(Len>d)
							Len=d;
						dp=Img->GetY(0);
						fread(dp,Len,1,file);
						d-=Len;
					}
				}
			}
			for(;y<mMaxLines;y++){
				int Len=min(GetDotPerLine(page),mDotPerLine);
				BYTE    *dp=Img->GetY(0);
				fread(dp,Len,1,file);
				if(mDotPerLine>Len){
					int d=mDotPerLine-Len;
					while(d>0){
						if(Len>d)
							Len=d;
						dp=Img->GetY(0);
						fread(dp,Len,1,file);
						d-=Len;
					}
				}
			}
		}
	}
	else if(ID==0xA55AE00F){
		if(fread(&mMaxScans     ,sizeof(mMaxScans     ),1,file)!=1)
			return false;
		if(fread(&mDotPerLine   ,sizeof(mDotPerLine   ),1,file)!=1)
			return false;
		if(fread(&mMaxLines     ,sizeof(mMaxLines     ),1,file)!=1)
			return false;
		int32 rLayerNumb;
		if(fread(&rLayerNumb    ,sizeof(rLayerNumb          ),1,file)!=1)
			return false;
		for(int r=0;r<rLayerNumb && r<GetLayerNumb(0);r++){
			for(int page=0;page<mMaxScans && page<GetPageNumb();page++){
				int y;
				ImageBuffer	*Img=&GetLayersBase()->GetPageData(page)->GetLayerData(r)->GetMasterBuff();
				for(y=0;y<mMaxLines && y<GetMaxLines(page);y++){
					int Len=min(GetDotPerLine(page),mDotPerLine);
					BYTE    *dp=Img->GetY(y);
					fread(dp,Len,1,file);
					if(mDotPerLine>Len){
						int d=mDotPerLine-Len;
						while(d>0){
							if(Len>d)
								Len=d;
							dp=Img->GetY(0);
							fread(dp,Len,1,file);
							d-=Len;
						}
					}
				}
				for(;y<mMaxLines;y++){
					int Len=min(GetDotPerLine(page),mDotPerLine);
					BYTE    *dp=Img->GetY(0);
					fread(dp,Len,1,file);
					if(mDotPerLine>Len){
						int d=mDotPerLine-Len;
						while(d>0){
							if(Len>d)
								Len=d;
							dp=Img->GetY(0);
							fread(dp,Len,1,file);
							d-=Len;
						}
					}
				}
			}
		}
	}
	else{
		return false;		
        }
	//GetLayersBase()->CloseProcessingForm ();
	BroadcastDirectly(GUIFormBase::_BC_BuildForShow ,GetLayersBase()->GetCurrentInspectIDForDisplay());
	return true;
}
