#include "SaveMasterImageInInspectionResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SaveMasterImageInInspection\SaveMasterImageInInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "SaveMasterImageInInspection.h"
#include "XDLLOnly.h"
#include "XForWindows.h"
#include <QMessageBox>
#include "XDataInLayer.h"
#include "XMainSchemeMemory.h"
#include <omp.h>
#include "XEntryPoint.h"

static	const	char	*sRoot=/**/"Other";
static	const	char	*sName=/**/"SaveMasterImageInInspection";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Save MasterImage in Inspection");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqImageInInspection(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new SaveMasterImageInInspection(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"double";
	Data[0].VariableNameWithRoute=/**/"ZoomRate";
	Data[0].Pointer				 =&((SaveMasterImageInInspection *)Instance)->ZoomRate;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SaveMasterImageInInspection.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
SaveMasterImageInInspection::SaveMasterImageInInspection(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
}

SaveMasterImageInInspection::~SaveMasterImageInInspection(void)
{
}
void	SaveMasterImageInInspection::Prepare(void)
{

}
void	SaveMasterImageInInspection::ShowInPlayer(int64 shownInspectionID)
{
	if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==true){
		QStringList	ImagePathes=GetParamGlobal()->ImageFilePath.split(QChar(';'));
		QString		ImagePath;
		if(ImagePathes.count()>0){
			ImagePath=ImagePathes[0];
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdReqImageInInspection	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
				RCmd.ZoomRate	=ZoomRate;
				RCmd.MasterCode	=GetLayersBase()->GetMasterCode();
				RCmd.MachineID	=GetLayersBase()->GetMachineID();
				RCmd.ImagePath	=ImagePath;
				if(RCmd.MasterCode>=0 && RCmd.MachineID>=0){
					RCmd.Send(NULL,GlobalPage,0);
				}
			}
		}
	}
}

//=================================================================
GUICmdReqImageInInspection::GUICmdReqImageInInspection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqImageInInspection::Load(QIODevice *f)
{
	if(::Load(f,ZoomRate)==false)
		return false;
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,MachineID)==false)
		return false;
	if(::Load(f,ImagePath)==false)
		return false;
	return true;
}
	
bool	GUICmdReqImageInInspection::Save(QIODevice *f)
{
	if(::Save(f,ZoomRate)==false)
		return false;
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,MachineID)==false)
		return false;
	if(::Save(f,ImagePath)==false)
		return false;
	return true;
}

void	GUICmdReqImageInInspection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);

	DataInPage	*Pd=GetLayersBase()->GetPageData(localPage);
	QString	FileName=Pd->CreateMasterImageFileName(MasterCode ,MachineID ,ImagePath,0,0);
	if(FileName.isEmpty()==false){
		int	XLen=Pd->GetDotPerLine()*ZoomRate;
		int	YLen=Pd->GetMaxLines()*ZoomRate;

		QFileInfo	FInfo(FileName);

		//if(FInfo.size()<XLen*YLen){
			QFile	File(FileName);
			if(File.open(QIODevice::WriteOnly)==true){
				for(int LNumb=0;LNumb<GetLayerNumb(localPage);LNumb++){
					DataInLayer	*Ly=Pd->GetLayerData(LNumb);
					ImageBuffer	Img(0,XLen,YLen);
					ImageBuffer	*SBuff;
					if(Ly->GetMasterBuff().IsNull()==false)
						SBuff=&Ly->GetMasterBuff();
					else if(Ly->GetTargetBuff().IsNull()==false)
						SBuff=&Ly->GetTargetBuff();
					else
						break;
					double	Z=1.0/ZoomRate;
				
					#pragma omp parallel
					{
						#pragma omp for
						for(int y=0;y<YLen;y++){
							BYTE	*s=SBuff->GetY(y*Z);
							BYTE	*d=Img.GetY(y);
							double	Xz=0.0;
							for(int x=0;x<XLen;x++,Xz+=Z){
								d[x]=s[(int)Xz];
							}
						}
					}
					if(Img.Save(&File)==false){
						return;
					}
					ImageBuffer	Dummy;
					if(Dummy.Save(&File)==false){
						return;
					}
					if(Dummy.Save(&File)==false){
						return;
					}
				}
				bool	AllocBit;
				if(GetParamGlobal()->AllocBitBuffer==true){
					AllocBit=true;
					if(::Save(&File,AllocBit)==false)
						return;

					for(int LNumb=0;LNumb<GetLayerNumb(localPage);LNumb++){
						DataInLayer	*L=Pd->GetLayerData(LNumb);
						if(L->GetBitBuff().IsChanged()==true){
							if(GetParamGlobal()->NoLoadSaveMasterImage==false){
								if(L->GetBitBuff().Save(&File)==false){
									return;
								}
							}
						}
					}
				}
				else{
					AllocBit=false;
					if(::Save(&File,AllocBit)==false)
						return;
				}
			}
		//}
	}
}
