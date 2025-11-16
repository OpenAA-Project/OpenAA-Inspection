#include "DrawHookControlPanelForm.h"
#include "ui_DrawHookControlPanelForm.h"
#include "XDrawHookControlPanelCommon.h"
#include "swap.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QMenu>
#include <QFontDialog>

DrawHookControlPanelForm::DrawHookControlPanelForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent)
	,DrawerItemDatas(this)
    ,ui(new Ui::DrawHookControlPanelForm)
{
    ui->setupUi(this);

	CurrentStepNo=0;
	MoveStep	=0;
	GlobalMovX1=GlobalMovY1=0;
	GlobalMovX2=GlobalMovY2=0;
	Active	=true;
	OperationMode = Mode_None;

    connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	ButtonLineColor			=new mtPushButtonColored(this);
	ButtonDrawLineColor		=new mtPushButtonColored(this);
	ButtonDrawInsideColor	=new mtPushButtonColored(this);
	ButtonTextColor			=new mtPushButtonColored(this);

	ButtonLineColor			->setGeometry(ui->toolButtonLineColor->geometry());
	ButtonDrawLineColor		->setGeometry(ui->toolButtonDrawLineColor->geometry());
	ButtonDrawInsideColor	->setGeometry(ui->toolButtonDrawInsideColor->geometry());
	ButtonTextColor			->setGeometry(ui->toolButtonTextColor->geometry());

	ButtonLineColor			->setParent(ui->toolBox->widget(0));
	ButtonDrawLineColor		->setParent(ui->toolBox->widget(1));
	ButtonDrawInsideColor	->setParent(ui->toolBox->widget(1));
	ButtonTextColor			->setParent(ui->toolBox->widget(2));

	delete	ui->toolButtonLineColor;
	delete	ui->toolButtonDrawLineColor;
	delete	ui->toolButtonDrawInsideColor;
	delete	ui->toolButtonTextColor;

	connect(ButtonLineColor			,SIGNAL(clicked()),this,SLOT(on_toolButtonLineColor_clicked()));
	connect(ButtonDrawLineColor		,SIGNAL(clicked()),this,SLOT(on_toolButtonDrawLineColor_clicked()));
	connect(ButtonDrawInsideColor	,SIGNAL(clicked()),this,SLOT(on_toolButtonDrawInsideColor_clicked()));
	connect(ButtonTextColor			,SIGNAL(clicked()),this,SLOT(on_toolButtonTextColor_clicked()));

	ButtonLineColor			->setColor(Qt::green);
	ButtonDrawLineColor		->setColor(Qt::red);
	ButtonDrawInsideColor	->setColor(Qt::lightGray);
	ButtonTextColor			->setColor(Qt::red);
}

DrawHookControlPanelForm::~DrawHookControlPanelForm()
{
    delete ui;
}

void	DrawHookControlPanelForm::Prepare(void)
{
}

static	bool TargetFunctionPaintLast(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL && DImage->IsShown()==true){
		DrawHookControlPanelForm	*Form=dynamic_cast<DrawHookControlPanelForm *>(Obj);
		if(Form!=NULL){
			if(Form->GetLayersBase()->TryLockWeakDraw()==true){
				Form->Draw(DImage,pnt,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());
				Form->GetLayersBase()->UnlockWeakDraw();
			}
		}
	}
	return true;
}
static	bool TargetFunctionMouseMove(FunctionServerClass *Obj,GUIFormBase *TargetObj,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		DrawHookControlPanelForm	*Form=dynamic_cast<DrawHookControlPanelForm *>(Obj);
		if(Form!=NULL
		&& (Form->OperationMode== DrawHookControlPanelForm::Mode_Edit || Form->OperationMode == DrawHookControlPanelForm::Mode_Append)
		&& DImage->GetTargetPage()==Form->GetTargetPage()){
			if(Form->Active==false)
				return true;
			if(Form->IsModeNew()==true || Form->OperationMode == DrawHookControlPanelForm::Mode_Edit){
				Form->MouseMove(DImage,GlobalPosX,GlobalPosY,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());
				return false;
			}
			else if(Form->MoveStep==2){
				Form->GlobalMovX1=GlobalPosX;
				Form->GlobalMovY1=GlobalPosY;
				Form->GlobalMovX2=GlobalPosX;
				Form->GlobalMovY2=GlobalPosY;
			}
			else if(Form->MoveStep==3){
				Form->GlobalMovX2=GlobalPosX;
				Form->GlobalMovY2=GlobalPosY;
			}
			return false;
		}
		else if (Form != NULL && Form->OperationMode == DrawHookControlPanelForm::Mode_Move && DImage->GetTargetPage() == Form->GetTargetPage()) {
			if (Form->MoveStep == 1) {
				Form->GlobalMovX2 = GlobalPosX;
				Form->GlobalMovY2 = GlobalPosY;
				Form->MoveItemsTmp(Form->GlobalMovX2 - Form->GlobalMovX1, Form->GlobalMovY2 - Form->GlobalMovY1);
				Form->GlobalMovX1 = GlobalPosX;
				Form->GlobalMovY1 = GlobalPosY;
			}
			return false;
		}
	}
	return true;
}
static	bool TargetFunctionMouseLClick(FunctionServerClass *Obj,GUIFormBase *TargetObj,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		DrawHookControlPanelForm	*Form=dynamic_cast<DrawHookControlPanelForm *>(Obj);
		if(Form!=NULL && DImage->GetTargetPage()==Form->GetTargetPage()){
			//if(Form->Active==false)
			//	return true;
			if(Form->OperationMode== DrawHookControlPanelForm::Mode_Delete){
				if(Form->MouseLClickDelete(DImage,GlobalPosX,GlobalPosY,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy())==true){
					return false;
				}
			}
			else
			if(Form->OperationMode == DrawHookControlPanelForm::Mode_Append){	//IsModeNew()==true){
				Form->MouseLClickNew(DImage,GlobalPosX,GlobalPosY,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());
				return false;
			}
			if(Form->OperationMode== DrawHookControlPanelForm::Mode_Edit && (Form->IsModeSelect()==true || Form->MoveStep>0)){
				if(Form->MoveStep==1 || Form->MoveStep==0){
					if(Form->IsModeSelectedOnCreating()==true){
						Form->MouseLClickSelectedOnCreating(DImage,GlobalPosX,GlobalPosY,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());							
						return false;
					}
					else if(Form->MouseLClickSelect(DImage,GlobalPosX,GlobalPosY,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy())==true){
						//Form->MoveStep=2;
						return false;
					}
				}
				else if(Form->MoveStep==2){
					if(Form->OperationMode != DrawHookControlPanelForm::Mode_Edit){
						Form->GlobalMovX1=GlobalPosX;
						Form->GlobalMovY1=GlobalPosY;
						Form->GlobalMovX2=GlobalPosX;
						Form->GlobalMovY2=GlobalPosY;
						Form->MoveStep=3;
					}
					else{
						Form->MouseFinishEdit();
						return false;
					}
				}
				else if(Form->MoveStep==3){
					Form->GlobalMovX2=GlobalPosX;
					Form->GlobalMovY2=GlobalPosY;
					Form->MoveItems(Form->GlobalMovX2-Form->GlobalMovX1,Form->GlobalMovY2-Form->GlobalMovY1);
					Form->GlobalMovX1=GlobalPosX;
					Form->GlobalMovY1=GlobalPosY;
					Form->MoveStep=2;
				}
				return false;
			}
			if (Form->OperationMode == DrawHookControlPanelForm::Mode_Move) {
				if (Form->MoveStep == 0) {
					Form->GlobalMovX1 = GlobalPosX;
					Form->GlobalMovY1 = GlobalPosY;
					Form->GlobalMovX2 = GlobalPosX;
					Form->GlobalMovY2 = GlobalPosY;
					if (Form->IsModeSelectedOnCreating() == true) {
						//Form->MouseLClickSelectedOnCreating(DImage, GlobalPosX, GlobalPosY, DImage->GetZoomRate(), DImage->GetMovx(), DImage->GetMovy());
						Form->MoveStep = 1;
						return false;
					}
					else if (Form->MouseLClickSelectForMove(DImage, GlobalPosX, GlobalPosY, DImage->GetZoomRate(), DImage->GetMovx(), DImage->GetMovy()) == true) {
						Form->MoveStep = 1;
						return false;
					}
				}
				else {
					Form->GlobalMovX2 = GlobalPosX;
					Form->GlobalMovY2 = GlobalPosY;
					Form->MoveItems(Form->GlobalMovX2 - Form->GlobalMovX1, Form->GlobalMovY2 - Form->GlobalMovY1);
					Form->GlobalMovX1 = GlobalPosX;
					Form->GlobalMovY1 = GlobalPosY;
					Form->MoveStep = 0;
					Form->MouseFinishMove();
				}
			}
		}
	}
	return true;
}
static	bool TargetFunctionMouseLDoubleClick(FunctionServerClass *Obj,GUIFormBase *TargetObj,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		DrawHookControlPanelForm	*Form=dynamic_cast<DrawHookControlPanelForm *>(Obj);
		if(Form!=NULL && DImage->GetTargetPage()==Form->GetTargetPage()){
			if(Form->Active==false)
				return true;
			if(Form->IsModeNew()==true){
				Form->MouseLDoubleClickNew(DImage,GlobalPosX,GlobalPosY,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());
				return false;
			}
			if(Form->IsModeSelect()==true){
				Form->MouseLDoubleClickSelect(DImage,GlobalPosX,GlobalPosY,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());
				return false;
			}
		}
	}
	return true;
}

