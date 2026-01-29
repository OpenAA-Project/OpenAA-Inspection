#include "BCRInspectionResource.h"
#include "swap.h"
#include "XBCRInspection.h"
#include "XCriticalFunc.h"
#include "ReadBarcode.h"

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
				Thr->BarcodeIsOnlyDigit	=CmdSetBCodeInfoByItemVar->BarcodeIsOnlyDigit	;
			}
		}
		return;
	}
}

//=================================================================

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
	MinBarcodeImageDispersion	=5.0;
	ResultOKWithoutBarcode		=true;


	SetParam(&FixedMode			, /**/"Setting"		,/**/"FixedMode"		,LangSolver.GetString(XBCRInspection_LS,LID_0)/*"Fixed Mode"*/);
	SetParam(&FixedValue		, /**/"Setting"		,/**/"FixedValue"		,LangSolver.GetString(XBCRInspection_LS,LID_1)/*"Fixed value"*/);
	SetParam(&FixedValueMax		, /**/"Setting"		,/**/"FixedValueMax"	,LangSolver.GetString(XBCRInspection_LS,LID_2)/*"Fixed value as maximum"*/);
	SetParam(&FixedValueMin		, /**/"Setting"		,/**/"FixedValueMin"	,LangSolver.GetString(XBCRInspection_LS,LID_3)/*"Fixed value as minimum"*/);
	SetParam(&AdotpedLayer		, /**/"Setting"		,/**/"AdotpedLayer"		,LangSolver.GetString(XBCRInspection_LS,LID_5)/*"Adotped Layer , -1:Color"*/);	
	SetParam(&IdealSize			, /**/"Setting"		,/**/"IdealSize"		,LangSolver.GetString(XBCRInspection_LS,LID_14)/*"Ideal size insside"*/);
	SetParam(&MinBarcodeImageDispersion	, /**/"Setting"	,/**/"MinBarcodeImageDispersion"	,"Minimum Barcode Image Dispersion");
	SetParam(&ResultOKWithoutBarcode	, /**/"Setting"	,/**/"ResultOKWithoutBarcode"		,"OK result without Barcode");
}

BCRInspectionBase::~BCRInspectionBase(void)
{
}

AlgorithmDrawAttr	*BCRInspectionBase::CreateDrawAttr(void)
{
	return new BCRInspectionDrawAttr();
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

    QImage image(FileName); 
    //QImage image=image2.convertedTo(QImage::Format_Mono);
    image = image.convertToFormat(QImage::Format_Grayscale8);

    if (!image.isNull()) {
        auto result = ZXing::ReadBarcode({
            image.bits(), 
            static_cast<int>(image.width()), 
            static_cast<int>(image.height()), 
            ZXing::ImageFormat::Lum,
            static_cast<int>(image.bytesPerLine())
        });
		Result=QString::fromStdString(result.text());
		if(BarcodeIsOnlyDigit==true){
			bool	ok;
			qlonglong r=Result.toLongLong (&ok);
			if(ok==false){
				Result.clear();
			}
		}
		Ret=true;
	}

	return Ret;
}


bool	BCRInspectionBase::GetBCR1D(bool BarcodeIsOnlyDigit
				,const QString &FileName ,QString &Result)
{
	bool	Ret=false;

    QImage image(FileName); 
    //QImage image=image2.convertedTo(QImage::Format_Mono);
    image = image.convertToFormat(QImage::Format_Grayscale8);

    if (!image.isNull()) {
        auto result = ZXing::ReadBarcode({
            image.bits(), 
            static_cast<int>(image.width()), 
            static_cast<int>(image.height()), 
            ZXing::ImageFormat::Lum,
            static_cast<int>(image.bytesPerLine())
        });
		Result=QString::fromStdString(result.text());
		if(BarcodeIsOnlyDigit==true){
			bool	ok;
			qlonglong r=Result.toLongLong (&ok);
			if(ok==false){
				Result.clear();
			}
		}
		Ret=true;
	}

	return Ret;
}


QString	BCRInspectionBase::GetNameByCurrentLanguage(void)
{
	return LangSolver.GetString(XBCRInspection_LS,LID_16)/*"バーコード検査"*/;
}

