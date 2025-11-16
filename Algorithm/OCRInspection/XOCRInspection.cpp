//#include "OCRInspectionResource.h"
#include "XOCRInspection.h"
#include "swap.h"
#include "XGeneralFunc.h"
#include "XImageProcess.h"
#include "XDisplayBitImage.h"
#include <QMessageBox>


#include "TOCRdll.h"
#include "TOCRuser.h"
#include "TOCRerrs.h"

OCRInspectionThreshold::OCRInspectionThreshold(OCRInspectionItem *parent) 
	: AlgorithmThreshold(parent)
{	
	AbsLR=AbsHR=0;
	AbsLG=AbsHG=0;
	AbsLB=AbsHB=0;

	EnlargeDot	=0;
	EnsmallDot	=0;
	MinSize		=0;

	BlockWidth=BlockHeight	=100;
	Mergin					=0;
	UseColorLogic			=false;
	Rotation				=0;

	RegNumber				=0;
	InspectMatching			=false;
	SaveIntoResult			=false;
	OKByFailingRecognition	=false;
}

void	OCRInspectionThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const OCRInspectionThreshold	*s=dynamic_cast<const OCRInspectionThreshold *>(&src);
	if(s!=NULL){
		AbsLR=((OCRInspectionThreshold *)&src)->AbsLR;
		AbsHR=((OCRInspectionThreshold *)&src)->AbsHR;
		AbsLG=((OCRInspectionThreshold *)&src)->AbsLG;
		AbsHG=((OCRInspectionThreshold *)&src)->AbsHG;
		AbsLB=((OCRInspectionThreshold *)&src)->AbsLB;
		AbsHB=((OCRInspectionThreshold *)&src)->AbsHB;
		EnlargeDot		=((OCRInspectionThreshold *)&src)->EnlargeDot;
		EnsmallDot		=((OCRInspectionThreshold *)&src)->EnsmallDot;
		BlockWidth		=((OCRInspectionThreshold *)&src)->BlockWidth;
		BlockHeight		=((OCRInspectionThreshold *)&src)->BlockHeight;
		MinSize			=((OCRInspectionThreshold *)&src)->MinSize;
		Mergin			=((OCRInspectionThreshold *)&src)->Mergin;
		MaskingColor	=((OCRInspectionThreshold *)&src)->MaskingColor;
		UseColorLogic	=((OCRInspectionThreshold *)&src)->UseColorLogic;
		Rotation		=((OCRInspectionThreshold *)&src)->Rotation;

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
		if(AbsLR			!=((OCRInspectionThreshold *)&src)->AbsLR		)	return false;
		if(AbsHR			!=((OCRInspectionThreshold *)&src)->AbsHR		)	return false;
		if(AbsLG			!=((OCRInspectionThreshold *)&src)->AbsLG		)	return false;
		if(AbsHG			!=((OCRInspectionThreshold *)&src)->AbsHG		)	return false;
		if(AbsLB			!=((OCRInspectionThreshold *)&src)->AbsLB		)	return false;
		if(AbsHB			!=((OCRInspectionThreshold *)&src)->AbsHB		)	return false;
		if(EnlargeDot		!=((OCRInspectionThreshold *)&src)->EnlargeDot	)	return false;
		if(EnsmallDot		!=((OCRInspectionThreshold *)&src)->EnsmallDot	)	return false;
		if(BlockWidth		!=((OCRInspectionThreshold *)&src)->BlockWidth	)	return false;
		if(BlockHeight		!=((OCRInspectionThreshold *)&src)->BlockHeight	)	return false;
		if(MinSize			!=((OCRInspectionThreshold *)&src)->MinSize		)	return false;
		if(Mergin			!=((OCRInspectionThreshold *)&src)->Mergin		)	return false;
		if(MaskingColor		!=((OCRInspectionThreshold *)&src)->MaskingColor)	return false;
		if(UseColorLogic	!=((OCRInspectionThreshold *)&src)->UseColorLogic)	return false;
		if(Rotation			!=((OCRInspectionThreshold *)&src)->Rotation	)	return false;

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
	if(::Save(f,AbsLR)==false)
		return false;
	if(::Save(f,AbsHR)==false)
		return false;
	if(::Save(f,AbsLG)==false)
		return false;
	if(::Save(f,AbsHG)==false)
		return false;
	if(::Save(f,AbsLB)==false)
		return false;
	if(::Save(f,AbsHB)==false)
		return false;
	if(::Save(f,EnlargeDot)==false)
		return false;
	if(::Save(f,EnsmallDot)==false)
		return false;
	if(::Save(f,BlockWidth)==false)
		return false;
	if(::Save(f,BlockHeight)==false)
		return false;

	if(::Save(f,Mergin)==false)
		return false;
	if(MaskingColor.Save(f)==false)
		return false;
	if(::Save(f,MinSize)==false)
		return false;
	if(::Save(f,UseColorLogic)==false)
		return false;
	if(::Save(f,Rotation)==false)
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
	if(::Load(f,AbsLR)==false)
		return false;
	if(::Load(f,AbsHR)==false)
		return false;
	if(::Load(f,AbsLG)==false)
		return false;
	if(::Load(f,AbsHG)==false)
		return false;
	if(::Load(f,AbsLB)==false)
		return false;
	if(::Load(f,AbsHB)==false)
		return false;
	if(::Load(f,EnlargeDot)==false)
		return false;
	if(::Load(f,EnsmallDot)==false)
		return false;
	if(::Load(f,BlockWidth)==false)
		return false;
	if(::Load(f,BlockHeight)==false)
		return false;

	if(::Load(f,Mergin)==false)
		return false;
	if(MaskingColor.Load(f)==false)
		return false;
	if(::Load(f,MinSize)==false)
		return false;
	if(::Load(f,UseColorLogic)==false)
		return false;
	if(::Load(f,Rotation)==false)
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
	MaskingMap	=NULL;
	TmpBuff		=NULL;
	XByte	=0;
	YLen	=0;
	Mx=My=0;
	AVector=NULL;
}

