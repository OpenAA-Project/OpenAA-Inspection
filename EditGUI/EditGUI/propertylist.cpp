/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditGUI\EditGUI\propertylist.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "propertylist.h"
#include "ui_propertylist.h"
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QColorDialog>
#include <XGeneralFunc.h>
#include <QFontDialog>
#if	defined(ModeEditGUI)
#include "ImageDialog.h"
#include "TunableListDialog.h"
#endif
#include "XGUIInterfaceDLL.h"
#include "InputStringList.h"

ColorButton::ColorButton(QWidget *parent) : QPushButton(parent)
{
    SColor=Qt::white;
}
ColorButton::~ColorButton()
{
}
void	ColorButton::setColor(const QColor &c)
{
    SColor=c;
    repaint(0,0,width(),height());
}
void ColorButton::paintEvent ( QPaintEvent * event )
{
}

ImageButton::ImageButton(const QModelIndex &mindex,PropertyList *p,QWidget *parent)
	: QPushButton(parent),MIndex(mindex)
{
    connect(this,SIGNAL(clicked()),this,SLOT(ButtonClick()));
	if(p!=NULL){
		connect(this,SIGNAL(SignalImage(QModelIndex ,QImage)),p,SLOT(SlotImage(QModelIndex ,QImage)),Qt::QueuedConnection);
	}
}
ImageButton::~ImageButton()
{
}
void	ImageButton::setImage(const QImage &c)
{
    SImage=c;
}
void ImageButton::ButtonClick()
{
#if	defined(ModeEditGUI)
	emit	SignalImage(MIndex,SImage);
#endif
}

StringListDialogList::StringListDialogList(QWidget *parent)
    : WMultiGrid(parent)
{
}

void	StringListDialogList::ChangeValue(int row ,int col,const QVariant &value)
{
    QWidget	*w=parentWidget();
    InputStringList *dw=dynamic_cast<InputStringList *>(w);
    if(dw->MList.count()==row){
        dw->MList.append(value.toString());
        emit	Changed();
    }
    else{
        dw->MList.replace(row,value.toString());
    }
}
void	StringListDialogList::GetValue(int row ,int col,QVariant &value)
{
    QWidget	*w=parentWidget();
    InputStringList *dw=dynamic_cast<InputStringList *>(w);
    if(dw->MList.count()>row){
        value=QVariant(dw->MList.value(row));
    }
}

//StringListDialog::StringListDialog(QWidget *parent ,QStringList &mlist)
//: QDialog(parent)
//{
//    resize(200,300);
//    RGrid.setParent(this);
//    RGrid.resize(200,300);
//    RGrid.move(0,0);
//    RGrid.SetColumnCount(1);
//    MList=mlist;
//    SetGrid();
//    connect(&RGrid ,SIGNAL(Changed()),this,SLOT(Changed()),Qt::QueuedConnection);
//}
//
//void	StringListDialog::SetGrid(void)
//{
//    RGrid.SetRowCount(MList.count()+1);
//    RGrid.move(0,0);
//    RGrid.resize(width(),height());
//    for(int r=0;r<MList.count();r++){
//        WMultiGrid::CellData *L=RGrid.GetData(r ,0);
//        L->Value	=MList.value(r);
//        L->CType	=WMultiGrid::_CType_LineEdit;
//        L->Alignment=Qt::AlignVCenter | Qt::AlignLeft;
//    }
//    WMultiGrid::CellData *L=RGrid.GetData(MList.count() ,0);
//    L->Value	=MList.value(MList.count());
//    L->CType	=WMultiGrid::_CType_LineEdit;
//    L->Alignment=Qt::AlignVCenter | Qt::AlignLeft;
//    RGrid.InitialGrid();
//}
//
//void	StringListDialog::Changed()
//{
//    SetGrid();
//}
//void StringListDialog::resizeEvent ( QResizeEvent * event )
//{
//    RGrid.resize(width(),height());
//    RGrid.setColumnWidth(0,width()-72);
//}

StringListButton::StringListButton(const QModelIndex &index,PropertyList *_ParentRoot,QWidget *parent)
    : QPushButton(parent),Index(index),ParentRoot(_ParentRoot)
{
    connect(this,SIGNAL(clicked()),this,SLOT(ButtonClick()));
}
StringListButton::~StringListButton()
{
}
void StringListButton::ButtonClick()
{
    if(ParentRoot!=NULL){
        InputStringList *D=new InputStringList(Index,ParentRoot,MList);
        if (D->exec()==(int)true) {
            D->Parent->SetStringList(D->MList,D->Index);
        }
        D->deleteLater();
    }
}

