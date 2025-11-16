#include "ColorDifferenceResource.h"
#include "ColorDifferenceForm.h"
#include "ui_ColorDifferenceForm.h"
#include "XColorDifference.h"
#include "XColorDifferenceLibrary.h"
#include "XDataInLayerCommander.h"
#include "swap.h"
#include "XCrossObj.h"
#include "XColorSpace.h"
#include "SHowFlowGraphDialog.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

HSVMap::HSVMap(ColorDifferenceForm *p)
	:Parent(p)
{
	V=255;
	FlapToShowThreshold	=false;
	TM.setSingleShot(false);
	TM.setInterval(300);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}

void	HSVMap::SetV(int v)
{
	V=Clipping(v,0,255);
	repaint();
}
void HSVMap::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);

	HSVImageMap.fill(Qt::white);
	int	L=min(width(),height());
	int	R=L/2;
	int	Cx=width()/2;
	int	Cy=height()/2;
	ZoomRate=((double)L)/256.0;
	for(int y=-R;y<=R;y++){
		QRgb	*d=(QRgb *)HSVImageMap.scanLine(Cy+y);
		for(int x=-R;x<=R;x++){
			double	r=hypot(x,y);
			double	s=r*255/R;
			double	h=GetSita(x,y);
			if(s<256 && r<=V){
				int	R ,G ,B;
				HSV2RGB(h*360.0/(2*M_PI),s ,V ,R ,G ,B);
				if(FlapToShowThreshold==true && Parent->IsInsideInCurrentColor(R,G,B)==true){
					d[Cx+x]=qRgb(255,255,255);
				}
				else
				if(FlapToShowThreshold==true && Parent->IsInsideInThresholdOK(R,G,B)==true){
					d[Cx+x]=qRgb(0,255,0);
				}
				else
				if(FlapToShowThreshold==true && Parent->IsInsideInThresholdNG(R,G,B)==true){
					d[Cx+x]=qRgb(255,0,0);
				}
				else{
					d[Cx+x]=qRgb(R,G,B);
				}
			}
		}
	}
	Pnt.drawImage(0,0,HSVImageMap);
}
void HSVMap::mouseReleaseEvent ( QMouseEvent * event )
{
	int	L=min(width(),height());
	int	R=L/2;
	int	Cx=width()/2;
	int	Cy=height()/2;
	int	x=event->pos().x()-Cx;
	int	y=event->pos().y()-Cy;
	double	r=hypot(x,y);
	double	s=r*255/R;
	double	h=GetSita(x,y);
	if(r<=V){
		int	R ,G ,B;
		HSV2RGB(h*360.0/(2*M_PI),s ,V ,R ,G ,B);
		emit	SignalClickRGB(R,G,B);
	}
}
void HSVMap::resizeEvent ( QResizeEvent * event )
{
	HSVImageMap=QImage(width(),height(),QImage::Format_RGB32);
	repaint();
}
void	HSVMap::SlotTimeOut()
{
	FlapToShowThreshold=!FlapToShowThreshold;
	repaint();
}

//===============================================================
ColorDifferenceForm::ColorDifferenceForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base)
	,PasswordInQWodget(Base,this)
	,PanelHSVMap(this)
    ,ui(new Ui::ColorDifferenceForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	IData=NULL;

	PanelHSVMap.setParent(ui->frame);
	PanelHSVMap.setGeometry(ui->frameMap->geometry());
	connect(&PanelHSVMap,SIGNAL(SignalClickRGB(int,int,int)),this,SLOT(SlotClickRGB(int,int,int)));

	ui->tableWidgetHSVInfo->setColumnWidth(0,84);
	ui->tableWidgetHSVInfo->setColumnWidth(1,84);
	ui->tableWidgetHSVInfo->setColumnWidth(2,84);

	InstallOperationLog(this);
}

ColorDifferenceForm::~ColorDifferenceForm()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
	
	delete ui;
}

