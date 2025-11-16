#include "BCRInspectionResource.h"
#include "swap.h"
#include "XBCRInspection.h"
#include "DTKBarReader.h"
#include "DTKImage.h"
#include "XCriticalFunc.h"

//=================================================================
BCRInspectionInPage::BCRInspectionInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent)
{
	ModeParallel.ModeParallelExecuteProcessing=false;
}
void	BCRInspectionInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqBCodeList	*CmdReqBCodeListVar=dynamic_cast<CmdReqBCodeList *>(packet);
	if(CmdReqBCodeListVar!=NULL){
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			BCRInspectionItem	*Item=dynamic_cast<BCRInspectionItem *>(a);
			if(Item!=NULL){
				BCRList	*k=new BCRList();
				k->LocalPage	=GetPage();
				k->ItemID		=Item->GetID();
				Item->GetXY(k->X1,k->Y1,k->X2,k->Y2);
				k->BCRType		=Item->BCRType;
				k->CheckType	=Item->GetThresholdR()->CheckType;
				CmdReqBCodeListVar->Container->AppendList(k);
			}
		}
		return;
	}
	CmdReqBCodeTest	*CmdReqBCodeTestVar=dynamic_cast<CmdReqBCodeTest *>(packet);
	if(CmdReqBCodeTestVar!=NULL){
		AlgorithmItemRoot	*a=SearchIDItem(CmdReqBCodeTestVar->ItemID);
		if(a!=NULL){
			BCRInspectionItem	*Item=dynamic_cast<BCRInspectionItem *>(a);
			if(Item!=NULL){
				ImagePointerContainer ImageList;
				if(CmdReqBCodeTestVar->Mastered==true){
					Item->GetMasterBuffList(ImageList);
				}
				else{
					Item->GetTargetBuffList(ImageList);
				}

				if(Item->GetThresholdR()->CheckType==0){
					Item->Calc2D(ImageList);
					CmdReqBCodeTestVar->Result=Item->Result;
				}
				else
				if(Item->GetThresholdR()->CheckType==1){
					double MaxV;
					BCRGradeList	*MinL=Item->CheckQuality(ImageList,MaxV);
					if(MinL!=NULL){
						CmdReqBCodeTestVar->Result=MinL->Grade
												+QString(/**/" : ")
												+QString::number(MaxV,'f',2);
					}
					else{
						CmdReqBCodeTestVar->Result=QString::number(MaxV,'f',2);
					}
				}
				else
				if(Item->GetThresholdR()->CheckType==2){
					Item->Calc1D(ImageList);
					CmdReqBCodeTestVar->Result=Item->Result;
				}
				
			}
		}
		return;
	}
	AddBCRInspectionAreaPacket	*AddBCRInspectionAreaVar=dynamic_cast<AddBCRInspectionAreaPacket *>(packet);
	if(AddBCRInspectionAreaVar!=NULL){
		BCRInspectionItem	*Item=new BCRInspectionItem();
		Item->SetArea(AddBCRInspectionAreaVar->Area);
		Item->BCRType=AddBCRInspectionAreaVar->BCRType;
		AppendItem(Item);
		BCRInspectionThreshold	*WThr=Item->GetThresholdW();
		WThr->CheckType			=AddBCRInspectionAreaVar->CheckType;
		WThr->QuilityGrade		=AddBCRInspectionAreaVar->QuilityGrade;
		WThr->GradeList			=AddBCRInspectionAreaVar->GradeList;
		WThr->BarcodeOrientation=AddBCRInspectionAreaVar->BarcodeOrientation;
		WThr->BarcodeType		=AddBCRInspectionAreaVar->BarcodeType;
		WThr->BarcodeIsOnlyDigit=AddBCRInspectionAreaVar->BarcodeIsOnlyDigit;
		return;
	}
	CmdReqBCodeResults	*CmdReqBCodeResultsVar=dynamic_cast<CmdReqBCodeResults *>(packet);
	if(CmdReqBCodeResultsVar!=NULL){
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			BCRInspectionItem	*Item=dynamic_cast<BCRInspectionItem *>(a);
			if(Item!=NULL){
				CmdReqBCodeResultsVar->ResultBarcode.append(Item->Result);
			}
		}
		return;
	}
	CmdSetBCodeResults	*CmdSetBCodeResultsVar=dynamic_cast<CmdSetBCodeResults *>(packet);
	if(CmdSetBCodeResultsVar!=NULL){
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			BCRInspectionItem	*Item=dynamic_cast<BCRInspectionItem *>(a);
			if(Item!=NULL){
				Item->Result=CmdSetBCodeResultsVar->ResultBarcode;
				CmdSetBCodeResultsVar->OK=true;
			}
		}
		return;
	}
	CmdReqBCodeInfoByItem	*CmdReqBCodeInfoByItemVar=dynamic_cast<CmdReqBCodeInfoByItem *>(packet);
	if(CmdReqBCodeInfoByItemVar!=NULL){
		AlgorithmItemRoot	*a=SearchIDItem(CmdReqBCodeInfoByItemVar->ItemID);
		if(a!=NULL){
			BCRInspectionItem	*Item=dynamic_cast<BCRInspectionItem *>(a);
			if(Item!=NULL){
				const	BCRInspectionThreshold	*Thr=Item->GetThresholdR();

				CmdReqBCodeInfoByItemVar->CheckType			=Thr->CheckType		;
				CmdReqBCodeInfoByItemVar->QuilityGrade		=Thr->QuilityGrade	;
				CmdReqBCodeInfoByItemVar->GradeList			=Thr->GradeList		;
				CmdReqBCodeInfoByItemVar->BarcodeOrientation=Thr->BarcodeOrientation		;
				CmdReqBCodeInfoByItemVar->BarcodeType		=Thr->BarcodeType	;
				CmdReqBCodeInfoByItemVar->BarcodeIsOnlyDigit=Thr->BarcodeIsOnlyDigit;
			}
		}
		return;
	}
	CmdSetBCodeInfoByItem	*CmdSetBCodeInfoByItemVar=dynamic_cast<CmdSetBCodeInfoByItem *>(packet);
	if(CmdSetBCodeInfoByItemVar!=NULL){
		AlgorithmItemRoot	*a=SearchIDItem(CmdSetBCodeInfoByItemVar->ItemID);
		if(a!=NULL){
			BCRInspectionItem	*Item=dynamic_cast<BCRInspectionItem *>(a);
			if(Item!=NULL){
				BCRInspectionThreshold	*Thr=Item->GetThresholdW();

				Thr->CheckType			=CmdSetBCodeInfoByItemVar->CheckType			;
				Thr->QuilityGrade		=CmdSetBCodeInfoByItemVar->QuilityGrade			;
				Thr->GradeList			=CmdSetBCodeInfoByItemVar->GradeList			;
				Thr->BarcodeOrientation	=CmdSetBCodeInfoByItemVar->BarcodeOrientation	;
				Thr->BarcodeType		=CmdSetBCodeInfoByItemVar->BarcodeType			;
				Thr->BarcodeIsOnlyDigit	=CmdSetBCodeInfoByItemVar->BarcodeIsOnlyDigit	;
			}
		}
		return;
	}
}