PropertyListPushButton::PropertyListPushButton(QWidget * parent ,PropertyList *rootParent ,StructList	*pointList)
        :QPushButton(parent)
{
    PointList		=pointList;
    RootParent		=rootParent;
    connect(this,SIGNAL(clicked()),this,SLOT(Click()));
}

void PropertyListPushButton::Click ()
{
    PointList->Opened=!PointList->Opened;
    //PropertyList	*p=dynamic_cast<PropertyList *>(parentWidget()->parentWidget());
    //if(p!=NULL)
    //	p->ShowList();
    RootParent->ShowListInside();
}

TunableListButton::TunableListButton(QWidget *parent) : QPushButton(parent)
{
    connect(this,SIGNAL(clicked()),this,SLOT(ButtonClick()));
}
TunableListButton::~TunableListButton()
{
}
void TunableListButton::ButtonClick()
{
#if	defined(ModeEditGUI)
    TunableListDialog	D(MList,this);
    D.exec();
    //MList=D.MList;
#endif
}

FileNameButton::FileNameButton(PropertyList *rootparent ,QWidget *parent,int row) : QPushButton(parent)
{
    RootParent=rootparent;
    Row=row;
    connect(this,SIGNAL(clicked()),this,SLOT(ButtonClick()),Qt::QueuedConnection);
}
FileNameButton::~FileNameButton()
{}

void FileNameButton::ButtonClick()
{
    FileName=QFileDialog::getOpenFileName (0, "Open file name");
    setText(FileName);
    RootParent->SetData(Row,FileName);
}


PathNameButton::PathNameButton(QWidget *parent) : QPushButton(parent)
{
    connect(this,SIGNAL(clicked()),this,SLOT(ButtonClick()));
}
PathNameButton::~PathNameButton()
{
}
void PathNameButton::ButtonClick()
{
    PathName=QFileDialog::getExistingDirectory(0, "Path name");
    setText(PathName);
}

FileNamesButton::FileNamesButton(QWidget *parent) : QPushButton(parent)
{
    connect(this,SIGNAL(clicked()),this,SLOT(ButtonClick()));
}
FileNamesButton::~FileNamesButton()
{
}
void FileNamesButton::ButtonClick()
{
    FileNames=QFileDialog::getOpenFileNames (0, "Open file name");
    if(FileNames.count()>0){
        setText(FileNames[0]);
    }
    else{
        setText(/**/"");
    }
}

ByteArrayButton::ByteArrayButton(PropertyList *p,PropertyListDelegate *d,const QModelIndex &Index,const QString &_VariableName ,QWidget *parent)
    :QPushButton(parent)
    ,Parent(p)
    ,Delegate(d)
    ,VariableName(_VariableName)
    ,MIndex(Index)
{
    connect(this,SIGNAL(clicked()),this,SLOT(ButtonClick()));
    connect(this,SIGNAL(SignalClickToDelegate(const QString,const QModelIndex)),Delegate,SLOT(SlotClickToDelegate(const QString,const QModelIndex)),Qt::QueuedConnection);
}
ByteArrayButton::~ByteArrayButton(void)
{
}

void	ByteArrayButton::SetQByteArray(const QByteArray &c)
{
    if(Parent->DLLInst!=NULL){
        for(StructList *s=Parent->DLLInst->StructInstance.GetFirst();s!=NULL;s=s->GetNext()){
            if(s->VName==VariableName){
                s->SetValue(c);
                break;
            }
        }
    }
}

QByteArray	ByteArrayButton::GetQByteArray(void)
{
    if(Parent->DLLInst!=NULL){
        for(StructList *s=Parent->DLLInst->StructInstance.GetFirst();s!=NULL;s=s->GetNext()){
            if(s->VName==VariableName){
                return s->GetQByteArray();
            }
        }
    }
    return QByteArray();
}

void ByteArrayButton::ButtonClick()
{
    emit	SignalClickToDelegate(VariableName,MIndex);
    /*
    static	bool	Test=false;
    if(Parent->DLLInst!=NULL && Parent->DLLInst->GetForm()!=NULL){
        Parent->DLLInst->GetForm()->ShowQByteArrayDialog(VariableName);
        //QByteArray	A;
        //for(StructList *s=Parent->DLLInst->StructInstance.GetFirst();s!=NULL;s=s->GetNext()){
        //	if(s->VName==VariableName){
        //		A=s->GetQByteArray();
        //		Test=true;
        //	}
        //}
    }
    */
}


//=========================================================================================

PropertyListDelegate::PropertyListDelegate(PropertyList *_RootParent ,QObject *parent)
        : QItemDelegate(parent)
{
    RootParent=_RootParent;
}

