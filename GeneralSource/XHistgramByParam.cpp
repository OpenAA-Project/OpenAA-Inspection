#include "XTypeDef.h"
#include "XHistgramByParam.h"
#include "XGeneralFunc.h"
#include "XDataAlgorithm.h"
#include "XDataInLayer.h"
#include "swap.h"
#include "XNormal.h"
#include "XDataAlgorithmList.h"

ValueDimStockerBase	*ValueDimStockerBase::LoadNew(QIODevice *f)
{
	int	TypeCode;
	int	ParamID;
	ValueDimStockerBase	*Ret;

	if(::Load(f,TypeCode)==false)
		return NULL;
	if(::Load(f,ParamID)==false)
		return NULL;

	Ret=Create(TypeCode ,ParamID);

	if(Ret->Load(f)==false){
		delete	Ret;
		return NULL;
	}
	return Ret;
}

ValueDimStockerBase	*ValueDimStockerBase::Create(int TypeCode ,int ParamID)
{
	ValueDimStockerBase	*Ret;
	if(TypeCode==1){
		Ret=new HistgramByParamByte(ParamID);
	}
	else if(TypeCode==2){
		Ret=new HistgramByParamChar(ParamID);
	}
	else if(TypeCode==3){
		Ret=new HistgramByParamInt(ParamID);
	}
	else if(TypeCode==4){
		Ret=new HistgramByParamShort(ParamID);
	}
	else if(TypeCode==5){
		Ret=new HistgramByParamDouble(ParamID);
	}
	else if(TypeCode==11){
		Ret=new HistgramByBoundaryByte(ParamID);
	}
	else if(TypeCode==12){
		Ret=new HistgramByBoundaryChar(ParamID);
	}
	else if(TypeCode==13){
		Ret=new HistgramByBoundaryInt(ParamID);
	}
	else if(TypeCode==14){
		Ret=new HistgramByBoundaryShort(ParamID);
	}
	else if(TypeCode==15){
		Ret=new HistgramByBoundaryDouble(ParamID);
	}
	else{
		return NULL;
	}
	return Ret;
}
//==================================================================================

template<class T>
ValueDimStocker<T>::~ValueDimStocker<T>(void)
{
	Release();
}
template<class T>
void	ValueDimStocker<T>::Set(T n)
{
	Dim[CurrentPoint]=n;
	CurrentPoint++;
	CurrentCount++;
	if(CurrentPoint>=AllocatedCount){
		CurrentPoint=0;
	}
	if(CurrentCount>=AllocatedCount){
		CurrentCount=AllocatedCount;
	}
}

template<class T>
void	ValueDimStocker<T>::Release(void)
{
	delete	[]Dim;
}

template<class T>
double	ValueDimStocker<T>::GetAverage(void)
{
	double	D=0.0;
	for(int i=0;i<CurrentCount;i++){
		D+=(double)Dim[i];
	}
	if(CurrentCount!=0){
		return D/CurrentCount;
	}
	return 0;
}
template<class T>
double	ValueDimStocker<T>::GetDispersion(void)
{
	return 0.0;
}

template<class T>
bool	ValueDimStocker<T>::GetMinMax(T &MinData ,T &MaxData)
{
	int Count=GetCount();
	if(Count<=0)
		return false;
	T	*p=GetPointer();
	if(Count>0){
		MinData=p[0];
		MaxData=p[0];
	}
	for(int i=1;i<Count;i++){
		if(p[i]<MinData){
			MinData=p[i];
		}
		if(p[i]>MaxData){
			MaxData=p[i];
		}
	}
	return true;
}

template<class T>
bool	ValueDimStocker<T>::Save(QIODevice *f)
{
	if(::Save(f,AllocatedCount)==false){
		return false;
	}
	if(::Save(f,CurrentCount)==false){
		return false;
	}
	if(::Save(f,CurrentPoint)==false){
		return false;
	}
	if(f->write((const char *)Dim,AllocatedCount*sizeof(T))!=AllocatedCount*sizeof(T)){
		return false;
	}
	return true;
}

template<class T>
bool	ValueDimStocker<T>::Load(QIODevice *f)
{
	int32	iAllocatedCount;
	if(::Load(f,iAllocatedCount)==false){
		return false;
	}
	if(::Load(f,CurrentCount)==false){
		return false;
	}
	if(::Load(f,CurrentPoint)==false){
		return false;
	}
	if(iAllocatedCount!=AllocatedCount || Dim==NULL){
		if(Dim!=NULL){
			delete []Dim;
		}
		if(AllocatedCount>0){
			Dim=new T[AllocatedCount];
			AllocatedCount=iAllocatedCount;
		}
	}
	if(f->read((char *)Dim,AllocatedCount*sizeof(T))!=AllocatedCount*sizeof(T)){
		return false;
	}
	return true;
}

template<class T>
bool	ValueDimStocker<T>::AddTo(HistStepClass *Dest)
{
	T	tMin,tMax;
	GetMinMax(tMin,tMax);
	if(tMin<Dest->GetMinData() || Dest->GetMaxData()<tMax){
		return false;
	}
	for(int i=0;i<GetCount();i++){
		double	d=(double)Dim[i];
		Dest->AddCount(d,1);
	}
	return true;
}

template<class T>
bool	ValueDimStocker<T>::SaveText(QIODevice *f)
{
	QTextStream	Txt(f);
	for(int n=0;n<GetCount();n++){
		Txt<<QString::number((int)GetPointer()[n])<<QString("\r\n");
	}
	return true;
}

//====================================================================================
template<class T>
HistgramDimStocker<T>::~HistgramDimStocker<T>(void)
{
	Release();
}

template<class T>
void	HistgramDimStocker<T>::Set(T n)
{
	if(n<MinData)
		n=MinData;
	if(MaxData<n)
		n=MaxData;
	int	Index=(n-MinData)/Step;
	if(Dim!=NULL && Index<AllocatedCount){
		Dim[Index]++;
	}
}

template<class T>
void	HistgramDimStocker<T>::Clear(void)
{
	if(Dim!=NULL){
		for(int i=0;i<AllocatedCount;i++){
			Dim[i]=0;
		}
	}
}

template<class T>
int		HistgramDimStocker<T>::GetCount(void)
{
	int	Count=0;
	if(Dim!=NULL){
		for(int i=0;i<AllocatedCount;i++){
			Count+=Dim[i];
		}
	}
	return Count;
}

