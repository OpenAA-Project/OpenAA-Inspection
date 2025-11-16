#ifndef LIBFOLDERFORM_H
#define LIBFOLDERFORM_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QString>
#include "XServiceForLayers.h"

namespace Ui {
class LibFolderForm;
}
class	LayersBase;
class	LibFolderForm;

class	LibFolderNode : public QTreeWidgetItem	//ライブラリのフォルダー表示、選択のクラス
{
    QString	FolderName;
    int		ParentID;
    int		LibFolderID;
    int		NumberInFolder;

public:
    LibFolderNode(const QString &_FolderName
                ,int _ParentID
                ,int _LibFolderID
                ,int _NumberInFolder);

    LibFolderNode	*SetCurrentLibFolder(int _LibFolderID);
    void	SetFolderName(const QString &s)	{	FolderName=s;			}
    const QString	&GetFolderName(void)	{	return FolderName;		}
    int		GetParentID(void)				{	return ParentID;		}
    int		GetLibFolderID(void)			{	return LibFolderID;		}
    void	SetLibFolderID(int id)			{	LibFolderID=id;			}
    int		GetNumberInFolder(void)			{	return NumberInFolder;	}
};

class	LibFolderTreeWidget : public QTreeWidget
{
    LibFolderForm	*TreeParent;
public:

    LibFolderTreeWidget(LibFolderForm *treeParent,QWidget *parent=NULL);
    LibFolderNode	*SetCurrentLibFolder(int LibFolderID);

    virtual	void mousePressEvent ( QMouseEvent * event )    override;
    virtual	void dragEnterEvent(QDragEnterEvent *event)     override;
    virtual	void dragMoveEvent(QDragMoveEvent *event)       override;
    virtual	void dropEvent(QDropEvent *event)               override;
};

class LibFolderForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    LibFolderTreeWidget	treeWidget;
    int			LibType;
public:
    explicit LibFolderForm(int libType ,LayersBase *lbase ,QWidget *parent = 0);
    ~LibFolderForm();

    void	SetNodes(void);

    QString	SelectedFolderName;
    int		SelectedParentID;
    int		SelectedLibFolderID;
    int		CopiedID;

    int		CreateNewFolder(void);
    int		SetLibType(int libType);
    void	SetCurrentLibFolder(int LibFolderID);
    void	Show(void);
    void	Drop(int FolderParentID ,int LibFolderID , QWidget *w);
    void	FitToFrame(QWidget *ParentFrame);

    QTreeWidget *GetTreeWidget(void)    {   return &treeWidget; }

signals:
    void	SelectLibFolder(int LibFolderID ,QString FolderName);
    void	SignalDrop(int FolderParentID ,int LibFolderID , QWidget *w);

private slots:
    void    on_pushButtonUpdate_clicked();
    void	on_treeWidget_clicked(const QModelIndex &);
    void	on_treeWidget_itemDoubleClicked(QTreeWidgetItem*,int);
    void    SlotItemSelectionChanged();
    void    SlotCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void	SlotCopyFolder(void);
    void	SlotPasteFolder(void);

private:
    Ui::LibFolderForm *ui;

    int		ShowAllNodes(void);
    void	ShowAllNodes(LibFolderNode *parentNode ,int parentID);
    virtual	void	resizeEvent ( QResizeEvent * event )	override;
    virtual	void    showEvent(QShowEvent *event)            override;
    bool	AlertNewFolder(void);
};

#endif // LIBFOLDERFORM_H
