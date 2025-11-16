/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditGUI\EditGUI\propertylist.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef PROPERTYLIST_H
#define PROPERTYLIST_H

#include <QWidget>
#include "XGUI.h"
#include <QItemDelegate>
#include <QStandardItemModel>
#include <QPushButton>
#include <QColor>
#include <QImage>
#include <QPaintEvent>
#include <QStringList>
#include <QVariant>
#include <QModelIndex>
#include "XGUIFormBase.h"
#include "WMultiGrid.h"
#include "XServiceForLayers.h"

namespace Ui {
class PropertyList;
}

class	PropertyList;

class	ColorButton : public QPushButton
{
    Q_OBJECT
public:
    QColor	SColor;

    ColorButton(QWidget *parent = 0);
    ~ColorButton();
    void	setColor(const QColor &c);
protected:
    virtual	void paintEvent ( QPaintEvent * event )	override;
};

class	ImageButton : public QPushButton
{
    Q_OBJECT
public:
    QImage	SImage;
	const	QModelIndex	MIndex;

    ImageButton(const QModelIndex &mindex, PropertyList *p,QWidget *parent = 0);
    ~ImageButton();
    void	setImage(const QImage &c);

signals:
	void	SignalImage(QModelIndex MIndex ,QImage Img);
private slots:
    void ButtonClick();
};

class	StringListButton : public QPushButton
{
    Q_OBJECT
    const QModelIndex   Index;
    PropertyList *ParentRoot;
public:
    QStringList	MList;

    StringListButton(const QModelIndex &index,PropertyList *_ParentRoot,QWidget *parent = 0);
    ~StringListButton();

private slots:
    void ButtonClick();
};

class	StringListDialogList : public WMultiGrid
{
    Q_OBJECT
public:
    StringListDialogList(QWidget *parent = 0);
    virtual	void	ChangeValue(int row ,int col,const QVariant &value);
    virtual	void	GetValue(int row ,int col,QVariant &value);
signals:
    void	Changed();
};

//class	StringListDialog : public QDialog
//{
//    Q_OBJECT
//    StringListDialogList	RGrid;
//public:
//    QStringList	MList;
//    StringListDialog(QWidget *parent,QStringList &mlist);
//    ~StringListDialog(void){}
//    void	SetGrid(void);
//private slots:
//    void	Changed();
//protected:
//    virtual	void resizeEvent ( QResizeEvent * event )	override;
//};

class	TunableListButton : public QPushButton
{
    Q_OBJECT
public:
    QStringList	MList;

    TunableListButton(QWidget *parent = 0);
    ~TunableListButton();

private slots:
    void ButtonClick();
};

class	FileNameButton : public QPushButton
{
    Q_OBJECT
public:
    PropertyList *RootParent;
    int	Row;
    QString	FileName;

    FileNameButton(PropertyList *rootparent ,QWidget *parent,int row);
    ~FileNameButton();

private slots:
    void ButtonClick();
};

class	PathNameButton : public QPushButton
{
    Q_OBJECT
public:
    QString	PathName;

    PathNameButton(QWidget *parent = 0);
    ~PathNameButton();

private slots:
    void ButtonClick();
};

class	FileNamesButton : public QPushButton
{
    Q_OBJECT
public:
    QStringList	FileNames;

    FileNamesButton(QWidget *parent = 0);
    ~FileNamesButton();

private slots:
    void ButtonClick();
};

class PropertyListDelegate : public QItemDelegate
{
    Q_OBJECT
    PropertyList *RootParent;

public:
    PropertyListDelegate(PropertyList *rootparent ,QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                          const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
            const QStyleOptionViewItem &option, const QModelIndex &index) const;

public slots:
    void	SlotClickToDelegate(const QString VName ,const QModelIndex index);
};

class	PropertyListPushButton : public QPushButton
{
    Q_OBJECT
    PropertyList *RootParent;
public:
    StructList	*PointList;

    PropertyListPushButton(QWidget * parent ,PropertyList *rootParent ,StructList	*pointList);

private slots:
    void Click ();
};


class	ByteArrayButton : public QPushButton
{
    Q_OBJECT

    PropertyList	*Parent;
    PropertyListDelegate	*Delegate;
    QString			VariableName;
    QModelIndex		MIndex;
public:
    ByteArrayButton(PropertyList *p,PropertyListDelegate *d,const QModelIndex &Index,const QString &VariableName ,QWidget *parent = 0);
    ~ByteArrayButton(void);

    void	SetQByteArray(const QByteArray &c)	;
    QByteArray	GetQByteArray(void)				;

signals:
    void	SignalClickToDelegate(const QString VName,const QModelIndex index);
private slots:
    void ButtonClick();
};

class PropertyList : public GUIFormBase
{
	friend	class	PropertyListDelegate;
    Q_OBJECT

    GUIItemInstance DLLInstDummy;
    bool	OnShowing;
public:
    explicit PropertyList(LayersBase *Base,QWidget *parent = 0);
    ~PropertyList();

    void	SetDLL(GuiDLLItem *dllItem);
    void	ShowList(const QString &DLLRoot ,const QString &DLLName);
    void	ShowListInside(void);
    void	ShowData(void);
    void	ClearList();
    StructList	*GetStructItem(int LineNo ,int &depthNo);
    StructList	*FindStructItem(const QString &VName);

    GUIItemInstance *DLLInst;
    GUIFormBase		*PutTop;
	virtual	void	Repaint(void) override;
    void	SetData(int Row ,QVariant v);

    GUIItemInstance *GetCurrentDLLInst(void)	{	return DLLInst;		}
	QAbstractItemModel *GetModel(void);
private:
    Ui::PropertyList *ui;

    QStandardItemModel *model;

protected:
    virtual	void resizeEvent ( QResizeEvent * event )	override;
private slots:
    void	ModelDataChanged (const QModelIndex &topleft ,const QModelIndex &bottomright);
	void	SlotImage(QModelIndex MIndex ,QImage Img);

public:
    void	SetStringList(const QStringList &MList,const QModelIndex &Index);
};
extern	PropertyList	*MainProperty;

#endif // PROPERTYLIST_H
