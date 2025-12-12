#include "CheckBoard.h"
#include <QtWidgets/QApplication>

/*
    CheckBoard BoardName [Parameters]

	Parameters: E       Check existence of Board
                X1      Check Board Link width ,should be x1
                X4      Check Board Link width ,should be x4
                X8      Check Board Link width ,should be x8
                X16     Check Board Link width ,should be x16
				Wxx	    Waiting time in seconds before checking Board existence ,default is 10 seconds
*/


int main(int argc, char *argv[])
{
    QString BoardName;
	bool    CheckExistence = false;
	int	    LinkWidth = 0;
    int     WaitingSec=10;

    for(int i=0;i<argc;i++){
        QString Param=QString::fromLocal8Bit(argv[i]);
        if(i==1){
            BoardName=Param;
        }
        else if(Param.compare("E",Qt::CaseInsensitive)==0){
            CheckExistence=true;
        }
        else if(Param.compare("X1",Qt::CaseInsensitive)==0){
            LinkWidth=1;
        }
        else if(Param.compare("X4",Qt::CaseInsensitive)==0){
            LinkWidth=4;
        }
        else if(Param.compare("X8",Qt::CaseInsensitive)==0){
            LinkWidth=8;
        }
        else if(Param.compare("X16",Qt::CaseInsensitive)==0){
            LinkWidth=16;
        }
	}

    QApplication app(argc, argv);
    CheckBoard window(BoardName,CheckExistence,LinkWidth,WaitingSec);
    window.show();
    return app.exec();
}