template<class T>
double	HistgramDimStocker<T>::GetAverage(void)
{
	double	A=0.0;
	int		N=0;
	if(Dim!=NULL){
		for(int i=0;i<AllocatedCount;i++){
			N+=Dim[i];
			A+=Dim[i]*i;
		}
	}
	if(N!=0){
		return A/N;
	}
	return 0;
}

/*
ƒ°(x-a)*(x-a)=ƒ°xx-2aƒ°x+aaN=ƒ°xx-aaN
a=ƒ°x/N
*/
template<class T>
double	HistgramDimStocker<T>::GetDispersion(void)
{
	double	AA=0.0;
	double	A=0.0;
	int		N=0;
	if(Dim!=NULL){
		for(int i=0;i<AllocatedCount;i++){
			N+=Dim[i];
			A+=Dim[i]*i;
			AA+=Dim[i]*i*i;
		}
	}
	if(N!=0){
		double	Avr=A/N;
		return AA/N-Avr*Avr;
	}
	return 0;
}

template<class T>
bool	HistgramDimStocker<T>::GetMinMax(T &_MinData ,T &_MaxData)
{
	_MinData=MinData;
	_MaxData=MaxData;
	return true;
}

template<class T>
bool	HistgramDimStocker<T>::Save(QIODevice *f)
{
	if(::Save(f,AllocatedCount)==false){
		return false;
	}
	if(::Save(f,MinData)==false){
		return false;
	}
	if(::Save(f,MaxData)==false){
		return false;
	}
	if(::Save(f,Step)==false){
		return false;
	}
	if(f->write((const char *)Dim,AllocatedCount*sizeof(uint))!=AllocatedCount*sizeof(uint)){
		return false;
	}
	return true;
}

template<class T>
bool	HistgramDimStocker<T>::Load(QIODevice *f)
{
	uint	iAllocatedCount;
	if(::Load(f,iAllocatedCount)==false){
		return false;
	}
	if(::Load(f,MinData)==false){
		return false;
	}
	if(::Load(f,MaxData)==false){
		return false;
	}
	if(::Load(f,Step)==false){
		return false;
	}
	if(iAllocatedCount!=AllocatedCount){
		if(Dim!=NULL){
			delete	[]Dim;
		}
		AllocatedCount=iAllocatedCount;
		if(AllocatedCount>0){
			Dim=new uint[AllocatedCount];
		}
	}
	if(f->read((char *)Dim,AllocatedCount*sizeof(uint))!=AllocatedCount*sizeof(uint)){
		return false;
	}
	return true;
}
	
template<class T>
void	HistgramDimStocker<T>::Release(void)
{
	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
		AllocatedCount=0;
	}
}

template<class T>
bool	HistgramDimStocker<T>::AddTo(HistStepClass *Dest)
{
	T	tMin,tMax;
	GetMinMax(tMin,tMax);
	if(tMin<Dest->GetMinData() || Dest->GetMaxData()<tMax){
		return false;
	}
	for(int i=0;i<AllocatedCount;i++){
		int	d=Dim[i];
		double	Index=i*Step+MinData;
		Dest->AddCount(Index,d);
	}
	return true;
}

template<class T>
bool	HistgramDimStocker<T>::SaveText(QIODevice *f)
{
	QTextStream	Txt(f);
	for(int n=0;n<GetCount();n++){
		Txt<<QString::number(n)<<QString("\t,\t")+QString::number((int)GetPointer()[n])<<QString("\r\n");
	}
	return true;
}

//====================================================================================
bool	HistgramByParamByte::GetMinMaxData(double &MinData ,double &MaxData)
{
	BYTE	tMin,tMax;
	if(GetMinMax(tMin,tMax)==false)
		return false;
	MinData=tMin;
	MaxData=tMax;
	return true;
}

bool	HistgramByParamChar::GetMinMaxData(double &MinData ,double &MaxData)
{
	char	tMin,tMax;
	if(GetMinMax(tMin,tMax)==false)
		return false;
	MinData=tMin;
	MaxData=tMax;
	return true;
}

bool	HistgramByParamInt::GetMinMaxData(double &MinData ,double &MaxData)
{
	int	tMin,tMax;
	if(GetMinMax(tMin,tMax)==false)
		return false;
	MinData=tMin;
	MaxData=tMax;
	return true;
}

bool	HistgramByParamShort::GetMinMaxData(double &MinData ,double &MaxData)
{
	short	tMin,tMax;
	if(GetMinMax(tMin,tMax)==false)
		return false;
	MinData=tMin;
	MaxData=tMax;
	return true;
}

bool	HistgramByParamDouble::GetMinMaxData(double &MinData ,double &MaxData)
{
	if(GetMinMax(MinData,MaxData)==false)
		return false;
	return true;
}

bool	HistgramByBoundaryByte::GetMinMaxData(double &MinData ,double &MaxData)
{
	BYTE	tMin,tMax;
	if(GetMinMax(tMin,tMax)==false)
		return false;
	MinData=tMin;
	MaxData=tMax;
	return true;
}

bool	HistgramByBoundaryChar::GetMinMaxData(double &MinData ,double &MaxData)
{
	char	tMin,tMax;
	if(GetMinMax(tMin,tMax)==false)
		return false;
	MinData=tMin;
	MaxData=tMax;
	return true;
}

bool	HistgramByBoundaryInt::GetMinMaxData(double &MinData ,double &MaxData)
{
	int	tMin,tMax;
	if(GetMinMax(tMin,tMax)==false)
		return false;
	MinData=tMin;
	MaxData=tMax;
	return true;
}

bool	HistgramByBoundaryShort::GetMinMaxData(double &MinData ,double &MaxData)
{
	short	tMin,tMax;
	if(GetMinMax(tMin,tMax)==false)
		return false;
	MinData=tMin;
	MaxData=tMax;
	return true;
}

bool	HistgramByBoundaryDouble::GetMinMaxData(double &MinData ,double &MaxData)
{
	if(GetMinMax(MinData,MaxData)==false)
		return false;
	return true;
}


bool	HistgramByParamDouble::SaveText(QIODevice *f)
{
	QTextStream	Txt(f);
	for(int n=0;n<HistgramByParamBase::GetCount();n++){
		Txt<<QString::number((double)(GetPointer()[n]))<<QString("\r\n");
	}
	return true;
}

bool	HistgramByBoundaryDouble::SaveText(QIODevice *f)
{
	QTextStream	Txt(f);
	for(int n=0;n<HistgramByParamBase::GetCount();n++){
		Txt<<QString::number(n)<<QString("\t,\t")+QString::number((double)(GetPointer()[n]))<<QString("\r\n");
	}
	return true;
}

