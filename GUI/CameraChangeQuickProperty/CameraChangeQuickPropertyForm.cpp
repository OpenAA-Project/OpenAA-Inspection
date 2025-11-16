#include "CameraChangeQuickPropertyResource.h"
#include "CameraChangeQuickPropertyForm.h"
#include "ui_CameraChangeQuickPropertyForm.h"
#include "XExecuteInspectBase.h"
#include "XCameraClass.h"
#include "XDisplayImage.h"
#include "XEntryPoint.h"

extern  const	char	*sRoot;
extern  const	char	*sName;

CameraChangeQuickPropertyForm::CameraChangeQuickPropertyForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::CameraChangeQuickPropertyForm)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);

    SavedDrawingMode=mtFrameDraw::fdNone;
    RegularColor.SetColor(0,0,0);
    TitleName=LangSolver.GetString(CameraChangeQuickPropertyForm_LS,LID_1)/*"明るさ"*/;
    VValue=0;
}

CameraChangeQuickPropertyForm::~CameraChangeQuickPropertyForm()
{
    delete ui;
}

void	CameraChangeQuickPropertyForm::ReadyParam(void)
{
    if(CameraQuickPropertyStr==/**/"Brighter")
        Attr=CameraQuickProperty_Brighter;
    else
    if(CameraQuickPropertyStr==/**/"Faster")
        Attr=CameraQuickProperty_Faster;
    else
    if(CameraQuickPropertyStr==/**/"SideBrighter")
        Attr=CameraQuickProperty_SideBrighter;

    VValue=0;
    if(Attr==CameraQuickProperty_Brighter){
        ui->toolButtonTitle   ->setText(LangSolver.GetString(CameraChangeQuickPropertyForm_LS,LID_2)/*"明るさ"*/);
    }
    if(Attr==CameraQuickProperty_Faster){
        ui->toolButtonTitle   ->setText(LangSolver.GetString(CameraChangeQuickPropertyForm_LS,LID_3)/*"速度"*/);
    }
    if(Attr==CameraQuickProperty_SideBrighter){
        ui->toolButtonTitle   ->setText(LangSolver.GetString(CameraChangeQuickPropertyForm_LS,LID_4)/*"周辺明るさ"*/);
    }

    ui->doubleSpinBoxValue->setValue(VValue);
    ui->toolButtonTitle->setText(TitleName);
}

void CameraChangeQuickPropertyForm::on_toolButtonDown_clicked()
{
    VValue--;
    ui->doubleSpinBoxValue->setValue(VValue);

	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdCameraChangeQuickProperty	RCmd(GetLayersBase(),sRoot,sName,globalPage);
        RCmd.Attr   =Attr;
        RCmd.VValue =VValue;
		RCmd.Send(NULL,globalPage,0);
	}
}

void CameraChangeQuickPropertyForm::on_toolButtonUp_clicked()
{
    VValue++;
    ui->doubleSpinBoxValue->setValue(VValue);
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdCameraChangeQuickProperty	RCmd(GetLayersBase(),sRoot,sName,globalPage);
        RCmd.Attr   =Attr;
        RCmd.VValue =VValue;
		RCmd.Send(NULL,globalPage,0);
	}
}

void CameraChangeQuickPropertyForm::on_doubleSpinBoxValue_valueChanged(double)
{
    double  VValue=ui->doubleSpinBoxValue->value();
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdCameraChangeQuickProperty	RCmd(GetLayersBase(),sRoot,sName,globalPage);
        RCmd.Attr   =Attr;
        RCmd.VValue =VValue;
		RCmd.Send(NULL,globalPage,0);
	}
}

