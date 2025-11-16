#include "ConfirmForm.h"
#include "ui_ConfirmForm.h"
#include "LearningServer.h"
#include "XLearningServer.h"
#include <QScrollArea>
#include <QScrollBar>
#include <QMenu>
#include "XDLLType.h"
#include "XGUIComponent.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"

ItemPanelImage::ItemPanelImage(ItemPanel *parent)
	:Parent(parent)
{
}
void ItemPanelImage::mouseReleaseEvent(QMouseEvent *Ev)
{
	bool	LeftClicked		= ((Ev->button() & Qt::LeftButton)!=0) ? true : false;
	bool	RightClicked	= ((Ev->button() & Qt::RightButton)!=0) ? true : false;

	int x=Ev->x();
	int y=Ev->y();
	if(LeftClicked==true){
		Parent->ShowItemInWindow();
	}
	else
	if(RightClicked==true){
		QMenu	Menu(this);
		Menu.addAction (QString(tr("Edit")	), this, SLOT(EditAction()));
		Menu.addAction (QString(tr("Remove")), this, SLOT(RemoveAction()));
		QPoint	Q=mapToGlobal(Ev->pos());
		Menu.exec(Q);
	}
}
void    ItemPanelImage::EditAction()
{
	Parent->EditAction();
}
void    ItemPanelImage::RemoveAction()
{
	Parent->RemoveAction();
}

ItemPanel::ItemPanel(int LayerNumb,ConfirmForm *parent,LearningInDB *b,LearningParamInDB *p)
    :Parent(parent)
	,LearningInDBPoint(b)
	,Param(p)
	,Title(this)
	,Panel(this)
	,Message(this)
{
	setAutoFillBackground(true);
    resize(LearningConfirmItemPanelWidth,LearningConfirmItemPanelHeight);
	Title	.setParent(this);
	Panel	.setParent(this);
	Message	.setParent(this);
	Title.setGeometry(0,LearningConfirmItemMergin
					,LearningConfirmItemImagePanelWidth-LearningConfirmItemMergin*2,LearningConfirmItemTitlePanelHeight);
	Title.setAlignment(Qt::AlignCenter);
	Title.setAutoFillBackground(true);
	QPalette	P=Title.palette();
	P.setColor(QPalette::Window,Qt::gray);
	Title.setPalette(P);
	Panel.setGeometry(LearningConfirmItemMergin,LearningConfirmItemTitlePanelHeight+LearningConfirmItemMergin
					,LearningConfirmItemImagePanelWidth -LearningConfirmItemMergin*2
					,LearningConfirmItemImagePanelHeight-LearningConfirmItemMergin);
	Message.setGeometry(0,LearningConfirmItemTitlePanelHeight+LearningConfirmItemMergin+LearningConfirmItemImagePanelHeight
						,LearningConfirmItemImagePanelWidth,LearningConfirmItemMessageHeight);
	Message.setWordWrap(true);

	LayersBase	*LBase=LearningInDBPoint->LayerForCalc;
	ImageBuffer *TargetBuffDim[100];
	QBuffer	TargetImageBuff(&LearningInDBPoint->TargetImage);
	TargetImageBuff.open(QIODevice::ReadOnly);

	for(int Layer=0;Layer<LayerNumb;Layer++){
		DataInLayer	*Ly=LBase->GetPageData(0)->GetLayerData(Layer);

		TargetBuffDim[Layer]=&Ly->GetTargetBuff();
		TargetBuffDim[Layer]->Load(&TargetImageBuff);
	}
	TargetImage=Parent->Parent->MakeImage(TargetBuffDim ,LBase,LayerNumb
							,LearningConfirmItemImagePanelWidth,LearningConfirmItemImagePanelHeight);

	Panel.setPixmap(QPixmap::fromImage(TargetImage));
	Title.setText(QString::number(LearningInDBPoint->LearningID));
	Message.setText("...");
}
void    ItemPanel::ShowResult(void)
{
	DetailResultInfoListContainer RetList;
	Result=Parent->Parent->ExecuteProcess(LearningInDBPoint,Param
									,RetList);
	if(Result==1){
		QPalette	P=palette();
		P.setColor(QPalette::Window,Qt::green);
		setPalette(P);
	}
	else
	if(Result==2){
		QPalette	P=palette();
		P.setColor(QPalette::Window,Qt::red);
		setPalette(P);
	}
	else
	{
		QPalette	P=palette();
		P.setColor(QPalette::Window,Qt::gray);
		setPalette(P);
	}
	QStringList StrList;
	RetList.GetInfoStringList(StrList);
	
	QString	Str;
	for(int i=0;i<StrList.count();i++){
		Str+=StrList[i];
		Str+=/**/" ";
	}
	Message.setText(Str);
}
void    ItemPanel::ShowItemInWindow(void)
{
	Parent->ShowItemInWindow(this);
}
void    ItemPanel::ShowAll(void)
{
	update();
	show();
	Panel.update();
	Message.update();
	Panel.show();
	Message.show();
}
void    ItemPanel::EditAction()
{
	Parent->Parent->EditItem(LearningInDBPoint->LearningID);
}

