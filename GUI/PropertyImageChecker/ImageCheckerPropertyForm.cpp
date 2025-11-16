#include "ChooseItemTypeFormResource.h"
#include "ImageCheckerPropertyForm.h"
#include "XImageChecker.h"
#include "XGeneralFunc.h"
#include "ChooseItemTypeForm.h"


extern	const	char	*sRoot;
extern	const	char	*sName;


ImageCheckerPropertyForm::ImageCheckerPropertyForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	PageTab.setParent(this);
		
	CurrentRegData=new ImageCheckerRegData[GetPageNumb()];

	ModeLightWhole	=true;
	ModeParamEntry	=true;
	ModeCamZ		=false;
	ModeResolution	=false;
	ModeSlide		=false;
	ModeIncline		=false;

	PageTab.move(ui.stackedWidget->geometry().left(),ui.stackedWidget->geometry().top()-32);
	PageTab.resize(ui.stackedWidget->width(),32);
	for(int page=0;page<GetPageNumb();page++){
		PageTab.addTab(QString::number(page));
	}
	connect(&PageTab,SIGNAL(currentChanged (int)),this,SLOT(SlotTabChanged(int)));
}

ImageCheckerPropertyForm::~ImageCheckerPropertyForm()
{
	delete	[]CurrentRegData;
	CurrentRegData=NULL;
}


QString	ImageCheckerPropertyForm::GetInitialFileName(void)
{
	return GetLayersBase()->GetUserPath()+QDir::separator()+QString(/**/"ImageCheckerInitial.dat");
}
void	ImageCheckerPropertyForm::Prepare(void)
{
	int	N=0;
	if(ModeLightWhole	==true)
		N++;
	else
		ui.toolButtonLightWhole->setVisible(false);

	if(ModeParamEntry	==true)
		N++;
	else
		ui.toolButtonParamEntry->setVisible(false);

	if(ModeCamZ			==true)
		N++;
	else
		ui.toolButtonCamZ	->setVisible(false);

	if(ModeResolution	==true)
		N++;
	else
		ui.toolButtonResolution->setVisible(false);

	if(ModeSlide		==true)
		N++;
	else
		ui.toolButtonSlide	->setVisible(false);

	if(ModeIncline		==true)
		N++;
	else
		ui.toolButtonIncline->setVisible(false);

	if(N!=0){
		int	ButtonHeight=ui.frame->height()/N;
		int	Y=0;
		if(ModeLightWhole	==true){
			ui.toolButtonLightWhole	->setGeometry(ui.toolButtonLightWhole->geometry().left(),Y
												, ui.toolButtonLightWhole->width(),ButtonHeight-1);
			Y+=ButtonHeight;
		}
		if(ModeParamEntry	==true){
			ui.toolButtonParamEntry	->setGeometry(ui.toolButtonParamEntry->geometry().left(),Y
												, ui.toolButtonParamEntry->width(),ButtonHeight-1);
			Y+=ButtonHeight;
		}
		if(ModeCamZ			==true){
			ui.toolButtonCamZ		->setGeometry(ui.toolButtonCamZ->geometry().left(),Y
												, ui.toolButtonCamZ->width(),ButtonHeight-1);
			Y+=ButtonHeight;
		}
		if(ModeResolution	==true){
			ui.toolButtonResolution	->setGeometry(ui.toolButtonResolution->geometry().left(),Y
												, ui.toolButtonResolution->width(),ButtonHeight-1);
			Y+=ButtonHeight;
		}
		if(ModeSlide		==true){
			ui.toolButtonSlide		->setGeometry(ui.toolButtonSlide->geometry().left(),Y
												, ui.toolButtonSlide->width(),ButtonHeight-1);
			Y+=ButtonHeight;
		}
		if(ModeIncline		==true){
			ui.toolButtonIncline	->setGeometry(ui.toolButtonIncline->geometry().left(),Y
												, ui.toolButtonIncline->width(),ButtonHeight-1);
			Y+=ButtonHeight;
		}
	}
	QString	FileName	=GetInitialFileName();
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		LoadContent(&File);
	}
	PageTab.setCurrentIndex(0);
	on_toolButtonLightWhole_clicked();
	CalcOnShow();
}
void	ImageCheckerPropertyForm::BuildForShow(void)
{
	QString	FileName	=GetInitialFileName();
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		LoadContent(&File);
	}
}