static	bool TargetFunctionMouseRClick(FunctionServerClass *Obj,GUIFormBase *TargetObj,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		DrawHookControlPanelForm	*Form=dynamic_cast<DrawHookControlPanelForm *>(Obj);
		if(Form!=NULL && DImage->GetTargetPage()==Form->GetTargetPage()){
			if(Form->Active==false)
				return true;
			if(Form->IsModeSelect()==true && Form->MoveStep>0){
				Form->MouseRClick(DImage,GlobalPosX,GlobalPosY,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());
				Form->MoveStep=0;
			}
			//else if(Form->MoveStep>0){
			//	Form->MoveStep=0;
			//}
			else{
				Form->MouseRClick(DImage,GlobalPosX,GlobalPosY,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());
			}
			return false;
		}
	}
	return true;
}

void	DrawHookControlPanelForm::ReadyParam(void)
{
	TargetPanels.RemoveAll();

	for(int i=0;i<HookedPanelListName.count();i++){
		QString	HookedPanelName=HookedPanelListName[i];
		DisplayImage *TargetPanel=dynamic_cast<DisplayImage *>(GetLayersBase()->FindByName(HookedPanelName));
		if(TargetPanel!=NULL){
			TargetPanels.Add(TargetPanel);

			TargetPanel->SetHookInPaintLast			(this,TargetFunctionPaintLast);
			TargetPanel->SetHookInMouseMove			(this,TargetFunctionMouseMove);
			TargetPanel->SetHookInMouseLClick		(this,TargetFunctionMouseLClick);
			TargetPanel->SetHookInMouseLDoubleClick	(this,TargetFunctionMouseLDoubleClick);
			TargetPanel->SetHookInMouseRClick		(this,TargetFunctionMouseRClick);

			connect(TargetPanel,SIGNAL(SignalReleaseAllSelection()),this,SLOT(SlotReleaseAllSelection()));
		}
	}
}

void	DrawHookControlPanelForm::ResizeAction()
{
}