//=================================================================
typedef HRESULT (STDAPICALLTYPE* CreateBarcodeReader)(IBarcodeReader**);
typedef HRESULT (STDAPICALLTYPE* DestroyBarcodeReader)(IBarcodeReader*);

CreateBarcodeReader fCreateBarcodeReader;
DestroyBarcodeReader fDestroyBarcodeReader=NULL;


BCRInspectionBase::BCRInspectionBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ModeParallelForPhase.ModeParallelExecuteInitialAfterEdit=false;

	ColorBCR			=Qt::green;
	ColorSelected		=Qt::yellow;
	ColorActive			=Qt::red;
	TransparentLevel	=120;
	NegColorBCR			=Qt::darkGreen;
	NegColorSelected	=Qt::darkYellow;
	FixedMode			=false;
	FixedValue			=128;
	FixedValueMax		=180;
	FixedValueMin		=100;
	AdotpedLayer		=0;
	barReader			=NULL;
	IdealSize			=150;
	TryAllFilter		=true;

	LicenseKey		=/**/"Q19ZE7ES9AIIO6CCF5E8";

	BarcodeImageInvert		=false;
	BarcodeImageDespeckle	=false;
	BarcodeImageDilate		=false;
	BarcodeImageErode		=false;
	BarcodeImageSharp		=false;


	SetParam(&FixedMode			, /**/"Setting"		,/**/"FixedMode"		,LangSolver.GetString(XBCRInspection_LS,LID_0)/*"Fixed Mode"*/);
	SetParam(&FixedValue		, /**/"Setting"		,/**/"FixedValue"		,LangSolver.GetString(XBCRInspection_LS,LID_1)/*"Fixed value"*/);
	SetParam(&FixedValueMax		, /**/"Setting"		,/**/"FixedValueMax"	,LangSolver.GetString(XBCRInspection_LS,LID_2)/*"Fixed value as maximum"*/);
	SetParam(&FixedValueMin		, /**/"Setting"		,/**/"FixedValueMin"	,LangSolver.GetString(XBCRInspection_LS,LID_3)/*"Fixed value as minimum"*/);
	SetParam(&LicenseKey		, /**/"Setting"		,/**/"LicenseKey"		,LangSolver.GetString(XBCRInspection_LS,LID_4)/*"LicenseKey"*/);
	SetParam(&AdotpedLayer		, /**/"Setting"		,/**/"AdotpedLayer"		,LangSolver.GetString(XBCRInspection_LS,LID_5)/*"Adotped Layer , -1:Color"*/);	
	SetParam(&IdealSize			, /**/"Setting"		,/**/"IdealSize"		,LangSolver.GetString(XBCRInspection_LS,LID_14)/*"Ideal size insside"*/);

	SetParam(&TryAllFilter			, /**/"Option"		,/**/"TryAllFilter"				,LangSolver.GetString(XBCRInspection_LS,LID_15)/*"Try al filter"*/);
	SetParam(&BarcodeImageInvert	, /**/"Option"		,/**/"BarcodeImageInvert"		,LangSolver.GetString(XBCRInspection_LS,LID_7)/*"Option Invert"*/);
	SetParam(&BarcodeImageDespeckle	, /**/"Option"		,/**/"BarcodeImageDespeckle"	,LangSolver.GetString(XBCRInspection_LS,LID_8)/*"Option Despeckle"*/);
	SetParam(&BarcodeImageDilate	, /**/"Option"		,/**/"BarcodeImageDilate"		,LangSolver.GetString(XBCRInspection_LS,LID_9)/*"Option Dilate"*/);
	SetParam(&BarcodeImageErode		, /**/"Option"		,/**/"BarcodeImageErode"		,LangSolver.GetString(XBCRInspection_LS,LID_10)/*"Option Erode"*/);
	SetParam(&BarcodeImageSharp		, /**/"Option"		,/**/"BarcodeImageSharp"		,LangSolver.GetString(XBCRInspection_LS,LID_11)/*"Option Sharp"*/);
}

