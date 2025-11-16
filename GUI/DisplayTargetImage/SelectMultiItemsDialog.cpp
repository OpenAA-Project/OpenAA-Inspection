#include "SelectMultiItemsDialog.h"
#include "ui_SelectMultiItemsDialog.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

SelectMultiItemsDialog::SelectMultiItemsDialog(LayersBase *Base ,FlexArea &Area,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::SelectMultiItemsDialog)
{
    ui->setupUi(this);

	Selected=NULL;
	IntList PageList;
	GetLayersBase()->GetLocalPageFromArea(Area,PageList);
	for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
		int	page=p->GetValue();
		DataInPage	*dp=GetLayersBase()->GetPageData(page);
		FlexArea	A=Area;
		if(dp->ClipMoveAreaFromGlobal(A)==true){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqMultiItemsByArea	RCmd(GetLayersBase(),sRoot,sName,globalPage);
			GUICmdSendMultiItemsByArea	SCmd(GetLayersBase(),sRoot,sName,globalPage);
			RCmd.Area=A;
			if(RCmd.Send(globalPage,0,SCmd)==true){
				for(ItemsByAlgorithm *a=SCmd.Container.GetFirst();a!=NULL;a=a->GetNext()){
					ItemsByAlgorithm *b;
					for(b=ContainersBindedPhase.GetFirst();b!=NULL;b=b->GetNext()){
						if(a->LibType==b->LibType
						&& a->LibID==b->LibID
						&& a->Layer==b->Layer){
							b->ItemID+=a->ItemID;
							break;
						}
					}
					if(b==NULL){
						b=new ItemsByAlgorithm();
						b->LibType	=a->LibType;
						b->LibID	=a->LibID;
						b->Layer	=a->Layer;
						b->ItemID=a->ItemID;
						ContainersBindedPhase.AppendList(b);
					}
				}
				for(ItemsByAlgorithm *a=SCmd.Container.GetFirst();a!=NULL;a=a->GetNext()){
					for(ListPhasePageID *t=a->ItemID.GetFirst();t!=NULL;t=t->GetNext()){
						ItemsByAlgorithm *b;
						for(b=ContainersEachPhase.GetFirst();b!=NULL;b=b->GetNext()){
							if(a->LibType==b->LibType
							&& a->LibID==b->LibID
							&& a->Layer==b->Layer
							&& t->Phase==b->ItemID.GetFirst()->Phase){
								ListPhasePageID	*m=new ListPhasePageID(*t);
								b->ItemID.AppendList(m);
								break;
							}
						}
						if(b==NULL){
							b=new ItemsByAlgorithm();
							b->LibType	=a->LibType;
							b->LibID	=a->LibID;
							b->Layer	=a->Layer;
							ListPhasePageID	*m=new ListPhasePageID(*t);
							b->ItemID.AppendList(m);
							ContainersEachPhase.AppendList(b);
						}
					}
				}
			}
		}
	}
	ui->tableWidget->setRowCount(ContainersEachPhase.GetCount());
	int	Row=0;
	for(ItemsByAlgorithm *t=ContainersEachPhase.GetFirst();t!=NULL;t=t->GetNext(),Row++){
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(t->LibType);
		::SetDataToTable(ui->tableWidget,0, Row, QString::number(t->ItemID.GetFirst()->Phase));
		if(ABase!=NULL){
			QString DLLRoot ,DLLName;
			ABase->GetAlgorithmRootName(DLLRoot ,DLLName);
			::SetDataToTable(ui->tableWidget,1, Row, DLLRoot+QString(":")+DLLName);
		}
		else{
			::SetDataToTable(ui->tableWidget,1, Row, QString("---"));
		}
		::SetDataToTable(ui->tableWidget,2, Row,QString::number(t->LibID));
		if(ABase!=NULL){
			AlgorithmLibraryContainer	*ALibContainer=ABase->GetLibraryContainer();
			if(ALibContainer!=NULL){
				QString	LibName=ALibContainer->GetLibraryName(t->LibID);
				::SetDataToTable(ui->tableWidget,3, Row, LibName);
			}
		}
		::SetDataToTable(ui->tableWidget,4, Row,QString::number(t->Layer));
		::SetDataToTable(ui->tableWidget,5, Row,QString::number(t->ItemID.GetCount()));
	}

	ui->tableWidgetBinded->setRowCount(ContainersBindedPhase.GetCount());
	Row=0;
	for(ItemsByAlgorithm *t=ContainersBindedPhase.GetFirst();t!=NULL;t=t->GetNext(),Row++){
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(t->LibType);
		if(ABase!=NULL){
			QString DLLRoot ,DLLName;
			ABase->GetAlgorithmRootName(DLLRoot ,DLLName);
			::SetDataToTable(ui->tableWidgetBinded,0, Row, DLLRoot+QString(":")+DLLName);
		}
		else{
			::SetDataToTable(ui->tableWidgetBinded,0, Row, QString("---"));
		}
		::SetDataToTable(ui->tableWidgetBinded,1, Row,QString::number(t->LibID));
		if(ABase!=NULL){
			AlgorithmLibraryContainer	*ALibContainer=ABase->GetLibraryContainer();
			if(ALibContainer!=NULL){
				QString	LibName=ALibContainer->GetLibraryName(t->LibID);
				::SetDataToTable(ui->tableWidgetBinded,2, Row, LibName);
			}
		}
		::SetDataToTable(ui->tableWidgetBinded,3, Row,QString::number(t->Layer));
		::SetDataToTable(ui->tableWidgetBinded,4, Row,QString::number(t->ItemID.GetCount()));
	}
}

