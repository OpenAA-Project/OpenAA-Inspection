#ifndef DFSPROVIDER_H
#define DFSPROVIDER_H

#include <QMainWindow>
#include "ui_DFSProvider.h"
#include "XDFSProvider.h"

class DFSProvider : public QMainWindow
{
	Q_OBJECT

	DFSProviderClass	DFSProviderData;
	DFSClientInProvider	Socket;
public:
	DFSProvider(QString &IPAddress , int Address ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~DFSProvider();

	void	ReqEnumFolders(TreeFolderContainer &FolderData);
	void	ReqEnumFiles(const QString &RelativePath ,FileAttrContainer &FilesData);
	void	ReqSaveFile(FileSaveAttr &SaveAttr,QString &DestFolder,int32 &Priority);
	void	ReqLoadFile(FileLoadAttr &LoadedAttr,QString &DestNetworkFile);
	void	ReqRemoveFile(FileLoadAttr &LoadedAttr);
	bool	ReqAddFolder(AddFolderAttr &AddedAttr);
	bool	ReqRemoveFolder(const QString &RelativeFolder);
	bool	ReqFindFile(const QString &RelativeFolder,const QString &FileName,FileFindAttr &FFindInfo);

private slots:
    void on_pushButtonAddRoute_clicked();
    void on_pushButtonDeleteRoute_clicked();

    void on_tableWidgetRoute_doubleClicked(const QModelIndex &index);

private:
	Ui::DFSProviderClass ui;

	bool	Save(void);
	bool	Load(void);
	void	ShowDFSProviderList(void);

};

#endif // DFSPROVIDER_H