HistgramByParamBase::~HistgramByParamBase(void)
{
	if(Base!=NULL){
		//delete	Base;	=this
		Base=NULL;
	}
}

ValueDimStockerBase	*HistgramByParamBase::CreateCopy(void)
{
	return ValueDimStockerBase::Create(Base->GetTypeCode(),Base->GetParamID());
}

//====================================================================================

HistgramInThreshold::HistgramInThreshold(AlgorithmItemRoot *item)
{
	Item=item;
}

void	HistgramInThreshold::RegistByte	(const QString &Name ,int id)
{
	if(Item!=NULL && Item->GetParentBase()!=NULL){
		if(Item->GetParamGlobal()->MakeHistgramData==true){
			Item->GetParentBase()->RegistHistgram(Item,Name,id);
			HistgramByParamByte	*W=new HistgramByParamByte(id);
			AppendList(W);
		}
	}
}
void	HistgramInThreshold::RegistChar	(const QString &Name ,int id)
{
	if(Item!=NULL && Item->GetParentBase()!=NULL){
		if(Item->GetParamGlobal()->MakeHistgramData==true){
			Item->GetParentBase()->RegistHistgram(Item,Name,id);
			HistgramByParamChar	*W=new HistgramByParamChar(id);
			AppendList(W);
		}
	}
}
void	HistgramInThreshold::RegistShort	(const QString &Name ,int id)
{
	if(Item!=NULL && Item->GetParentBase()!=NULL){
		if(Item->GetParamGlobal()->MakeHistgramData==true){
			Item->GetParentBase()->RegistHistgram(Item,Name,id);
			HistgramByParamShort	*W=new HistgramByParamShort(id);
			AppendList(W);
		}
	}
}
void	HistgramInThreshold::RegistInt	(const QString &Name ,int id)
{
	if(Item!=NULL && Item->GetParentBase()!=NULL){
		if(Item->GetParamGlobal()->MakeHistgramData==true){
			Item->GetParentBase()->RegistHistgram(Item,Name,id);
			HistgramByParamInt	*W=new HistgramByParamInt(id);
			AppendList(W);
		}
	}
}
void	HistgramInThreshold::RegistDouble(const QString &Name ,int id)
{
	if(Item!=NULL && Item->GetParentBase()!=NULL){
		if(Item->GetParamGlobal()->MakeHistgramData==true){
			Item->GetParentBase()->RegistHistgram(Item,Name,id);
			HistgramByParamDouble	*W=new HistgramByParamDouble(id);
			AppendList(W);
		}
	}
}
void	HistgramInThreshold::RegistBoundaryByte	(const QString &Name ,int id ,BYTE mindata ,BYTE maxdata)
{
	if(Item!=NULL && Item->GetParentBase()!=NULL){
		if(Item->GetParamGlobal()->MakeHistgramData==true){
			Item->GetParentBase()->RegistHistgram(Item,Name,id);
			HistgramByBoundaryByte	*W=new HistgramByBoundaryByte(id,mindata ,maxdata);
			AppendList(W);
		}
	}
}
void	HistgramInThreshold::RegistBoundaryChar	(const QString &Name ,int id ,char mindata ,char maxdata)
{
	if(Item!=NULL && Item->GetParentBase()!=NULL){
		if(Item->GetParamGlobal()->MakeHistgramData==true){
			Item->GetParentBase()->RegistHistgram(Item,Name,id);
			HistgramByBoundaryChar	*W=new HistgramByBoundaryChar(id,mindata ,maxdata);
			AppendList(W);
		}
	}
}
void	HistgramInThreshold::RegistBoundaryShort	(const QString &Name ,int id ,short mindata ,short maxdata)
{
	if(Item!=NULL && Item->GetParentBase()!=NULL){
		if(Item->GetParamGlobal()->MakeHistgramData==true){
			Item->GetParentBase()->RegistHistgram(Item,Name,id);
			HistgramByBoundaryShort	*W=new HistgramByBoundaryShort(id,mindata ,maxdata);
			AppendList(W);
		}
	}
}

void	HistgramInThreshold::RegistBoundaryInt	(const QString &Name ,int id ,int mindata ,int maxdata)
{
	if(Item!=NULL && Item->GetParentBase()!=NULL){
		if(Item->GetParamGlobal()->MakeHistgramData==true){
			Item->GetParentBase()->RegistHistgram(Item,Name,id);
			HistgramByBoundaryInt	*W=new HistgramByBoundaryInt(id,mindata ,maxdata);
			AppendList(W);
		}
	}
}
void	HistgramInThreshold::RegistBoundaryDouble(const QString &Name ,int id ,double mindata ,double maxdata,double step)
{
	if(Item!=NULL && Item->GetParentBase()!=NULL){
		if(Item->GetParamGlobal()->MakeHistgramData==true){
			Item->GetParentBase()->RegistHistgram(Item,Name,id);
			HistgramByBoundaryDouble	*W=new HistgramByBoundaryDouble(id,mindata ,maxdata,step);
			AppendList(W);
		}
	}
}

HistgramByParamBase	*HistgramInThreshold::GetHistgramBase(int id)
{
	for(HistgramByParamBase *b=GetFirst();b!=NULL;b=b->GetNext()){
		if(b->GetID()==id){
			return b;
		}
	}
	return NULL;
}

void	HistgramInThreshold::AddHist(int id ,BYTE data)
{
	HistgramByParamBase	*a=GetHistgramBase(id);
	if(a!=NULL){
		a->Set((int)data);
	}
}

void	HistgramInThreshold::AddHist(int id ,char data)
{
	HistgramByParamBase	*a=GetHistgramBase(id);
	if(a!=NULL){
		a->Set((int)data);
	}
}

void	HistgramInThreshold::AddHist(int id ,int  data)
{
	HistgramByParamBase	*a=GetHistgramBase(id);
	if(a!=NULL){
		a->Set((int)data);
	}
}

void	HistgramInThreshold::AddHist(int id ,short data)
{
	HistgramByParamBase	*a=GetHistgramBase(id);
	if(a!=NULL){
		a->Set((int)data);
	}
}

void	HistgramInThreshold::AddHist(int id ,double data)
{
	HistgramByParamBase	*a=GetHistgramBase(id);
	if(a!=NULL){
		a->Set(data);
	}
}