QWidget *PropertyListDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &/* option */,
        const QModelIndex &MIndex/* index */) const
{
    int	depthNo;
    StructList	*L=RootParent->GetStructItem(MIndex.row() ,depthNo);
    if(L==NULL){
        return NULL;
    }
    if(MIndex.column()==0){
        if(L->StructInstance.GetNumber()==0){
            QLabel *label =new QLabel(parent);
            label->setText(QString::number(depthNo));
            return(label);
        }
        else{
            PropertyListPushButton	*bttn=new PropertyListPushButton(parent,RootParent ,L);
            bttn->setText(QString::number(depthNo));
            return(bttn);
        }
    }
    else if(MIndex.column()==1){
        QLabel *label =new QLabel(parent);
        label->setText(L->VName);
        return(label);
    }
    else if(MIndex.column()==2){
        if(L!=NULL){
            if(L->VType==_DT_bool){
                QComboBox	*editor = new QComboBox(parent);
                QStringList	List;
                List.append(QString(/**/"true"));
                List.append(QString(/**/"false"));
                editor->addItems(List);
                editor->setEditable(false);
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_byte){
                QSpinBox *editor = new QSpinBox(parent);
                editor->setMinimum(0);
                editor->setMaximum(255);
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_short){
                QSpinBox *editor = new QSpinBox(parent);
                editor->setMinimum(-32768);
                editor->setMaximum(32767);
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_int){
                QSpinBox *editor = new QSpinBox(parent);
                editor->setMinimum(-0x7FFFFFFF);
                editor->setMaximum(0x7FFFFFFF);
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_int32){
                QSpinBox *editor = new QSpinBox(parent);
                editor->setMinimum(-0x7FFFFFFF);
                editor->setMaximum(0x7FFFFFFF);
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_int64){
                QSpinBox *editor = new QSpinBox(parent);
                editor->setMinimum(-0x7FFFFFFF);
                editor->setMaximum(0x7FFFFFFF);
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_QString){
                QLineEdit *editor = new QLineEdit(parent);
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_double){
                QLineEdit *editor = new QLineEdit(parent);
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_float){
                QLineEdit *editor = new QLineEdit(parent);
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_QColor){
                QLineEdit *editor = new QLineEdit(parent);
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                QString value = MIndex.model()->data(MIndex, Qt::DisplayRole).toString();
                QColor	C=QColorDialog::getColor(QString2QColor(value));
                if(C.isValid()){
                    ((QAbstractItemModel *)MIndex.model())->setData(MIndex, QColor2QString(C));
                    editor->setText(QColor2QString(C));
                }
                return editor;
            }
            else if(L->VType==_DT_QFont){
                QLineEdit *editor = new QLineEdit(parent);
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                QString value = MIndex.model()->data(MIndex, Qt::DisplayRole).toString();
                bool	ok;
                QFont	InitialFont;
                InitialFont.fromString(value);
                QFont	F=QFontDialog::getFont(&ok,InitialFont);
                if(ok==true){
                    ((QAbstractItemModel *)MIndex.model())->setData(MIndex, F.toString());
                    editor->setText(F.toString());
                }
                return editor;
            }
            else if(L->VType==_DT_enum){
                QComboBox	*editor = new QComboBox(parent);
                QStringList	List;
                editor->addItems(L->Enum);
                editor->setEditable(false);
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_IntList){
                QLineEdit *editor = new QLineEdit(parent);
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_QStringList){
                StringListButton *editor = new StringListButton(MIndex,RootParent,parent);
                editor->MList = MIndex.model()->data(MIndex, Qt::DisplayRole).toStringList();
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_TunableList){
                TunableListButton *editor = new TunableListButton(parent);
                editor->MList = MIndex.model()->data(MIndex, Qt::DisplayRole).toStringList();
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_FileName){
                FileNameButton *editor = new FileNameButton(RootParent,parent,MIndex.row() );
                editor->FileName = MIndex.model()->data(MIndex, Qt::DisplayRole).toString();
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_PathName){
                PathNameButton *editor = new PathNameButton(parent);
                editor->PathName = MIndex.model()->data(MIndex, Qt::DisplayRole).toString();
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_FileNames){
                FileNamesButton *editor = new FileNamesButton(parent);
                editor->FileNames = MIndex.model()->data(MIndex, Qt::DisplayRole).toStringList();
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_QImage){
                ImageButton *editor = new ImageButton(MIndex,RootParent,parent);
                editor->SImage = MIndex.model()->data(MIndex, Qt::DisplayRole).value<QImage>();
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else if(L->VType==_DT_QByteArray){
                ByteArrayButton *editor = new ByteArrayButton(RootParent,(PropertyListDelegate *)this,MIndex,L->VName,parent);
                //editor->SetQByteArray(MIndex.model()->data(MIndex, Qt::DisplayRole).value<QByteArray>());
                editor->installEventFilter(const_cast<PropertyListDelegate*>(this));
                return editor;
            }
            else{
                return NULL;
            }
        }
    }
    return(NULL);
}

void PropertyListDelegate::setEditorData(QWidget *editor,
                                        const QModelIndex &MIndex) const
{
    int	depthNo;
    StructList	*L=RootParent->GetStructItem(MIndex.row() ,depthNo);
    if(MIndex.column()==2){
        if(L!=NULL){
            if(L->VType==_DT_bool){
                QString value = MIndex.model()->data(MIndex, Qt::DisplayRole).toString();
                QComboBox	*v = static_cast<QComboBox*>(editor);
                if(value==/**/"true"){
                    v->setEditText(/**/"true");
                }
                else{
                    v->setEditText(/**/"false");
                }
            }
            else if(L->VType==_DT_byte){
                int value = MIndex.model()->data(MIndex, Qt::DisplayRole).toInt();
                QSpinBox *v = static_cast<QSpinBox *>(editor);
                v->setValue(value);
            }
            else if(L->VType==_DT_short){
                int value = MIndex.model()->data(MIndex, Qt::DisplayRole).toInt();
                QSpinBox *v = static_cast<QSpinBox *>(editor);
                v->setValue(value);
            }
            else if(L->VType==_DT_int){
                int value = MIndex.model()->data(MIndex, Qt::DisplayRole).toInt();
                QSpinBox *v = static_cast<QSpinBox *>(editor);
                v->setValue(value);
            }
            else if(L->VType==_DT_int32){
                int value = MIndex.model()->data(MIndex, Qt::DisplayRole).toInt();
                QSpinBox *v = static_cast<QSpinBox *>(editor);
                v->setValue(value);
            }
            else if(L->VType==_DT_int64){
                int value = MIndex.model()->data(MIndex, Qt::DisplayRole).toInt();
                QSpinBox *v = static_cast<QSpinBox *>(editor);
                v->setValue(value);
            }
            else if(L->VType==_DT_QString){
                QString value = MIndex.model()->data(MIndex, Qt::DisplayRole).toString();
                QLineEdit *v = static_cast<QLineEdit *>(editor);
                v->setText(value);
            }
            else if(L->VType==_DT_double){
                double value = MIndex.model()->data(MIndex, Qt::DisplayRole).toDouble();
                QLineEdit *v = static_cast<QLineEdit *>(editor);
                v->setText(QString::number(value));
            }
            else if(L->VType==_DT_float){
                float value = MIndex.model()->data(MIndex, Qt::DisplayRole).toDouble();
                QLineEdit *v = static_cast<QLineEdit *>(editor);
                v->setText(QString::number((double)value));
            }
            else if(L->VType==_DT_QColor){
                QString	value = MIndex.model()->data(MIndex, Qt::DisplayRole).toString();
                QLineEdit *v = static_cast<QLineEdit *>(editor);
                v->setText(value);
            }
            else if(L->VType==_DT_QFont){
                QString	value = MIndex.model()->data(MIndex, Qt::DisplayRole).toString();
                QLineEdit *v = static_cast<QLineEdit *>(editor);
                v->setText(value);
            }
            else if(L->VType==_DT_enum){
                QString value = MIndex.model()->data(MIndex, Qt::DisplayRole).toString();
                QComboBox	*v = static_cast<QComboBox*>(editor);
                int	index=v->findText(value);
                v->setCurrentIndex(index);
            }
            else if(L->VType==_DT_IntList){
                QString value = MIndex.model()->data(MIndex, Qt::DisplayRole).toString();
                QLineEdit *v = static_cast<QLineEdit *>(editor);
                v->setText(value);
            }
            else if(L->VType==_DT_QStringList){
                QStringList value = MIndex.model()->data(MIndex, Qt::DisplayRole).toStringList();
                StringListButton	*v = static_cast<StringListButton*>(editor);
                v->MList = value;
                v->setText(QString::number(value.count()));
            }
            else if(L->VType==_DT_TunableList){
                QStringList value = MIndex.model()->data(MIndex, Qt::DisplayRole).toStringList();
                TunableListButton	*v = static_cast<TunableListButton*>(editor);
                v->MList = value;
                v->setText(QString::number(value.count()));
            }
            else if(L->VType==_DT_FileName){
                QString value = MIndex.model()->data(MIndex, Qt::DisplayRole).toString();
                FileNameButton *v = static_cast<FileNameButton *>(editor);
                v->FileName	=value;
            }
            else if(L->VType==_DT_PathName){
                QString value = MIndex.model()->data(MIndex, Qt::DisplayRole).toString();
                PathNameButton *v = static_cast<PathNameButton *>(editor);
                v->PathName	=value;
            }
            else if(L->VType==_DT_FileNames){
                QStringList value = MIndex.model()->data(MIndex, Qt::DisplayRole).toStringList();
                FileNamesButton *v = static_cast<FileNamesButton *>(editor);
                v->FileNames	=value;
            }
            else if(L->VType==_DT_QImage){
                QImage	value = MIndex.model()->data(MIndex, Qt::DisplayRole).value<QImage>();
                ImageButton *v = static_cast<ImageButton *>(editor);
                v->setImage(value);
            }
            else if(L->VType==_DT_QByteArray){
                QByteArray	value = MIndex.model()->data(MIndex, Qt::DisplayRole).value<QByteArray>();
                ByteArrayButton *v = static_cast<ByteArrayButton *>(editor);
                v->SetQByteArray(value);
            }
        }
    }
}

void PropertyListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                       const QModelIndex &MIndex) const
{
    int	depthNo;
    StructList	*L=RootParent->GetStructItem(MIndex.row() ,depthNo);
    if(MIndex.column()==2){
        if(L!=NULL){
            if(L->VType==_DT_bool){
                QComboBox	*v = static_cast<QComboBox*>(editor);
                QString	value=v->currentText();
                model->setData(MIndex, value);
            }
            else if(L->VType==_DT_byte){
                QSpinBox *v = static_cast<QSpinBox *>(editor);
                v->interpretText();
                int value = v->value();
                model->setData(MIndex, value);
            }
            else if(L->VType==_DT_short){
                QSpinBox *v = static_cast<QSpinBox *>(editor);
                v->interpretText();
                int value = v->value();
                model->setData(MIndex, value);
            }
            else if(L->VType==_DT_int){
                QSpinBox *v = static_cast<QSpinBox *>(editor);
                v->interpretText();
                int value = v->value();
                model->setData(MIndex, value);
            }
            else if(L->VType==_DT_int32){
                QSpinBox *v = static_cast<QSpinBox *>(editor);
                v->interpretText();
                int value = v->value();
                model->setData(MIndex, value);
            }
            else if(L->VType==_DT_int64){
                QSpinBox *v = static_cast<QSpinBox *>(editor);
                v->interpretText();
                int value = v->value();
                model->setData(MIndex, value);
            }
            else if(L->VType==_DT_QString){
                QLineEdit *v = static_cast<QLineEdit *>(editor);
                QString value = v->text();
                model->setData(MIndex, value);
            }
            else if(L->VType==_DT_double){
                QLineEdit *v = static_cast<QLineEdit *>(editor);
                QString value = v->text();
                model->setData(MIndex, value.toDouble());
            }
            else if(L->VType==_DT_float){
                QLineEdit *v = static_cast<QLineEdit *>(editor);
                QString value = v->text();
                model->setData(MIndex, value.toFloat());
            }
            else if(L->VType==_DT_QColor){
                QLineEdit *v = static_cast<QLineEdit *>(editor);
                QString	value = v->text();
                model->setData(MIndex, value);
            }
            else if(L->VType==_DT_QFont){
                QLineEdit *v = static_cast<QLineEdit *>(editor);
                QString value = v->text();
                model->setData(MIndex, value);
            }
            else if(L->VType==_DT_enum){
                QComboBox	*v = static_cast<QComboBox*>(editor);
                QString	value=v->currentText();
                model->setData(MIndex, value);
            }
             else if(L->VType==_DT_IntList){
                QLineEdit *v = static_cast<QLineEdit *>(editor);
                QString value = v->text();
                model->setData(MIndex, value);
            }
             else if(L->VType==_DT_QStringList){
                StringListButton *v = static_cast<StringListButton *>(editor);
                QStringList value = v->MList;
                model->setData(MIndex, value);
            }
            else if(L->VType==_DT_TunableList){
                TunableListButton *v = static_cast<TunableListButton *>(editor);
                QStringList value = v->MList;
                model->setData(MIndex, value);
            }
            else if(L->VType==_DT_FileName){
                FileNameButton *v = static_cast<FileNameButton *>(editor);
                QString value = v->FileName;
                model->setData(MIndex, value);
            }
            else if(L->VType==_DT_PathName){
                PathNameButton *v = static_cast<PathNameButton *>(editor);
                QString value = v->PathName;
                model->setData(MIndex, value);
            }
            else if(L->VType==_DT_FileNames){
                FileNamesButton *v = static_cast<FileNamesButton *>(editor);
                QStringList value = v->FileNames;
                model->setData(MIndex, value);
            }
            else if(L->VType==_DT_QImage){
                ImageButton *v = static_cast<ImageButton *>(editor);
                QImage	value = v->SImage;
                model->setData(MIndex, value);
            }
            else if(L->VType==_DT_QByteArray){
                ByteArrayButton *v = static_cast<ByteArrayButton *>(editor);
                QByteArray	value = v->GetQByteArray();
                model->setData(MIndex, value);
            }
        }
    }
}

