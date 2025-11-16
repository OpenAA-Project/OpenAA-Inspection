/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditGUI\EditGUI\itemlistwindow.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "itemlistwindow.h"
#include "ui_itemlistwindow.h"
#include <QTabWidget>
#include "propertylist.h"
#include <QScrollBar>
#include "XGUIInterfaceDLL.h"

const	int		DefButtonSize=36;
const	int		DefRowMergin=2;

ItemButton::ItemButton(QWidget *parent)
:QToolButton(parent)
{
    ItemPoint=NULL;
    connect(this,SIGNAL(clicked()),this,SLOT(SlotClick(void)));
}


void ItemButton::mouseMoveEvent ( QMouseEvent * event )
{
    if(ItemPoint!=NULL && ItemPoint->DLLPoint!=NULL){
        RootParent->SBar.showMessage(ItemPoint->DLLPoint->Explain);
    }
    else
        RootParent->SBar.showMessage("Point");
}

void	ItemButton::SlotClick(void)
{
    if(ItemPoint->DLLPoint!=NULL){
        MainProperty->SetDLL(ItemPoint->DLLPoint);
    }
}


ItemButtonList::ItemButtonList(void)
{
    DLLPoint	=NULL;
    Button		=NULL;
    Parent		=NULL;
    LabelName	=new QLabel();
    LabelName->setWordWrap(false);
    LabelName->setFrameShadow(QFrame::Sunken);
    LabelName->setFrameShape(QFrame::Panel);
    LabelName->resize(150,DefButtonSize);
    LabelExplain	=new QLabel();
    LabelExplain->setWordWrap(true);
    LabelExplain->setFrameShadow(QFrame::Sunken);
    LabelExplain->setFrameShape(QFrame::Panel);
    LabelExplain->resize(100,DefButtonSize);
}
ItemButtonList::~ItemButtonList(void)
{
    DLLPoint	=NULL;
    if(Button!=NULL){
        delete	Button;
    }
    Button		=NULL;
    Parent		=NULL;
}

int	ItemButtonList::Compare(ItemButtonList &src)
{
    if(DLLPoint==NULL)
        return -1;
    if(src.DLLPoint==NULL)
        return 1;
    if(DLLPoint->GetDLLName()<src.DLLPoint->GetDLLName())
        return -1;
    if(DLLPoint->GetDLLName()>src.DLLPoint->GetDLLName())
        return 1;
    return 0;
}

//--------------------------------------------------------

ItemListWindow::ItemListWindow(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ItemListWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    SBar.setParent(this);
    SBar.showMessage("Nothing");
    //SBar.addWidget(this);
}

ItemListWindow::~ItemListWindow()
{
    delete ui;
}

