#include <QTcpSocket>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //CheckPort w;
    //w.show();
    //return a.exec();

	if(argc>=2){
		QString	s(argv[1]);
		bool	ok;
		int	Port=s.toInt(&ok);
		if(ok==false){
			return -1;
		}
		QTcpSocket	LocalSock;

		LocalSock.connectToHost(/**/"127.0.0.1",Port);
		bool	Ret=LocalSock.waitForConnected(2000);
		if(Ret==true){
			return 0;
		}
		return 1;
	}
	return -2;
}
