/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#ifndef SELECTCOLORSAMPLE_H
#define SELECTCOLORSAMPLE_H

#include <QWidget>
#include "XColorSpace.h"
#include "XServiceForLayers.h"
#include <QTreeWidget>

namespace Ui {
class SelectColorSample;
}

class	SelectColorSample;

class	ColorFolderNode : public QTreeWidgetItem
{
    QString	FolderName;
    int		ParentID;
    int		ColorFolderID;
    int		NumberInFolder;
public:

    //ColorFolderNode(int libFolderID);
    explicit	ColorFolderNode( const QString &_FolderName
                    ,int _ParentID
                    ,int _ColorFolderID
                    ,int _NumberInFolder);

    ColorFolderNode	*SetCurrentColorFolder(int _LibFolderID);
    const QString	GetFolderName(void)		{	return FolderName;		}
    int		GetParentID(void)				{	return ParentID;		}
    int		GetColorFolderID(void)			{	return ColorFolderID;	}
    int		GetNumberInFolder(void)			{	return NumberInFolder;	}

    void	SetFolderName(const QString &s)	{	FolderName=s;		}
    void	SetColorFolderID(int d)			{	ColorFolderID=d;	}
};

class	ColorFolderTreeWidget : public QTreeWidget
{
    SelectColorSample	*TreeParent;
public:

    explicit	ColorFolderTreeWidget(SelectColorSample *treeParent,QWidget *parent=NULL);
    ColorFolderNode	*SetCurrentColorFolder(int ColorFolderID);

    virtual	void mousePressEvent ( QMouseEvent * event )	override;
};

class SelectColorSample : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectColorSample(LayersBase *Base ,QWidget *parent = 0);
    ~SelectColorSample();

    ColorFolderTreeWidget	treeWidget;
    ColorSampleList	CData;
    ColorSampleList EnumData[1000];

    void	ShowList(void);
    QString	SelectedFolderName;
    int		SelectedParentID;
    int		SelectedColorFolderID;
    int		CopiedID;

signals:
    void	SignalSelectCData();
    void	SignalBeforeSave();
    void	SelectColorFolder(int ColorFolderID ,QString FolderName);

private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonSaveNew_clicked();
    void on_pushButtonUpdate_clicked();

    void	on_treeWidget_clicked(const QModelIndex &);
    void	on_treeWidget_itemDoubleClicked(QTreeWidgetItem*,int);
    void	SlotCopyFolder(void);
    void	SlotPasteFolder(void);
private:
    Ui::SelectColorSample *ui;

    virtual	void closeEvent ( QCloseEvent * event ) 	override;

    int		ShowAllNodes(void);
    void	ShowAllNodes(ColorFolderNode *parentNode ,int parentID);
    int		CreateNewFolder(void);
};

#endif // SELECTCOLORSAMPLE_H