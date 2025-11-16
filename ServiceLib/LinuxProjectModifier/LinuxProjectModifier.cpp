#include "LinuxProjectModifier.h"
#include <QString>
#include <QFileInfo>
#include <QFileDialog>
#include <QDir>
#include <QDomDocument>
#include <QDomNodeList>
#include <QDomElement>
#include "XGeneralFunc.h"

LinuxProjectModifier::LinuxProjectModifier(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	::SetColumnWidthInTable(ui.tableWidget ,0, 75);
	::SetColumnWidthInTable(ui.tableWidget ,1, 25);

	PathQtLib=/**/"/lib/arm-linux-gnueabihf";
	ui.lineEditQtLib->setText(PathQtLib);

	PathQtInclude=/**/"/usr/include/arm-linux-gnueabihf/qt5";
	ui.lineEditQtInclude->setText(PathQtInclude);
}

void LinuxProjectModifier::on_pushButtonSelectQtLib_clicked()
{
	QString	FolderPath=QFileDialog::getExistingDirectory(nullptr
														, ""
														, QString()
														);
	if(FolderPath.isEmpty()==false){
		ui.lineEditQtLib->setText(FolderPath);
		PathQtLib=FolderPath.replace(/**/"\\",/**/"/");
	}
}

void LinuxProjectModifier::on_pushButtonSelectQtInclude_clicked()
{
	QString	FolderPath=QFileDialog::getExistingDirectory(nullptr
														, ""
														, QString()
														);
	if(FolderPath.isEmpty()==false){
		ui.lineEditQtInclude->setText(FolderPath);
		PathQtInclude=FolderPath.replace(/**/"\\",/**/"/");
	}
}

void LinuxProjectModifier::SearchPathProj(const QString &FolderPath)
{
	QDir	cd(FolderPath);
	QStringList nameFilters;
	nameFilters.append(/**/"*.vcxproj");
	QFileInfoList	FInfo=cd.entryInfoList(nameFilters,QDir::Files | QDir::NoDotAndDotDot);
	for(int i=0;i<FInfo.count();i++){
		QString	BaseName=FInfo[i].baseName();
		ProjectList	*p=new ProjectList();
		p->Path=FolderPath;
		p->BaseName=BaseName;
		ProjectListContainer.AppendList(p);
	}

	QFileInfoList	FolderList=cd.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
	for(int i=0;i<FolderList.count();i++){
		QString	Path=FolderPath + QDir::separator() + FolderList[i].fileName();
		SearchPathProj(Path);
	}
}

void LinuxProjectModifier::on_pushButtonSelectFolder_clicked()
{
	QString	FolderPath=QFileDialog::getExistingDirectory(nullptr
														, ""
														, QString()
														);

	if(FolderPath.isEmpty()==false){
		ProjectListContainer.RemoveAll();
		SearchPathProj(FolderPath);
		int	N=ProjectListContainer.GetCount();
		ui.tableWidget->setRowCount(N);
		int	Row=0;
		for(ProjectList *p= ProjectListContainer.GetFirst();p!=NULL;p=p->GetNext(),Row++){
			::SetDataToTable(ui.tableWidget, 0, Row, p->Path);
			::SetDataToTable(ui.tableWidget, 1, Row, p->BaseName);
		}
	}
}

void LinuxProjectModifier::on_pushButtonExecute_clicked()
{
	PathQtLib		=ui.lineEditQtLib		->text();
	PathQtInclude	=ui.lineEditQtInclude	->text();

	for(ProjectList *p= ProjectListContainer.GetFirst();p!=NULL;p=p->GetNext()){
		QString	VCXProjectFileName	=p->Path 
									+QDir::separator()
									+p->BaseName
									+/**/".vcxproj";
		QString	ProProjectFileName	=p->Path 
									+QDir::separator()
									+p->BaseName
									+/**/".pro";
		QStringList DirList;
		QStringList ModuleList;
		QStringList AddedLib;
		if(LoadVCX(VCXProjectFileName,DirList,ModuleList,AddedLib)==true){
			SavePro(ProProjectFileName,DirList,PathQtLib,PathQtInclude,ModuleList,AddedLib);
		}
	}
}