void	PropertyListDelegate::SlotClickToDelegate(const QString VName,const QModelIndex MIndex)
{
    if(RootParent->DLLInst!=NULL && RootParent->DLLInst->GetForm()!=NULL){
        RootParent->DLLInst->GetForm()->ShowQByteArrayDialog(VName);

        for(StructList *s=RootParent->DLLInst->StructInstance.GetFirst();s!=NULL;s=s->GetNext()){
            if(s->VName==VName){
                QByteArray	value = s->GetQByteArray();
                RootParent->model->setData(MIndex, value);
            }
        }
    }
}

void PropertyListDelegate::updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}


//==========================================================================

PropertyList::PropertyList(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent)
    ,DLLInstDummy(NULL) 
    ,DLLInst(&DLLInstDummy)
    ,PutTop(NULL)
    ,ui(new Ui::PropertyList)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    ui->tableView->move(0,ui->frame->height());
    OnShowing=false;
}

PropertyList::~PropertyList()
{
    delete ui;
}

void	PropertyList::SetDLL(GuiDLLItem *dllItem)
{
    DWORD ErrorCode;
    DLLInst=&DLLInstDummy;
    DLLInst->Clear();
    DLLInst->Initial(GetLayersBase(),NULL,ErrorCode ,dllItem);
    if(DLLInst->DLLAccess!=NULL){
        ShowList(DLLInst->DLLAccess->RootName,DLLInst->DLLAccess->Name);
    }
}

