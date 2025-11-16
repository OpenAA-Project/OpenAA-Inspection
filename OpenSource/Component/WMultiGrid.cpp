/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\WMultiGrid.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "WMultiGrid.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QStandardItemModel>
#include <QAbstractItemModel>


WMultiGridPushButton::WMultiGridPushButton(int row ,int col ,QWidget * parent)
:QPushButton(parent)
,Row(row),Col(col)
{
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
}
WMultiGridPushButton::~WMultiGridPushButton(void)
{
	disconnect(this,SLOT(SlotClicked()));
}
void WMultiGridPushButton::SlotClicked()
{
	emit	ClickedXY( Row ,Col);
}


WMultiGridDelegate::WMultiGridDelegate(WMultiGrid *rootparent ,QObject *parent)
: QItemDelegate(parent)
{
	RootParent=rootparent;
}

QWidget *WMultiGridDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                              const QModelIndex &MIndex)const
{
	WMultiGrid::CellData	*L=RootParent->GetData(MIndex.row() ,MIndex.column());
	if(L!=NULL){
		if(L->CType==WMultiGrid::_CType_Label){
			QLabel *label =new QLabel(parent);
			return(label);
		}
		else if(L->CType==WMultiGrid::_CType_LineEdit){
			QLineEdit *editor = new QLineEdit(parent);
			editor->installEventFilter(const_cast<WMultiGridDelegate*>(this));
			connect(editor,SIGNAL(textChanged(const QString) ),RootParent,SLOT(SlotTextChanged ( const QString)));
			return editor;
		}
		else if(L->CType==WMultiGrid::_CType_SpinBox){
			QSpinBox *editor = new QSpinBox(parent);
			editor->setMinimum(L->MinValue);
			editor->setMaximum(L->MaxValue);
			editor->installEventFilter(const_cast<WMultiGridDelegate*>(this));
			connect(editor,SIGNAL(valueChanged (int) ),RootParent,SLOT(SlotValueChanged (int i)));
			return editor;
		}
		else if(L->CType==WMultiGrid::_CType_CheckBox){
			QCheckBox *chk =new QCheckBox(parent);
			return(chk);
		}
		else if(L->CType==WMultiGrid::_CType_ComboBox){
			QComboBox	*editor = new QComboBox(parent);
			editor->addItems(L->CBoxList);
			editor->setEditable(false);
			editor->installEventFilter(const_cast<WMultiGridDelegate*>(this));
			return editor;
		}
		else if(L->CType==WMultiGrid::_CType_PushButton){
			WMultiGridPushButton	*btn =new WMultiGridPushButton(MIndex.row(),MIndex.column(),parent);
			btn->setText(L->Value.toString());
			connect(btn,SIGNAL(ClickedXY(int ,int)),RootParent,SLOT(SlotClickedXYButton(int ,int)));
			return(btn);
		}
		else if(L->CType==WMultiGrid::_CType_Special){
			QPushButton	*btn =new QPushButton(parent);
			return(btn);
		}
	}
	return(NULL);
}

