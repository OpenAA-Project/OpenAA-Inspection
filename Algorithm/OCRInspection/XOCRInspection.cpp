/*
 * Copyright (C) 2026
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

//#include "OCRInspectionResource.h"
#include "XOCRInspection.h"
#include "swap.h"
#include "XGeneralFunc.h"
#include "XImageProcess.h"
#include "XDisplayBitImage.h"
#include <QMessageBox>

// Tesseract�̃w�b�_�[
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>


OCRInspectionThreshold::OCRInspectionThreshold(OCRInspectionItem *parent) 
	: AlgorithmThreshold(parent)
{	
	Mergin					=0;

	RegNumber				=0;
	InspectMatching			=false;
	SaveIntoResult			=false;
	OKByFailingRecognition	=false;
}

void	OCRInspectionThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const OCRInspectionThreshold	*s=dynamic_cast<const OCRInspectionThreshold *>(&src);
	if(s!=NULL){
		Mergin			=((OCRInspectionThreshold *)&src)->Mergin;

		RegNumber		=s->RegNumber;
		InspectMatching	=s->InspectMatching;
		SaveIntoResult	=s->SaveIntoResult;
		OKByFailingRecognition	=s->OKByFailingRecognition;
		CorrectList		=s->CorrectList;
	}
}

bool	OCRInspectionThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const OCRInspectionThreshold	*s=dynamic_cast<const OCRInspectionThreshold *>(&src);
	if(s!=NULL){
		if(Mergin			!=((OCRInspectionThreshold *)&src)->Mergin		)	return false;

		if(RegNumber		!=s->RegNumber									)	return false;
		if(InspectMatching	!=s->InspectMatching							)	return false;
		if(SaveIntoResult	!=s->SaveIntoResult								)	return false;
		if(OKByFailingRecognition	!=s->OKByFailingRecognition				)	return false;
		if(CorrectList		!=s->CorrectList								)	return false;
		return  true;
	}
	return false;
}
	
bool	OCRInspectionThreshold::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return(false);

	if(::Save(f,Mergin)==false)
		return false;

	if(::Save(f,RegNumber)==false)
		return false;
	if(::Save(f,InspectMatching)==false)
		return false;
	if(::Save(f,SaveIntoResult)==false)
		return false;
	if(::Save(f,OKByFailingRecognition)==false)
		return false;
	if(::Save(f,CorrectList)==false)
		return false;
	return true;
}
	
bool	OCRInspectionThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return(false);

	if(::Load(f,Mergin)==false)
		return false;

	if(::Load(f,RegNumber)==false)
		return false;
	if(::Load(f,InspectMatching)==false)
		return false;
	if(::Load(f,SaveIntoResult)==false)
		return false;
	if(::Load(f,OKByFailingRecognition)==false)
		return false;
	if(::Load(f,CorrectList)==false)
		return false;
	return true;
}

//===============================================================================================================================
OCRInspectionItem::OCRInspectionItem(void)
{
	XByte	=0;
	XLen	=0;
	YLen	=0;
	Mx=My=0;
	AVector=NULL;
}

OCRInspectionItem::~OCRInspectionItem(void)
{
}

const	int	XMergin=16;
const	int	YMergin=16;

ExeResult	OCRInspectionItem::ExecuteInitialAfterEdit	(int ExeID,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit	(ExeID,ThreadNo,Res,EInfo);


	AllocateBuff();

	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);
	Mx=My=0;

	return Ret;
}

void	OCRInspectionItem::AllocateBuff(void)
{
	int	iYLen		=GetArea().GetHeight()+YMergin*2;
	if(iYLen>=GetMaxLines())
		iYLen = GetMaxLines()-1;
	int	iXLen		=GetArea().GetWidth()+XMergin*2;
	if(iXLen>=GetDotPerLine())
		iXLen = GetDotPerLine()-1;
	int	iXByte		=(XLen+7)/8;

	if(iXLen!=XLen || iYLen!=YLen){
		YLen		=iYLen;
		XLen		=iXLen;
		XByte		=(XLen+7)/8;
		Map = QImage(XLen,YLen,QImage::Format_RGB888);
		Map.fill(Qt::black);
	}
}

ExeResult	OCRInspectionItem::ExecuteProcessing		(int ExeID,int ThreadNo,ResultInItemRoot *Res)
{
	ImagePointerContainer ImageList;
	GetTargetBuffList(ImageList);
	Result.clear();
	Calc(ImageList);
	const OCRInspectionThreshold	*RThr=GetThresholdR();
	if(Result.isEmpty()==false){
		if(RThr->InspectMatching==true){
			if(Match(Result)==true)
				Res->SetError(1);
			else{
				Res->SetError(2);
			}
		}
	}
	else{
		if(RThr->OKByFailingRecognition==true){
			Res->SetError(1);
		}
		else{
			Res->SetError(2);
		}
	}

	if(RThr->SaveIntoResult==true){
		ResultInspection	*R=Res->GetResultInspection();
		if(R!=NULL){
			R->SetInspectionBarcode(Result);
		}
	}

	return _ER_true;
}
bool	OCRInspectionItem::Match(QString &_Result)
{
	const OCRInspectionThreshold	*RThr=GetThresholdR();
	int i;
	for(i=0;i<RThr->CorrectList.count();i++){
		QRegularExpression	E(RThr->CorrectList[i]);
		QRegularExpressionMatch match = E.match(Result);
		if(match.hasMatch()==true){
			return true;
		}
	}
	return false;
}
bool	OCRInspectionItem::Calc(ImagePointerContainer &ImageList)
{
	if(AVector!=NULL){
		Mx=AVector->ShiftX;
		My=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		Mx=V.ShiftX;
		My=V.ShiftY;
	}

	Result=/**/"";
	OCRInspectionBase		*ABase=(OCRInspectionBase *)GetParentBase();
	if(ABase!=NULL){
		try{
			AllocateBuff();
			//QImage	Map(XLen,YLen,QImage::Format_RGB888);
			MakeImage(Map,Mx,My,ImageList);

			//QImage	TmpImage=Map.convertToFormat(QImage::Format_RGB32);
			//TmpImage.save("TmpOCR.png","PNG");

			ABase->GetOCR(Map,Result);
		}
		catch(...){}
		
	}

	return true;
}

