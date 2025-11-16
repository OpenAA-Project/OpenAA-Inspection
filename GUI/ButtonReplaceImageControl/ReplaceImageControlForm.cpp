#include "ReplaceImageControlForm.h"
#include "ButtonReplaceImageControl.h"
#include "ui_ReplaceImageControlForm.h"
#include "XGUIFormBase.h"
#include "XDisplayImage.h"
#include "XPropertyReplaceImagePacket.h"
#include <QFileDialog>
#include <QColorDialog>
#include "XGUI.h"
#include "XDrawHookControlPanelCommon.h"

extern  const	char	*sRoot;
extern  const	char	*sName;

ReplaceImageControlForm::ReplaceImageControlForm(LayersBase *base
                                                ,ButtonReplaceImageControl *p
                                                ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(base)
    ,Parent(p)
    ,ui(new Ui::ReplaceImageControlForm)
{
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
    ui->setupUi(this);

    ui->comboBoxCompositePage->clear();
    for(int page=0;page<GetPageNumb();page++){
        if(page!=Parent->CurrentPage){
            CompPageList.Add(page);
            ui->comboBoxCompositePage->addItem(QString("Cam ")+QString::number(page));
        }
    }

    MainGUIFormBase *f=(MainGUIFormBase*)GetLayersBase()->GetMainWidget();
    connect(f,SIGNAL(SignalCloseEvent()),this,SLOT(SlotClose()));

    ui->frameIsolateByColor  ->setEnabled(ui->radioButtonIsolateByColor ->isChecked());
    ui->frameIsolateByMask   ->setEnabled(ui->radioButtonIsolateByMask  ->isChecked());

    ui->frameCompositeColor->setEnabled(ui->radioButtonCompositeColor->isChecked());
    ui->frameCompositeImage->setEnabled(ui->radioButtonCompositeImage->isChecked());
    ui->frameCompositePage ->setEnabled(ui->radioButtonCompositePage->isChecked());

    DisplayImage *DispP=GetImagePanel();
    if(f!=NULL){
        LastDrawingMode =DispP->GetDrawMode();
        LastDrawingColor=DispP->GetDrawColor();
    }
    SetMaskMode();
    SetProcessMode();
}

ReplaceImageControlForm::~ReplaceImageControlForm()
{
    delete ui;
}

void    ReplaceImageControlForm::SlotClose()
{
    Parent->CloseForm();
}

void    ReplaceImageControlForm::showEvent(QShowEvent *event)
{
    Parent->SetHook();
}

void	ReplaceImageControlForm::closeEvent(QCloseEvent *event)
{
    DisplayImage *f=GetImagePanel();
    if(f!=NULL){
        f->SetModeByOthers(LastDrawingMode,LastDrawingColor);
    }
    ui->radioButtonIsolateByColor       ->setChecked(false);
    ui->radioButtonIsolateByMask        ->setChecked(false);
    ui->radioButtonIsolateByOutline     ->setChecked(false);
    ui->radioButtonIsolateByDrawing     ->setChecked(false);
    ui->radioButtonCompositeNone->setChecked(true);
    SetProcessMode();
    Parent->DeleteHook();
}

DisplayImage *ReplaceImageControlForm::GetImagePanel(void)
{
    DisplayImage *f=(DisplayImage *)GetLayersBase()->FindByName(/**/"Inspection",/**/"ReplaceImagePanel",/**/"");
    if(f==NULL){
        f=dynamic_cast<DisplayImage *>(GetLayersBase()->FindByName(Parent->HookPanelInst));
    }
    return f;
}

void    ReplaceImageControlForm::SetDrawEnd(FlexArea &Area)
{
    if(ui->toolButtonIsolateByColor->isChecked()==true
    && ui->radioButtonIsolateByColor->isChecked()==true){
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(Area,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			int	page=P->GetValue();
			DataInPage	*pdata=GetLayersBase()->GetPageData(page);
			FlexArea	A=Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
                GUICmdReplaceImageAddMaskArea   RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
                GUICmdReplaceImageAckMaskArea   ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
                RCmd.Area=A;
                if(RCmd.Send(GlobalPage,0,ACmd)==true){
                    QPalette    P=ui->widgetIsolateByColor->palette();
                    P.setColor(QPalette::Window,ACmd.AverageColor);
                    ui->widgetIsolateByColor->setPalette(P);
                }
            }
        }
    }
}
void   ReplaceImageControlForm::ExeMouseLDown(int globalX, int globalY)
{
	int	localX ,localY;
	int	GlobalPage=GetLayersBase()->GetLocalMatrixFromGlobal(globalX ,globalY ,localX ,localY);
	GUICmdReplaceImageMouseLDown	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	RCmd.X=localX;
	RCmd.Y=localY;
    RCmd.Send(NULL,GlobalPage,0);
}