void WMultiGridDelegate::setEditorData(QWidget *editor, const QModelIndex &MIndex)const
{
	WMultiGrid::CellData	*L=RootParent->GetData(MIndex.row() ,MIndex.column());
	QVariant				V=MIndex.model()->data(MIndex, Qt::DisplayRole);

	if(L!=NULL){
		if(L->CType==WMultiGrid::_CType_Label){
		}
		else if(L->CType==WMultiGrid::_CType_LineEdit){
			QLineEdit *v = static_cast<QLineEdit *>(editor);
			if(V.type()==QVariant::String){
				QString value = V.toString();
				v->setText(value);
				RootParent->ChangeValue(MIndex.row() ,MIndex.column() ,QVariant(value));
			}
			else if(V.type()==QVariant::Double){
				double value = V.toDouble();
				v->setText(QString::number(value));
				RootParent->ChangeValue(MIndex.row() ,MIndex.column() ,QVariant(value));
			}
		}
		else if(L->CType==WMultiGrid::_CType_SpinBox){
			QSpinBox *v = static_cast<QSpinBox *>(editor);
			if(V.type()==QVariant::Int){
				int value = V.toInt();
				v->setValue(value);
				RootParent->ChangeValue(MIndex.row() ,MIndex.column() ,QVariant(value));
			}
		}
		else if(L->CType==WMultiGrid::_CType_CheckBox){
			QCheckBox *v = static_cast<QCheckBox *>(editor);
			if(V.type()==QVariant::Bool){
				bool value = V.toBool();
				if(value==true){
					v->setCheckState(Qt::Checked);
				}
				else{
					v->setCheckState(Qt::Unchecked);
				}
				RootParent->ChangeValue(MIndex.row() ,MIndex.column() ,QVariant(value));
			}
			else if(V.type()==QVariant::String){
				QString value = V.toString();
				if((value=="true") || (value=="TRUE") || (value=="True")){
					v->setCheckState(Qt::Checked);
				}
				else{
					v->setCheckState(Qt::Unchecked);
				}
				RootParent->ChangeValue(MIndex.row() ,MIndex.column() ,QVariant(value));
			}
		}
		else if(L->CType==WMultiGrid::_CType_ComboBox){
			QComboBox *v = static_cast<QComboBox *>(editor);
			if(V.type()==QVariant::Int){
				int value = V.toInt();
				v->setCurrentIndex(value);
				RootParent->ChangeValue(MIndex.row() ,MIndex.column() ,QVariant(value));
			}
			else if(V.type()==QVariant::String){
				QString value = V.toString();
				v->setEditText(value);
				RootParent->ChangeValue(MIndex.row() ,MIndex.column() ,QVariant(value));
			}
		}
		else if(L->CType==WMultiGrid::_CType_Special){
		}
	}
}
void WMultiGridDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                          const QModelIndex &MIndex)const
{
	WMultiGrid::CellData	*L=RootParent->GetData(MIndex.row() ,MIndex.column());
	QVariant				V=MIndex.model()->data(MIndex, Qt::DisplayRole);

	if(L!=NULL){
		if(L->CType==WMultiGrid::_CType_Label){
		}
		else if(L->CType==WMultiGrid::_CType_LineEdit){
			QLineEdit *v = static_cast<QLineEdit *>(editor);
			QString value = v->text();
			model->setData(MIndex, value);
			if(V.type()==QVariant::String){
				RootParent->ChangeValue(MIndex.row() ,MIndex.column() ,QVariant(value));
			}
			else if(V.type()==QVariant::Double){
				RootParent->ChangeValue(MIndex.row() ,MIndex.column() ,QVariant(value.toDouble()));
			}
		}
		else if(L->CType==WMultiGrid::_CType_SpinBox){
			QSpinBox *v = static_cast<QSpinBox *>(editor);
			v->interpretText();
			int value = v->value();
			model->setData(MIndex, value);
			if(V.type()==QVariant::Int){
				RootParent->ChangeValue(MIndex.row() ,MIndex.column() ,QVariant(value));
			}
		}
		else if(L->CType==WMultiGrid::_CType_CheckBox){
			QCheckBox *v = static_cast<QCheckBox *>(editor);
			bool	value=false;
			if(v->checkState()==Qt::Checked){
				value=true;
			}
			else{
				value=false;
			}
			model->setData(MIndex, value);
	
			if(V.type()==QVariant::Bool){
				RootParent->ChangeValue(MIndex.row() ,MIndex.column() ,QVariant(value));
			}
			else if(V.type()==QVariant::String){
				QString	m;
				if(value==true){
					m="true";
				}
				else{
					m="false";
				}
				RootParent->ChangeValue(MIndex.row() ,MIndex.column() ,QVariant(m));
			}
		}
		else if(L->CType==WMultiGrid::_CType_ComboBox){
			QComboBox	*v = static_cast<QComboBox*>(editor);
			QString	value=v->currentText();
			model->setData(MIndex, value);
	
			if(V.type()==QVariant::Int){
				int Lvalue = v->currentIndex();
				RootParent->ChangeValue(MIndex.row() ,MIndex.column() ,QVariant(Lvalue));
			}
			else if(V.type()==QVariant::String){
				RootParent->ChangeValue(MIndex.row() ,MIndex.column() ,QVariant(value));
			}
		}
		else if(L->CType==WMultiGrid::_CType_Special){
		}
	}
}