void	HistgramInThreshold::EnumHistgram(IntList &RetIDLists)
{
	RetIDLists.RemoveAll();
	for(HistgramByParamBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		RetIDLists.Add(a->GetID());
	}
}

void	HistgramInThreshold::Copy(const HistgramInThreshold &src)
{
	RemoveAll();
	for(HistgramByParamBase *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		HistgramByParamBase	*b=a->Clone();
		AppendList(b);
	}
}

bool	HistgramInThreshold::SaveHistgram(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(HistgramByParamBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(::Save(f,a->GetTypeCode())==false){
			return false;
		}
		if(::Save(f,a->GetParamID())==false){
			return false;
		}

		if(a->SaveHistgram(f)==false){
			return false;
		}
	}
	return true;
}

bool	HistgramInThreshold::LoadHistgram(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ValueDimStockerBase	*c=ValueDimStockerBase::LoadNew(f);
		if(c==NULL){
			return false;
		}
		HistgramByParamBase	*d=dynamic_cast<HistgramByParamBase *>(c);
		if(d==NULL){
			return false;
		}
		AppendList(d);
	}
	return true;
}

void	HistgramInThreshold::ClearHistgram(void)
{
	for(HistgramByParamBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Clear();
	}
}

//====================================================================================

HistStepClass::HistStepClass(void)
{
	HistData=NULL;
	MinData	=0.0;
	MaxData	=0.0;
	Step	=0.0;
	AllocatedNumb=0;
}
HistStepClass::~HistStepClass(void)
{
	if(HistData!=NULL){
		delete	[]HistData;
		HistData=NULL;
	}
	AllocatedNumb=0;
}

void	HistStepClass::Create(double mindata ,double maxdata ,double step)
{
	int	iAllocatedNumb=ceil(maxdata-mindata)+1;
	if(AllocatedNumb!=NULL){
		iAllocatedNumb=ceil(max(MaxData,maxdata)-min(MinData,mindata))+1;
	}
	else{
		MinData=mindata;
		MaxData=maxdata;
	}
	if(iAllocatedNumb>AllocatedNumb){
		int *iHistData=new int[iAllocatedNumb];
		for(int i=0;i<iAllocatedNumb;i++){
			iHistData[i]=0;
		}
		if(HistData!=NULL){
			double	imin=min(MinData,mindata);
			for(int i=0;i<AllocatedNumb;i++){
				iHistData[i+(int)(MinData-imin)]=HistData[i];
			}
			//_heapchk();
			delete	[]HistData;
		}
		HistData=iHistData;
		AllocatedNumb=iAllocatedNumb;
		MinData=min(MinData,mindata);
		MaxData=max(MaxData,maxdata);
	}
	//else{
	//	AllocatedNumb=iAllocatedNumb;
	//	int *HistData=new int[AllocatedNumb];
	//	Clear();
	//}
	Step=step;	
}

/*
bool	HistStepClass::Add(HistgramByParamBase *src)
{
	if(HistData==NULL){
		return false;
	}
	double	tMin,tMax;
	src->GetMinMaxData(tMin,tMax);
	if(tMin<MinData || MaxData<tMax){
		return false;
	}
	for(int i=0;i<src->GetCount();i++){
		double	d=src->GetData(i);
		int	Index=(d-MinData)/Step;
		if(Index<0 || AllocatedNumb<=Index){
			return false;
		}
		HistData[Index]++;
	}
	return true;
}
*/

void	HistStepClass::Clear(void)
{
	if(HistData!=NULL){
		for(int i=0;i<AllocatedNumb;i++){
			HistData[i]=0;
		}
	}
}
HistStepClass	&HistStepClass::operator=(const HistStepClass &src)
{
	if(this!=&src){
		MinData			=src.MinData;
		MaxData			=src.MaxData;
		Step			=src.Step;
		AllocatedNumb	=src.AllocatedNumb;
		if(HistData!=NULL){
			delete	[]HistData;
		}
		if(AllocatedNumb>0){
			HistData=new int[AllocatedNumb];
		}
		for(int i=0;i<AllocatedNumb;i++){
			HistData[i]=src.HistData[i];
		}
	}
	return *this;
}
HistStepClass	&HistStepClass::operator+=(const HistStepClass &src)
{
	if(Step==0.0 || src.MinData<MinData || MaxData<src.MaxData){
		double	pMinData=min(MinData,src.MinData);
		double	pMaxData=max(MaxData,src.MaxData);
		double	pStep=max(Step,src.Step);
		HistStepClass	Tmp;
		Tmp.Create(pMinData,pMaxData,pStep);
		int	Offset=floor((MinData-pMinData)/pStep);
		for(int i=0;i<AllocatedNumb;i++){
			Tmp.HistData[i+Offset]=HistData[i];
		}
		Tmp+=src;
		operator=(Tmp);
		return *this;
	}

	int	Offset=floor((src.MinData-MinData)/Step);
	for(int i=0;i<src.AllocatedNumb;i++){
		HistData[i+Offset]+=src.HistData[i];
	}
	return *this;
}

void	HistStepClass::AddCount(double value ,int Counter)
{
	int	Index=(value-MinData)/Step;
	if(0<=Index && Index<AllocatedNumb){
		HistData[Index]+=Counter;
	}
}

int		HistStepClass::GetTotalCount(void)
{
	int		N=0;
	for(int i=0;i<AllocatedNumb;i++){
		N+=HistData[i];
	}
	return N;
}

double	HistStepClass::GetAverage(void)
{
	double	D=0;
	int		N=0;
	for(int i=0;i<AllocatedNumb;i++){
		D+=HistData[i]*i;
		N+=HistData[i];
	}
	if(N>0){
		return D/N+MinData;
	}
	return 0;
}

double	HistStepClass::GetDispersion(double Avr)
{
	if(Avr<=-99999999.0){
		Avr=GetAverage();
	}
	double	D=0;
	int		N=0;
	for(int i=0;i<AllocatedNumb;i++){
		D+=HistData[i]*(i-(Avr-MinData))*(i-(Avr-MinData));
		N+=HistData[i];
	}
	if(N>0){
		return Step*Step*D/N;
	}
	return 0;
}

