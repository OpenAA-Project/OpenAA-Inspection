#include "XRuleOfBinder.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XCrossObj.h"

RuleOfBinderBase	*RuleOfBinderContainer::Create(int ID)
{
	switch(ID){
	case ID_ChildOfRuleAlgorithmItem				:
		return new ChildOfRuleAlgorithmItem(this);
	case ID_ChildOfRuleAllItemsInLayerAlgorithm		:
		return new ChildOfRuleAllItemsInLayerAlgorithm(this);
	case ID_ChildOfRuleAllItemsInPageAlgorithm		:
		return new ChildOfRuleAllItemsInPageAlgorithm(this);
	case ID_ChildOfRuleOperationOR					:
		return new ChildOfRuleOperationOR(this);
	case ID_ChildOfRuleOperationAND					:
		return new ChildOfRuleOperationAND(this);
	case ID_ChildOfRuleOperationXOR					:
		return new ChildOfRuleOperationXOR(this);
	case ID_ChildOfRuleOperationNEG					:
		return new ChildOfRuleOperationNEG(this);
	case ID_ChildOfRuleOperationCond					:
		return new ChildOfRuleOperationConditional(this);
	}
	return NULL;
}

int		RuleOfBinderContainer::GetLastID(void)
{
	int	MaxID=0;
	for(RuleOfBinderBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->RuleID>MaxID){
			MaxID=a->RuleID;
		}
	}
	return MaxID;
}

bool	RuleOfBinderContainer::IsInclude(int X ,int Y,double ZoomRate)
{
	for(RuleOfBinderBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(X,Y,ZoomRate)==true)
			return true;
	}
	return false;
}

bool	RuleOfBinderContainer::GetClosedConnection(int X ,int Y,double ZoomRate, int &ParentRuleID ,int &ChildRuleID ,int Isolation)
{
	for(RuleOfBinderBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetClosedConnection(X ,Y, ZoomRate,ChildRuleID ,Isolation)==true){
			ParentRuleID=a->RuleID;
			return true;
		}
	}
	return false;
}
bool	RuleOfBinderContainer::RemoveConnection(int ParentRuleID,int ChildRuleID)
{
	for(RuleOfBinderBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->RuleID==ParentRuleID){
			for(RuleOfBinderPointer *p=a->Children.GetFirst();p!=NULL;p=p->GetNext()){
				if(p->Pointer->RuleID==ChildRuleID){
					a->Children.RemoveList(p);
					delete	p;
					return true;
				}
			}
		}
	}
	return false;
}
void	RuleOfBinderContainer::DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)
{
	for(RuleOfBinderBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->DrawRule(pnt,ZoomRate ,movx,movy);
	}
	for(RuleOfBinderBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->DrawRuleChild(pnt ,ZoomRate ,movx ,movy);
	}
}

bool	RuleOfBinderContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(RuleOfBinderBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		int32	ID=a->GetClassID();
		if(::Save(f,ID)==false)
			return false;
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

bool	RuleOfBinderContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		int32	ID;
		if(::Load(f,ID)==false)
			return false;
		RuleOfBinderBase	*a=Create(ID);
		if(a!=NULL){
			if(a->Load(f)==false)
				return false;
			AppendList(a);
		}
	}
	BuildLinkFromIDList();

	return true;
}

void	RuleOfBinderContainer::BuildLinkFromIDList(void)
{
	for(RuleOfBinderBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->BuildLinkFromIDList();
	}
}
	
RuleOfBinderBase	*RuleOfBinderContainer::Find(int x ,int y,double ZoomRate)
{
	for(RuleOfBinderBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(x,y,ZoomRate)==true)
			return a;
	}
	return NULL;
}

RuleOfBinderBase	*RuleOfBinderContainer::Find(int RuleID)
{
	for(RuleOfBinderBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->RuleID==RuleID)
			return a;
	}
	return NULL;
}
RuleOfBinderBase	*RuleOfBinderContainer::GetConclusionRule(void)
{
	for(RuleOfBinderBase *r=GetFirst();r!=NULL;r=r->GetNext()){
		if(r->Conclusion==true){
			return r;;
		}
	}
	return NULL;
}