BCRInspectionBase::~BCRInspectionBase(void)
{
	if(fDestroyBarcodeReader!=NULL){
		fDestroyBarcodeReader(barReader);
		fDestroyBarcodeReader=NULL;
	}
}

AlgorithmDrawAttr	*BCRInspectionBase::CreateDrawAttr(void)
{
	return new BCRInspectionDrawAttr();
}

static	VARIANT_BOOL	Boo=true;

void	BCRInspectionBase::InitialAfterParamLoaded(void)
{
	DTKLib.setFileName(/**/"DTKBarReader.dll");
	if(DTKLib.load()==true){
		fCreateBarcodeReader	=(CreateBarcodeReader)DTKLib.resolve(/**/"CreateBarcodeReader");
		fDestroyBarcodeReader	=(DestroyBarcodeReader)DTKLib.resolve(/**/"DestroyBarcodeReader");
		if(fCreateBarcodeReader(&barReader)!=0){
			return;
		}
		ILicManager *licenseManager;
		barReader->get_LicenseManager(&licenseManager);

		wchar_t	LicenseStr[2000];
		memset(LicenseStr,0,sizeof(LicenseStr));
		LicenseKey.toWCharArray(LicenseStr);
		licenseManager->AddLicenseKey(LicenseStr);

		QString	Lic1=/**/"Q19ZE7ES9AIIO6CCF5E8";
		memset(LicenseStr,0,sizeof(LicenseStr));
		Lic1.toWCharArray(LicenseStr);
		licenseManager->AddLicenseKey(LicenseStr);

		QString	Lic2=/**/"FF531F20-EF4A-47e6-8C05-13FB16C77B2F";
		memset(LicenseStr,0,sizeof(LicenseStr));
		Lic2.toWCharArray(LicenseStr);
		licenseManager->AddLicenseKey(LicenseStr);

		//licenseManager->AddLicenseKey(L"Q19ZE7ES9AIIO6CCF5E8");	//This will remove server license popup window.
		//licenseManager->AddLicenseKey(L"FF531F20-EF4A-47e6-8C05-13FB16C77B2F");	//This will remove server license popup window.
		licenseManager->get_IsLicensed(&Boo);

	}
}

