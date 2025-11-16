/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\WMultiGrid.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(WMULTIGRID_H)
#define	WMULTIGRID_H

#include <QTableView>
#include <QVariant>
#include <QItemDelegate>
#include <QPushButton>

class	WMultiGrid;
class WMultiGridDelegate : public QItemDelegate
{
    Q_OBJECT
	WMultiGrid *RootParent;

public:
	explicit	WMultiGridDelegate(WMultiGrid *rootparent ,QObject *parent = 0);

private:
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
                          const QModelIndex &index) const;

	void updateEditorGeometry(QWidget *editor,
            const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class	WMultiGridPushButton : public QPushButton
{
    Q_OBJECT
	
	int	Row,Col;
public:
	explicit	WMultiGridPushButton(int row ,int col ,QWidget * parent = 0);
	~WMultiGridPushButton(void);
public slots:
	void SlotClicked ();

signals:
	void ClickedXY( int row ,int col);
};


class	WMultiGrid : public QTableView
{
	friend class WMultiGridDelegate;
    Q_OBJECT

public:
	explicit	WMultiGrid(QWidget * parent=0);
	~WMultiGrid();

	void	SetRowCount(int n);
	void	SetColumnCount(int n);
	void	SetRowHeight(int h);
	void	InitialGrid(void);
	void	ShowGrid(void);

	int		GetRowCount(void)	const	{	return RowCount;	}
	void	AppendRow(void);
	void	RemoveLine(int row);

	void	SetTopHeader(int column, const QString &title);
	void	SetLeftHeader(int row, const QString &title);

	enum	CellType{
			_CType_Label
			,_CType_LineEdit
			,_CType_SpinBox
			,_CType_CheckBox
			,_CType_ComboBox
			,_CType_PushButton
			,_CType_Special
	};

	struct	CellData{
		QVariant		Value;
		CellType		CType;
		int				MaxValue;
		int				MinValue;
		QStringList		CBoxList;
		Qt::Alignment	Alignment;

		CellData(void);
		CellData	&operator=(const CellData &src);
	};
private:
	int			RowCount;
	int			ColumnCount;
	CellData	**Data;

signals:
	void	ChangedValue();
	void	SignalClickedXYButton( int row ,int col);

protected:

	virtual	void	ChangeValue(int row ,int col,const QVariant &value)=0;
	virtual	void	GetValue(int row ,int col,QVariant &value)=0;
	virtual	QVariant	OpenDialogSpecial(int row ,int col);
public:
	CellData	*GetData(int row ,int col){	return(&Data[row][col]);	}
	
	int	GetSelectedRow();

private slots:
	virtual	void	selectRowX(int row);
	void SlotClickedXYButton( int row ,int col);

public slots:
	void	SlotTextChanged ( const QString &);
	void	SlotValueChanged (int i);
};



#endif