void ReplaceImageControlForm::on_toolButtonIsolateByColor_clicked()
{
    if(ui->toolButtonIsolateByColor->isChecked()==true){
        DisplayImage *f=GetImagePanel();
        if(f!=NULL){
            f->SetModeByOthers(mtFrameDraw::fdRectangle,Qt::red);
        }
    }
}


void ReplaceImageControlForm::on_radioButtonIsolateByColor_clicked()
{
    DisplayImage *f=GetImagePanel();
    if(f!=NULL){
        f->Repaint();
    }
    ui->frameIsolateByColor  ->setEnabled(ui->radioButtonIsolateByColor ->isChecked());
    ui->frameIsolateByMask   ->setEnabled(ui->radioButtonIsolateByMask  ->isChecked());
    SetMaskMode();
}


void ReplaceImageControlForm::on_radioButtonIsolateByMask_clicked()
{
    DisplayImage *f=GetImagePanel();
    if(f!=NULL){
        f->Repaint();
    }
    ui->frameIsolateByColor  ->setEnabled(ui->radioButtonIsolateByColor ->isChecked());
    ui->frameIsolateByMask   ->setEnabled(ui->radioButtonIsolateByMask  ->isChecked());
    SetMaskMode();
}


void ReplaceImageControlForm::on_radioButtonIsolateByOutline_clicked()
{
    DisplayImage *f=GetImagePanel();
    if(f!=NULL){
        f->Repaint();
    }
    ui->frameIsolateByColor  ->setEnabled(ui->radioButtonIsolateByColor ->isChecked());
    ui->frameIsolateByMask   ->setEnabled(ui->radioButtonIsolateByMask  ->isChecked());
    SetMaskMode();
}


void ReplaceImageControlForm::on_pushButtonLoadMaskImage_clicked()
{
    QString FileName=QFileDialog::getOpenFileName(nullptr, "Load mask image"
                                                ,QString()
                                                ,/**/"PNG(*.png);;Bmp(*.bmp);;All file(*.*)");
    if(FileName.isEmpty()==false){
        QImage  Img;
        Img.load(FileName);
        QImage  WImage(Img.width(),Img.height(),QImage::Format_RGB32);
        WImage=Img.convertToFormat(QImage::Format_RGB32);

		int GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Parent->CurrentPage);
        GUICmdReplaceImageAddMaskImage   RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
        RCmd.Image=WImage;
        RCmd.Send(NULL,GlobalPage,0);
    }
}

void ReplaceImageControlForm::on_radioButtonIsolateByDrawing_clicked()
{
    CmdDHControlPanel_MakeFlexArea  Cmd(GetLayersBase());
    GUIFormBase *f=GetLayersBase()->FindByName(/**/"General",/**/"DrawHookControlPanel",/**/"");
    if(f!=NULL){
        f->TransmitDirectly(&Cmd);

        int GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Parent->CurrentPage);
        GUICmdReplaceImageMakeAreaMask   RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
        RCmd.Area=Cmd.Area;
        RCmd.Send(NULL,GlobalPage,0);
    }
}


void ReplaceImageControlForm::on_checkBoxCompositeInside_clicked()
{
    SetProcessMode();
}