bool	RuleOfBinderContainer::ExecuteInitialAfterEdit(LayersBase *base,ExecuteInitialAfterEditInfo &EInfo)
{
	bool	Ret=true;
	for(RuleOfBinderBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ExecuteInitialAfterEdit(base,EInfo)==false){
			Ret=false;
		}
	}
	return Ret;
}

void	RuleOfBinderContainer::ReplaceOKInSource(void)
{
	for(RuleOfBinderBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->ReplaceOKInSource();
	}
}

	
bool	RuleOfBinderBase::Save(QIODevice *f)
{
	GenerateChildIDListFromLink();
	if(IDList.Save(f)==false)
		return false;
	if(::Save(f,RuleID)==false)
		return false;
	if(::Save(f,Location)==false)
		return false;
	if(::Save(f,Name)==false)
		return false;
	if(::Save(f,Remark)==false)
		return false;
	if(::Save(f,Conclusion)==false)
		return false;
	return true;
}

bool	RuleOfBinderBase::Load(QIODevice *f)
{
	if(IDList.Load(f)==false)
		return false;
	if(::Load(f,RuleID)==false)
		return false;
	if(::Load(f,Location)==false)
		return false;
	if(::Load(f,Name)==false)
		return false;
	if(::Load(f,Remark)==false)
		return false;
	if(::Load(f,Conclusion)==false)
		return false;
	return true;
}

bool	RuleOfBinderBase::ExecuteInitialAfterEdit(LayersBase *base,ExecuteInitialAfterEditInfo &EInfo)
{
	return true;
}
void	RuleOfBinderBase::DrawRuleChild(QImage &pnt ,double ZoomRate ,int movx ,int movy)
{
	QPainter	Pnt(&pnt);

	Pnt.setPen(Qt::magenta);

	int	ACx,ACy;
	GetCenter(ACx,ACy,ZoomRate);
	for(RuleOfBinderPointer *p=Children.GetFirst();p!=NULL;p=p->GetNext()){
		int	BCx,BCy;
		p->Pointer->GetCenter(BCx,BCy,ZoomRate);

		int	x1,y1;
		GetArrow(BCx,BCy,x1,y1,ZoomRate);
		int	x2,y2;
		p->Pointer->GetArrow(ACx,ACy,x2,y2,ZoomRate);

		DrawArrow(Pnt,x1,y1,x2,y2 ,ZoomRate ,movx ,movy);
	}
}

void	RuleOfBinderBase::DrawArrow(QPainter &Pnt,int gx1,int gy1,int gx2,int gy2 ,double ZoomRate ,int movx ,int movy)
{
	int	x1=(gx1+movx)*ZoomRate;
	int	y1=(gy1+movy)*ZoomRate;
	int	x2=(gx2+movx)*ZoomRate;
	int	y2=(gy2+movy)*ZoomRate;
	Pnt.drawLine(x1,y1,x2,y2);

	double	s=::GetSita(gx2-gx1,gy2-gy1);
	double	s1=s+M_PI/6.0;
	double	s2=s-M_PI/6.0;
	int		LLen=20;

	Pnt.drawLine(LLen*cos(s1)+x1,LLen*sin(s1)+y1,x1,y1);
	Pnt.drawLine(LLen*cos(s2)+x1,LLen*sin(s2)+y1,x1,y1);
}

void	RuleOfBinderBase::GetCenter(int &cx ,int &cy,double ZoomRate)
{
	cx=Location.x()+GetWidth()/ZoomRate/2;
	cy=Location.y()+GetHeight()/ZoomRate/2;
}