bool	ImageCheckerPropertyForm::SaveContent(QIODevice *f)
{
	//struct	ImageCheckerRegData Data;
	//GetFromWindow(Data);
	int	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	int	PageN=GetPageNumb();
	if(::Save(f,PageN)==false)
		return false;

	for(int page=0;page<PageN;page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqRegData	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdSendRegData	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.Send(GlobalPage,0,ACmd);
		CurrentRegData[page]=ACmd.RegData;

		if(f->write((const char *)&CurrentRegData[page],sizeof(CurrentRegData[page]))!=sizeof(CurrentRegData[page])){
			return false;
		}
	}
	return true;
}
bool	ImageCheckerPropertyForm::LoadContent(QIODevice *f)
{

	int	Ver;

	if(::Load(f,Ver)==false)
		return false;
	int	iPageN;
	if(::Load(f,iPageN)==false)
		return false;

	for(int page=0;page<GetPageNumb() && page<iPageN;page++){
		if(f->read((char *)&CurrentRegData[page],sizeof(CurrentRegData[page]))!=sizeof(CurrentRegData[page])){
			return false;
		}
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetRegData	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.RegData	=CurrentRegData[page];
		RCmd.Send(NULL,GlobalPage,0);
	}
	on_pushButtonMeasue_clicked();

	return true;
}