void    ItemPanel::RemoveAction()
{
	Parent->RemoveItem(LearningInDBPoint->LearningID);
}

//============================================================================

ConfirmForm::ConfirmForm(int _LayerNumb,LearningServer *parent ,LogicDLL *L,AlgorithmComponentWindow *w,QWidget *p) :
    QWidget(p)
    ,Parent(parent)
	,LogicDLLInst(L)
	,AdjustWindow(w)
	,LayerNumb(_LayerNumb)
    ,ui(new Ui::ConfirmForm)
{
    ui->setupUi(this);
	//AdjustWindow=NULL;
	OKWindow=ui->scrollAreaShouldOK->widget();	//new QWidget();
	//OKWindow->setObjectName("OKWindow");
	//OKWindow->setGeometry(0,0,1000,1000);
	NGWindow=ui->scrollAreaShouldNG->widget();	//new QWidget();
	//NGWindow->setObjectName("NGWindow");
	//NGWindow->setGeometry(0,0,1000,1000);

	AlgorithmComponentWindow	*A=dynamic_cast<AlgorithmComponentWindow *>(LogicDLLInst->GetShowAndSetItemsForm());
	if(A!=NULL){
		connect(A,SIGNAL(SignalChangeValue()),this,SLOT(SlotChangeValue()));
	}
	connect(ui->scrollAreaShouldOK->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(SlotOKScrollBarChanged(int)));
	connect(ui->scrollAreaShouldOK->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(SlotNGScrollBarChanged(int)));
}

ConfirmForm::~ConfirmForm()
{
    delete ui;
}

void    ConfirmForm::closeEvent(QCloseEvent *event)
{
	if(AdjustWindow!=NULL){
		AdjustWindow->close();
		AdjustWindow=NULL;
		Parent->CurrentAlgoWindow=NULL;
	}
}

void    ConfirmForm::SetLibrary(int _LibType,int _LibID)
{
    LibType =_LibType;
    LibID   =_LibID;

	ItemPanel *aOk;
	while((aOk=OKItems.GetFirst())!=NULL){
		OKItems.RemoveList(aOk);
		aOk->close();
		aOk->deleteLater();
	}
	ItemPanel *aNg;
	while((aNg=OKItems.GetFirst())!=NULL){
		NGItems.RemoveList(aNg);
		aNg->close();
		aNg->deleteLater();
	}
	//OKItems.RemoveAll();
	//NGItems.RemoveAll();

	//ui->scrollAreaShouldOK->setWidget(OKWindow);
	//ui->scrollAreaShouldNG->setWidget(NGWindow);

    for(LearningInDB *s=Parent->Executer->LearningList.GetFirst();s!=NULL;s=s->GetNext()){
		for(LearningParamInDB *a=s->NPListPackSaveLoad<LearningParamInDB>::GetFirst();a!=NULL;a=a->GetNext()){
			if(a->LibType==LibType && a->LibID==LibID){
				ItemPanel	*P=new ItemPanel(LayerNumb,this,s,a);
				if(s->SampleType==1){
					P->setParent(OKWindow);
					P->show();
					OKItems.AppendList(P);
				}
				else
				if(s->SampleType>=2){
					P->setParent(NGWindow);
					P->show();
					NGItems.AppendList(P);
				}
				break;
			}
		}
	}
	ShowResult();
	resizeEvent(NULL);
}

