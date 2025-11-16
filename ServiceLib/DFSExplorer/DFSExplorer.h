#ifndef DFSEXPLORER_H
#define DFSEXPLORER_H

#include <QMainWindow>
#include "ui_DFSExplorer.h"
#include <QTimer>
#include "XDFSClient.h"

class DFSExplorer : public QMainWindow
{
	Q_OBJECT

	QTimer		TM;
	DFSClient	Socket;
	TreeFolderContainer		Folders;
	TreeFolder				*CurrentFolder;
	FileAttrContainer		Files;
public:
	DFSExplorer(QString &IPAddress , int Address 
				,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~DFSExplorer();

private slots:
    void on_pushButtonAddFolder_clicked();
	void	SlotTimeOut();
	void	SlotShowFolders();
	void	SlotShowFiles();

    void on_treeWidgetFolders_clicked(const QModelIndex &index);
    void on_pushButtonCopyTo_clicked();
    void on_pushButtonCopyFrom_clicked();
    void on_pushButtonRemove_clicked();
    void on_pushButtonRemoveFolder_clicked();

private:
	Ui::DFSExplorerClass ui;

	void	ShowFolder(void);
	void	SetSubFolder(QTreeWidgetItem *Parent ,TreeFolder *F);
	void	ShowFiles(void);
};

#endif // DFSEXPLORER_H