void	ImageCheckerPropertyForm::CalcOnShow(void)
{
	int	Page=PageTab.currentIndex();
	if(Page<0)
		return;
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Page);
	if(0<=GlobalPage){
		GUICmdReqRegData	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdSendRegData	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.Send(GlobalPage,0,ACmd);
		CurrentRegData[Page]=ACmd.RegData;
		SetToWindow(ACmd.RegData);
		SetValueToWindow(ACmd.RegData);
	}
}
void	ImageCheckerPropertyForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdImageCheckerDrawMode	*CmdImageCheckerDrawModeVar=dynamic_cast<CmdImageCheckerDrawMode*>(packet);
	if(CmdImageCheckerDrawModeVar!=NULL){
		if(ui.toolButtonCamZ->isChecked()==true){
			CmdImageCheckerDrawModeVar->Mode=ImageCheckerThreshold::_ImageCheckerRegCalcCamZ;
		}
		if(ui.toolButtonLightWhole->isChecked()==true){
			CmdImageCheckerDrawModeVar->Mode=ImageCheckerThreshold::_ImageCheckerRegCalcLightWhole;
		}
		return;
	}
	CmdSetImageCheckerDrawMode	*CmdSetImageCheckerDrawModeVar=dynamic_cast<CmdSetImageCheckerDrawMode *>(packet);
	if(CmdSetImageCheckerDrawModeVar!=NULL){
		switch(CmdSetImageCheckerDrawModeVar->Mode){
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamX:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamY:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamZ:
				ui.toolButtonCamZ->setChecked(true);
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamXTilt:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamYTilt:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamRot:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcStageFlat:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcStageVerocity:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcStageVConst:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcLightWhole:
				ui.toolButtonLightWhole->setChecked(true);
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcLightLeftRight:
				break;
		}
		return;
	}
	AddAreaPacket	*AddAreaPacketVar=dynamic_cast<AddAreaPacket *>(packet);
	if(AddAreaPacketVar!=NULL){
		/*
		ChooseItemTypeForm	Q(this);
		ChooseItemTypeForm::ItemType	RType=(ChooseItemTypeForm::ItemType)Q.exec();
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(AddAreaPacketVar->Area,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
			FlexArea	A=AddAreaPacketVar->Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				GUICmdAddManual	Cmd(GetLayersBase(),QString(sRoot),QString(sName),pdata->GetPage());
				Cmd.Area=A;
				//Cmd.LayerList=AddAreaPacketVar->LayerList;
				if(ui.toolButtonCamZ->isChecked()==true){
					Cmd.Mode=ImageCheckerThreshold::_ImageCheckerRegCalcCamZ;
				}
				if(ui.toolButtonLightWhole->isChecked()==true){
					Cmd.Mode=ImageCheckerThreshold::_ImageCheckerRegCalcLightWhole;
				}
				if(RType==ChooseItemTypeForm::Type_Pad){
					Cmd.Mode=ImageCheckerThreshold::_ImageCheckerRegCalcSlide;
				}
				else if(RType==ChooseItemTypeForm::Type_Line){
					Cmd.Mode=ImageCheckerThreshold::_ImageCheckerRegCalcResolution;
				}
				else if(RType==ChooseItemTypeForm::Type_Matching){
					Cmd.Mode=ImageCheckerThreshold::_ImageCheckerRegCalcMatching;
				}
				Cmd.SendOnly(pdata->GetPage(),0);
			}
		}
		*/
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(AddAreaPacketVar->Area,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			int	page=P->GetValue();
			DataInPage	*pdata=GetLayersBase()->GetPageData(page);
			FlexArea	A=AddAreaPacketVar->Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdAddManual	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
				Cmd.Area=A;
				//Cmd.LayerList=AddAreaPacketVar->LayerList;
				if(ui.toolButtonCamZ->isChecked()==true){
					Cmd.Mode=ImageCheckerThreshold::_ImageCheckerRegCalcCamZ;
				}
				if(ui.toolButtonLightWhole->isChecked()==true){
					Cmd.Mode=ImageCheckerThreshold::_ImageCheckerRegCalcLightWhole;
				}
				Cmd.SendOnly(GlobalPage,0);
			}
		}
		return;
	}
	CmdGetResultPacket	*CmdGetResultPacketVar=dynamic_cast<CmdGetResultPacket *>(packet);
	if(CmdGetResultPacketVar!=NULL){
		/*
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqValue	RCmd(GetLayersBase(),sRoot,sName,page);
			GUICmdAckValue	ACmd(GetLayersBase(),sRoot,sName,page);
			RCmd.Send(page,0,ACmd);
			CmdGetResultPacketVar->RegData[page]	=ACmd.RegData;
			CmdGetResultPacketVar->Effective[page]	=ACmd.Effective;
		}
		*/

		NPListPack<GUICmdPacketDim>	GUICmdDim;
		GUICmdReqValue	**RCmd=new GUICmdReqValue*[GetPageNumb()];
		GUICmdAckValue	**ACmd=new GUICmdAckValue*[GetPageNumb()];
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			RCmd[page]=new GUICmdReqValue(GetLayersBase(),sRoot,sName,GlobalPage);
			ACmd[page]=new GUICmdAckValue(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdDim.AppendList(new GUICmdPacketDim(RCmd[page],ACmd[page],GlobalPage,0));
		}
		GetLayersBase()->PacketSender(GUICmdDim,GetParamGlobal()->MaxWaitingCommMilisec);

		for(int page=0;page<GetPageNumb();page++){
			CmdGetResultPacketVar->RegData[page]	=ACmd[page]->RegData;
			CmdGetResultPacketVar->Effective[page]	=ACmd[page]->Effective;
		}
		for(int page=0;page<GetPageNumb();page++){
			delete	RCmd[page];
			delete	ACmd[page];
		}
		delete	[]RCmd;
		delete	[]ACmd;

		return;
	}
}

void	ImageCheckerPropertyForm::GetRegDataInPage(int Page,struct ImageCheckerRegData &Data)
{
	AlgorithmBase *BBase	=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ImageChecker");
	if(BBase!=NULL){
		ReqRegDataPacket	Cmd(GetLayersBase());
		AlgorithmInPageRoot		*P=BBase->GetPageData(Page);
		P->TransmitDirectly(&Cmd);
		Data=Cmd.RegData;
	}
}
void	ImageCheckerPropertyForm::SetRegDataInPage(int Page,struct ImageCheckerRegData &Data)
{
	AlgorithmBase *BBase	=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ImageChecker");
	if(BBase!=NULL){
		SetRegDataPacket	Cmd(GetLayersBase());
		Cmd.RegData=Data;
		AlgorithmInPageRoot		*P=BBase->GetPageData(Page);
		P->TransmitDirectly(&Cmd);
	}
}

void ImageCheckerPropertyForm::SetDrawMode(void)
{
	CmdImageCheckerDrawMode	Da(GetLayersBase());
	TransmitDirectly(&Da);
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdChangeDrawMode	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.Mode=Da.Mode;
		RCmd.Send(NULL,GlobalPage,0);
	}
	BroadcastShowInEdit();
}

