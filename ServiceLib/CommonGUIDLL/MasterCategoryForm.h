/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\MasterCategoryForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef MASTERCATEGORYFORM_H
#define MASTERCATEGORYFORM_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "XServiceForLayers.h"

namespace Ui {
class MasterCategoryForm;
}
class	LayersBase;

class	CategoryNode : public QTreeWidgetItem
{
    QString	FolderName;
    int		ParentID;
    int		CategoryID;
    QString	Remark;
public:
    //CategoryNode(int categoryID);
    CategoryNode(const QString &_FolderName
                ,int _ParentID
                ,int _CategoryID
                ,const QString &_Remark);

    const QString	&GetFolderName(void)		{	return FolderName;	}
    int				GetParentID(void)			{	return ParentID;	}
    int				GetCategoryID(void)			{	return CategoryID;	}
    const QString	&GetRemark(void)			{	return Remark;		}

    void	SetFolderName(const QString	&s)		{	FolderName=s;	}
    void	SetRemark(const QString	&s)			{	Remark=s;		}
    void	SetCategoryID(int d)				{	CategoryID=d;	}
};

class MasterCategoryForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit MasterCategoryForm(LayersBase *lbase ,QWidget *parent = 0);
    ~MasterCategoryForm();

    void	SetNodes(void);

    QString	SelectedFolderName;
    int		SelectedParentID;
    int		SelectedCategoryID;
    QString	SelectedRemark;
    int		CreateNewFolder(void);
    int		ShowAllNodes(void);

signals:
	void	SelectCategory(int CategoryID ,QString FolderName ,QString Remark);
private slots:
    void on_pushButtonUpdateButton_clicked();
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_pushButton_clicked();
    void TreeClicked(const QModelIndex & index);

private:
    Ui::MasterCategoryForm *ui;
    virtual	void closeEvent ( QCloseEvent * event ) 	override;
    void	ShowAllNodes(CategoryNode *parentNode ,int parentID);
};

#endif // MASTERCATEGORYFORM_H