void	BCRInspectionBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqBCodeResults	*CmdReqBCodeResultsVar=dynamic_cast<CmdReqBCodeResults *>(packet);
	if(CmdReqBCodeResultsVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot	*Pg=GetPageData(page);
			Pg->TransmitDirectly(packet);
		}
		return;
	}
	CmdCreateBCRInspectionThreshold	*CmdCreateBCRInspectionThresholdVar=dynamic_cast<CmdCreateBCRInspectionThreshold *>(packet);
	if(CmdCreateBCRInspectionThresholdVar!=NULL){
		CmdCreateBCRInspectionThresholdVar->Item=new BCRInspectionItem();
		CmdCreateBCRInspectionThresholdVar->Threshold=(BCRInspectionThreshold *)CmdCreateBCRInspectionThresholdVar->Item->CreateThresholdInstance();
		return;
	}
	CmdBCRInspectionSendTryThreshold	*CmdBCRInspectionSendTryThresholdVar=dynamic_cast<CmdBCRInspectionSendTryThreshold *>(packet);
	if(CmdBCRInspectionSendTryThresholdVar!=NULL){
		CmdBCRInspectionSendTryThresholdVar->PTry=new BCRInspectionSendTryThreshold();
		CmdBCRInspectionSendTryThresholdVar->Target=new BCRInspectionItem();
		AlgorithmInPagePI		*Ap=(AlgorithmInPagePI *)(CmdBCRInspectionSendTryThresholdVar->Src->GetParentInPage());
		CmdBCRInspectionSendTryThresholdVar->Target->SetParent(Ap);
		QBuffer	Buff(&CmdBCRInspectionSendTryThresholdVar->ThresholdDataForTarget);
		Buff.open(QIODevice::ReadWrite);
		CmdBCRInspectionSendTryThresholdVar->Target->GetThresholdW()->Load(&Buff);
		CmdBCRInspectionSendTryThresholdVar->PTry->Calc( CmdBCRInspectionSendTryThresholdVar->Target
														,CmdBCRInspectionSendTryThresholdVar->Src
														,this
														,NULL);
		return;
	}	
}