void	OCRInspectionItem::MakeImage(QImage &Map,int mx,int my,ImagePointerContainer &ImageList)
{
	int	X1 = GetArea().GetMinX()+mx-XMergin;
	int	Y1 = GetArea().GetMinY()+my-YMergin;
	int	X2 = GetArea().GetMaxX()+mx+XMergin;
	int	Y2 = GetArea().GetMaxY()+my+YMergin;

	if(X1<0)			X1 = 0;
	if(Y1<0)			Y1 = 0;
	if(X2>=GetDotPerLine())	X1 -= X2-GetDotPerLine();
	if(Y2>=GetMaxLines())	Y1 -= Y2-GetMaxLines();

	ImageList.MakeImage(Map ,-X1 ,-Y1);
}

static	int	Clip255(int n,int d)
{
	if(n<0)	return d-20;
	else	return d+20;
}


QString	OCRInspectionItem::OutputResult(ResultPosList *p)
{
	return QString(/**/"OCR=")+Result;
}
	
void	OCRInspectionItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	OCRInspectionDrawAttr	*A=dynamic_cast<OCRInspectionDrawAttr *>(Attr);
	if(A!=NULL){
		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
	
void	OCRInspectionItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	AlgorithmItemPI::DrawResultItem(Res,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);

	int	cx,cy;
	GetArea().GetCenter(cx,cy);
	int	kx=(cx+MovX+Mx)*ZoomRate;
	int	ky=(cy+MovY+My)*ZoomRate;
	if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
		QRect	rect(0,0,IData.width(),IData.height());
		PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
			,Qt::AlignLeft | Qt::AlignTop
			,QString(/**/" Sft(")+QString::number(Mx)+QString(/**/",")+QString::number(My)+QString(/**/")")
			,&rect);
		PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
			,Qt::AlignLeft | Qt::AlignTop
			,Result
			,&rect);
	}
}

//=================================================================

