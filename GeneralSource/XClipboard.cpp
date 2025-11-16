#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XFlexArea.h"


ClipboardAlgorithmItem::ClipboardAlgorithmItem(void)
{	
	Page=-1;
	Layer=-1;
	Vector=NULL;	
}

bool	ClipboardAlgorithmItem::Save(QIODevice *f)
{
	if(Area.Save(f)==false){
		return false;
	}
	if(::Save(f,ItemData)==false){
		return false;
	}
	if(::Save(f,ItemClassType)==false){
		return false;
	}
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(Vector==NULL){
		if(::Save(f,false)==false){
			return false;
		}
	}
	else{
		if(::Save(f,true)==false){
			return false;
		}
		int	id=Vector->GetID();
		if(::Save(f,id)==false){
			return false;
		}
		if(Vector->Save(f)==false){
			return false;
		}
	}

	return true;
}
bool	ClipboardAlgorithmItem::Load(QIODevice *f)
{
	if(Area.Load(f)==false){
		return false;
	}
	if(::Load(f,ItemData)==false){
		return false;
	}
	if(::Load(f,ItemClassType)==false){
		return false;
	}
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	bool	VectorMode;
	if(::Load(f,VectorMode)==false){
		return false;
	}
	if(VectorMode==true){
		int	id;
		if(::Load(f,id)==false){
			return false;
		}
		if(Vector!=NULL){
			delete	Vector;
		}
		Vector=VectorLineBase::Create(id);
		if(Vector==NULL){
			return false;
		}
		if(Vector->Load(f)==false){
			return false;
		}
	}

	return true;
}
bool	ClipboardAlgorithmItem::Draw(int dx,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &Col)
{
	bool	RetArea=Area.Draw(dx,dy ,&pnt ,Col.rgba()	,ZoomRate ,movx ,movy);
	bool	RetVector=false;
	if(Vector!=NULL){
		RetVector=Vector->DrawShift(dx,dy ,pnt ,Col.rgba(),ZoomRate ,movx ,movy);
	}
	if(RetArea==true || RetVector==true){
		return true;
	}
	return false;
}

ClipboardAlgorithmItem	&ClipboardAlgorithmItem::operator=(const ClipboardAlgorithmItem &src)
{
	if(this!=&src){
		Area			=src.Area;
		ItemData		=src.ItemData;
		ItemClassType	=src.ItemClassType;
		Page			=src.Page;
		Layer			=src.Layer;
		if(Vector!=NULL){
			delete	Vector;
			Vector=NULL;
		}
		if(src.Vector!=NULL){
			int	id=src.Vector->GetID();
			Vector=VectorLineBase::Create(id);
			*Vector=*src.Vector;
		}
	}
	return *this;
}

bool	ClipboardAlgorithm::Save(int localPage,QIODevice *f)
{
	QString DLLRoot;
	QString DLLName;
	if(Base->GetDLLName(DLLRoot ,DLLName)==true){
		if(::Save(f,DLLRoot)==false){
			return false;
		}
		if(::Save(f,DLLName)==false){
			return false;
		}
		int64	N=0;
		for(ClipboardAlgorithmItem *c=Items.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->Page==localPage){
				N++;
			}
		}
		if(::Save(f,N)==false){
			return false;
		}
		for(ClipboardAlgorithmItem *c=Items.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->Page==localPage){
				if(c->Save(f)==false){
					return false;
				}
			}
		}
		if(::Save(f,Remark)==false){
			return false;
		}
		return true;
	}
	return false;
}
bool	ClipboardAlgorithm::Load(int localPage,QIODevice *f)
{
	QString DLLRoot;
	QString DLLName;
	if(::Load(f,DLLRoot)==false){
		return false;
	}
	if(::Load(f,DLLName)==false){
		return false;
	}
	Base=LBase->GetAlgorithmBase(DLLRoot ,DLLName);
	int64	N;
	if(::Load(f,N)==false){
		return false;
	}
	if(localPage==0){
		Items.RemoveAll();
	}
	for(int i=0;i<(int)N;i++){
		ClipboardAlgorithmItem *c=new ClipboardAlgorithmItem();
		if(c->Load(f)==false){
			delete	c;
			return false;
		}
		Items.AppendList(c);
	}
	if(::Load(f,Remark)==false){
		return false;
	}
	return true;
}


