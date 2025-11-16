#include "RegistLearningDialog.h"
#include "swap.h"
#include "ui_RegistLearningDialog.h"
#include "XLearningRegist.h"
#include "XAlgorithmLibrary.h"

RegistLearningDialog::RegistLearningDialog(LayersBase *base ,int _PointX,int _PointY 
											,int _GlobalX1 ,int _GlobalY1  ,int _GlobalX2 ,int _GlobalY2
											,int _LibType,int _LibID
											,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base)
	,GlobalX1(_GlobalX1) ,GlobalY1(_GlobalY1)
	,GlobalX2(_GlobalX2) ,GlobalY2(_GlobalY2)
	,PointX(_PointX),PointY(_PointY)
    ,ui(new Ui::RegistLearningDialog)
{
    ui->setupUi(this);
	LibType	=_LibType;
	LibID	=_LibID;
}

RegistLearningDialog::~RegistLearningDialog()
{
    delete ui;
}

void RegistLearningDialog::on_pushButtonOK_clicked()
{
	FlexArea	PointArea;
	PointArea.SetRectangle(PointX-1,PointY-1,PointX+1,PointY+1);
	int	Priority=ui->horizontalSliderPriority->value();
	AlgorithmLibraryListContainer	LibList;
	LibList.Merge(GetLayersBase(),LibType,LibID);
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

void RegistLearningDialog::on_pushButtonNG_clicked()
{
	FlexArea	PointArea;
	PointArea.SetRectangle(PointX-1,PointY-1,PointX+1,PointY+1);
	int	Priority=ui->horizontalSliderPriority->value();
	AlgorithmLibraryListContainer	LibList;
	LibList.Merge(GetLayersBase(),LibType,LibID);
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

void RegistLearningDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void RegistLearningDialog::on_horizontalSliderPriority_valueChanged(int value)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	ui->spinBoxPriority->setValue(ui->horizontalSliderPriority->value());
	ReEntrant=false;
}


void RegistLearningDialog::on_spinBoxPriority_valueChanged(int arg1)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	ui->horizontalSliderPriority->setValue(ui->spinBoxPriority->value());
	ReEntrant=false;
}