OCRInspectionItem::~OCRInspectionItem(void)
{
	if(MaskingMap!=NULL){
		DeleteMatrixBuff(MaskingMap,YLen);
		DeleteMatrixBuff(TmpBuff,YLen);
		MaskingMap	=NULL;
		TmpBuff		=NULL;
	}
}

const	int	XMergin=16;
const	int	YMergin=16;

ExeResult	OCRInspectionItem::ExecuteInitialAfterEdit	(int ExeID,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit	(ExeID,ThreadNo,Res,EInfo);

	if(MaskingMap!=NULL){
		DeleteMatrixBuff(MaskingMap,YLen);
		DeleteMatrixBuff(TmpBuff,YLen);
	}
	YLen		=GetArea().GetHeight()+YMergin*2;
	XByte		=(GetArea().GetWidth()+XMergin*2+7)/8;
	MaskingMap	=MakeMatrixBuff(XByte ,YLen);
	TmpBuff		=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(MaskingMap ,0 ,XByte ,YLen);

	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);
	Mx=My=0;

	return Ret;
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
		QString	FileName=QString(/**/"TmpOCR")+QString::number(GetPage())+QString(/**/"-")+QString::number(GetID())
						+QString(/**/".bmp");
		try{
			MakeImage(Mx,My,ImageList);
			SaveBmpFileBit (FileName ,MaskingMap ,XByte ,YLen);
		}
		catch(...){}

		
		ABase->GetOCR(FileName,Result);
	}

	return true;
}