void	DrawHookControlPanelForm::Draw		(DisplayImage *Target ,QPainter &pnt ,double ZoomRate,int movx ,int movy)
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(Target ,pnt,ZoomRate,movx ,movy);
	}
	if(MoveStep==1 || MoveStep==2 || MoveStep==3){
		int	gdx=GlobalMovX2-GlobalMovX1;
		int	gdy=GlobalMovY2-GlobalMovY1;
		for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Selected==true){
				a->Draw(Target ,pnt,ZoomRate,movx+gdx ,movy+gdy,false);
			}
		}
	}
}
void	DrawHookControlPanelForm::MouseMove	(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy)
{
	if(OperationMode != Mode_Edit){
		if(ui->toolBox->currentIndex()==0){
			if(CurrentStepNo==1){
				DrawItemLine	*D=dynamic_cast<DrawItemLine *>(DrawerItemDatas.GetCreating());
				if(D!=NULL){
					D->x2=GlobalPosX;
					D->y2=GlobalPosY;
				}
			}
		}
		else if(ui->toolBox->currentIndex()==1){
			DrawItemDraw	*D=dynamic_cast<DrawItemDraw *>(DrawerItemDatas.GetCreating());
			if(D!=NULL){
				XYClass	*p=D->Points.GetLast();
				p->x=GlobalPosX;
				p->y=GlobalPosY;
			}
		}
	}
	else if (OperationMode == Mode_Edit) {
		DrawItemLine	*D1=dynamic_cast<DrawItemLine *>(DrawerItemDatas.GetSelectedOnCreating());
		if(D1!=NULL && D1->OnCreating==true){
			D1->x2=GlobalPosX;
			D1->y2=GlobalPosY;
		}
		DrawItemDraw	*D2=dynamic_cast<DrawItemDraw *>(DrawerItemDatas.GetSelectedOnCreating());
		if(D2!=NULL && D2->OnCreating==true){
			XYClass	*p=D2->Points.GetLast();
			p->x=GlobalPosX;
			p->y=GlobalPosY;
		}
		DrawItemText	*D3=dynamic_cast<DrawItemText *>(DrawerItemDatas.GetSelectedOnCreating());
		if(D3!=NULL && D3->OnCreating==true){
			D3->X=GlobalPosX;
			D3->Y=GlobalPosY;
		}
	}
}
void	DrawHookControlPanelForm::MouseLClickNew	(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy)
{
	if(ui->toolBox->currentIndex()==0){
		if(CurrentStepNo==0){
			DrawItemLine	*D=new DrawItemLine(this);
			D->x1=GlobalPosX;
			D->y1=GlobalPosY;
			D->x2=GlobalPosX;
			D->y2=GlobalPosY;
			D->LineWidth	=ui->spinBoxLineWidth	->value();
			D->LineType		=ui->comboBoxLineType	->currentIndex();
			D->LineColor	=ButtonLineColor	->color();
			D->LineStartType=ui->comboBoxLineStartType	->currentIndex();
			D->LineEndType	=ui->comboBoxLineEndType	->currentIndex();
			D->Selected=true;
			D->ID=DrawerItemDatas.CurrentMaxID++;
			DrawerItemDatas.AppendList(D);
			CurrentStepNo=1;
		}
		else{
			DrawItemLine	*D=dynamic_cast<DrawItemLine *>(DrawerItemDatas.GetCreating());
			if(D!=NULL){
				D->x2=GlobalPosX;
				D->y2=GlobalPosY;
				D->OnCreating=false;
				D->CreatingNew=false;
				D->Selected	=false;
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add line in HookControl");			
				UndoElement<DrawHookControlPanelForm>	*UPointer=new UndoElement<DrawHookControlPanelForm>(this,&DrawHookControlPanelForm::UndoAddItem,&DrawHookControlPanelForm::RedoAddItem);
				int32	ClassType=D->GetClassType();
				::Save(UPointer->GetWritePointer(),ClassType);
				D->Save(UPointer->GetWritePointer());
				GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
				emit	SignalAddItem(typeid(*D).name(),D->ID);
			}
			CurrentStepNo=0;
		}
	}
	if(ui->toolBox->currentIndex()==1){
		if(ui->comboBoxDrawType->currentIndex()==0){
			if(CurrentStepNo==0){
				DrawItemDraw	*D=new DrawItemDraw(this);
				D->Points.AppendList(new XYClass(GlobalPosX,GlobalPosY));
				D->Points.AppendList(new XYClass(GlobalPosX,GlobalPosY));
				D->DrawType=0;
				D->LineType			=ui->comboBoxLineType	->currentIndex();
				D->DrawLineWidth	=ui->spinBoxDrawLineWidth->value();
				D->DrawLineColor	=ButtonDrawLineColor	->color();
				D->DrawInsideType	=ui->comboBoxDrawInsideType	->currentIndex();
				D->DrawInsideColor	=ButtonDrawInsideColor	->color();
				D->Selected=true;
				D->ID=DrawerItemDatas.CurrentMaxID++;
				DrawerItemDatas.AppendList(D);
				CurrentStepNo=1;
			}
			else{
				DrawItemDraw	*D=dynamic_cast<DrawItemDraw *>(DrawerItemDatas.GetCreating());
				if(D!=NULL){
					XYClass	*p=D->Points.GetLast();
					p->x=GlobalPosX;
					p->y=GlobalPosY;
					D->OnCreating=false;
					D->CreatingNew=false;
					D->Selected	=false;

					GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add DrawArea in HookControl");			
					UndoElement<DrawHookControlPanelForm>	*UPointer=new UndoElement<DrawHookControlPanelForm>(this,&DrawHookControlPanelForm::UndoAddItem,&DrawHookControlPanelForm::RedoAddItem);
					int32	ClassType=D->GetClassType();
					::Save(UPointer->GetWritePointer(),ClassType);
					D->Save(UPointer->GetWritePointer());			
					GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
					emit	SignalAddItem(typeid(*D).name(),D->ID);
				}
				CurrentStepNo=0;
			}
			
		}
		else if(ui->comboBoxDrawType->currentIndex()==1){
			if(CurrentStepNo==0){
				DrawItemDraw	*D=new DrawItemDraw(this);
				D->Points.AppendList(new XYClass(GlobalPosX,GlobalPosY));
				D->Points.AppendList(new XYClass(GlobalPosX,GlobalPosY));
				D->DrawType=1;
				D->LineType			=ui->comboBoxLineType	->currentIndex();
				D->DrawLineWidth	=ui->spinBoxDrawLineWidth->value();
				D->DrawLineColor	=ButtonDrawLineColor	->color();
				D->DrawInsideType	=ui->comboBoxDrawInsideType	->currentIndex();
				D->DrawInsideColor	=ButtonDrawInsideColor	->color();
				D->Selected=true;
				D->ID=DrawerItemDatas.CurrentMaxID++;
				DrawerItemDatas.AppendList(D);
				CurrentStepNo=1;
			}
			else if(CurrentStepNo==1){
				DrawItemDraw	*D=dynamic_cast<DrawItemDraw *>(DrawerItemDatas.GetCreating());
				if(D!=NULL){
					XYClass	*p=D->Points.GetLast();
					p->x=GlobalPosX;
					p->y=GlobalPosY;
	
					D->OnCreating=false;
					D->CreatingNew=false;
					D->Selected	=false;

					GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add DrawArea in HookControl");			
					UndoElement<DrawHookControlPanelForm>	*UPointer=new UndoElement<DrawHookControlPanelForm>(this,&DrawHookControlPanelForm::UndoAddItem,&DrawHookControlPanelForm::RedoAddItem);
					int32	ClassType=D->GetClassType();
					::Save(UPointer->GetWritePointer(),ClassType);
					D->Save(UPointer->GetWritePointer());			
					GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
				}
				CurrentStepNo=0;
				if(D!=NULL){
					emit	SignalAddItem(typeid(*D).name(),D->ID);
				}
			}
		}
		else if(ui->comboBoxDrawType->currentIndex()==2){
			if(CurrentStepNo==0){
				DrawItemDraw	*D=new DrawItemDraw(this);
				D->Points.AppendList(new XYClass(GlobalPosX,GlobalPosY));
				D->Points.AppendList(new XYClass(GlobalPosX,GlobalPosY));
				D->DrawType=2;
				D->LineType			=ui->comboBoxLineType	->currentIndex();
				D->DrawLineWidth	=ui->spinBoxDrawLineWidth->value();
				D->DrawLineColor	=ButtonDrawLineColor	->color();
				D->DrawInsideType	=ui->comboBoxDrawInsideType	->currentIndex();
				D->DrawInsideColor	=ButtonDrawInsideColor	->color();
				D->Selected=true;
				D->ID=DrawerItemDatas.CurrentMaxID++;
				DrawerItemDatas.AppendList(D);
				CurrentStepNo=1;
			}
			else{
				DrawItemDraw	*D=dynamic_cast<DrawItemDraw *>(DrawerItemDatas.GetCreating());
				if(D!=NULL){
					XYClass	*p=D->Points.GetLast();
					p->x=GlobalPosX;
					p->y=GlobalPosY;
					D->Points.AppendList(new XYClass(GlobalPosX,GlobalPosY));		
				}
				CurrentStepNo++;
			}
		}
	}
	if(ui->toolBox->currentIndex()==2){
		bool	ShowingLens=GetLayersBase()->IsShowingLensWindow();
		if(ShowingLens==true){
			GetLayersBase()->ShowLensWindow(false);
		}
		QString Text=QInputDialog::getText (NULL
								, "テキスト入力"
								, "文字"
								,QLineEdit::Normal
								,QString()
								,nullptr
								,Qt::WindowCloseButtonHint);
		if(ShowingLens==true){
			GetLayersBase()->ShowLensWindow();
		}

		if(Text.isEmpty()==false){
			DrawItemText	*D=new DrawItemText(this);
			D->X=GlobalPosX;
			D->Y=GlobalPosY;
			D->Text	=Text;
			D->TextHeight	=ui->spinBoxTextSize->value();
			D->TextFont		=CurrentFont;
			D->TextColor	=ButtonTextColor	->color();
			D->OnCreating=false;
			D->CreatingNew=false;
			D->Selected	=false;
			D->ID=DrawerItemDatas.CurrentMaxID++;
			DrawerItemDatas.AppendList(D);

			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add Text in HookControl");			
			UndoElement<DrawHookControlPanelForm>	*UPointer=new UndoElement<DrawHookControlPanelForm>(this,&DrawHookControlPanelForm::UndoAddItem,&DrawHookControlPanelForm::RedoAddItem);
			int32	ClassType=D->GetClassType();
			::Save(UPointer->GetWritePointer(),ClassType);
			D->Save(UPointer->GetWritePointer());			
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			emit	SignalAddItem(typeid(*D).name(),D->ID);
		}
	}
}
bool	DrawHookControlPanelForm::MouseLClickSelect	(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy)
{
	bool	Ret=false;
	//DrawerItemDatas.ReleaseSelect();
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsNear(Target,GlobalPosX,GlobalPosY)==true){
			//Target->ExecuteReleaseAllSelection();
			if(a->Selected==false && a->OnCreating==false){
				a->CopyToLast();
				a->Selected=true;
				a->SetOffset(0, 0);
			}
			else if(a->Selected==true && a->OnCreating==false){
				a->OnCreating=true;
				a->CopyToLast();
				a->SetOffset(0, 0);
			}		
			ui->toolButtonSelect->setChecked(true);
			Ret=true;
			emit	SignalSelectedItem(typeid(*a).name(),a->ID);
		}
	}
	return Ret;
}