bool	HistStepClass::GetAverageByTable(double AdoptedRate ,double &Avr , double &VAdd)
{
	double	N=0;
	for(int i=0;i<AllocatedNumb;i++){
		N+=HistData[i];
	}
	int	AwayCount=N*(1.0-AdoptedRate)/2.0;
	int	AwayCountL=AwayCount;
	int	AwayCountH=AwayCount;

	double	Added=0;
	int	AddedCount=0;

	int		IndexL=AllocatedNumb;
	for(int i=0;i<AllocatedNumb;i++){
		if(AwayCountL>HistData[i]){
			AwayCountL-=HistData[i];
		}
		else{
			Added+=(HistData[i]-AwayCountL)*i;
			AddedCount+=HistData[i]-AwayCountL;
			IndexL=i+1;
			break;
		}
	}
	int	IndexH=0;
	for(int i=AllocatedNumb-1;i>=IndexL;i--){
		if(AwayCountH>HistData[i]){
			AwayCountH-=HistData[i];
		}
		else{
			Added+=(HistData[i]-AwayCountH)*i;
			AddedCount+=HistData[i]-AwayCountH;
			IndexH=i-1;
			break;
		}
	}
	for(int i=IndexL;i<IndexH;i++){
		Added+=HistData[i]*i;
		AddedCount+=HistData[i];
	}
	if(AddedCount>0){
		Avr=Added/(double)AddedCount;

		VAdd=(IndexL-1-Avr)*(IndexL-1-Avr)*(HistData[IndexL-1]-AwayCountL)
			+(IndexH+1-Avr)*(IndexH+1-Avr)*(HistData[IndexH+1]-AwayCountH);

		for(int i=IndexL;i<IndexH;i++){
			VAdd+=HistData[i]*(i-Avr)*(i-Avr);
		}
		VAdd/=AddedCount;
		VAdd=sqrt(VAdd);

		Avr+=MinData;
		return true;
	}
	return false;
}
double	HistStepClass::RealPercentage(double ThresholdL,double ThresholdH)
{
	if(ThresholdL>ThresholdH)
		swap(ThresholdL,ThresholdH);

	if(ThresholdL<GetMinData())
		ThresholdL=GetMinData();
	if(ThresholdH>GetMaxData())
		ThresholdH=GetMaxData();

	double	IndexL=(ThresholdL-GetMinData())/Step;
	double	IndexH=(ThresholdH-GetMinData())/Step;

	int	IndexIL=floor(IndexL);
	int	IndexIH=floor(IndexH);

	double	D	= HistData[IndexIL]*(1.0-(IndexL-IndexIL));
			D	+=HistData[IndexIH]*(IndexH-IndexIH);
	for(int i=IndexIL+1;i<IndexIH;i++){
		D+=HistData[i];
	}
	int	N=GetTotalCount();
	if(N==0){
		return 0.0;
	}
	return D/N;
}

double	HistStepClass::IdealPercentage(double ThresholdL,double ThresholdH)
{
	double	Avr=GetAverage();
	double	Dis=sqrt(GetDispersion(Avr));

	//NormalDistribution	D(Avr,sqrt(Dis));
	//return D.p(ThresholdL,ThresholdH);

	double	r1=qnorm((ThresholdL-Avr)/Dis);
	double	r2=qnorm((ThresholdH-Avr)/Dis);
	return r2-r1;
}

void	HistStepClass::GetRealThreshold(double SpareRateL,double SpareRateH 
										,double &ThresholdL,double &ThresholdH)
{
	ThresholdL=GetMinData();
	ThresholdH=GetMinData()+AllocatedNumb*Step;

	int	N=GetTotalCount();
	double	SpareL=SpareRateL*N;
	double	D=0;
	for(int i=0;i<AllocatedNumb;i++){
		if(D+HistData[i]>=SpareL){
			double	Diff=D+HistData[i]-SpareL;
			if(HistData[i]>0){
				ThresholdL=GetMinData()+(i+(Diff/HistData[i]))*Step;
			}
			else{
				ThresholdL=GetMinData()+i*Step;
			}
			break;
		}
		D+=HistData[i];
	}
	double	SpareH=SpareRateH*N;
	D=0;
	for(int i=AllocatedNumb-1;i>=0;i--){
		if(D+HistData[i]>=SpareH){
			double	Diff=D+HistData[i]-SpareH;
			if(HistData[i]>0){
				ThresholdH=GetMinData()+(i+(1.0-Diff/HistData[i]))*Step;
			}
			else{
				ThresholdH=GetMinData()+i*Step;
			}
			break;
		}
		D+=HistData[i];
	}
}

void	HistStepClass::GetIdealThreshold(double RateL,double RateH ,double &ThresholdL,double &ThresholdH)
{
	double	Avr=GetAverage();
	double	Dis=sqrt(GetDispersion(Avr));

	ThresholdL	=pnorm(0.5-RateL)*Dis+Avr;
	ThresholdH	=pnorm(0.5+RateH)*Dis+Avr;
}

bool	HistStepClass::Save(QIODevice *f)
{
	if(::Save(f,MinData)==false){
		return false;
	}
	if(::Save(f,MaxData)==false){
		return false;
	}
	if(::Save(f,Step)==false){
		return false;
	}
	if(::Save(f,AllocatedNumb)==false){
		return false;
	}
	bool	HistDataNull;
	if(HistData==NULL)
		HistDataNull=true;
	else
		HistDataNull=false;
	if(::Save(f,HistDataNull)==false){
		return false;
	}
	if(HistDataNull==false){
		if(f->write((const char *)HistData,AllocatedNumb*sizeof(int))!=AllocatedNumb*sizeof(int)){
			return false;
		}
	}
	return true;
}

bool	HistStepClass::Load(QIODevice *f)
{
	if(::Load(f,MinData)==false){
		return false;
	}
	if(::Load(f,MaxData)==false){
		return false;
	}
	if(::Load(f,Step)==false){
		return false;
	}
	if(::Load(f,AllocatedNumb)==false){
		return false;
	}
	if(HistData!=NULL){
		delete	[]HistData;
		HistData=NULL;
	}
	bool	HistDataNull;
	if(::Load(f,HistDataNull)==false){
		return false;
	}
	if(HistDataNull==false){
		if(AllocatedNumb>0){
			HistData=new int[AllocatedNumb];
		}
		if(f->read((char *)HistData,AllocatedNumb*sizeof(int))!=AllocatedNumb*sizeof(int)){
			return false;
		}
	}
	return true;
}
//====================================================================================

bool	HistgramTypeListInAlgo::Save(QIODevice *f)
{
	if(::Save(f,HistID)==false)
		return false;
	if(::Save(f,HistName)==false)
		return false;
	return true;
}

bool	HistgramTypeListInAlgo::Load(QIODevice *f)
{
	if(::Load(f,HistID)==false)
		return false;
	if(::Load(f,HistName)==false)
		return false;
	return true;
}

