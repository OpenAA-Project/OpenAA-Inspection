#include "ProjectPropertyManager.h"
#include <QApplication>
#include "XShowVersion.h"
#include <QDomDocument>
#include <QFile>

bool	Test(void)
{
	QString	FileName="C:/Regulus64v3/ServiceLib/CommonGUIDLL/CommonGUIDLL.vcxproj";
	QFile	ProjectFile(FileName);
	if(ProjectFile.open(QFile::ReadOnly | QFile::Text)==false)
		return false;
	QString	ErrorMsg;
	QDomDocument	ProjectData;
	if(ProjectData.setContent(&ProjectFile,&ErrorMsg)==false)
		return false;
	return true;
}


int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	//Test();

	QApplication a(argc, argv);
	ProjectPropertyManager w;
	w.show();
	return a.exec();
}
