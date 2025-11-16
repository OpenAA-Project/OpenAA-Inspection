#include "XDustReducerAI.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XIntClass.h"

DustRegList::DustRegList(void)
{
	ID			=-1;
	Pattern[0]	=NULL;
	Pattern[1]	=NULL;
	Pattern[2]	=NULL;
	LayerNumb	=1;
	XLen		=256;
	YLen		=256;
	JudgeDustValue	=_Judge_NG;
}
DustRegList::~DustRegList(void)
{
	for(int i=0;i<3;i++){
		if(Pattern[i]!=NULL){
			delete	[]Pattern[i];
		}
		Pattern[i]=NULL;
	}
}

bool	DustRegList::Save(QIODevice *f)
{
	int16	Ver=1;

	if(::Save(f,Ver)==false)		return false;
	if(::Save(f,ID)==false)			return false;
	if(::Save(f,LayerNumb)==false)	return false;
	if(::Save(f,XLen)==false)		return false;
	if(::Save(f,YLen)==false)		return false;
	if(::Save(f,Comment)==false)	return false;

	BYTE	d=(BYTE)JudgeDustValue;
	if(::Save(f,d)==false)			return false;

	int	Len=XLen*YLen;
	for(int layer=0;layer<LayerNumb;layer++){
		if(Pattern[layer]!=NULL){
			if(f->write((const char *)Pattern[layer],Len)!=Len){
				return false;
			}
		}
		else{
			BYTE	c=0;
			for(int i=0;i<Len;i++){
				if(f->write((const char *)&c,1)!=1){
					return false;
				}
			}
		}
	}
	return true;
}
bool	DustRegList::Load(QIODevice *f)
{
	int16	Ver=1;

	int16	iLayerNumb;
	int16	iXLen;
	int16	iYLen;

	if(::Load(f,Ver)==false)		return false;
	if(::Load(f,ID)==false)			return false;
	if(::Load(f,iLayerNumb)==false)	return false;
	if(::Load(f,iXLen)==false)		return false;
	if(::Load(f,iYLen)==false)		return false;
	if(::Load(f,Comment)==false)	return false;

	BYTE	d;
	if(::Load(f,d)==false)			return false;
	JudgeDustValue	=(JudgeDust)d;

	if(iLayerNumb!=LayerNumb || iXLen!=XLen || iYLen!=YLen){
		for(int i=0;i<3;i++){
			if(Pattern[i]!=NULL){
				delete	[]Pattern[i];
			}
			Pattern[i]=NULL;
		}
		LayerNumb=iLayerNumb;
		XLen	=iXLen;
		YLen	=iYLen;
		int	Len=XLen*YLen;
		for(int layer=0;layer<LayerNumb;layer++){
			Pattern[layer]=new BYTE[Len];
		}
	}
	int	Len=XLen*YLen;
	for(int layer=0;layer<LayerNumb;layer++){
		if(f->read((char *)Pattern[layer],Len)!=Len){
			return false;
		}
	}
	CalcInitial();
	return true;
}
void	DustRegList::Set(BYTE *CurrentPattern[3],int _LayerNumb ,int _XLen ,int _YLen ,const QString &_Comment,JudgeDust OkNg)
{
	for(int i=0;i<3;i++){
		if(Pattern[i]!=NULL){
			delete	[]Pattern[i];
		}
		Pattern[i]=NULL;
	}
	LayerNumb=_LayerNumb;
	XLen	=_XLen;
	YLen	=_YLen;
	int	Len=XLen*YLen;
	for(int layer=0;layer<LayerNumb;layer++){
		Pattern[layer]=new BYTE[Len];
		if(CurrentPattern[layer]!=NULL){
			memcpy(Pattern[layer],CurrentPattern[layer],Len);
		}
	}
	Comment			=_Comment;
	JudgeDustValue=OkNg;
	CalcInitial();
}
void	DustRegList::CalcInitial(void)
{
	int	Len=XLen*YLen;
	for(int layer=0;layer<LayerNumb;layer++){
		A[layer]=0;
		AA[layer]=0;
		BYTE	*s=Pattern[layer];
		for(int i=0;i<Len;i++){
			BYTE	k=*(s++);
			A [layer]+=k;
			AA[layer]+=k*k;
		}
	}
}

int	DustRegListPointer::Compare(DustRegListPointer &src)
{
	double	R=Result-src.Result;
	if(R>0)
		return -1;
	if(R<0)
		return 1;
	return 0;
}

int		DustRegContainer::GetMaxID(void)
{
	int	MaxID=0;
	for(DustRegList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ID>MaxID){
			MaxID=a->ID;
		}
	}
	return MaxID;
}


DustRegListPointer	*DustRegContainer::Calc(BYTE *CurrentPattern[3] ,int LayerNumb ,int XLen ,int YLen,IntList &AdaptedLayer,JudgeDust Filter)
{
	if(GetCount()!=DustRegListPointerContainer.GetCount()){
		DustRegListPointerContainer.RemoveAll();
		for(DustRegList *a=GetFirst();a!=NULL;a=a->GetNext()){
			DustRegListPointer	*p=new DustRegListPointer(a);
			DustRegListPointerContainer.AppendList(p);
		}
	}
	DustRegListPointer	*p=DustRegListPointerContainer.GetFirst();
	for(DustRegList *a=GetFirst();a!=NULL;a=a->GetNext(),p=p->GetNext()){
		p->Point=a;
		if(Filter==_Judge_None || Filter==a->JudgeDustValue){
			p->Result=a->Calc(CurrentPattern,LayerNumb,XLen,YLen,AdaptedLayer);
		}
		else{
			p->Result=0;
		}
	}
	DustRegListPointerContainer.Sort();
	p=DustRegListPointerContainer.GetFirst();
	if(p!=NULL){
		return p;
	}
	return NULL;
}

DustRegList	*DustRegContainer::FindByID(int ID)
{
	for(DustRegList *r=GetFirst();r!=NULL;r=r->GetNext()){
		if(r->ID==ID){
			return r;
		}
	}
	return NULL;
}
DustRegListPointer	*DustRegContainer::FindPointer(int ID)
{
	for(DustRegListPointer *r=DustRegListPointerContainer.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->Point->ID==ID){
			return r;
		}
	}
	return NULL;

}