HistgramTypeListInAlgo	&HistgramTypeListInAlgo::operator=(const HistgramTypeListInAlgo &src)
{
	HistID		=src.HistID;
	HistName	=src.HistName;
	return *this;
}

bool				HistgramTypeListInAlgo::operator==(const HistgramTypeListInAlgo &src)	const
{
	if(HistID	!=src.HistID)
		return false;
	if(HistName	!=src.HistName)
		return false;
	return true;
}


HistgramTypeListInAlgoContainer	&HistgramTypeListInAlgoContainer::operator=(const HistgramTypeListInAlgoContainer &src)
{
	RemoveAll();
	for(HistgramTypeListInAlgo *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		HistgramTypeListInAlgo *b=new HistgramTypeListInAlgo();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

bool	HistgramTypeListInAlgoContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(HistgramTypeListInAlgo *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

bool	HistgramTypeListInAlgoContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		HistgramTypeListInAlgo	*a=new HistgramTypeListInAlgo();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}

ParamAutoThreshold::ParamAutoThreshold(void)
{
	ModeOneWork		=true;
	ModeMultiWork	=true;
	AdoptRate		=0.9;
	SigmaMultiply	=3.0;
}
bool	ParamAutoThreshold::Save(QIODevice *f)
{
	if(::Save(f,ModeOneWork)==false)
		return false;
	if(::Save(f,ModeMultiWork)==false)
		return false;
	if(::Save(f,AdoptRate)==false)
		return false;
	if(::Save(f,SigmaMultiply)==false)
		return false;
	return true;
}
bool	ParamAutoThreshold::Load(QIODevice *f)
{
	if(::Load(f,ModeOneWork)==false)
		return false;
	if(::Load(f,ModeMultiWork)==false)
		return false;
	if(::Load(f,AdoptRate)==false)
		return false;
	if(::Load(f,SigmaMultiply)==false)
		return false;
	return true;
}

bool	HistgramInBinder::ExecuteAutoThreshold(ParamAutoThreshold &executer)
{
	AlgorithmItemPointerListContainerByLibContainer Items;
	GenerateItemListForAutoThreshold(Items);
	if(Items.GetCount()!=0){
		bool	Ret=ExecuteAutoThresholdByAlgo(Items ,executer);
		return Ret;
	}
	return true;
}
ParamAutoThreshold *HistgramInBinder::CreateParamAutoThreshold(void)
{
	return new ParamAutoThreshold();
}

//====================================================================================
GUICmdReqEnumHistgram::GUICmdReqEnumHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqEnumHistgram::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}

bool	GUICmdReqEnumHistgram::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

void	GUICmdReqEnumHistgram::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckEnumHistgram	*SendBack=GetSendBack(GUICmdAckEnumHistgram,GetLayersBase(),"ANY","ANY" ,localPage);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*APage=Ph->GetPageData(localPage);
			if(APage!=NULL){
				AlgorithmInLayerRoot	*ALayer=APage->GetLayerData(Layer);
				if(ALayer!=NULL){
					AlgorithmItemRoot	*AItem=ALayer->SearchIDItem(ItemID);
					if(AItem!=NULL){
						IntList	IDList;
						AItem->GetThresholdBaseWritable()->EnumHistgram(IDList);
						for(IntClass *a=IDList.GetFirst();a!=NULL;a=a->GetNext()){
							HistgramTypeListInAlgo	*k=new HistgramTypeListInAlgo();
							k->HistID	=a->GetValue();
							k->HistName	=ABase->GetHistgramName(a->GetValue());
							SendBack->RetLists.AppendList(k);
						}
					}
				}
				else{
					AlgorithmItemRoot	*AItem=APage->SearchIDItem(ItemID);
					if(AItem!=NULL){
						IntList	IDList;
						AItem->GetThresholdBaseWritable()->EnumHistgram(IDList);
						for(IntClass *a=IDList.GetFirst();a!=NULL;a=a->GetNext()){
							HistgramTypeListInAlgo	*k=new HistgramTypeListInAlgo();
							k->HistID	=a->GetValue();
							k->HistName	=ABase->GetHistgramName(a->GetValue());
							SendBack->RetLists.AppendList(k);
						}
					}
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckEnumHistgram::GUICmdAckEnumHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckEnumHistgram::Load(QIODevice *f)
{
	if(RetLists.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAckEnumHistgram::Save(QIODevice *f)
{
	if(RetLists.Save(f)==false)
		return false;
	return true;
}


//====================================================================================

GUICmdReqHistgram::GUICmdReqHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqHistgram::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false){
		return false;
	}
	if(::Load(f,HistID)==false){
		return false;
	}
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqHistgram::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false){
		return false;
	}
	if(::Save(f,HistID)==false){
		return false;
	}
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	return true;
}

void	GUICmdReqHistgram::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckHistgram	*SendBack=GetSendBack(GUICmdAckHistgram,GetLayersBase(),"ANY","ANY" ,localPage);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*APage=Ph->GetPageData(localPage);
			if(APage!=NULL){
				AlgorithmInLayerRoot	*ALayer=APage->GetLayerData(Layer);
				if(ALayer!=NULL){
					AlgorithmItemRoot	*AItem=ALayer->SearchIDItem(ItemID);
					if(AItem!=NULL){
						HistgramByParamBase	*h=AItem->GetThresholdBaseWritable()->GetHistgramBase(HistID);
						if(h!=NULL && h->GetCount()>0){
							double	MinData ,MaxData;
							h->GetMinMaxData(MinData ,MaxData);
							if(MinData<=MaxData){
								SendBack->HistData.Create(MinData ,MaxData ,1.0);
								h->AddTo(&SendBack->HistData);
							}
						}
					}
				}
				else{
					AlgorithmItemRoot	*AItem=APage->SearchIDItem(ItemID);
					if(AItem!=NULL){
						HistgramByParamBase	*h=AItem->GetThresholdBaseWritable()->GetHistgramBase(HistID);
						if(h!=NULL && h->GetCount()>0){
							double	MinData ,MaxData;
							h->GetMinMaxData(MinData ,MaxData);
							if(MinData<=MaxData){
								SendBack->HistData.Create(MinData ,MaxData ,1.0);
								h->AddTo(&SendBack->HistData);
							}
						}
					}
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckHistgram::GUICmdAckHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}


bool	GUICmdAckHistgram::Load(QIODevice *f)
{
	if(HistData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckHistgram::Save(QIODevice *f)
{
	if(HistData.Save(f)==false)
		return false;
	return true;
}

//====================================================================================

GUICmdReqInfoForHistgram::GUICmdReqInfoForHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID	=-1;
	HistID	=-1;
	Phase	=-1;
	Layer	=-1;
}

bool	GUICmdReqInfoForHistgram::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false){
		return false;
	}
	if(::Load(f,HistID)==false){
		return false;
	}
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqInfoForHistgram::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false){
		return false;
	}
	if(::Save(f,HistID)==false){
		return false;
	}
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	return true;
}

void	GUICmdReqInfoForHistgram::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckInfoForHistgram	*SendBack=GetSendBack(GUICmdAckInfoForHistgram,GetLayersBase(),"ANY","ANY" ,localPage);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*APage=Ph->GetPageData(localPage);
			if(APage!=NULL){
				AlgorithmInLayerRoot	*ALayer=APage->GetLayerData(Layer);
				if(ALayer!=NULL){
					AlgorithmItemRoot	*AItem=ALayer->SearchIDItem(ItemID);
					if(AItem!=NULL){
						SendBack->LibID		=AItem->GetLibID();
						SendBack->HistName	=ABase->GetHistgramName(HistID);
					}
				}
				else{
					AlgorithmItemRoot	*AItem=APage->SearchIDItem(ItemID);
					if(AItem!=NULL){
						SendBack->LibID		=AItem->GetLibID();
						SendBack->HistName	=ABase->GetHistgramName(HistID);
					}
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckInfoForHistgram::GUICmdAckInfoForHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckInfoForHistgram::Load(QIODevice *f)
{
	if(::Load(f,HistName)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}
	return true;
}
bool	GUICmdAckInfoForHistgram::Save(QIODevice *f)
{
	if(::Save(f,HistName)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	return true;
}

//====================================================================================

GUICmdReqInfoForHistDirect::GUICmdReqInfoForHistDirect(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqInfoForHistDirect::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,ItemID)==false){
		return false;
	}
	if(::Load(f,HistID)==false){
		return false;
	}
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	return true;
}

bool	GUICmdReqInfoForHistDirect::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,ItemID)==false){
		return false;
	}
	if(::Save(f,HistID)==false){
		return false;
	}
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	return true;
}