bool	RuleOfBinderBase::IsInclude(int X ,int Y,double ZoomRate)
{
	int	W=GetWidth()/ZoomRate;
	int	H=GetHeight()/ZoomRate;

	if(Location.x()<=X && X<Location.x()+W
	&& Location.y()<=Y && Y<Location.y()+H)
		return true;
	return false;
}
bool	RuleOfBinderBase::GetClosedConnection(int X ,int Y,double ZoomRate, int &ChildRuleID ,int Isolation)
{
	int	ACx,ACy;
	GetCenter(ACx,ACy,ZoomRate);

	for(RuleOfBinderPointer *p=Children.GetFirst();p!=NULL;p=p->GetNext()){
		int	BCx,BCy;
		p->Pointer->GetCenter(BCx,BCy,ZoomRate);
		double	Distance=GetLengthLine2Point(ACx,ACy,BCx,BCy,X,Y);
		if(Distance<=Isolation){
			ChildRuleID=p->Pointer->RuleID;
			return true;
		}
	}	 
	return false;
}
bool	RuleOfBinderBase::GetArrow(int fromX ,int fromY ,int &ToX ,int &ToY,double ZoomRate)
{
	int	W=GetWidth()/ZoomRate;
	int	H=GetHeight()/ZoomRate;
	int	Cx,Cy;
	GetCenter(Cx,Cy,ZoomRate);

	long	X,Y;

	if(GetCrossInnerPoint(fromX,fromY,Cx,Cy
						,Location.x(),Location.y(),Location.x()+W,Location.y(), X ,Y)==true){
		ToX=X;
		ToY=Y;
		return true;
	}
	if(GetCrossInnerPoint(fromX,fromY,Cx,Cy
						,Location.x()+W,Location.y(),Location.x()+W,Location.y()+H, X ,Y)==true){
		ToX=X;
		ToY=Y;
		return true;
	}
	if(GetCrossInnerPoint(fromX,fromY,Cx,Cy
						,Location.x()+W,Location.y()+H,Location.x(),Location.y()+H, X ,Y)==true){
		ToX=X;
		ToY=Y;
		return true;
	}
	if(GetCrossInnerPoint(fromX,fromY,Cx,Cy
						,Location.x(),Location.y()+H,Location.x(),Location.y(), X ,Y)==true){
		ToX=X;
		ToY=Y;
		return true;
	}
	return false;
}
void	RuleOfBinderBase::GenerateChildIDListFromLink(void)
{
	IDList.RemoveAll();
	for(RuleOfBinderPointer *a=Children.GetFirst();a!=NULL;a=a->GetNext()){
		IDList.Add(a->Pointer->RuleID);
	}
}
void	RuleOfBinderBase::BuildLinkFromIDList(void)
{
	for(IntClass *a=IDList.GetFirst();a!=NULL;a=a->GetNext()){
		for(RuleOfBinderBase *r=Root->GetFirst();r!=NULL;r=r->GetNext()){
			if(a->GetValue()==r->RuleID){
				RuleOfBinderPointer	*p=new RuleOfBinderPointer(r);
				Children.AppendList(p);
				break;
			}
		}
	}
}
void	RuleOfBinderBase::ReplaceOKInSource(void)
{
	for(RuleOfBinderPointer *a=Children.GetFirst();a!=NULL;a=a->GetNext()){
		a->Pointer->ReplaceOKInSource();
	}
}

void	RuleOfBinderBase::DrawResult(QPainter &Pnt ,int XPos ,int YPos)
{
	Pnt.setPen(Qt::red);
	if(Error==0)
		Pnt.drawText(XPos ,YPos, QString("Error:None"));
	else if(Error==1)
		Pnt.drawText(XPos ,YPos, QString("Error:OK"));
	else if(Error==2)
		Pnt.drawText(XPos ,YPos, QString("Error:NG ")+QString("Code:")+QString::number(ResultCode));
}

//=======================================================================

bool	ChildOfRuleAlgorithmItem::Save(QIODevice *f)
{
	if(RuleOfBinderBase::Save(f)==false)
		return false;
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}


bool	ChildOfRuleAlgorithmItem::Load(QIODevice *f)
{
	if(RuleOfBinderBase::Load(f)==false)
		return false;
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}

