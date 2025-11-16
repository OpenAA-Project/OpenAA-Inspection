#include "DisplayNGListButtonResource.h"
#include "NGListForm.h"
#include "ui_NGListForm.h"
#include "XResult.h"
#include "DisplayThumbnailImagePacket.h"
#include "GeneralTabSheetPacket.h"
#include <QMessageBox>

NGListForm::NGListForm(LayersBase *Base ,QWidget *parent)
	:QDialog(parent),
    ui(new Ui::NGListForm)
{
	ui->setupUi(this);
	LangSolver.SetUI(this);

	LBase=Base;
	DisplayTargetImagePanel=NULL;
	ZoomRate=1.0;
	PreviousRow=-1;
	pGeneralTabSheet=NULL;
	NGSize=-1;

	WidthLineNumber		=24;
	WidthPageNumber		=24;
	WidthPosition		=64;
	WidthLocationName	=0;
	WidthCause			=64;

	ThumbnailCount		=1;

	pDisplayNGListButton=(DisplayNGListButton *)parent;

	QPalette P;
	P.setColor(QPalette::Base,QColor(Qt::cyan));
	ui->leNGCount->setPalette(P);

///	ErrorGroupData	=new ErrorGroupPack[Base->GetPhaseNumb()];

//	SetWidgetCenter(this);

	//ParentWidget
	ParentWidget=GetParentWidget();

	//画面レイアウト
    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QString::fromUtf8(/**/"gridLayout"));
    twNGList = new mtQTableWidget(ui->layoutWidget);
    twNGList->setObjectName(QString::fromUtf8(/**/"twNGList"));
    twNGList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    twNGList->setSelectionMode(QAbstractItemView::SingleSelection);
    twNGList->setSelectionBehavior(QAbstractItemView::SelectRows);

    gridLayout->addWidget(twNGList, 0, 0);
    gridLayout->addWidget(ui->layoutWidget, 1, 0);
    //gridLayout->addWidget(ui->layoutWidget1, 2, 0);
	setLayout(gridLayout);

	connect(twNGList,SIGNAL(SignalKeyDown())		,this,SLOT(twNGListKeyDown()));
//	connect(twNGList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(twNGListRowChanged(QModelIndex)));
	connect(twNGList,SIGNAL(itemSelectionChanged())	,this,SLOT(twNGListitemSelectionChanged()));
	connect(twNGList,SIGNAL(clicked(QModelIndex))	,this,SLOT(twNGListitemSelectionChanged()));

	//Visible false
	ui->label_2			->setVisible(false);
	ui->leNGPointCount	->setVisible(false);
}

NGListForm::~NGListForm()
{
	delete ui;
}
/*
void	NGListForm::SetErrorGroupData(ErrorGroupPack *Data)
{
	for(int phase=0;phase<LBase->GetPhaseNumb();phase++){
		ErrorGroupData[phase]=Data[phase];
	}
}
*/

	
void	NGListForm::SetNGCount(int Value)
{	
	ui->leNGCount	 ->setText(QString::number(Value));	
}

void	NGListForm::SetNGPointCount(int Value)
{	
	ui->leNGPointCount->setText(QString::number(Value));
}

void	NGListForm::ConnectItemSelectionChanged(bool Enable)
{
	if(Enable==true){
		connect		(twNGList,SIGNAL(itemSelectionChanged()),this,SLOT(twNGListitemSelectionChanged()));
	}
	else{
		disconnect	(twNGList,SIGNAL(itemSelectionChanged()),this,SLOT(twNGListitemSelectionChanged()));
	}
}