void ImageCheckerPropertyForm::on_toolButtonCamZ_clicked()
{
	ui.stackedWidget->setCurrentIndex(0);
	SetDrawMode();

	int	Page=PageTab.currentIndex();
	if(Page<0)
		return;
	GetFromWindow(CurrentRegData[Page]);
	SetToWindow(CurrentRegData[Page]);
	SetValueToWindow(CurrentRegData[Page]);
}

void ImageCheckerPropertyForm::on_toolButtonLightWhole_clicked()
{
	ui.stackedWidget->setCurrentIndex(1);
	SetDrawMode();
	int	Page=PageTab.currentIndex();
	if(Page<0)
		return;
	GetFromWindow(CurrentRegData[Page]);
	SetToWindow(CurrentRegData[Page]);
	SetValueToWindow(CurrentRegData[Page]);
}

void ImageCheckerPropertyForm::on_toolButtonResolution_clicked()
{
	ui.stackedWidget->setCurrentIndex(2);
	SetDrawMode();
	int	Page=PageTab.currentIndex();
	if(Page<0)
		return;
	GetFromWindow(CurrentRegData[Page]);
	SetToWindow(CurrentRegData[Page]);
	SetValueToWindow(CurrentRegData[Page]);
}

void ImageCheckerPropertyForm::on_toolButtonSlide_clicked()
{
	ui.stackedWidget->setCurrentIndex(3);
	SetDrawMode();
	int	Page=PageTab.currentIndex();
	if(Page<0)
		return;
	GetFromWindow(CurrentRegData[Page]);
	SetToWindow(CurrentRegData[Page]);
	SetValueToWindow(CurrentRegData[Page]);
}

void ImageCheckerPropertyForm::on_toolButtonIncline_clicked()
{
	ui.stackedWidget->setCurrentIndex(5);
	SetDrawMode();
	int	Page=PageTab.currentIndex();
	if(Page<0)
		return;
	GetFromWindow(CurrentRegData[Page]);
	SetToWindow(CurrentRegData[Page]);
	SetValueToWindow(CurrentRegData[Page]);
}

void ImageCheckerPropertyForm::on_toolButtonParamEntry_clicked()
{
	ui.stackedWidget->setCurrentIndex(4);
	SetDrawMode();
	int	Page=PageTab.currentIndex();
	if(Page<0)
		return;
	GetFromWindow(CurrentRegData[Page]);
	SetToWindow(CurrentRegData[Page]);
	SetValueToWindow(CurrentRegData[Page]);
}

void ImageCheckerPropertyForm::SlotTabChanged ( int index )
{
	CalcOnShow();
}