bool	ClipboardAlgorithm::Save(QIODevice *f)
{
	QString DLLRoot;
	QString DLLName;
	if(Base->GetDLLName(DLLRoot ,DLLName)==true){
		if(::Save(f,DLLRoot)==false){
			return false;
		}
		if(::Save(f,DLLName)==false){
			return false;
		}
		int64	N=Items.GetCount();
		if(::Save(f,N)==false){
			return false;
		}
		for(ClipboardAlgorithmItem *c=Items.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->Save(f)==false){
				return false;
			}
		}
		if(::Save(f,Remark)==false){
			return false;
		}
		return true;
	}
	return false;
}
bool	ClipboardAlgorithm::Load(QIODevice *f)
{
	QString DLLRoot;
	QString DLLName;
	if(::Load(f,DLLRoot)==false){
		return false;
	}
	if(::Load(f,DLLName)==false){
		return false;
	}
	Base=LBase->GetAlgorithmBase(DLLRoot ,DLLName);
	int64	N;
	if(::Load(f,N)==false){
		return false;
	}
	Items.RemoveAll();
	for(int i=0;i<(int)N;i++){
		ClipboardAlgorithmItem *c=new ClipboardAlgorithmItem();
		if(c->Load(f)==false){
			delete	c;
			return false;
		}
		Items.AppendList(c);
	}
	if(::Load(f,Remark)==false){
		return false;
	}
	return true;
}
bool	ClipboardAlgorithm::Draw(int localPage ,int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &Col)
{
	bool	Ret=false;
	for(ClipboardAlgorithmItem *c=Items.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Page==localPage){
			if(c->Draw(dx,dy,pnt, movx ,movy ,ZoomRate ,Col)==true){
				Ret=true;
			}
		}
	}
	return Ret;
}
ClipboardAlgorithm	&ClipboardAlgorithm::operator=(ClipboardAlgorithm &src)
{
	LBase	=src.LBase;
	Base	=src.Base;
	Items.RemoveAll();
	for(ClipboardAlgorithmItem *a=src.Items.GetFirst();a!=NULL;a=a->GetNext()){
		ClipboardAlgorithmItem *b=new ClipboardAlgorithmItem();
		*b= *a;
		Items.AppendList(b);
	}
	CreatedTime	=src.CreatedTime;
	Remark	=src.Remark;

	return *this;
}

void	ClipboardAlgorithm::CopyInPages(ClipboardAlgorithm &src ,IntList &LocalPages)
{
	LBase	=src.LBase;
	Base	=src.Base;
	Items.RemoveAll();
	for(ClipboardAlgorithmItem *a=src.Items.GetFirst();a!=NULL;a=a->GetNext()){
		if(LocalPages.IsInclude(a->Page)==true){
			ClipboardAlgorithmItem *b=new ClipboardAlgorithmItem();
			*b= *a;
			Items.AppendList(b);
		}
	}
	CreatedTime	=src.CreatedTime;
	Remark	=src.Remark;
}

void	ClipboardAlgorithm::Absorb(ClipboardAlgorithm *From)
{
	ClipboardAlgorithmItem	*c;
	while((c=From->Items.GetFirst())!=NULL){
		From->Items.RemoveList(c);
		Items.AppendList(c);
	}
}

ClipboardList::~ClipboardList(void)
{
	ClipboardAlgorithm	*p;
	while((p=GetFirst())!=NULL){
		RemoveList(p);
	}
}

void	ClipboardList::AppendList(ClipboardAlgorithm *item ,bool EnableDup)
{
	if(GetNumber()>=5){
		ClipboardAlgorithm	*a=GetFirst();
		RemoveList(a);
		delete	a;
	}
	if(EnableDup==false){
		for(ClipboardAlgorithm *a=GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Base==item->Base){
				RemoveList(a);
				delete a;
				break;
			}
		}
	}
	NPListPack<ClipboardAlgorithm>::AppendList(item);
}
ClipboardAlgorithm	*ClipboardList::Find(XDateTime &CreatedTime)
{
	for(ClipboardAlgorithm *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetCreatedTime()==CreatedTime){
			return a;
		}
	}
	return NULL;
}