SelectMultiItemsDialog::~SelectMultiItemsDialog()
{
    delete ui;
}

void	SelectMultiItemsDialog::resizeEvent(QResizeEvent *event)
{
	ui->frame->setGeometry(0,height()-ui->frame->height(),width(),ui->frame->height());
	int	W=(width()-ui->pushButtonSelect->width()-ui->pushButtonCancel->width())/3;
	ui->pushButtonSelect->move(W,ui->pushButtonSelect->geometry().top());
	ui->pushButtonCancel->move((width()+W)/2,ui->pushButtonCancel->geometry().top());

	ui->tabWidget->resize(width(),height()-ui->frame->height());

	int	ClientWidth	=ui->tabWidget->widget(0)->width();
	int	ClientHeight=ui->tabWidget->widget(0)->height();
	ui->tableWidget			->resize(ClientWidth,ClientHeight);
	ui->tableWidgetBinded	->resize(ClientWidth,ClientHeight);

	::SetColumnWidthInTable(ui->tableWidget ,0, 10);
	::SetColumnWidthInTable(ui->tableWidget ,1, 27);
	::SetColumnWidthInTable(ui->tableWidget ,2, 10);
	::SetColumnWidthInTable(ui->tableWidget ,3, 25);
	::SetColumnWidthInTable(ui->tableWidget ,4, 12);
	::SetColumnWidthInTable(ui->tableWidget ,5, 12);

	::SetColumnWidthInTable(ui->tableWidgetBinded ,0, 30);
	::SetColumnWidthInTable(ui->tableWidgetBinded ,1, 11);
	::SetColumnWidthInTable(ui->tableWidgetBinded ,2, 30);
	::SetColumnWidthInTable(ui->tableWidgetBinded ,3, 12);
	::SetColumnWidthInTable(ui->tableWidgetBinded ,4, 12);
}

void SelectMultiItemsDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}

void SelectMultiItemsDialog::on_tableWidgetBinded_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}


void SelectMultiItemsDialog::on_pushButtonSelect_clicked()
{
	if(ui->tabWidget->currentIndex()==0){
		int	Row=ui->tableWidget->currentRow();
		if(Row<0)
			return;
		Selected=ContainersEachPhase[Row];
		if(Selected==NULL)
			return;
	}
	else{
		int	Row=ui->tableWidgetBinded->currentRow();
		if(Row<0)
			return;
		Selected=ContainersBindedPhase[Row];
		if(Selected==NULL)
			return;
	}
	done(true);
}

void SelectMultiItemsDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