void ImageCheckerPropertyForm::GetFromWindow(ImageCheckerRegData &Data)
{
	Data.RegCalcCamZ.StandardValue		=ui.doubleSpinBoxRegCamZ->value();
	Data.RegCalcCamZ.LLimit				=ui.doubleSpinBoxLowCamZ->value();
	Data.RegCalcCamZ.HLimit				=ui.doubleSpinBoxHighCamZ->value();

	Data.RegCalcLightWhole[0].StandardValue	=ui.doubleSpinBoxRegLightWholeR->value();
	Data.RegCalcLightWhole[0].LLimit		=ui.doubleSpinBoxLowLightWholeR->value();
	Data.RegCalcLightWhole[0].HLimit		=ui.doubleSpinBoxHighLightWholeR->value();

	Data.RegCalcLightWhole[1].StandardValue	=ui.doubleSpinBoxRegLightWholeG->value();
	Data.RegCalcLightWhole[1].LLimit		=ui.doubleSpinBoxLowLightWholeG->value();
	Data.RegCalcLightWhole[1].HLimit		=ui.doubleSpinBoxHighLightWholeG->value();

	Data.RegCalcLightWhole[2].StandardValue	=ui.doubleSpinBoxRegLightWholeB->value();
	Data.RegCalcLightWhole[2].LLimit		=ui.doubleSpinBoxLowLightWholeB->value();
	Data.RegCalcLightWhole[2].HLimit		=ui.doubleSpinBoxHighLightWholeB->value();

	Data.RegCalcResolution.Resolution	=ui.doubleSpinBoxRegResolution->value();
	Data.RegCalcResolution.PosY			=ui.doubleSpinBoxRegResolutionPosY->value();
	Data.RegCalcResolution.DifResLow	=ui.doubleSpinBoxLowDifResolution->value();
	Data.RegCalcResolution.DifResHigh	=ui.doubleSpinBoxHighDifResolution->value();

	Data.RegCalcSlide.XPos				=ui.doubleSpinBoxRegSlideX->value();
	Data.RegCalcSlide.YPos				=ui.doubleSpinBoxRegSlideY->value();
	Data.RegCalcSlide.DifPosLow			=ui.doubleSpinBoxLowDifSlide->value();
	Data.RegCalcSlide.DifPosHigh		=ui.doubleSpinBoxHighDifSlide->value();

	Data.RegCalcIncline.VarTop			=ui.doubleSpinBoxRegInclineTop->value();
	Data.RegCalcIncline.VarLeft			=ui.doubleSpinBoxRegInclineLeft->value();
	Data.RegCalcIncline.VarRight		=ui.doubleSpinBoxRegInclineRight->value();
	Data.RegCalcIncline.VarBottom		=ui.doubleSpinBoxRegInclineBottom->value();
	Data.RegCalcIncline.DifLow			=ui.doubleSpinBoxLowDifIncline->value();
	Data.RegCalcIncline.DifHigh			=ui.doubleSpinBoxHighDifIncline->value();

	Data.RegParamEntry.CamA				=ui.doubleSpinBoxParamEntryCamA	->value();
	Data.RegParamEntry.CamB				=ui.doubleSpinBoxParamEntryCamB	->value();
	Data.RegParamEntry.LightA			=ui.doubleSpinBoxParamEntryLightA->value();
	Data.RegParamEntry.LightB			=ui.doubleSpinBoxParamEntryLightB->value();
}

void ImageCheckerPropertyForm::SetToWindow(ImageCheckerRegData &Data)
{
	ui.doubleSpinBoxRegCamZ	->setValue(Data.RegCalcCamZ.StandardValue);
	ui.doubleSpinBoxLowCamZ	->setValue(Data.RegCalcCamZ.LLimit);
	ui.doubleSpinBoxHighCamZ->setValue(Data.RegCalcCamZ.HLimit);

	ui.doubleSpinBoxRegLightWholeR	->setValue(Data.RegCalcLightWhole[0].StandardValue);
	ui.doubleSpinBoxLowLightWholeR	->setValue(Data.RegCalcLightWhole[0].LLimit);
	ui.doubleSpinBoxHighLightWholeR	->setValue(Data.RegCalcLightWhole[0].HLimit);

	ui.doubleSpinBoxRegLightWholeG	->setValue(Data.RegCalcLightWhole[1].StandardValue);
	ui.doubleSpinBoxLowLightWholeG	->setValue(Data.RegCalcLightWhole[1].LLimit);
	ui.doubleSpinBoxHighLightWholeG	->setValue(Data.RegCalcLightWhole[1].HLimit);

	ui.doubleSpinBoxRegLightWholeB	->setValue(Data.RegCalcLightWhole[2].StandardValue);
	ui.doubleSpinBoxLowLightWholeB	->setValue(Data.RegCalcLightWhole[2].LLimit);
	ui.doubleSpinBoxHighLightWholeB	->setValue(Data.RegCalcLightWhole[2].HLimit);

	ui.doubleSpinBoxRegResolution	->setValue(Data.RegCalcResolution.Resolution);
	ui.doubleSpinBoxRegResolutionPosY->setValue(Data.RegCalcResolution.PosY);
	ui.doubleSpinBoxLowDifResolution->setValue(Data.RegCalcResolution.DifResLow);
	ui.doubleSpinBoxHighDifResolution->setValue(Data.RegCalcResolution.DifResHigh);

	ui.doubleSpinBoxRegSlideX		->setValue(Data.RegCalcSlide.XPos);
	ui.doubleSpinBoxRegSlideY		->setValue(Data.RegCalcSlide.YPos);
	ui.doubleSpinBoxLowDifSlide		->setValue(Data.RegCalcSlide.DifPosLow);
	ui.doubleSpinBoxHighDifSlide	->setValue(Data.RegCalcSlide.DifPosHigh);

	ui.doubleSpinBoxRegInclineTop	->setValue(Data.RegCalcIncline.VarTop);
	ui.doubleSpinBoxRegInclineLeft	->setValue(Data.RegCalcIncline.VarLeft);
	ui.doubleSpinBoxRegInclineRight	->setValue(Data.RegCalcIncline.VarRight);
	ui.doubleSpinBoxRegInclineBottom->setValue(Data.RegCalcIncline.VarBottom);
	ui.doubleSpinBoxLowDifIncline	->setValue(Data.RegCalcIncline.DifLow);
	ui.doubleSpinBoxHighDifIncline	->setValue(Data.RegCalcIncline.DifHigh);

	ui.doubleSpinBoxParamEntryCamA	->setValue(Data.RegParamEntry.CamA	);
	ui.doubleSpinBoxParamEntryCamB	->setValue(Data.RegParamEntry.CamB	);
	ui.doubleSpinBoxParamEntryLightA->setValue(Data.RegParamEntry.LightA);
	ui.doubleSpinBoxParamEntryLightB->setValue(Data.RegParamEntry.LightB);
}