bool	BCRInspectionBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==BCRInspectionHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==BCRInspectionHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==BCRInspectionReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==BCRInspectionReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==BCRInspectionReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==BCRInspectionSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==BCRInspectionReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*BCRInspectionBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==BCRInspectionReqThresholdReqCommand){
		return new BCRInspectionThresholdReq();
	}
	else if(Command==BCRInspectionReqThresholdSendCommand){
		BCRInspectionThresholdSend	*pSend=new BCRInspectionThresholdSend();
		if(reqData!=NULL){
			BCRInspectionThresholdReq	*req=(BCRInspectionThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==BCRInspectionReqTryThresholdCommand){
		return new BCRInspectionReqTryThreshold();
	}
	else if(Command==BCRInspectionSendTryThresholdCommand){
		BCRInspectionSendTryThreshold	*pSend=new BCRInspectionSendTryThreshold();
		if(reqData!=NULL){
			BCRInspectionReqTryThreshold	*req=(BCRInspectionReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}

	return NULL;
}
bool	BCRInspectionBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==BCRInspectionReqThresholdReqCommand){
		BCRInspectionThresholdReq	*p=(BCRInspectionThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==BCRInspectionReqThresholdSendCommand){
		BCRInspectionThresholdSend	*p=(BCRInspectionThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==BCRInspectionReqTryThresholdCommand){
		BCRInspectionReqTryThreshold	*p=(BCRInspectionReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==BCRInspectionSendTryThresholdCommand){
		BCRInspectionSendTryThreshold	*p=(BCRInspectionSendTryThreshold *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	BCRInspectionBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==BCRInspectionReqThresholdReqCommand){
		BCRInspectionThresholdReq	*p=(BCRInspectionThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==BCRInspectionReqThresholdSendCommand){
		BCRInspectionThresholdSend	*p=(BCRInspectionThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==BCRInspectionReqTryThresholdCommand){
		BCRInspectionReqTryThreshold	*p=(BCRInspectionReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==BCRInspectionSendTryThresholdCommand){
		BCRInspectionSendTryThreshold	*p=(BCRInspectionSendTryThreshold *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}

	return false;
}
bool	BCRInspectionBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==BCRInspectionReqThresholdReqCommand){
		BCRInspectionThresholdReq	*p=(BCRInspectionThresholdReq *)data;
		return true;
	}
	else if(Command==BCRInspectionReqThresholdSendCommand){
		BCRInspectionThresholdSend	*p=(BCRInspectionThresholdSend *)data;
		return true;
	}
	else if(Command==BCRInspectionReqTryThresholdCommand){
		BCRInspectionReqTryThreshold	*p=(BCRInspectionReqTryThreshold *)data;
		return true;
	}
	else if(Command==BCRInspectionSendTryThresholdCommand){
		BCRInspectionSendTryThreshold	*p=(BCRInspectionSendTryThreshold *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}

	return false;
}

bool	BCRInspectionBase::GetBCR2D( bool BarcodeIsOnlyDigit
									,const QString &FileName ,QString &Result)
{
	bool	Ret=false;

	if(barReader!=NULL){
		barReader->put_BarcodeTypes((BarcodeTypeEnum)((((int)BT_DataMatrix) | ((int)BT_QRCode) | ((int)BT_MicroQRCode) | ((int)BT_PDF417))));
		barReader->put_ThresholdMode(TM_Adaptive);

		BarcodeOrientationEnum orientation = BO_Unknown;
		barReader->put_BarcodeOrientation(orientation);

		barReader->put_BarcodesToRead(1);
		barReader->put_ScanInterval(1);
		barReader->put_ScanPage(0);
		barReader->put_Threshold(45);
		barReader->put_QuietZoneSize(QZ_Normal);
		barReader->put_PDFReadingType(PDF_Images);
		if(FixedMode==false)
			barReader->put_ThresholdMode(TM_Adaptive);
		else{
			barReader->put_ThresholdMode(TM_Fixed);
			barReader->put_Threshold(FixedValue);
		}

		barReader->put_ImageInvert	(BarcodeImageInvert);
		barReader->put_ImageDespeckle(BarcodeImageDespeckle);
		barReader->put_ImageDilate	(BarcodeImageDilate);
		barReader->put_ImageErode	(BarcodeImageErode);
		barReader->put_ImageSharp	(BarcodeImageSharp);

		wchar_t	FileNameStr[2000];
		memset(FileNameStr,0,sizeof(FileNameStr));
		FileName.toWCharArray(FileNameStr);

		if(barReader->ReadFromFile(FileNameStr)!=0){
			return false;
		}	
		if(GetBCR2D(Result ,BarcodeIsOnlyDigit)==false){
			if(GetBCR2DFilterVarious(Result ,BarcodeIsOnlyDigit)==false){
				if(FixedMode==true){
					for(int i=1;i<50;i++){
						int	v=FixedValue+i*5;
						if(v<=FixedValueMax){
							barReader->put_Threshold(v);
							if(barReader->ReadFromFile(FileNameStr)!=0){
								return false;
							}
							if(GetBCR2D(Result ,BarcodeIsOnlyDigit)==true){
								Ret=true;
								return Ret;
							}
						}
						v=FixedValue-i*5;
						if(FixedValueMin<=v){
							barReader->put_Threshold(v);
							if(barReader->ReadFromFile(FileNameStr)!=0){
								return false;
							}
							if(GetBCR2D(Result ,BarcodeIsOnlyDigit)==true){
								Ret=true;
								return Ret;
							}
						}
					}
					for(int i=1;i<50;i++){
						int	v=FixedValue+i;
						if(v<=FixedValueMax){
							barReader->put_Threshold(v);
							if(barReader->ReadFromFile(FileNameStr)!=0){
								return false;
							}
							if(GetBCR2D(Result ,BarcodeIsOnlyDigit)==true){
								Ret=true;
								return Ret;
							}
						}
						v=FixedValue-i;
						if(FixedValueMin<=v){
							barReader->put_Threshold(v);
							if(barReader->ReadFromFile(FileNameStr)!=0){
								return false;
							}
							if(GetBCR2D(Result ,BarcodeIsOnlyDigit)==true){
								Ret=true;
								return Ret;
							}
						}
					}
				}
			}
		}
		else{
			Ret=true;
		}
	}
	return Ret;
}
bool	BCRInspectionBase::GetBCR2D(QString &Result ,bool BarcodeIsOnlyDigit)
{
	if(barReader!=NULL){
		IBarcodeCollection * barcodes = NULL;
		if(barReader->get_Barcodes(&barcodes)!=0){
			return false;
		}

		LONG barcodesCount;
		barcodes->get_Count(&barcodesCount);
		if (barcodesCount > 0)
		{
			for (int i=0; i<barcodesCount; i++)
			{
				IBarcode * bar;
				barcodes->get_Item(i, &bar);

				// Barcode string
				BSTR barcodeString;
				bar->get_BarcodeString(&barcodeString);
				Result=QString::fromWCharArray(barcodeString);
				SysFreeString(barcodeString);
				bar->Release();
				if(BarcodeIsOnlyDigit==true){
					bool	ok;
					qlonglong r=Result.toLongLong (&ok);
					if(ok==false){
						Result.clear();
					}
				}
				return true;
			}
		}
		if (barcodes){
			barcodes->Release();
		}
	}
	return false;
}

bool	BCRInspectionBase::GetBCR2DFilterVarious(QString &Result ,bool BarcodeIsOnlyDigit)
{
	if(TryAllFilter==true && barReader!=NULL){
		for(int i=0;i<32;i++){
			barReader->put_ImageInvert		((i&0x01)!=0?true:false);
			barReader->put_ImageDespeckle	((i&0x02)!=0?true:false);
			barReader->put_ImageDilate		((i&0x04)!=0?true:false);
			barReader->put_ImageErode		((i&0x08)!=0?true:false);
			barReader->put_ImageSharp		((i&0x10)!=0?true:false);
			if(GetBCR2D(Result ,BarcodeIsOnlyDigit)==true){
				return true;
			}
		}
	}
	return false;
}

bool	BCRInspectionBase::GetBCR1D(BYTE BarcodeOrientation,uint32 BarcodeType ,bool BarcodeIsOnlyDigit
				,const QString &FileName ,QString &Result)
{
	bool	Ret=false;

	if(barReader!=NULL){
		barReader->put_BarcodeTypes((BarcodeTypeEnum)BarcodeType);
		barReader->put_ThresholdMode(TM_Adaptive);
		barReader->put_BarcodeOrientation((BarcodeOrientationEnum)BarcodeOrientation);

		barReader->put_BarcodesToRead(1);
		barReader->put_ScanInterval(1);
		barReader->put_ScanPage(0);
		barReader->put_Threshold(45);
		barReader->put_QuietZoneSize(QZ_Normal);
		barReader->put_PDFReadingType(PDF_Images);
		if(FixedMode==false)
			barReader->put_ThresholdMode(TM_Automatic);	//TM_Adaptive);
		else{
			barReader->put_ThresholdMode(TM_Fixed);
			barReader->put_Threshold(FixedValue);
		}

		barReader->put_ImageInvert	(BarcodeImageInvert);
		barReader->put_ImageDespeckle(BarcodeImageDespeckle);
		barReader->put_ImageDilate	(BarcodeImageDilate);
		barReader->put_ImageErode	(BarcodeImageErode);
		barReader->put_ImageSharp	(BarcodeImageSharp);

		wchar_t	FileNameStr[2000];
		memset(FileNameStr,0,sizeof(FileNameStr));
		FileName.toWCharArray(FileNameStr);

		if(barReader->ReadFromFile(FileNameStr)!=0){
			return false;
		}	
		if(GetBCR1D(Result ,BarcodeIsOnlyDigit)==false){
			if(GetBCR1DFilterVarious(Result ,BarcodeIsOnlyDigit)==false){
				if(FixedMode==true){
					for(int i=1;i<50;i++){
						int	v=FixedValue+i*5;
						if(v<=FixedValueMax){
							barReader->put_Threshold(v);
							if(barReader->ReadFromFile(FileNameStr)!=0){
								return false;
							}
							if(GetBCR1D(Result ,BarcodeIsOnlyDigit)==true){
								Ret=true;
								return Ret;
							}
						}
						v=FixedValue-i*5;
						if(FixedValueMin<=v){
							barReader->put_Threshold(v);
							if(barReader->ReadFromFile(FileNameStr)!=0){
								return false;
							}
							if(GetBCR1D(Result ,BarcodeIsOnlyDigit)==true){
								Ret=true;
								return Ret;
							}
						}
					}
					for(int i=1;i<50;i++){
						int	v=FixedValue+i;
						if(v<=FixedValueMax){
							barReader->put_Threshold(v);
							if(barReader->ReadFromFile(FileNameStr)!=0){
								return false;
							}
							if(GetBCR1D(Result ,BarcodeIsOnlyDigit)==true){
								Ret=true;
								return Ret;
							}
						}
						v=FixedValue-i;
						if(FixedValueMin<=v){
							barReader->put_Threshold(v);
							if(barReader->ReadFromFile(FileNameStr)!=0){
								return false;
							}
							if(GetBCR1D(Result ,BarcodeIsOnlyDigit)==true){
								Ret=true;
								return Ret;
							}
						}
					}
				}
			}
		}
		else{
			Ret=true;
		}
	}
	return Ret;
}

bool	BCRInspectionBase::GetBCR1D(QString &Result ,bool BarcodeIsOnlyDigit)
{
	if(barReader!=NULL){
		IBarcodeCollection * barcodes = NULL;
		if(barReader->get_Barcodes(&barcodes)!=0){
			return false;
		}

		LONG barcodesCount;
		barcodes->get_Count(&barcodesCount);
		if (barcodesCount > 0)
		{
			for (int i=0; i<barcodesCount; i++)
			{
				IBarcode * bar;
				barcodes->get_Item(i, &bar);

				// Barcode string
				BSTR barcodeString;
				bar->get_BarcodeString(&barcodeString);
				Result=QString::fromWCharArray(barcodeString);
				SysFreeString(barcodeString);
				bar->Release();
				if(BarcodeIsOnlyDigit==true){
					bool	ok;
					qlonglong r=Result.toLongLong (&ok);
					if(ok==false){
						Result.clear();
					}
				}
				return true;
			}
		}
		if (barcodes){
			barcodes->Release();
		}
	}
	return false;
}

bool	BCRInspectionBase::GetBCR1DFilterVarious(QString &Result ,bool BarcodeIsOnlyDigit)
{
	if(TryAllFilter==true && barReader!=NULL){
		for(int i=0;i<32;i++){
			barReader->put_ImageInvert		((i&0x01)!=0?true:false);
			barReader->put_ImageDespeckle	((i&0x02)!=0?true:false);
			barReader->put_ImageDilate		((i&0x04)!=0?true:false);
			barReader->put_ImageErode		((i&0x08)!=0?true:false);
			barReader->put_ImageSharp		((i&0x10)!=0?true:false);
			if(GetBCR1D(Result ,BarcodeIsOnlyDigit)==true){
				return true;
			}
		}
	}
	return false;
}

QString	BCRInspectionBase::GetNameByCurrentLanguage(void)
{
	return LangSolver.GetString(XBCRInspection_LS,LID_16)/*"バーコード検査"*/;
}