StructList	*PropertyList::GetStructItem(int LineNo ,int &depthNo)
{
    if(DLLInst==NULL){
        return(NULL);
    }
    return(DLLInst->StructInstance.GetStructItem(LineNo ,depthNo));
}
StructList	*PropertyList::FindStructItem(const QString &VName)
{
    if(DLLInst==NULL){
        return(NULL);
    }
    return(DLLInst->StructInstance.FindStructItem(VName));
}

void	PropertyList::ShowList(const QString &DLLRoot ,const QString &DLLName)
{
    ui->labelDLLRoot->setText(DLLRoot);
    ui->labelDLLName->setText(DLLName);

    ShowListInside();
}

void	PropertyList::ShowListInside(void)
{
    int	N=0;
    if(DLLInst==NULL){
        return;
    }
    DLLInst->StructInstance.GetLineNumb(N);

    QAbstractItemModel *sm=ui->tableView->model();
    model=new QStandardItemModel(N, 3);
    ui->tableView->setModel(model);
    if(sm!=NULL){
        delete	sm;
    }
    model->setHeaderData(0, Qt::Horizontal, tr("Dep")	,Qt::DisplayRole);
    model->setHeaderData(1, Qt::Horizontal, tr("Name")	,Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, tr("Value")	,Qt::EditRole	);
    connect(model,SIGNAL(dataChanged (const QModelIndex &,const QModelIndex &)),this ,SLOT(ModelDataChanged (const QModelIndex &,const QModelIndex &)));

    QAbstractItemDelegate	*s=ui->tableView->itemDelegate();
    PropertyListDelegate *Delegate=new PropertyListDelegate (this);
    ui->tableView->setItemDelegate(Delegate);
    if(s!=NULL){
        delete	s;
    }

    resizeEvent(NULL);
    ShowData();
}

