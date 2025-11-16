#include "XReferencePDF.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include <math.h>
#include <QColor>

inline	double	GetColorDistance(const QColor &C1, const QColor &C2)
{
	int	RL=C1.red()-C2.red();
	int	GL=C1.green()-C2.green();
	int	BL=C1.blue()-C2.blue();
	return sqrt((double)(RL*RL+GL*GL+BL*BL));
}


ReferencePDF::ReferencePDF(void)
{
	ID				=-1;
	ColorDim		=NULL;
	CountOfColorDim	=0;
}
ReferencePDF::ReferencePDF(const ReferencePDF &src)
{
	ID				=src.ID;
	PDFColor		=src.PDFColor;
	ReferenceName	=src.ReferenceName;
	CountOfColorDim	=src.CountOfColorDim;
	ColorDim		=new double[CountOfColorDim];
	for(int i=0;i<CountOfColorDim;i++){
		ColorDim[i]=src.ColorDim[i];
	}
}
ReferencePDF::~ReferencePDF(void)
{
	if(ColorDim!=NULL){
		delete	[]ColorDim;
		ColorDim=NULL;
	}
	CountOfColorDim	=0;
}
ReferencePDF	&ReferencePDF::operator=(const ReferencePDF &src)
{
	if(&src==this){
		return *this;
	}
	ID				=src.ID;
	PDFColor		=src.PDFColor;
	ReferenceName	=src.ReferenceName;
	if(CountOfColorDim!=src.CountOfColorDim){
		if(ColorDim!=NULL){
			delete	[]ColorDim;
			ColorDim=NULL;
		}
	}
	CountOfColorDim	=src.CountOfColorDim;
	if(ColorDim==NULL){
		ColorDim	=new double[CountOfColorDim];
	}
	for(int i=0;i<CountOfColorDim;i++){
		ColorDim[i]=src.ColorDim[i];
	}
	return *this;
}
bool	ReferencePDF::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,ReferenceName)==false)
		return false;
	if(::Save(f,PDFColor)==false)
		return false;
	if(::Save(f,CountOfColorDim)==false)
		return false;
	if(CountOfColorDim!=0){
		if(f->write((const char *)ColorDim,sizeof(ColorDim[0])*CountOfColorDim)!=sizeof(ColorDim[0])*CountOfColorDim)
			return false;
	}
	return true;
}
bool	ReferencePDF::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,ReferenceName)==false)
		return false;
	if(::Load(f,PDFColor)==false)
		return false;
	if(::Load(f,CountOfColorDim)==false)
		return false;
	if(ColorDim!=NULL){
		delete	[]ColorDim;
		ColorDim=NULL;
	}
	if(CountOfColorDim!=0){
		ColorDim	=new double[CountOfColorDim];
		if(f->read((char *)ColorDim,sizeof(ColorDim[0])*CountOfColorDim)!=sizeof(ColorDim[0])*CountOfColorDim)
			return false;
	}
	return true;
}
double	ReferencePDF::GetColorDistance(const QColor &Col)
{
	return ::GetColorDistance(PDFColor, Col);
}
//====================================================================
ReferencePDFContainer::ReferencePDFContainer(LayersBase *Base)
:ServiceForLayers(Base)
{
}

ReferencePDFContainer::ReferencePDFContainer(const ReferencePDFContainer &src)
	:ServiceForLayers(src.GetLayersBase())
{
	for(ReferencePDF *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ReferencePDF *d=new ReferencePDF();
		*d=*s;
		AppendList(d);
	}
}
ReferencePDF	*ReferencePDFContainer::Create(void)
{
	return new ReferencePDF();
}
ReferencePDFContainer	&ReferencePDFContainer::operator=(const ReferencePDFContainer &src)
{
	RemoveAll();
	for(ReferencePDF *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ReferencePDF *d=new ReferencePDF();
		*d=*s;
		AppendList(d);
	}
	return *this;
}

void	ReferencePDFContainer::AppendListItem(ReferencePDF *additem)
{
	RemoveList(additem);
	int	MaxID=0;
	for(ReferencePDF *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(MaxID<s->ID){
			MaxID=s->ID;
		}
	}
	additem->ID=MaxID+1;
	AppendList(additem);
}
	
bool	ReferencePDFContainer::LoadDefault(void)
{
    QString FileName=GetLayersBase()->GetUserPath()
                    +QDir::separator()
                    +GetDefaultFileName();
    QFile   File(FileName);
    if(File.open(QIODevice::ReadOnly)==true){
        return Load(&File);
    }
	return false;
}
bool	ReferencePDFContainer::SaveDefault(void)
{
    QString FileName=GetLayersBase()->GetUserPath()
                    +QDir::separator()
                    +GetDefaultFileName();
    QFile   File(FileName);
    if(File.open(QIODevice::WriteOnly)==true){
        return Save(&File);
    }
	return false;
}

ReferencePDF	*ReferencePDFContainer::FindClosed(const QColor &Col ,double ColerDistance)
{
	double	MinD=99999999;
	ReferencePDF	*Ret=NULL;
	for(ReferencePDF *s=GetFirst();s!=NULL;s=s->GetNext()){
		double	D=GetColorDistance(s->PDFColor,Col);
		if(MinD>D){
			MinD=D;
			Ret=s;
		}
	}
	if(MinD<=ColerDistance){
		return Ret;
	}
	return NULL;
}
ReferencePDF	*ReferencePDFContainer::FindClosed(const QColor &Col)
{
	double	MinD=99999999;
	ReferencePDF	*Ret=NULL;
	for(ReferencePDF *s=GetFirst();s!=NULL;s=s->GetNext()){
		double	D=GetColorDistance(s->PDFColor,Col);
		if(MinD>D){
			MinD=D;
			Ret=s;
		}
	}
	return Ret;
}

struct ReferencePDFDim
{
	ReferencePDF	*Point;
	double			Len;
};

int	ReferencePDFDimFunc(const void *a ,const void *b)
{
	struct ReferencePDFDim	*pa=(struct ReferencePDFDim *)a;
	struct ReferencePDFDim	*pb=(struct ReferencePDFDim *)b;
	if(pa->Len<pb->Len)
		return 1;
	if(pa->Len>pb->Len)
		return -1;
	return 0;
}

int	ReferencePDFContainer::FindClosed(const QColor &Col ,ReferencePDF **R1 ,ReferencePDF **R2 ,ReferencePDF **R3)
{
	struct ReferencePDFDim	*Dim=new struct ReferencePDFDim[GetCount()];
	int	n=0;
	for(ReferencePDF *s=GetFirst();s!=NULL;s=s->GetNext(),n++){
		Dim[n].Len=GetColorDistance(s->PDFColor,Col);
		Dim[n].Point=s;
	}
	QSort(Dim,n,sizeof(Dim[0]),ReferencePDFDimFunc);
	if(n>=3){
		*R1=Dim[0].Point;
		*R2=Dim[1].Point;
		*R3=Dim[2].Point;
		n=3;
	}
	else if(n==2){
		*R1=Dim[0].Point;
		*R2=Dim[1].Point;
		*R3=NULL;
	}
	else if(n==1){
		*R1=Dim[0].Point;
		*R2=NULL;
		*R3=NULL;
	}
	else if(n==0){
		*R1=NULL;
		*R2=NULL;
		*R3=NULL;
	}
	delete	[]Dim;
	return n;
}
void	ReferencePDFContainer::ReGenerateID(void)
{
	int	ID=0;
	for(ReferencePDF *s=GetFirst();s!=NULL;s=s->GetNext(),ID++){
		s->ID=ID;
	}
}
