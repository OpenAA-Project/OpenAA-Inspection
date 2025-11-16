#if	!defined(XDFSClient_H)
#define	XDFSClient_H

#include "XDFSSocket.h"
#include "XDFS.h"

class	DFSClient: public DFSSocket
{
	Q_OBJECT

public:
	TreeFolderContainer		Folders;
	FileAttrContainer		FileNames;
	QString					DestNetwordFolder;
	QString					DestNetworkFile;
	FileFindAttr			CurrentInfo;

	DFSClient(QObject *parent ,const QString &IPAddress,int PortNumber);

signals:
	void	SignalShowFolders();
	void	SignalShowFiles();

protected:
	virtual	void	Received(int cmd ,QByteArray &data);
};



#endif