void	PropertyList::ClearList()
{
    ShowList(/**/"" ,/**/"");
}

void	PropertyList::ModelDataChanged (const QModelIndex &topleft ,const QModelIndex &bottomright)
{
    if(OnShowing==true){
        return;
    }
    int	depthNo;
    if(topleft.column()<=2 && 2<=bottomright.column()){
		int	R1=topleft.row();
		int	R2=bottomright.row();
        for(int r=R1;r<=R2;r++){
            QModelIndex	MIndex=topleft.sibling(r, 2);
            StructList	*L=GetStructItem(r ,depthNo);
            if(L!=NULL){
                if(L->VType==_DT_bool){
                    QString value = model->data(MIndex, Qt::DisplayRole).toString();
                    if(value==/**/"true"){
                        L->SetValue(true);
                    }
                    else{
                        L->SetValue(false);
                    }
                }
                else if(L->VType==_DT_byte){
                    byte value = model->data(MIndex, Qt::DisplayRole).toInt();
                    L->SetValue(value);
                }
                else if(L->VType==_DT_short){
                    short value = model->data(MIndex, Qt::DisplayRole).toInt();
                    L->SetValue(value);
                }
                else if(L->VType==_DT_int){
                    int value = model->data(MIndex, Qt::DisplayRole).toInt();
                    L->SetValue(value);
                }
                else if(L->VType==_DT_int32){
                    int32 value = model->data(MIndex, Qt::DisplayRole).toInt();
                    L->SetValue(value);
                }
                else if(L->VType==_DT_int64){
                    int64 value = model->data(MIndex, Qt::DisplayRole).toInt();
                    L->SetValue(value);
                }
                else if(L->VType==_DT_QString){
                    QString value = model->data(MIndex, Qt::DisplayRole).toString();
                    L->SetValue(value);
                }
                else if(L->VType==_DT_double){
                    double value = model->data(MIndex, Qt::DisplayRole).toDouble();
                    L->SetValue(value);
                }
                else if(L->VType==_DT_float){
                    float value = model->data(MIndex, Qt::DisplayRole).toDouble();
                    L->SetValue(value);
                }
                else if(L->VType==_DT_QColor){
                    QString	value = model->data(MIndex, Qt::DisplayRole).toString();
                    QColor	Qc=QString2QColor(value);
                    L->SetValue(Qc);
                }
                else if(L->VType==_DT_QFont){
                    QString	value = model->data(MIndex, Qt::DisplayRole).toString();
                    QFont	F;
                    F.fromString(value);
                    L->SetValue(F);
                }
                else if(L->VType==_DT_enum){
                    QString value = model->data(MIndex, Qt::DisplayRole).toString();
                    L->SetEnumValue(value);
                }
                else if(L->VType==_DT_IntList){
                    QString value = model->data(MIndex, Qt::DisplayRole).toString();
                    QStringList LList=value.split(/**/",");
                    IntList D;
                    for(int i=0;i<LList.count();i++){
                        bool    ok;
                        int n=LList[i].toInt(&ok);
                        if(ok==true){
                            D.Add(n);
                        }
                    }
                    L->SetIntListValue(D);
                }
                else if(L->VType==_DT_QStringList){
                    QStringList value = model->data(MIndex, Qt::DisplayRole).toStringList();
                    L->SetValue(value);
                }
                else if(L->VType==_DT_TunableList){
                    QStringList value = model->data(MIndex, Qt::DisplayRole).toStringList();
                    L->SetTunableValue(value);
                }
                else if(L->VType==_DT_FileName){
                    QString value = model->data(MIndex, Qt::DisplayRole).toString();
                    L->SetFileNameValue(value);
                }
                else if(L->VType==_DT_PathName){
                    QString value = model->data(MIndex, Qt::DisplayRole).toString();
                    L->SetPathNameValue(value);
                }
                else if(L->VType==_DT_FileNames){
                    QStringList value = model->data(MIndex, Qt::DisplayRole).toStringList();
                    L->SetFileNamesValue(value);
                }
                else if(L->VType==_DT_QImage){
                    QImage	value = model->data(MIndex, Qt::DisplayRole).value<QImage>();
                    L->SetValue(value);
                }
                else if(L->VType==_DT_QByteArray){
                    QByteArray	value = model->data(MIndex, Qt::DisplayRole).value<QByteArray>();
                    L->SetValue(value);
                }
                if((L->VName==/**/"Left"
                 || L->VName==/**/"Right"
                 || L->VName==/**/"Top"
                 || L->VName==/**/"Bottom")
                && GetCurrentDLLInst()!=NULL){
                    StructList	*LX1=FindStructItem(/**/"Left");
                    StructList	*LY1=FindStructItem(/**/"Top");
                    StructList	*LX2=FindStructItem(/**/"Right");
                    StructList	*LY2=FindStructItem(/**/"Bottom");
                    if(LX1!=NULL && LY1!=NULL && LX2!=NULL && LY2!=NULL){
                        int W=LX2->GetInt32()-LX1->GetInt32();
                        if(W<0){
                            LX2->SetValue(LX1->GetInt32());
                        }
                        int H=LY2->GetInt32()-LY1->GetInt32();
                        if(H<0){
                            LY2->SetValue(LY1->GetInt32());
                        }
                        int x1=LX1->GetInt32();
                        int y1=LY1->GetInt32();
                        GetCurrentDLLInst()->Handle->setGeometry(x1,y1,W,H);
                        GetCurrentDLLInst()->SlotResize();
                    }
                }
            }
        }
        DLLInst->ChangedValue();
    }
}

