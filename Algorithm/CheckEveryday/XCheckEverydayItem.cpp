#include "XCheckEveryday.h"

CheckEverydayItemBase::CheckEverydayItemBase(void)
{
	Result	=false;
	AVector	=NULL;
	RegNumber	=360;
}
CheckEverydayItemBase::~CheckEverydayItemBase(void)
{
}
	
bool	CheckEverydayItemBase::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,RegNumber)==false)
		return false;

	return true;
}

bool	CheckEverydayItemBase::Load(QIODevice *f,LayersBase *LBase)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,RegNumber)==false)
		return false;

	return true;
}

//----------------------------------------------------------------------------------------------------

CheckEverydayLightItem::CheckEverydayLightItem(void)
{
	BrightnessLow=0;
	BrightnessHigh=255;
	Average=0;
}
CheckEverydayLightItem::~CheckEverydayLightItem(void)
{
}


ExeResult	CheckEverydayLightItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);
	return _ER_true;
}
ExeResult	CheckEverydayLightItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
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
		mx=V.ShiftX;
		my=V.ShiftY;
	}

	Average=GetArea().GetAverage(GetTargetBuff(),mx,my);
	Res->SetAlignedXY(mx,my);
	if(Average<BrightnessLow){
		int	Cx,Cy;
		GetCenter(Cx,Cy);
		ResultPosList	*R=new ResultPosList(Cx,Cy,mx,my);
		R->result=0x10000+1;
		R->SetResult(Average);
		Res->AddPosList(R);
		Result=false;
		Res->SetResult1(1);
		Res->SetError(2);
	}
	else
	if(BrightnessHigh<Average){
		int	Cx,Cy;
		GetCenter(Cx,Cy);
		ResultPosList	*R=new ResultPosList(Cx,Cy,mx,my);
		R->result=0x10000+2;
		R->SetResult(Average);
		Res->AddPosList(R);
		Result=false;
		Res->SetResult1(2);
		Res->SetError(2);
	}	
	else{
		Result=true;
		Res->SetError(1);
	}

	return _ER_true; 
}

void	CheckEverydayLightItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	CheckEverydayDrawAttr	*BAttr=dynamic_cast<CheckEverydayDrawAttr *>(Attr);
	if(BAttr!=NULL){
		CheckEverydayDrawAttr	TmpAttr;
		TmpAttr=*BAttr;
		TmpAttr.NormalColor=Qt::green;
		AlgorithmItemPLI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,&TmpAttr);
	}
	else{
		AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	CheckEverydayLightItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		QColor	c=Qt::red;
		c.setAlpha(100);
		GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
							,&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
		if(ZoomRate>1.0){
			int	cx,cy;
			GetArea().GetCenter(cx,cy);
			int	kx=(cx+MovX)*ZoomRate;
			int	ky=(cy+MovY)*ZoomRate;
			if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
				QRect	rect(0,0,IData.width(),IData.height());
				PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
						,QString(/**/"Light")+GetParamGlobal()->GetLayerName((int)GetParent()->GetLayer())
						+QString(/**/" Now:")+QString::number(Average)
						+QString(/**/" ID:")+QString::number((int)GetID())
						,&rect);
			}
		}
	}
}

bool	CheckEverydayLightItem::Save(QIODevice *f)
{
	if(AlgorithmItemPLI::Save(f)==false)
		return false;
	int32	Ver=3;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,BrightnessLow)==false)
		return false;
	if(::Save(f,BrightnessHigh)==false)
		return false;
	//if(::Save(f,ItemName)==false)
	//	return false;

	if(CheckEverydayItemBase::Save(f)==false)
		return false;

	return true;
}
bool	CheckEverydayLightItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return false;

	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,BrightnessLow)==false)
		return false;
	if(::Load(f,BrightnessHigh)==false)
		return false;
	if(Ver==2){
		QString	tItemName;
		if(::Load(f,tItemName)==false)
			return false;
		SetItemName(tItemName);
	}
	if(Ver>=3){
		if(CheckEverydayItemBase::Load(f,LBase)==false)
			return false;
	}
	return true;
}

//----------------------------------------------------------------------------------------------------
CheckEverydayFocusItem::CheckEverydayFocusItem(void)
{
	LineCount=0;
	VCoeff=0;
	FocusLow=100;
}
CheckEverydayFocusItem::~CheckEverydayFocusItem(void)
{
}


ExeResult	CheckEverydayFocusItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);
	return _ER_true;
}

ExeResult	CheckEverydayFocusItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
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
		mx=V.ShiftX;
		my=V.ShiftY;
	}

	double	Average=GetArea().GetAverage(GetTargetBuff(),mx,my);
	Res->SetAlignedXY(mx,my);
	if(Average>0){
		VCoeff=GetArea().GetBunsan(GetTargetBuff(),Average,mx,my);
		VCoeff=100.0*sqrt(VCoeff)/Average;
	}
	else{
		VCoeff=0;
	}
	CheckEverydayBase	*ABase=(CheckEverydayBase *)GetParentBase();
	if(ABase->UseFocusLayer>=0){
		if(GetLayer()!=ABase->UseFocusLayer){
			VCoeff=0;
		}
	}
	if(FocusLow>VCoeff && VCoeff>0){
		int	Cx,Cy;
		GetCenter(Cx,Cy);
		ResultPosList	*R=new ResultPosList(Cx,Cy,mx,my);
		R->result=0x10000+0x10;
		R->SetResult(VCoeff);
		Res->AddPosList(R);
		Result=false;
		Res->SetResult1(0x10);
		Res->SetError(2);
	}
	else{
		Res->SetError(1);
		Result=true;
	}
	return _ER_true;
}

void	CheckEverydayFocusItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	CheckEverydayDrawAttr	*BAttr=dynamic_cast<CheckEverydayDrawAttr *>(Attr);
	if(BAttr!=NULL){
		CheckEverydayDrawAttr	TmpAttr;
		TmpAttr=*BAttr;
		TmpAttr.NormalColor=Qt::cyan;
		AlgorithmItemPLI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,&TmpAttr);
	}
	else{
		AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	CheckEverydayFocusItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		QColor	c=Qt::red;
		c.setAlpha(100);
		GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
							,&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
		if(ZoomRate>1.0){
			int	cx,cy;
			GetArea().GetCenter(cx,cy);
			int	kx=(cx+MovX)*ZoomRate;
			int	ky=(cy+MovY)*ZoomRate;
			if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
				QRect	rect(0,0,IData.width(),IData.height());
				PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
						,QString(/**/"Focus")+GetParamGlobal()->GetLayerName((int)GetParent()->GetLayer())
						+QString(/**/" Now:")+QString::number(VCoeff)
						+QString(/**/" ID:")+QString::number((int)GetID())
						,&rect);
			}
		}
	}
}

	
bool	CheckEverydayFocusItem::Save(QIODevice *f)
{
	if(AlgorithmItemPLI::Save(f)==false)
		return false;
	int32	Ver=4;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,FocusLow)==false)
		return false;
	//if(::Save(f,ItemName)==false)
	//	return false;
	if(CheckEverydayItemBase::Save(f)==false)
		return false;

	return true;
}

bool	CheckEverydayFocusItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return false;
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,FocusLow)==false)
		return false;
	if(Ver==2){
		QString	tItemName;
		if(::Load(f,tItemName)==false)
			return false;
		SetItemName(tItemName);
	}
	if(Ver>=4){
		if(CheckEverydayItemBase::Load(f,LBase)==false)
			return false;
	}
	return true;
}
