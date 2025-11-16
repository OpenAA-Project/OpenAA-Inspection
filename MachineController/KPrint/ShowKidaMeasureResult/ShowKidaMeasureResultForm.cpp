#include "ShowKidaMeasureResultForm.h"
#include "ui_ShowKidaMeasureResultForm.h"
#include "XMeasureLineMove.h"
#include "EasyPropertyDentMeasureForm.h"

ShowKidaMeasureResultForm::ShowKidaMeasureResultForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowKidaMeasureResultForm)
{
    ui->setupUi(this);

	SlaveNoToShow=1;

	for(int i=0;i<sizeof(EasyPropertyDentMeasurePointer)/sizeof(EasyPropertyDentMeasurePointer[0]);i++){
		EasyPropertyDentMeasurePointer[i]=NULL;
	}
	//ui->tableWidget->setColumnWidth(0,150);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowKidaMeasureResultForm::~ShowKidaMeasureResultForm()
{
    delete ui;
}

void	ShowKidaMeasureResultForm::ResizeAction()
{
	ui->tableWidgetW->setColumnWidth(0,width()-80);
	ui->tableWidgetY->setColumnWidth(0,width()-80);
	ui->tableWidgetX->setColumnWidth(0,width()-80);
	ui->tableWidgetR->setColumnWidth(0,width()-80);
}

void	ShowKidaMeasureResultForm::ReadyParam(void)
{
	GUIFormBase *Ret[10];
	int N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyDentMeasure",Ret ,10);
	for(int i=0;i<N;i++){
		EasyPropertyDentMeasureForm		*f=dynamic_cast<EasyPropertyDentMeasureForm	*>(Ret[i]);
		if(f!=NULL && f->SlaveNo>=0 && f->SlaveNo<10){
			EasyPropertyDentMeasurePointer[f->SlaveNo]	=f;
		}
	}
}

void	ShowKidaMeasureResultForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdReqUpdateHistory	*CmdReqUpdateHistoryVar=dynamic_cast<CmdReqUpdateHistory *>(v);
	if(CmdReqUpdateHistoryVar!=NULL){
		ShowData();
		return;
	}
	CmdChangeLotID	*CmdChangeLotIDVar=dynamic_cast<CmdChangeLotID *>(v);
	if(CmdChangeLotIDVar!=NULL){
		SwordListContainer.RemoveAll();
		ShowData();
		return;
	}
	CmdChangeNewLotID	*CmdChangeNewLotIDVar=dynamic_cast<CmdChangeNewLotID *>(v);
	if(CmdChangeNewLotIDVar!=NULL){
		SwordListContainer.RemoveAll();
		ShowData();
		return;
	}
}
struct	MeasureHVInfo	*FindMeasureHVInfo(BladeMeasure &BData
							,bool	bOnlyInside
							,bool	bHorizontal
							,bool	bFrom0
							,bool	bPartnerFrom0
							,int ItemID)
{
	if(0<=ItemID && ItemID<100){
		int	n=ItemID;
		if(n<BData.CountGenDatas){
			if(BData.GenDatas[n].bOnlyInside==bOnlyInside
			&& BData.GenDatas[n].bHorizontal==bHorizontal
			&& BData.GenDatas[n].bFrom0==bFrom0
			&& BData.GenDatas[n].bPartnerFrom0==bPartnerFrom0){
				return &BData.GenDatas[n];
			}
		}
	}
	else
	if(1000<=ItemID && ItemID<2000){
		int	n=ItemID-1000;
		if(n<BData.CountGenDatas){
			if(BData.GenDatas[n].bOnlyInside==bOnlyInside
			&& BData.GenDatas[n].bHorizontal==bHorizontal
			&& BData.GenDatas[n].bFrom0==bFrom0
			&& BData.GenDatas[n].bPartnerFrom0==bPartnerFrom0){
				return &BData.GenDatas[n];
			}
		}
	}

	return NULL;
}
void	ShowKidaMeasureResultForm::ShowData(void)
{
	bool	Added=false;
	for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		int	SlaveNo=m->GetIntegrationSlaveNo();
		InspectionList	*L=m->GetCurrentInspection().GetLast();
		if(L!=NULL){
			for(NGPointInAllPage *Ph=L->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
				for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
					for(NGPoint *p=Pg->NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
						if(p->LibType==DefLibTypeMeasureLineMove){
							bool	Found=false;
							for(SwordList *s=SwordListContainer.GetFirst();s!=NULL;s=s->GetNext()){
								if(s->SlaveNo==SlaveNo && s->ItemID==p->UniqueID){
									s->Refer=p;
									Found	=true;
									break;
								}
							}
							if(Found==false){
								SwordList *ss=new SwordList();
								ss->ItemID	=p->UniqueID;
								ss->SlaveNo	=SlaveNo;
								ss->Refer	=p;
								SwordListContainer.AppendList(ss);
								Added=true;
							}
						}
					}
				}
			}
		}
	}
	/*
	if(Added==true && SwordListContainer.GetCount()>0){
		int	ColumnNumb=SwordListContainer.GetCount();
		ui->tableWidget->setColumnCount(ColumnNumb);
		ui->tableWidget->setVerticalHeaderLabels(Header);

		int	W=(width()-16)/ColumnNumb;
		for(int i=0;i<ColumnNumb;i++){
			ui->tableWidget->setColumnWidth(i,W);
		}
	}
	*/
	int	CenterNumb=0;
	int	Col=0;
	bool	BladeUpsideDown=true;
	for(SwordList *s=SwordListContainer.GetFirst();s!=NULL;s=s->GetNext(),Col++){
		if(s->SlaveNo!=SlaveNoToShow){
			continue;
		}
		EasyPropertyDentMeasureForm	*f=EasyPropertyDentMeasurePointer[s->SlaveNo];
		if(f!=NULL){
			BladeUpsideDown=f->BladeUpsideDown;
			int	Row=0;
			QTableWidget	*Table=NULL;
			if(s->Refer!=NULL && s->Refer->UniqueID<100){
				struct	MeasureHVInfo	*h=FindMeasureHVInfo(f->BladeMeasureData,true,true,true,true,s->Refer->UniqueID);
				if(h!=NULL){
					Table=ui->tableWidgetW;
					if(f->BladeUpsideDown==false){
						Row=0;
					}
					else{
						Row=1;
					}
					goto	GShowList;
				}
			}
			if(s->Refer!=NULL && s->Refer->UniqueID<100){
				struct	MeasureHVInfo	*h=FindMeasureHVInfo(f->BladeMeasureData,true,true,true,false,s->Refer->UniqueID);
				if(h!=NULL){
					Table=ui->tableWidgetW;
					if(f->BladeUpsideDown==false){
						Row=1;
					}
					else{
						Row=0;
					}
					goto	GShowList;
				}
			}
			if(s->Refer!=NULL && s->Refer->UniqueID<100){
				struct	MeasureHVInfo	*h=FindMeasureHVInfo(f->BladeMeasureData,false,true,false,false,s->Refer->UniqueID);
				if(h!=NULL){
					Table=ui->tableWidgetY;
					if(f->BladeUpsideDown==false){
						Row=1;
					}
					else{
						Row=0;
					}
					goto	GShowList;
				}
			}
			if(s->Refer!=NULL && s->Refer->UniqueID<100){
				struct	MeasureHVInfo	*h=FindMeasureHVInfo(f->BladeMeasureData,false,false,true,true,s->Refer->UniqueID);
				if(h!=NULL){
					Table=ui->tableWidgetX;
					if(f->BladeUpsideDown==false){
						Row=0;
					}
					else{
						Row=1;
					}
					goto	GShowList;
				}
			}
			if(s->Refer!=NULL && s->Refer->UniqueID<100){
				struct	MeasureHVInfo	*h=FindMeasureHVInfo(f->BladeMeasureData,false,false,false,true,s->Refer->UniqueID);
				if(h!=NULL){
					Table=ui->tableWidgetX;
					if(f->BladeUpsideDown==false){
						Row=1;
					}
					else{
						Row=0;
					}
					goto	GShowList;
				}
			}
			if(s->Refer!=NULL && 1000<=s->Refer->UniqueID){
				//Pet
				struct	MeasureHVInfo	*h=FindMeasureHVInfo(f->FilmMeasureData,true,false,false,true,s->Refer->UniqueID);
				if(h!=NULL){
					Table=ui->tableWidgetR;
					if(f->BladeUpsideDown==false){
						Row=0;
					}
					else{
						Row=1;
					}
					goto	GShowList;
				}
			}
			if(s->Refer!=NULL && 1000<=s->Refer->UniqueID){
				//Pet
				struct	MeasureHVInfo	*h=FindMeasureHVInfo(f->FilmMeasureData,true,false,false,false,s->Refer->UniqueID);
				if(h!=NULL){
					Table=ui->tableWidgetR;
					if(f->BladeUpsideDown==false){
						Row=1;
					}
					else{
						Row=0;
					}
					goto	GShowList;
				}
			}
GShowList:;
			if(s->Refer!=NULL && Table!=NULL){
				::SetDataToTable(Table ,0,Row ,QString::number(s->Refer->DoubleCause,'f',2));
				if(s->Refer->Error>=2){
					::SetTableColor(Table ,0 ,Row ,Qt::red);
				}
				else{
					::SetTableColor(Table ,0 ,Row ,Qt::white);
				}
			}
		}
	}
	int	MinID=99999999;
	NGPoint	*MinNGPoint=NULL;
	for(SwordList *s=SwordListContainer.GetFirst();s!=NULL;s=s->GetNext(),Col++){
		if(s->SlaveNo!=SlaveNoToShow){
			continue;
		}
		EasyPropertyDentMeasureForm	*f=EasyPropertyDentMeasurePointer[s->SlaveNo];
		if(f!=NULL){
			if(s->Refer!=NULL){
				struct	MeasureHVInfo	*h=FindMeasureHVInfo(f->BladeMeasureData,false,true,false,true,s->Refer->UniqueID);
				if(h!=NULL){
					if(s->Refer->UniqueID<1000 && MinID>s->Refer->UniqueID){
						MinID=s->Refer->UniqueID;
						MinNGPoint=s->Refer;
					}
				}
			}
		}
	}
	if(MinNGPoint!=NULL){
		if(BladeUpsideDown==false){
			::SetDataToTable(ui->tableWidgetY ,0,0 ,QString::number(MinNGPoint->DoubleCause,'f',2));
			if(MinNGPoint->Error>=2){
				::SetTableColor(ui->tableWidgetY ,0 ,0 ,Qt::red);
			}
			else{
				::SetTableColor(ui->tableWidgetY ,0 ,0 ,Qt::white);
			}
			NGPoint	*CNGPoint=NULL;
			for(SwordList *s=SwordListContainer.GetFirst();s!=NULL;s=s->GetNext(),Col++){
				if(s->SlaveNo!=SlaveNoToShow){
					continue;
				}
				EasyPropertyDentMeasureForm	*f=EasyPropertyDentMeasurePointer[s->SlaveNo];
				if(f!=NULL){
					if(s->Refer!=NULL && s->Refer->UniqueID<1000){
						struct	MeasureHVInfo	*h=FindMeasureHVInfo(f->BladeMeasureData,false,true,false,true,s->Refer->UniqueID);
						if(h!=NULL){
							if(MinID!=s->Refer->UniqueID){
								CNGPoint=s->Refer;
								break;
							}
						}
					}
				}
			}
			if(CNGPoint!=NULL){
				::SetDataToTable(ui->tableWidgetY ,0,2 ,QString::number(CNGPoint->DoubleCause,'f',2));
				if(CNGPoint->Error>=2){
					::SetTableColor(ui->tableWidgetY ,0 ,2 ,Qt::red);
				}
				else{
					::SetTableColor(ui->tableWidgetY ,0 ,2 ,Qt::white);
				}
			}
		}
		else{
			::SetDataToTable(ui->tableWidgetY ,0,1 ,QString::number(MinNGPoint->DoubleCause,'f',2));
			if(MinNGPoint->Error>=2){
				::SetTableColor(ui->tableWidgetY ,0 ,1 ,Qt::red);
			}
			else{
				::SetTableColor(ui->tableWidgetY ,0 ,1 ,Qt::white);
			}
			NGPoint	*CNGPoint=NULL;
			for(SwordList *s=SwordListContainer.GetFirst();s!=NULL;s=s->GetNext(),Col++){
				if(s->SlaveNo!=SlaveNoToShow){
					continue;
				}
				EasyPropertyDentMeasureForm	*f=EasyPropertyDentMeasurePointer[s->SlaveNo];
				if(f!=NULL){
					if(s->Refer!=NULL && s->Refer->UniqueID<1000){
						struct	MeasureHVInfo	*h=FindMeasureHVInfo(f->BladeMeasureData,false,true,false,true,s->Refer->UniqueID);
						if(h!=NULL){
							if(MinID!=s->Refer->UniqueID){
								CNGPoint=s->Refer;
								break;
							}
						}
					}
				}
			}
			if(CNGPoint!=NULL){
				::SetDataToTable(ui->tableWidgetY ,0,2 ,QString::number(CNGPoint->DoubleCause,'f',2));
				if(CNGPoint->Error>=2){
					::SetTableColor(ui->tableWidgetY ,0 ,2 ,Qt::red);
				}
				else{
					::SetTableColor(ui->tableWidgetY ,0 ,2 ,Qt::white);
				}
			}
		}
	}
}