bool	ChildOfRuleAlgorithmItem::ExecuteInitialAfterEdit(LayersBase *base,ExecuteInitialAfterEditInfo &EInfo)
{
	RuleOfBinderBase::ExecuteInitialAfterEdit(base,EInfo);
	if(Phase>=0 && Page>=0){
		AlgorithmBase	*A=base->GetAlgorithmBase(AlgoRoot ,AlgoName);
		if(A!=NULL){
			AlgorithmInPageInOnePhase	*Ph=A->GetPageDataPhase(Phase);
			if(Ph!=NULL){
				AlgorithmInPageRoot		*Pg=Ph->GetPageData(Page);
				if(Pg!=NULL){
					if(Layer>=0){
						AlgorithmInLayerRoot	*AL=Pg->GetLayerData(Layer);
						if(AL!=NULL){
							if(ItemID>=0){
								Item=AL->SearchIDItem(ItemID);
								return true;
							}
							else{
								Item=AL->SearchItemByName(ItemName);
								return true;
							}
						}
						else if(Layer==0){
							if(ItemID>=0){
								Item=Pg->SearchIDItem(ItemID);
								if(Item!=NULL){
									return true;
								}
							}
							else{
								Item=Pg->SearchItemByName(ItemName);
								if(Item!=NULL){
									return true;
								}
							}
						}
					}
					else{
						if(ItemID>=0){
							Item=Pg->SearchIDItem(ItemID);
							return true;
						}
						else{
							Item=Pg->SearchItemByName(ItemName);
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool	ChildOfRuleAlgorithmItem::GetResult(ResultInItemRoot *Res)
{
	if(Item!=NULL){
		ResultInItemRoot *s=Item->GetCurrentResult();
		if(s!=NULL){
			Error		=s->GetError();
			ResultCode	=s->GetResult1();
			Res->SetError(Error);
			Res->SetResult1(ResultCode);
			Res->SetResult2(s->GetResult2());
			Res->SetResultDouble(s->GetResultDouble());
			Res->SetAlignedXY(s->GetAlignedX(),s->GetAlignedY());
			Res->SetItemSearchedXY(s->GetItemSearchedX(),s->GetItemSearchedY());
			return true;
		}
	}
	return false;
}

void	ChildOfRuleAlgorithmItem::DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)
{
	int	W=GetWidth();
	int	H=GetHeight();

	QPainter	Pnt(&pnt);

	int	XPos=(Location.x()+movx)*ZoomRate;
	int	YPos=(Location.y()+movy)*ZoomRate;

	Pnt.setPen(Qt::green);
	QColor	BackCol=Qt::darkGray;
	BackCol.setAlpha(128);
	Pnt.setBrush(BackCol);
	Pnt.drawRect(XPos	,YPos  ,W,H);

	Pnt.setPen(Qt::cyan);

	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*1 , QString("Type   :AlgorithmItem"));
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*2 , QString("DLLRoot:")+AlgoRoot);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*3 , QString("DLLName:")+AlgoName);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*4 , QString("Ph:")+QString::number(Phase)+QString(" Pg:")+QString::number(Page) +QString("Ly:")+QString::number(Layer));
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*5 , QString("Item:")+QString::number(ItemID) +QString(" , ")+ItemName);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*6 , QString("Name:")+Name);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*7 , Remark);

	DrawResult(Pnt ,XPos+5 ,YPos+5+CharaterHeight*8);

}

void	ChildOfRuleAlgorithmItem::ReplaceOKInSource(void)
{
	RuleOfBinderBase::ReplaceOKInSource();

	if(Item!=NULL){
		ResultInItemRoot	*s=Item->GetCurrentResult();
		if(s!=NULL){
			s->SetError(1);
		}
	}
}

//=======================================================================