bool	DrawHookControlPanelForm::MouseLClickSelectForMove(DisplayImage* Target, int GlobalPosX, int GlobalPosY, double ZoomRate, int movx, int movy)
{
	bool	Ret = false;
	//DrawerItemDatas.ReleaseSelect();
	for (DrawerItemBase* a = DrawerItemDatas.GetFirst(); a != NULL; a = a->GetNext()) {
		if (a->IsNear(Target, GlobalPosX, GlobalPosY) == true) {
			//Target->ExecuteReleaseAllSelection();
			if (a->Selected == false && a->OnCreating == false) {
				a->Selected = true;
				a->CopyToLast();
				a->SetOffset(0, 0);
			}
			else if (a->Selected == true && a->OnCreating == false) {
				a->OnCreating = true;
				a->CopyToLast();
				a->SetOffset(0, 0);
			}			
			ui->toolButtonSelect->setChecked(true);
			Ret = true;
		}
	}
	return Ret;
}
bool	DrawHookControlPanelForm::MouseLClickSelectedOnCreating	(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy)
{
	bool	Ret=false;
	//DrawerItemDatas.ReleaseSelect();
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Selected==true && a->OnCreating==true && a->CreatingNew==false
		&& a->GetClassType()==2
		&& dynamic_cast<DrawItemDraw *>(a)->DrawType==2){
			a->OnCreating	= false;
			a->Selected		= false;
			Ret=true;
		}
		else if(a->IsNear(Target,GlobalPosX,GlobalPosY)==true){
			//Target->ExecuteReleaseAllSelection();
			if(a->Selected==true && a->OnCreating==true){
				a->OnCreating	= false;
				a->Selected		= false;
			}
			Ret=true;
		}
	}
	if(Ret==true){
		emit	SignalReleaseAllSelection();
	}
	return Ret;
}
bool	DrawHookControlPanelForm::MouseLClickDelete(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy)
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsNear(Target,GlobalPosX,GlobalPosY)==true){
			DrawerItemDatas.RemoveList(a);

			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Delete Item in HookControl");			
			UndoElement<DrawHookControlPanelForm>	*UPointer=new UndoElement<DrawHookControlPanelForm>(this,&DrawHookControlPanelForm::UndoDeleteItem,&DrawHookControlPanelForm::RedoDeleteItem);
			int32	ClassType=a->GetClassType();
			::Save(UPointer->GetWritePointer(),ClassType);
			a->Save(UPointer->GetWritePointer());			
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			delete	a;
			emit	SignalDeleteItem();
			return true;
		}
	}
	return false;
}
void	DrawHookControlPanelForm::MouseLDoubleClickNew	(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy)
{
	if(ui->toolBox->currentIndex()==1
	&& ui->comboBoxDrawType->currentIndex()==2){
		if(CurrentStepNo>0){
			DrawItemDraw	*D=dynamic_cast<DrawItemDraw *>(DrawerItemDatas.GetCreating());
			if(D!=NULL){	
				D->OnCreating=false;
				D->CreatingNew=false;
				D->Selected	=false;
				for(XYClass *a=D->Points.GetFirst();a!=NULL;){
					XYClass *b=a->GetNext();
					if(b==NULL){
						break;
					}
					if(*a==*b){
						D->Points.RemoveList(b);
						delete	b;
					}
					else{
						a=a->GetNext();
					}
				}

				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add DrawItemDraw in HookControl");			
				UndoElement<DrawHookControlPanelForm>	*UPointer=new UndoElement<DrawHookControlPanelForm>(this,&DrawHookControlPanelForm::UndoAddItem,&DrawHookControlPanelForm::RedoAddItem);
				int32	ClassType=D->GetClassType();
				::Save(UPointer->GetWritePointer(),ClassType);
				D->Save(UPointer->GetWritePointer());			
				GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
				emit	SignalAddItem(typeid(*D).name(),D->ID);
			}
		}
		CurrentStepNo=0;
	}
}
void	DrawHookControlPanelForm::MouseLDoubleClickSelect(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy)
{
	if(ui->toolBox->currentIndex()==2){
		for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
			DrawItemText	*d=dynamic_cast<DrawItemText *>(a);
			if(d!=NULL && d->Selected==true){
				bool	ShowingLens=GetLayersBase()->IsShowingLensWindow();
				if(ShowingLens==true){
					GetLayersBase()->ShowLensWindow(false);
				}
				bool	ok;
				QString Text=QInputDialog::getText (NULL
								, "テキスト入力"
								, "文字"
								,QLineEdit::Normal
								,d->Text
								,&ok
								,Qt::WindowCloseButtonHint);
				if(ShowingLens==true){
					GetLayersBase()->ShowLensWindow();
				}
				if(ok==true){
					if(Text.isEmpty()==false){
						d->Text=Text;
					}
					else{
						DrawerItemDatas.RemoveList(a);
						delete	a;
					}
				}
				CurrentStepNo=0;
				return;
			}
		}
		CurrentStepNo=0;
	}

}
void	DrawHookControlPanelForm::MouseRClick	(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy)
{
	if(IsModeSelect()==true && MoveStep>0){
		if(OperationMode== Mode_Edit || OperationMode == Mode_Move){
			for (DrawerItemBase* a = DrawerItemDatas.GetFirst(); a != NULL; a = a->GetNext()) {
				if (a->Selected == true) {
					a->RestoreFromLast();
				}
			}
		}
		SlotReleaseAllSelection();
	}
	else{
		if(ui->toolBox->currentIndex()==1
		&& ui->comboBoxDrawType->currentIndex()==2
		&& CurrentStepNo>0){
			QMenu	Menu(this);
			Menu.addAction ("取り消し"	, this, SLOT(CancelPolyAction()), Qt::Key_Delete);
			Menu.addAction ("確定"		, this, SLOT(DonePolyAction()));

			QPoint Q=QCursor::pos ();
			Menu.exec(Q);
		}
		else{
			if(MoveStep==0){
				SlotReleaseAllSelection();
			}
			MoveStep=0;
		}
	}
}

void	DrawHookControlPanelForm::CancelPolyAction()
{
	DrawerItemDatas.RemoveCreating();
	DrawerItemDatas.ReleaseSelect();
	CurrentStepNo=0;
	MoveStep=0;
}
void	DrawHookControlPanelForm::DonePolyAction()
{
	if(ui->toolBox->currentIndex()==1
	&& ui->comboBoxDrawType->currentIndex()==2){
		if(CurrentStepNo>0){
			DrawItemDraw	*D=dynamic_cast<DrawItemDraw *>(DrawerItemDatas.GetCreating());
			if(D!=NULL){	
				D->OnCreating=false;
				D->Selected	=false;
			}
		}
		CurrentStepNo=0;
	}
}

void	DrawHookControlPanelForm::MoveItems(int dx ,int dy)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Move Items in HookControl");			
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Selected==true){
			UndoElement<DrawHookControlPanelForm>	*UPointer=new UndoElement<DrawHookControlPanelForm>(this,&DrawHookControlPanelForm::UndoMoveItem,&DrawHookControlPanelForm::RedoMoveItem);
			int32	ClassType=a->GetClassType();
			::Save(UPointer->GetWritePointer(),ClassType);
			a->Save(UPointer->GetWritePointer());			
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			a->MoveTo(a->OffsetX+dx, a->OffsetY + dy);
			a->SetOffset(0, 0);
			emit	SignalMoveItem(typeid(*a).name(),a->ID);
		}
	}
}

void	DrawHookControlPanelForm::MoveItemsTmp(int dx, int dy)
{
	for (DrawerItemBase* a = DrawerItemDatas.GetFirst(); a != NULL; a = a->GetNext()) {
		if (a->Selected == true) {
			//a->MoveTo(dx, dy);
			a->OffsetX += dx;
			a->OffsetY += dy;
		}
	}
}
void DrawHookControlPanelForm::on_spinBoxLineWidth_valueChanged(int arg1)
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		DrawItemLine	*d=dynamic_cast<DrawItemLine *>(a);
		if(d!=NULL && d->Selected==true){
			d->LineWidth=ui->spinBoxLineWidth	->value();
		}
	}

	TargetPanels.Repaint();
}

void DrawHookControlPanelForm::on_comboBoxLineType_currentIndexChanged(int index)
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		DrawItemLine	*L=dynamic_cast<DrawItemLine *>(a);
		if(L!=NULL && L->Selected==true){
			L->LineType=ui->comboBoxLineType->currentIndex();
		}
		DrawItemDraw	*D=dynamic_cast<DrawItemDraw *>(a);
		if(D!=NULL && D->Selected==true){
			D->LineType=ui->comboBoxLineType->currentIndex();
		}
	}

	TargetPanels.Repaint();
}

void DrawHookControlPanelForm::on_toolButtonLineColor_clicked()
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		DrawItemLine	*d=dynamic_cast<DrawItemLine *>(a);
		if(d!=NULL && d->Selected==true){
			d->LineColor=ButtonLineColor->color();
		}
	}

	TargetPanels.Repaint();
}

void DrawHookControlPanelForm::on_comboBoxLineStartType_currentIndexChanged(int index)
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		DrawItemLine	*d=dynamic_cast<DrawItemLine *>(a);
		if(d!=NULL && d->Selected==true){
			d->LineStartType=ui->comboBoxLineStartType->currentIndex();
		}
	}

	TargetPanels.Repaint();
}

void DrawHookControlPanelForm::on_comboBoxLineEndType_currentIndexChanged(int index)
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		DrawItemLine	*d=dynamic_cast<DrawItemLine *>(a);
		if(d!=NULL && d->Selected==true){
			d->LineEndType=ui->comboBoxLineEndType->currentIndex();
		}
	}

	TargetPanels.Repaint();
}