void	GUICmdReqInfoForHistDirect::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckInfoForHistDirect	*SendBack=GetSendBack(GUICmdAckInfoForHistDirect,GetLayersBase(),"ANY","ANY" ,localPage);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*APage=Ph->GetPageData(localPage);
			if(APage!=NULL){
				AlgorithmInLayerRoot	*ALayer=APage->GetLayerData(Layer);
				if(ALayer!=NULL){
					AlgorithmItemRoot	*AItem=ALayer->SearchIDItem(ItemID);
					if(AItem!=NULL){
						HistgramByParamBase	*h=AItem->GetThresholdBaseWritable()->GetHistgramBase(HistID);
						if(h!=NULL){
							SendBack->Data=h->CreateCopy();
							QBuffer	Buff;
							Buff.open(QIODevice::ReadWrite);
							h->SaveHistgram(&Buff);
							Buff.seek(0);
							SendBack->Data->Load(&Buff);
						}
					}
				}
				else{
					AlgorithmItemRoot	*AItem=APage->SearchIDItem(ItemID);
					if(AItem!=NULL){
						HistgramByParamBase	*h=AItem->GetThresholdBaseWritable()->GetHistgramBase(HistID);
						if(h!=NULL){
							SendBack->Data=h->CreateCopy();
							QBuffer	Buff;
							Buff.open(QIODevice::ReadWrite);
							h->SaveHistgram(&Buff);
							Buff.seek(0);
							SendBack->Data->Load(&Buff);
						}
					}
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckInfoForHistDirect::GUICmdAckInfoForHistDirect(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Data=NULL;
}

bool	GUICmdAckInfoForHistDirect::Load(QIODevice *f)
{
	bool	B;
	if(::Load(f,B)==false)
		return false;
	if(B==true){
		int	TypeCode;
		int	ParamID	;
		if(::Load(f,TypeCode)==false)
			return false;
		if(::Load(f,ParamID)==false)
			return false;
	
		Data=ValueDimStockerBase::Create(TypeCode ,ParamID);
		if(Data==NULL){
			return false;
		}
		if(Data->Load(f)==false)
			return false;
	}
	else{
		Data=NULL;
	}
	return true;
}

bool	GUICmdAckInfoForHistDirect::Save(QIODevice *f)
{
	if(Data==NULL){
		bool	B=false;
		if(::Save(f,B)==false)
			return false;
	}
	else{
		bool	B=true;
		if(::Save(f,B)==false)
			return false;
	}
	if(Data!=NULL){
		int	TypeCode=Data->GetTypeCode();
		int	ParamID	=Data->GetParamID();
		if(::Save(f,TypeCode)==false)
			return false;
		if(::Save(f,ParamID)==false)
			return false;
		if(Data->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	GetAverageByTable(double Table[] ,int TableCount ,double AdoptedRate ,double &Avr , double &VAdd)
{
	double	N=0;
	for(int i=0;i<TableCount;i++){
		N+=Table[i];
	}
	int	AwayCount=N*(1.0-AdoptedRate)/2.0;
	int	AwayCountL=AwayCount;
	int	AwayCountH=AwayCount;

	double	Added=0;
	int	AddedCount=0;

	int		IndexL=TableCount;
	for(int i=0;i<TableCount;i++){
		if(AwayCountL>Table[i]){
			AwayCountL-=Table[i];
		}
		else{
			Added+=(Table[i]-AwayCountL)*i;
			AddedCount+=Table[i]-AwayCountL;
			IndexL=i+1;
			break;
		}
	}
	int	IndexH=0;
	for(int i=TableCount-1;i>=IndexL;i--){
		if(AwayCountH>Table[i]){
			AwayCountH-=Table[i];
		}
		else{
			Added+=(Table[i]-AwayCountH)*i;
			AddedCount+=Table[i]-AwayCountH;
			IndexH=i-1;
			break;
		}
	}
	for(int i=IndexL;i<IndexH;i++){
		Added+=Table[i]*i;
		AddedCount+=Table[i];
	}
	if(AddedCount>0){
		Avr=Added/(double)AddedCount;

		VAdd=(IndexL-1-Avr)*(IndexL-1-Avr)*(Table[IndexL-1]-AwayCountL)
			+(IndexH+1-Avr)*(IndexH+1-Avr)*(Table[IndexH+1]-AwayCountH);

		for(int i=IndexL;i<IndexH;i++){
			VAdd+=Table[i]*(i-Avr)*(i-Avr);
		}
		VAdd/=AddedCount;
		VAdd=sqrt(VAdd);
		return true;
	}
	return false;
}
//====================================================================================

GUICmdReqAlgorithmUsageLib::GUICmdReqAlgorithmUsageLib(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Phase	=-1;
	Layer	=-1;
}

bool	GUICmdReqAlgorithmUsageLib::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqAlgorithmUsageLib::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	return true;
}

void	GUICmdReqAlgorithmUsageLib::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlgorithmUsageLib	*SendBack=GetSendBack(GUICmdAckAlgorithmUsageLib,GetLayersBase(),"ANY","ANY" ,localPage);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*APage=Ph->GetPageData(localPage);
			if(APage!=NULL){
				AlgorithmInLayerRoot	*ALayer=APage->GetLayerData(Layer);
				if(ALayer!=NULL){
					ALayer->EnumLibID(SendBack->LibList);
				}
				else{
					APage->EnumLibID(SendBack->LibList);
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAlgorithmUsageLib::GUICmdAckAlgorithmUsageLib(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckAlgorithmUsageLib::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckAlgorithmUsageLib::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	return true;
}

//====================================================================================

GUICmdReqHistgramLib::GUICmdReqHistgramLib(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqHistgramLib::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,HistID)==false){
		return false;
	}
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqHistgramLib::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,HistID)==false){
		return false;
	}
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	return true;
}

void	GUICmdReqHistgramLib::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckHistgramLib	*SendBack=GetSendBack(GUICmdAckHistgramLib,GetLayersBase(),"ANY","ANY" ,localPage);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*APage=Ph->GetPageData(localPage);
			if(APage!=NULL){
				AlgorithmInLayerRoot	*ALayer=APage->GetLayerData(Layer);
				if(ALayer!=NULL){
					IntList LibIDs;
					LibIDs.Add(LibID);
					AlgorithmItemPointerListContainer ItemPointers;
					ALayer->EnumItemsByLib(LibIDs ,ItemPointers);
					int	R=0;
					for(AlgorithmItemPointerList *p=ItemPointers.GetFirst();p!=NULL;p=p->GetNext(),R++){
						if(R==720)
							R=721;
						AlgorithmItemRoot	*AItem=p->GetItem();
						HistgramByParamBase	*h=AItem->GetThresholdBaseWritable()->GetHistgramBase(HistID);
						if(h!=NULL && h->GetCount()>0){
							double	MinData ,MaxData;
							h->GetMinMaxData(MinData ,MaxData);
							if(MinData<=MaxData){
								SendBack->HistData.Create(MinData ,MaxData ,1.0);
								h->AddTo(&SendBack->HistData);
								//_heapchk();
							}
						}
					}
				}
				else{
					IntList LibIDs;
					LibIDs.Add(LibID);
					AlgorithmItemPointerListContainer ItemPointers;
					APage->EnumItemsByLib(LibIDs ,ItemPointers);
					for(AlgorithmItemPointerList *p=ItemPointers.GetFirst();p!=NULL;p=p->GetNext()){
						AlgorithmItemRoot	*AItem=p->GetItem();
						HistgramByParamBase	*h=AItem->GetThresholdBaseWritable()->GetHistgramBase(HistID);
						if(h!=NULL && h->GetCount()>0){
							double	MinData ,MaxData;
							h->GetMinMaxData(MinData ,MaxData);
							if(MinData<=MaxData){
								SendBack->HistData.Create(MinData ,MaxData ,1.0);
								h->AddTo(&SendBack->HistData);
							}
						}
					}
				}
			}
		}
		SendBack->HistName	=ABase->GetHistgramName(HistID);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckHistgramLib::GUICmdAckHistgramLib(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}


bool	GUICmdAckHistgramLib::Load(QIODevice *f)
{
	if(HistData.Load(f)==false)
		return false;
	if(::Load(f,HistName)==false){
		return false;
	}

	return true;
}
bool	GUICmdAckHistgramLib::Save(QIODevice *f)
{
	if(HistData.Save(f)==false)
		return false;
	if(::Save(f,HistName)==false){
		return false;
	}
	return true;
}

//====================================================================================

GUICmdReqSetThreshold::GUICmdReqSetThreshold(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSetThreshold::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,HistID)==false){
		return false;
	}
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,ThresholdA)==false){
		return false;
	}
	if(::Load(f,ThresholdB)==false){
		return false;
	}
	return true;
}