void	ItemListWindow::Initial(void)
{
    ui->tabWidget->removeTab(0);
    for(GuiDLLItem *p=GetLayersBase()->GetGuiInitializer()->GuiDLLPack->GetFirst();p!=NULL;p=p->GetNext()){
        bool	Found=false;
        for(int i=0;i<sizeof(Item)/sizeof(Item[0]);i++){
            if(Item[i].GetCount()>0 && Item[i].GetItem(1)->DLLPoint->GetDLLRoot()==p->GetDLLRoot()){
                ItemButtonList	*w=new ItemButtonList();
                w->DLLPoint=p;
                Item[i].AppendList(w);
                Found=true;
                break;
            }
        }
        if(Found==false){
            for(int i=0;i<sizeof(Item)/sizeof(Item[0]);i++){
                if(Item[i].GetCount()==0){
                    ItemButtonList	*Dummy=new ItemButtonList();
                    Dummy->DLLPoint=NULL;
                    Item[i].AppendList(Dummy);

                    ItemButtonList	*w=new ItemButtonList();
                    w->DLLPoint=p;
                    Item[i].AppendList(w);
                    break;
                }
            }
        }
    }

    for(int t=0;t<sizeof(Item)/sizeof(Item[0]);t++){
        if(Item[t].GetCount()>0){
            Item[t].Sort();

            GuiDLLItem	*p=Item[t].GetItem(1)->DLLPoint;
            TabScrollArea	*C=new TabScrollArea();
            C->W=new QWidget();
            C->setWidget(C->W);
            ui->tabWidget->addTab(C,p->RootName);
            QWidget	*w=ui->tabWidget->widget(t);
            ItemButton	*DummyButton=new ItemButton(C->W);
            DummyButton->setAutoExclusive(true);
            DummyButton->setCheckable(true);
            DummyButton->resize(DefButtonSize,DefButtonSize);
            DummyButton->RootParent=this;
            DummyButton->setMouseTracking(true);
            ItemButtonList	*D	=Item[t].GetItem(0);
            D->Parent			=w;
            D->Button			=DummyButton;
            D->DLLPoint			=NULL;
            D->Page				=t;
            D->TabBase			=C->W;
            DummyButton->ItemPoint	=D;

            for(ItemButtonList *E=D->GetNext();E!=NULL;E=E->GetNext()){
                ItemButton	*b=new ItemButton(C->W);
                b->setAutoExclusive(true);
                b->setCheckable(true);
                b->setIconSize(QSize(32,32));
                b->resize(DefButtonSize,DefButtonSize);
                b->setIcon(E->DLLPoint->GetIcon());
                b->RootParent=this;
                b->setMouseTracking(true);
                b->ItemPoint=E;

                E->Parent	=w;
                E->Button	=b;
                E->Page=t;
                E->LabelName	->setParent(C->W);
                E->LabelName	->setText(E->DLLPoint->Name);
                E->LabelExplain	->setParent(C->W);
                E->LabelExplain	->setText(E->DLLPoint->Explain);
                E->TabBase=C->W;
            }
        }
    }
}
void	ItemListWindow::ShowItems(void)
{
    if(ui->tabWidget==NULL){
        return;
    }
    SBar.resize(width(),16);
    SBar.move(0,height()-SBar.height());
    ui->tabWidget->move(0,0);
    ui->tabWidget->resize(width(),height()-SBar.height());
    int	n=ui->tabWidget->count();
    for(int i=0;i<sizeof(Item)/sizeof(Item[0]);i++){
        if(Item[i].GetNumber()==0){
            break;
        }

        int	pnumb=0;
        int	Lw=0;
        bool    Checked = false;
        for(ItemButtonList *p=Item[i].GetFirst();p!=NULL;p=p->GetNext(),pnumb++){
            //p->Button->move((pnumb%WNumb)*w ,(pnumb/WNumb)*h);
            Lw=p->Parent->geometry().width()-24;
            if (p->Button->isChecked() == true) {
                Checked = true;
            }
            p->Button		->move(0				,pnumb*(DefButtonSize+DefRowMergin));
            p->LabelName	->move(DefButtonSize+2	,pnumb*(DefButtonSize+DefRowMergin));
            p->LabelExplain	->move(DefButtonSize+4+p->LabelName->geometry().width()	,pnumb*(DefButtonSize+DefRowMergin));
            int	W=Lw-p->LabelExplain->geometry().left();
            if(W<20){
                W=20;
            }
            p->LabelExplain	->resize(W,DefButtonSize);
        }
        ItemButtonList *pi=Item[i].GetFirst();
        if(Checked==false && pi!=NULL){
            pi->Button->setChecked(true);
            pi->TabBase->setGeometry(0,0,Lw,pnumb*(DefButtonSize+DefRowMergin));
        }
    }
}

void ItemListWindow::resizeEvent ( QResizeEvent * event )
{
    ShowItems();
}

ItemButtonList	*ItemListWindow::GetActiveButton(void)
{
    for(int i=0;i<sizeof(Item)/sizeof(Item[0]);i++){
        if(Item[i].GetNumber()==0){
            break;
        }
        for(ItemButtonList *p=Item[i].GetFirst();p!=NULL;p=p->GetNext()){
            if(p->Button->isChecked()==true
                && ui->tabWidget->widget(ui->tabWidget->currentIndex ())==p->Parent){
                return(p);
            }
        }
    }
    return(NULL);
}
void		ItemButtonList::setUnchecked()
{
    QWidget	*p=Button;
    for(;;){
        QWidget	*q=p->parentWidget ();
        if(q==NULL){
            return;
        }
        ItemListWindow	*s=dynamic_cast<ItemListWindow *>(q);
        if(s!=NULL){
            s->Item[Page].GetFirst()->Button->setChecked(true);
            break;
        }
        p=q;
    }
}

void	ItemListWindow::SelectGUI(GUINameClassified *v)
{
    for(int i=0;i<sizeof(Item)/sizeof(Item[0]);i++){
        int	row=0;
        for(ItemButtonList *a=Item[i].GetFirst();a!=NULL;a=a->GetNext(),row++){
            if(a->DLLPoint==v->Point){
                a->Button->setChecked(true);
                a->Button->SlotClick();
                for(int k=0;k<ui->tabWidget->count();k++){
                    QString s=ui->tabWidget->tabText (k);
                    if(s==a->DLLPoint->GetDLLRoot()){
                        ui->tabWidget->setCurrentIndex(k);
                        break;
                    }
                }
                TabScrollArea	*C=dynamic_cast<TabScrollArea *>(ui->tabWidget->widget(i));
                C->verticalScrollBar()->setSliderPosition(row*(DefButtonSize+DefRowMergin));
                return;
            }
        }
    }
}
