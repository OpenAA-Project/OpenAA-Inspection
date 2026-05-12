#pragma once

#include "XGeneralFunc.h"


//====================================================================================
template<class T>
inline HistgramDimStocker<T>::~HistgramDimStocker<T>(void)
{
	Release();
}

template<class T>
inline	void	HistgramDimStocker<T>::Set(T n)
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
inline	void	HistgramDimStocker<T>::Clear(void)
{
	if(Dim!=NULL){
		for(int i=0;i<AllocatedCount;i++){
			Dim[i]=0;
		}
	}
}

template<class T>
inline int		HistgramDimStocker<T>::GetCount(void)
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
inline double	HistgramDimStocker<T>::GetAverage(void)
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

template<class T>
inline double	HistgramDimStocker<T>::GetDispersion(void)
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
inline bool	HistgramDimStocker<T>::GetDistribution(double &Average,double &Dispersion)
{
	double	D=0.0;
	double	DD=0.0;
	for(int i=0;i<AllocatedCount;i++){
		double	v = (double)Dim[i];
		D	+=v;
		DD	+= v*v;
	}
	if(AllocatedCount!=0){
		Average=D/AllocatedCount;
		Dispersion=DD/AllocatedCount - Average*Average;
		return true;
	}
	return false;
}

template<class T>
inline bool	HistgramDimStocker<T>::GetMinMax(T &_MinData ,T &_MaxData)
{
	_MinData=MinData;
	_MaxData=MaxData;
	return true;
}

template<class T>
inline bool	HistgramDimStocker<T>::Save(QIODevice *f)
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
inline bool	HistgramDimStocker<T>::Load(QIODevice *f)
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
inline void	HistgramDimStocker<T>::Release(void)
{
	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
		AllocatedCount=0;
	}
}

template<class T>
inline bool	HistgramDimStocker<T>::AddTo(HistStepClass *Dest)
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
inline bool	HistgramDimStocker<T>::SaveText(QIODevice *f)
{
	QTextStream	Txt(f);
	for(int n=0;n<GetCount();n++){
		Txt<<QString::number(n)<<QString("\t,\t")+QString::number((int)GetPointer()[n])<<QString("\r\n");
	}
	return true;
}

//====================================================================================

template<class T>
inline ValueDimStocker<T>::~ValueDimStocker<T>(void)
{
	Release();
}
template<class T>
inline void	ValueDimStocker<T>::Set(T n)
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
inline void	ValueDimStocker<T>::Release(void)
{
	delete	[]Dim;
}

template<class T>
inline double	ValueDimStocker<T>::GetAverage(void)
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
inline double	ValueDimStocker<T>::GetDispersion(void)
{
	double	D=0.0;
	double	DD=0.0;
	for(int i=0;i<CurrentCount;i++){
		double	v = (double)Dim[i];
		D	+=v;
		DD	+= v*v;
	}
	if(CurrentCount!=0){
		double	Avr=D/CurrentCount;
		return DD/CurrentCount - Avr*Avr;
	}
	return 0;
}
template<class T>
inline bool	ValueDimStocker<T>::GetDistribution(double &Average,double &Dispersion)
{
	double	D=0.0;
	double	DD=0.0;
	for(int i=0;i<CurrentCount;i++){
		double	v = (double)Dim[i];
		D	+=v;
		DD	+= v*v;
	}
	if(CurrentCount!=0){
		Average=D/CurrentCount;
		Dispersion=DD/CurrentCount - Average*Average;
		return true;
	}
	return false;
}

template<class T>
inline bool	ValueDimStocker<T>::GetMinMax(T &MinData ,T &MaxData)
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
inline bool	ValueDimStocker<T>::Save(QIODevice *f)
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
inline bool	ValueDimStocker<T>::Load(QIODevice *f)
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
inline bool	ValueDimStocker<T>::AddTo(HistStepClass *Dest)
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
inline bool	ValueDimStocker<T>::SaveText(QIODevice *f)
{
	QTextStream	Txt(f);
	for(int n=0;n<GetCount();n++){
		Txt<<QString::number((int)GetPointer()[n])<<QString("\r\n");
	}
	return true;
}

//====================================================================================