void	CameraChangeQuickPropertyForm::TransmitDirectly(GUIDirectMessage *packet)
{
    CmdCameraChangeQuickProperty    *CmdCameraChangeQuickPropertyVar=dynamic_cast<CmdCameraChangeQuickProperty *>(packet);
    if(CmdCameraChangeQuickPropertyVar!=NULL){
        VValue=CmdCameraChangeQuickPropertyVar->VValue;
        ui->doubleSpinBoxValue->setValue(VValue);
	    for(int page=0;page<GetPageNumb();page++){
	    	int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
	    	GUICmdCameraChangeQuickProperty	RCmd(GetLayersBase(),sRoot,sName,globalPage);
            RCmd.Attr   =CmdCameraChangeQuickPropertyVar->Attr;
            RCmd.VValue =VValue;
	    	RCmd.Send(NULL,globalPage,0);
	    }
        return;
    }
    CmdReqCurrentCameraChangeQuickProperty  *CmdReqCurrentCameraChangeQuickPropertyVar=dynamic_cast<CmdReqCurrentCameraChangeQuickProperty *>(packet);
    if(CmdReqCurrentCameraChangeQuickPropertyVar!=NULL){
        CmdReqCurrentCameraChangeQuickPropertyVar->Attr=Attr;
        CmdReqCurrentCameraChangeQuickPropertyVar->VValue=VValue;
        return;
    }
    CmdCameraAdjustment *CmdCameraAdjustmentVar=dynamic_cast<CmdCameraAdjustment *>(packet);
    if(CmdCameraAdjustmentVar!=NULL){
        ui->toolButtonAdjustment->setChecked(CmdCameraAdjustmentVar->ON);
        return;
    }
}
static	bool TargetFunctionPaintLast(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL && DImage->IsShown()==true){
		CameraChangeQuickPropertyForm	*Form=dynamic_cast<CameraChangeQuickPropertyForm *>(Obj);
		if(Form!=NULL && DImage->GetTargetPage()==Form->GetTargetPage()){
			DImage->LockPaintMutex();
			if(Form->GetLayersBase()->TryLockWeakDraw()==true){
				Form->Draw(DImage,pnt,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());
				Form->GetLayersBase()->UnlockWeakDraw();
			}
			DImage->UnlockPaintMutex();
		}
	}
	return true;
}
static  bool FunctionDrawEnd(FunctionServerClass *TargetObj,GUIFormBase *TartgetForm)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TartgetForm);
	if(DImage!=NULL){
        CameraChangeQuickPropertyForm   *p=dynamic_cast<CameraChangeQuickPropertyForm *>(TargetObj);
        if(p!=NULL){
            FlexArea    Area;
            DisplayImage::ToFlexArea(*DImage->GetRawSDataPoint(),Area);
            p->SetReferenceArea(Area);
        }
    }
    return true;
}
void CameraChangeQuickPropertyForm::on_toolButtonTitle_clicked()
{
    GUIFormBase	*f=GetLayersBase()->FindByName(LinkPanelInst);
    if(f==NULL){
        return;
    }
    DisplayImage    *Disp=dynamic_cast<DisplayImage *>(f);
    if(Disp!=NULL){
        if(ui->toolButtonTitle->isChecked()==true){
            SavedDrawingMode=Disp->GetDrawMode();
            Disp->SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
        }
        else{
            Disp->SetModeByOthers(SavedDrawingMode,Qt::red);
        }
    }
    DisplayImageHooked  *h=dynamic_cast<DisplayImageHooked *>(f);
    if(h==NULL){
        return;
    }
    if(ui->toolButtonTitle->isChecked()==true){
        h->SetHookInDrawEnd     (this	,FunctionDrawEnd);
        h->SetHookInPaintLast   (this   ,TargetFunctionPaintLast);
    }
    else{
        h->ReleaseHook(this);
    }
    f->Repaint();
}
void	CameraChangeQuickPropertyForm::Draw	(DisplayImage *DImage,QPainter &pnt	,double ZoomRate,int movx ,int movy)
{
    QRgb    Col=qRgba(255,128,0,100);
    if(ReferenceImage.width() !=DImage->GetCanvasWidth()
    || ReferenceImage.height()!=DImage->GetCanvasHeight()){
        ReferenceImage=QImage(DImage->GetCanvasWidth(),DImage->GetCanvasHeight()
                            ,QImage::Format_ARGB32);
    }
    ReferenceImage.fill(qRgba(0,0,0,0));
    ReferenceArea.DrawAlpha(0,0,&ReferenceImage,Col,ZoomRate,movx,movy);
    pnt.drawImage(0,0,ReferenceImage);
}

void	CameraChangeQuickPropertyForm::ShowInPlayer(int64 shownInspectionID)
{
    if(Attr==CameraQuickProperty_Brighter){
        if(ui->toolButtonAdjustment->isChecked()==true){
            if(RegularColor.R!=0.0 || RegularColor.G!=0.0 || RegularColor.B!=0.0){
                FloatRGBColor   CurrentColor;
	            IntList PageList;
	            GetLayersBase()->GetLocalPageFromArea(ReferenceArea,PageList);
	            for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
	            	int	page=P->GetValue();
	            	DataInPage	*pdata=GetLayersBase()->GetPageData(page);
	            	FlexArea	A=ReferenceArea;
	            	pdata->ClipMoveAreaFromGlobal(A);
	            	if(A.GetPatternByte()>0){
	            		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
	            		GUICmdReqBrightness	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	            		RCmd.ReferenceArea=A;
	            		GUICmdAckBrightness	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
	            		if(RCmd.Send(GlobalPage,0,ACmd)==true){
                            CurrentColor=ACmd.CurrentColor;
                            break;
                        }
                    }
                }
	            double	dR=CurrentColor.R-RegularColor.R;
	            double	dG=CurrentColor.G-RegularColor.G;
	            double	dB=CurrentColor.B-RegularColor.B;

                double  VValue=ui->doubleSpinBoxValue->value();
               if(dR>0 && dG>0 && dB>0){
                   double   Len=sqrt((dR*dR+dG*dG+dB*dB)/3.0);
                   double   dV=Len/20.0;
                   ui->doubleSpinBoxValue->setValue(VValue-dV);
                   on_doubleSpinBoxValue_valueChanged(0);
               }
               else
               if(dR<0 && dG<0 && dB<0){
                   double   Len=sqrt((dR*dR+dG*dG+dB*dB)/3.0);
                   double   dV=Len/20.0;
                   ui->doubleSpinBoxValue->setValue(VValue+dV);
                   on_doubleSpinBoxValue_valueChanged(0);
               }
            }
        }
    }
}
void	CameraChangeQuickPropertyForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
    //LoadMasterSpecifiedBroadcaster      *L1Var=dynamic_cast<LoadMasterSpecifiedBroadcaster *>(v);
    CreateNewMasterSpecifiedBroadcaster *L2Var=dynamic_cast<CreateNewMasterSpecifiedBroadcaster *>(v);
    if(L2Var!=NULL){
        RegularColor.SetColor(0,0,0);
        ReferenceArea.Clear();
        return;
    }
}
void    CameraChangeQuickPropertyForm::SetReferenceArea(FlexArea &Area)
{
    ReferenceArea=Area;

	IntList PageList;
	GetLayersBase()->GetLocalPageFromArea(ReferenceArea,PageList);
	for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
		int	page=P->GetValue();
		DataInPage	*pdata=GetLayersBase()->GetPageData(page);
		FlexArea	A=ReferenceArea;
		pdata->ClipMoveAreaFromGlobal(A);
		if(A.GetPatternByte()>0){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqBrightness	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.ReferenceArea=A;
			GUICmdAckBrightness	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
			if(RCmd.Send(GlobalPage,0,ACmd)==true){
                RegularColor=ACmd.CurrentColor;
                break;
            }
        }
    }
}