void ReplaceImageControlForm::on_radioButtonCompositeNone_clicked()
{
    ui->frameCompositeColor->setEnabled(ui->radioButtonCompositeColor->isChecked());
    ui->frameCompositeImage->setEnabled(ui->radioButtonCompositeImage->isChecked());
    ui->frameCompositePage ->setEnabled(ui->radioButtonCompositePage->isChecked());

    SetProcessMode();
}


void ReplaceImageControlForm::on_radioButtonCompositeColor_clicked()
{
    ui->frameCompositeColor->setEnabled(ui->radioButtonCompositeColor->isChecked());
    ui->frameCompositeImage->setEnabled(ui->radioButtonCompositeImage->isChecked());
    ui->frameCompositePage ->setEnabled(ui->radioButtonCompositePage->isChecked());
    SetProcessMode();
}


void ReplaceImageControlForm::on_radioButtonTransparent_clicked()
{
    ui->frameCompositeColor->setEnabled(ui->radioButtonCompositeColor->isChecked());
    ui->frameCompositeImage->setEnabled(ui->radioButtonCompositeImage->isChecked());
    ui->frameCompositePage ->setEnabled(ui->radioButtonCompositePage->isChecked());
    SetProcessMode();
}


void ReplaceImageControlForm::on_radioButtonCompositeImage_clicked()
{
    ui->frameCompositeColor->setEnabled(ui->radioButtonCompositeColor->isChecked());
    ui->frameCompositeImage->setEnabled(ui->radioButtonCompositeImage->isChecked());
    ui->frameCompositePage ->setEnabled(ui->radioButtonCompositePage->isChecked());
    SetProcessMode();
}


void ReplaceImageControlForm::on_radioButtonCompositePage_clicked()
{
    ui->frameCompositeColor->setEnabled(ui->radioButtonCompositeColor->isChecked());
    ui->frameCompositeImage->setEnabled(ui->radioButtonCompositeImage->isChecked());
    ui->frameCompositePage ->setEnabled(ui->radioButtonCompositePage->isChecked());
    SetProcessMode();
}

void ReplaceImageControlForm::on_radioButtonViewMask_clicked()
{
    ui->frameCompositeColor->setEnabled(ui->radioButtonCompositeColor->isChecked());
    ui->frameCompositeImage->setEnabled(ui->radioButtonCompositeImage->isChecked());
    ui->frameCompositePage ->setEnabled(ui->radioButtonCompositePage->isChecked());
    SetProcessMode();
}



void ReplaceImageControlForm::on_pushButtonCompositeColor_clicked()
{
    QPalette    P=ui->widgetCompositeColor->palette();
    QColor  CurrentColor=P.color(QPalette::Window);
    QColor  Col=QColorDialog::getColor(CurrentColor, nullptr
                                    ,"塗る色");
    if(Col.isValid()==true){
		int GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Parent->CurrentPage);
        GUICmdReplaceImageSetCompositeColor   RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
        RCmd.Color=Col;
        RCmd.Send(NULL,GlobalPage,0);

        QPalette    P=ui->widgetCompositeColor->palette();
        P.setColor(QPalette::Window,Col);
        ui->widgetCompositeColor->setPalette(P);
    }
}


void ReplaceImageControlForm::on_pushButtonLoadCompositeImage_clicked()
{
    QString FileName=QFileDialog::getOpenFileName(nullptr, "合成の背景画像の読込"
                                                ,QString()
                                                ,/**/"PNG(*.png);;Bmp(*.bmp);;All file(*.*)");
    if(FileName.isEmpty()==false){
        QImage  Img;
        Img.load(FileName);
        QImage  WImage(Img.width(),Img.height(),QImage::Format_RGB32);
        WImage=Img.convertToFormat(QImage::Format_RGB32);

		int GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Parent->CurrentPage);
        GUICmdReplaceImageSetCompositeImage   RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
        RCmd.Image=WImage;
        RCmd.Send(NULL,GlobalPage,0);
    }
}


