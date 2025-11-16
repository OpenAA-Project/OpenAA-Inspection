#include "CopyAndExecute.h"
#include <QApplication>
#include <QMessageBox>
#include <QProcess>
#include "Regulus64System.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CopyAndExecute w;
	w.show();
	QString	SourcePath;
	QString	Executer;
	QStringList	ExeParams;

	for(int i=1;i<argc;i++){
		if(*argv[i]=='S'){
			SourcePath=QString(argv[i]+1);
		}
		if(*argv[i]=='E'){
			Executer=QString(argv[i]+1);
			for(i++;i<argc;i++){
				ExeParams.append(argv[i]);
			}
			break;
		}
	}
	if(Executer.isEmpty()==true){
		QMessageBox::warning(NULL,"Error","No executer(*.exe)");
		return 1;
	}

	w.Initial(SourcePath);
	w.DeleteFiles(/**/"Algorithm\\*.dll");
	w.CopyFiles(/**/"Algorithm\\*.dll",DefAlgorithmPath);
	w.DeleteFiles(/**/"GUI\\*.dll");
	w.CopyFiles(/**/"GUI\\*.dll",DefGUIPath);
	w.DeleteFiles(/**/"Filter\\*.dll");
	w.CopyFiles(/**/"Filter\\*.dll","Filter");
	w.DeleteFiles(/**/"PluginDLL\\*.dll");
	w.CopyFiles(/**/"PluginDLL\\*.dll",DefPluginDLLPath);
	w.DeleteFiles(/**/"ResultAnalizer\\*.dll");
	w.CopyFiles(/**/"ResultAnalizer\\*.dll","ResultAnalizer");
	w.CopyFiles(/**/"*.dll","");
	w.CopyFiles(/**/"*.exe","");

	w.close();
	//a.exec();

	QProcess::startDetached (Executer,ExeParams);

	return 0;
}
