/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\XLSProject.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XLSProject.h"
#include "XGeneralFunc.h"

extern	LanguageStocker	LStocker;
LSProjectClass	LSProjectData;

bool	LSSourceFileItem::Save(QIODevice &File)
{
	if(::Save(&File,FileName)==false)
		return false;
	return true;
}
bool	LSSourceFileItem::Load(QIODevice &File)
{
	if(::Load(&File,FileName)==false)
		return false;
	return true;
}

bool	LSUIFileItem::Save(QIODevice &File)
{
	if(::Save(&File,FileName)==false)
		return false;
	return true;
}
bool	LSUIFileItem::Load(QIODevice &File)
{
	if(::Load(&File,FileName)==false)
		return false;
	return true;
}


bool	LSProjectItem::Save(QIODevice &File)
{
	int	Ver=2;

	if(::Save(&File,ProjectItemName)==false)
		return false;
	int	N=SourceFiles.GetNumber()+(Ver<<16);

	if(::Save(&File,N)==false)
		return false;
	for(LSSourceFileItem *c=SourceFiles.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(File)==false)
			return false;
	}
	N=UIFiles.GetNumber();
	if(::Save(&File,N)==false)
		return false;
	for(LSUIFileItem *c=UIFiles.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(File)==false)
			return false;
	}
	if(::Save(&File,ResourceFileName)==false)
		return false;
	if(::Save(&File,CSVFileName)==false)
		return false;
	if(::Save(&File,XLSXFileName)==false)
		return false;

	return true;
}
	
bool	LSProjectItem::Load(QIODevice &File)
{
	int	Ver=1;
	if(::Load(&File,ProjectItemName)==false)
		return false;
	SourceFiles.RemoveAll();
	int	N;
	if(::Load(&File,N)==false)
		return false;

	Ver=N>>16;
	N&=0xFFFF;

	for(int i=0;i<N;i++){
		LSSourceFileItem *c=new LSSourceFileItem();
		if(c->Load(File)==false)
			return false;
		SourceFiles.AppendList(c);
	}
	if(::Load(&File,N)==false)
		return false;
	for(int i=0;i<N;i++){
		LSUIFileItem *c=new LSUIFileItem();
		if(c->Load(File)==false)
			return false;
		UIFiles.AppendList(c);
	}
	if(::Load(&File,ResourceFileName)==false)
		return false;
	if(::Load(&File,CSVFileName)==false)
		return false;
	if(Ver>=2){
		if(::Load(&File,XLSXFileName)==false)
			return false;
	}
	else{
		QFileInfo	iFileInfo(CSVFileName);
		XLSXFileName=iFileInfo.baseName()+/**/".xlsx";
	}
	return true;
}