void	OCRInspectionInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqOCRList	*CmdReqOCRListVar=dynamic_cast<CmdReqOCRList *>(packet);
	if(CmdReqOCRListVar!=NULL){
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			OCRInspectionItem	*Item=dynamic_cast<OCRInspectionItem *>(a);
			if(Item!=NULL){
				OCRList	*k=new OCRList();
				k->GlobalPage				=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
				k->ItemID					=Item->GetID();
				k->ItemName					=Item->GetItemName();
				const OCRInspectionThreshold	*RThr=Item->GetThresholdR(GetLayersBase());
				k->Mergin		=RThr->Mergin		;
		
				k->RegNumber				=RThr->RegNumber;
				k->InspectMatching			=RThr->InspectMatching;
				k->SaveIntoResult			=RThr->SaveIntoResult;
				k->OKByFailingRecognition	=RThr->OKByFailingRecognition;
				k->CorrectList				=RThr->CorrectList;
				Item->GetArea().GetXY(k->x1,k->y1,k->x2,k->y2);
				
				CmdReqOCRListVar->Container->AppendList(k);
			}
		}
		return;
	}
	CmdReqBCodeTest	*CmdReqBCodeTestVar=dynamic_cast<CmdReqBCodeTest *>(packet);
	if(CmdReqBCodeTestVar!=NULL){
		AlgorithmItemRoot	*a=SearchIDItem(CmdReqBCodeTestVar->ItemID);
		if(a!=NULL){
			OCRInspectionItem	*Item=dynamic_cast<OCRInspectionItem *>(a);
			if(Item!=NULL){

				ImagePointerContainer ImageList;
				if(CmdReqBCodeTestVar->Mastered==true){
					Item->GetMasterBuffList(ImageList);
				}
				else{
					Item->GetTargetBuffList(ImageList);
				}
				Item->Calc(ImageList);
				CmdReqBCodeTestVar->Result	=Item->Result;
				CmdReqBCodeTestVar->Mastered=Item->Match(Item->Result);	
			}
		}
		return;
	}
	AddOCRInspectionAreaPacket	*AddOCRInspectionAreaVar=dynamic_cast<AddOCRInspectionAreaPacket *>(packet);
	if(AddOCRInspectionAreaVar!=NULL){
		OCRInspectionItem	*Item=new OCRInspectionItem();
		Item->SetArea(AddOCRInspectionAreaVar->Area);
		Item->SetItemName(AddOCRInspectionAreaVar->ItemName);
		Item->GetThresholdW()->Mergin		=AddOCRInspectionAreaVar->Mergin;

		Item->GetThresholdW()->RegNumber				=AddOCRInspectionAreaVar->RegNumber;
		Item->GetThresholdW()->InspectMatching			=AddOCRInspectionAreaVar->InspectMatching;
		Item->GetThresholdW()->SaveIntoResult			=AddOCRInspectionAreaVar->SaveIntoResult;
		Item->GetThresholdW()->OKByFailingRecognition	=AddOCRInspectionAreaVar->OKByFailingRecognition;
		Item->GetThresholdW()->CorrectList				=AddOCRInspectionAreaVar->CorrectList;
		AppendItem(Item);
		return;
	}
	UpdateOCRInspectionAreaPacket	*UpdateOCRInspectionAreaPacketVar=dynamic_cast<UpdateOCRInspectionAreaPacket *>(packet);
	if(UpdateOCRInspectionAreaPacketVar!=NULL){
		OCRInspectionItem	*Item=(OCRInspectionItem *)SearchIDItem(UpdateOCRInspectionAreaPacketVar->ItemID);
		Item->SetItemName(UpdateOCRInspectionAreaPacketVar->ItemName);
		Item->GetThresholdW()->Mergin		=UpdateOCRInspectionAreaPacketVar->Mergin;

		Item->GetThresholdW()->RegNumber				=UpdateOCRInspectionAreaPacketVar->RegNumber;
		Item->GetThresholdW()->InspectMatching			=UpdateOCRInspectionAreaPacketVar->InspectMatching;
		Item->GetThresholdW()->SaveIntoResult			=UpdateOCRInspectionAreaPacketVar->SaveIntoResult;
		Item->GetThresholdW()->OKByFailingRecognition	=UpdateOCRInspectionAreaPacketVar->OKByFailingRecognition;
		Item->GetThresholdW()->CorrectList				=UpdateOCRInspectionAreaPacketVar->CorrectList;
		return;
	}
	DeleteOCRInspectionAreaPacket	*DeleteOCRInspectionAreaPacketVar=dynamic_cast<DeleteOCRInspectionAreaPacket *>(packet);
	if(DeleteOCRInspectionAreaPacketVar!=NULL){
		OCRInspectionItem	*Item=(OCRInspectionItem *)SearchIDItem(DeleteOCRInspectionAreaPacketVar->ItemID);
		RemoveItem(Item);
		return;
	}
	ReqOCRItemPacket	*ReqOCRItemPacketVar=dynamic_cast<ReqOCRItemPacket *>(packet);
	if(ReqOCRItemPacketVar!=NULL){
		OCRInspectionItem	*Item=(OCRInspectionItem *)SearchIDItem(ReqOCRItemPacketVar->ItemID);
		ReqOCRItemPacketVar->Area	=Item->GetArea();
		return;
	}

	CmdReqOCRTest	*CmdReqOCRTestVar=dynamic_cast<CmdReqOCRTest *>(packet);
	if(CmdReqOCRTestVar!=NULL){
		OCRInspectionItem	*Item=(OCRInspectionItem *)SearchIDItem(CmdReqOCRTestVar->ItemID);

		ImagePointerContainer ImageList;
		GetTargetBuffList(ImageList);
		Item->Result.clear();
		Item->Calc(ImageList);

		CmdReqOCRTestVar->Result	=Item->Result;
		return;
	}
	CmdReqOCRResults *CmdReqOCRResultsVar = dynamic_cast<CmdReqOCRResults *>(packet);
	if(CmdReqOCRResultsVar!= NULL) {
		for (AlgorithmItemPI* a = GetFirstData(); a != NULL; a = a->GetNext()) {
			OCRInspectionItem* Item = dynamic_cast<OCRInspectionItem*>(a);
			if (Item != NULL) {
				if(CmdReqOCRResultsVar->ItemName.isEmpty()==true
				|| Item->GetItemName()==CmdReqOCRResultsVar->ItemName){
					CmdReqOCRResultsVar->ResultOCR=Item->Result;
				}
			}
		}
		return;
	}
}