void ReplaceImageControlForm::on_comboBoxCompositePage_currentIndexChanged(int index)
{
    int Index=ui->comboBoxCompositePage->currentIndex();
    if(Index<0)
        return;
    int Page=CompPageList[Index];
    if(0<=Page){
	    int GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Parent->CurrentPage);
        GUICmdReplaceImageSetCompositePage   RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
        if(Page>=0){
            RCmd.CompPage=Page;
            RCmd.Send(NULL,GlobalPage,0);
        }
    }
}

void	ReplaceImageControlForm::DrawPanel(QPainter &pnt,int movx ,int movy,double ZoomRate,int CanvasWidth ,int CanvasHeight)
{
    if(ui->radioButtonViewMask->isChecked()==true){
		int GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Parent->CurrentPage);
        GUICmdReplaceImageReqDraw   RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
        GUICmdReplaceImageAckDraw   ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
        RCmd.Data.movx          =movx;
        RCmd.Data.movy          =movy;
        RCmd.Data.ZoomRate      =ZoomRate;
        RCmd.Data.CanvasWidth   =CanvasWidth;
        RCmd.Data.CanvasHeight  =CanvasHeight;
        RCmd.Data.ShowIsoMask   =true;
        if(RCmd.Send(GlobalPage,0,ACmd)==true){
            pnt.drawImage(0,0,ACmd.Image);
        }
    }
}
	
bool	ReplaceImageControlForm::IsAvailableShowMask(void)
{
    if(ui->radioButtonViewMask->isChecked()==true){
        return true;
    }
    return false;
}

bool	ReplaceImageControlForm::IsAvailableDrawAreaForMask(void)
{
    if(ui->radioButtonIsolateByColor->isChecked()==true
    && ui->toolButtonIsolateByColor->isChecked()==true){
        return true;
    }
    return false;
}

bool    ReplaceImageControlForm::IsAvailableMouseLDouble(void)
{
    if(ui->radioButtonIsolateByOutline->isChecked()==true){
        return true;
    }
    return false;
}

void    ReplaceImageControlForm::SetProcessMode(void)
{
    int GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Parent->CurrentPage);
    GUICmdReplaceImageProcessMode   RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
    
    RCmd.CompositeInside=ui->checkBoxCompositeInside->isChecked();
    if(ui->radioButtonCompositeNone->isChecked()==true)
        RCmd.CompMode   =ReplaceImageThreshold::_RC_None;
    else
    if(ui->radioButtonViewMask->isChecked()==true)
        RCmd.CompMode   =ReplaceImageThreshold::_RC_Mask;
    else
    if(ui->radioButtonCompositeColor->isChecked()==true)
        RCmd.CompMode   =ReplaceImageThreshold::_RC_Color;
    else
    if(ui->radioButtonTransparent->isChecked()==true)
        RCmd.CompMode   =ReplaceImageThreshold::_RC_Transparent;
    else
    if(ui->radioButtonCompositeImage->isChecked()==true)
        RCmd.CompMode   =ReplaceImageThreshold::_RC_Image;
    else
    if(ui->radioButtonCompositePage->isChecked()==true)
        RCmd.CompMode   =ReplaceImageThreshold::_RC_Page;

    RCmd.Send(NULL,GlobalPage,0);
}
void    ReplaceImageControlForm::SetMaskMode(void)
{
    int GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Parent->CurrentPage);
    GUICmdReplaceImageMaskMode   RCmd(GetLayersBase(),sRoot,sName,GlobalPage);

    RCmd.OpeMode=ReplaceImageThreshold::_RI_None;
    if(ui->radioButtonIsolateByColor->isChecked()==true)
        RCmd.OpeMode   =ReplaceImageThreshold::_RI_ByColor;
    else
    if(ui->radioButtonIsolateByMask->isChecked()==true)
        RCmd.OpeMode   =ReplaceImageThreshold::_RI_ByMaskImage;
    else
    if(ui->radioButtonIsolateByOutline->isChecked()==true)
        RCmd.OpeMode   =ReplaceImageThreshold::_RI_ByOutline;
    else
    if(ui->radioButtonIsolateByDrawing->isChecked()==true)
        RCmd.OpeMode   =ReplaceImageThreshold::_RI_ByDrawing;

    RCmd.Send(NULL,GlobalPage,0);
}