void ImageCheckerPropertyForm::SetValueToWindow(ImageCheckerRegData &Data)
{
	ui.doubleSpinBoxValueCamZ		->setValue(Data.RegCalcCamZ.Value		);
	ui.doubleSpinBoxValueCamZ2		->setValue(Data.RegCalcCamZ.Value2		);
	ui.doubleSpinBoxValueLightWholeR	->setValue(Data.RegCalcLightWhole[0].Value	);
	ui.doubleSpinBoxValueLightWholeG	->setValue(Data.RegCalcLightWhole[1].Value	);
	ui.doubleSpinBoxValueLightWholeB	->setValue(Data.RegCalcLightWhole[2].Value	);

	ui.doubleSpinBoxValueResolution->setValue(Data.RegCalcResolution.Value);

	ui.doubleSpinBoxValueSlideX		->setValue(Data.RegCalcSlide.Value);
	ui.doubleSpinBoxValueSlideY		->setValue(Data.RegCalcSlide.Value2);

	ui.doubleSpinBoxValueInclineTop		->setValue(Data.RegCalcIncline.Value);
	ui.doubleSpinBoxValueInclineLeft	->setValue(Data.RegCalcIncline.Value2);
	ui.doubleSpinBoxValueInclineRight	->setValue(Data.RegCalcIncline.Value3);
	ui.doubleSpinBoxValueInclineBottom	->setValue(Data.RegCalcIncline.Value4);
	ui.doubleSpinBoxInclineResultY		->setValue(Data.RegCalcIncline.Value5);
	ui.doubleSpinBoxInclineResultX		->setValue(Data.RegCalcIncline.Value6);

	ui.doubleSpinBoxParamEntryCamReq	->setValue(Data.RegParamEntry.ValueCam);
	//ui.doubleSpinBoxParamEntryLightReq	->setValue(Data.RegParamEntry.Value[0]);
	//ui.doubleSpinBoxParamEntryLightReq	->setValue(Data.RegParamEntry.Value[1]);
	//ui.doubleSpinBoxParamEntryLightReq	->setValue(Data.RegParamEntry.Value[2]);
}

void ImageCheckerPropertyForm::on_pushButtonMeasue_clicked()
{
	int	Page=PageTab.currentIndex();
	if(Page<0)
		return;
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Page);
	if(0<=GlobalPage){
		GUICmdReqValue	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckValue	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.Send(GlobalPage,0,ACmd);
		CurrentRegData[Page]=ACmd.RegData;

		//SetToWindow(CurrentRegData[Page]);
		SetValueToWindow(CurrentRegData[Page]);
	}
}

void ImageCheckerPropertyForm::on_pushButtonSetRegData_clicked()
{
	int	Page=PageTab.currentIndex();
	if(Page<0)
		return;
	struct	ImageCheckerRegData Data;
	GetFromWindow(Data);
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Page);
	if(0<=GlobalPage){
		GUICmdSetRegData	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.RegData	=Data;
		RCmd.Send(NULL,GlobalPage,0);

		QString	FileName	=GetInitialFileName();
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			SaveContent(&File);
		}
	}
}

//=======================================================================================