bool	ChildOfRuleAllItemsInLayerAlgorithm::Save(QIODevice *f)
{
	if(RuleOfBinderBase::Save(f)==false)
		return false;
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

bool	ChildOfRuleAllItemsInLayerAlgorithm::Load(QIODevice *f)
{
	if(RuleOfBinderBase::Load(f)==false)
		return false;
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}


bool	ChildOfRuleAllItemsInLayerAlgorithm::ExecuteInitialAfterEdit(LayersBase *base,ExecuteInitialAfterEditInfo &EInfo)
{
	RuleOfBinderBase::ExecuteInitialAfterEdit(base,EInfo);
	if(Phase>=0 && Page>=0){
		AlgorithmBase	*A=base->GetAlgorithmBase(AlgoRoot ,AlgoName);
		if(A!=NULL){
			AlgorithmInPageInOnePhase	*Ph=A->GetPageDataPhase(Phase);
			if(Ph!=NULL){
				AlgorithmInPageRoot		*Pg=Ph->GetPageData(Page);
				if(Pg!=NULL){
					if(Layer>=0){
						AlgoLayer=Pg->GetLayerData(Layer);
						if(AlgoLayer!=NULL){
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool	ChildOfRuleAllItemsInLayerAlgorithm::GetResult(ResultInItemRoot *Res)
{
	Error		=1;
	ResultCode	=0;
	Res->SetError(1);	//OK
	Res->SetResult1(0);
	Res->SetResult2(0);
	Res->SetResultDouble(0);
	Res->SetAlignedXY(0,0);
	Res->SetItemSearchedXY(0,0);
	if(AlgoLayer!=NULL){
		int	N=AlgoLayer->GetItemCount();
		for(int i=0;i<N;i++){
			AlgorithmItemRoot	*Item=AlgoLayer->GetItemRoot(i);
			if(Item!=NULL){
				ResultInItemRoot *s=Item->GetCurrentResult();
				if(s!=NULL){
					if(s->GetError()>=2){
						Error		=s->GetError();
						ResultCode	=s->GetResult1();
						Res->SetError(Error);
						Res->SetResult1(ResultCode);
						Res->SetResult2(s->GetResult2());
						Res->SetResultDouble(s->GetResultDouble());
						Res->SetAlignedXY(s->GetAlignedX(),s->GetAlignedY());
						Res->SetItemSearchedXY(s->GetItemSearchedX(),s->GetItemSearchedY());
					}
				}
			}
		}
		return true;
	}
	return false;
}

void	ChildOfRuleAllItemsInLayerAlgorithm::DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)
{
	int	W=GetWidth();
	int	H=GetHeight();

	QPainter	Pnt(&pnt);

	int	XPos=(Location.x()+movx)*ZoomRate;
	int	YPos=(Location.y()+movy)*ZoomRate;

	Pnt.setPen(Qt::green);
	QColor	BackCol=Qt::darkGray;
	BackCol.setAlpha(128);
	Pnt.setBrush(BackCol);
	Pnt.drawRect(XPos	,YPos  ,W,H);

	Pnt.setPen(Qt::cyan);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*1 , QString("Type   :AllItemsInLayer"));
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*2 , QString("DLLRoot:")+AlgoRoot);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*3 , QString("DLLName:")+AlgoName);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*4 , QString("Ph:")+QString::number(Phase)+QString(" Pg:")+QString::number(Page) +QString("Ly:")+QString::number(Layer));
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*5 , QString("Name:")+Name);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*6 , Remark);
	DrawResult(Pnt ,XPos+5 ,YPos+5+CharaterHeight*7);

}

static	void ReplaceOKInLayer(AlgorithmItemRoot *Item ,void *_Something)
{
	int	*Layer=(int *)_Something;
	if(Item!=NULL){
		if(*Layer==Item->GetLayer()){
			ResultInItemRoot	*s=Item->GetCurrentResult();
			if(s!=NULL){
				s->SetError(1);
			}
		}
	}
}

void	ChildOfRuleAllItemsInLayerAlgorithm::ReplaceOKInSource(void)
{
	RuleOfBinderBase::ReplaceOKInSource();

	AlgoLayer->LoopforAllItems(ReplaceOKInLayer,&Layer);
}

//=======================================================================

bool	ChildOfRuleAllItemsInPageAlgorithm::Save(QIODevice *f)
{
	if(RuleOfBinderBase::Save(f)==false)
		return false;
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	return true;
}
	
bool	ChildOfRuleAllItemsInPageAlgorithm::Load(QIODevice *f)
{
	if(RuleOfBinderBase::Load(f)==false)
		return false;
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;

	return true;
}


bool	ChildOfRuleAllItemsInPageAlgorithm::ExecuteInitialAfterEdit(LayersBase *base,ExecuteInitialAfterEditInfo &EInfo)
{
	RuleOfBinderBase::ExecuteInitialAfterEdit(base,EInfo);
	if(Phase>=0 && Page>=0){
		AlgorithmBase	*A=base->GetAlgorithmBase(AlgoRoot ,AlgoName);
		if(A!=NULL){
			AlgorithmInPageInOnePhase	*Ph=A->GetPageDataPhase(Phase);
			if(Ph!=NULL){
				AlgoPage=Ph->GetPageData(Page);
				if(AlgoPage!=NULL){
					return true;
				}
			}
		}
	}
	return false;
}
	
bool	ChildOfRuleAllItemsInPageAlgorithm::GetResult(ResultInItemRoot *Res)
{
	Error		=1;
	ResultCode	=0;
	Res->SetError(1);	//OK
	Res->SetResult1(0);
	Res->SetResult2(0);
	Res->SetResultDouble(0);
	Res->SetAlignedXY(0,0);
	Res->SetItemSearchedXY(0,0);
	if(AlgoPage!=NULL){
		int	LayerNumb=AlgoPage->GetLayerNumb();
		AlgorithmInLayerRoot	*Ly=AlgoPage->GetLayerData(0);
		if(Ly!=NULL){
			for(int Layer=0;Layer<LayerNumb;Layer++){
				AlgorithmInLayerRoot	*AL=AlgoPage->GetLayerData(Layer);
				int	N=AL->GetItemCount();
				for(int i=0;i<N;i++){
					AlgorithmItemRoot	*Item=AL->GetItemRoot(i);
					if(Item!=NULL){
						ResultInItemRoot *s=Item->GetCurrentResult();
						if(s!=NULL){
							if(s->GetError()>=2){
								Error		=s->GetError();
								ResultCode	=s->GetResult1();
								Res->SetError(Error);
								Res->SetResult1(ResultCode);
								Res->SetResult2(s->GetResult2());
								Res->SetResultDouble(s->GetResultDouble());
								Res->SetAlignedXY(s->GetAlignedX(),s->GetAlignedY());
								Res->SetItemSearchedXY(s->GetItemSearchedX(),s->GetItemSearchedY());
							}
						}
					}
				}
			}
		}
		else{
			int	N=AlgoPage->GetItemCount();
			for(int i=0;i<N;i++){
				AlgorithmItemRoot	*Item=AlgoPage->GetItemData(0,i);
				if(Item!=NULL){
					ResultInItemRoot *s=Item->GetCurrentResult();
					if(s!=NULL){
						if(s->GetError()>=2){
							Error		=s->GetError();
							ResultCode	=s->GetResult1();
							Res->SetError(Error);
							Res->SetResult1(ResultCode);
							Res->SetResult2(s->GetResult2());
							Res->SetResultDouble(s->GetResultDouble());
							Res->SetAlignedXY(s->GetAlignedX(),s->GetAlignedY());
							Res->SetItemSearchedXY(s->GetItemSearchedX(),s->GetItemSearchedY());
						}
					}
				}
			}
		}
		return true;
	}
	return false;
}

void	ChildOfRuleAllItemsInPageAlgorithm::DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)
{
	int	W=GetWidth();
	int	H=GetHeight();

	QPainter	Pnt(&pnt);

	int	XPos=(Location.x()+movx)*ZoomRate;
	int	YPos=(Location.y()+movy)*ZoomRate;

	Pnt.setPen(Qt::green);
	QColor	BackCol=Qt::darkGray;
	BackCol.setAlpha(128);
	Pnt.setBrush(BackCol);
	Pnt.drawRect(XPos	,YPos  ,W,H);

	Pnt.setPen(Qt::cyan);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*1 , QString("Type   :AllItemsInPage"));
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*2 , QString("DLLRoot:")+AlgoRoot);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*3 , QString("DLLName:")+AlgoName);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*4 , QString("Ph:")+QString::number(Phase)+QString(" Pg:")+QString::number(Page));
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*5 , QString("Name:")+Name);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*6 , Remark);
	DrawResult(Pnt ,XPos+5 ,YPos+5+CharaterHeight*7);

}
static	void ReplaceOKIPage(AlgorithmItemRoot *Item ,void *_Something)
{
	int	*Page=(int *)_Something;
	if(Item!=NULL){
		if(*Page==Item->GetPage()){
			ResultInItemRoot	*s=Item->GetCurrentResult();
			if(s!=NULL){
				s->SetError(1);
			}
		}
	}
}

