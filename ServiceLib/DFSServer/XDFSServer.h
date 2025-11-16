#if	!defined(XDFSServer_h)
#define	XDFSServer_h

#include "XTypeDef.h"
#include <QBuffer>
#include <QMutex>
#include <QObject>
#include "NList.h"
#include <QTcpServer>
#include "XDFSSocket.h"
#include "XDFS.h"


class DFSServer;

class	DFSServerToProvider : public QTcpServer
{
	Q_OBJECT

	DFSServer	*Parent;
public:
	NPListPack<DFSSocket>	Client;

	DFSServerToProvider(void);
	void	SetParent(DFSServer *parent);

	void	SendEnumFolders(void);
	void	GatherEnumFolders(TreeFolderContainer &FolderData);

	void	SendEnumFiles(QByteArray &RelativePathArray);
	void	GatherEnumFiles(FileAttrContainer &FilesData);

	void	SendFolderToSaveFile(QByteArray &SaveAttr);
	void	GatherFolderToSaveFile(QString &DestFolder,int32 &Priority);
	void	AllocateFolderToSaveFile(QString &DestFolder);

	void	SendFileToLoad(QByteArray &LoadedAttr);
	void	GatherFileToLoad(QString &DestNetworkFile);

	void	ReqRemoveFile(QByteArray &data);

	void	ReqMakeFolder(QByteArray &data);
	void	ReqRemoveFolder(QByteArray &data);

	void	SendFindFile(QByteArray &FileAttr);
	void	GatherFindFile(FileFindAttr &FileInfo);

protected slots:
	void SlotNewConnection ();
};

class	DFSServerToClient : public QTcpServer
{
	Q_OBJECT

	DFSServer	*Parent;
public:
	NPListPack<DFSSocket>	Client;

	DFSServerToClient(void);
	void	SetParent(DFSServer *parent);
protected slots:
	void SlotNewConnection ();
};

//-------------------------------------------------------

class	DFSClientSocketInProvider : public DFSSocket
{
	DFSServer	*Parent;

public:
	TreeFolderContainer		Folders;
	FileAttrContainer		FilesData;
	QString					DestFolder;
	int32					DestPriority;
	QString					DestNetworkFile;
	FileFindAttr			FFindInfo;

	DFSClientSocketInProvider(DFSServer *parent ,QTcpSocket *sv);

protected:
	virtual	void	Received(int cmd ,QByteArray &data);
	virtual	void	SlotDisconnected();
};

//-------------------------------------------------------

class	DFSClientSocketInServer : public DFSSocket
{
	DFSServer	*Parent;
public:
	DFSClientSocketInServer(DFSServer *parent ,QTcpSocket *sv);

protected:
	virtual	void	Received(int cmd ,QByteArray &data);
	virtual	void	SlotDisconnected();
};


#endif