//=================================================================

OCRInspectionBase::OCRInspectionBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorOCR			=Qt::green;
	ColorSelected		=Qt::yellow;
	ColorActive			=Qt::red;
	TransparentLevel	=120;
	NegColorOCR			=Qt::darkGreen;
	NegColorSelected	=Qt::darkYellow;
	AdotpedLayer		=0;
	OcrApi				=NULL;
	OCRDataPath			="./tessdata";
	OCRLanguage			= "jpn";

	SetParam(&AdotpedLayer		, /**/"Setting"		,/**/"AdotpedLayer"		,"Adotped Layer , -1:Color");	
	SetParam(&OCRDataPath		, /**/"Setting"		,/**/"OCRDataPath"		,"OCR Data Path (./tessdata)");	
	SetParam(&OCRLanguage		, /**/"Setting"		,/**/"OCRLanguage"		,"Language name(jpn)");	
}

OCRInspectionBase::~OCRInspectionBase(void)
{
	if(OcrApi!=NULL){
		OcrApi->End();
        delete OcrApi;
		OcrApi = NULL;
	}
}

AlgorithmDrawAttr	*OCRInspectionBase::CreateDrawAttr(void)
{
	return new OCRInspectionDrawAttr();
}

void	OCRInspectionBase::InitialAfterParamLoaded(void)
{
    OcrApi = new tesseract::TessBaseAPI();
    
    
	char *OCRDataPathCStr = new char[OCRDataPath.length() + 1];
	std::strcpy(OCRDataPathCStr,OCRDataPath.toStdString().c_str());
	char *OCRLanguageCStr = new char[OCRLanguage.length() + 1];
	std::strcpy(OCRLanguageCStr,OCRLanguage.toStdString().c_str());

	QDir::setCurrent(GetLayersBase()->GetSystemPath());
    if (OcrApi->Init(OCRDataPathCStr, OCRLanguageCStr)) { 
        delete OcrApi;
		OcrApi = NULL;
    }
	delete[] OCRDataPathCStr;
	delete[] OCRLanguageCStr;
}

void	OCRInspectionBase::TransmitDirectly(GUIDirectMessage *packet)
{

}


bool	OCRInspectionBase::GetOCR(const QString &FileName ,QString &Result)
{
    QImage image(FileName);
    if (image.isNull()) {
        return false;
    }
	return GetOCR(image ,Result);
}

bool	OCRInspectionBase::GetOCR(const QImage &Image ,QString &Result)
{
	QImage	image;
	QImage	*pImage;
	if(Image.format() != QImage::Format_RGB888){
		image = Image.convertToFormat(QImage::Format_RGB888);
		pImage=&image;
	}
	else{
		pImage = (QImage *)&Image;
	}

    // 3. QImage �̃f�[�^�𒼐� Tesseract �ɓn��
    // SetImage(buffer, width, height, bytes_per_pixel, bytes_per_line)
	if(OcrApi!=NULL){
		int	XLen=pImage->width();
		int	YLen=pImage->height();
		OcrApi->SetImage(
				pImage->bits(),           // �摜�f�[�^�̐擪�|�C���^
				XLen,          // ��
				YLen,         // ����
				3,                      // 1�s�N�Z���������̃o�C�g�� (RGB888�Ȃ�3)
				pImage->bytesPerLine()    // 1�s�������̃o�C�g�� (�X�g���C�h)
			);

		// 4. �����F���̎��s
		char* outText = OcrApi->GetUTF8Text();
		Result = QString::fromUtf8(outText);
		// 5. ���Еt��
		delete[] outText;
		return true;
	}

	return false;
}