void	PropertyList::SetStringList(const QStringList &MList,const QModelIndex &MIndex)
{
    int	depthNo;
    StructList* L=GetStructItem(MIndex.row(),depthNo);
    if (L!=NULL && L->VType==_DT_QStringList){
        model->setData(MIndex,MList);
    }
}

void	PropertyList::SetData(int Row ,QVariant v)
{
    QModelIndex MIndex=ui->tableView->currentIndex();
    ui->tableView->model()->setData(MIndex, v,Qt::DisplayRole);
}
void	PropertyList::ShowData(void)
{
    QAbstractItemModel *sm=ui->tableView->model();
    int	N=0;
    if(DLLInst==NULL){
        return;
    }
    OnShowing=true;
    DLLInst->StructInstance.GetLineNumb(N);
    for(int i=0;i<N;i++){
        ui->tableView->setRowHeight(i,20);
        int	depthNo;
        StructList	*L=DLLInst->StructInstance.GetStructItem(i ,depthNo);

        if(L!=NULL){
            QModelIndex index0 = sm->index(i, 0, QModelIndex());
            sm->setData(index0, depthNo);

            QModelIndex index1 = sm->index(i, 1, QModelIndex());
            sm->setData(index1, L->VName);

            QModelIndex index2 = sm->index(i, 2, QModelIndex());
            if(L->VType==_DT_bool){
                if(L->GetBool()==true){
                    sm->setData(index2, /**/"true");
                }
                else{
                    sm->setData(index2, /**/"false");
                }
            }
            else if(L->VType==_DT_byte){
                sm->setData(index2, L->GetByte());
            }
            else if(L->VType==_DT_short){
                sm->setData(index2, L->GetShort());
            }
            else if(L->VType==_DT_int){
                sm->setData(index2, L->GetInt());
            }
            else if(L->VType==_DT_int32){
                sm->setData(index2, L->GetInt32());
            }
            else if(L->VType==_DT_int64){
                sm->setData(index2, L->GetInt64());
            }
            else if(L->VType==_DT_QString){
                sm->setData(index2, L->GetQString());
            }
            else if(L->VType==_DT_double){
                sm->setData(index2, QString::number(L->GetDouble()));
            }
            else if(L->VType==_DT_float){
                sm->setData(index2, QString::number(L->GetFloat()));
            }
            else if(L->VType==_DT_QColor){
                QColor	C=L->GetColor();
                //sm->setData(index2, QString::number(C.value()));
                sm->setData(index2, QColor2QString(C));
            }
            else if(L->VType==_DT_QFont){
                QFont	F=L->GetFont();
                sm->setData(index2, F.toString());
            }
            else if(L->VType==_DT_enum){
                sm->setData(index2, L->GetEnum());
            }
            else if(L->VType==_DT_IntList){
                IntList D=L->GetIntList();
                QString LStr;
                for(IntClass *c=D.GetFirst();c!=NULL;c=c->GetNext()){
                    LStr+=QString::number(c->GetValue());
                    if(c->GetNext()!=NULL){
                        LStr+=/**/",";
                    }
                }
                sm->setData(index2, LStr);
            }
            else if(L->VType==_DT_QStringList){
                sm->setData(index2, L->GetQStringList());
            }
            else if(L->VType==_DT_TunableList){
                sm->setData(index2, L->GetTunableList());
            }
            else if(L->VType==_DT_FileName){
                sm->setData(index2, L->GetQString());
            }
            else if(L->VType==_DT_PathName){
                sm->setData(index2, L->GetQString());
            }
            else if(L->VType==_DT_FileNames){
                sm->setData(index2, L->GetQStringList());
            }
            else if(L->VType==_DT_QImage){
                QVariant	v=L->GetQImage();
                sm->setData(index2, v);
            }
            else if(L->VType==_DT_QByteArray){
                QVariant	v=L->GetQByteArray();
                sm->setData(index2, v);
            }
        }
    }
    OnShowing=false;
}

