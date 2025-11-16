#include "ShowPieceResultListResource.h"
#include "ShowPieceResultListForm.h"
#include "ui_ShowPieceResultListForm.h"
#include "XShowPieceResultListPacket.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowPieceResultListForm::ShowPieceResultListForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowPieceResultListForm)
{
    ui->setupUi(this);
	ResPointer=NULL;
	ResPointerCount=0;

	ui->tableWidget->setColumnWidth(0,30);
	ui->tableWidget->setColumnWidth(1,120);
	ui->tableWidget->setColumnWidth(2,40);
}

ShowPieceResultListForm::~ShowPieceResultListForm()
{
    delete ui;
}

static	int	ResPointerFuc(const void *a ,const void *b)
{
	ResultPieceList *am=((ResultPieceList **)a)[0];
	ResultPieceList *bm=((ResultPieceList **)b)[0];
	return am->AreaNumber-bm->AreaNumber;
}


void	ShowPieceResultListForm::ShowInPlayer(int64 shownInspectionID)
{
	int64	CurrentInspectionID	=shownInspectionID;
	ResData.RemoveAll();

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqPieceList		CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.ShownInspectionID=CurrentInspectionID;
		GUICmdSendPieceList		CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);
		if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
			for(ResultPieceList *a=CmdAck.ResData.GetFirst();a!=NULL;a=a->GetNext()){
				ResultPieceList *b;
				for(b=ResData.GetFirst();b!=NULL;b=b->GetNext()){
					if(b->AreaNumber==a->AreaNumber){
						if(a->Result==ResultPieceList::_MaxError){
							b->Result=ResultPieceList::_MaxError;
						}
						else if(a->Result==ResultPieceList::_TimeOver){
							b->Result=ResultPieceList::_TimeOver;
						}
						else if(a->Result==ResultPieceList::_Ng){
							b->Result=ResultPieceList::_Ng;
						}
						break;
					}
				}
				if(b==NULL){
					b=new ResultPieceList();
					b->AreaNumber=a->AreaNumber;
					b->AreaName	 =a->AreaName;
					b->Result	=a->Result;
					ResData.AppendList(b);
				}
			}
		}
	}
	int	n=ResData.GetCount();
	if(n!=ResPointerCount){
		ResPointerCount=n;
		if(ResPointer!=NULL){
			delete	[]ResPointer;
		}
		ResPointer=new ResultPieceList*[ResPointerCount];
	}
	int	i=0;
	for(ResultPieceList *a=ResData.GetFirst();a!=NULL;a=a->GetNext()){
		ResPointer[i]=a;
		i++;
	}
	QSort(ResPointer,ResPointerCount,sizeof(ResultPieceList*),ResPointerFuc);
	ui->tableWidget->setRowCount(ResPointerCount);

	for(int Row=0;Row<ResPointerCount;Row++){
		::SetDataToTable(ui->tableWidget,0,Row ,QString::number(ResPointer[Row]->AreaNumber));
		::SetDataToTable(ui->tableWidget,1,Row ,ResPointer[Row]->AreaName);

		QColor	Col;
		if(ResPointer[Row]->Result==ResultPieceList::_MaxError){
			::SetDataToTable(ui->tableWidget,2,Row ,LangSolver.GetString(ShowPieceResultListForm_LS,LID_0)/*"MaxError"*/);
			Col=Qt::yellow;
		}
		else if(ResPointer[Row]->Result==ResultPieceList::_TimeOver){
			::SetDataToTable(ui->tableWidget,2,Row ,LangSolver.GetString(ShowPieceResultListForm_LS,LID_1)/*"TimeOver"*/);
			Col=Qt::yellow;
		}
		else if(ResPointer[Row]->Result==ResultPieceList::_Ng){
			::SetDataToTable(ui->tableWidget,2,Row ,LangSolver.GetString(ShowPieceResultListForm_LS,LID_2)/*"NG"*/);
			Col=Qt::red;
		}
		else if(ResPointer[Row]->Result==ResultPieceList::_Ok){
			::SetDataToTable(ui->tableWidget,2,Row ,LangSolver.GetString(ShowPieceResultListForm_LS,LID_3)/*"OK"*/);
			Col=Qt::white;
		}

		QTableWidgetItem *W;
		W=ui->tableWidget->item ( Row, 0);
		W->setBackground(Col);

		W=ui->tableWidget->item ( Row, 1);
		W->setBackground(Col);

		W=ui->tableWidget->item ( Row, 2);
		W->setBackground(Col);
	}
}

void ShowPieceResultListForm::resizeEvent ( QResizeEvent * event )
{
	ui->tableWidget->resize(width(),height());
}

