#include <cmath>
#include "stdlib.h"
#include <string.h>
#include <omp.h>
#include"XTypeDef.h"
#include <malloc.h>

void quickSort_parallel(void* array, int lenArray ,int datasize,int (*func)(const void *a ,const void *b), int numThreads=8);
void quickSort_single(void* array, int lenArray ,int datasize,int (*func)(const void *a ,const void *b));

void quickSort_parallel(void* array, int lenArray ,int datasize,int (*func)(const void *a ,const void *b), int numThreads);
void quickSort_parallel_internal(void *parray,void* endarray, int left, int right, int cutoff ,int datasize,int (*func)(const void *a ,const void *b));

void QSort(void* parray, int lenArray ,int datasize,int (*func)(const void *a ,const void *b) ,bool3 ThreadMode)
{
	if(lenArray<=0)
		return;
#if _OPENMP==200203
	quickSort_single(parray, lenArray, datasize, func);
#else
	if(ThreadMode==true3){
		quickSort_parallel(parray, lenArray ,datasize,func);
	}
	else if(ThreadMode==false3){
		quickSort_single(parray, lenArray ,datasize,func);
	}
	else if(lenArray>=50000){
		quickSort_parallel(parray, lenArray ,datasize,func);
	}
	else{
		quickSort_single(parray, lenArray ,datasize,func);
	}
#endif
}

#if _OPENMP!=200203
void quickSort_parallel(void* array,int lenArray ,int datasize,int (*func)(const void *a ,const void *b), int numThreads)
{

	int cutoff = 1000;
	void	*endarray=&((char *)array)[(lenArray-1)*datasize];

	#pragma omp parallel num_threads(numThreads)
	{	
		#pragma omp single nowait
		{
			quickSort_parallel_internal(array, endarray, 0, lenArray-1, cutoff,datasize,func);	
		}
	}	
}

void quickSort_parallel_internal(void *parray, void* endarray, int left, int right, int cutoff ,int datasize,int (*func)(const void *a ,const void *b)) 
{
	int i = left, j = right;
	char	pivotp[datasize];
	memcpy(pivotp,&(((char *)parray)[((left + right) / 2)*datasize]),datasize);

	//void *pivot = (void *)&(((char *)parray)[((left + right) / 2)*datasize]);
	{
	  	/* PARTITION PART */
		while (i <= j) {
			//while (parray[i] < pivot)
			while((&((char *)parray)[i*datasize]!=endarray) && func(&((char *)parray)[i*datasize],pivotp)<0)
				i++;
			//while (parray[j] > pivot)
			while(j>0 && func(&((char *)parray)[j*datasize],pivotp)>0)
				j--;
			if (i <= j) {
				char	tmp[datasize];
				memcpy(tmp,&((char *)parray)[i*datasize],datasize);
				memcpy(&((char *)parray)[i*datasize],&((char *)parray)[j*datasize],datasize);
				memcpy(&((char *)parray)[j*datasize],tmp,datasize);
				i++;
				j--;
			}
		}
	}

	if ( ((right-left)<cutoff) ){
		if (left < j && j<right){ quickSort_parallel_internal(parray,endarray, left, j, cutoff,datasize,func); }			
		if (left<i && i < right){ quickSort_parallel_internal(parray,endarray, i, right, cutoff,datasize,func); }
	}else{
		#pragma omp task 	
		{ 
			quickSort_parallel_internal(parray, endarray,left, j, cutoff,datasize,func); 
		}
		#pragma omp task 	
		{
			quickSort_parallel_internal(parray,endarray, i, right, cutoff,datasize,func); 
		}
	}
}
#endif

void quickSort_single_internal(void *parray,void* endarray, int left, int right, int cutoff ,int datasize,int (*func)(const void *a ,const void *b)) ;

void quickSort_single(void* array, int lenArray ,int datasize,int (*func)(const void *a ,const void *b))
{
	int cutoff = 1000;
	void	*endarray=&((char *)array)[(lenArray-1)*datasize];
	//quickSort_parallel_internal(array, 0, lenArray-1, cutoff,datasize,func);	
	quickSort_single_internal(array,endarray, 0, lenArray-1, cutoff,datasize,func);	
}

void quickSort_single_internal(void *parray, void* endarray, int left, int right, int cutoff ,int datasize,int (*func)(const void *a ,const void *b)) 
{
	int i = left, j = right;
#if _OPENMP!=200203
	char	pivotp[datasize];
#else
	char* pivotp = (char *)alloca(datasize);
#endif

	memcpy(pivotp,&(((char *)parray)[((left + right) / 2)*datasize]),datasize);
	{
	  	/* PARTITION PART */
		while (i <= j) {
			//while (parray[i] < pivot)
			while((&((char *)parray)[i*datasize]!=endarray) && func(&((char *)parray)[i*datasize],pivotp)<0)
				i++;
			//while (parray[j] > pivot)
			while(j>0 && func(&((char *)parray)[j*datasize],pivotp)>0)
				j--;
			if (i <= j) {
#if _OPENMP!=200203
				char	tmp[datasize];
#else
				char* tmp = (char*)alloca(datasize);
#endif
				memcpy(tmp,&((char *)parray)[i*datasize],datasize);
				memcpy(&((char *)parray)[i*datasize],&((char *)parray)[j*datasize],datasize);
				memcpy(&((char *)parray)[j*datasize],tmp,datasize);
				i++;
				j--;
			}
		}
	}

	if ( ((right-left)<cutoff) ){
		if (left < j && j<right){ quickSort_single_internal(parray, endarray,left, j, cutoff,datasize,func); }			
		if (left<i && i<right){ quickSort_single_internal(parray,endarray, i, right, cutoff,datasize,func); }
	}else{
		quickSort_single_internal(parray,endarray ,left, j, cutoff,datasize,func); 
		quickSort_single_internal(parray,endarray ,i, right, cutoff,datasize,func); 
	}
}

