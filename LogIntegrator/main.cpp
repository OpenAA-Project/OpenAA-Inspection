#include <QtCore/QCoreApplication>
#include "LogIntegratorlib.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QString Path1 = "D:/";	//HDDのパス1台目
	QString Path2 = "";		//HDDのパス2台目
	QString OutPath = "";	//ログの出力先フォルダ
	QString SaveDate = "";	//保存する日時？
	QString LotNo = "";		//ロット番号
	QString BaseNo = "";	//基板番号
	bool SilentFlg = false;	//？

	for( int i=1; i<argc; i++ ) {
		if ( *argv[i] == 'P' || *argv[i] == 'p' ) {
			char *fp = argv[i]+1;
			Path1 = QString(fp);
		}
		if ( *argv[i] == 'Q' || *argv[i] == 'q' ) {
			char *fp = argv[i]+1;
			Path2 = QString(fp);
		}
		if ( *argv[i] == 'O' || *argv[i] == 'o' ) {
			char *fp = argv[i]+1;
			OutPath = QString(fp);
		}
		if ( *argv[i] == 'D' || *argv[i] == 'd' ) {
			char *fp = argv[i]+1;
			SaveDate = QString(fp);
		}
		if ( *argv[i] == 'L' || *argv[i] == 'l' ) {
			char *fp = argv[i]+1;
			LotNo = QString(fp);
		}
		if ( *argv[i] == 'B' || *argv[i] == 'b' ) {
			char *fp = argv[i]+1;
			BaseNo = QString(fp);
		}
		if ( *argv[i] == 'S' || *argv[i] == 's' ) {
			SilentFlg = true;
		}
	}

	if ( Path1 == "" ) {
		return 1;
	}
	if ( OutPath == "" ) {
		OutPath = Path1;
	}
	clsLogIntegratorLib obj;
	obj.setPath1(Path1);
	obj.setPath2(Path2);
	obj.setOutPath(OutPath);
	obj.setSaveDate(SaveDate);
	obj.setLotNo(LotNo);
	obj.setBaseNo(BaseNo);
	if ( SaveDate != "" ) {
		if ( obj.makeLogIntegrate() == false ) {
			return 2;
		}
	} else if ( LotNo != "" ) {
		if ( obj.makeLogIntegrateSearch() == false ) {
			return 2;
		}
	} else {
		return 0;
	}

	if ( obj.outLog() == false ) {
		return 3;	//this application cannot find the path
	}

	//if ( obj.errChk() == false ) {
		obj.showErrDialog();
		a.exec();
	//}
	return 0;
}

//マッチングしたかどうかを毎回表示する