void DrawHookControlPanelForm::on_comboBoxDrawType_currentIndexChanged(int index)
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		DrawItemDraw	*d=dynamic_cast<DrawItemDraw *>(a);
		if(d!=NULL && d->Selected==true){
			d->DrawType=ui->comboBoxDrawType->currentIndex();
		}
	}

	TargetPanels.Repaint();
}

void DrawHookControlPanelForm::on_spinBoxDrawLineWidth_valueChanged(int arg1)
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		DrawItemDraw	*d=dynamic_cast<DrawItemDraw *>(a);
		if(d!=NULL && d->Selected==true){
			d->DrawLineWidth=ui->spinBoxDrawLineWidth->value();
		}
	}

	TargetPanels.Repaint();
}

void DrawHookControlPanelForm::on_toolButtonDrawLineColor_clicked()
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		DrawItemDraw	*d=dynamic_cast<DrawItemDraw *>(a);
		if(d!=NULL && d->Selected==true){
			d->DrawLineColor=ButtonDrawLineColor->color();
		}
	}

	TargetPanels.Repaint();
}

void DrawHookControlPanelForm::on_comboBoxDrawInsideType_currentIndexChanged(int index)
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		DrawItemDraw	*d=dynamic_cast<DrawItemDraw *>(a);
		if(d!=NULL && d->Selected==true){
			d->DrawInsideType=ui->comboBoxDrawInsideType->currentIndex();
		}
	}

	TargetPanels.Repaint();
}

void DrawHookControlPanelForm::on_toolButtonDrawInsideColor_clicked()
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		DrawItemDraw	*d=dynamic_cast<DrawItemDraw *>(a);
		if(d!=NULL && d->Selected==true){
			d->DrawInsideColor=ButtonDrawInsideColor->color();
		}
	}

	TargetPanels.Repaint();
}

void DrawHookControlPanelForm::on_spinBoxTextSize_valueChanged(int arg1)
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		DrawItemText	*d=dynamic_cast<DrawItemText *>(a);
		if(d!=NULL && d->Selected==true){
			d->TextHeight=ui->spinBoxTextSize->value();
		}
	}

	TargetPanels.Repaint();
}

void DrawHookControlPanelForm::on_pushButtonTextFont_clicked()
{
	bool ok;
	QFont f=QFontDialog::getFont ( &ok, CurrentFont,NULL
								, "Set Font");
	if(ok==true){
		ui->lineEditTextFont	->setText(f.family());
		for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
			DrawItemText	*d=dynamic_cast<DrawItemText *>(a);
			if(d!=NULL && d->Selected==true){
				d->TextFont=f;
			}
		}
		CurrentFont=f;

		TargetPanels.Repaint();
	}
}

void DrawHookControlPanelForm::on_toolButtonTextColor_clicked()
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		DrawItemText	*d=dynamic_cast<DrawItemText *>(a);
		if(d!=NULL && d->Selected==true){
			d->TextColor=ButtonTextColor->color();
		}
	}

	TargetPanels.Repaint();
}

void DrawHookControlPanelForm::on_toolButtonNew_clicked()
{
	if(ui->toolButtonNew->isChecked()==true){
		ui->toolButtonSelect->setChecked(false);
		for(DisplayImagePointer *a=TargetPanels.GetFirst();a!=NULL;a=a->GetNext()){
			DisplayImage	*TargetPanel=a->GetPanel();
			TargetPanel->SetModeByOthers(mtFrameDraw::fdNone,TargetPanel->GetDrawColor());
		}
	}
}

void DrawHookControlPanelForm::on_toolButtonSelect_clicked()
{
	if(ui->toolButtonSelect->isChecked()==true){
		ui->toolButtonNew->setChecked(false);
	}
}

bool	DrawHookControlPanelForm::IsModeNew(void)
{
	return ui->toolButtonNew->isChecked();
}
bool	DrawHookControlPanelForm::IsModeSelect(void)
{
	return ui->toolButtonSelect->isChecked();
}

bool	DrawHookControlPanelForm::IsModeSelectedOnCreating(void)
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Selected==true && a->OnCreating==true){
			return true;
		}
	}
	return false;
}
void DrawHookControlPanelForm::on_toolButtonDelete_clicked()
{
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;){
		DrawerItemBase *NextA=a->GetNext();
		if(a->Selected==true){
			DrawerItemDatas.RemoveList(a);
			delete	a;
		}
		a=NextA;
	}
	TargetPanels.Repaint();
}

