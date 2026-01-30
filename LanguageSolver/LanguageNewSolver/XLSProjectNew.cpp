/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



#include "XLSProjectNew.h"
#include "XGeneralFunc.h"
#include "XLanguageNewSolver.h"

bool	LSSourceFileItem::Save(QIODevice *File)
{
	if(::Save(File,FileName)==false)
		return false;
	return true;
}
bool	LSSourceFileItem::Load(QIODevice *File)
{
	if(::Load(File,FileName)==false)
		return false;
	return true;
}

bool	LSUIFileItem::Save(QIODevice *File)
{
	if(::Save(File,FileName)==false)
		return false;
	return true;
}
bool	LSUIFileItem::Load(QIODevice *File)
{
	if(::Load(File,FileName)==false)
		return false;
	return true;
}


bool	LSProjectItem::Save(QIODevice *File)
{
	int	Ver=3;

	if(::Save(File,Ver)==false)
		return false;

	if(::Save(File,ProjectItemName)==false)
		return false;
	if(::Save(File,ReferenceFolder)==false)
		return false;
	if(SourceFiles.Save(File)==false)
		return false;
	if(UIFiles.Save(File)==false)
		return false;

	if(::Save(File,ResourceFileName)==false)
		return false;
	if(::Save(File,XLSXFileName)==false)
		return false;

	return true;
}
	
bool	LSProjectItem::Load(QIODevice *File)
{
	int	Ver;

	if(::Load(File,Ver)==false)
		return false;

	if(::Load(File,ProjectItemName)==false)
		return false;
	if(::Load(File,ReferenceFolder)==false)
		return false;
	if(SourceFiles.Load(File)==false)
		return false;
	if(UIFiles.Load(File)==false)
		return false;

	if(::Load(File,ResourceFileName)==false)
		return false;
	if(::Load(File,XLSXFileName)==false)
		return false;

	return true;
}

int	LSProjectItem::Compare(LSProjectItem &src)
{
	if(ProjectItemName<src.ProjectItemName)
		return -1;
	if(ProjectItemName>src.ProjectItemName)
		return 1;
	return 0;
}

bool	LSProjectItem::Execute(LanguageStocker &Stocker ,LanguagePack &LangPack ,QString &ErrMsg)
{
	QDir	Dir(Parent->XLSXFolder);
	QString	AbsXLSXFilePath;

	if(Dir.isAbsolute ()==false){
		AbsXLSXFilePath=QCoreApplication::applicationDirPath()+GetSeparator()+Parent->XLSXFolder;
	}
	else{
		AbsXLSXFilePath=Parent->XLSXFolder;
	}

	ForceDirectories(AbsXLSXFilePath);
	QString	XLSXFilePathName=AbsXLSXFilePath+GetSeparator()+XLSXFileName;
	if(QFile::exists(XLSXFilePathName)==true){
		if(Stocker.LoadXLSXFile(XLSXFilePathName)==false){
			ErrMsg=QString("Error : loading XLSX file : ")+XLSXFilePathName;
			return false;
		}
	}

	for(LSUIFileItem *c=UIFiles.GetFirst();c!=NULL;c=c->GetNext()){
		if(Stocker.LoadUIFile(c->FileName)==false){
			ErrMsg="Error : loading UI file(";
			ErrMsg = ErrMsg+c->FileName+QString(")");
			return false;
		}
	}
	for(LSSourceFileItem *c=SourceFiles.GetFirst();c!=NULL;c=c->GetNext()){
		if(Stocker.ScanLoadCPPFile(LangPack,c->FileName)==false){
			ErrMsg="Error : scanning CPP file(";
			ErrMsg = ErrMsg+c->FileName+QString(")");
			return false;
		}
	}
	for(LSSourceFileItem *c=SourceFiles.GetFirst();c!=NULL;c=c->GetNext()){
		if(Stocker.ReplaceCPPFile(LangPack,c->FileName,c->FileName,ResourceFileName)==false){
			ErrMsg="Error : loading CPP file(";
			ErrMsg = ErrMsg+c->FileName+QString(")");
			return false;
		}
	}
	QFileInfo	FRInfo(ResourceFileName);
	QString	HeaderFileName=FRInfo.path() + QDir::separator() + FRInfo.baseName() + QString(".h");

	if(QFile::exists(HeaderFileName)==true){
		if(Stocker.LoadHeaderFile(HeaderFileName)==false){
			ErrMsg=QString("Error : saving header file : ")+HeaderFileName;
			return false;
		}
	}
	Stocker.RemoveUnusedHeader();

	Stocker.MakeHeaderDefinition();

	Stocker.ReNumberHeader();

	if(Stocker.SaveResource(ResourceFileName)==false){
		ErrMsg=QString("Error : saving resource file : ")+ResourceFileName;
		return false;
	}

	if(Stocker.SaveXLSXFile(XLSXFilePathName,LangPack)==false){
		ErrMsg=QString("Error : saving XLSX file : ") + XLSXFilePathName;
		return false;
	}

	if(Stocker.SaveHeaderFile(HeaderFileName)==false){
		ErrMsg=QString("Error : saving header file :") +HeaderFileName;
		return false;
	}
	
	return true;
}

//=============================================================
void	LSProjectClass::Clear(void)
{
	RemoveAll();
	KeywordForLangSolver="LangSolver";
	XLSXFolder			="";
	FileName			="";
}

bool	LSProjectClass::Save(QIODevice *f)
{
	int	Ver=3;
	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,KeywordForLangSolver)==false)
		return false;
	if(::Save(f,XLSXFolder)==false)
		return false;
	if(NPListPackSaveLoad<LSProjectItem>::Save(f)==false)
		return false;
	return true;
}
	
bool	LSProjectClass::Load(QIODevice *f)
{
	int	Ver;
	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,KeywordForLangSolver)==false)
		return false;
	if(::Load(f,XLSXFolder)==false)
		return false;

	if(NPListPackSaveLoad<LSProjectItem>::Load(f)==false)
		return false;

	return true;
}

int		LSProjectClass::SearchRow(const QString &ProjName)
{
	int	Row=0;
	for(LSProjectItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ProjectItemName==ProjName){
			return Row;
		}
		Row++;
	}
	return -1;
}