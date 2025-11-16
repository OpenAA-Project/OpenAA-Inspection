/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XLogo.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XLogo.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include <QTextStream>
#include <QChar>
#include <QWidget>
#include <QLabel>


static	QString CutWord(const QString &LineData,QString &RetBuff)
{
	QString	RData	=LineData.trimmed();
	int	i;
	for(i=0;i<RData.length();i++){
		QChar	c=RData[i];
		if(c==','){
			break;
		}
		RetBuff[i]=c;
	}
	RetBuff=RetBuff.trimmed();
	if(RetBuff[0]=='\"' && RetBuff[RetBuff.length()-1]=='\"'){
		RetBuff=RetBuff.mid(1,RetBuff.length()-2);
	}
	return RData.remove(0,i);
}

bool	LogoLeaf::Analyze(QString &LineData)
{
	LineData=CutWord(LineData,DLLRoot);
	if(LineData[0]!=','){
		return false;
	}
	LineData=LineData.remove(0,1);
	LineData=CutWord(LineData,DLLName);
	if(LineData[0]!=','){
		return false;
	}
	LineData=LineData.remove(0,1);
	LineData=CutWord(LineData,Name);
	if(LineData[0]!=','){
		return false;
	}
	LineData=LineData.remove(0,1);
	LineData=CutWord(LineData,ClassName);
	if(LineData[0]!=','){
		return false;
	}
	QString	XPosStr;
	QString	YPosStr;
	LineData=LineData.remove(0,1);
	LineData=CutWord(LineData,XPosStr);
	if(LineData[0]!=','){
		return false;
	}
	LineData=LineData.remove(0,1);
	LineData=CutWord(LineData,YPosStr);
	if(LineData[0]!=','){
		return false;
	}
	LineData=LineData.remove(0,1);
	LineData=CutWord(LineData,FileName);
	if(FileName.isEmpty()==true){
		return false;
	}
	bool	ok;
	XPos=XPosStr.toInt(&ok);
	if(ok==false){
		return false;
	}
	YPos=YPosStr.toInt(&ok);
	if(ok==false){
		return false;
	}
	return true;
}
void	LogoLeaf::Execute(QWidget *W)
{
	QPixmap		LogoImage;
	if(LogoImage.load(FileName)==false){
		return;
	}
	QLabel	*L=new QLabel(W);
	L->setParent(W);
	L->setGeometry(XPos,YPos,LogoImage.width(),LogoImage.height());
	L->setPixmap(LogoImage);
}

bool	LogoStocker::LoadFromLogoListFile(LayersBase *base)
{
	RemoveAll();
	if(QFile::exists(base->GetParamGlobal()->LogoListFileName)==false){
		return false;
	}
	QFile	File(base->GetParamGlobal()->LogoListFileName);
	if(File.open(QIODevice::ReadOnly)==false){
		return false;
	}
	QTextStream	TextStr(&File);
	while(TextStr.atEnd()==false){
		QString LineData=TextStr.readLine();
		LogoLeaf	*L=new LogoLeaf();
		if(L->Analyze(LineData)==true){
			AppendList(L);
		}
		else{
			delete	L;
		}
	}
	return true;
}


static	QString	PickupClassName(const char *name)
{
	QString	L=name;
	for(int i=0;i<20;i++){
		QString	s=L.section(' ',i,i);
		s=s.trimmed();
		if(s=="class"){
			continue;
		}
		return s;
	}
	return /**/"";
}



void	LogoStocker::ExecuteInGUIForm(GUIFormBase *G ,const QString &dllroot ,const QString &dllname)
{
	for(LogoLeaf *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->DLLRoot==dllroot && L->DLLName==dllname){
			if(L->Name.isEmpty()==false){
				if(G->GetName()==L->Name && L->ClassName.isEmpty()==true){
					L->Execute(G);
				}
			}
			else{
				if(L->ClassName.isEmpty()==true){
					L->Execute(G);
				}
			}
		}
	}
}
void	LogoStocker::ExecuteInQWidget(QWidget *W ,const char *_typename ,const QString &dllroot ,const QString &dllname)
{
	QString	LClassName=PickupClassName(_typename);

	for(LogoLeaf *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->DLLRoot==dllroot && L->DLLName==dllname){
			if(L->Name.isEmpty()==false){
				if(LClassName==L->ClassName){
					QWidget *Wi=W;
					for(;;){
						Wi=Wi->parentWidget();
						GUIFormBase	*G=dynamic_cast<GUIFormBase	*>(Wi);
						if(G!=NULL && G->GetName()==L->Name && G->IsCreatedInGUIDLL()==true){
							L->Execute(W);
							break;
						}
					}
				}
			}
			else{
				if(LClassName==L->ClassName){
					L->Execute(W);
				}
			}
		}
	}
}