bool	LSProjectItem::Execute(QString &ErrMsg)
{
	Stocker.Clear();
	Stocker.CopyCodec(&LStocker);
	/*
	if(QFile::exists(ResourceFileName)==true){
		if(Stocker.LoadResource(ResourceFileName)==false){
			ErrMsg="Error : loading resource file";
			return false;
		}
	}
	*/

	/*
	if(QFile::exists(CSVFileName)==true){
		if(QFile::exists(ResourceFileName)==false){
			if(Stocker.LoadCSVFile(CSVFileName)==false){
				ErrMsg="Error : loading CSV file";
				return false;
			}
		}
		else{
			QFileInfo	InfoCSV(CSVFileName);
			QFileInfo	InfoRes(ResourceFileName);
			if(InfoCSV.lastModified() > InfoRes.lastModified()){
				if(Stocker.LoadCSVFile(CSVFileName)==false){
					ErrMsg="Error : loading CSV file";
					return false;
				}
			}
		}
	}
	*/

	QDir	Dir(Parent->XLSXFolder);
	QString	AbsXLSXFilePath;

	if(Dir.isAbsolute ()==false){
		AbsXLSXFilePath=QCoreApplication::applicationDirPath()+GetSeparator()+Parent->XLSXFolder;
	}
	else{
		AbsXLSXFilePath=Parent->XLSXFolder;;
	}


	ForceDirectories(AbsXLSXFilePath);
	QString	XLSXFilePathName=AbsXLSXFilePath+GetSeparator()+XLSXFileName;
	if(QFile::exists(XLSXFilePathName)==true){
		/*
		if(QFile::exists(ResourceFileName)==false){
			if(Stocker.LoadXLSXFile(XLSXFilePathName)==false){
				ErrMsg="Error : loading XLSX file";
				return false;
			}
		}
		else{
			QFileInfo	InfoXLSX(XLSXFilePathName);
			QFileInfo	InfoRes(ResourceFileName);
			if(InfoXLSX.lastModified() > InfoRes.lastModified()){
				if(Stocker.LoadXLSXFile(XLSXFilePathName)==false){
					ErrMsg="Error : loading XLSX file";
					return false;
				}
			}
		}
		*/
		if(Stocker.LoadXLSXFile(XLSXFilePathName)==false){
			ErrMsg="Error : loading XLSX file";
			return false;
		}

	}
	else if(QFile::exists(CSVFileName)==true){
		if(QFile::exists(ResourceFileName)==false){
			if(Stocker.LoadCSVFile(CSVFileName)==false){
				ErrMsg="Error : loading CSV file";
				return false;
			}
		}
		else{
			QFileInfo	InfoCSV(CSVFileName);
			QFileInfo	InfoRes(ResourceFileName);
			if(InfoCSV.lastModified() > InfoRes.lastModified()){
				if(Stocker.LoadCSVFile(CSVFileName)==false){
					ErrMsg="Error : loading CSV file";
					return false;
				}
			}
		}
	}


	Stocker.CopyCodec(&LStocker);
	for(LSUIFileItem *c=UIFiles.GetFirst();c!=NULL;c=c->GetNext()){
		if(Stocker.LoadUIFile(c->FileName)==false){
			ErrMsg="Error : loading UI file(";
			ErrMsg = ErrMsg+c->FileName+QString(")");
			return false;
		}
	}
	for(LSSourceFileItem *c=SourceFiles.GetFirst();c!=NULL;c=c->GetNext()){
		if(Stocker.ReplaceCPPFile(c->FileName,c->FileName,ResourceFileName)==false){
			ErrMsg="Error : loading CPP file(";
			ErrMsg = ErrMsg+c->FileName+QString(")");
			return false;
		}
	}

	if(Stocker.SaveResource(ResourceFileName)==false){
		ErrMsg="Error : saving resource file";
		return false;
	}
	/*
	if(Stocker.SaveCSVFile(CSVFileName)==false){
		ErrMsg="Error : saving CSV file";
		return false;
	}
	*/
	if(Stocker.SaveXLSXFile(XLSXFilePathName)==false){
		ErrMsg="Error : saving CSV file";
		return false;
	}


	QFileInfo	FRInfo(ResourceFileName);
	QString	HeaderFileName=FRInfo.path() + QDir::separator() + FRInfo.baseName() + QString(".h");
	if(Stocker.SaveHeaderFile(HeaderFileName)==false){
		ErrMsg="Error : saving header file";
		return false;
	}

	return true;
}


bool	LSProjectClass::Save(QIODevice &File)
{
	int	Ver=2;
	if(::Save(&File,Ver)==false)
		return false;
	if(::Save(&File,KeywordForLangSolver)==false)
		return false;
	int	N=GetNumber();
	if(::Save(&File,N)==false)
		return false;
	for(LSProjectItem *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(File)==false)
			return false;
	}
	if(::Save(&File,XLSXFolder)==false)
		return false;
	return true;
}
	
bool	LSProjectClass::Load(QIODevice &File)
{
	int	Ver;
	if(::Load(&File,Ver)==false)
		return false;
	if(::Load(&File,KeywordForLangSolver)==false)
		return false;

	RemoveAll();
	int	N;
	if(::Load(&File,N)==false)
		return false;
	for(int i=0;i<N;i++){
		LSProjectItem *c=new LSProjectItem(this,KeywordForLangSolver);
		if(c->Load(File)==false)
			return false;
		AppendList(c);
	}
	SetKeyword(KeywordForLangSolver);

	if(Ver>=2){
		if(::Load(&File,XLSXFolder)==false)
			return false;
	}

	return true;
}

void	LSProjectClass::SetKeyword(QString _KeywordForLangSolver)
{
	for(LSProjectItem *c=GetFirst();c!=NULL;c=c->GetNext()){
		c->Stocker.KeywordForLangSolver=_KeywordForLangSolver;
	}
	KeywordForLangSolver=_KeywordForLangSolver;
}