void	ColorDifferenceForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	ShowOKColorList();
	ShowNGColorList();
	ShowThreshold();
	Calc();
}
void	ColorDifferenceForm::ShowThreshold(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			{
				ColorDifferenceItem	*BData=dynamic_cast<ColorDifferenceItem *>(DA);
				if(BData!=NULL){
					ui->frameThreshold->setEnabled(true);
					int	ItemID=BData->GetID();
					setWindowTitle(QString(/**/"ItemID=")+QString::number(ItemID));
					ui->lineEditItemName			->setText(BData->GetItemName());
					const	ColorDifferenceThreshold	*RThr=BData->GetThresholdR(GetLayersBase());
					ui->doubleSpinBoxAdoptedRate->setValue(RThr->AdoptedRate	);
					ui->doubleSpinBoxTHDeltaE	->setValue(RThr->THDeltaE		);
					ui->comboBoxJudgeMethod			->setCurrentIndex(RThr->JudgeMethod);
					ui->checkBoxOutputConstantly	->setChecked(BData->OutputConstantly);
					ui->doubleSpinBoxdH				->setValue(RThr->dH);
					ui->doubleSpinBoxdSL			->setValue(RThr->dSL);
					ui->doubleSpinBoxdSH			->setValue(RThr->dSH);
					ui->doubleSpinBoxdVL			->setValue(RThr->dVL);
					ui->doubleSpinBoxdVH			->setValue(RThr->dVH);
					ui->checkBoxAdaptAlignment		->setChecked(RThr->AdaptAlignment);
				}
			}
			{
				ColorDifferenceRegulation	*BData=dynamic_cast<ColorDifferenceRegulation *>(DA);
				if(BData!=NULL){
					ui->frameThreshold->setEnabled(false);
					int	ItemID=BData->GetID();
					setWindowTitle(QString(/**/"ItemID=")+QString::number(ItemID));
					ui->lineEditItemName			->setText(BData->GetItemName());
					const	ColorDifferenceThreshold	*RThr=BData->GetThresholdR(GetLayersBase());
					ui->checkBoxAdaptAlignment		->setChecked(RThr->AdaptAlignment);
				}
			}
		}
	}
}
bool	ColorDifferenceForm::IsInsideInThresholdOK(int R,int G,int B)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			ColorDifferenceItem	*BData=dynamic_cast<ColorDifferenceItem *>(DA);
			if(BData!=NULL){
				return BData->OKBrightness.IsInclude(R,G,B,3);
			}
		}
	}
	return false;
}

bool	ColorDifferenceForm::IsInsideInThresholdNG(int R,int G,int B)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			ColorDifferenceItem	*BData=dynamic_cast<ColorDifferenceItem *>(DA);
			if(BData!=NULL){
				return BData->NGBrightness.IsInclude(R,G,B,3);
			}
		}
	}
	return false;
}

bool	ColorDifferenceForm::IsInsideInCurrentColor(int R,int G,int B)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorDifferenceItem	*BData=dynamic_cast<ColorDifferenceItem *>(DA);
		if(BData!=NULL){
			double	dR=R-BData->TargetColor.Red.GetFloat();
			double	dG=G-BData->TargetColor.Green.GetFloat();
			double	dB=B-BData->TargetColor.Blue.GetFloat();
			double	d=sqrt(dR*dR+dG*dG+dB*dB);
			if(d<=4){
				return true;
			}
		}
	}
	return false;
}

void ColorDifferenceForm::on_verticalSliderY_valueChanged(int value)
{
	int	Y=ui->verticalSliderY->value();
	ui->spinBoxK->setValue(Y);
	PanelHSVMap.SetV(Y);
}

void ColorDifferenceForm::on_spinBoxK_valueChanged(int arg1)
{
	int	Y=ui->spinBoxK->value();
	ui->verticalSliderY->setValue(Y);
	PanelHSVMap.SetV(Y);
}

void ColorDifferenceForm::on_listWidgetOKBrightness_currentRowChanged(int currentRow)
{
	int	Row=ui->listWidgetOKBrightness->currentRow();
	if(Row<0)
		return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorDifferenceItem	*BData=dynamic_cast<ColorDifferenceItem *>(DA);
		if(BData==NULL)
			continue;
		RGBSample	*s=BData->OKBrightness[Row];
		if(s!=NULL){
			ShowRGB(s->GetRed(),s->GetGreen(),s->GetBlue());
			break;
		}
	}
}

