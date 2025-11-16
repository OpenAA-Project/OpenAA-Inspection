/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\IntegrationShowName\IntegrationShowName.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationShowName.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XIntegrationComm.h"
#include "swap.h"
#include "XDatabaseLoader.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"ShowName";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show master name");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new IntegrationShowName(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QFont";
	Data[0].VariableNameWithRoute=/**/"TitleFont";
	Data[0].Pointer				 =&((IntegrationShowName *)Instance)->TitleFont;
	Data[1].Type				 =/**/"QFont";
	Data[1].VariableNameWithRoute=/**/"CharFont";
	Data[1].Pointer				 =&((IntegrationShowName *)Instance)->CharFont;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"TitleMasterNumber";
	Data[2].Pointer				 =&((IntegrationShowName *)Instance)->TitleMasterNumber;
	Data[2].Translatable		 =true;
	Data[3].Type				 =/**/"QString";
	Data[3].VariableNameWithRoute=/**/"TitleMasterName";
	Data[3].Pointer				 =&((IntegrationShowName *)Instance)->TitleMasterName;
	Data[3].Translatable		 =true;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"TitleRemark";
	Data[4].Pointer				 =&((IntegrationShowName *)Instance)->TitleRemark;
	Data[4].Translatable		 =true;
	Data[5].Type				 =/**/"QColor";
	Data[5].VariableNameWithRoute=/**/"TitleColor";
	Data[5].Pointer				 =&((IntegrationShowName *)Instance)->TitleColor;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationShowName.png")));
}

//==================================================================================================================

IntegrationShowName::IntegrationShowName(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	LabelTitleNumber.setParent(this);
	LabelTitleName	.setParent(this);
	LabelTitleRemark.setParent(this);
	LabelDataNumber	.setParent(this);
	LabelDataName	.setParent(this);
	LabelDataRemark	.setParent(this);
	resize(250,250);

	TitleMasterNumber	=/**/"Master Number";
	TitleMasterName		=/**/"Master Name";
	TitleRemark			=/**/"Remark";

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationShowName::~IntegrationShowName()
{
}

void	IntegrationShowName::Prepare(void)
{
	LabelTitleNumber.setFont(TitleFont);
	LabelTitleName	.setFont(TitleFont);
	LabelDataNumber	.setFont(CharFont);
	LabelDataName	.setFont(CharFont);
	LabelTitleRemark.setFont(TitleFont);
	LabelDataRemark	.setFont(CharFont);

	LabelTitleNumber.setFrameShape(QFrame::Panel);
	LabelTitleName	.setFrameShape(QFrame::Panel);
	LabelDataNumber	.setFrameShape(QFrame::Panel);
	LabelDataName	.setFrameShape(QFrame::Panel);
	LabelTitleRemark.setFrameShape(QFrame::Panel);
	LabelDataRemark	.setFrameShape(QFrame::Panel);

	LabelTitleNumber.setFrameShadow(QFrame::Sunken);
	LabelTitleName	.setFrameShadow(QFrame::Sunken);
	LabelDataNumber	.setFrameShadow(QFrame::Sunken);
	LabelDataName	.setFrameShadow(QFrame::Sunken);
	LabelTitleRemark.setFrameShadow(QFrame::Sunken);
	LabelDataRemark	.setFrameShadow(QFrame::Sunken);

	LabelTitleNumber.setText(TitleMasterNumber);
	LabelTitleName	.setText(TitleMasterName);
	LabelTitleRemark.setText(TitleRemark);
}

void	IntegrationShowName::ResizeAction()
{
	int	RowCount=3;
	QFontInfo	TitleFontInfo	(TitleFont);
	QFontInfo	DataFontInfo	(CharFont);
	int	YLen=max(TitleFontInfo.pixelSize(),DataFontInfo.pixelSize());
	if(height()>(YLen*RowCount+8)){
		YLen=(height()-8)/RowCount;
	}
	YLen+=2;
	QFontMetrics	FontM(TitleFont);
	int	TitleWidth	=max(FontM.boundingRect(TitleMasterNumber).width()
					,max(FontM.boundingRect(TitleMasterName).width(),FontM.boundingRect(TitleRemark	).width()))+6;

	LabelTitleNumber.setGeometry(0,0		,TitleWidth,YLen);
	LabelTitleName	.setGeometry(0,YLen+2	,TitleWidth,YLen);
	LabelTitleRemark.setGeometry(0,YLen*2+4	,TitleWidth,YLen);
	LabelDataNumber	.setGeometry(TitleWidth+2,0			,width()-TitleWidth-2,YLen);
	LabelDataName	.setGeometry(TitleWidth+2,YLen+2	,width()-TitleWidth-2,YLen);
	LabelDataRemark	.setGeometry(TitleWidth+2,YLen*2+2	,width()-TitleWidth-2,YLen);
}

void	IntegrationShowName::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdLoadedMasterData		*CmdLoadedMasterDataVar=dynamic_cast<CmdLoadedMasterData *>(v);
	CmdUpdatedMasterImage	*CmdUpdatedMasterImageVar=dynamic_cast<CmdUpdatedMasterImage *>(v);
	if(CmdLoadedMasterDataVar!=NULL || CmdUpdatedMasterImageVar!=NULL){
		int	RelationCode=GetLayersBase()->GetIntegrationBasePointer()->GetMasterRelationCode();
		QString	RetRelationNumber;
		QString RetRelationName	;
		QString RetRemark		;
		int		RetRelationType	;
		QByteArray	CommonByteArray;
		int32	ThresholdLevelID;
		if(GetLayersBase()->GetDatabaseLoader()->G_GetMasterRelation(GetLayersBase()->GetDatabase() 
										,RelationCode
										,RetRelationNumber
										,RetRelationName
										,RetRemark
										,RetRelationType
										,CommonByteArray
										,ThresholdLevelID)==true){
			LabelDataNumber	.setText(RetRelationNumber);
			LabelDataName	.setText(RetRelationName);
			LabelDataRemark	.setText(RetRemark);
		}
		return;
	}
	CmdShowNameInfo	*CmdShowNameInfoVar=dynamic_cast<CmdShowNameInfo *>(v);
	if(CmdShowNameInfoVar!=NULL){
		LabelDataNumber	.setText(CmdShowNameInfoVar->MasterNumber);
		LabelDataName	.setText(CmdShowNameInfoVar->MasterName);
		LabelDataRemark	.setText(CmdShowNameInfoVar->Remark);
		return;
	}
}