PageAndLayerList::PageAndLayerList(void)
{
	Page= -1;
	Layer= -1;
}
PageAndLayerList	&PageAndLayerList::operator=(PageAndLayerList &src)
{
	Page=src.Page;
	Layer=src.Layer;
	return *this;
}

bool	PageAndLayerList::Save(QIODevice *f)
{
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	return true;
}
bool	PageAndLayerList::Load(QIODevice *f)
{
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	return true;
}

PageAndLayerFlagList::PageAndLayerFlagList(void)
{
	Page	= -1;
	Layer	= -1;
	Done	=false;
}
PageAndLayerFlagList::PageAndLayerFlagList(int page ,int layer)
{
	Page	=page;
	Layer	=layer;
	Done	=false;
}

PageAndLayerFlagList	&PageAndLayerFlagList::operator=(PageAndLayerFlagList &src)
{
	Page	=src.Page;
	Layer	=src.Layer;
	Done	=src.Done;
	return *this;
}

bool	PageAndLayerFlagList::Save(QIODevice *f)
{
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,Done)==false){
		return false;
	}
	return true;
}
bool	PageAndLayerFlagList::Load(QIODevice *f)
{
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,Done)==false){
		return false;
	}
	return true;
}

PageAndLayerFlagListContainer	&PageAndLayerFlagListContainer::operator+=(PageAndLayerFlagListContainer &src)
{
	for(PageAndLayerFlagList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		PageAndLayerFlagList	*d=new PageAndLayerFlagList();
		*d= *s;
		AppendList(d);
	}
	return *this;
}

PasteListMatrix::PasteListMatrix(void)
{
	GlobalPage	=-1;
	XPos		=0;
	YPos		=0;
}

bool	PasteListMatrix::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,XPos)==false)
		return false;
	if(::Save(f,YPos)==false)
		return false;
	return true;
}

bool	PasteListMatrix::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,XPos)==false)
		return false;
	if(::Load(f,YPos)==false)
		return false;
	return true;
}
PasteListMatrix	&PasteListMatrix::operator=(PasteListMatrix &src)
{
	GlobalPage	=src.GlobalPage;
	Layers		=src.Layers;
	XPos		=src.XPos;
	YPos		=src.YPos;
	return *this;
}

bool	PasteListMatrixContainer::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(PasteListMatrix *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

bool	PasteListMatrixContainer::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		PasteListMatrix	*a=new PasteListMatrix();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}
	
bool	PasteListMatrixContainer::Save(QStringListListCSV &csv)
{
	csv.clear();
	int	Row=0;
	for(PasteListMatrix *a=GetFirst();a!=NULL;a=a->GetNext(),Row++){
		csv.Set(0,Row,QString::number(a->GlobalPage));
		csv.Set(1,Row,QString::number(a->XPos));
		csv.Set(2,Row,QString::number(a->YPos));
	}
	return true;
}

bool	PasteListMatrixContainer::Load(QStringListListCSV &csv)
{
	RemoveAll();
	for(int Row=0;Row<csv.GetRowCount();Row++){
		PasteListMatrix	*a=new PasteListMatrix();
		bool	ok;
		a->GlobalPage	=csv.Get(0,Row).toInt(&ok);
		if(ok==false)
			return false;
		a->XPos			=csv.Get(1,Row).toInt(&ok);
		if(ok==false)
			return false;
		a->YPos			=csv.Get(2,Row).toInt(&ok);
		if(ok==false)
			return false;
		AppendList(a);
	}
	return true;
}
PasteListMatrixContainer	&PasteListMatrixContainer::operator=(PasteListMatrixContainer &src)
{
	RemoveAll();
	for(PasteListMatrix *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		PasteListMatrix	*b=new PasteListMatrix();
		*b=*a;
		AppendList(b);
	}
	return *this;
}