void ColorDifferenceForm::on_listWidgetNGBrightness_currentRowChanged(int currentRow)
{
	int	Row=ui->listWidgetNGBrightness->currentRow();
	if(Row<0)
		return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorDifferenceItem	*BData=dynamic_cast<ColorDifferenceItem *>(DA);
		if(BData==NULL)
			continue;
		RGBSample	*s=BData->NGBrightness[Row];
		if(s!=NULL){
			ShowRGB(s->GetRed(),s->GetGreen(),s->GetBlue());
			break;
		}
	}
}
void ColorDifferenceForm::on_listWidgetOKBrightness_pressed(const QModelIndex &index)
{
	on_listWidgetOKBrightness_currentRowChanged(0);
}

void ColorDifferenceForm::on_listWidgetNGBrightness_pressed(const QModelIndex &index)
{
	on_listWidgetNGBrightness_currentRowChanged(0);
}

void	ColorDifferenceForm::ShowRGB(int R, int G ,int B)
{
	double	h,s ,v;
	RGB2HSV(h,s ,v ,R ,G ,B);

	ui->verticalSliderY->setValue(v);
	ui->spinBoxK->setValue(v);
	PanelHSVMap.SetV(v);
}

void ColorDifferenceForm::on_toolButtonDelOKColor_clicked()
{
	int	Row=ui->listWidgetOKBrightness->currentRow();
	if(Row<0)
		return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorDifferenceItem	*BData=dynamic_cast<ColorDifferenceItem *>(DA);
		if(BData!=NULL){
			RGBSample	*s=BData->OKBrightness[Row];
			if(s!=NULL){
				BData->OKBrightness.RemoveList(s);
				delete	s;
				Calc();
			}
			ShowOKColorList();
		}
	}
}

void ColorDifferenceForm::on_toolButtonDelNGColor_clicked()
{
	int	Row=ui->listWidgetNGBrightness->currentRow();
	if(Row<0)
		return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorDifferenceItem	*BData=dynamic_cast<ColorDifferenceItem *>(DA);
		if(BData!=NULL){
			RGBSample	*s=BData->NGBrightness[Row];
			if(s!=NULL){
				BData->NGBrightness.RemoveList(s);
				delete	s;
				Calc();
			}
			ShowNGColorList();
		}
	}
}