void	OCRInspectionItem::MakeImage(int mx,int my,ImagePointerContainer &ImageList)
{
	int	MinX=GetArea().GetMinX();
	int	MinY=GetArea().GetMinY();
	int	H=GetArea().GetHeight();
	int	W=GetArea().GetWidth();
	MatrixBuffClear	(MaskingMap ,0 ,XByte ,YLen);
	const OCRInspectionThreshold	*RThr=GetThresholdR();
	if(GetLayerNumb()>=3){
		ImageBuffer *hR=ImageList[0];
		ImageBuffer *hG=ImageList[1];
		ImageBuffer *hB=ImageList[2];
		for(int y=0;y<H;y++){
			BYTE	*d=MaskingMap[y];
			int		Y=MinY+y+my;
			if(Y<0)
				continue;
			if(Y>=GetMaxLines())
				break;
			BYTE	*sR=hR->GetY(Y);
			BYTE	*sG=hG->GetY(Y);
			BYTE	*sB=hB->GetY(Y);
			if(RThr->UseColorLogic==false){
				for(int x=0;x<W;x++){
					int	X=MinX+x+mx;
					if(0<=X && X<GetDotPerLine()){
						BYTE	R=sR[X];
						BYTE	G=sG[X];
						BYTE	B=sB[X];
						if(RThr->AbsLR<=R && R<=RThr->AbsHR
						&& RThr->AbsLG<=G && G<=RThr->AbsHG
						&& RThr->AbsLB<=B && B<=RThr->AbsHB){
							SetBmpBitOnY1(d,x);
						}
					}
				}
			}
			else{
				for(int x=0;x<W;x++){
					int	X=MinX+x+mx;
					if(0<=X && X<GetDotPerLine()){
						BYTE	R=sR[X];
						BYTE	G=sG[X];
						BYTE	B=sB[X];
						if(GetThresholdW()->MaskingColor.Calc(R,G,B,RThr->Mergin)==true){
							SetBmpBitOnY1(d,x);
						}
					}
				}
			}
		}
	}
	else if(GetLayerNumb()>=2){
		ImageBuffer *hR=ImageList[0];
		ImageBuffer *hG=ImageList[1];
		for(int y=0;y<H;y++){
			BYTE	*d=MaskingMap[y];
			int		Y=MinY+y+my;
			if(Y<0)
				continue;
			if(Y>=GetMaxLines())
				break;
			BYTE	*sR=hR->GetY(Y);
			BYTE	*sG=hG->GetY(Y);
			for(int x=0;x<W;x++){
				int	X=MinX+x+mx;
				if(0<=X && X<GetDotPerLine()){
					BYTE	R=sR[X];
					BYTE	G=sG[X];
					if(RThr->AbsLR<=R && R<=RThr->AbsHR
					&& RThr->AbsLG<=G && G<=RThr->AbsHG){
						SetBmpBitOnY1(d,x);
					}
				}
			}
		}
	}
	else if(GetLayerNumb()>=1){
		ImageBuffer *hR=ImageList[0];
		for(int y=0;y<H;y++){
			BYTE	*d=MaskingMap[y];
			int		Y=MinY+y+my;
			if(Y<0)
				continue;
			if(Y>=GetMaxLines())
				break;
			BYTE	*sR=hR->GetY(Y);
			for(int x=0;x<W;x++){
				int	X=MinX+x+mx;
				if(0<=X && X<GetDotPerLine()){
					BYTE	R=sR[X];
					if(RThr->AbsLR<=R && R<=RThr->AbsHR){
						SetBmpBitOnY1(d,x);
					}
				}
			}
		}
	}
	GetLayersBase()->ThinAreaN(MaskingMap
			,TmpBuff
			,XByte, YLen 
			,RThr->EnsmallDot);
	GetLayersBase()->FatAreaN(MaskingMap
			,TmpBuff
			,XByte, YLen 
			,RThr->EnsmallDot+RThr->EnlargeDot);

	PureFlexAreaListContainer FPack;
	PickupFlexArea(MaskingMap ,XByte ,XByte*8,YLen ,FPack);
	MatrixBuffClear	(MaskingMap ,0 ,XByte ,YLen);
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->GetWidth()>=RThr->BlockWidth
		&& f->GetHeight()>=RThr->BlockHeight
		&& f->GetPatternByte()>=RThr->MinSize){
			f->MakeBitData(MaskingMap,XByte*8 ,YLen);
		}
	}
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

		if(MaskingMap!=NULL){
			DrawBitImage(pnt, (const BYTE **)MaskingMap ,XByte*8 ,XByte ,YLen
						,movx ,movy ,ZoomRate
						,-GetArea().GetMinX() ,-GetArea().GetMinY()
						,Qt::cyan);
		}
	}
}
	
