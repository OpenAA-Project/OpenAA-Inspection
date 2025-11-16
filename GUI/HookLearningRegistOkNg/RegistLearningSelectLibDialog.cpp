#include "RegistLearningSelectLibDialog.h"
#include "ui_RegistLearningSelectLibDialog.h"
#include "XLearningRegist.h"
#include "swap.h"
#include "HookLearningRegistOkNg.h"
#include "XGeneralFunc.h"
#include "XRememberer.h"

RegistLearningSelectLibDialog::RegistLearningSelectLibDialog(LayersBase *Base 
                                    ,int _PointX,int _PointY 
									,int _GlobalX1 ,int _GlobalY1 ,int _GlobalX2 ,int _GlobalY2
                                    ,LibIDListWithResultContainer &Container
                                    ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,LibContainer(Container)
	,GlobalX1(_GlobalX1) ,GlobalY1(_GlobalY1)
	,GlobalX2(_GlobalX2) ,GlobalY2(_GlobalY2)
	,PointX(_PointX),PointY(_PointY)
    ,ui(new Ui::RegistLearningSelectLibDialog)
{
    ui->setupUi(this);

    ::SetColumnWidthInTable(ui->tableWidgetSelectLibrary ,0,15);
    ::SetColumnWidthInTable(ui->tableWidgetSelectLibrary ,1,15);
    ::SetColumnWidthInTable(ui->tableWidgetSelectLibrary ,2,50);
    ::SetColumnWidthInTable(ui->tableWidgetSelectLibrary ,3,20);

    ui->tableWidgetSelectLibrary->setRowCount(LibContainer.GetCount());
    int Row=0;
    for(LibIDListWithResult *s=LibContainer.GetFirst();s!=NULL;s=s->GetNext(),Row++){
        ::SetDataToTableCheckable(ui->tableWidgetSelectLibrary, 0, Row, /**/"", false);
        ::SetDataToTable(ui->tableWidgetSelectLibrary, 1, Row, QString::number(s->LibID));
        QString LibName=GetLayersBase()->GetLibraryName(s->LibType,s->LibID);
        ::SetDataToTable(ui->tableWidgetSelectLibrary, 2, Row, LibName);
        if(s->Result==0)
            ::SetDataToTable(ui->tableWidgetSelectLibrary, 3, Row, /**/"None");
        else
        if(s->Result==1)
            ::SetDataToTable(ui->tableWidgetSelectLibrary, 3, Row, /**/"OK");
        else
        if(s->Result>=2)
            ::SetDataToTable(ui->tableWidgetSelectLibrary, 3, Row, /**/"NG");
    }
	ui->horizontalSliderPriority->setValue(ControlRememberer::GetInt(ui->horizontalSliderPriority));
}

RegistLearningSelectLibDialog::~RegistLearningSelectLibDialog()
{
    delete ui;
}

void RegistLearningSelectLibDialog::on_pushButtonOK_clicked()
{
    int Row=0;
    AlgorithmLibraryListContainer	LibList;
    for(LibIDListWithResult *s=LibContainer.GetFirst();s!=NULL;s=s->GetNext(),Row++){
        bool    b=GetCheckedFromTable(ui->tableWidgetSelectLibrary, 0, Row);
        if(b==true){
            LibIDListWithResult *d=new LibIDListWithResult(*s);
            SelectedLibContainer.AppendList(d);
            LibList.Merge(GetLayersBase(),s->LibType,s->LibID);
        }
    }
	FlexArea	PointArea;
	PointArea.SetRectangle(PointX-1,PointY-1,PointX+1,PointY+1);
	int	Priority=ControlRememberer::SetValue(ui->horizontalSliderPriority);
	GetLayersBase()->GetLearningRegister()->RegistForLearning(GlobalX1 ,GlobalY1 ,GlobalX2 ,GlobalY2
						,true
						,LibList
						,Priority
						,PointArea);

	for(int i=0;i<GetLayersBase()->GetShadowChildrenCount();i++){
		ShadowTree	*s=GetLayersBase()->GetShadowChildren(i);
		LayersBase	*Base=s->GetTreeLayersBase();
		FlexArea	PointArea;
		int	LPointX=PointX;
		int	LPointY=PointY;
		s->ConvertToLocal(LPointX,LPointY);
		FlexArea	LPointArea;
		LPointArea.SetRectangle(LPointX-1,LPointY-1,LPointX+1,LPointY+1);

		int	LGlobalX1=GlobalX1;
		int	LGlobalY1=GlobalY1;
		int	LGlobalX2=GlobalX2;
		int	LGlobalY2=GlobalY2;
		s->ConvertToLocal(LGlobalX1,LGlobalY1);
		s->ConvertToLocal(LGlobalX2,LGlobalY2);
		Base->GetLearningRegister()->RegistForLearning(LGlobalX1 ,LGlobalY1 ,LGlobalX2 ,LGlobalY2
							,true
							,LibList
							,Priority
							,LPointArea);
	}

	done(true);
}

void RegistLearningSelectLibDialog::on_pushButtonNG_clicked()
{
    int Row=0;
    AlgorithmLibraryListContainer	LibList;
    for(LibIDListWithResult *s=LibContainer.GetFirst();s!=NULL;s=s->GetNext(),Row++){
        bool    b=GetCheckedFromTable(ui->tableWidgetSelectLibrary, 0, Row);
        if(b==true){
            LibIDListWithResult *d=new LibIDListWithResult(*s);
            SelectedLibContainer.AppendList(d);
            LibList.Merge(GetLayersBase(),s->LibType,s->LibID);
        }
    }
	FlexArea	PointArea;
	PointArea.SetRectangle(PointX-1,PointY-1,PointX+1,PointY+1);
	int	Priority=ControlRememberer::SetValue(ui->horizontalSliderPriority);
	GetLayersBase()->GetLearningRegister()->RegistForLearning(GlobalX1 ,GlobalY1 ,GlobalX2 ,GlobalY2
						,false
						,LibList
						,Priority
						,PointArea);

	for(int i=0;i<GetLayersBase()->GetShadowChildrenCount();i++){
		ShadowTree	*s=GetLayersBase()->GetShadowChildren(i);
		LayersBase	*Base=s->GetTreeLayersBase();
		FlexArea	PointArea;
		int	LPointX=PointX;
		int	LPointY=PointY;
		s->ConvertToLocal(LPointX,LPointY);
		FlexArea	LPointArea;
		LPointArea.SetRectangle(LPointX-1,LPointY-1,LPointX+1,LPointY+1);

		int	LGlobalX1=GlobalX1;
		int	LGlobalY1=GlobalY1;
		int	LGlobalX2=GlobalX2;
		int	LGlobalY2=GlobalY2;
		s->ConvertToLocal(LGlobalX1,LGlobalY1);
		s->ConvertToLocal(LGlobalX2,LGlobalY2);
		Base->GetLearningRegister()->RegistForLearning(LGlobalX1 ,LGlobalY1 ,LGlobalX2 ,LGlobalY2
							,false
							,LibList
							,Priority
							,LPointArea);
	}

	done(true);
}

void RegistLearningSelectLibDialog::on_horizontalSliderPriority_valueChanged(int value)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	ui->spinBoxPriority->setValue(ui->horizontalSliderPriority->value());
	ReEntrant=false;
}

void RegistLearningSelectLibDialog::on_spinBoxPriority_valueChanged(int arg1)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	ui->horizontalSliderPriority->setValue(ui->spinBoxPriority->value());
	ReEntrant=false;
}


void RegistLearningSelectLibDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