void ColorDifferenceForm::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ColorDifferenceForm_LS,LID_8)/*"Reflecting ONE block threshold"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one block threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_OnlyOneColorDifference;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void ColorDifferenceForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ColorDifferenceForm_LS,LID_9)/*"Reflecting ALL blocks\' threshold"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all blocks threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_AllColorDifference;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}

	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void ColorDifferenceForm::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorDifferenceItem	*BData=dynamic_cast<ColorDifferenceItem *>(DA);
		if(BData==NULL)
			continue;
		GetDataFromWindow();
		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			ColorDifferenceLibrary	*ALib=dynamic_cast<ColorDifferenceLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			ColorDifferenceThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			ALib->AdoptedRate	=BData->GetThresholdR(GetLayersBase())->AdoptedRate;
			ALib->JudgeMethod	=BData->GetThresholdR(GetLayersBase())->JudgeMethod;
			ALib->THDeltaE		=BData->GetThresholdR(GetLayersBase())->THDeltaE	;
			ALib->dH			=BData->GetThresholdR(GetLayersBase())->dH			;
			ALib->dSL			=BData->GetThresholdR(GetLayersBase())->dSL		;
			ALib->dSH			=BData->GetThresholdR(GetLayersBase())->dSH		;
			ALib->dVL			=BData->GetThresholdR(GetLayersBase())->dVL		;
			ALib->dVH			=BData->GetThresholdR(GetLayersBase())->dVH		;
			ALib->AdaptAlignment=BData->GetThresholdR(GetLayersBase())->AdaptAlignment		;
			Container->Update(DestLib);
			return;
		}
	}
}

void ColorDifferenceForm::on_ButtonLoadFromLibrary_clicked()
{
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorDifferenceItem	*BData=dynamic_cast<ColorDifferenceItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(Container->GetLibrary(LibID ,SrcLib)==true){
			ColorDifferenceLibrary	*ALib=dynamic_cast<ColorDifferenceLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			ColorDifferenceThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			return;
		}
	}
}

void ColorDifferenceForm::on_ButtonClose_clicked()
{
	close();
}

void	ColorDifferenceForm::SlotClickRGB(int R ,int G ,int B)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			ColorDifferenceItem	*BData=dynamic_cast<ColorDifferenceItem *>(DA);
			if(BData!=NULL){
				if(ui->toolButtonAddOKColor->isChecked()==true){
					if(BData->OKBrightness.IsInclude(R,G,B,0)==false){
						RGBSample	*s=new RGBSample(qRgb(R,G,B),0);
						BData->OKBrightness.AppendList(s);
						Calc();
					}
					ShowOKColorList();
				}
				if(ui->toolButtonAddNGColor->isChecked()==true){
					if(BData->NGBrightness.IsInclude(R,G,B,0)==false){
						RGBSample	*s=new RGBSample(qRgb(R,G,B),0);
						BData->NGBrightness.AppendList(s);
						Calc();
					}
					ShowNGColorList();
				}
			}
		}
	}
}

void	ColorDifferenceForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			{
				ColorDifferenceItem	*BData=dynamic_cast<ColorDifferenceItem *>(DA);
				if(BData!=NULL){
					BData->SetItemName(ui->lineEditItemName->text());
					ColorDifferenceThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
					Thr->AdoptedRate	=ui->doubleSpinBoxAdoptedRate->value();
					Thr->THDeltaE		=ui->doubleSpinBoxTHDeltaE	->value();
					BData->OutputConstantly				=ui->checkBoxOutputConstantly	->isChecked();
					Thr->JudgeMethod	=ui->comboBoxJudgeMethod		->currentIndex();
					Thr->dH				=ui->doubleSpinBoxdH			->value();
					Thr->dSL			=ui->doubleSpinBoxdSL			->value();
					Thr->dSH			=ui->doubleSpinBoxdSH			->value();
					Thr->dVL			=ui->doubleSpinBoxdVL			->value();
					Thr->dVH			=ui->doubleSpinBoxdVH			->value();
					Thr->AdaptAlignment	=ui->checkBoxAdaptAlignment		->isChecked();
				}
			}
			{
				ColorDifferenceRegulation	*BData=dynamic_cast<ColorDifferenceRegulation *>(DA);
				if(BData!=NULL){
					BData->SetItemName(ui->lineEditItemName->text());
					ColorDifferenceThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
					//Thr->AdoptedRate	=ui->doubleSpinBoxAdoptedRate->value();
					//Thr->THDeltaE		=ui->doubleSpinBoxTHDeltaE	->value();
					//Thr->JudgeMethod	=ui->comboBoxJudgeMethod		->currentIndex();
					//Thr->dH				=ui->doubleSpinBoxdH			->value();
					//Thr->dSL			=ui->doubleSpinBoxdSL			->value();
					//Thr->dSH			=ui->doubleSpinBoxdSH			->value();
					//Thr->dVL			=ui->doubleSpinBoxdVL			->value();
					//Thr->dVH			=ui->doubleSpinBoxdVH			->value();
					Thr->AdaptAlignment	=ui->checkBoxAdaptAlignment		->isChecked();
				}
			}
		}
	}
}

void	ColorDifferenceForm::ShowOKColorList(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			ColorDifferenceItem	*BData=dynamic_cast<ColorDifferenceItem *>(DA);
			if(BData!=NULL){
				int	N=BData->OKBrightness.GetCount();
				ui->listWidgetOKBrightness->clear();
				for(int i=0;i<N;i++){
					ui->listWidgetOKBrightness->addItem(QString::number(i+1));
				}
			}
		}
	}
}

void	ColorDifferenceForm::ShowNGColorList(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			ColorDifferenceItem	*BData=dynamic_cast<ColorDifferenceItem *>(DA);
			if(BData!=NULL){
				int	N=BData->NGBrightness.GetCount();
				ui->listWidgetNGBrightness->clear();
				for(int i=0;i<N;i++){
					ui->listWidgetNGBrightness->addItem(QString::number(i+1));
				}
			}
		}
	}
}

void ColorDifferenceForm::on_toolButtonCurrentColor_clicked()
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorDifferenceItem	*BData=dynamic_cast<ColorDifferenceItem *>(DA);
		if(BData!=NULL){
			ShowRGB(BData->TargetColor.Red.GetInt(),BData->TargetColor.Green.GetInt(),BData->TargetColor.Blue.GetInt());
		}
	}
}

QString	ConvertColorToStr(PreciseColor &Col)
{
	return	 QString::number(Col.GetRed(),'f',1)
			+QString(/**/",")
			+QString::number(Col.GetGreen(),'f',1)
			+QString(/**/",")
			+QString::number(Col.GetBlue(),'f',1);
}
QString	ConvertColorToStr(double x, double y ,double z)
{
	return   QString::number(x,'f',1)
			+QString(/**/",")
			+QString::number(y,'f',1)
			+QString(/**/",")
			+QString::number(z,'f',1);
}


