/*
#ifdef _SDEBUG
#define	NOMINMAX
#include <Windows.h>
#include "XTypeDef.h"
#include "LeakChecker.h"
#pragma comment(lib, "LeakChecker")
#endif
*/

#include "XMLServerV3.h"
#include <QApplication>
#include "XShowVersion.h"
#include "XDataInLayer.h"
//#include <chkp.h>

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

int main(int argc, char *argv[])
{
#ifdef _SDEBUG
	//LeakCheckerStart();
#endif
		
	//__chkp_report_control(__CHKP_REPORT_TRACE_LOG, 0);
	//__chkp_report_control(__CHKP_REPORT_TRACE_BPT, 0);

	if(CheckExeVersion(argc, argv)==false)
		return 1;
	QString	AbsPath;
	QString	UserPath;
 	for(int i=1;i<argc;i++){
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if((*argv[i]=='Q' || *argv[i]=='q') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			UserPath	=fp;
		}
	}

	QApplication a(argc, argv);
	XMLServerV3 w(UserPath);
	w.show();
	return a.exec();
}