bool LinuxProjectModifier::LoadVCX(const QString &VCXProjectFileName
									,QStringList &DirList
									,QStringList &ModuleList
									,QStringList &AddedLib)
{
	QFile	File(VCXProjectFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		QDomDocument domDocument;
		bool ok = domDocument.setContent(&File);
		if (ok==true){
			{
				QDomNodeList domList = domDocument.elementsByTagName("ItemDefinitionGroup");
				for(int i=0;i<domList.count();i++){
					QDomNode	Node=domList.at(i);
					QDomElement element = Node.toElement();
					QString s=element.attribute(/**/"Condition");
					if(s.contains(/**/"\'$(Configuration)|$(Platform)\'")==true
					&& s.contains("==")==true
					&& s.contains("\'Release|x64\'")==true){
						QDomNodeList ClCompile=element.elementsByTagName(/**/"ClCompile");
						for(int c=0;c<ClCompile.count();c++){
							QDomNode	CompileNode=ClCompile.at(c);
							QDomElement DElement = Node.toElement();
							QDomNodeList DList=DElement.elementsByTagName(/**/"AdditionalIncludeDirectories");
							if(DList.count()>0){
								QDomNode	DNode=DList.at(0);
								QDomElement HElement = DNode.toElement();
								QString	DStr=HElement.text();
								QStringList	LList=DStr.split(';');
								for(int k=0;k<LList.count();k++){
									QString	h=LList[k];
									if(h.contains(/**/'%')==true){
										continue;
									}
									DirList.append(h.replace(/**/"\\",/**/"/"));
								}
							}
						}
					}
				}
			}
			{
				QDomNodeList domList = domDocument.elementsByTagName("PropertyGroup");
				for(int i=0;i<domList.count();i++){
					QDomNode	Node=domList.at(i);
					QDomElement element = Node.toElement();
					QString s=element.attribute(/**/"Condition");
					if(s.contains(/**/"\'$(Configuration)|$(Platform)\'")==true
					&& s.contains("==")==true
					&& s.contains("\'Release|x64\'")==true){
						QDomNodeList DList=element.elementsByTagName(/**/"QtModules");
						if(DList.count()>0){
							QDomNode	DNode=DList.at(0);
							QDomElement HElement = DNode.toElement();
							QString	DStr=HElement.text();
							ModuleList=DStr.split(';');
						}
					}
				}
			}
			{
				QDomNodeList domList = domDocument.elementsByTagName("ItemGroup");
				for(int i=0;i<domList.count();i++){
					QDomNode	Node=domList.at(i);
					QDomElement element = Node.toElement();
					QDomNodeList DList=element.elementsByTagName(/**/"Library");
					for(int k=0;k<DList.count();k++){
						QDomNode	DNode=DList.at(k);
						QDomElement DElement = DNode.toElement();
						QString s=DElement.attribute(/**/"Include");
						AddedLib.append(s);
					}
				}
			}
			return true;
		}
	}
	return false;
}