void	ColorDifferenceForm::Calc(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		{
			ColorDifferenceItem	*nBData=dynamic_cast<ColorDifferenceItem *>(DA);
			if(nBData!=NULL){

				GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
				PacketReq.BuildData(sRoot,sName,ColorDifferenceReqTryThresholdCommand ,ColorDifferenceSendTryThresholdCommand);
				ColorDifferenceItem	*BData=&((ColorDifferenceReqTryThreshold *)PacketReq.Data)->Threshold;
				((ColorDifferenceReqTryThreshold *)PacketReq.Data)->GlobalPage		=D->GlobalPage;
				((ColorDifferenceReqTryThreshold *)PacketReq.Data)->ColorDifferenceItemID	=DA->GetID();

				ColorDifferenceThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
				Thr->AdoptedRate	=ui->doubleSpinBoxAdoptedRate	->value();
				BData->OutputConstantly				=ui->checkBoxOutputConstantly	->isChecked();
				Thr->THDeltaE		=ui->doubleSpinBoxTHDeltaE		->value();
				Thr->JudgeMethod	=ui->comboBoxJudgeMethod		->currentIndex();
				Thr->dH				=ui->doubleSpinBoxdH			->value();
				Thr->dSL			=ui->doubleSpinBoxdSL			->value();
				Thr->dSH			=ui->doubleSpinBoxdSH			->value();
				Thr->dVL			=ui->doubleSpinBoxdVL			->value();
				Thr->dVH			=ui->doubleSpinBoxdVH			->value();
				Thr->AdaptAlignment	=ui->checkBoxAdaptAlignment		->isChecked();
				BData->OKBrightness		=nBData->OKBrightness;
				BData->NGBrightness		=nBData->NGBrightness;
				BData->MasterColor		=nBData->MasterColor;

				GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
				if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

					ColorDifferenceSendTryThreshold	*R=((ColorDifferenceSendTryThreshold *)PacketSend.Data);

					ui->lineEditLenOK	->setText(QString::number(R->LenOK ,'f',3));
					ui->lineEditLenNG	->setText(QString::number(R->LenNG ,'f',3));
					ui->lineEditDeltaE	->setText(QString::number(R->DeltaE,'f',3));
					::SetDataToTable(ui->tableWidgetResult,0,0,ConvertColorToStr(R->ReferenceColor1));
					::SetDataToTable(ui->tableWidgetResult,0,1,ConvertColorToStr(R->ReferenceColor2));
					::SetDataToTable(ui->tableWidgetResult,0,2,ConvertColorToStr(R->MasterColor));
					::SetDataToTable(ui->tableWidgetResult,0,3,ConvertColorToStr(R->TargetColor));
					double	H1,S1,V1;
					RGB2HSV(H1,S1,V1 ,R->ReferenceColor1.GetRed(),R->ReferenceColor1.GetGreen(),R->ReferenceColor1.GetBlue());
					::SetDataToTable(ui->tableWidgetResult,1,0,ConvertColorToStr(H1,S1,V1));
					RGB2HSV(H1,S1,V1 ,R->ReferenceColor2.GetRed(),R->ReferenceColor2.GetGreen(),R->ReferenceColor2.GetBlue());
					::SetDataToTable(ui->tableWidgetResult,1,1,ConvertColorToStr(H1,S1,V1));
					RGB2HSV(H1,S1,V1 ,R->MasterColor.GetRed(),R->MasterColor.GetGreen(),R->MasterColor.GetBlue());
					::SetDataToTable(ui->tableWidgetResult,1,2,ConvertColorToStr(H1,S1,V1));
					//RGB2HSV(H,S,V ,R->TargetColor.GetRed(),R->TargetColor.GetGreen(),R->TargetColor.GetBlue());
					if(R->StatisticData.TargetH==0 && R->StatisticData.TargetS==0 && R->StatisticData.TargetV==0){
						RGB2HSV(H1,S1,V1 ,R->TargetColor.GetRed(),R->TargetColor.GetGreen(),R->TargetColor.GetBlue());
						::SetDataToTable(ui->tableWidgetResult,1,3,ConvertColorToStr(H1,S1,V1));				}
					else{
						::SetDataToTable(ui->tableWidgetResult,1,3,ConvertColorToStr(R->StatisticData.TargetH,R->StatisticData.TargetS,R->StatisticData.TargetV));
					}

					double	X,Y,Z;
					double	L,A,B;
					RGB2XYZ(R->ReferenceColor1.Red.GetFloat(),R->ReferenceColor1.Green.GetFloat(),R->ReferenceColor1.Blue.GetFloat(),X ,Y ,Z);
					XYZ2LAB(X ,Y ,Z,L,A ,B);
					::SetDataToTable(ui->tableWidgetResult,2,0,ConvertColorToStr(L,A,B));
					RGB2XYZ(R->ReferenceColor2.Red.GetFloat(),R->ReferenceColor2.Green.GetFloat(),R->ReferenceColor2.Blue.GetFloat(),X ,Y ,Z);
					XYZ2LAB(X ,Y ,Z,L,A ,B);
					::SetDataToTable(ui->tableWidgetResult,2,1,ConvertColorToStr(L,A,B));
					RGB2XYZ(R->MasterColor.Red.GetFloat(),R->MasterColor.Green.GetFloat(),R->MasterColor.Blue.GetFloat(),X ,Y ,Z);
					XYZ2LAB(X ,Y ,Z,L,A ,B);
					::SetDataToTable(ui->tableWidgetResult,2,2,ConvertColorToStr(L,A,B));
					RGB2XYZ(R->TargetColor.Red.GetFloat(),R->TargetColor.Green.GetFloat(),R->TargetColor.Blue.GetFloat(),X ,Y ,Z);
					XYZ2LAB(X ,Y ,Z,L,A ,B);
					::SetDataToTable(ui->tableWidgetResult,2,3,ConvertColorToStr(L,A,B));

					::SetDataToTable(ui->tableWidgetHSVInfo,0,0,R->StatisticData.MasterH);
					::SetDataToTable(ui->tableWidgetHSVInfo,1,0,R->StatisticData.MasterS);
					::SetDataToTable(ui->tableWidgetHSVInfo,2,0,R->StatisticData.MasterV);
					::SetDataToTable(ui->tableWidgetHSVInfo,0,1,R->StatisticData.TargetH-R->StatisticData.MasterH);
					::SetDataToTable(ui->tableWidgetHSVInfo,1,1,R->StatisticData.TargetS-R->StatisticData.MasterS);
					::SetDataToTable(ui->tableWidgetHSVInfo,2,1,R->StatisticData.TargetV-R->StatisticData.MasterV);
					::SetDataToTable(ui->tableWidgetHSVInfo,0,2,R->StatisticData.SigmaH);
					::SetDataToTable(ui->tableWidgetHSVInfo,1,2,R->StatisticData.SigmaS);
					::SetDataToTable(ui->tableWidgetHSVInfo,2,2,R->StatisticData.SigmaV);
					break;
				}
			}
		}
		{
			ColorDifferenceRegulation	*nBData=dynamic_cast<ColorDifferenceRegulation *>(DA);
			if(nBData!=NULL){

				GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
				PacketReq.BuildData(sRoot,sName,ColorDifferenceReqTryThresholdCommand ,ColorDifferenceSendTryThresholdCommand);
				ColorDifferenceRegulation	*BData=&((ColorDifferenceReqTryThreshold *)PacketReq.Data)->ThresholdReg;
				((ColorDifferenceReqTryThreshold *)PacketReq.Data)->GlobalPage		=D->GlobalPage;
				((ColorDifferenceReqTryThreshold *)PacketReq.Data)->ColorDifferenceItemID	=DA->GetID();

				ColorDifferenceThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
				Thr->AdoptedRate	=ui->doubleSpinBoxAdoptedRate	->value();
				Thr->THDeltaE		=ui->doubleSpinBoxTHDeltaE		->value();
				Thr->JudgeMethod	=ui->comboBoxJudgeMethod		->currentIndex();
				Thr->dH				=ui->doubleSpinBoxdH			->value();
				Thr->dSL			=ui->doubleSpinBoxdSL			->value();
				Thr->dSH			=ui->doubleSpinBoxdSH			->value();
				Thr->dVL			=ui->doubleSpinBoxdVL			->value();
				Thr->dVH			=ui->doubleSpinBoxdVH			->value();
				Thr->AdaptAlignment	=ui->checkBoxAdaptAlignment		->isChecked();

				BData->MasterColor		=nBData->MasterColor;

				GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
				if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

					ColorDifferenceSendTryThreshold	*R=((ColorDifferenceSendTryThreshold *)PacketSend.Data);

					ui->lineEditLenOK	->setText(QString::number(R->LenOK ,'f',3));
					ui->lineEditLenNG	->setText(QString::number(R->LenNG ,'f',3));
					ui->lineEditDeltaE	->setText(QString::number(R->DeltaE,'f',3));
					::SetDataToTable(ui->tableWidgetResult,0,0,ConvertColorToStr(R->ReferenceColor1));
					::SetDataToTable(ui->tableWidgetResult,0,1,ConvertColorToStr(R->ReferenceColor2));
					::SetDataToTable(ui->tableWidgetResult,0,2,ConvertColorToStr(R->MasterColor));
					::SetDataToTable(ui->tableWidgetResult,0,3,ConvertColorToStr(R->TargetColor));
					double	H1,S1,V1;
					RGB2HSV(H1,S1,V1 ,R->ReferenceColor1.GetRed(),R->ReferenceColor1.GetGreen(),R->ReferenceColor1.GetBlue());
					::SetDataToTable(ui->tableWidgetResult,1,0,ConvertColorToStr(H1,S1,V1));
					RGB2HSV(H1,S1,V1 ,R->ReferenceColor2.GetRed(),R->ReferenceColor2.GetGreen(),R->ReferenceColor2.GetBlue());
					::SetDataToTable(ui->tableWidgetResult,1,1,ConvertColorToStr(H1,S1,V1));
					RGB2HSV(H1,S1,V1 ,R->MasterColor.GetRed(),R->MasterColor.GetGreen(),R->MasterColor.GetBlue());
					::SetDataToTable(ui->tableWidgetResult,1,2,ConvertColorToStr(H1,S1,V1));
					//RGB2HSV(H,S,V ,R->TargetColor.GetRed(),R->TargetColor.GetGreen(),R->TargetColor.GetBlue());
					if(R->StatisticData.TargetH==0 && R->StatisticData.TargetS==0 && R->StatisticData.TargetV==0){
						RGB2HSV(H1,S1,V1 ,R->TargetColor.GetRed(),R->TargetColor.GetGreen(),R->TargetColor.GetBlue());
						::SetDataToTable(ui->tableWidgetResult,1,3,ConvertColorToStr(H1,S1,V1));				}
					else{
						::SetDataToTable(ui->tableWidgetResult,1,3,ConvertColorToStr(R->StatisticData.TargetH,R->StatisticData.TargetS,R->StatisticData.TargetV));
					}

					double	X,Y,Z;
					double	L,A,B;
					RGB2XYZ(R->ReferenceColor1.Red.GetFloat(),R->ReferenceColor1.Green.GetFloat(),R->ReferenceColor1.Blue.GetFloat(),X ,Y ,Z);
					XYZ2LAB(X ,Y ,Z,L,A ,B);
					::SetDataToTable(ui->tableWidgetResult,2,0,ConvertColorToStr(L,A,B));
					RGB2XYZ(R->ReferenceColor2.Red.GetFloat(),R->ReferenceColor2.Green.GetFloat(),R->ReferenceColor2.Blue.GetFloat(),X ,Y ,Z);
					XYZ2LAB(X ,Y ,Z,L,A ,B);
					::SetDataToTable(ui->tableWidgetResult,2,1,ConvertColorToStr(L,A,B));
					RGB2XYZ(R->MasterColor.Red.GetFloat(),R->MasterColor.Green.GetFloat(),R->MasterColor.Blue.GetFloat(),X ,Y ,Z);
					XYZ2LAB(X ,Y ,Z,L,A ,B);
					::SetDataToTable(ui->tableWidgetResult,2,2,ConvertColorToStr(L,A,B));
					RGB2XYZ(R->TargetColor.Red.GetFloat(),R->TargetColor.Green.GetFloat(),R->TargetColor.Blue.GetFloat(),X ,Y ,Z);
					XYZ2LAB(X ,Y ,Z,L,A ,B);
					::SetDataToTable(ui->tableWidgetResult,2,3,ConvertColorToStr(L,A,B));

					::SetDataToTable(ui->tableWidgetHSVInfo,0,0,/**/"");
					::SetDataToTable(ui->tableWidgetHSVInfo,1,0,/**/"");
					::SetDataToTable(ui->tableWidgetHSVInfo,2,0,/**/"");
					::SetDataToTable(ui->tableWidgetHSVInfo,0,1,/**/"");
					::SetDataToTable(ui->tableWidgetHSVInfo,1,1,/**/"");
					::SetDataToTable(ui->tableWidgetHSVInfo,2,1,/**/"");
					::SetDataToTable(ui->tableWidgetHSVInfo,0,2,/**/"");
					::SetDataToTable(ui->tableWidgetHSVInfo,1,2,/**/"");
					::SetDataToTable(ui->tableWidgetHSVInfo,2,2,/**/"");
					break;
				}
			}
		}
	}
}

void ColorDifferenceForm::on_pushButtonSetItemName_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ColorDifferenceForm_LS,LID_14)/*"Transmiting ItemName all"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Transmit ItemName all");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemNameDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void ColorDifferenceForm::on_pushButtonOutputFlowList_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorDifferenceItem	*nBData=dynamic_cast<ColorDifferenceItem *>(DA);
		if(nBData!=NULL){
			GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
			PacketReq.BuildData(sRoot,sName,ColorDifferenceReqThresholdReqCommand ,ColorDifferenceReqThresholdSendCommand);
			((ColorDifferenceThresholdReq *)PacketReq.Data)->GlobalPage				=D->GlobalPage;
			((ColorDifferenceThresholdReq *)PacketReq.Data)->ColorDifferenceItemID	=DA->GetID();

			GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
			if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){
				nBData->TargetColor	=((ColorDifferenceThresholdSend *)PacketSend.Data)->TargetColor;
				nBData->ReferedCurrentColor	=((ColorDifferenceThresholdSend *)PacketSend.Data)->ReferedCurrentColor;
				
				SHowFlowGraphDialog	D(GetLayersBase(),nBData);
				D.exec();
				break;
			}
		}
	}
}