QAbstractItemModel *PropertyList::GetModel(void)
{
	 QAbstractItemModel *sm=ui->tableView->model();
	 return sm;
}

void PropertyList::resizeEvent ( QResizeEvent * event )
{
    int H1=ui->labelDLLRoot->height();
    int H2=ui->labelDLLName->height();
    ui->labelDLLRoot->resize(width()-ui->labelDLLRoot->geometry().left(),H1);
    ui->labelDLLName->resize(width()-ui->labelDLLName->geometry().left(),H2);
    ui->frame->setGeometry(0,0,width(),H1+H2);
    int H=ui->frame->height();
    ui->tableView->setGeometry(0,H,width(),height()-H);

    int	W=width()-72;
    ui->tableView->setColumnWidth(0,W*0.15);
    ui->tableView->setColumnWidth(1,W*0.45);
    ui->tableView->setColumnWidth(2,W*0.40);
}

void	PropertyList::Repaint(void)
{
    //QAbstractItemModel *sm=ui->tableView->model();
    //sm->submit();
    ShowData();
}
void	PropertyList::SlotImage(QModelIndex MIndex,QImage Img)
{
    ImageDialog	D(Img);
    D.exec();
	if(D.SImage.isNull()==false){
		QAbstractItemModel	*sm=GetModel();
		sm->setData(MIndex, D.SImage);
	}
}