bool	LinuxProjectModifier::SavePro(const QString &ProProjectFileName
									,const QStringList &DirList
									,const QString &tPathQtLib
									,const QString &tPathQtInclude
									,const QStringList &ModuleList
									,const QStringList &AddedLib)
{
	QStringList	TxtList;

	{
		QFile	File(ProProjectFileName);
		if(File.open(QIODevice::ReadOnly)==true){
			QTextStream	txt(&File);
			while(txt.atEnd()==false){
				TxtList.append(txt.readLine());
			}
		}
	}
	QStringList	QtLibs=ModuleList;
	//{
	//	for(int LineNo=0;LineNo<TxtList.count();LineNo++){
	//		QString	s=TxtList[LineNo];
	//		if(s.left(2)==/**/"QT"){
	//			QStringList	LList=s.split(/**/"+=");
	//			if(LList.count()>=2){
	//				QtLibs=LList[1].trimmed().split(/**/' ');
	//			}
	//		}
	//	}
	//}

	QFile	File(ProProjectFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		QTextStream	txt(&File);
		for(int LineNo=0;LineNo<TxtList.count();LineNo++){

			if(LineNo==3){ 
				if(QtLibs.count()==0){
					QtLibs.append(/**/"core");
					QtLibs.append(/**/"gui");
					QtLibs.append(/**/"network");
					QtLibs.append(/**/"sql");
					QtLibs.append(/**/"widgets");
				}
				txt<<QString(/**/"QT +=");
				for(int k=0;k<QtLibs.count();k++){
					txt<<QString(/**/" ")+QtLibs[k];
				}
				txt<<QString("\n");
			}
			QString	s=TxtList[LineNo];
			if(s.contains(/**/"INCLUDEPATH")==true){
				for(;;){
					QString L = s.right(1);
					if(L!="\\"){
						break;
					}
					LineNo++;
					s=TxtList[LineNo];
				}
				continue;
			}
			if(s.contains(/**/"DEPENDPATH")==true){
				for(;;){
					QString L = s.right(1);
					if(L!="\\"){
						break;
					}
					LineNo++;
					s=TxtList[LineNo];
				}
				continue;
			}
			if(s.left(2)==/**/"QT"){
				continue;
			}

			if(s.contains(/**/"win32:CONFIG")==true){
				continue;
			}
			if(s.contains(/**/"else:win32:CONFIG")==true){
				continue;
			}
			if(s.contains(/**/"else:unix")==true){
				continue;
			}
			if(s.contains(/**/"unix: LIBS")==true){
				continue;
			}
			if(s.contains(/**/"CONFIG")==true){
				QStringList	LList=s.split(' ');
				for(int i=0;i<LList.count();i++){
					QString	h=LList[i];
					if(h.isEmpty()==false){
						if(h==/**/"debug"){
							h=/**/"release";
						}
						txt<<h;
						if((i+1)!=LList.count()){
							txt<<QString(/**/" ");
						}
					}
				}
				txt<<QString("\n");
				continue;
			}
			if(s.left(4)==/**/"LIBS"){
				if(AddedLib.count()>0){
					bool	SameTxt=false;
					for(int k=0;k<AddedLib.count();k++){
						QString	h=AddedLib[k];
						QFileInfo	FInfo(h);
						QString	path=FInfo.path();
						QString FileName=FInfo.baseName();
						QString	ts;
						if(path.isEmpty()==false){
							ts =QString(/**/"LIBS += -L\"")
								+path
								+QString(/**/"\" -l")
								+FileName;
						}
						if(ts==s){
							SameTxt=true;
							break;
						}
					}
					if(SameTxt==true){
						continue;
					}
				}
			}

			if(s.contains(/**/"include(")==true){
				if(AddedLib.count()>0){
					for(int k=0;k<AddedLib.count();k++){
						QString	h=AddedLib[k];
						QFileInfo	FInfo(h);
						QString	path=FInfo.path();
						QString FileName=FInfo.fileName();
						if(path.isEmpty()==false){
							txt<<QString(/**/"LIBS += -L\"")
								+path
								+QString(/**/"\" -l")
								+FileName
								+QString("\n");
						}
					}
				}

				for(int k=0;k<DirList.count();k++){
					QString	h=DirList[k];
					if(h.isEmpty()==false){
						txt<<QString(/**/"INCLUDEPATH += ")+h
							+QString("\n");
						txt<<QString(/**/"DEPENDPATH += ")+h
							+QString("\n");
					}
				}
				for(int k=0;k<QtLibs.count();k++){
					QString	h=QtLibs[k];
					if(h.isEmpty()==false){
						QString	HHead=h.left(1).toUpper();
						h=HHead+h.mid(1);
						if(h=="Serialport"){
							h="SerialPort";
						}
						if(h=="Multimediawidgets"){
							h="MultimediaWidgets";
						}
						txt<<QString(/**/"unix: LIBS += -L")+tPathQtLib
							+QString(/**/" -lQt5")
							+h
							+QString("\n");
					}
				}
				for(int k=0;k<QtLibs.count();k++){
					QString	h=QtLibs[k];
					if(h.isEmpty()==false){
						QString	HHead=h.left(1).toUpper();
						h=HHead+h.mid(1);
						if(h=="Serialport"){
							h="SerialPort";
						}
						if(h=="Multimediawidgets"){
							h="MultimediaWidgets";
						}
						txt<<QString(/**/"INCLUDEPATH += ")+tPathQtInclude
							+QDir::separator()
							+QString(/**/"Qt")
							+h
							+QString("\n");
					}
				}

				txt<<QString(/**/"INCLUDEPATH += ")+tPathQtInclude
					+QString("\n");
				txt<<QString(/**/"DEPENDPATH += ")+tPathQtInclude
					+QString("\n");

			}

			txt<<s+QString("\n");
		}
		return true;
	}
	return false;
}