void	OCRInspectionItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	AlgorithmItemPI::DrawResultItem(Res,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);

	DrawBitImage(IData, (const BYTE **)MaskingMap ,XByte*8 ,XByte ,YLen
					,MovX ,MovY ,ZoomRate
					,-GetArea().GetMinX()-Mx ,-GetArea().GetMinY()-My
					,Qt::cyan);
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
				k->AbsLR		=RThr->AbsLR		;
				k->AbsHR		=RThr->AbsHR		;
				k->AbsLG		=RThr->AbsLG		;
				k->AbsHG		=RThr->AbsHG		;
				k->AbsLB		=RThr->AbsLB		;
				k->AbsHB		=RThr->AbsHB		;
				k->EnsmallDot	=RThr->EnsmallDot	;
				k->EnlargeDot	=RThr->EnlargeDot	;
				k->BlockWidth	=RThr->BlockWidth	;
				k->BlockHeight	=RThr->BlockHeight	;
				k->MinSize		=RThr->MinSize		;
				k->Mergin		=RThr->Mergin		;
				k->MaskingColor	=RThr->MaskingColor	;
				k->UseColorLogic=RThr->UseColorLogic	;
				k->Rotation		=RThr->Rotation		;
		
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
		Item->GetThresholdW()->AbsLR		=AddOCRInspectionAreaVar->AbsLR;
		Item->GetThresholdW()->AbsHR		=AddOCRInspectionAreaVar->AbsHR;
		Item->GetThresholdW()->AbsLG		=AddOCRInspectionAreaVar->AbsLG;
		Item->GetThresholdW()->AbsHG		=AddOCRInspectionAreaVar->AbsHG;
		Item->GetThresholdW()->AbsLB		=AddOCRInspectionAreaVar->AbsLB;
		Item->GetThresholdW()->AbsHB		=AddOCRInspectionAreaVar->AbsHB;
		Item->GetThresholdW()->EnsmallDot	=AddOCRInspectionAreaVar->EnsmallDot;
		Item->GetThresholdW()->EnlargeDot	=AddOCRInspectionAreaVar->EnlargeDot;
		Item->GetThresholdW()->BlockWidth	=AddOCRInspectionAreaVar->BlockWidth;
		Item->GetThresholdW()->BlockHeight	=AddOCRInspectionAreaVar->BlockHeight;
		Item->GetThresholdW()->MinSize		=AddOCRInspectionAreaVar->MinSize;
		Item->GetThresholdW()->Mergin		=AddOCRInspectionAreaVar->Mergin;
		Item->GetThresholdW()->MaskingColor	=AddOCRInspectionAreaVar->MaskingColor;
		Item->GetThresholdW()->UseColorLogic=AddOCRInspectionAreaVar->UseColorLogic;
		Item->GetThresholdW()->Rotation		=AddOCRInspectionAreaVar->Rotation;

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
		Item->GetThresholdW()->AbsLR		=UpdateOCRInspectionAreaPacketVar->AbsLR;
		Item->GetThresholdW()->AbsHR		=UpdateOCRInspectionAreaPacketVar->AbsHR;
		Item->GetThresholdW()->AbsLG		=UpdateOCRInspectionAreaPacketVar->AbsLG;
		Item->GetThresholdW()->AbsHG		=UpdateOCRInspectionAreaPacketVar->AbsHG;
		Item->GetThresholdW()->AbsLB		=UpdateOCRInspectionAreaPacketVar->AbsLB;
		Item->GetThresholdW()->AbsHB		=UpdateOCRInspectionAreaPacketVar->AbsHB;
		Item->GetThresholdW()->EnsmallDot	=UpdateOCRInspectionAreaPacketVar->EnsmallDot;
		Item->GetThresholdW()->EnlargeDot	=UpdateOCRInspectionAreaPacketVar->EnlargeDot;
		Item->GetThresholdW()->BlockWidth	=UpdateOCRInspectionAreaPacketVar->BlockWidth;
		Item->GetThresholdW()->BlockHeight	=UpdateOCRInspectionAreaPacketVar->BlockHeight;
		Item->GetThresholdW()->MinSize		=UpdateOCRInspectionAreaPacketVar->MinSize;
		Item->GetThresholdW()->Mergin		=UpdateOCRInspectionAreaPacketVar->Mergin;
		Item->GetThresholdW()->MaskingColor	=UpdateOCRInspectionAreaPacketVar->MaskingColor;
		Item->GetThresholdW()->UseColorLogic=UpdateOCRInspectionAreaPacketVar->UseColorLogic;
		Item->GetThresholdW()->Rotation		=UpdateOCRInspectionAreaPacketVar->Rotation;

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
	CmdReqBCodeResults	*CmdReqBCodeResultsVar=dynamic_cast<CmdReqBCodeResults *>(packet);
	if(CmdReqBCodeResultsVar!=NULL){
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			OCRInspectionItem	*Item=dynamic_cast<OCRInspectionItem *>(a);
			if(Item!=NULL){
				CmdReqBCodeResultsVar->ResultBarcode.append(Item->Result);
			}
		}
		return;
	}
	CmdSetBCodeResults	*CmdSetBCodeResultsVar=dynamic_cast<CmdSetBCodeResults *>(packet);
	if(CmdSetBCodeResultsVar!=NULL){
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			OCRInspectionItem	*Item=dynamic_cast<OCRInspectionItem *>(a);
			if(Item!=NULL){
				Item->Result=CmdSetBCodeResultsVar->ResultBarcode;
				CmdSetBCodeResultsVar->OK=true;
			}
		}
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

	SetParam(&AdotpedLayer		, /**/"Setting"		,/**/"AdotpedLayer"		,"Adotped Layer , -1:Color");	
}