void WMultiGridDelegate::updateEditorGeometry(QWidget *editor,
            const QStyleOptionViewItem &option, const QModelIndex &index)const
{
	editor->setGeometry(option.rect);
}

//============================================================================
WMultiGrid::CellData::CellData(void)
{
	CType		= _CType_Label;
	MaxValue	=  0x7FFFFFFF;
	MinValue	= -0x7FFFFFFF;
	Alignment	= Qt::AlignLeft | Qt::AlignVCenter;
}
WMultiGrid::CellData	&WMultiGrid::CellData::operator=(const WMultiGrid::CellData &src)
{
	Value		=src.Value;
	CType		=src.CType;
	MaxValue	=src.MaxValue;
	MinValue	=src.MinValue;
	CBoxList	=src.CBoxList;
	Alignment	=src.Alignment;
	return(*this);
}

WMultiGrid::WMultiGrid(QWidget * parent)
:QTableView(parent)
{
	Data=NULL;
	RowCount	=0;
	ColumnCount	=0;
}
WMultiGrid::~WMultiGrid()
{
	disconnect(this, SLOT(selectRowX(int)));
	if(Data!=NULL){
		for(int i=0;i<RowCount;i++){
			delete	[]Data[i];
		}
		delete	[]Data;
	}
	Data=NULL;
}


void	WMultiGrid::SetRowCount(int n)
{
	if(Data!=NULL){
		CellData	**tmpData;
		tmpData =new CellData*[n];
		for(int i=0;i<n;i++){
			tmpData[i]=new CellData[ColumnCount];
		}
		for(int i=0;i<RowCount && i<n;i++){
			for(int j=0;j<ColumnCount;j++){
				tmpData[i][j]=Data[i][j];
			}
		}
		for(int i=0;i<RowCount;i++){
			delete	[]Data[i];
		}
		delete	[]Data;
		Data=tmpData;
	}
	else{
		if(ColumnCount==0){
			ColumnCount=1;
		}
		Data =new CellData*[n];
		for(int i=0;i<n;i++){
			Data[i]=new CellData[ColumnCount];
		}
	}
	RowCount=n;
}

void	WMultiGrid::SetColumnCount(int n)
{
	if(Data!=NULL){
		CellData	**tmpData;
		tmpData =new CellData*[RowCount];
		for(int i=0;i<RowCount;i++){
			tmpData[i]=new CellData[n];
		}
		for(int i=0;i<RowCount;i++){
			for(int j=0;(j<ColumnCount) && (j<n);j++){
				tmpData[i][j]=Data[i][j];
			}
		}
		for(int i=0;i<RowCount;i++){
			delete	[]Data[i];
		}
		delete	[]Data;
		Data=tmpData;
	}
	else{
		if(RowCount==0){
			RowCount=1;
		}
		Data =new CellData*[RowCount];
		for(int i=0;i<RowCount;i++){
			Data[i]=new CellData[n];
		}
	}
	ColumnCount=n;
}
void	WMultiGrid::AppendRow(void)
{
	QAbstractItemModel *sm=model();
	if(sm!=NULL){
		int	Count=sm->rowCount();
		if(Count-1<0){
			sm->insertRow(0);
		}
		else{
			sm->insertRow(Count-1);
		}
		SetRowCount(RowCount+1);
	}
}
void	WMultiGrid::RemoveLine(int row)
{
	int	n=RowCount-1;
	if(Data!=NULL){
		CellData	**tmpData;
		tmpData =new CellData*[n];
		for(int i=0;i<n;i++){
			tmpData[i]=new CellData[ColumnCount];
		}
		int	t=0;
		for(int i=0;i<RowCount && i<row;i++,t++){
			for(int j=0;j<ColumnCount;j++){
				tmpData[t][j]=Data[t][j];
			}
		}
		for(int i=row+1;i<RowCount;i++,t++){
			for(int j=0;j<ColumnCount;j++){
				tmpData[t][j]=Data[t][j];
			}
		}
		for(int i=0;i<RowCount;i++){
			delete	[]Data[i];
		}
		delete	[]Data;
		Data=tmpData;
	}
	else{
		if(ColumnCount==0){
			ColumnCount=1;
		}
		Data =new CellData*[n];
		for(int i=0;i<n;i++){
			Data[i]=new CellData[ColumnCount];
		}
	}
	RowCount=n;
	QAbstractItemModel *sm=model();
	if(sm!=NULL){
		sm->removeRow(row);
	}
}