void	ChildOfRuleAllItemsInPageAlgorithm::ReplaceOKInSource(void)
{
	RuleOfBinderBase::ReplaceOKInSource();

	AlgoPage->LoopforAllItems(ReplaceOKIPage,&Page);
}

//=======================================================================

bool	ChildOfRuleOperationOR::GetResult(ResultInItemRoot *Res)
{
	int	Result=2;
	for(RuleOfBinderPointer *a=Children.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Pointer->GetResult(Res)==true){
			if(Res->GetError()==1)
				Result=1;
		}
	}
	Error		=Result;
	Res->SetError(Result);
	return true;
}
void	ChildOfRuleOperationOR::DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)
{
	int	W=GetWidth();
	int	H=GetHeight();

	QPainter	Pnt(&pnt);

	int	XPos=(Location.x()+movx)*ZoomRate;
	int	YPos=(Location.y()+movy)*ZoomRate;

	Pnt.setPen(Qt::green);
	QColor	BackCol=Qt::darkGray;
	BackCol.setAlpha(128);
	Pnt.setBrush(BackCol);
	Pnt.drawRect(XPos	,YPos  ,W,H);

	Pnt.setPen(Qt::cyan);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*1 , QString("Type   :OperationOR"));
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*2 , QString("Name:")+Name);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*3 , Remark);
	DrawResult(Pnt ,XPos+5 ,YPos+5+CharaterHeight*4);

}