bool	GUICmdReqSetThreshold::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,HistID)==false){
		return false;
	}
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,ThresholdA)==false){
		return false;
	}
	if(::Save(f,ThresholdB)==false){
		return false;
	}
	return true;
}

void	GUICmdReqSetThreshold::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*APage=Ph->GetPageData(localPage);
			if(APage!=NULL){
				ParamAutoThreshold *H=APage->CreateParamAutoThreshold();
				H->DirectThreshold=true;
				H->LibID		=-1;
				H->HistID		=HistID;
				H->AdoptRate	=0;
				H->SigmaMultiply=0;
				H->ModeOneWork	=false;
				H->ModeMultiWork=false;
				H->ThresholdA	=ThresholdA;
				H->ThresholdB	=ThresholdB;

				AlgorithmInLayerRoot	*ALayer=APage->GetLayerData(Layer);
				if(ALayer!=NULL){
					IntList LibIDs;
					LibIDs.Add(LibID);
					AlgorithmItemPointerListContainer ItemPointers;
					ALayer->EnumItemsByLib(LibIDs ,ItemPointers);
					int	R=0;
					for(AlgorithmItemPointerList *p=ItemPointers.GetFirst();p!=NULL;p=p->GetNext(),R++){
						AlgorithmItemRoot	*AItem=p->GetItem();
						AItem->SetAutoThreshold(*H);
					}
				}
				else{
					IntList LibIDs;
					LibIDs.Add(LibID);
					AlgorithmItemPointerListContainer ItemPointers;
					APage->EnumItemsByLib(LibIDs ,ItemPointers);
					for(AlgorithmItemPointerList *p=ItemPointers.GetFirst();p!=NULL;p=p->GetNext()){
						AlgorithmItemRoot	*AItem=p->GetItem();
						AItem->SetAutoThreshold(*H);
					}
				}
				delete	H;
			}
		}
	}
}