void	WMultiGrid::SetRowHeight(int h)
{
	for(int r=0;r<RowCount;r++){
		setRowHeight(r,h);
	}
}

void	WMultiGrid::SetTopHeader(int column, const QString &title)
{
	if(model()==NULL){
		QStandardItemModel	*model=new QStandardItemModel(RowCount,ColumnCount);
		setModel(model);
	}
	model()->setHeaderData(column, Qt::Horizontal, title	,Qt::DisplayRole);
}
void	WMultiGrid::SetLeftHeader(int row, const QString &title)
{
	if(model()==NULL){
		QStandardItemModel	*model=new QStandardItemModel(RowCount,ColumnCount);
		setModel(model);
	}
	if((model()!=NULL) && ((model()->rowCount()!=RowCount) || (model()->columnCount()!=ColumnCount))){
		QAbstractItemModel	*sm=model();
		QStandardItemModel	*NewModel=new QStandardItemModel(RowCount,ColumnCount);
		if(sm!=NULL){
			for(int i=0;i<(sm->rowCount()) && (i<RowCount);i++){
				QVariant	_title=sm->headerData(i, Qt::Vertical, Qt::DisplayRole);
				NewModel->setHeaderData(i, Qt::Vertical, _title	,Qt::DisplayRole);
			}
			for(int i=0;i<(sm->columnCount()) && (i<ColumnCount);i++){
				QVariant	_title=sm->headerData(i, Qt::Horizontal, Qt::DisplayRole);
				NewModel->setHeaderData(i, Qt::Horizontal, _title	,Qt::DisplayRole);
			}
			delete	sm;
		}
		setModel(NewModel);
	}

	if(model()!=NULL){
		model()->setHeaderData(row, Qt::Vertical, title	,Qt::DisplayRole);
	}
   connect((const QObject*)verticalHeader(), SIGNAL(sectionPressed(int)), this, SLOT(selectRowX(int)));
}


void	WMultiGrid::InitialGrid(void)
{
	QAbstractItemModel *sm=model();
	if(sm==NULL){
	    QStandardItemModel *model=new QStandardItemModel(RowCount, ColumnCount);
		setModel(model);
	}

	QAbstractItemDelegate	*s=itemDelegate();
    WMultiGridDelegate *Delegate=new WMultiGridDelegate (this);
    setItemDelegate(Delegate);
	if(s!=NULL){
		delete	s;
	}
	ShowGrid();
}

void	WMultiGrid::ShowGrid(void)
{
	QAbstractItemModel *sm=model();
	for(int r=0;r<RowCount;r++){
		for(int c=0;c<ColumnCount;c++){
			QModelIndex index = sm->index(r, c, QModelIndex());
			QVariant value;
			GetValue(r ,c,value);
			sm->setData(index, value);
		}
	}
}
/*
void	WMultiGrid::ChangeValue(int row ,int col,QVariant &value)
{
}
void	WMultiGrid::GetValue(int row ,int col,QVariant &value)
{
}
*/
QVariant	WMultiGrid::OpenDialogSpecial(int row ,int col)
{
	return(QVariant());
}

int	WMultiGrid::GetSelectedRow()
{
	QModelIndex Q=currentIndex();
	return Q.row();
	/*
	QModelIndexList Q=selectedIndexes ();
	if(Q.isEmpty()==true)
		return -1;
	return(Q.first().row());
	*/

}

void	WMultiGrid::selectRowX(int row)
{

}

void WMultiGrid::SlotClickedXYButton( int row ,int col)
{
	emit	SignalClickedXYButton(row ,col);
}


void	WMultiGrid::SlotTextChanged ( const QString &)
{
	emit	ChangedValue();
}
	
void	WMultiGrid::SlotValueChanged (int i)
{
	emit	ChangedValue();
}