OCRInspectionBase::~OCRInspectionBase(void)
{
}

AlgorithmDrawAttr	*OCRInspectionBase::CreateDrawAttr(void)
{
	return new OCRInspectionDrawAttr();
}

void	OCRInspectionBase::InitialAfterParamLoaded(void)
{
}

void	OCRInspectionBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqBCodeResults	*CmdReqBCodeResultsVar=dynamic_cast<CmdReqBCodeResults *>(packet);
	if(CmdReqBCodeResultsVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot	*Pg=GetPageData(page);
			Pg->TransmitDirectly(packet);
		}
		return;
	}
}

bool OCRWait(long JobNo, TOCRJOBINFO_EG JobInfoEg)
{
	long				Status;
	long				JobStatus=-1;
	long				ErrorMode;
	char				Msg[TOCRJOBMSGLENGTH];

	Status = TOCRDoJob_EG(JobNo, &JobInfoEg);
	if (Status == TOCR_OK) {
		Status = TOCRWaitForJob(JobNo, &JobStatus);
	}

	if (Status == TOCR_OK && JobStatus == TOCRJOBSTATUS_DONE)
	{
		return true;
	}
	else {
		// If something has gone wrong display a message
		// (Check that the OCR engine hasn't already displayed a message)
		TOCRGetConfig(JobNo, TOCRCONFIG_DLL_ERRORMODE, &ErrorMode);
		if (ErrorMode == TOCRERRORMODE_NONE) {
			TOCRGetJobStatusMsg(JobNo, Msg);
			QMessageBox::warning(NULL, "OCRWait", Msg);
		}
		return false;
	}
} // OCRWait()