void	ConfirmForm::resizeEvent(QResizeEvent *event)
{
	ui->labelShouldOK->setGeometry(0,0,width(),ui->labelShouldOK->height());
	ui->scrollAreaShouldOK->setGeometry(0,ui->labelShouldOK->height()
										,width(),height()/2-ui->labelShouldOK->height()-6);

	ui->labelShouldNG->setGeometry(0,height()/2,width(),ui->labelShouldNG->height());
	ui->scrollAreaShouldNG->setGeometry(0,height()/2+ui->labelShouldNG->height()
										,width(),height()/2-ui->labelShouldNG->height()-6);

	XNumb=(width()-16)/LearningConfirmItemPanelWidth;
	if(XNumb==0)
		XNumb=1;
	int	OKYNumb=(OKItems.GetCount()+XNumb-1)/XNumb;
	OKWindow->move(0,0);
	OKWindow->resize(XNumb*LearningConfirmItemPanelWidth,OKYNumb*LearningConfirmItemPanelHeight);
	int	n=0;
	for(ItemPanel *a=OKItems.GetFirst();a!=NULL;a=a->GetNext(),n++){
		int	Xn=n%XNumb;
		int	Yn=n/XNumb;
		a->setParent(OKWindow);
		a->move(Xn*LearningConfirmItemPanelWidth,Yn*LearningConfirmItemPanelHeight);
		a->show();
	}
	OKWindow->update();

	int	NGYNumb=(NGItems.GetCount()+XNumb-1)/XNumb;
	NGWindow->move(0,0);
	NGWindow->resize(XNumb*LearningConfirmItemPanelWidth,NGYNumb*LearningConfirmItemPanelHeight);
	n=0;
	for(ItemPanel *a=NGItems.GetFirst();a!=NULL;a=a->GetNext(),n++){
		int	Xn=n%XNumb;
		int	Yn=n/XNumb;
		a->setParent(NGWindow);
		a->move(Xn*LearningConfirmItemPanelWidth,Yn*LearningConfirmItemPanelHeight);
		a->show();
	}
	NGWindow->update();
	int	OKPageSize=ui->scrollAreaShouldOK->verticalScrollBar()->pageStep();
	int	NGPageSize=ui->scrollAreaShouldNG->verticalScrollBar()->pageStep();
	ui->scrollAreaShouldOK->verticalScrollBar()->setMaximum(OKYNumb*LearningConfirmItemPanelHeight-OKPageSize);
	ui->scrollAreaShouldNG->verticalScrollBar()->setMaximum(NGYNumb*LearningConfirmItemPanelHeight-NGPageSize);

	//ui->scrollAreaShouldOK->setWidget(OKWindow);
	//ui->scrollAreaShouldNG->setWidget(NGWindow);
}
void    ConfirmForm::ShowResult(void)
{
	for(ItemPanel *a=OKItems.GetFirst();a!=NULL;a=a->GetNext()){
		a->ShowResult();
	}
	for(ItemPanel *a=NGItems.GetFirst();a!=NULL;a=a->GetNext()){
		a->ShowResult();
	}
}

void    ConfirmForm::SlotChangeValue()
{
	if(AdjustWindow!=NULL){
		QByteArray	ItemData=AdjustWindow->RequiteItemDataInWindow();
		Parent->SetThreshold(LibType,LibID,ItemData);
	}
	ShowResult();
}

void    ConfirmForm::ShowItemInWindow(ItemPanel *From)
{
	Parent->SetItemDataInWindow(From->LearningInDBPoint,From->Param);
}
void    ConfirmForm::SetShowAndSetItems(AlgorithmComponentWindow *w)
{
	AdjustWindow=w;
	if(AdjustWindow!=NULL){
		connect(AdjustWindow,SIGNAL(SignalChangeValue()),this,SLOT(SlotChangeValue()));
	}
}

void    ConfirmForm::SlotOKScrollBarChanged(int)
{
	OKWindow->show();
	for(ItemPanel *a=OKItems.GetFirst();a!=NULL;a=a->GetNext()){
		a->ShowAll();
	}
}
void    ConfirmForm::SlotNGScrollBarChanged(int)
{
	NGWindow->show();
	for(ItemPanel *a=NGItems.GetFirst();a!=NULL;a=a->GetNext()){
		a->ShowAll();
	}
}

void    ConfirmForm::RemoveItem(int LearningID)
{
	Parent->RemoveItem(LearningID);
	SetLibrary(LibType,LibID);
}