void	DrawHookControlPanelForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdDHControlPanel_SetType	*CmdDHControlPanel_SetTypeVar=dynamic_cast<CmdDHControlPanel_SetType *>(packet);
	if(CmdDHControlPanel_SetTypeVar!=NULL){
		ui->toolBox->setCurrentIndex(CmdDHControlPanel_SetTypeVar->DrawType);
		if(CmdDHControlPanel_SetTypeVar->DrawType>=0){
			ui->toolButtonNew->setChecked(true);
			OperationMode = Mode_Edit;
		}
		else{
			ui->toolButtonNew->setChecked(false);
		}
		ui->toolButtonSelect->setChecked(false);
		return;
	}
	CmdDHControlPanel_MakeFlexArea *CmdDHControlPanel_MakeFlexAreaVar=dynamic_cast<CmdDHControlPanel_MakeFlexArea *>(packet);
	if(CmdDHControlPanel_MakeFlexAreaVar!=NULL){
		for(DrawerItemBase *f=DrawerItemDatas.GetFirst();f!=NULL;f=f->GetNext()){
			CmdDHControlPanel_MakeFlexAreaVar->Area += f->MakeArea();
		}
		return;
	}
	CmdDHControlPanel_SetLineWidth	*CmdDHControlPanel_SetLineWidthVar=dynamic_cast<CmdDHControlPanel_SetLineWidth *>(packet);
	if(CmdDHControlPanel_SetLineWidthVar!=NULL){
		ui->spinBoxLineWidth	->setValue(CmdDHControlPanel_SetLineWidthVar->LineWidth);
		ui->spinBoxDrawLineWidth->setValue(CmdDHControlPanel_SetLineWidthVar->LineWidth);
		return;
	}
	CmdDHControlPanel_SetLineType	*CmdDHControlPanel_SetLineTypeVar=dynamic_cast<CmdDHControlPanel_SetLineType *>(packet);
	if(CmdDHControlPanel_SetLineTypeVar!=NULL){
		ui->comboBoxLineType	->setCurrentIndex(CmdDHControlPanel_SetLineTypeVar->LineType);
		return;
	}
	CmdDHControlPanel_SetLineColor	*CmdDHControlPanel_SetLineColorVar=dynamic_cast<CmdDHControlPanel_SetLineColor *>(packet);
	if(CmdDHControlPanel_SetLineColorVar!=NULL){
		ButtonLineColor	->setColor(CmdDHControlPanel_SetLineColorVar->LineColor);
		return;
	}
	CmdDHControlPanel_GetLineColor	*CmdDHControlPanel_GetLineColorVar=dynamic_cast<CmdDHControlPanel_GetLineColor *>(packet);
	if(CmdDHControlPanel_GetLineColorVar!=NULL){
		CmdDHControlPanel_GetLineColorVar->LineColor=ButtonLineColor->color();
		return;
	}
	CmdDHControlPanel_GetDrawColor	*CmdDHControlPanel_GetDrawColorVar=dynamic_cast<CmdDHControlPanel_GetDrawColor *>(packet);
	if(CmdDHControlPanel_GetDrawColorVar!=NULL){
		CmdDHControlPanel_GetDrawColorVar->LineColor	=ButtonDrawLineColor->color();
		CmdDHControlPanel_GetDrawColorVar->InsideColor	=ButtonDrawInsideColor->color();
		return;
	}
	CmdDHControlPanel_SetLineStartType	*CmdDHControlPanel_SetLineStartTypeVar=dynamic_cast<CmdDHControlPanel_SetLineStartType *>(packet);
	if(CmdDHControlPanel_SetLineStartTypeVar!=NULL){
		ui->comboBoxLineStartType->setCurrentIndex(CmdDHControlPanel_SetLineStartTypeVar->LineStartType);
		return;
	}
	CmdDHControlPanel_SetLineEndType	*CmdDHControlPanel_SetLineEndTypeVar=dynamic_cast<CmdDHControlPanel_SetLineEndType *>(packet);
	if(CmdDHControlPanel_SetLineEndTypeVar!=NULL){
		ui->comboBoxLineEndType->setCurrentIndex(CmdDHControlPanel_SetLineEndTypeVar->LineEndType);
		return;
	}
	CmdDHControlPanel_SetDrawType	*CmdDHControlPanel_SetDrawTypeVar=dynamic_cast<CmdDHControlPanel_SetDrawType *>(packet);
	if(CmdDHControlPanel_SetDrawTypeVar!=NULL){
		ui->comboBoxDrawType	->setCurrentIndex(CmdDHControlPanel_SetDrawTypeVar->DrawType);
		return;
	}
	CmdDHControlPanel_SetDrawLineWidth	*CmdDHControlPanel_SetDrawLineWidthVar=dynamic_cast<CmdDHControlPanel_SetDrawLineWidth *>(packet);
	if(CmdDHControlPanel_SetDrawLineWidthVar!=NULL){
		ui->spinBoxDrawLineWidth->setValue(CmdDHControlPanel_SetDrawLineWidthVar->DrawLineWidth);
		return;
	}
	CmdDHControlPanel_SetDrawLineColor	*CmdDHControlPanel_SetDrawLineColorVar=dynamic_cast<CmdDHControlPanel_SetDrawLineColor *>(packet);
	if(CmdDHControlPanel_SetDrawLineColorVar!=NULL){
		ButtonDrawLineColor	->setColor(CmdDHControlPanel_SetDrawLineColorVar->DrawLineColor);
		ButtonLineColor		->setColor(CmdDHControlPanel_SetDrawLineColorVar->DrawLineColor);
		if(CmdDHControlPanel_SetDrawLineColorVar->ChangeSelection==true){
			for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Selected==true){
					DrawItemLine	*L=dynamic_cast<DrawItemLine *>(a);
					if(L!=NULL){
						L->LineColor	=CmdDHControlPanel_SetDrawLineColorVar->DrawLineColor;
					}
					DrawItemDraw	*D=dynamic_cast<DrawItemDraw *>(a);
					if(D!=NULL){
						D->DrawLineColor=CmdDHControlPanel_SetDrawLineColorVar->DrawLineColor;
					}
				}
			}
		}
		return;
	}
	CmdDHControlPanel_SetDrawInsideType	*CmdDHControlPanel_SetDrawInsideTypeVar=dynamic_cast<CmdDHControlPanel_SetDrawInsideType *>(packet);
	if(CmdDHControlPanel_SetDrawInsideTypeVar!=NULL){
		ui->comboBoxDrawInsideType->setCurrentIndex(CmdDHControlPanel_SetDrawInsideTypeVar->DrawInsideType);
		return;
	}
	CmdDHControlPanel_SetDrawInsideColor	*CmdDHControlPanel_SetDrawInsideColorVar=dynamic_cast<CmdDHControlPanel_SetDrawInsideColor *>(packet);
	if(CmdDHControlPanel_SetDrawInsideColorVar!=NULL){
		ButtonDrawInsideColor	->setColor(CmdDHControlPanel_SetDrawInsideColorVar->DrawInsideColor);
		if(CmdDHControlPanel_SetDrawInsideColorVar->ChangeSelection==true){
			for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Selected==true){
					DrawItemDraw	*D=dynamic_cast<DrawItemDraw *>(a);
					if(D!=NULL){
						D->DrawInsideColor=CmdDHControlPanel_SetDrawInsideColorVar->DrawInsideColor;
					}
				}
			}
		}
		return;
	}
	CmdDHControlPanel_SelectTextFont	*CmdDHControlPanel_SelectTextFontVar=dynamic_cast<CmdDHControlPanel_SelectTextFont *>(packet);
	if(CmdDHControlPanel_SelectTextFontVar!=NULL){
		on_pushButtonTextFont_clicked();
		CmdDHControlPanel_SelectTextFontVar->TextFont=CurrentFont;
		return;
	}
	CmdDHControlPanel_SetTextFont	*CmdDHControlPanel_SetTextFontVar=dynamic_cast<CmdDHControlPanel_SetTextFont *>(packet);
	if(CmdDHControlPanel_SetTextFontVar!=NULL){
		CurrentFont	=CmdDHControlPanel_SetTextFontVar->TextFont;
		ui->spinBoxTextSize	->setValue(CmdDHControlPanel_SetTextFontVar->TextFont.pointSize());
		if(CmdDHControlPanel_SetTextFontVar->ChangeSelection==true){
			for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Selected==true){
					DrawItemText	*T=dynamic_cast<DrawItemText *>(a);
					if(T!=NULL){
						T->TextFont	 =CmdDHControlPanel_SetTextFontVar->TextFont;
						T->TextHeight=CmdDHControlPanel_SetTextFontVar->TextFont.pointSize();
					}
				}
			}
		}
		return;
	}
	CmdDHControlPanel_SetTextColor	*CmdDHControlPanel_SetTextColorVar=dynamic_cast<CmdDHControlPanel_SetTextColor *>(packet);
	if(CmdDHControlPanel_SetTextColorVar!=NULL){
		ButtonTextColor	->setColor(CmdDHControlPanel_SetTextColorVar->TextColor);
		if(CmdDHControlPanel_SetTextColorVar->ChangeSelection==true){
			for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Selected==true){
					DrawItemText	*T=dynamic_cast<DrawItemText *>(a);
					if(T!=NULL){
						T->TextColor=CmdDHControlPanel_SetTextColorVar->TextColor;
					}
				}
			}
		}
		return;
	}
	CmdDHControlPanel_GetTextColor	*CmdDHControlPanel_GetTextColorVar=dynamic_cast<CmdDHControlPanel_GetTextColor *>(packet);
	if(CmdDHControlPanel_GetTextColorVar!=NULL){
		CmdDHControlPanel_GetTextColorVar->TextColor=ButtonTextColor->color();
		return;
	}

	CmdDHControlPanel_ExeSelect	*CmdDHControlPanel_ExeSelectVar=dynamic_cast<CmdDHControlPanel_ExeSelect *>(packet);
	if(CmdDHControlPanel_ExeSelectVar!=NULL){
		if(CmdDHControlPanel_ExeSelectVar->MoveMode==true){
			MoveStep=1;
		}
		else{
			MoveStep=0;
		}
		if (OperationMode == Mode_Delete)
			OperationMode = Mode_None;
		ui->toolButtonSelect->setChecked(true);
		ui->toolButtonNew	->setChecked(false);
		return;
	}
	CmdDHControlPanel_ExeDel	*CmdDHControlPanel_ExeDelVar=dynamic_cast<CmdDHControlPanel_ExeDel *>(packet);
	if(CmdDHControlPanel_ExeDelVar!=NULL){
		on_toolButtonDelete_clicked();
		return;
	}
	CmdDrawHookControlPanel	*CmdDrawHookControlPanelVar=dynamic_cast<CmdDrawHookControlPanel *>(packet);
	if(CmdDrawHookControlPanelVar!=NULL){
		for(DisplayImagePointer *a=TargetPanels.GetFirst();a!=NULL;a=a->GetNext()){
			DisplayImage	*TargetPanel=a->GetPanel();
			Draw	(TargetPanel,*CmdDrawHookControlPanelVar->Pnt	,CmdDrawHookControlPanelVar->ZoomRate,CmdDrawHookControlPanelVar->movx ,CmdDrawHookControlPanelVar->movy);
		}
		return;
	}
	CmdHookControlPanel_Save	*CmdHookControlPanel_SaveVar=dynamic_cast<CmdHookControlPanel_Save *>(packet);
	if(CmdHookControlPanel_SaveVar!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		DrawerItemDatas.Save(&Buff);
		CmdHookControlPanel_SaveVar->Data=Buff.buffer();
		return;
	}
	CmdHookControlPanel_Load	*CmdHookControlPanel_LoadVar=dynamic_cast<CmdHookControlPanel_Load *>(packet);
	if(CmdHookControlPanel_LoadVar!=NULL){
		QBuffer	Buff(&CmdHookControlPanel_LoadVar->Data);
		Buff.open(QIODevice::ReadOnly);
		DrawerItemDatas.Load(&Buff);
		TargetPanels.Repaint();
		return;
	}
	CmdHookControlPanel_SetActivate	*CmdHookControlPanel_SetActivateVar=dynamic_cast<CmdHookControlPanel_SetActivate *>(packet);
	if(CmdHookControlPanel_SetActivateVar!=NULL){
		Active=CmdHookControlPanel_SetActivateVar->Active;
		if(OperationMode==Mode_Delete)
			OperationMode = Mode_None;
		return;
	}
	CmdHookControlPanel_SetDeleteMode	*CmdHookControlPanel_SetDeleteModeVar=dynamic_cast<CmdHookControlPanel_SetDeleteMode *>(packet);
	if(CmdHookControlPanel_SetDeleteModeVar!=NULL){
		Active=true;
		OperationMode = Mode_Delete;
		return;
	}
	CmdHookControlPanel_SetDeleteOff	*CmdHookControlPanel_SetDeleteOffVar=dynamic_cast<CmdHookControlPanel_SetDeleteOff *>(packet);
	if(CmdHookControlPanel_SetDeleteOffVar!=NULL){
		OperationMode = Mode_None;
		return;
	}
	CmdHookControlPanel_SetEditMode	*CmdHookControlPanel_SetEditModeVar=dynamic_cast<CmdHookControlPanel_SetEditMode *>(packet);
	if(CmdHookControlPanel_SetEditModeVar!=NULL){
		if(CmdHookControlPanel_SetEditModeVar->EditMode==true){
			OperationMode = Mode_Edit;
			MoveStep = 0;
		}
		if(OperationMode != Mode_Edit){
			SlotReleaseAllSelection();
		}
		return;
	}
	CmdHookControlPanel_SetAppendMode* CmdHookControlPanel_SetAppendModeVar = dynamic_cast<CmdHookControlPanel_SetAppendMode*>(packet);
	if (CmdHookControlPanel_SetAppendModeVar != NULL) {
		if (CmdHookControlPanel_SetAppendModeVar->AppendMode == true)
			OperationMode = Mode_Append;
		if (OperationMode != Mode_Append) {
			SlotReleaseAllSelection();
		}
		return;
	}
	CmdHookControlPanel_SetMoveMode* CmdHookControlPanel_SetMoveModeVar = dynamic_cast<CmdHookControlPanel_SetMoveMode*>(packet);
	if (CmdHookControlPanel_SetMoveModeVar != NULL) {
		if (CmdHookControlPanel_SetMoveModeVar->MoveMode == true) {
			OperationMode = Mode_Move;
			MoveStep = 0;
		}
		if (OperationMode != Mode_Move) {
			SlotReleaseAllSelection();
		}
		return;
	}
	CmdDHControlPanel_Transform	*CmdDHControlPanel_TransformVar=dynamic_cast<CmdDHControlPanel_Transform *>(packet);
	if(CmdDHControlPanel_TransformVar!=NULL){
		for(DrawerItemBase *a=DrawerItemDatas.GetLast();a!=NULL;a=a->GetPrev()){
			a->Transform(CmdDHControlPanel_TransformVar->m);
		}
		return;
	}
	CmdHookControlPanel_GetLineProperty	*CmdHookControlPanel_GetLinePropertyVar=dynamic_cast<CmdHookControlPanel_GetLineProperty *>(packet);
	if(CmdHookControlPanel_GetLinePropertyVar!=NULL){
		for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->ID==CmdHookControlPanel_GetLinePropertyVar->ID){
				DrawItemLine	*L=dynamic_cast<DrawItemLine *>(a);
				if(L!=NULL){
					CmdHookControlPanel_GetLinePropertyVar->LineWidth	=L->LineWidth;
					CmdHookControlPanel_GetLinePropertyVar->LineType	=L->LineType;	//0:Solid	1:Dot	2:Double
					CmdHookControlPanel_GetLinePropertyVar->LineColor	=L->LineColor;
					CmdHookControlPanel_GetLinePropertyVar->LineStartType=L->LineStartType;	//0:Closed	1:Open	2:Arrow	3:Round	4:Bar
					CmdHookControlPanel_GetLinePropertyVar->LineEndType	=L->LineEndType;	//0:Closed	1:Open	2:Arrow	3:Round	4:Bar
					CmdHookControlPanel_GetLinePropertyVar->Found=true;
					return;
				}
			}
		}
		CmdHookControlPanel_GetLinePropertyVar->Found=false;
		return;
	}
	CmdHookControlPanel_GetDrawInfo	*CmdHookControlPanel_GetDrawInfoVar=dynamic_cast<CmdHookControlPanel_GetDrawInfo *>(packet);
	if(CmdHookControlPanel_GetDrawInfoVar!=NULL){
		for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->ID==CmdHookControlPanel_GetDrawInfoVar->ID){
				DrawItemDraw	*D=dynamic_cast<DrawItemDraw *>(a);
				if(D!=NULL){
					CmdHookControlPanel_GetDrawInfoVar->DrawType		=D->DrawType;
					CmdHookControlPanel_GetDrawInfoVar->LineType		=D->LineType;
					CmdHookControlPanel_GetDrawInfoVar->DrawLineWidth	=D->DrawLineWidth;
					CmdHookControlPanel_GetDrawInfoVar->DrawLineColor	=D->DrawLineColor;
					CmdHookControlPanel_GetDrawInfoVar->DrawInsideType	=D->DrawInsideType;	
					CmdHookControlPanel_GetDrawInfoVar->DrawInsideColor	=D->DrawInsideColor;
					CmdHookControlPanel_GetDrawInfoVar->Found=true;
					return;
				}
			}
		}
		CmdHookControlPanel_GetDrawInfoVar->Found=false;
		return;
	}
	CmdHookControlPanel_GetTextInfo	*CmdHookControlPanel_GetTextInfoVar=dynamic_cast<CmdHookControlPanel_GetTextInfo *>(packet);
	if(CmdHookControlPanel_GetTextInfoVar!=NULL){
		for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->ID==CmdHookControlPanel_GetTextInfoVar->ID){
				DrawItemText	*T=dynamic_cast<DrawItemText *>(a);
				if(T!=NULL){
					CmdHookControlPanel_GetTextInfoVar->Text		=T->Text		;
					CmdHookControlPanel_GetTextInfoVar->TextHeight	=T->TextHeight	;
					CmdHookControlPanel_GetTextInfoVar->TextFont	=T->TextFont	;
					CmdHookControlPanel_GetTextInfoVar->TextColor	=T->TextColor	;
					CmdHookControlPanel_GetTextInfoVar->Found=true;
					return;
				}
			}
		}
		CmdHookControlPanel_GetTextInfoVar->Found=false;
		return;
	}
	CmdHookControlPanel_GetSelectedItemCount	*CmdHookControlPanel_GetSelectedItemCountVar=dynamic_cast<CmdHookControlPanel_GetSelectedItemCount *>(packet);
	if(CmdHookControlPanel_GetSelectedItemCountVar!=NULL){
		CmdHookControlPanel_GetSelectedItemCountVar->SelectedItemCount=0;
		for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Selected==true){
				CmdHookControlPanel_GetSelectedItemCountVar->SelectedItemCount++;
			}
		}
		return;
	}
}

