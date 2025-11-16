#include "ButtonSelectLearningTargetImageResource.h"
#include "XSelectLearningPacketResource.h"
#include "SelectLearningImageForm.h"
#include "XYCross.h"
#include "XDisplayImage.h"
#include "ButtonSelectLearningTargetImage.h"
#include "XLearningRegist.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

static	bool PaintFunctionLater(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage);

SelectLearningImageForm::SelectLearningImageForm(LayersBase *Base
												,ButtonSelectLearningTargetImage *parentForm
												,const QString	&_DisplayImageRoot
												,const QString	&_DisplayImageName
												,const QString	&_DisplayImageInst
												 ,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);

	DisplayImageRoot=_DisplayImageRoot;
	DisplayImageName=_DisplayImageName;
	DisplayImageInst=_DisplayImageInst;
	ParentForm		=parentForm;

	GUIFormBase	*m=GetLayersBase()->FindByName(DisplayImageRoot,DisplayImageName,DisplayImageInst);
	if(m!=NULL){
		DisplayImage	*DImg=dynamic_cast<DisplayImage *>(m);
		if(DImg!=NULL){
			DImg->SetHookInPaintLast(this,PaintFunctionLater);
		}
	}

	on_pushButtonUpdate_clicked();
	InstallOperationLog(this);
}

SelectLearningImageForm::~SelectLearningImageForm()
{
}

bool PaintFunctionLater(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		SelectLearningImageForm	*Form=dynamic_cast<SelectLearningImageForm *>(Obj);
		if(Form!=NULL){
			if(Form->GetLayersBase()->TryLockWeakDraw()==true){
				Form->Draw(pnt,DImage->GetMovx(),DImage->GetMovy(),DImage->GetZoomRate());
				Form->GetLayersBase()->UnlockWeakDraw();
			}
		}
	}
	return true;
}

void	SelectLearningImageForm::Draw(QPainter &pnt,int movx ,int movy ,double ZoomRate)
{
	for(RectClass *r=RectStocker.GetFirst();r!=NULL;r=r->GetNext()){
		int	kx1=(r->x1+movx)*ZoomRate;
		int	ky1=(r->y1+movy)*ZoomRate;
		int	kx2=(r->x2+movx)*ZoomRate;
		int	ky2=(r->y2+movy)*ZoomRate;

		pnt.setPen(Qt::cyan);
		pnt.drawLine(kx1,ky1,kx2,ky1);
		pnt.drawLine(kx2,ky1,kx2,ky2);
		pnt.drawLine(kx2,ky2,kx1,ky2);
		pnt.drawLine(kx1,ky2,kx1,ky1);
	}
}

void SelectLearningImageForm::on_pushButtonClose_clicked()
{
	bool	Mastered=false;
	GUIFormBase	*m=GetLayersBase()->FindByName(DisplayImageRoot,DisplayImageName,DisplayImageInst);
	if(m!=NULL){
		DisplayImage	*DImg=dynamic_cast<DisplayImage *>(m);
		if(DImg!=NULL){
			DImg->RemoveHook(this);
			if(DImg->GetDisplayType()==DisplayImage::__Master){
				Mastered=true;
			}
			if(DImg->GetDisplayType()==DisplayImage::__Target || DImg->GetDisplayType()==DisplayImage::__DelayedView){
				Mastered=false;
			}
		}
	}
	for(int Page=0;Page<GetPageNumb();Page++){
		GUICmdReqSetLearningImage	RCmd(GetLayersBase(),sRoot,sName,Page);
		GUICmdSendSetLearningImage	ACmd(GetLayersBase(),sRoot,sName,Page);
		RCmd.CreatedTime=XDateTime::currentDateTime();
		RCmd.Mastered=Mastered;
		if(RCmd.Send(Page,0,ACmd)==true){
		}
	}
	close();
	deleteLater();
}

