#include "XNickInspection.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XYCross.h"
#include "XFlexArea.h"
#include "XDisplayBitImage.h"
#include "swap.h"
#include "XAlgorithmDLL.h"

const int	NickAreaMergin	=6;

void	MatrixBuffCopyWindow(BYTE **MapSrc,int SrcXLen,int SrcYLen
						,int Px,int Py
						,BYTE **DstMap,int DstXLen,int DstYLen
						,int DstMerginX,int DstMerginY);

static	int	DbgPx=4350;
static	int	DbgPy=1000;
static	int	DbgD=0;

//==================================================================================================

NickInspectionItem::NickInspectionItem(void)
{
	BMap	=NULL;
	TmpMap	=NULL;
	BMapXByte=0;
	BMapXLen=0;
	BMapYLen=0;
}
NickInspectionItem::NickInspectionItem(FlexArea *area)
	:AlgorithmItemPI(area)
{
	BMap	=NULL;
	TmpMap	=NULL;
	BMapXByte=0;
	BMapXLen=0;
	BMapYLen=0;
}
NickInspectionItem::~NickInspectionItem(void)
{
	if(BMap!=NULL){
		DeleteMatrixBuff(BMap,BMapYLen);
		BMap=NULL;
	}
	if(TmpMap!=NULL){
		DeleteMatrixBuff(TmpMap,BMapYLen);
		TmpMap=NULL;
	}

	BMapXByte=0;
	BMapXLen=0;
	BMapYLen=0;
}

struct	CallerStruct
{
	NickInspectionItem	*NickItem;
	int		AreaX1,AreaY1,AreaX2,AreaY2;
	int		LibType;
	IntList	LibList;
};

bool	SearchFunc(void *caller,AlgorithmItemRoot *item)
{
	struct	CallerStruct	*CallerPointer=(struct	CallerStruct *)caller;
	if(CallerPointer->LibList.IsInclude(item->GetLibID())==true){
		if(item->GetArea().CheckOverlapRectangle(CallerPointer->AreaX1,CallerPointer->AreaY1,CallerPointer->AreaX2,CallerPointer->AreaY2)==true){
			return true;
		}
	}
	return false;
}

ExeResult	NickInspectionItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	const NickInspectionThreshold	*RThr=GetThresholdR();
	TargetItems.RemoveAll();
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypeProcessing)==true){
			AlgorithmBase	*ABase=L->GetInstance();
			if(RThr->LibList.IsIncludeLibType(ABase->GetLibType())==true){
				AlgorithmInPageRoot	*Ap=ABase->GetPageData(GetPage());
				struct	CallerStruct	CallerData;
				CallerData.NickItem=this;
				GetXY(CallerData.AreaX1,CallerData.AreaY1,CallerData.AreaX2,CallerData.AreaY2);
				RThr->LibList.MakeLibList(ABase->GetLibType(),CallerData.LibList);
				TargetItems.RemoveAll();
				Ap->EnumItems(&CallerData,TargetItems,SearchFunc);
			}	
		}
	}
	if(BMap!=NULL){
		DeleteMatrixBuff(BMap,BMapYLen);
		BMap=NULL;
	}
	if(TmpMap!=NULL){
		DeleteMatrixBuff(TmpMap,BMapYLen);
		TmpMap=NULL;
	}
	
	X1=GetArea().GetMinX()-GetArea().GetWidth()/4;
	Y1=GetArea().GetMinY()-GetArea().GetHeight()/4;
	BMapXLen=GetArea().GetWidth()*1.5;
	BMapYLen=GetArea().GetHeight()*1.5;
	BMapXByte	=(BMapXLen+7)/8;
	BMap	=MakeMatrixBuff(BMapXByte ,BMapYLen);
	TmpMap	=MakeMatrixBuff(BMapXByte ,BMapYLen);
	return _ER_true;
}

ExeResult	NickInspectionItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	MatrixBuffClear(BMap,0,BMapXByte,BMapYLen);
	for(AlgorithmLibraryListWithResult *s=GetThresholdR()->LibList.GetFirst();s!=NULL;s=s->GetNext()){
		s->SetResultOk(true);
	}
	return _ER_true;
}