GUICmdAddManual::GUICmdAddManual(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAddManual::Load(QIODevice *f)
{
	if(Area.Load(f)==false){
		return false;
	}
	BYTE	d;
	if(::Load(f,d)==false){
		return false;
	}
	Mode=(ImageCheckerThreshold::__ImageCheckerRegMode)d;
	return true;
}
bool	GUICmdAddManual::Save(QIODevice *f)
{
	if(Area.Save(f)==false){
		return false;
	}
	BYTE	d=(BYTE)Mode;
	if(::Save(f,d)==false){
		return false;
	}
	return true;
}

void	GUICmdAddManual::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *BBase	=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ImageChecker");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*P=BBase->GetPageData(localPage);
		AddAreaPacket	Cmd(this);
		Cmd.Area=Area;
		Cmd.Mode=Mode;
		//Cmd.LayerList=LayerList;
		P->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=======================================================================================

GUICmdSetRegData::GUICmdSetRegData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetRegData::Load(QIODevice *f)
{
	if(f->read((char *)&RegData,sizeof(RegData))!=sizeof(RegData)){
		return false;
	}
	return true;
}
bool	GUICmdSetRegData::Save(QIODevice *f)
{
	if(f->write((const char *)&RegData,sizeof(RegData))!=sizeof(RegData)){
		return false;
	}
	return true;
}

void	GUICmdSetRegData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *BBase	=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ImageChecker");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*P=BBase->GetPageData(localPage);
		SetRegDataPacket	Cmd(this);
		Cmd.RegData=RegData;
		P->TransmitDirectly(&Cmd);
	}
	//SendAck(localPage);
}

//=======================================================================================

GUICmdReqRegData::GUICmdReqRegData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqRegData::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqRegData::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqRegData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendRegData	*SendBack=GetSendBack(GUICmdSendRegData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase *BBase	=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ImageChecker");
	ReqRegDataPacket	Cmd(this);
	if(BBase!=NULL){
		AlgorithmInPageRoot		*P=BBase->GetPageData(localPage);
		P->TransmitDirectly(&Cmd);
	}
	SendBack->RegData=Cmd.RegData;
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendRegData::GUICmdSendRegData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendRegData::Load(QIODevice *f)
{
	if(f->read((char *)&RegData,sizeof(RegData))!=sizeof(RegData)){
		return false;
	}
	return true;
}
bool	GUICmdSendRegData::Save(QIODevice *f)
{
	if(f->write((const char *)&RegData,sizeof(RegData))!=sizeof(RegData)){
		return false;
	}
	return true;
}

void	GUICmdSendRegData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================================

GUICmdReqValue::GUICmdReqValue(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}


bool	GUICmdReqValue::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqValue::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqValue::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckValue	*SendBack=GetSendBack(GUICmdAckValue,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase *BBase	=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ImageChecker");
	ReqValuePacket	Cmd(this);
	if(BBase!=NULL){
		AlgorithmInPageRoot		*P=BBase->GetPageData(localPage);
		P->TransmitDirectly(&Cmd);
	}
	SendBack->RegData=Cmd.RegData;
	SendBack->Effective=Cmd.Effective;
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckValue::GUICmdAckValue(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckValue::Load(QIODevice *f)
{
	if(f->read((char *)&RegData,sizeof(RegData))!=sizeof(RegData)){
		return false;
	}
	if(::Load(f,Effective)==false){
		return false;
	}
	return true;
}
bool	GUICmdAckValue::Save(QIODevice *f)
{
	if(f->write((const char *)&RegData,sizeof(RegData))!=sizeof(RegData)){
		return false;
	}
	if(::Save(f,Effective)==false){
		return false;
	}
	return true;
}

void	GUICmdAckValue::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================================
GUICmdChangeDrawMode::GUICmdChangeDrawMode(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdChangeDrawMode::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false){
		return false;
	}
	Mode=(ImageCheckerThreshold::__ImageCheckerRegMode)d;
	return true;
}
bool	GUICmdChangeDrawMode::Save(QIODevice *f)
{
	BYTE	d=(BYTE)Mode;
	if(::Save(f,d)==false){
		return false;
	}
	return true;
}

void	GUICmdChangeDrawMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyImageChecker" ,/**/"");
	if(GProp!=NULL){
		CmdSetImageCheckerDrawMode	Da(this);
		Da.Mode=Mode;
		GProp->TransmitDirectly(&Da);
	}
}



