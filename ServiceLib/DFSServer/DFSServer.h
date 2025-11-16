#ifndef DFSSERVER_H
#define DFSSERVER_H

#include <QMainWindow>
#include "ui_DFSServer.h"
#include "XDFSServer.h"
#include "XDFSSocket.h"


class DFSServer : public QMainWindow
{
	Q_OBJECT

	DFSServerToProvider	ServerProvider[16];
	DFSServerToClient	ServerClient[16];
public:
	DFSServer(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~DFSServer();

	void	ReqEnumFolders(TreeFolderContainer &FolderData);
	void	ReqEnumFiles(QByteArray &RelativePathArray,FileAttrContainer &FileNames);
	bool	ReqFolderToSaveFile(QByteArray &data,QString &DestFolder);
	bool	ReqFileToLoad(QByteArray &data,QString &DestNetworkFile);
	void	ReqRemoveFile(QByteArray &data);
	void	ReqMakeFolder(QByteArray &data);
	void	ReqRemoveFolder(QByteArray &data);
	bool	ReqFindFile(QByteArray &data,FileFindAttr &FileInfo);

	void	ShowClient(void);
	void	ShowProvider(void);

	void	RemoveProvider	(DFSClientSocketInProvider *s);
	void	RemoveClient	(DFSClientSocketInServer *s);
private slots:

private:
	Ui::DFSServerClass ui;
};

#endif // DFSSERVER_H
