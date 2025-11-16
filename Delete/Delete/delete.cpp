/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Delete\Delete\delete.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "delete.h"
Delete::Delete(QWidget *parent, Qt::WindowFlags flags)	
	: QWidget(parent, flags)
{
	ui.setupUi(this);
}
void Delete::on_pushButton_clicked()
{
	setFilters();
	ui.pushButton	   ->setEnabled(false);
	ui.pushButtonSource->setEnabled(false);
	DeleteMain(QDir::currentPath());
	exit(0);
}
void Delete::on_pushButtonSource_clicked()
{
	setFilters_Source();
	ui.pushButton	   ->setEnabled(false);
	ui.pushButtonSource->setEnabled(false);
	DeleteMain(QDir::currentPath());
	exit(0);
}
void Delete::setFilters(){
	nameFilters <<"*.ilk"	 <<"*.lib"	  <<"*.obj"			<<"*.tds"	  <<"*.lzh"		<<"*.zip"  <<"*.cpp"	<<"*.~cpp"
				<<"*.~h"	 <<"*.h"	  <<"*.ui"			<<"*.sln"	  <<"*.ncb"		<<"*.suo"  <<"*.qrc"	<<"*.idb"
				<<"*.vcproj" <<"*.user"	  <<"*.icproj"		<<"*.manifest"<<"*.htm"		<<"*.dg"   <<"*.exp"	<<"*.pgm"
				<<"*.sln_old"<<"*.qm"	  <<"*.ts"			<<"*.c"		  <<"*.asm"		<<"*.rc"   <<"*.png"	<<"*.ico"
				<<"*.log"	 <<"*.ts"	  <<"*.hws"			<<"*.tws"	  <<"*.csv"		<<"*.bpr"  <<"*.res"	<<"*.dfm"
				<<"*.hwp"	 <<"*.ddl"	  <<"*.dep"			<<"*.doc"	  <<"*.docx"	<<"*.ppt"  <<"*.aqt"	<<"*.pro"
				<<"*.pri"	 <<"*.lsp"	  <<"*.classpath"	<<"*.class"	  <<"*.project"	<<"*.pdf"  <<"*.bat"	<<"*.cod"
				<<"*.java"	 <<"*.pas"	  <<"*.guess"		<<"*.sub"	  <<"*.sh"		<<"*.icm"  <<"*.mif"	<<"*.mif0"
				<<"*.bmp"	 <<"*.jpg"	  <<"*.ras"			<<"*.am"	  <<"*.in"		<<"*.dsp"  <<"*.m4"		<<"*.spec"
				<<"*.doxygen"<<"*.html"	  <<"*.pro"			<<"*.bak0"	  <<"*.cproject"<<"*.debug"<<"*.Release"<<"*.xslt"
				<<"*.gif"	 <<"*.filters"<<"*.ipch"		<<"*.sdf"	  <<"*.spi"		<<"*.spl"  <<"*.cu"	    <<"*.eap"			
				<<"*.vcxproj"<<"*.xls"	  <<"*.uhg744"		<<"*.db"	  <<"*.tmpl"	<<"*.cache"<<"*.ac"		<<"*.dyn"
				<<"*.pdb"	 <<"*.tlog"	  <<"*.src"			<<"*.pnm"	  <<"*.dsw"	    <<"*.css"  <<"*.txt"    <<"*.epc"
				<<"*.manifest.res"<<"*.lastbuildstate"<<"*.unsuccessfulbuild";
}
void Delete::setFilters_Source(){
	nameFilters <<"*.icproj" <<"*.vcproj"<<"*.vcxproj" <<"*.qrc"	<<"*.cpp" <<"*.h" <<"*.ui" <<"*.png" <<"*.c" <<"*.sln";
}
void Delete::DeleteMain(const QString &NowDirName)	
{
	QDir NowDir (NowDirName);
	if(NowDir.cd(NowDirName)==false){
		return;
	}	
	removeFile(NowDir,NowDirName);
	removeSvn (NowDirName);

	QStringList AllDirFilters("*");
	QStringList ChildDirList = NowDir.entryList ( AllDirFilters, QDir::Dirs | QDir::NoDotAndDotDot, QDir::NoSort );
	QString		ChildDirName;
	for(int i=0;i<ChildDirList.size();i++){
		ChildDirName = NowDirName + QString(QDir::separator()) + ChildDirList.at(i);
		DeleteMain (ChildDirName);
		NowDir.rmdir(ChildDirName);
	}		
}
void Delete::removeFile(QDir &NowDir, const QString &NowDirName){
	QStringList removeFileList=NowDir.entryList (nameFilters, QDir::Files | QDir::Hidden, QDir::NoSort);
	QString FileName;
	QFile file;
	for(int i=0;i<removeFileList.size();i++){
		if(shouldDeleteFile(removeFileList[i])==false){
			continue;	
		}
		FileName=NowDirName+QString(QDir::separator())+removeFileList.at(i);			
		if(QLibrary::isLibrary(FileName)==true){
			continue;
		}
		file.setFileName(FileName);
		file.remove();
	}
}
bool Delete::shouldDeleteFile(const QString &FileName){
	if(FileName.startsWith("Microsoft")==true && FileName.right(8)=="manifest"){
		return false;
	}
	return true;
}
void Delete::removeSvn(const QString &NowDirName){
	QString svnD=NowDirName+QString(QDir::separator())+".svn";				
	removeSvnFile(svnD);
	QDir svndir;
	svndir.rmdir(svnD);
}
void Delete::removeSvnFile(const QString &NowDirName)
{
	QDir Dir (NowDirName);
	if(Dir.cd(NowDirName)==false){
		return;
	}
	QStringList AllFileFilters;
	AllFileFilters<<"*";
	QStringList removeFileList = Dir.entryList ( AllFileFilters, QDir::Files, QDir::NoSort );	
	QString FileName;
	QFile removeFile;
	for(int i=0; i<removeFileList.size(); i++){
		FileName=NowDirName + QString(QDir::separator()) + removeFileList.at(i);
		if(QLibrary::isLibrary(FileName)==true){
			continue;
		}
		removeFile.setFileName(FileName);
		removeFile.setPermissions(FileName,QFile::WriteOther);
		removeFile.remove();
	}
	removeSvnDir(NowDirName);	
}
void Delete::removeSvnDir(const QString &NowDirName)
{
	QDir Dir(NowDirName);
	QStringList AllDirFilters("*");
	QStringList removeDirList=Dir.entryList ( AllDirFilters, QDir::Dirs | QDir::NoDotAndDotDot, QDir::NoSort );
	QString ChildDirName;
	for(int i=0; i<removeDirList.size(); i++){
		ChildDirName = NowDirName + QString(QDir::separator()) + removeDirList.at(i);
		removeSvnFile(ChildDirName);
		Dir.rmdir	 (ChildDirName);
	}
}