void	NGListForm::twNGListKeyDown()
{
	//ResultImportance対応
	if(twNGList->rowCount()==0){
		twNGList->SetIsSignalKeyDown(false);
		return;
	}

	ErrorGroup *e=NULL;
	int	r=0;
	for(int phase=0;phase<LBase->GetPhaseNumb();phase++){
		for(int i=0;i<pDisplayNGListButton->GetErrorGroupNumber(phase);i++,r++){
			ErrorGroup *er=pDisplayNGListButton->GetErrorGroupTable(phase,i);
			if(r==PreviousRow){
				e=er;
				goto	FoundPreE;
			}
		}
	}
FoundPreE:;
	if(e!=NULL){
		if(e->GetImportanceLevel()<100){
			//確認画面を表示
			QMessageBox MsgBox;
			QFont font1;
			font1.setPointSize(12);
			font1.setBold(true);
			font1.setWeight(75);
			MsgBox.setFont	(font1);
			MsgBox.setText	(LangSolver.GetString(NGListForm_LS,LID_1)/*"Is it really OK?"*/);				//本当にOKですか？
			MsgBox.addButton(LangSolver.GetString(NGListForm_LS,LID_2)/*"Yes"*/,QMessageBox::AcceptRole);	//はい
			MsgBox.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);
			MsgBox.resize(400,200);
			MsgBox.move(ParentWidget->x()+(ParentWidget->width()>>1)-(MsgBox.width()>>1),ParentWidget->y()+(ParentWidget->height()>>1)-400);
			int Ret=MsgBox.exec();
			if(Ret==QMessageBox::RejectRole){	//キャンセル
				twNGList->SetIsSignalKeyDown(false);
				return;
			}
		}
	}
	twNGList->SetIsSignalKeyDown(true);
}

//void NGListForm::twNGListRowChanged(const QModelIndex &CIndex)
void	NGListForm::twNGListitemSelectionChanged()
{
	if(twNGList->rowCount()==0){
		return;
	}
	pDisplayNGListButton->LoadNGColorInPlayer();

	int row	=twNGList->currentRow();
	ErrorGroup *e=NULL;
	int	r=0;
	for(int phase=0;phase<LBase->GetPhaseNumb();phase++){
///		for(ErrorGroup *er=ErrorGroupData[phase].GetFirst();er!=NULL;er=er->GetNext(),r++){
		for(int i=0;i<pDisplayNGListButton->GetErrorGroupNumber(phase);i++,r++){
			ErrorGroup *er=pDisplayNGListButton->GetErrorGroupTable(phase,i);
			if(r==row){
				e=er;
				goto	FoundE;
			}
		}
	}
FoundE:;

	//ErrorGroup *e=ErrorGroupData[phase].GetItem(row);
	if(e!=NULL){
////////////
		if(GetLayersBasePointer()->GetPhaseNumb()>1 && twNGList->item(row,0)->text()==/**/"1")
			DisplayTargetImagePanel = dynamic_cast<DisplayImage *>(GetLayersBasePointer()->FindByName(/**/"Inspection",/**/"DisplayTargetImage" ,/**/"TargetImage2"));
		else
			DisplayTargetImagePanel = dynamic_cast<DisplayImage *>(GetLayersBasePointer()->FindByName(/**/"Inspection",/**/"DisplayTargetImage" ,/**/"TargetImage"));
////////////
		if(DisplayTargetImagePanel!=NULL){
			int	ex1,ey1,ex2,ey2;
			e->GetXY(ex1,ey1,ex2,ey2);
			DataInPage *pdata=LBase->GetPageData(e->GetPage());
			if(pdata!=NULL){
				//NGSizeによる色表示対応
				if(pGeneralTabSheet!=NULL){
					if(e->GetNGSize()<NGSize){
						CmdExecNormalColor	CmdExNormalColor(LBase);
						pGeneralTabSheet->TransmitDirectly(&CmdExNormalColor);
					}
					else{
						CmdExecNGSizeColor	CmdExNGSizeColor(LBase);
						pGeneralTabSheet->TransmitDirectly(&CmdExNGSizeColor);
					}
					pGeneralTabSheet->repaint();
				}
				DisplayTargetImagePanel->ShowCenter((ex1+ex2)/2 +pdata->GetOutlineOffset()->x,(ey1+ey2)/2 +pdata->GetOutlineOffset()->y,ZoomRate);
			}
		}
	}
	twNGList->setFocus();
	PreviousRow=row;

	//DisplayThumbnailImageへデータの受け渡し
	GUIFormBase	*DTImageForm=LBase->FindByName(/**/"Inspection" ,/**/"DisplayThumbnailImage" ,/**/"");
	if(DTImageForm!=NULL){
		CmdSetCurrentRow	CmdSetCurRow(LBase);
		CmdSetCurRow.CurrentRow	=row;
		DTImageForm->TransmitDirectly(&CmdSetCurRow);
		DTImageForm->repaint();
	}
}

QWidget	*NGListForm::GetParentWidget()
{
	QWidget *P=NULL;
	for(P=parentWidget();P!=NULL;P=P->parentWidget()){
		if(P->parentWidget()==NULL){
			break;
		}
	}
	return P;
}
