#include "EVDLLListForm.h"
#include "ui_EVDLLListForm.h"
#include "XExecuteVisualizerInterface.h"

CategoryListGrid::CategoryListGrid(EVCategoryList *category,QWidget * parent)
	:WMultiGrid(parent),Category(category)
{
	setSelectionMode	(QAbstractItemView::SingleSelection);
	setSelectionBehavior(QAbstractItemView::SelectRows);

	SetRowCount(Category->GetCount());
	SetColumnCount(3);
	SetTopHeader(0, /**/"");
	SetTopHeader(0, /**/"Name");
	SetTopHeader(0, /**/"Explain");

	//setColumnWidth ( 0, 20);
	//setColumnWidth ( 1, 64);
	//setColumnWidth ( 2, 100);
	SetRowHeight   (32);

	int	r=0;
	for(EVDLLList *v=Category->NPListPack<EVDLLList>::GetFirst();v!=NULL;v=v->GetNext()){
		QString DLLRoot;
		QString DLLName;
		QString Explain;
		v->Item->GetRootName(DLLRoot, DLLName);
		const QString	s=v->Item->GetExplain();
		if(s.isEmpty()==false){
			Explain=s;
		}
		WMultiGrid::CellData *L1=GetData(r ,0);
		L1->Value	=DLLRoot;
		L1->CType	=WMultiGrid::_CType_Label;
		L1->Alignment=Qt::AlignVCenter | Qt::AlignLeft;

		WMultiGrid::CellData *L2=GetData(r ,1);
		L2->Value	=DLLName;
		L2->CType	=WMultiGrid::_CType_Label;
		L2->Alignment=Qt::AlignVCenter | Qt::AlignLeft;

		WMultiGrid::CellData *L3=GetData(r ,2);
		L3->Value	=Explain;
		L3->CType	=WMultiGrid::_CType_Label;
		L3->Alignment=Qt::AlignVCenter | Qt::AlignLeft;
		r++;
	}
}

void	CategoryListGrid::ChangeValue(int row ,int col,const QVariant &value)
{
}
void	CategoryListGrid::GetValue(int row ,int col,QVariant &value)
{
	EVDLLList *v=Category->NPListPack<EVDLLList>::GetItem(row);
	if(v!=NULL){
		QString DLLRoot;
		QString DLLName;
		v->Item->GetRootName(DLLRoot, DLLName);
		if(col==0){
			value=DLLRoot;
		}
		else if(col==1){
			value=DLLName;
		}
		else if(col==2){
			QString Explain;
			const	QString	s=v->Item->GetExplain();
			if(s.isEmpty()==false){
				Explain=s;
			}
			value=Explain;
		}
	}
}
void	CategoryListGrid::resizeEvent(QResizeEvent *event)
{
	int	W=width()-72;
	setColumnWidth(0,W*0.2);
	setColumnWidth(1,W*0.40);
	setColumnWidth(2,W*0.40);
}

//============================================================================

EVDLLListForm::EVDLLListForm(RunnerMap &_RMap,QWidget *parent) :
    QWidget(parent),
	RMap(_RMap),
    ui(new Ui::EVDLLListForm)
{
    ui->setupUi(this);
	BuildCategoryData();
	MakeTabList();
}

EVDLLListForm::~EVDLLListForm()
{
    delete ui;
}

void	EVDLLListForm::BuildCategoryData(void)
{
	for(RunnerObjDLL *a=RMap.GetFirst();a!=NULL;a=a->GetNext()){
		QString DLLRoot;
		QString DLLName;
		a->GetRootName(DLLRoot, DLLName);
		EVCategoryList *b;
		for(b=CategoryContainer.GetFirst();b!=NULL;b=b->GetNext()){
			if(b->DLLRoot==DLLRoot){
				b->AppendList(new EVDLLList(a));
				break;
			}
		}
		if(b==NULL){
			EVCategoryList	*bb=new EVCategoryList(DLLRoot);
			bb->AppendList(new EVDLLList(a));
			CategoryContainer.AppendList(bb);
		}
	}
}

void	EVDLLListForm::MakeTabList(void)
{
	ui->tabWidgetDLLList->clear();
	for(EVCategoryList *a=CategoryContainer.GetFirst();a!=NULL;a=a->GetNext()){
		CategoryListGrid	*W=new CategoryListGrid(a);
		W->InitialGrid();
		ui->tabWidgetDLLList->addTab(W,a->DLLRoot);
	}
}

RunnerObjDLL	*EVDLLListForm::GetCurrentDLL(void)
{
	CategoryListGrid	*W=dynamic_cast<CategoryListGrid *>(ui->tabWidgetDLLList->currentWidget());
	if(W!=NULL){
		QModelIndex M=W->currentIndex ();
		EVDLLList	*e=W->Category->GetItem(M.row());
		if(e!=NULL){
			return e->Item;
		}
	}
	return NULL;
}
void	EVDLLListForm::resizeEvent ( QResizeEvent * event )
{
	QRect R=contentsRect();
	ui->tabWidgetDLLList->resize(R.width(),R.height());
}