void	DrawHookControlPanelForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdCancelSelection	*CmdCancelSelectionVar=dynamic_cast<CmdCancelSelection *>(v);
	if(CmdCancelSelectionVar!=NULL){
		ui->toolButtonNew		->setChecked(false);
		ui->toolButtonSelect	->setChecked(false);
		return;
	}
}
void	DrawHookControlPanelForm::SlotReleaseAllSelection()
{
	int	SelectedOnCreating=0;
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;){
		DrawerItemBase *ANext=a->GetNext();
		if(a->Selected==true){
			if(a->OnCreating==true && a->CreatingNew==true){
				DrawerItemDatas.RemoveList(a);
				delete	a;
			}
			else{
				a->RestoreFromLast();
				SelectedOnCreating++;
			}
		}
		a=ANext;
	}
	if(SelectedOnCreating==0){
		return;
	}
	int	SelectedCount=0;
	for(DrawerItemBase *a=DrawerItemDatas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Selected==true){
			SelectedCount++;
		}
	}
	DrawerItemDatas.RemoveCreating();
	DrawerItemDatas.ReleaseSelect();
	CurrentStepNo=0;
	MoveStep=0;
	if(SelectedCount!=0){
		emit	SignalReleaseAllSelection();
	}
}
bool	DrawHookControlPanelForm::MouseFinishEdit(void)
{
	bool	Ret = false;
	for (DrawerItemBase* a = DrawerItemDatas.GetFirst(); a != NULL; a = a->GetNext()) {
		if (a->Selected == true) {
			a->Selected = false;
			a->OnCreating = false;
			Ret = true;
		}
	}
	if (Ret == true) {
		MoveStep = 1;
	}
	return Ret;
}
bool	DrawHookControlPanelForm::MouseFinishMove(void)
{
	bool	Ret = MouseFinishEdit();
	emit	SignalReleaseAllSelection();
	return Ret;
}