//=======================================================================

bool	ChildOfRuleOperationAND::GetResult(ResultInItemRoot *Res)
{
	int	Result=1;
	for(RuleOfBinderPointer *a=Children.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Pointer->GetResult(Res)==true){
			if(Res->GetError()>=2)
				Result=2;
		}
	}
	Error		=Result;
	Res->SetError(Result);
	return true;
}
void	ChildOfRuleOperationAND::DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)
{
	int	W=GetWidth();
	int	H=GetHeight();

	QPainter	Pnt(&pnt);

	int	XPos=(Location.x()+movx)*ZoomRate;
	int	YPos=(Location.y()+movy)*ZoomRate;

	Pnt.setPen(Qt::green);
	QColor	BackCol=Qt::darkGray;
	BackCol.setAlpha(128);
	Pnt.setBrush(BackCol);
	Pnt.drawRect(XPos	,YPos  ,W,H);

	Pnt.setPen(Qt::cyan);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*1 , QString("Type   :OperationAND"));
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*2 , QString("Name:")+Name);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*3 , Remark);
	DrawResult(Pnt ,XPos+5 ,YPos+5+CharaterHeight*4);
}

//=======================================================================

bool	ChildOfRuleOperationXOR::GetResult(ResultInItemRoot *Res)
{
	int	Result=1;
	RuleOfBinderPointer *a1=Children.GetFirst();
	if(a1==NULL)
		return false;
	RuleOfBinderPointer *a2=a1->GetNext();
	if(a2==NULL)
		return false;
	if(a1->Pointer->GetResult(Res)==false)
		return false;
	bool	OK1;
	if(Res->GetError()==1)
		OK1=true;
	else
		OK1=false;

	if(a2->Pointer->GetResult(Res)==false)
		return false;
	bool	OK2;
	if(Res->GetError()==1)
		OK2=true;
	else
		OK2=false;

	if((OK1==true && OK2==false) || (OK1==false && OK2==true)){
		Error		=1;
		Res->SetError(1);
	}
	else{
		Error		=2;
		Res->SetError(2);
	}
	return true;
}
void	ChildOfRuleOperationXOR::DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)
{
	int	W=GetWidth();
	int	H=GetHeight();

	QPainter	Pnt(&pnt);

	int	XPos=(Location.x()+movx)*ZoomRate;
	int	YPos=(Location.y()+movy)*ZoomRate;

	Pnt.setPen(Qt::green);
	QColor	BackCol=Qt::darkGray;
	BackCol.setAlpha(128);
	Pnt.setBrush(BackCol);
	Pnt.drawRect(XPos	,YPos  ,W,H);

	Pnt.setPen(Qt::cyan);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*1 , QString("Type   :OperationXOR"));
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*2 , QString("Name:")+Name);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*3 , Remark);
	DrawResult(Pnt ,XPos+5 ,YPos+5+CharaterHeight*4);
}

//=======================================================================