ExeResult	NickInspectionItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	ImagePointerContainer ImageList;
	GetTargetBuffList(ImageList);
	const NickInspectionThreshold	*RThr=GetThresholdR();
	ImageBuffer	*IBuff=ImageList[RThr->Layer];
	NickInspectionBase	*PBase=(NickInspectionBase *)GetParentBase();

	for(AlgorithmItemPointerList *s=TargetItems.GetFirst();s!=NULL;s=s->GetNext()){
		ResultInItemRoot	*R=s->GetItem()->GetCurrentResult();
		if(R!=NULL){
			if(R->IsOk()==false){
				for(ResultPosList *r=R->GetPosList().GetFirst();r!=NULL;){
					ResultPosList *rnext=r->GetNext();

					int	Mx,My;
					R->GetTotalShifted(Mx,My);
					Mx+=r->Rx;
					My+=r->Ry;
					r->NGShape.MakeBitData(BMap
                                    ,-X1 ,-Y1
                                    ,BMapYLen, BMapYLen);
					int	W=r->NGShape.GetWidth();
					int	H=r->NGShape.GetHeight();
					int	L=max(W,H)*100/RThr->NGPercentage;
					if(L<PBase->MaxNSize){
						GetLayersBase()->FatAreaN(BMap,TmpMap,BMapXByte,BMapYLen,L);

						MakePartialBinaryBit(IBuff,TmpMap,X1+Mx,Y1+My);
						PureFlexAreaListContainer FPack1;
						PureFlexAreaListContainer FPack2;
						PickupFlexArea(TmpMap ,BMapXByte ,BMapXLen,BMapYLen ,FPack1);
						MatrixBuffNotAnd(TmpMap ,(const BYTE **)BMap,BMapXByte ,BMapYLen);
						PickupFlexArea(TmpMap ,BMapXByte ,BMapXLen,BMapYLen ,FPack2);
						if(FPack1.GetCount()==FPack2.GetCount()){
							R->GetPosList().RemoveList(r);
							delete	r;
						}
						else{
							AlgorithmLibraryListWithResult	*A=GetThresholdW()->LibList.Find(s->GetItem()->GetParentBase()->GetLibType(), s->GetItem()->GetLibID());
							if(A!=NULL){
								A->SetResultOk(false);
							}
						}
					}
					else{
						AlgorithmLibraryListWithResult	*A=GetThresholdW()->LibList.Find(s->GetItem()->GetParentBase()->GetLibType(), s->GetItem()->GetLibID());
						if(A!=NULL){
							A->SetResultOk(false);
						}
					}
					r=rnext;
				}
				if(R->GetPosList().GetCount()==0){
					R->SetError(1);
				}
			}
		}
	}

	return _ER_true;
}

void	NickInspectionItem::MakePartialBinaryBit(ImageBuffer *IBuff, BYTE **TmpMap,int X,int Y)
{
	const NickInspectionThreshold	*RThr=GetThresholdR();
	bool	EnableWhite		=RThr->EnableWhite;
	int		RefBrightness	=RThr->RefBrightness;

	for(int y=0;y<BMapYLen;y++){
		int	my=Y+y;
		BYTE	*d=TmpMap[y];
		if(my<0 || GetMaxLines()<=my){
			memset(d,0,BMapXByte);
			continue;
		}
		BYTE	*s=IBuff->GetY(my);
		for(int x=0;x<BMapXLen;x++){
			int	mx=X+x;
			if(mx<0 || GetDotPerLine()<=mx){
				SetBmpBitOnY0(d,x);
				continue;
			}
			int	c=s[mx];
			if(EnableWhite==true && c>=RefBrightness)
				SetBmpBitOnY1(d,x);
			else
			if(EnableWhite==false && c<=RefBrightness)
				SetBmpBitOnY1(d,x);
			else
				SetBmpBitOnY0(d,x);
		}
	}
}


void	NickInspectionItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	NickInspectionDrawAttr	*BAttr=dynamic_cast<NickInspectionDrawAttr *>(Attr);
	if(BAttr!=NULL){
		AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,BAttr);
		const NickInspectionThreshold	*RThr=GetThresholdR();
		if(RThr->LibList.GetResultOk()==false && BMap!=NULL){
			QColor	Col(0,0,192,128);
			DrawBitImageOr(pnt, (const BYTE **)BMap ,BMapXLen ,BMapXByte ,BMapYLen
					,movx ,movy ,ZoomRate
					,-X1 ,-Y1
					,Col);
		}
	}
	else{
		AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	NickInspectionItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	QColor	Col(0,0,192,128);
	DrawBitImageOr(IData, (const BYTE **)BMap ,BMapXLen ,BMapXByte ,BMapYLen
					,MovX ,MovY ,ZoomRate
					,-GetArea().GetMinX()+NickAreaMergin ,-GetArea().GetMinY()+NickAreaMergin
					,Col);
	AlgorithmItemPI::DrawResultItem(Res,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);
}


void	NickInspectionItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			NickInspectionInPage	*Pg=dynamic_cast<NickInspectionInPage *>(GetParentInPage());
			UndoElement<NickInspectionInPage>	*UPointer=new UndoElement<NickInspectionInPage>(Pg,&NickInspectionInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			NickInspectionItem *src=(NickInspectionItem *)Data;
			CopyThresholdOnly(*src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((NickInspectionItem *)Data)->GetLibID()){
			NickInspectionInPage	*Pg=dynamic_cast<NickInspectionInPage *>(GetParentInPage());
			UndoElement<NickInspectionInPage>	*UPointer=new UndoElement<NickInspectionInPage>(Pg,&NickInspectionInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			NickInspectionItem *src=(NickInspectionItem *)Data;
			CopyThresholdOnly(*src);
			SetLibID(src->GetLibID());
		}
	}

}
void	NickInspectionItem::CopyThresholdOnly(NickInspectionItem &src)
{
	GetThresholdW()->CopyFrom(*((NickInspectionThreshold *)src.GetThresholdR()));
}

void	NickInspectionItem::MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)
{
}