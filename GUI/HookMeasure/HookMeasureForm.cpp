#include "HookMeasureForm.h"
#include "ui_HookMeasureForm.h"
#include "XDisplayImagePacket.h"
#include "XCrossObj.h"
#include "swap.h"
#include "SettingMeasureDialog.h"
#include <QMenu>

ItemButton::ItemButton ( QWidget * parent)
	:QToolButton(parent)
{
}

void	ItemButton::mouseReleaseEvent ( QMouseEvent * e )
{
	if(e->button()==Qt::RightButton){
		emit	SignalRightButton();
	}
	QToolButton::mouseReleaseEvent(e);
}

//======================================================================

HookMeasureForm::HookMeasureForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::HookMeasureForm)
	,CurrentData(this),LastLine(this)
{
    ui->setupUi(this);

	SelectionMode	=__S_Addmode;
	CurrentMaxID	=0;

	LineColor	=Qt::green;
	CircleColor	=Qt::red;
	LineWidth	=1;
	CircleSize	=3;
	TextSize	=15;
	ArrowSize	=15;
	CurrentData.Parent=this;
	MoveStep	=0;
	DistanceSelection	=10;
	Active		=true;

	QWidget	*W=ui->stackedWidget	->widget(0);

	delete	ui->toolButtonPoint2Point;
	ui->toolButtonPoint2Point = new ItemButton(W);
	ui->toolButtonPoint2Point->setObjectName(QString::fromUtf8("toolButtonPoint2Point"));
	ui->toolButtonPoint2Point->setGeometry(QRect(0, 0, 42, 42));
	QIcon icon;
	icon.addFile(QString::fromUtf8(":/Resources/Normal/StraightLineN.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon.addFile(QString::fromUtf8(":/Resources/Select/StraightLineS.png"), QSize(), QIcon::Normal, QIcon::On);
	ui->toolButtonPoint2Point->setIcon(icon);
	ui->toolButtonPoint2Point->setIconSize(QSize(48, 48));
	ui->toolButtonPoint2Point->setCheckable(true);
	ui->toolButtonPoint2Point->setAutoExclusive(true);
	ui->toolButtonPoint2Point->setToolTip("<html><head/><body><p>直線</p><p>2点間の距離を測定します</p></body></html>");
	connect(ui->toolButtonPoint2Point ,SIGNAL(clicked()),this,SLOT(on_toolButtonPoint2Point_clicked()));
	connect(((ItemButton *)ui->toolButtonPoint2Point) ,SIGNAL(SignalRightButton()),this,SLOT(SlotRClicked()));

	delete	ui->toolButtonFoldedLines;
	ui->toolButtonFoldedLines = new ItemButton(W);
	ui->toolButtonFoldedLines->setObjectName(QString::fromUtf8("toolButtonFoldedLines"));
	ui->toolButtonFoldedLines->setGeometry(QRect(45, 0, 42, 42));
	QIcon icon1;
	icon1.addFile(QString::fromUtf8(":/Resources/Normal/BrokenLineN.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon1.addFile(QString::fromUtf8(":/Resources/Select/BrokenLineS.png"), QSize(), QIcon::Normal, QIcon::On);
	ui->toolButtonFoldedLines->setIcon(icon1);
	ui->toolButtonFoldedLines->setIconSize(QSize(48, 48));
	ui->toolButtonFoldedLines->setCheckable(true);
	ui->toolButtonFoldedLines->setAutoExclusive(true);
	ui->toolButtonFoldedLines->setToolTip("<html><head/><body><p>折れ線</p><p>複数点の距離を測定します</p></body></html>");
	connect(ui->toolButtonFoldedLines ,SIGNAL(clicked()),this,SLOT(on_toolButtonFoldedLines_clicked()));
	connect(((ItemButton *)ui->toolButtonFoldedLines) ,SIGNAL(SignalRightButton()),this,SLOT(SlotRClicked()));

	delete	ui->toolButtonCenterCircle;
	ui->toolButtonCenterCircle = new ItemButton(W);
	ui->toolButtonCenterCircle->setObjectName(QString::fromUtf8("toolButtonCenterCircle"));
	ui->toolButtonCenterCircle->setGeometry(QRect(90, 0, 42, 42));
	QIcon icon2;
	icon2.addFile(QString::fromUtf8(":/Resources/Normal/CircleTwoPointsN.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon2.addFile(QString::fromUtf8(":/Resources/Select/CircleTwoPointsS.png"), QSize(), QIcon::Normal, QIcon::On);
	ui->toolButtonCenterCircle->setIcon(icon2);
	ui->toolButtonCenterCircle->setIconSize(QSize(48, 48));
	ui->toolButtonCenterCircle->setCheckable(true);
	ui->toolButtonCenterCircle->setAutoExclusive(true);
	ui->toolButtonCenterCircle->setToolTip("<html><head/><body><p>円心2点間距離</p><p>2つの円心間の距離、円の半径、円周、面積を測定します</p></body></html>");
	connect(ui->toolButtonCenterCircle ,SIGNAL(clicked()),this,SLOT(on_toolButtonCenterCircle_clicked()));
	connect(((ItemButton *)ui->toolButtonCenterCircle) ,SIGNAL(SignalRightButton()),this,SLOT(SlotRClicked()));

	delete	ui->toolButtonArc;
	ui->toolButtonArc = new ItemButton(W);
	ui->toolButtonArc->setObjectName(QString::fromUtf8("toolButtonArc"));
	ui->toolButtonArc->setGeometry(QRect(135, 0, 42, 42));
	QIcon icon3;
	icon3.addFile(QString::fromUtf8(":/Resources/Normal/CrcularArcN.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon3.addFile(QString::fromUtf8(":/Resources/Select/CrcularArcS.png"), QSize(), QIcon::Normal, QIcon::On);
	ui->toolButtonArc->setIcon(icon3);
	ui->toolButtonArc->setIconSize(QSize(48, 48));
	ui->toolButtonArc->setCheckable(true);
	ui->toolButtonArc->setAutoExclusive(true);
	ui->toolButtonArc->setToolTip("<html><head/><body><p>円弧</p><p>円弧の長さ、半径、角度、面積を測定します</p></body></html>");
	connect(ui->toolButtonArc ,SIGNAL(clicked()),this,SLOT(on_toolButtonArc_clicked()));
	connect(((ItemButton *)ui->toolButtonArc) ,SIGNAL(SignalRightButton()),this,SLOT(SlotRClicked()));

	delete	ui->toolButtonAngle;
	ui->toolButtonAngle = new ItemButton(W);
	ui->toolButtonAngle->setObjectName(QString::fromUtf8("toolButtonAngle"));
	ui->toolButtonAngle->setGeometry(QRect(180, 0, 42, 42));
	QIcon icon6;
	icon6.addFile(QString::fromUtf8(":/Resources/Normal/AngleN.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon6.addFile(QString::fromUtf8(":/Resources/Select/AngleS.png"), QSize(), QIcon::Normal, QIcon::On);
	ui->toolButtonAngle->setIcon(icon6);
	ui->toolButtonAngle->setIconSize(QSize(48, 48));
	ui->toolButtonAngle->setCheckable(true);
	ui->toolButtonAngle->setAutoExclusive(true);
	ui->toolButtonAngle->setToolTip("<html><head/><body><p>角度</p><p>角度を測定します</p></body></html>");
	connect(ui->toolButtonAngle ,SIGNAL(clicked()),this,SLOT(on_toolButtonAngle_clicked()));
	connect(((ItemButton *)ui->toolButtonAngle) ,SIGNAL(SignalRightButton()),this,SLOT(SlotRClicked()));

	delete	ui->toolButtonRectangle;
	ui->toolButtonRectangle = new ItemButton(W);
	ui->toolButtonRectangle->setObjectName(QString::fromUtf8("toolButtonRectangle"));
	ui->toolButtonRectangle->setGeometry(QRect(225, 0, 42, 42));
	QIcon icon4;
	icon4.addFile(QString::fromUtf8(":/Resources/Normal/RectangleN.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon4.addFile(QString::fromUtf8(":/Resources/Select/RectangleS.png"), QSize(), QIcon::Normal, QIcon::On);
	ui->toolButtonRectangle->setIcon(icon4);
	ui->toolButtonRectangle->setIconSize(QSize(48, 48));
	ui->toolButtonRectangle->setCheckable(true);
	ui->toolButtonRectangle->setAutoExclusive(true);
	ui->toolButtonRectangle->setToolTip("<html><head/><body><p>長方形</p><p>長方形の長さ（縦・横）・周長・面積を測定します</p></body></html>");
	connect(ui->toolButtonRectangle ,SIGNAL(clicked()),this,SLOT(on_toolButtonRectangle_clicked()));
	connect(((ItemButton *)ui->toolButtonRectangle) ,SIGNAL(SignalRightButton()),this,SLOT(SlotRClicked()));

	delete	ui->toolButtonPolyLine;
	ui->toolButtonPolyLine = new ItemButton(W);
	ui->toolButtonPolyLine->setObjectName(QString::fromUtf8("toolButtonPolyLine"));
	ui->toolButtonPolyLine->setGeometry(QRect(270, 0, 42, 42));
	QIcon icon5;
	icon5.addFile(QString::fromUtf8(":/Resources/Normal/MPolygonN.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon5.addFile(QString::fromUtf8(":/Resources/Select/MPolygonS.png"), QSize(), QIcon::Normal, QIcon::On);
	ui->toolButtonPolyLine->setIcon(icon5);
	ui->toolButtonPolyLine->setIconSize(QSize(48, 48));
	ui->toolButtonPolyLine->setCheckable(true);
	ui->toolButtonPolyLine->setAutoExclusive(true);
	ui->toolButtonPolyLine->setToolTip("<html><head/><body><p>多角形</p><p>多角形の円周・面積を測定します</p></body></html>");
	connect(ui->toolButtonPolyLine ,SIGNAL(clicked()),this,SLOT(on_toolButtonPolyLine_clicked()));
	connect(((ItemButton *)ui->toolButtonPolyLine) ,SIGNAL(SignalRightButton()),this,SLOT(SlotRClicked()));

	delete	ui->toolButtonCircle;
	ui->toolButtonCircle = new ItemButton(W);
	ui->toolButtonCircle->setObjectName(QString::fromUtf8("toolButtonCircle"));
	ui->toolButtonCircle->setGeometry(QRect(315, 0, 42, 42));
	QIcon icon7;
	icon7.addFile(QString::fromUtf8(":/Resources/Normal/Circle1N.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon7.addFile(QString::fromUtf8(":/Resources/Select/Circle1S.png"), QSize(), QIcon::Normal, QIcon::On);
	ui->toolButtonCircle->setIcon(icon7);
	ui->toolButtonCircle->setIconSize(QSize(48, 48));
	ui->toolButtonCircle->setCheckable(true);
	ui->toolButtonCircle->setAutoExclusive(true);
	ui->toolButtonCircle->setToolTip("<html><head/><body><p>円①</p><p>円の半径・円周・面積を測定します（直径２点）</p></body></html>");
	connect(ui->toolButtonCircle ,SIGNAL(clicked()),this,SLOT(on_toolButtonCircle_clicked()));
	connect(((ItemButton *)ui->toolButtonCircle) ,SIGNAL(SignalRightButton()),this,SLOT(SlotRClicked()));

	delete	ui->toolButtonCircle3;
	ui->toolButtonCircle3 = new ItemButton(W);
	ui->toolButtonCircle3->setObjectName(QString::fromUtf8("toolButtonCircle3"));
	ui->toolButtonCircle3->setGeometry(QRect(360, 0, 42, 42));
	QIcon icon9;
	icon9.addFile(QString::fromUtf8(":/Resources/Normal/Circle2N.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon9.addFile(QString::fromUtf8(":/Resources/Select/Circle2S.png"), QSize(), QIcon::Normal, QIcon::On);
	ui->toolButtonCircle3->setIcon(icon9);
	ui->toolButtonCircle3->setIconSize(QSize(48, 48));
	ui->toolButtonCircle3->setCheckable(true);
	ui->toolButtonCircle3->setAutoExclusive(true);
	ui->toolButtonCircle3->setToolTip("<html><head/><body><p>円②</p><p>円の半径・円周・面積を測定します（円周３点）</p></body></html>");
	connect(ui->toolButtonCircle3 ,SIGNAL(clicked()),this,SLOT(on_toolButtonCircle3_clicked()));
	connect(((ItemButton *)ui->toolButtonCircle3) ,SIGNAL(SignalRightButton()),this,SLOT(SlotRClicked()));

	delete	ui->toolButtonIsolation;
	ui->toolButtonIsolation = new ItemButton(W);
	ui->toolButtonIsolation->setObjectName(QString::fromUtf8("toolButtonIsolation"));
	ui->toolButtonIsolation->setGeometry(QRect(405, 0, 42, 42));
	QIcon icon8;
	icon8.addFile(QString::fromUtf8(":/Resources/Normal/ParallelLinesN.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon8.addFile(QString::fromUtf8(":/Resources/Select/ParallelLinesS.png"), QSize(), QIcon::Normal, QIcon::On);
	ui->toolButtonIsolation->setIcon(icon8);
	ui->toolButtonIsolation->setIconSize(QSize(48, 48));
	ui->toolButtonIsolation->setCheckable(true);
	ui->toolButtonIsolation->setAutoExclusive(true);
	ui->toolButtonIsolation->setToolTip("<html><head/><body><p>平行線距離</p><p>平行線の距離を測定します</p></body></html>");
	connect(ui->toolButtonIsolation ,SIGNAL(clicked()),this,SLOT(on_toolButtonIsolation_clicked()));
	connect(((ItemButton *)ui->toolButtonIsolation) ,SIGNAL(SignalRightButton()),this,SLOT(SlotRClicked()));

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	ui->stackedWidget	->setCurrentIndex(0);
}

HookMeasureForm::~HookMeasureForm()
{
    delete ui;
}
void	HookMeasureForm::ResizeAction()
{
}
static	bool TargetFunctionMouseLClick(FunctionServerClass *Obj,GUIFormBase *TargetObj,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		HookMeasureForm	*Form=dynamic_cast<HookMeasureForm *>(Obj);
		if(Form!=NULL && DImage->GetTargetPage()==Form->GetTargetPage()){
			if(Form->SelectionMode==HookMeasureForm::__S_SelectMode){
				if(Form->EditSelection(DImage,GlobalPosX,GlobalPosY,DImage->GetZoomRate())==true){
					Form->SelectionMode=HookMeasureForm::__S_ModifyMode;
					Form->Active=true;
					return false;
				}
			}
			else if(Form->SelectionMode==HookMeasureForm::__S_ModifyMode){
				HookMeasureForm::MeasuredList *a=Form->GetModified();
				if(a==NULL){
					if(Form->EditModification(DImage,GlobalPosX,GlobalPosY,DImage->GetZoomRate())==true){
						Form->SelectionMode=HookMeasureForm::__S_ModifyMode;
						Form->Active=true;
						return false;
					}
					else {
						if (Form->EditSelection(DImage, GlobalPosX, GlobalPosY, DImage->GetZoomRate()) == true) {
							Form->SelectionMode = HookMeasureForm::__S_ModifyMode;
							Form->Active = true;
							return false;
						}
					}
				}
				else{
					Form->MouseLClickModification(a,GlobalPosX,GlobalPosY);
					//Form->SelectionMode=HookMeasureForm::__S_SelectMode;
					return false;
				}
			}
			else if(Form->SelectionMode==HookMeasureForm::__S_DeleteMode){
				if(Form->DeleteSelection(DImage,GlobalPosX,GlobalPosY,DImage->GetZoomRate())==true){
					return false;
				}
			}
			else if(Form->SelectionMode==HookMeasureForm::__S_MoveMode){
				if(Form->MoveStep==1){
					if (Form->GetSelectedCount() > 0) {
						Form->GlobalMovX1 = GlobalPosX;
						Form->GlobalMovY1 = GlobalPosY;
						Form->GlobalMovX2 = GlobalPosX;
						Form->GlobalMovY2 = GlobalPosY;
						Form->MoveStep = 2;
						return false;
					}
					else
					if(Form->EditMove(DImage,GlobalPosX,GlobalPosY,DImage->GetZoomRate())==true){
						Form->GlobalMovX1	=GlobalPosX;
						Form->GlobalMovY1	=GlobalPosY;
						Form->GlobalMovX2	=GlobalPosX;
						Form->GlobalMovY2	=GlobalPosY;
						Form->MoveStep=2;
						return false;
					}
				}
				else if(Form->MoveStep==2){
					Form->GlobalMovX2	=GlobalPosX;
					Form->GlobalMovY2	=GlobalPosY;
					Form->MoveItems(Form->GlobalMovX2-Form->GlobalMovX1,Form->GlobalMovY2-Form->GlobalMovY1);
					Form->GlobalMovX1	=GlobalPosX;
					Form->GlobalMovY1	=GlobalPosY;
					Form->FinishAllMoveMode();
					Form->MoveStep=1;
					return false;
				}
			}
			else if(Form->IsModeEnable()==true){
				//if(Form->Active==true){
					if(Form->SelectionMode==HookMeasureForm::__S_ModifyMode){
						Form->MouseLClick(GlobalPosX,GlobalPosY);
						Form->SelectionMode=HookMeasureForm::__S_SelectMode;
						return false;
					}
					else{
						Form->MouseLClick(GlobalPosX,GlobalPosY);
						return false;
					}
				//}
			}
		}
	}
	return true;
}

static	bool TargetFunctionMouseLClickWithShift(FunctionServerClass *Obj,GUIFormBase *TargetObj,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		HookMeasureForm	*Form=dynamic_cast<HookMeasureForm *>(Obj);
		if(Form!=NULL && DImage->GetTargetPage()==Form->GetTargetPage()){
			if(Form->SelectionMode==HookMeasureForm::__S_MoveMode){
				if(Form->MoveStep==2){				
					if(Form->EditMove(DImage,GlobalPosX,GlobalPosY,DImage->GetZoomRate())==true){
						Form->GlobalMovX1	=GlobalPosX;
						Form->GlobalMovY1	=GlobalPosY;
						Form->GlobalMovX2	=GlobalPosX;
						Form->GlobalMovY2	=GlobalPosY;
						Form->MoveStep=2;
						return false;
					}
				}
			}
		}
	}
	return true;
}
static	bool TargetFunctionMouseLDblClick(FunctionServerClass *Obj,GUIFormBase *TargetObj,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		HookMeasureForm	*Form=dynamic_cast<HookMeasureForm *>(Obj);
		if(Form!=NULL && DImage->GetTargetPage()==Form->GetTargetPage()){
			if(Form->IsModeEnable()==true){
				Form->MouseLDblClick(GlobalPosX,GlobalPosY);
				return false;
			}
			else{
				HookMeasureForm::MeasuredList	*m=Form->GetModified();
				if(m!=NULL){
					Form->MouseLDblClickForModification(m);
					return false;
				}
			}
		}
	}
	return true;
}
static	bool TargetFunctionMouseRClick(FunctionServerClass *Obj,GUIFormBase *TargetObj,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		HookMeasureForm	*Form=dynamic_cast<HookMeasureForm *>(Obj);
		if(Form!=NULL && DImage->GetTargetPage()==Form->GetTargetPage()){
			if(Form->SelectionMode==HookMeasureForm::__S_MoveMode){
				Form->ReleaseAllMoveMode();
				Form->MoveStep=1;
				return true;
			}
			else if(Form->SelectionMode==HookMeasureForm::__S_SelectMode){
				Form->ReleaseAllSelectMode();
				Form->MoveStep=0;
				return true;
			}
			else if(Form->SelectionMode==HookMeasureForm::__S_ModifyMode){
				HookMeasureForm::MeasuredList *a=Form->GetModified();
				if(a!=NULL){
					Form->MouseRClickModification(a,GlobalPosX,GlobalPosY);
					return false;
				}
				else{
					Form->ReleaseAllSelectMode();
					Form->MoveStep=0;
					return true;
				}
			}
			else if(Form->IsModeEnable()==true){
				{
					HookMeasureForm::MeasuredList *a=Form->GetModified();
					if(a!=NULL){
						Form->ReleaseAllSelectMode();
						Form->MoveStep=0;
						return false;
					}
				}
				{
					HookMeasureForm::MeasuredList *a=Form->GetSelected();
					if(a!=NULL){
						Form->ReleaseAllSelectMode();
						Form->MoveStep=0;
						return false;
					}
				}
				//if(Form->Active==true){
					Form->MouseRClick(GlobalPosX,GlobalPosY);
					return false;
				//}
			}
		}
	}
	return true;
}
static	bool TargetFunctionMouseMove(FunctionServerClass *Obj,GUIFormBase *TargetObj,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		HookMeasureForm	*Form=dynamic_cast<HookMeasureForm *>(Obj);
		if(Form!=NULL && DImage->GetTargetPage()==Form->GetTargetPage()){
			if(Form->SelectionMode==HookMeasureForm::__S_MoveMode){
				if(Form->MoveStep==2){
					Form->GlobalMovX2	=GlobalPosX;
					Form->GlobalMovY2	=GlobalPosY;
					return false;
				}
			}
			else if(Form->SelectionMode==HookMeasureForm::__S_ModifyMode){
				HookMeasureForm::MeasuredList *a=Form->GetModified();
				if(a!=NULL){
					if(Form->MouseModify(a,GlobalPosX,GlobalPosY)==true){
						return false;
					}
				}
			}
			if(Form->IsModeEnable()==true){
				if(Form->MouseMove(GlobalPosX,GlobalPosY)==true){
					return false;
				}
			}
		}
	}
	return true;
}
static	bool TargetFunctionPaintLast(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL && DImage->IsShown()==true){
		HookMeasureForm	*Form=dynamic_cast<HookMeasureForm *>(Obj);
		if(Form!=NULL && DImage->GetTargetPage()==Form->GetTargetPage()){
			DImage->LockPaintMutex();
			if(Form->GetLayersBase()->TryLockWeakDraw()==true){
				Form->Draw(pnt,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());
				Form->GetLayersBase()->UnlockWeakDraw();
			}
			DImage->UnlockPaintMutex();
		}
	}
	return true;
}

void	HookMeasureForm::ReadyParam(void)
{
	for(int i=0;i<HookTargetListInst.count();i++){
		QString	HookedPanelName=HookTargetListInst[i];
		DisplayImage *TargetPanel=dynamic_cast<DisplayImage *>(GetLayersBase()->FindByName(HookedPanelName));
		if(TargetPanel!=NULL){
			TargetPanels.Add(TargetPanel);

			TargetPanel->SetHookInMouseLClick			(this,TargetFunctionMouseLClick);
			TargetPanel->SetHookInMouseLClickWithShift	(this,TargetFunctionMouseLClickWithShift);
			TargetPanel->SetHookInMouseRClick			(this,TargetFunctionMouseRClick);
			TargetPanel->SetHookInMouseLDoubleClick		(this,TargetFunctionMouseLDblClick);

			TargetPanel->SetHookInMouseMove				(this,TargetFunctionMouseMove);
			TargetPanel->SetHookInPaintLast				(this,TargetFunctionPaintLast);

			connect(TargetPanel,SIGNAL(SignalReleaseAllSelection()),this,SLOT(SlotReleaseAllSelection()));
		}
	}
}
bool	HookMeasureForm::IsModeEnable(void)
{
	if(isHidden()==true)
		return false;
	if(ui->toolButtonPoint2Point->isChecked()==true
	|| ui->toolButtonFoldedLines->isChecked()==true
	|| ui->toolButtonCenterCircle->isChecked()==true
	|| ui->toolButtonArc->isChecked()==true
	|| ui->toolButtonAngle->isChecked()==true
	|| ui->toolButtonRectangle->isChecked()==true
	|| ui->toolButtonPolyLine->isChecked()==true
	|| ui->toolButtonCircle->isChecked()==true
	|| ui->toolButtonCircle3->isChecked()==true
	|| ui->toolButtonIsolation->isChecked()==true){
		return true;
	}
	return false;
}

void HookMeasureForm::showEvent ( QShowEvent * event )
{
	ui->toolButtonPoint2Point->setChecked(true);
	on_toolButtonPoint2Point_clicked();
}

void	HookMeasureForm::MouseLClick(int GlobalPosX,int GlobalPosY)
{
	CurrentData.LineColor	=LineColor	;
	CurrentData.CircleColor	=CircleColor;	
	CurrentData.LineWidth	=LineWidth	;
	CurrentData.ArrowSize	=ArrowSize	;
	CurrentData.LineType	=LineType	;	
	if(ui->toolButtonPoint2Point->isChecked()==true){
		if(CurrentData.Step==0){
			CurrentData.P2PA.setX(GlobalPosX);
			CurrentData.P2PA.setY(GlobalPosY);
			CurrentData.Step=1;
		}
		else{
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			CurrentData.Step=2;
			MeasuredList	*m=new MeasuredList(this,CurrentData);
			m->ID=CurrentMaxID++;
			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			MeasuredData.AppendList(m);
			CurrentData.Step=0;

			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,&HookMeasureForm::UndoAddItem,&HookMeasureForm::RedoAddItem);
			int32	ClassType=(int)m->Action;
			::Save(UPointer->GetWritePointer(),ClassType);
			m->Save(UPointer->GetWritePointer());			
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
	else if(ui->toolButtonFoldedLines->isChecked()==true){
		QPoint	P(GlobalPosX,GlobalPosY);
		if (CurrentData.PN.count() == 0) {
			CurrentData.PN << P;
		}
		CurrentData.PN << P;
		CurrentData.Step=1;
		Active = true;
	}
	else if(ui->toolButtonArc->isChecked()==true){
		if(CurrentData.Step==0){
			CurrentData.P2PA.setX(GlobalPosX);
			CurrentData.P2PA.setY(GlobalPosY);
			CurrentData.Step=1;
		}
		else if(CurrentData.Step==1){
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			CurrentData.Step=2;
		}
		else if(CurrentData.Step==2){
			CurrentData.P2PC.setX(GlobalPosX);
			CurrentData.P2PC.setY(GlobalPosY);
			CurrentData.Step=3;

			MeasuredList	*m=new MeasuredList(this,CurrentData);
			m->ID=CurrentMaxID++;
			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			MeasuredData.AppendList(m);
			CurrentData.Step=0;

			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,&HookMeasureForm::UndoAddItem,&HookMeasureForm::RedoAddItem);
			int32	ClassType=(int)m->Action;
			::Save(UPointer->GetWritePointer(),ClassType);
			m->Save(UPointer->GetWritePointer());			
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
	else if(ui->toolButtonAngle->isChecked()==true){
		if(CurrentData.Step==0){
			CurrentData.P2PA.setX(GlobalPosX);
			CurrentData.P2PA.setY(GlobalPosY);
			CurrentData.Step=1;
		}
		else if(CurrentData.Step==1){
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			CurrentData.Step=2;
		}
		else if(CurrentData.Step==2){
			CurrentData.P2PC.setX(GlobalPosX);
			CurrentData.P2PC.setY(GlobalPosY);
			CurrentData.Step=3;
		}
		else{
			CurrentData.P2PD.setX(GlobalPosX);
			CurrentData.P2PD.setY(GlobalPosY);
			CurrentData.Step=4;

			MeasuredList	*m=new MeasuredList(this,CurrentData);
			m->ID=CurrentMaxID++;
			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			MeasuredData.AppendList(m);
			CurrentData.Step=0;

			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,&HookMeasureForm::UndoAddItem,&HookMeasureForm::RedoAddItem);
			int32	ClassType=(int)m->Action;
			::Save(UPointer->GetWritePointer(),ClassType);
			m->Save(UPointer->GetWritePointer());			
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
	else if(ui->toolButtonRectangle->isChecked()==true){
		if(CurrentData.Step==0){
			CurrentData.P2PA.setX(GlobalPosX);
			CurrentData.P2PA.setY(GlobalPosY);
			CurrentData.Step=1;
		}
		else{
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			CurrentData.Step=2;

			MeasuredList	*m=new MeasuredList(this,CurrentData);
			m->ID=CurrentMaxID++;
			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			MeasuredData.AppendList(m);
			CurrentData.Step=0;

			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,&HookMeasureForm::UndoAddItem,&HookMeasureForm::RedoAddItem);
			int32	ClassType=(int)m->Action;
			::Save(UPointer->GetWritePointer(),ClassType);
			m->Save(UPointer->GetWritePointer());			
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
	else if(ui->toolButtonPolyLine->isChecked()==true){
		QPoint	P(GlobalPosX,GlobalPosY);
		if (CurrentData.PN.count() == 0) {
			CurrentData.PN << P;
		}
		CurrentData.PN<<P;
		CurrentData.Step=1;
		Active = true;
	}
	else if(ui->toolButtonCircle->isChecked()==true){
		if(CurrentData.Step==0){
			CurrentData.P2PA.setX(GlobalPosX);
			CurrentData.P2PA.setY(GlobalPosY);
			CurrentData.Step=1;
		}
		else{
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			CurrentData.Step=2;

			MeasuredList	*m=new MeasuredList(this,CurrentData);
			m->ID=CurrentMaxID++;
			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			MeasuredData.AppendList(m);
			CurrentData.Step=0;

			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,&HookMeasureForm::UndoAddItem,&HookMeasureForm::RedoAddItem);
			int32	ClassType=(int)m->Action;
			::Save(UPointer->GetWritePointer(),ClassType);
			m->Save(UPointer->GetWritePointer());			
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
	else if(ui->toolButtonCircle3->isChecked()==true){
		if(CurrentData.Step==0){
			CurrentData.P2PA.setX(GlobalPosX);
			CurrentData.P2PA.setY(GlobalPosY);
			CurrentData.Step=1;
		}
		else if(CurrentData.Step==1){
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			CurrentData.Step=2;
		}
		else{
			CurrentData.P2PC.setX(GlobalPosX);
			CurrentData.P2PC.setY(GlobalPosY);
			CurrentData.Step=3;

			MeasuredList	*m=new MeasuredList(this,CurrentData);
			m->ID=CurrentMaxID++;
			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			MeasuredData.AppendList(m);
			CurrentData.Step=0;

			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,&HookMeasureForm::UndoAddItem,&HookMeasureForm::RedoAddItem);
			int32	ClassType=(int)m->Action;
			::Save(UPointer->GetWritePointer(),ClassType);
			m->Save(UPointer->GetWritePointer());			
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
	else if(ui->toolButtonCenterCircle->isChecked()==true){
		if(CurrentData.Step==0){
			CurrentData.P2PA.setX(GlobalPosX);
			CurrentData.P2PA.setY(GlobalPosY);
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			CurrentData.P2PD.setX(GlobalPosX);
			CurrentData.P2PD.setY(GlobalPosY);
			CurrentData.P2PE.setX(GlobalPosX);
			CurrentData.P2PE.setY(GlobalPosY);
			CurrentData.P2PF.setX(GlobalPosX);
			CurrentData.P2PF.setY(GlobalPosY);
			CurrentData.Step=1;
		}
		else if(CurrentData.Step==1){
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			CurrentData.Step=2;
		}
		else  if(CurrentData.Step==2){
			CurrentData.P2PC.setX(GlobalPosX);
			CurrentData.P2PC.setY(GlobalPosY);
			CurrentData.Step=3;
		}
		else if(CurrentData.Step==3){
			CurrentData.P2PD.setX(GlobalPosX);
			CurrentData.P2PD.setY(GlobalPosY);
			CurrentData.P2PE.setX(GlobalPosX);
			CurrentData.P2PE.setY(GlobalPosY);
			CurrentData.P2PF.setX(GlobalPosX);
			CurrentData.P2PF.setY(GlobalPosY);
			CurrentData.Step=4;
		}
		else if(CurrentData.Step==4){
			CurrentData.P2PE.setX(GlobalPosX);
			CurrentData.P2PE.setY(GlobalPosY);
			CurrentData.Step=5;
		}
		else {
			CurrentData.P2PF.setX(GlobalPosX);
			CurrentData.P2PF.setY(GlobalPosY);
			CurrentData.Step=6;
		
			MeasuredList	*m=new MeasuredList(this,CurrentData);
			m->ID=CurrentMaxID++;
			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			MeasuredData.AppendList(m);
			CurrentData.Step=0;

			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,&HookMeasureForm::UndoAddItem,&HookMeasureForm::RedoAddItem);
			int32	ClassType=(int)m->Action;
			::Save(UPointer->GetWritePointer(),ClassType);
			m->Save(UPointer->GetWritePointer());			
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
	else if(ui->toolButtonIsolation->isChecked()==true){
		if(CurrentData.Step==0){
			CurrentData.P2PA.setX(GlobalPosX);
			CurrentData.P2PA.setY(GlobalPosY);
			CurrentData.Step=1;
		}
		else if(CurrentData.Step==1){
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			CurrentData.Step=2;
		}
		else if(CurrentData.Step==2){
			CurrentData.P2PC.setX(GlobalPosX);
			CurrentData.P2PC.setY(GlobalPosY);
			CurrentData.Step=3;

			MeasuredList	*m=new MeasuredList(this,CurrentData);
			m->ID=CurrentMaxID++;
			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			MeasuredData.AppendList(m);
			CurrentData.Step=0;

			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,&HookMeasureForm::UndoAddItem,&HookMeasureForm::RedoAddItem);
			int32	ClassType=(int)m->Action;
			::Save(UPointer->GetWritePointer(),ClassType);
			m->Save(UPointer->GetWritePointer());			
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
}

void	HookMeasureForm::MouseLClickModification(HookMeasureForm::MeasuredList *m ,int GlobalPosX,int GlobalPosY)
{
	m->LineColor	=LineColor	;
	m->CircleColor	=CircleColor;	
	m->LineWidth	=LineWidth	;
	m->ArrowSize	=ArrowSize	;
	m->LineType		=LineType	;	
	if(ui->toolButtonPoint2Point->isChecked()==true){
		//if(m->Step==0){
		//	m->P2PA.setX(GlobalPosX);
		//	m->P2PA.setY(GlobalPosY);
		//	m->Step=1;
		//}
		//else
		if(m->Step>0){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			m->Step=2;

			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			m->Status		=MeasuredList::_MLA_Selected;
			SelectionMode	=HookMeasureForm::__S_SelectMode;

			//GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			//UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,HookMeasureForm::UndoAddItem,HookMeasureForm::RedoAddItem);
			//int32	ClassType=(int)m->Action;
			//::Save(UPointer->GetWritePointer(),ClassType);
			//m->Save(UPointer->GetWritePointer());			
			//GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			//emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
	else if(ui->toolButtonFoldedLines->isChecked()==true){
		if(m->PN.count()>1){
			QPoint	P(GlobalPosX,GlobalPosY);
			m->PN<<P;
			m->Step=1;
		}
	}
	else if(ui->toolButtonArc->isChecked()==true){
		//if(m->Step==0){
		//	m->P2PA.setX(GlobalPosX);
		//	m->P2PA.setY(GlobalPosY);
		//	m->Step=1;
		//}
		//else 
		if(m->Step==1){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			m->Step=2;
		}
		else if(m->Step==2){
			m->P2PC.setX(GlobalPosX);
			m->P2PC.setY(GlobalPosY);
			m->Step=3;

			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			m->Status		=MeasuredList::_MLA_Selected;
			SelectionMode	=HookMeasureForm::__S_SelectMode;

			//GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			//UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,HookMeasureForm::UndoAddItem,HookMeasureForm::RedoAddItem);
			//int32	ClassType=(int)m->Action;
			//::Save(UPointer->GetWritePointer(),ClassType);
			//m->Save(UPointer->GetWritePointer());			
			//GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			//emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
	else if(ui->toolButtonAngle->isChecked()==true){
		//if(m->Step==0){
		//	m->P2PA.setX(GlobalPosX);
		//	m->P2PA.setY(GlobalPosY);
		//	m->Step=1;
		//}
		//else
		if(m->Step==1){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			m->Step=2;
		}
		else if(m->Step==2){
			m->P2PC.setX(GlobalPosX);
			m->P2PC.setY(GlobalPosY);
			m->Step=3;
		}
		else if(m->Step>2){
			m->P2PD.setX(GlobalPosX);
			m->P2PD.setY(GlobalPosY);
			m->Step=4;

			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			m->Status		=MeasuredList::_MLA_Selected;
			SelectionMode	=HookMeasureForm::__S_SelectMode;

			//GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			//UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,HookMeasureForm::UndoAddItem,HookMeasureForm::RedoAddItem);
			//int32	ClassType=(int)m->Action;
			//::Save(UPointer->GetWritePointer(),ClassType);
			//m->Save(UPointer->GetWritePointer());			
			//GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			//emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
	else if(ui->toolButtonRectangle->isChecked()==true){
		//if(m->Step==0){
		//	m->P2PA.setX(GlobalPosX);
		//	m->P2PA.setY(GlobalPosY);
		//	m->Step=1;
		//}
		//else
		if(m->Step>0){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			m->Step=2;

			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			m->Status		=MeasuredList::_MLA_Selected;
			SelectionMode	=HookMeasureForm::__S_SelectMode;

			//GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			//UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,HookMeasureForm::UndoAddItem,HookMeasureForm::RedoAddItem);
			//int32	ClassType=(int)m->Action;
			//::Save(UPointer->GetWritePointer(),ClassType);
			//m->Save(UPointer->GetWritePointer());			
			//GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			//emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
	else if(ui->toolButtonPolyLine->isChecked()==true){
		if(m->PN.count()>0){
			QPoint	P(GlobalPosX,GlobalPosY);
			m->PN<<P;
			m->Step=1;
		}
	}
	else if(ui->toolButtonCircle->isChecked()==true){
		//if(m->Step==0){
		//	m->P2PA.setX(GlobalPosX);
		//	m->P2PA.setY(GlobalPosY);
		//	m->Step=1;
		//}
		//else
		if(m->Step>0){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			m->Step=2;

			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			m->Status		=MeasuredList::_MLA_Selected;
			SelectionMode	=HookMeasureForm::__S_SelectMode;

			//GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			//UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,HookMeasureForm::UndoAddItem,HookMeasureForm::RedoAddItem);
			//int32	ClassType=(int)m->Action;
			//::Save(UPointer->GetWritePointer(),ClassType);
			//m->Save(UPointer->GetWritePointer());			
			//GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			//emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
	else if(ui->toolButtonCircle3->isChecked()==true){
		//if(m->Step==0){
		//	m->P2PA.setX(GlobalPosX);
		//	m->P2PA.setY(GlobalPosY);
		//	m->Step=1;
		//}
		//else
		if(m->Step==1){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			m->Step=2;
		}
		else
		if(m->Step>1){
			m->P2PC.setX(GlobalPosX);
			m->P2PC.setY(GlobalPosY);
			m->Step=3;

			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			m->Status		=MeasuredList::_MLA_Selected;
			SelectionMode	=HookMeasureForm::__S_SelectMode;

			//GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			//UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,HookMeasureForm::UndoAddItem,HookMeasureForm::RedoAddItem);
			//int32	ClassType=(int)m->Action;
			//::Save(UPointer->GetWritePointer(),ClassType);
			//m->Save(UPointer->GetWritePointer());			
			//GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			//emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
	else if(ui->toolButtonCenterCircle->isChecked()==true){
		//if(m->Step==0){
		//	m->P2PA.setX(GlobalPosX);
		//	m->P2PA.setY(GlobalPosY);
		//	m->P2PB.setX(GlobalPosX);
		//	m->P2PB.setY(GlobalPosY);
		//	m->P2PD.setX(GlobalPosX);
		//	m->P2PD.setY(GlobalPosY);
		//	m->P2PE.setX(GlobalPosX);
		//	m->P2PE.setY(GlobalPosY);
		//	m->P2PF.setX(GlobalPosX);
		//	m->P2PF.setY(GlobalPosY);
		//	m->Step=1;
		//}
		//else 
		if(m->Step==1){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			m->Step=2;
		}
		else  if(m->Step==2){
			m->P2PC.setX(GlobalPosX);
			m->P2PC.setY(GlobalPosY);
			m->Step=3;
		}
		else if(m->Step==3){
			m->P2PD.setX(GlobalPosX);
			m->P2PD.setY(GlobalPosY);
			m->P2PE.setX(GlobalPosX);
			m->P2PE.setY(GlobalPosY);
			m->P2PF.setX(GlobalPosX);
			m->P2PF.setY(GlobalPosY);
			m->Step=4;
		}
		else if(m->Step==4){
			m->P2PE.setX(GlobalPosX);
			m->P2PE.setY(GlobalPosY);
			m->Step=5;
		}
		else if(m->Step>4){
			m->P2PF.setX(GlobalPosX);
			m->P2PF.setY(GlobalPosY);
			m->Step=6;
		
			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			m->Status		=MeasuredList::_MLA_Selected;
			SelectionMode	=HookMeasureForm::__S_SelectMode;

			//GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			//UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,HookMeasureForm::UndoAddItem,HookMeasureForm::RedoAddItem);
			//int32	ClassType=(int)m->Action;
			//::Save(UPointer->GetWritePointer(),ClassType);
			//m->Save(UPointer->GetWritePointer());			
			//GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			//emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
	else if(ui->toolButtonIsolation->isChecked()==true){
		//if(m->Step==0){
		//	m->P2PA.setX(GlobalPosX);
		//	m->P2PA.setY(GlobalPosY);
		//	m->Step=1;
		//}
		//else
		if(m->Step==1){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			m->Step=2;
		}
		else if(m->Step==2){
			m->P2PC.setX(GlobalPosX);
			m->P2PC.setY(GlobalPosY);
			m->Step=3;

			m->LineColor	=LineColor	;
			m->CircleColor	=CircleColor;	
			m->LineWidth	=LineWidth	;
			m->ArrowSize	=ArrowSize	;
			m->LineType		=LineType	;	
			m->TextFont		=TextFont	;
			m->TextSize		=TextSize	;
			m->Status		=MeasuredList::_MLA_Selected;
			SelectionMode	=HookMeasureForm::__S_SelectMode;

			//GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
			//UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,HookMeasureForm::UndoAddItem,HookMeasureForm::RedoAddItem);
			//int32	ClassType=(int)m->Action;
			//::Save(UPointer->GetWritePointer(),ClassType);
			//m->Save(UPointer->GetWritePointer());			
			//GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			//emit	SignalAddItem((int)m->Action,m->ID);
		}
	}
}

void	HookMeasureForm::MouseLDblClick(int GlobalPosX,int GlobalPosY)
{
	if(Active==false)
		return;
	if(ui->toolButtonFoldedLines->isChecked()==true){
		MeasuredList	*m=new MeasuredList(this,CurrentData);
		m->ID=CurrentMaxID++;
		m->LineColor	=LineColor	;
		m->CircleColor	=CircleColor;	
		m->LineWidth	=LineWidth	;
		m->ArrowSize	=ArrowSize	;
		m->LineType		=LineType	;	
		m->TextFont		=TextFont	;
		m->TextSize		=TextSize	;
		MeasuredData.AppendList(m);
		CurrentData.Step=0;
		CurrentData.PN.clear();

		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
		UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,&HookMeasureForm::UndoAddItem,&HookMeasureForm::RedoAddItem);
		int32	ClassType=(int)m->Action;
		::Save(UPointer->GetWritePointer(),ClassType);
		m->Save(UPointer->GetWritePointer());			
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		emit	SignalAddItem((int)m->Action,m->ID);
	}
	if(ui->toolButtonPolyLine->isChecked()==true){
		MeasuredList	*m=new MeasuredList(this,CurrentData);
		m->ID=CurrentMaxID++;
		m->LineColor	=LineColor	;
		m->CircleColor	=CircleColor;	
		m->LineWidth	=LineWidth	;
		m->ArrowSize	=ArrowSize	;
		m->LineType		=LineType	;	
		m->TextFont		=TextFont	;
		m->TextSize		=TextSize	;
		MeasuredData.AppendList(m);
		CurrentData.Step=0;
		CurrentData.PN.clear();

		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add MeasureList in HookMeasureForm");			
		UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,&HookMeasureForm::UndoAddItem,&HookMeasureForm::RedoAddItem);
		int32	ClassType=(int)m->Action;
		::Save(UPointer->GetWritePointer(),ClassType);
		m->Save(UPointer->GetWritePointer());			
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		emit	SignalAddItem((int)m->Action,m->ID);
	}
}

void	HookMeasureForm::MouseLDblClickForModification(MeasuredList *m)
{
	if(ui->toolButtonFoldedLines->isChecked()==true){
		m->ID=CurrentMaxID++;
		m->LineColor	=LineColor	;
		m->CircleColor	=CircleColor;	
		m->LineWidth	=LineWidth	;
		m->ArrowSize	=ArrowSize	;
		m->LineType		=LineType	;	
		m->TextFont		=TextFont	;
		m->TextSize		=TextSize	;
		m->Status		=MeasuredList::_MLA_Selected;

		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Modify MeasureList in HookMeasureForm");			
		UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,&HookMeasureForm::UndoAddItem,&HookMeasureForm::RedoAddItem);
		int32	ClassType=(int)m->Action;
		::Save(UPointer->GetWritePointer(),ClassType);
		m->Save(UPointer->GetWritePointer());			
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		emit	SignalAddItem((int)m->Action,m->ID);
		if(SelectionMode==__S_ModifyMode){
			SelectionMode=__S_SelectMode;
		}
	}
	if(ui->toolButtonPolyLine->isChecked()==true){
		m->ID=CurrentMaxID++;
		m->LineColor	=LineColor	;
		m->CircleColor	=CircleColor;	
		m->LineWidth	=LineWidth	;
		m->ArrowSize	=ArrowSize	;
		m->LineType		=LineType	;	
		m->TextFont		=TextFont	;
		m->TextSize		=TextSize	;
		m->Status		=MeasuredList::_MLA_Selected;

		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Modify MeasureList in HookMeasureForm");			
		UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,&HookMeasureForm::UndoAddItem,&HookMeasureForm::RedoAddItem);
		int32	ClassType=(int)m->Action;
		::Save(UPointer->GetWritePointer(),ClassType);
		m->Save(UPointer->GetWritePointer());			
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		emit	SignalAddItem((int)m->Action,m->ID);
		if(SelectionMode==__S_ModifyMode){
			SelectionMode=__S_SelectMode;
		}
	}
}
void	HookMeasureForm::MouseRClick(int GlobalPosX,int GlobalPosY)
{
	if(SelectionMode==__S_Addmode){
		if(ui->toolButtonPoint2Point->isChecked()==true){
			if(CurrentData.Step==2){
				CurrentData.Step=1;
			}
			else if(CurrentData.Step==1){
				CurrentData.Step=0;
			}
		}
		else if(ui->toolButtonFoldedLines->isChecked()==true){
			if(CurrentData.PN.count()>=1){
				QMenu	Menu(this);
				Menu.addAction ("取り消し"		, this, SLOT(CancelPolyAction()), Qt::Key_Delete);
				Menu.addAction ("点の取り消し"	, this, SLOT(CancelPolyPointAction()));
				Menu.addAction ("確定"			, this, SLOT(DonePolyAction()));

				QPoint Q=QCursor::pos ();
				Menu.exec(Q);
			}
			/*
			if(CurrentData.PN.count()>=1){
				CurrentData.PN.removeLast();
			}
			*/
		}
		else if(ui->toolButtonArc->isChecked()==true){
			if(CurrentData.Step==3){
				CurrentData.Step=2;
			}
			else if(CurrentData.Step==2){
				CurrentData.Step=1;
			}
			else if(CurrentData.Step==1){
				CurrentData.Step=0;
			}
		}
		else if(ui->toolButtonAngle->isChecked()==true){
			if(CurrentData.Step==4){
				CurrentData.Step=3;
			}
			else if(CurrentData.Step==3){
				CurrentData.Step=2;
			}
			else if(CurrentData.Step==2){
				CurrentData.Step=1;
			}
			else if(CurrentData.Step==1){
				CurrentData.Step=0;
			}
		}
		else if(ui->toolButtonRectangle->isChecked()==true){
			if(CurrentData.Step==2){
				CurrentData.Step=1;
			}
			else if(CurrentData.Step==1){
				CurrentData.Step=0;
			}
		}
		else if(ui->toolButtonPolyLine->isChecked()==true){
			if(CurrentData.PN.count()>=1){
				QMenu	Menu(this);
				Menu.addAction ("取り消し"		, this, SLOT(CancelPolyAction()), Qt::Key_Delete);
				Menu.addAction ("点の取り消し"	, this, SLOT(CancelPolyPointAction()));
				Menu.addAction ("確定"			, this, SLOT(DonePolyAction()));

				QPoint Q=QCursor::pos ();
				Menu.exec(Q);
			}
			/*
			if(CurrentData.PN.count()>=1){
				CurrentData.PN.removeLast();
			}
			*/
		}
		else if(ui->toolButtonCircle->isChecked()==true){
			if(CurrentData.Step==2){
				CurrentData.Step=1;
			}
			else if(CurrentData.Step==1){
				CurrentData.Step=0;
			}
		}
		else if(ui->toolButtonCircle3->isChecked()==true){
			if(CurrentData.Step==3){
				CurrentData.Step=2;
			}
			else if(CurrentData.Step==2){
				CurrentData.Step=1;
			}
			else if(CurrentData.Step==1){
				CurrentData.Step=0;
			}
		}
		else if(ui->toolButtonCenterCircle->isChecked()==true){
			if(CurrentData.Step==6){
				CurrentData.Step=5;
			}
			else if(CurrentData.Step==5){
				CurrentData.Step=4;
			}
			else if(CurrentData.Step==4){
				CurrentData.Step=3;
			}
			else if(CurrentData.Step==3){
				CurrentData.Step=2;
			}
			else if(CurrentData.Step==2){
				CurrentData.Step=1;
			}
			else if(CurrentData.Step==1){
				CurrentData.Step=0;
			}
		}
		else if(ui->toolButtonIsolation->isChecked()==true){
			if(CurrentData.Step==3){
				CurrentData.Step=2;
			}
			else if(CurrentData.Step==2){
				CurrentData.Step=1;
			}
			else if(CurrentData.Step==1){
				CurrentData.Step=0;
			}
		}
	}
	else if(SelectionMode==__S_ModifyMode){
		MeasuredList	*L=new MeasuredList(this,LastLine);
		L->ID=CurrentMaxID++;
		L->LineColor	=LineColor	;
		L->CircleColor	=CircleColor;	
		L->LineWidth	=LineWidth	;
		L->ArrowSize	=ArrowSize	;
		L->LineType		=LineType	;	
		MeasuredData.AppendList(L);
		CurrentData.Step=0;
		SelectionMode=HookMeasureForm::__S_SelectMode;
	}
}
void	HookMeasureForm::MouseRClickModification(HookMeasureForm::MeasuredList *m,int GlobalPosX,int GlobalPosY)
{
	if(SelectionMode==__S_ModifyMode){
		if(ui->toolButtonPoint2Point->isChecked()==true){
			if(m->Step==2){
				m->Step=1;
			}
			else if(m->Step==1){
				m->Step=0;
			}
		}
		else if(ui->toolButtonFoldedLines->isChecked()==true){
			if(m->PN.count()>=1){
				QMenu	Menu(this);
				//Menu.addAction ("取り消し"		, this, SLOT(MCancelPolyAction()), Qt::Key_Delete);
				Menu.addAction ("点の取り消し"	, this, SLOT(MCancelPolyPointAction()));
				Menu.addAction ("確定"			, this, SLOT(MDonePolyAction()));

				QPoint Q=QCursor::pos ();
				Menu.exec(Q);
			}
			/*
			if(m->PN.count()>=1){
				m->PN.removeLast();
			}
			*/
		}
		else if(ui->toolButtonArc->isChecked()==true){
			if(m->Step==3){
				m->Step=2;
			}
			else if(m->Step==2){
				m->Step=1;
			}
			else if(m->Step==1){
				m->Step=0;
			}
		}
		else if(ui->toolButtonAngle->isChecked()==true){
			if(m->Step==4){
				m->Step=3;
			}
			else if(m->Step==3){
				m->Step=2;
			}
			else if(m->Step==2){
				m->Step=1;
			}
			else if(m->Step==1){
				m->Step=0;
			}
		}
		else if(ui->toolButtonRectangle->isChecked()==true){
			if(m->Step==2){
				m->Step=1;
			}
			else if(m->Step==1){
				m->Step=0;
			}
		}
		else if(ui->toolButtonPolyLine->isChecked()==true){
			if(m->PN.count()>=1){
				QMenu	Menu(this);
				//Menu.addAction ("取り消し"		, this, SLOT(MCancelPolyAction()), Qt::Key_Delete);
				Menu.addAction ("点の取り消し"	, this, SLOT(MCancelPolyPointAction()));
				Menu.addAction ("確定"			, this, SLOT(MDonePolyAction()));

				QPoint Q=QCursor::pos ();
				Menu.exec(Q);
			}
			/*
			if(m->PN.count()>=1){
				m->PN.removeLast();
			}
			*/
		}
		else if(ui->toolButtonCircle->isChecked()==true){
			if(m->Step==2){
				m->Step=1;
			}
			else if(m->Step==1){
				m->Step=0;
			}
		}
		else if(ui->toolButtonCircle3->isChecked()==true){
			if(m->Step==3){
				m->Step=2;
			}
			else if(m->Step==2){
				m->Step=1;
			}
			else if(m->Step==1){
				m->Step=0;
			}
		}
		else if(ui->toolButtonCenterCircle->isChecked()==true){
			if(m->Step==6){
				m->Step=5;
			}
			else if(m->Step==5){
				m->Step=4;
			}
			else if(m->Step==4){
				m->Step=3;
			}
			else if(m->Step==3){
				m->Step=2;
			}
			else if(m->Step==2){
				m->Step=1;
			}
			else if(m->Step==1){
				m->Step=0;
			}
		}
		else if(ui->toolButtonIsolation->isChecked()==true){
			if(m->Step==3){
				m->Step=2;
			}
			else if(m->Step==2){
				m->Step=1;
			}
			else if(m->Step==1){
				m->Step=0;
			}
		}
	}
}

void	HookMeasureForm::CancelPolyAction()
{
	CurrentData.PN.clear();
}
void	HookMeasureForm::CancelPolyPointAction()
{
	if (CurrentData.PN.count() == 2) {
		CurrentData.PN.clear();
	}
	else
	if(CurrentData.PN.count()>=1){
		CurrentData.PN.removeLast();
	}
}
void	HookMeasureForm::DonePolyAction()
{
	MouseLDblClick(0,0);
}

void	HookMeasureForm::MCancelPolyAction()
{
	HookMeasureForm::MeasuredList *m=GetModified();
	m->PN.clear();
}
void	HookMeasureForm::MCancelPolyPointAction()
{
	HookMeasureForm::MeasuredList *m=GetModified();
	if(m->PN.count() == 2) {
		m->PN.clear();
	}
	else
	if(m->PN.count()>=0){
		m->PN.removeLast();
	}
}
void	HookMeasureForm::MDonePolyAction()
{
	HookMeasureForm::MeasuredList *m=GetModified();
	MouseLDblClickForModification(m);
}

bool	HookMeasureForm::EditSelection(DisplayImage *TargetPanel ,int GlobalPosX,int GlobalPosY ,double ZoomRate)
{
	for(MeasuredList *m=MeasuredData.GetFirst();m!=NULL;m=m->GetNext()){
		if(m->EditSelection(GlobalPosX,GlobalPosY,DistanceSelection/ZoomRate)==true){
			//TargetPanel->ExecuteReleaseAllSelection();
			//MeasuredData.RemoveList(m);
			//LastLine=*m;
			//CurrentData=*m;
			//delete	m;
			m->Status=MeasuredList::_MLA_Selected;
			emit	SignalSelectedItem((int)m->Action,m->ID);
			/*
			if(m->Action==MeasuredList::_MLA_Point2Point){
				m->Step=1;
			}
			else if(m->Action==MeasuredList::_MLA_FoldedLines){
				m->Step=1;
			}
			else if(m->Action==MeasuredList::_MLA_Arc){
				m->Step=2;
			}
			else if(m->Action==MeasuredList::_MLA_Angle){
				m->Step=3;
			}
			else if(m->Action==MeasuredList::_MLA_Rectangle){
				m->Step=1;
			}
			else if(m->Action==MeasuredList::_MLA_PolyLine){
				m->Step=1;
			}
			else if(m->Action==MeasuredList::_MLA_Circle){
				m->Step=1;
			}
			else if(m->Action==MeasuredList::_MLA_Isolation){
				m->Step=2;
			}
			else if(m->Action==MeasuredList::_MLA_Circle3){
				m->Step=2;
			}
			else if(m->Action==MeasuredList::_MLA_CenterCircle){
				m->Step=5;
			}
			*/
			return true;
		}
	}
	return false;
}
HookMeasureForm::MeasuredList *HookMeasureForm::GetModified(void)
{
	for(MeasuredList *a=MeasuredData.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Status==MeasuredList::_M_A_Modify){
			return a;
		}
	}
	return NULL;
}
HookMeasureForm::MeasuredList *HookMeasureForm::GetSelected(void)
{
	for(MeasuredList *a=MeasuredData.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Status==MeasuredList::_MLA_Selected){
			return a;
		}
	}
	return NULL;
}

bool	HookMeasureForm::EditModification(DisplayImage *TargetPanel ,int GlobalPosX,int GlobalPosY ,double ZoomRate)
{
	for(MeasuredList *m=MeasuredData.GetFirst();m!=NULL;m=m->GetNext()){
		if(m->Status==MeasuredList::_MLA_Selected
		&& m->EditSelection(GlobalPosX,GlobalPosY,DistanceSelection/ZoomRate)==true){
			//TargetPanel->ExecuteReleaseAllSelection();
			//MeasuredData.RemoveList(m);
			//LastLine=*m;
			//CurrentData=*m;
			//delete	m;
			m->Status=MeasuredList::_M_A_Modify;
			//emit	SignalSelectedItem((int)m->Action,m->ID);

			if(m->Action==MeasuredList::_MLA_Point2Point){
				m->Step=1;
			}
			else if(m->Action==MeasuredList::_MLA_FoldedLines){
				m->Step=1;
			}
			else if(m->Action==MeasuredList::_MLA_Arc){
				m->Step=2;
			}
			else if(m->Action==MeasuredList::_MLA_Angle){
				m->Step=3;
			}
			else if(m->Action==MeasuredList::_MLA_Rectangle){
				m->Step=1;
			}
			else if(m->Action==MeasuredList::_MLA_PolyLine){
				m->Step=1;
			}
			else if(m->Action==MeasuredList::_MLA_Circle){
				m->Step=1;
			}
			else if(m->Action==MeasuredList::_MLA_Isolation){
				m->Step=2;
			}
			else if(m->Action==MeasuredList::_MLA_Circle3){
				m->Step=2;
			}
			else if(m->Action==MeasuredList::_MLA_CenterCircle){
				m->Step=5;
			}
			return true;
		}
	}
	return false;
}
bool	HookMeasureForm::DeleteSelection(DisplayImage *TargetPanel ,int GlobalPosX,int GlobalPosY ,double ZoomRate)
{
	for(MeasuredList *m=MeasuredData.GetFirst();m!=NULL;m=m->GetNext()){
		if(m->EditSelection(GlobalPosX,GlobalPosY,DistanceSelection/ZoomRate)==true){
			MeasuredData.RemoveList(m);

			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Delete MeasureList in HookMeasureForm");			
			UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,&HookMeasureForm::UndoDeleteItem,&HookMeasureForm::RedoDeleteItem);
			int32	ClassType=(int)m->Action;
			::Save(UPointer->GetWritePointer(),ClassType);
			m->Save(UPointer->GetWritePointer());			
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			emit	SignalDeleteItem();

			delete	m;
			return true;
		}
	}
	return false;
}
bool	HookMeasureForm::EditMove(DisplayImage *TargetPanel ,int GlobalPosX,int GlobalPosY ,double ZoomRate)
{
	for(MeasuredList *m=MeasuredData.GetFirst();m!=NULL;m=m->GetNext()){
		if(m->EditSelection(GlobalPosX,GlobalPosY,DistanceSelection/ZoomRate)==true){
			TargetPanel->ExecuteReleaseAllSelection();
			m->Status=MeasuredList::_MLA_Selected;
			//emit	SignalSelectedItem((int)m->Action,m->ID);
			return true;
		}
	}
	return false;
}
void	HookMeasureForm::MoveItems(int gdx ,int gdy)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Move MeasureList in HookMeasureForm");			
	for(MeasuredList *m=MeasuredData.GetFirst();m!=NULL;m=m->GetNext()){
		if(m->Status==MeasuredList::_MLA_Selected){

			UndoElement<HookMeasureForm>	*UPointer=new UndoElement<HookMeasureForm>(this,&HookMeasureForm::UndoMoveItem,&HookMeasureForm::RedoMoveItem);
			int32	ClassType=(int)m->Action;
			::Save(UPointer->GetWritePointer(),ClassType);
			m->Save(UPointer->GetWritePointer());			
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			emit	SignalMoveItem((int)m->Action,m->ID);

			m->MoveTo(gdx,gdy);
		}
	}

}
bool	HookMeasureForm::MouseMove(int GlobalPosX,int GlobalPosY)
{
	MouseModify(&CurrentData,GlobalPosX,GlobalPosY);
	/*
	if(ui->toolButtonPoint2Point->isChecked()==true){
		if(CurrentData.Step==1){
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			return true;
		}
	}
	else if(ui->toolButtonFoldedLines->isChecked()==true){
		if(CurrentData.Step>0){
			QPoint	P=CurrentData.PN.last();
			CurrentData.PN.removeAt(CurrentData.PN.count()-1);
			P.setX(GlobalPosX);
			P.setY(GlobalPosY);
			CurrentData.PN<<P;
			return true;
		}
	}
	else if(ui->toolButtonArc->isChecked()==true){
		if(CurrentData.Step==1){
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			return true;
		}
		else if(CurrentData.Step==2){
			CurrentData.P2PC.setX(GlobalPosX);
			CurrentData.P2PC.setY(GlobalPosY);
			return true;
		}
	}
	else if(ui->toolButtonAngle->isChecked()==true){
		if(CurrentData.Step==1){
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			return true;
		}
		if(CurrentData.Step==3){
			CurrentData.P2PD.setX(GlobalPosX);
			CurrentData.P2PD.setY(GlobalPosY);
			return true;
		}
	}
	else if(ui->toolButtonRectangle->isChecked()==true){
		if(CurrentData.Step==1){
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			return true;
		}
	}
	else if(ui->toolButtonPolyLine->isChecked()==true){
		if(CurrentData.Step>0){
			QPoint	P=CurrentData.PN.last();
			CurrentData.PN.removeAt(CurrentData.PN.count()-1);
			P.setX(GlobalPosX);
			P.setY(GlobalPosY);
			CurrentData.PN<<P;
			return true;
		}
	}
	else if(ui->toolButtonCircle->isChecked()==true){
		if(CurrentData.Step==1){
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			return true;
		}
	}
	else if(ui->toolButtonCircle3->isChecked()==true){
		if(CurrentData.Step==1){
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			return true;
		}
		else if(CurrentData.Step==2){
			CurrentData.P2PC.setX(GlobalPosX);
			CurrentData.P2PC.setY(GlobalPosY);
			return true;
		}
	}
	else if(ui->toolButtonCenterCircle->isChecked()==true){
		if(CurrentData.Step==1){
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			return true;
		}
		else if(CurrentData.Step==2){
			CurrentData.P2PC.setX(GlobalPosX);
			CurrentData.P2PC.setY(GlobalPosY);
			return true;
		}
		else if(CurrentData.Step==3){
			CurrentData.P2PD.setX(GlobalPosX);
			CurrentData.P2PD.setY(GlobalPosY);
			CurrentData.P2PE.setX(GlobalPosX);
			CurrentData.P2PE.setY(GlobalPosY);
			CurrentData.P2PF.setX(GlobalPosX);
			CurrentData.P2PF.setY(GlobalPosY);
			return true;
		}
		else if(CurrentData.Step==4){
			CurrentData.P2PE.setX(GlobalPosX);
			CurrentData.P2PE.setY(GlobalPosY);
			CurrentData.P2PF.setX(GlobalPosX);
			CurrentData.P2PF.setY(GlobalPosY);
			return true;
		}
		else if(CurrentData.Step==5){
			CurrentData.P2PF.setX(GlobalPosX);
			CurrentData.P2PF.setY(GlobalPosY);
			return true;
		}
	}
	else if(ui->toolButtonIsolation->isChecked()==true){
		if(CurrentData.Step==1){
			CurrentData.P2PB.setX(GlobalPosX);
			CurrentData.P2PB.setY(GlobalPosY);
			return true;
		}
		else if(CurrentData.Step==2){
			CurrentData.P2PC.setX(GlobalPosX);
			CurrentData.P2PC.setY(GlobalPosY);
			return true;
		}
	}
	*/
	return false;
}

bool	HookMeasureForm::MouseModify(HookMeasureForm::MeasuredList *m,int GlobalPosX,int GlobalPosY)
{
	if(ui->toolButtonPoint2Point->isChecked()==true){
		if(m->Step==1){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			return true;
		}
	}
	else if(ui->toolButtonFoldedLines->isChecked()==true){
		if(m->Step>0){
			QPoint	P=m->PN.last();
			m->PN.removeAt(m->PN.count()-1);
			P.setX(GlobalPosX);
			P.setY(GlobalPosY);
			m->PN<<P;
			return true;
		}
	}
	else if(ui->toolButtonArc->isChecked()==true){
		if(m->Step==1){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			return true;
		}
		else if(m->Step==2){
			m->P2PC.setX(GlobalPosX);
			m->P2PC.setY(GlobalPosY);
			return true;
		}
	}
	else if(ui->toolButtonAngle->isChecked()==true){
		if(m->Step==1){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			return true;
		}
		if(m->Step==3){
			m->P2PD.setX(GlobalPosX);
			m->P2PD.setY(GlobalPosY);
			return true;
		}
	}
	else if(ui->toolButtonRectangle->isChecked()==true){
		if(m->Step==1){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			return true;
		}
	}
	else if(ui->toolButtonPolyLine->isChecked()==true){
		if(m->Step>0){
			QPoint	P=m->PN.last();
			m->PN.removeAt(m->PN.count()-1);
			P.setX(GlobalPosX);
			P.setY(GlobalPosY);
			m->PN<<P;
			return true;
		}
	}
	else if(ui->toolButtonCircle->isChecked()==true){
		if(m->Step==1){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			return true;
		}
	}
	else if(ui->toolButtonCircle3->isChecked()==true){
		if(m->Step==1){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			return true;
		}
		else if(m->Step==2){
			m->P2PC.setX(GlobalPosX);
			m->P2PC.setY(GlobalPosY);
			return true;
		}
	}
	else if(ui->toolButtonCenterCircle->isChecked()==true){
		if(m->Step==1){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			return true;
		}
		else if(m->Step==2){
			m->P2PC.setX(GlobalPosX);
			m->P2PC.setY(GlobalPosY);
			return true;
		}
		else if(m->Step==3){
			m->P2PD.setX(GlobalPosX);
			m->P2PD.setY(GlobalPosY);
			m->P2PE.setX(GlobalPosX);
			m->P2PE.setY(GlobalPosY);
			m->P2PF.setX(GlobalPosX);
			m->P2PF.setY(GlobalPosY);
			return true;
		}
		else if(m->Step==4){
			m->P2PE.setX(GlobalPosX);
			m->P2PE.setY(GlobalPosY);
			m->P2PF.setX(GlobalPosX);
			m->P2PF.setY(GlobalPosY);
			return true;
		}
		else if(m->Step==5){
			m->P2PF.setX(GlobalPosX);
			m->P2PF.setY(GlobalPosY);
			return true;
		}
	}
	else if(ui->toolButtonIsolation->isChecked()==true){
		if(m->Step==1){
			m->P2PB.setX(GlobalPosX);
			m->P2PB.setY(GlobalPosY);
			return true;
		}
		else if(m->Step==2){
			m->P2PC.setX(GlobalPosX);
			m->P2PC.setY(GlobalPosY);
			return true;
		}
	}
	return false;
}
void	HookMeasureForm::Draw(QPainter &pnt	,double ZoomRate,int movx ,int movy)
{
	for(MeasuredList *a=MeasuredData.GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(pnt	,ZoomRate,movx ,movy);
	}
	if(SelectionMode==__S_MoveMode){
		int	gdx=GlobalMovX2-GlobalMovX1;
		int	gdy=GlobalMovY2-GlobalMovY1;
		for(MeasuredList *a=MeasuredData.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Status==MeasuredList::_MLA_Selected){
				QColor	tLineColor	=a->LineColor;
				QColor	tCircleColor=a->CircleColor;
				a->LineColor	=Qt::red;
				a->CircleColor	=Qt::cyan;
				a->Draw(pnt	,ZoomRate,movx+gdx ,movy+gdy);
				a->LineColor	=tLineColor	;
				a->CircleColor	=tCircleColor;
			}
		}
	}
	QColor	tLineColor	=CurrentData.LineColor;
	QColor	tCircleColor=CurrentData.CircleColor;
	CurrentData.LineColor	=Qt::yellow;
	CurrentData.CircleColor	=Qt::yellow;
	CurrentData.TextSize	=TextSize;
	pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);

	CurrentData.Draw(pnt	,ZoomRate,movx ,movy);
	CurrentData.LineColor	=tLineColor	;
	CurrentData.CircleColor	=tCircleColor;
}

void HookMeasureForm::on_toolButtonPoint2Point_clicked()
{
	SelectionMode=__S_Addmode;
	CmdCancelSelection	Cmd;
	BroadcastSpecifiedDirectly(&Cmd);
	CurrentData.Step=0;
	CurrentData.Action	=MeasuredList::_MLA_Point2Point;
	emit	SignalChangeAction();
}

void HookMeasureForm::on_toolButtonFoldedLines_clicked()
{
	SelectionMode=__S_Addmode;
	CmdCancelSelection	Cmd;
	BroadcastSpecifiedDirectly(&Cmd);
	CurrentData.Step=0;
	CurrentData.PN.clear();
	CurrentData.Action	=MeasuredList::_MLA_FoldedLines;
	emit	SignalChangeAction();
}

void HookMeasureForm::on_toolButtonCenterCircle_clicked()
{
	SelectionMode=__S_Addmode;
	CmdCancelSelection	Cmd;
	BroadcastSpecifiedDirectly(&Cmd);
	CurrentData.Step=0;
	CurrentData.Action	=MeasuredList::_MLA_CenterCircle;
	emit	SignalChangeAction();
}

void HookMeasureForm::on_toolButtonArc_clicked()
{
	SelectionMode=__S_Addmode;
	CmdCancelSelection	Cmd;
	BroadcastSpecifiedDirectly(&Cmd);
	CurrentData.Step=0;
	CurrentData.Action	=MeasuredList::_MLA_Arc;
	emit	SignalChangeAction();
}

void HookMeasureForm::on_toolButtonAngle_clicked()
{
	SelectionMode=__S_Addmode;
	CmdCancelSelection	Cmd;
	BroadcastSpecifiedDirectly(&Cmd);
	CurrentData.Step=0;
	CurrentData.Action	=MeasuredList::_MLA_Angle;
	emit	SignalChangeAction();
}

void HookMeasureForm::on_toolButtonRectangle_clicked()
{
	SelectionMode=__S_Addmode;
	CmdCancelSelection	Cmd;
	BroadcastSpecifiedDirectly(&Cmd);
	CurrentData.Step=0;
	CurrentData.Action	=MeasuredList::_MLA_Rectangle;
	emit	SignalChangeAction();
}

void HookMeasureForm::on_toolButtonPolyLine_clicked()
{
	SelectionMode=__S_Addmode;
	CmdCancelSelection	Cmd;
	BroadcastSpecifiedDirectly(&Cmd);
	CurrentData.Step=0;
	CurrentData.PN.clear();
	CurrentData.Action	=MeasuredList::_MLA_PolyLine;
	emit	SignalChangeAction();
}

void HookMeasureForm::on_toolButtonCircle_clicked()
{
	SelectionMode=__S_Addmode;
	CmdCancelSelection	Cmd;
	BroadcastSpecifiedDirectly(&Cmd);
	CurrentData.Step=0;
	CurrentData.Action	=MeasuredList::_MLA_Circle;
	emit	SignalChangeAction();
}

void HookMeasureForm::on_toolButtonIsolation_clicked()
{
	SelectionMode=__S_Addmode;
	CmdCancelSelection	Cmd;
	BroadcastSpecifiedDirectly(&Cmd);
	CurrentData.Step=0;
	CurrentData.Action	=MeasuredList::_MLA_Isolation;
	emit	SignalChangeAction();
}

void HookMeasureForm::on_toolButtonCircle3_clicked()
{
	SelectionMode=__S_Addmode;
	CmdCancelSelection	Cmd;
	BroadcastSpecifiedDirectly(&Cmd);
    CurrentData.Step=0;
    CurrentData.Action	=MeasuredList::_MLA_Circle3;
	emit	SignalChangeAction();
}

void	HookMeasureForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSelectHookMeasure	*CmdSelectHookMeasureVar=dynamic_cast<CmdSelectHookMeasure *>(packet);
	if(CmdSelectHookMeasureVar!=NULL){
		ui->toolButtonPoint2Point	->setChecked(false);
		ui->toolButtonFoldedLines	->setChecked(false);
		ui->toolButtonCenterCircle	->setChecked(false);
		ui->toolButtonArc			->setChecked(false);
		ui->toolButtonAngle			->setChecked(false);
		ui->toolButtonRectangle		->setChecked(false);
		ui->toolButtonPolyLine		->setChecked(false);
		ui->toolButtonCircle		->setChecked(false);
		ui->toolButtonCircle3		->setChecked(false);
		ui->toolButtonIsolation		->setChecked(false);
		SelectionMode=__S_SelectMode;
		return;
	}
	CmdDeleteHookMeasure	*CmdDeleteHookMeasureVar=dynamic_cast<CmdDeleteHookMeasure *>(packet);
	if(CmdDeleteHookMeasureVar!=NULL){
		CurrentData.Step=0;
		CurrentData.Action=MeasuredList::_MLA_Nothing;
		return;
	}
	CmdDrawMeasure	*CmdDrawMeasureVar=dynamic_cast<CmdDrawMeasure *>(packet);
	if(CmdDrawMeasureVar!=NULL){
		Draw	(*CmdDrawMeasureVar->Pnt	,CmdDrawMeasureVar->ZoomRate,CmdDrawMeasureVar->movx ,CmdDrawMeasureVar->movy);
		return;
	}
	CmdMoveModeHookMeasure	*CmdMoveModeHookMeasureVar=dynamic_cast<CmdMoveModeHookMeasure *>(packet);
	if(CmdMoveModeHookMeasureVar!=NULL){
		if(CmdMoveModeHookMeasureVar->MoveMode==true){
			SelectionMode=__S_MoveMode;
			MoveStep=1;
		}
		else{
			SelectionMode=__S_Addmode;
			ReleaseAllMoveMode();
			MoveStep=1;
		}
		return;
	}
	CmdShowHookMeasure	*CmdShowHookMeasureVar=dynamic_cast<CmdShowHookMeasure *>(packet);
	if(CmdShowHookMeasureVar!=NULL){
		if(CmdShowHookMeasureVar->Showing==true){
			ui->stackedWidget	->setCurrentIndex(0);
			if(ui->toolButtonPoint2Point	->isChecked()==true)
				on_toolButtonPoint2Point_clicked();
			else
			if(ui->toolButtonFoldedLines	->isChecked()==true)
				on_toolButtonFoldedLines_clicked();
			else
			if(ui->toolButtonCenterCircle	->isChecked()==true)
				on_toolButtonCenterCircle_clicked();
			else
			if(ui->toolButtonArc	->isChecked()==true)
				on_toolButtonArc_clicked();
			else
			if(ui->toolButtonAngle	->isChecked()==true)
				on_toolButtonAngle_clicked();
			else
			if(ui->toolButtonRectangle	->isChecked()==true)
				on_toolButtonRectangle_clicked();
			else
			if(ui->toolButtonPolyLine	->isChecked()==true)
				on_toolButtonPolyLine_clicked();
			else
			if(ui->toolButtonCircle	->isChecked()==true)
				on_toolButtonCircle_clicked();
			else
			if(ui->toolButtonCircle3	->isChecked()==true)
				on_toolButtonCircle3_clicked();
			else
			if(ui->toolButtonIsolation	->isChecked()==true)
				on_toolButtonIsolation_clicked();

			if(ui->toolButtonPoint2Point	->isChecked()==false
			&& ui->toolButtonFoldedLines	->isChecked()==false
			&& ui->toolButtonCenterCircle	->isChecked()==false
			&& ui->toolButtonArc			->isChecked()==false
			&& ui->toolButtonAngle			->isChecked()==false
			&& ui->toolButtonRectangle		->isChecked()==false
			&& ui->toolButtonPolyLine		->isChecked()==false
			&& ui->toolButtonCircle			->isChecked()==false
			&& ui->toolButtonCircle3		->isChecked()==false
			&& ui->toolButtonIsolation		->isChecked()==false){
				ui->toolButtonPoint2Point	->setChecked(true);
				on_toolButtonPoint2Point_clicked();
			}
		}
		else{
			ui->stackedWidget	->setCurrentIndex(1);
		}
		return;
	}
	CmdSetHookMeasureLineColor	*CmdSetHookMeasureLineColorVar=dynamic_cast<CmdSetHookMeasureLineColor *>(packet);
	if(CmdSetHookMeasureLineColorVar!=NULL){
		LineColor=CmdSetHookMeasureLineColorVar->LineColor;
		if(CmdSetHookMeasureLineColorVar->ChangeSelection==true){
			for(MeasuredList *a=MeasuredData.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Status==MeasuredList::_MLA_Selected){
					a->LineColor=CmdSetHookMeasureLineColorVar->LineColor;
				}
			}
		}
		TargetPanels.Repaint();
		return;
	}
	CmdGetHookMeasureLineColor	*CmdGetHookMeasureLineColorVar=dynamic_cast<CmdGetHookMeasureLineColor *>(packet);
	if(CmdGetHookMeasureLineColorVar!=NULL){
		CmdGetHookMeasureLineColorVar->LineColor=LineColor;
		return;
	}
	CmdSetHookMeasureFont	*CmdSetHookMeasureFontVar=dynamic_cast<CmdSetHookMeasureFont *>(packet);
	if(CmdSetHookMeasureFontVar!=NULL){
		TextFont=CmdSetHookMeasureFontVar->TextFont;
		TextSize=CmdSetHookMeasureFontVar->TextFont.pointSize();
		if(CmdSetHookMeasureFontVar->ChangeSelection==true){
			for(MeasuredList *a=MeasuredData.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Status==MeasuredList::_MLA_Selected){
					a->TextFont=CmdSetHookMeasureFontVar->TextFont;
					a->TextSize=CmdSetHookMeasureFontVar->TextFont.pointSize();
				}
			}
		}
		TargetPanels.Repaint();
		return;
	}
	CmdGetHookMeasureFont	*CmdGetHookMeasureFontVar=dynamic_cast<CmdGetHookMeasureFont *>(packet);
	if(CmdGetHookMeasureFontVar!=NULL){
		CmdGetHookMeasureFontVar->TextFont=TextFont;
		CmdGetHookMeasureFontVar->TextFont.setPointSize(TextSize);
		return;
	}
	CmdSetCurrentHookMeasureType	*CmdSetCurrentHookMeasureTypeVar=dynamic_cast<CmdSetCurrentHookMeasureType *>(packet);
	if(CmdSetCurrentHookMeasureTypeVar!=NULL){
		CurrentData.Action=CmdSetCurrentHookMeasureTypeVar->CurrentIndex;
		CurrentData.Step=0;

		switch(CmdSetCurrentHookMeasureTypeVar->CurrentIndex){
		case MeasuredList::_MLA_Nothing		:
												ui->toolButtonPoint2Point	->setChecked(false);
												ui->toolButtonFoldedLines	->setChecked(false);
												ui->toolButtonCenterCircle	->setChecked(false);
												ui->toolButtonArc			->setChecked(false);
												ui->toolButtonAngle			->setChecked(false);
												ui->toolButtonRectangle		->setChecked(false);
												ui->toolButtonPolyLine		->setChecked(false);
												ui->toolButtonCircle		->setChecked(false);
												ui->toolButtonCircle3		->setChecked(false);
												ui->toolButtonIsolation		->setChecked(false);
												break;
		case MeasuredList::_MLA_Point2Point	:	ui->toolButtonPoint2Point	->setChecked(true);	break;
		case MeasuredList::_MLA_FoldedLines	:	ui->toolButtonFoldedLines	->setChecked(true);	break;
		case MeasuredList::_MLA_Arc			:	ui->toolButtonArc			->setChecked(true);	break;
		case MeasuredList::_MLA_CenterCircle:	ui->toolButtonCenterCircle	->setChecked(true);	break;
		case MeasuredList::_MLA_Angle		:	ui->toolButtonAngle			->setChecked(true);	break;
		case MeasuredList::_MLA_Rectangle	:	ui->toolButtonRectangle		->setChecked(true);	break;
		case MeasuredList::_MLA_PolyLine	:	ui->toolButtonPolyLine		->setChecked(true);	break;
		case MeasuredList::_MLA_Circle		:	ui->toolButtonCircle		->setChecked(true);	break;
		case MeasuredList::_MLA_Isolation	:	ui->toolButtonIsolation		->setChecked(true);	break;
		case MeasuredList::_MLA_Circle3		:	ui->toolButtonCircle3		->setChecked(true);	break;
		}
		TargetPanels.Repaint();
		return;
	}
	CmdGetCurrentHookMeasureType	*CmdGetCurrentHookMeasureTypeVar=dynamic_cast<CmdGetCurrentHookMeasureType *>(packet);
	if(CmdGetCurrentHookMeasureTypeVar!=NULL){
		if(ui->toolButtonPoint2Point	->isChecked()==true)	CmdGetCurrentHookMeasureTypeVar->CurrentIndex=MeasuredList::_MLA_Point2Point	;
		if(ui->toolButtonFoldedLines	->isChecked()==true)	CmdGetCurrentHookMeasureTypeVar->CurrentIndex=MeasuredList::_MLA_FoldedLines	;
		if(ui->toolButtonArc			->isChecked()==true)	CmdGetCurrentHookMeasureTypeVar->CurrentIndex=MeasuredList::_MLA_Arc			;
		if(ui->toolButtonCenterCircle	->isChecked()==true)	CmdGetCurrentHookMeasureTypeVar->CurrentIndex=MeasuredList::_MLA_CenterCircle	;
		if(ui->toolButtonAngle			->isChecked()==true)	CmdGetCurrentHookMeasureTypeVar->CurrentIndex=MeasuredList::_MLA_Angle			;
		if(ui->toolButtonRectangle		->isChecked()==true)	CmdGetCurrentHookMeasureTypeVar->CurrentIndex=MeasuredList::_MLA_Rectangle		;
		if(ui->toolButtonPolyLine		->isChecked()==true)	CmdGetCurrentHookMeasureTypeVar->CurrentIndex=MeasuredList::_MLA_PolyLine		;
		if(ui->toolButtonCircle			->isChecked()==true)	CmdGetCurrentHookMeasureTypeVar->CurrentIndex=MeasuredList::_MLA_Circle			;
		if(ui->toolButtonIsolation		->isChecked()==true)	CmdGetCurrentHookMeasureTypeVar->CurrentIndex=MeasuredList::_MLA_Isolation		;
		if(ui->toolButtonCircle3		->isChecked()==true)	CmdGetCurrentHookMeasureTypeVar->CurrentIndex=MeasuredList::_MLA_Circle3		;
		return;
	}
	CmdSetHookMeasureLineWidth	*CmdSetHookMeasureLineWidthVar=dynamic_cast<CmdSetHookMeasureLineWidth *>(packet);
	if(CmdSetHookMeasureLineWidthVar!=NULL){
		LineWidth=CmdSetHookMeasureLineWidthVar->LineWidth;
		if(CmdSetHookMeasureLineWidthVar->ChangeSelection==true){
			for(MeasuredList *a=MeasuredData.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Status==MeasuredList::_MLA_Selected){
					a->LineWidth=CmdSetHookMeasureLineWidthVar->LineWidth;
				}
			}
		}
		TargetPanels.Repaint();
		return;
	}
	CmdGetHookMeasureLineWidth	*CmdGetHookMeasureLineWidthVar=dynamic_cast<CmdGetHookMeasureLineWidth *>(packet);
	if(CmdGetHookMeasureLineWidthVar!=NULL){
		CmdGetHookMeasureLineWidthVar->LineWidth=LineWidth;
		return;
	}
	CmdHookMeasure_Save	*CmdHookMeasure_SaveVar=dynamic_cast<CmdHookMeasure_Save *>(packet);
	if(CmdHookMeasure_SaveVar!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		Save(&Buff);
		CmdHookMeasure_SaveVar->Data=Buff.buffer();
		return;
	}
	CmdHookMeasure_Load	*CmdHookMeasure_LoadVar=dynamic_cast<CmdHookMeasure_Load *>(packet);
	if(CmdHookMeasure_LoadVar!=NULL){
		QBuffer	Buff(&CmdHookMeasure_LoadVar->Data);
		Buff.open(QIODevice::ReadOnly);
		Load(&Buff);
		TargetPanels.Repaint();
		return;
	}
	CmdHookMeasure_SetActivate	*CmdHookMeasure_SetActivateVar=dynamic_cast<CmdHookMeasure_SetActivate *>(packet);
	if(CmdHookMeasure_SetActivateVar!=NULL){
		Active			=CmdHookMeasure_SetActivateVar->Active;
		SelectionMode	=__S_Addmode;
		return;
	}
	CmdHookMeasure_SetDeleteMode	*CmdHookMeasure_SetDeleteModeVar=dynamic_cast<CmdHookMeasure_SetDeleteMode *>(packet);
	if(CmdHookMeasure_SetDeleteModeVar!=NULL){
		Active			=true;
		SelectionMode	=__S_DeleteMode;
		return;
	}
	CmdSetHookMeasureLineType	*CmdSetHookMeasureLineTypeVar=dynamic_cast<CmdSetHookMeasureLineType *>(packet);
	if(CmdSetHookMeasureLineTypeVar!=NULL){
		LineType	=CmdSetHookMeasureLineTypeVar->LineType;
		if(CmdSetHookMeasureLineTypeVar->ChangeSelection==true){
			for(MeasuredList *a=MeasuredData.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Status==MeasuredList::_MLA_Selected){
					a->LineType=CmdSetHookMeasureLineTypeVar->LineType;
				}
			}
		}
		return;
	}
	CmdGetHookMeasureLineType	*CmdGetHookMeasureLineTypeVar=dynamic_cast<CmdGetHookMeasureLineType *>(packet);
	if(CmdGetHookMeasureLineTypeVar!=NULL){
		CmdGetHookMeasureLineTypeVar->LineType	=LineType;
		return;
	}
	CmdHookMeasure_Transform	*CmdHookMeasure_TransformVar=dynamic_cast<CmdHookMeasure_Transform *>(packet);
	if(CmdHookMeasure_TransformVar!=NULL){
		for(MeasuredList *a=MeasuredData.GetFirst();a!=NULL;a=a->GetNext()){
			a->Transform(CmdHookMeasure_TransformVar->m);
		}
		return;
	}
	GetHookMeasure_ReqLineProperty	*GetHookMeasure_ReqLinePropertyVar=dynamic_cast<GetHookMeasure_ReqLineProperty *>(packet);
	if(GetHookMeasure_ReqLinePropertyVar!=NULL){
		for(MeasuredList *a=MeasuredData.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->ID==GetHookMeasure_ReqLinePropertyVar->ID){
				GetHookMeasure_ReqLinePropertyVar->MLA_ActionID	=a->Action;
				GetHookMeasure_ReqLinePropertyVar->LineWidth	=a->LineWidth;
				GetHookMeasure_ReqLinePropertyVar->LineColor	=a->LineColor;
				GetHookMeasure_ReqLinePropertyVar->CircleColor	=a->CircleColor;
				GetHookMeasure_ReqLinePropertyVar->TextSize		=a->TextSize;
				GetHookMeasure_ReqLinePropertyVar->TextFont		=a->TextFont;
				GetHookMeasure_ReqLinePropertyVar->ArrowSize	=a->ArrowSize;
				GetHookMeasure_ReqLinePropertyVar->LineType		=a->LineType;
				GetHookMeasure_ReqLinePropertyVar->Found=true;
				return;
			}
		}
		GetHookMeasure_ReqLinePropertyVar->Found=false;
		return;
	}
	CmdHookMeasure_GetSelectedItemCount	*CmdHookMeasure_GetSelectedItemCountVar=dynamic_cast<CmdHookMeasure_GetSelectedItemCount *>(packet);
	if(CmdHookMeasure_GetSelectedItemCountVar!=NULL){
		CmdHookMeasure_GetSelectedItemCountVar->SelectedItemCount=0;
		for(MeasuredList *a=MeasuredData.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Status==MeasuredList::_MLA_Selected){
				CmdHookMeasure_GetSelectedItemCountVar->SelectedItemCount++;
			}
		}
		return;
	}
}

void	HookMeasureForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdCancelSelection	*CmdCancelSelectionVar=dynamic_cast<CmdCancelSelection *>(v);
	if(CmdCancelSelectionVar!=NULL){
		CurrentData.Action=MeasuredList::_MLA_Nothing;
		CurrentData.Step=-1;
		return;
	}
}

void	HookMeasureForm::ReleaseAllMoveMode(void)
{
	int	SelectedCount=0;
	for(MeasuredList *a=MeasuredData.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Status==MeasuredList::_MLA_Selected){
			SelectedCount++;
		}
		a->Status=MeasuredList::_MLA_Normal;
	}
	if(SelectedCount!=0){
		emit	SignalReleaseAllSelection();
	}
}

void	HookMeasureForm::ReleaseAllSelectMode(void)
{
	int	SelectedCount=0;
	for(MeasuredList *a=MeasuredData.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Status==MeasuredList::_MLA_Selected){
			SelectedCount++;
		}
		a->Status=MeasuredList::_MLA_Normal;
	}
	if(SelectedCount!=0){
		emit	SignalReleaseAllSelection();
	}
}

void	HookMeasureForm::FinishAllMoveMode(void)
{
	int	SelectedCount = 0;
	for (MeasuredList* a = MeasuredData.GetFirst(); a != NULL; a = a->GetNext()) {
		if (a->Status == MeasuredList::_MLA_Selected) {
			SelectedCount++;
		}
		a->Status = MeasuredList::_MLA_Normal;
	}
	emit	SignalReleaseAllSelection();
}
int		HookMeasureForm::GetSelectedCount(void)
{
	int	SelectedCount = 0;
	for (MeasuredList* a = MeasuredData.GetFirst(); a != NULL; a = a->GetNext()) {
		if (a->Status == MeasuredList::_MLA_Selected) {
			SelectedCount++;
		}
	}
	return SelectedCount;
}
void	HookMeasureForm::SlotRClicked()
{
	SettingMeasureDialog	D(GetLayersBase(),this, NULL);
	if(D.exec()==(bool)true){
	}
}

bool	HookMeasureForm::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)		return false;
	int32	N=MeasuredData.GetCount();
	if(::Save(f,N)==false)		return false;
	for(MeasuredList *a=MeasuredData.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	if(CurrentData.Save(f)==false)	return false;
	
	return true;
}
bool	HookMeasureForm::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)		return false;
	MeasuredData.RemoveAll();
	int32	N;
	if(::Load(f,N)==false)		return false;
	CurrentMaxID=0;
	for(int i=0;i<N;i++){
		MeasuredList *a=new MeasuredList (this);
		if(a->Load(f)==false)
			return false;
		MeasuredData.AppendList(a);
		CurrentMaxID=max(CurrentMaxID,a->ID);
	}
	CurrentMaxID++;

	if(CurrentData.Load(f)==false)	return false;
	
	return true;
}
void	HookMeasureForm::SlotReleaseAllSelection()
{
	ReleaseAllMoveMode();
	MoveStep=1;
}
void	HookMeasureForm::UndoAddItem(QIODevice *f)
{
	int32	ClassType;

	if(::Load(f,ClassType)==false)	return;

	MeasuredList	D(this);
	if(D.Load(f)==false)	return;
	for(MeasuredList *L=MeasuredData.GetLast();L!=NULL;L=L->GetPrev()){
		if(*L==D){
			MeasuredData.RemoveList(L);
			delete	L;
			break;
		}
	}
	TargetPanels.Repaint();
}

void	HookMeasureForm::RedoAddItem(QIODevice *f)
{
	int32	ClassType;

	if(::Load(f,ClassType)==false)	return;

	MeasuredList	*D=new MeasuredList(this);
	if(D->Load(f)==false)	return;
	MeasuredData.AppendList(D);
	TargetPanels.Repaint();
}
void	HookMeasureForm::UndoMoveItem(QIODevice *f)
{
	int32	ClassType;

	if(::Load(f,ClassType)==false)	return;

	MeasuredList	D(this);
	if(D.Load(f)==false)	return;
	for(MeasuredList *L=MeasuredData.GetLast();L!=NULL;L=L->GetPrev()){
		if(L->ID==D.ID){
			L->Swap(D);

			f->seek(0);
			if(::Save(f,ClassType)==false)	return;
			if(D.Save(f)==false)	return;
			break;
		}
	}
	TargetPanels.Repaint();
}
void	HookMeasureForm::RedoMoveItem(QIODevice *f)
{
	UndoMoveItem(f);
}
void	HookMeasureForm::UndoDeleteItem(QIODevice *f)
{
	int32	ClassType;

	if(::Load(f,ClassType)==false)	return;

	MeasuredList	*D=new MeasuredList(this);
	if(D->Load(f)==false)	return;
	MeasuredData.AppendList(D);
	TargetPanels.Repaint();
}
void	HookMeasureForm::RedoDeleteItem(QIODevice *f)
{
	int32	ClassType;

	if(::Load(f,ClassType)==false)	return;

	MeasuredList	D(this);
	if(D.Load(f)==false)	return;
	for(MeasuredList *L=MeasuredData.GetLast();L!=NULL;L=L->GetPrev()){
		if(L->ID==D.ID){
			MeasuredData.RemoveList(L);
			delete	L;
			break;
		}
	}
	TargetPanels.Repaint();
}