bool	ChildOfRuleOperationNEG::GetResult(ResultInItemRoot *Res)
{
	int	Result=1;
	RuleOfBinderPointer *a1=Children.GetFirst();
	if(a1==NULL)
		return false;

	if(a1->Pointer->GetResult(Res)==false)
		return false;

	if(Res->GetError()==1){
		Res->SetError(2);
		Error		=2;
	}
	else{
		Res->SetError(1);
		Error		=1;
	}
	return true;
}
void	ChildOfRuleOperationNEG::DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)
{
	int	W=GetWidth();
	int	H=GetHeight();

	QPainter	Pnt(&pnt);

	int	XPos=(Location.x()+movx)*ZoomRate;
	int	YPos=(Location.y()+movy)*ZoomRate;

	Pnt.setPen(Qt::green);
	QColor	BackCol=Qt::darkGray;
	BackCol.setAlpha(128);
	Pnt.setBrush(BackCol);
	Pnt.drawRect(XPos	,YPos  ,W,H);

	Pnt.setPen(Qt::cyan);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*1 , QString("Type   :OperationNEG"));
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*2 , QString("Name:")+Name);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*3 , Remark);
	DrawResult(Pnt ,XPos+5 ,YPos+5+CharaterHeight*4);
}

//=======================================================================
	
bool	ChildOfRuleOperationConditional::GetResult(ResultInItemRoot *Res)
{
	int	Result=1;
	for(ConditionList *C=ConditionData.GetFirst();C!=NULL;C=C->GetNext()){
		int	CondOK=0;
		int	n=0;
		int	InpCount=C->InputData.GetCount();
		for(RuleOfBinderPointer *a=Children.GetFirst();a!=NULL && n<InpCount;a=a->GetNext(),n++){
			if(a->Pointer->GetResult(Res)==true){
				if(Res->GetError()==1 && C->InputData[n]->OK==true)
					CondOK++;
				else if(Res->GetError()>=2 && C->InputData[n]->OK==false){
					if(C->InputData[n]->ErrorCondition==0)
						continue;
					else if(C->InputData[n]->ErrorCondition==1){
						if(Res->GetResult1()!=C->InputData[n]->ErrorCode)
							goto	NextCondition;
					}
					else if(C->InputData[n]->ErrorCondition==2){
						if(Res->GetResult1()<C->InputData[n]->ErrorCode)
							goto	NextCondition;
					}
					else if(C->InputData[n]->ErrorCondition==3){
						if(Res->GetResult1()>C->InputData[n]->ErrorCode)
							goto	NextCondition;
					}
				}
				else
					goto	NextCondition;
			}
		}
		Error		=C->OutputOK==true?1:2;
		Res->SetError(Error);
		Res->SetResult1(C->OutputErrorCode);
		return true;

		NextCondition:;
	}
	Error	=NGOthers==true?2:1;
	Res->SetError(Error);
	return true;
}

void	ChildOfRuleOperationConditional::DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)
{
	int	W=GetWidth();
	int	H=GetHeight();

	QPainter	Pnt(&pnt);

	int	XPos=(Location.x()+movx)*ZoomRate;
	int	YPos=(Location.y()+movy)*ZoomRate;

	Pnt.setPen(Qt::green);
	QColor	BackCol=Qt::darkGray;
	BackCol.setAlpha(128);
	Pnt.setBrush(BackCol);
	Pnt.drawRect(XPos	,YPos  ,W,H);

	Pnt.setPen(Qt::cyan);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*1 , QString("Type   :OperationConditional"));
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*2 , QString("Name:")+Name);
	Pnt.drawText(XPos+5 ,YPos+5+CharaterHeight*3 , Remark);
	DrawResult(Pnt ,XPos+5 ,YPos+5+CharaterHeight*4);
}
			
bool	ChildOfRuleOperationConditional::Save(QIODevice *f)
{
	if(RuleOfBinderBase::Save(f)==false)
		return false;
	if(ConditionData.Save(f)==false)
		return false;
	if(::Save(f,NGOthers)==false)
		return false;
	return true;
}

bool	ChildOfRuleOperationConditional::Load(QIODevice *f)
{
	if(RuleOfBinderBase::Load(f)==false)
		return false;
	if(ConditionData.Load(f)==false)
		return false;
	if(::Load(f,NGOthers)==false)
		return false;
	return true;
}