bool	CameraChangeQuickPropertyForm::SaveContent(QIODevice *f)
{
    int Ver=2;
    if(::Save(f,Ver)==false)            return false;
    if(ReferenceArea.Save(f)==false)    return false;
    if(RegularColor.Save(f)==false)     return false;

    double  VValue=ui->doubleSpinBoxValue->value();
    if(::Save(f,VValue)==false)            return false;

    return true;
}
bool	CameraChangeQuickPropertyForm::LoadContent(QIODevice *f)
{
    ReferenceArea.Clear();
    RegularColor.SetColor(0,0,0);

    int Ver;
    if(::Load(f,Ver)==false)            return false;
    if(ReferenceArea.Load(f)==false)    return false;
    if(RegularColor.Load(f)==false)     return false;

    if(Ver>=2){
        double  VValue;
        if(::Load(f,VValue)==false)            return false;
	    for(int page=0;page<GetPageNumb();page++){
	    	int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
	    	GUICmdCameraChangeQuickProperty	RCmd(GetLayersBase(),sRoot,sName,globalPage);
            RCmd.Attr   =Attr;
            RCmd.VValue =VValue;
	    	RCmd.Send(NULL,globalPage,0);
	    }
        ui->doubleSpinBoxValue->setValue(VValue);
    }
    return true;
}

//===============================================================================

GUICmdCameraChangeQuickProperty::GUICmdCameraChangeQuickProperty(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdCameraChangeQuickProperty::Load(QIODevice *f)
{
	int32	d;
	if(::Load(f,d)==false)
		return false;
	Attr=(CameraQuickProperty)d;
	if(::Load(f,VValue)==false)
		return false;
	return true;
}
bool	GUICmdCameraChangeQuickProperty::Save(QIODevice *f)
{
	int32	d=(int32)Attr;
	if(::Save(f,d)==false)
		return false;
	if(::Save(f,VValue)==false)
		return false;
	return true;
}

void	GUICmdCameraChangeQuickProperty::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
    EntryPointBase	*E=GetLayersBase()->GetEntryPoint();
    if(E!=NULL){
        ExecuteInspectBase	*B=E->GetExecuteInspect();
        if(B!=NULL){
            for(int i=0;i<B->GetAllocatedCameraCount();i++){
                CameraClass *C=B->GetCamera(i);
                if(C!=NULL){
                    C->SetQuickProperty(Attr, VValue);
                }
            }
        }
    }
}

//===============================================================================
GUICmdReqBrightness::GUICmdReqBrightness(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqBrightness::Load(QIODevice *f)
{
    if(ReferenceArea.Load(f)==false)    return false;
    return true;
}
bool	GUICmdReqBrightness::Save(QIODevice *f)
{
    if(ReferenceArea.Save(f)==false)    return false;
    return true;
}

void	GUICmdReqBrightness::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckBrightness	*SendBack=GetSendBack(GUICmdAckBrightness,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

    double  Col[3];
    Col[0]=0;
    Col[1]=0;
    Col[2]=0;
    DataInPage  *Pg=GetLayersBase()->GetPageData(localPage);
    for(int layer=0;layer<GetLayerNumb(localPage) && layer<3;layer++){
        DataInLayer *Ly=Pg->GetLayerData(layer);
        ImageBuffer &B=Ly->GetTargetBuff();
        Col[layer]=ReferenceArea.GetAverage(B,0,0);
    }
    SendBack->CurrentColor.SetColor(Col[0],Col[1],Col[2]);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckBrightness::GUICmdAckBrightness(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckBrightness::Load(QIODevice *f)
{
    if(CurrentColor.Load(f)==false)    return false;
    return true;
}
bool	GUICmdAckBrightness::Save(QIODevice *f)
{
    if(CurrentColor.Save(f)==false)    return false;
    return true;
}