void SelectLearningImageForm::on_listWidget_clicked(const QModelIndex &)
{
	bool	Mastered=false;
	DisplayImage	*DImg=NULL;
	GUIFormBase	*m=GetLayersBase()->FindByName(DisplayImageRoot,DisplayImageName,DisplayImageInst);
	if(m!=NULL){
		DImg=dynamic_cast<DisplayImage *>(m);
		if(DImg!=NULL){
			if(DImg->GetDisplayType()==DisplayImage::__Master){
				Mastered=true;
			}
			if(DImg->GetDisplayType()==DisplayImage::__Target || DImg->GetDisplayType()==DisplayImage::__DelayedView){
				Mastered=false;
			}
		}
	}
	int	Row=ui.listWidget->currentRow();
	LearningImageList *d=Stocker.GetItem(Row);
	if(d==NULL)
		return;

	RectStocker.RemoveAll();
	for(int Page=0;Page<GetPageNumb();Page++){
		GUICmdReqSetLearningImage	RCmd(GetLayersBase(),sRoot,sName,Page);
		GUICmdSendSetLearningImage	ACmd(GetLayersBase(),sRoot,sName,Page);
		RCmd.CreatedTime=d->CreateTime;
		RCmd.Mastered=Mastered;
		if(RCmd.Send(Page,0,ACmd)==true){
			if(ACmd.LocalX1==-1 && ACmd.LocalX2==-1 && ACmd.LocalY1==-1 && ACmd.LocalY2==-1){
				continue;
			}
			int	GlobalX1,GlobalY1;
			GetLayersBase()->GetGlobalMatrixFromLocal(Page 
													,ACmd.LocalX1,ACmd.LocalY1
													,GlobalX1,GlobalY1);
			int	GlobalX2,GlobalY2;
			GetLayersBase()->GetGlobalMatrixFromLocal(Page 
													,ACmd.LocalX2,ACmd.LocalY2
													,GlobalX2,GlobalY2);
			RectClass	*r=new RectClass();
			r->x1=GlobalX1;
			r->y1=GlobalY1;
			r->x2=GlobalX2;
			r->y2=GlobalY2;
			RectStocker.AppendList(r);
			if(DImg!=NULL){
				DImg->ShowCenter((GlobalX1+GlobalX2)/2, (GlobalY1+GlobalY2)/2);
			}
		}
	}
	ParentForm->BroadcastShowInEdit();
}

void SelectLearningImageForm::on_pushButtonUpdate_clicked()
{
	Stocker.RemoveAll();
	int	Row=ui.listWidget->currentRow();
	ui.listWidget->clear();
	for(int Page=0;Page<GetPageNumb();Page++){
		GUICmdReqLearningStockerList	RCmd(GetLayersBase(),sRoot,sName,Page);
		GUICmdSendLearningStockerList	ACmd(GetLayersBase(),sRoot,sName,Page);
		if(RCmd.Send(Page,0,ACmd)==true){
			for(LearningImageList *d=ACmd.Stocker.GetFirst();d!=NULL;d=d->GetNext()){
				LearningImageList	*a;
				for(a=Stocker.GetFirst();a!=NULL;a=a->GetNext()){
					if(d->CreateTime==a->CreateTime){
						break;
					}
				}
				if(a==NULL){
					LearningImageList	*b=new LearningImageList();
					*b=*d;
					Stocker.AppendList(b);
				}
			}
		}
	}
	for(LearningImageList *d=Stocker.GetFirst();d!=NULL;d=d->GetNext()){
		ui.listWidget->addItem(d->CreateTime.toString(/**/"yyyy/MM/dd hh:mm:ss"));
	}
	if(Row>=0 && ui.listWidget->count()>Row){
		ui.listWidget->setCurrentRow(Row);
	}
}

void SelectLearningImageForm::on_listWidget_itemDoubleClicked(QListWidgetItem*)
{
	int	Row=ui.listWidget->currentRow();
	LearningImageList *d=Stocker.GetItem(Row);
	if(d==NULL)
		return;

	for(int page=0;page<GetPageNumb();page++){
		LearningImage	*L=GetLayersBase()->GetPageData(page)->Find(d->CreateTime);
		if(L!=NULL){
			GetLayersBase()->GetEntryPoint()->ShowOtherGUI(
				ParentForm
				,GetLayersBase()->GetGUIFileName()
				,L->GetLearningLayersBase());
			break;
		}
	}
}

void SelectLearningImageForm::on_pushButtonEdit_clicked()
{
	on_listWidget_itemDoubleClicked(NULL);
}

void SelectLearningImageForm::on_pushButtonDelete_clicked()
{
	int	Row=ui.listWidget->currentRow();
	LearningImageList *d=Stocker.GetItem(Row);
	if(d==NULL)
		return;

	RectStocker.RemoveAll();
	for(int Page=0;Page<GetPageNumb();Page++){
		GUICmdReqDeleteLearningImage	RCmd(GetLayersBase(),sRoot,sName,Page);
		RCmd.CreatedTime=d->CreateTime;
		RCmd.Send(NULL,Page,0);
	}
	on_pushButtonUpdate_clicked();
}