void	DrawHookControlPanelForm::UndoAddItem(QIODevice *f)
{
	int32	ClassType;
	if(::Load(f,ClassType)==false)	return;
	if(ClassType==1){
		DrawItemLine	D(this);
		if(D.Load(f)==false)	return;
		for(DrawerItemBase *a=DrawerItemDatas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->GetClassType()==ClassType){
				DrawItemLine	*item=dynamic_cast<DrawItemLine *>(a);
				if(item!=NULL){
					if(*item==D){
						DrawerItemDatas.RemoveList(a);
						delete	a;
						break;
					}
				}
			}
		}
	}
	else
	if(ClassType==2){
		DrawItemDraw	D(this);
		if(D.Load(f)==false)	return;
		for(DrawerItemBase *a=DrawerItemDatas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->GetClassType()==ClassType){
				DrawItemDraw	*item=dynamic_cast<DrawItemDraw *>(a);
				if(item!=NULL){
					if(*item==D){
						DrawerItemDatas.RemoveList(a);
						delete	a;
						break;
					}
				}
			}
		}
	}
	else
	if(ClassType==3){
		DrawItemText	D(this);
		if(D.Load(f)==false)	return;
		for(DrawerItemBase *a=DrawerItemDatas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->GetClassType()==ClassType){
				DrawItemText	*item=dynamic_cast<DrawItemText *>(a);
				if(item!=NULL){
					if(*item==D){
						DrawerItemDatas.RemoveList(a);
						delete	a;
						break;
					}
				}
			}
		}
	}
	TargetPanels.Repaint();
}

void	DrawHookControlPanelForm::RedoAddItem(QIODevice *f)
{
	int32	ClassType;
	if(::Load(f,ClassType)==false)	return;
	if(ClassType==1){
		DrawItemLine	*D=new DrawItemLine(this);
		if(D->Load(f)==false)	return;
		D->OnCreating=false;
		D->Selected	=false;
		DrawerItemDatas.AppendList(D);
	}
	else
	if(ClassType==2){
		DrawItemDraw	*D=new DrawItemDraw(this);
		if(D->Load(f)==false)	return;
		D->OnCreating=false;
		D->Selected	=false;
		DrawerItemDatas.AppendList(D);
	}
	else
	if(ClassType==3){
		DrawItemText	*D=new DrawItemText(this);
		if(D->Load(f)==false)	return;
		D->OnCreating=false;
		D->Selected	=false;
		DrawerItemDatas.AppendList(D);
	}
	TargetPanels.Repaint();
}
void	DrawHookControlPanelForm::UndoMoveItem(QIODevice *f)
{
	int32	ClassType;
	if(::Load(f,ClassType)==false)	return;
	if(ClassType==1){
		DrawItemLine	D(this);
		if(D.Load(f)==false)	return;
		for(DrawerItemBase *a=DrawerItemDatas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->GetClassType()==ClassType && a->ID==D.ID){
				DrawItemLine	*item=dynamic_cast<DrawItemLine *>(a);
				if(item!=NULL){
					swap(item->x1,D.x1);
					swap(item->y1,D.y1);
					swap(item->x2,D.x2);
					swap(item->y2,D.y2);
					break;
				}
			}
		}
		f->seek(0);
		if(::Save(f,ClassType)==false)	return;
		if(D.Save(f)==false)	return;
	}
	else
	if(ClassType==2){
		DrawItemDraw	D(this);
		if(D.Load(f)==false)	return;
		for(DrawerItemBase *a=DrawerItemDatas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->GetClassType()==ClassType && a->ID==D.ID){
				DrawItemDraw	*item=dynamic_cast<DrawItemDraw *>(a);
				if(item!=NULL){
					item->Points.Swap(D.Points);
				}
			}
		}
		f->seek(0);
		if(::Save(f,ClassType)==false)	return;
		if(D.Save(f)==false)	return;
	}
	else
	if(ClassType==3){
		DrawItemText	D(this);
		if(D.Load(f)==false)	return;
		for(DrawerItemBase *a=DrawerItemDatas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->GetClassType()==ClassType && a->ID==D.ID){
				DrawItemText	*item=dynamic_cast<DrawItemText *>(a);
				if(item!=NULL){
					swap(item->X,D.X);
					swap(item->Y,D.Y);
					break;
				}
			}
		}
		f->seek(0);
		if(::Save(f,ClassType)==false)	return;
		if(D.Save(f)==false)	return;
	}
	TargetPanels.Repaint();
}
void	DrawHookControlPanelForm::RedoMoveItem(QIODevice *f)
{
	UndoMoveItem(f);
}
void	DrawHookControlPanelForm::UndoDeleteItem(QIODevice *f)
{
	int32	ClassType;
	if(::Load(f,ClassType)==false)	return;
	if(ClassType==1){
		DrawItemLine	*D=new DrawItemLine(this);
		if(D->Load(f)==false)	return;
		D->OnCreating=false;
		D->Selected	=false;
		DrawerItemDatas.AppendList(D);
	}
	else
	if(ClassType==2){
		DrawItemDraw	*D=new DrawItemDraw(this);
		if(D->Load(f)==false)	return;
		D->OnCreating=false;
		D->Selected	=false;
		DrawerItemDatas.AppendList(D);
	}
	else
	if(ClassType==3){
		DrawItemText	*D=new DrawItemText(this);
		if(D->Load(f)==false)	return;
		D->OnCreating=false;
		D->Selected	=false;
		DrawerItemDatas.AppendList(D);
	}
	TargetPanels.Repaint();
}
void	DrawHookControlPanelForm::RedoDeleteItem(QIODevice *f)
{
	int32	ClassType;
	if(::Load(f,ClassType)==false)	return;
	if(ClassType==1){
		DrawItemLine	D(this);
		if(D.Load(f)==false)	return;
		for(DrawerItemBase *a=DrawerItemDatas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->GetClassType()==ClassType && a->ID==D.ID){
				DrawItemLine	*item=dynamic_cast<DrawItemLine *>(a);
				if(item!=NULL){
					DrawerItemDatas.RemoveList(a);
					delete	a;
					break;
				}
			}
		}
	}
	else
	if(ClassType==2){
		DrawItemDraw	D(this);
		if(D.Load(f)==false)	return;
		for(DrawerItemBase *a=DrawerItemDatas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->GetClassType()==ClassType && a->ID==D.ID){
				DrawItemDraw	*item=dynamic_cast<DrawItemDraw *>(a);
				if(item!=NULL){
					DrawerItemDatas.RemoveList(a);
					delete	a;
					break;
				}
			}
		}
	}
	else
	if(ClassType==3){
		DrawItemText	D(this);
		if(D.Load(f)==false)	return;
		for(DrawerItemBase *a=DrawerItemDatas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->GetClassType()==ClassType && a->ID==D.ID){
				DrawItemText	*item=dynamic_cast<DrawItemText *>(a);
				if(item!=NULL){
					DrawerItemDatas.RemoveList(a);
					delete	a;
					break;
				}
			}
		}
	}
	TargetPanels.Repaint();
}


void DrawHookControlPanelForm::on_toolBox_currentChanged(int index)
{
	//for(DisplayImagePointer *a=TargetPanels.GetFirst();a!=NULL;a=a->GetNext()){
	//	DisplayImage	*TargetPanel=a->GetPanel();
	//	TargetPanel->SetModeByOthers(mtFrameDraw::fdNone,TargetPanel->GetDrawColor());
	//}
	//return;
}