// Get the results from TOCR
bool getresults(long JobNo, long mode, void **Results)
{
	long				Status;
	long				ResultsInf;
	char				Msg[TOCRJOBMSGLENGTH];

	if ( mode == TOCRGETRESULTS_NORMAL_EG || mode == TOCRGETRESULTS_EXTENDED_EG ) {
		Status = TOCRGetJobResultsEx_EG(JobNo, mode, &ResultsInf, 0);
		if ( Status != TOCR_OK ) {
			sprintf(Msg, "TOCRGetJobResultsEx_EG failed - %d\n", (int)Status);
		}
	} else {
		Status = TOCRGetJobResultsEx(JobNo, mode, &ResultsInf, 0);
		if ( Status != TOCR_OK ) {
			sprintf(Msg, "TOCRGetJobResultsEx failed - %d\n", (int)Status);
		}
	}
	if ( Status != TOCR_OK ) {
		QMessageBox::warning(NULL, "getresults",Msg);
		return false;
	}
	if ( ResultsInf > 0 ) {
		// Allocate memory for results

		*Results = (void *)malloc(ResultsInf * sizeof(unsigned char));
		if ( *Results ) {

			// Retrieve the results
			if ( mode == TOCRGETRESULTS_NORMAL_EG || mode == TOCRGETRESULTS_EXTENDED_EG ) {
				Status = TOCRGetJobResultsEx_EG(JobNo, mode, &ResultsInf, *Results);
				if ( Status != TOCR_OK ) {
					sprintf(Msg, "TOCRGetJobResultsEx_EG failed - %d\n", (int)Status);
				}
			} else {
				Status = TOCRGetJobResultsEx(JobNo, mode, &ResultsInf, *Results);
				if ( Status != TOCR_OK ) {
					sprintf(Msg, "TOCRGetJobResultsEx failed - %d\n", (int)Status);
				}
			}
			if ( Status != TOCR_OK ) {
				QMessageBox::warning(NULL, "getresults", Msg);
				free(*Results);
				*Results = 0;
				return false;
			}
		} else {
			QMessageBox::warning(NULL, "getresults", "Failed to allocate memory for results\n");
			return false;
		}
	} else {
		QMessageBox::warning(NULL, "getresults","No results found\n");
	}
	
	return true;
} // getresults()

// Get normal results
bool GetResults(long JobNo, TOCRRESULTS **Results)
{
	return getresults(JobNo, TOCRGETRESULTS_NORMAL, (void **)Results);
} // GetResults()

// Get extended results
bool GetResults(long JobNo, TOCRRESULTSEX **Results)
{
	return getresults(JobNo, TOCRGETRESULTS_EXTENDED, (void **)Results);
} // GetResults()

// Get extended eg results
bool GetResults(long JobNo, TOCRRESULTSEX_EG **Results)
{
	return getresults(JobNo, TOCRGETRESULTS_EXTENDED_EG, (void **)Results);
} // GetResults()

// Convert results to a string
bool FormatResults(TOCRRESULTS *Results, char *Msg)
{
	long			ItemNo;
	long			APos = 0;
	bool			Status = false;

	if ( Results->Hdr.NumItems > 0 ) {
		for (ItemNo = 0; ItemNo < Results->Hdr.NumItems; ItemNo ++ ) {
			if ( Results->Item[ItemNo].OCRCha == '\r' )
				Msg[APos] = '\n';
			else
				Msg[APos] = (char)Results->Item[ItemNo].OCRCha;
			APos ++;
		}
		Msg[APos] = 0;
		Status = true;
	}

	return Status;

} // FormatResults()

bool	OCRInspectionBase::GetOCR(const QString &FileName ,QString &Result)
{
	TOCRJOBINFO_EG		JobInfo_EG;
	TOCRRESULTS			*Results = 0;
	long				Status;
	long				JobNo = 0;
	char				InputFile[MAX_PATH];
	char				Msg[10240];

	TOCRSetConfig(TOCRCONFIG_DEFAULTJOB, TOCRCONFIG_DLL_ERRORMODE, TOCRERRORMODE_MSGBOX);
	//TOCRSetConfig(TOCRCONFIG_DEFAULTJOB, TOCRCONFIG_DLL_ERRORMODE, TOCRERRORMODE_LOG); // Log Errors
	//	TOCRGetJobDBInfo(&JobNo);

	memset(&JobInfo_EG, 0, sizeof(JobInfo_EG));

	QString2Char(FileName ,InputFile ,sizeof(InputFile));
	JobInfo_EG.JobType = TOCRJOBTYPE_DIBFILE;

	JobInfo_EG.InputFile = InputFile;

	Status = TOCRInitialise(&JobNo);


	if ( Status == TOCR_OK ) {
		if ( OCRWait(JobNo, JobInfo_EG) ) {
		//if ( OCRPoll(JobNo, JobInfo2) ) {
			if ( GetResults(JobNo, &Results) ) {

				// Display the results

				if (FormatResults(Results, Msg)) {
					//QMessageBox::warning(NULL, "Example 1", Msg);
					Result=Msg;
				}

				free(Results);
			}
		}

		TOCRShutdown(JobNo);
	}


	bool	Ret=false;


	return Ret;
}
