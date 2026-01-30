/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



//      Finish Debugging
#include "XTypeDef.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "XBsearch.h"

void *EqualSearch(const void *key , const void *base , unsigned int numb , int width , int( *sortFunc)(const void *e1, const void *e2))
//      �����v�f���T��
//      ������ key �ɓ������f�[�^�����������Ƃ��A�ǂ̃f�[�^�����^�[�����邩�킩���Ȃ�
{
	char  *basemin;
	char  *bdata;
	int i;
	int	k;

	basemin = (char *) base;
	while (numb > 0){
		i = numb >> 1;
		bdata = basemin + i * width;
		k = (*sortFunc)(key, bdata);
		if (k == 0){
			return(bdata);
		}
		else if (k < 0){ //�L�[�̂ق����������Ƃ�
			numb = i;
		}
		else  {         //�L�[�̂ق����傫���Ƃ�
			basemin = bdata + width;
			numb -= i + 1;
		}
	}
	return(0);
}

void *EqualLeastSearch(const void *key , const void *base ,unsigned int numb , int width , int( *sortFunc)(const void *e1, const void *e2))
//      Bn-1 < Bn <= key �ƂȂ� Bn ���T��
//      key �ɓ��������̂����������Ƃ��A���̒��̍ł�base�ɋ߂����̂��Ԃ�
//      key �ɓ������f�[�^�͑��݂��Ă��Ȃ��Ă͂Ȃ��Ȃ�
//      ���݂��Ȃ��Ƃ� NULL ���Ԃ�
{
	char  *basemin;
	char  *bdata;
	int		i;
	int		k;

	basemin = (char *) base;
	while (numb > 0){
		i = numb >> 1;
		bdata = basemin + i * width;
		k = (*sortFunc)(key, bdata);
		if (k == 0){
			while (numb > 0){
				i = numb >> 1;
				bdata = basemin + i * width;
				k = (*sortFunc)(key, bdata);
				if (k <= 0){     //�L�[�̂ق����������Ƃ�
					numb = i;
				}
				else  {         //�L�[�̂ق����傫���Ƃ�
					basemin = bdata + width;
					numb -= i + 1;
					}
				}
			k = (*sortFunc)(key, bdata);
			if(k<0){
				bdata-=width;
			}
			else if(k>0){
				bdata+=width;
			}
			return(bdata);
		}
		else if (k < 0){ //�L�[�̂ق����������Ƃ�
			numb = i;
		}
		else  {         //�L�[�̂ق����傫���Ƃ�
			basemin = bdata + width;
			numb -= i + 1;
		}
	}
	return(0);
}

void *EqualGreatestSearch(const void *key , const void *base ,unsigned  int numb , int width , int( *sortFunc)(const void *e1, const void *e2))
//      key <= Bn < Bn+1 �ƂȂ� Bn ���T��
//      key �ɓ��������̂����������Ƃ��A���̒��̍ł�base���牓�����̂��Ԃ�
//      key �ɓ������f�[�^�͑��݂��Ă��Ȃ��Ă͂Ȃ��Ȃ�
//      ���݂��Ȃ��Ƃ� NULL ���Ԃ�
{
	char  *basemin;
	char	*bdata;
	int		i;
	int		k;

	basemin = (char *) base;
	while (numb > 0){
		i = numb >> 1;
		bdata = basemin + i * width;
		k = (*sortFunc)(key, bdata);
		if (k == 0){
			while (numb > 0){
				i = numb >> 1;
				bdata = basemin + i * width;
				k = (*sortFunc)(key, bdata);
				if (k < 0){     //�L�[�̂ق����������Ƃ�
					numb = i;
				}
				else  {         //�L�[�̂ق����傫���Ƃ�
					basemin = bdata + width;
					numb -= i + 1;
					}
				}
			k = (*sortFunc)(key, bdata);
			if(k<0){
				bdata-=width;
			}
			else if(k>0){
				bdata+=width;
			}
			return(bdata);
		}
		else if (k < 0){ //�L�[�̂ق����������Ƃ�
			numb = i;
		}
		else  {         //�L�[�̂ق����傫���Ƃ�
			basemin = bdata + width;
			numb -= i + 1;
		}
	}
	return(0);
}

void *LessSearch(const void *key , const void *base ,unsigned int numb , int width , int( *sortFunc)(const void *e1, const void *e2))
//      Bn-1 < Bn <= key �ƂȂ� Bn ���T��
//      key �ɓ��������̂����������Ƃ��A���̒��̍ł�base�ɋ߂����̂��Ԃ�
//      key �ɓ������f�[�^�͑��݂��Ȃ��Ă��悢
//      ���݂��Ȃ��Ƃ� NULL ���Ԃ�
{
	char  *basemin;
	char	*bdata;
	int		i;
	int		k;
	int     savenumb=numb;

	basemin = (char *) base;
	while (numb > 0){
		i = numb >> 1;
		bdata = basemin + i * width;
		k = (*sortFunc)(key, bdata);
		if (k == 0){
			while (numb > 0){
				i = numb >> 1;
				bdata = basemin + i * width;
				k = (*sortFunc)(key, bdata);
				if (k <= 0){     //�L�[�̂ق����������Ƃ�
					numb = i;
				}
				else  {         //�L�[�̂ق����傫���Ƃ�
					basemin = bdata + width;
					numb -= i + 1;
					}
				}
			k = (*sortFunc)(key, bdata);
			if(k<0){
				bdata-=width;
			}
			else if(k>0){
				bdata+=width;
			}
			return(bdata);
		}
		else if (k < 0){ //�L�[�̂ق����������Ƃ�
			numb = i;
		}
		else  {         //�L�[�̂ق����傫���Ƃ�
			basemin = bdata + width;
			numb -= i + 1;
		}
	}
	if(savenumb!=0){
		k = (*sortFunc)(key, bdata);
		if(k<0){
			if((char *)base<bdata){
				bdata-=width;
			}
			else{
				return(NULL);
			}
		}
		return(bdata);
	}
	return(NULL);
}
void *GreaterSearch(const void *key , const void *base , unsigned int numb , int width , int( *sortFunc)(const void *e1, const void *e2))
//      key <= Bn < Bn+1 �ƂȂ� Bn ���T��
//      key �ɓ��������̂����������Ƃ��A���̒��̍ł�base���牓�����̂��Ԃ�
//      key �ɓ������f�[�^�͑��݂��Ȃ��Ă��悢
//      ���݂��Ȃ��Ƃ� NULL ���Ԃ�
{
	char	*basemin;
	char	*bdata;
	int		i;
	int		k;
	int     savenumb=numb;

	basemin = (char *) base;
	while (numb > 0){
		i = numb >> 1;
		bdata = basemin + i * width;
		k = (*sortFunc)(key, bdata);
		if (k == 0){
			while (numb > 0){
				i = numb >> 1;
				bdata = basemin + i * width;
				k = (*sortFunc)(key, bdata);
				if (k < 0){      //�L�[�̂ق����������Ƃ�
					numb = i;
				}
				else  {         //�L�[�̂ق����傫���Ƃ�
					basemin = bdata + width;
					numb -= i + 1;
					}
				}
			k = (*sortFunc)(key, bdata);
			if(k<0){
				bdata-=width;
			}
			else if(k>0){
				bdata+=width;
			}
			return(bdata);
		}
		else if (k < 0){ //�L�[�̂ق����������Ƃ�
			numb = i;
		}
		else  {         //�L�[�̂ق����傫���Ƃ�
			basemin = bdata + width;
			numb -= i + 1;
		}
	}
	if(savenumb!=0){
		k = (*sortFunc)(key, bdata);
		if(k>0){
			bdata+=width;
			if((char *)base+savenumb*width<=bdata){
				return(NULL);
			}
		}
		return(bdata);
	}
	return(NULL);
}

/*


typedef struct  Pdata{
	int     x;
	}PPP;

PPP     QQ[1000];


int SearchExe(const void *e1, const void *e2)
{
	return( ((PPP *)e1)->x - ((PPP *)e2)->x);
}


#include<time.h>
#include<stdlib.h>

void main()
{

	PPP     *n;
	int     r;
	int     i;

	for(i=0;i<1000;i++){
		while((r=random(100))==80);
		QQ[i].x =r;
		}
	PPP     q;

	q.x=0;
	QSort(QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)EqualSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)EqualLeastSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)EqualGreatestSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)LessSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)GreaterSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);

	q.x=99;
	n=(PPP *)EqualSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)EqualLeastSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)EqualGreatestSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)LessSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)GreaterSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);

	q.x=80;
	n=(PPP *)EqualSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)EqualLeastSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)EqualGreatestSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)LessSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)GreaterSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);

	q.x=-1;
	n=(PPP *)EqualSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)EqualLeastSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)EqualGreatestSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)LessSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)GreaterSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);

	q.x=100;
	n=(PPP *)EqualSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)EqualLeastSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)EqualGreatestSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)LessSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);
	n=(PPP *)GreaterSearch(&q,QQ, sizeof(QQ)/sizeof(QQ[0]),sizeof(PPP),SearchExe);


	PPP     *n1;
	PPP     *n2;
	PPP     *n3;
	PPP     *n4;
	PPP     *n5;

	for(unsigned a=0;a<60000U;a++){
		srand(a);
		int Numb=random(1000);

		for(i=0;i<Numb;i++){
			QQ[i].x = random(100);
			}
		PPP     q;
		q.x=random(100);

		QSort(QQ, Numb,sizeof(PPP),SearchExe);

		n1=(PPP *)EqualSearch(&q,QQ, Numb,sizeof(PPP),SearchExe);
		if( (Numb!=0 && n1!=NULL && n1->x!=q.x)
		 || (Numb==0 && n1!=NULL)){
			printf("Error(1) %d\n",a);
			return;
			}
		n2=(PPP *)EqualLeastSearch(&q,QQ, Numb,sizeof(PPP),SearchExe);
		if(  (Numb!=0 && n2!=NULL && n2->x!=q.x)
		  || (Numb!=0 && n2!=NULL && n2!=QQ && (n2-1)->x>=q.x)
		  || (Numb==0 && n2!=NULL)
		  || (Numb!=0 && n2==NULL && n1!=NULL)){
			printf("Error(2) %d\n",a);
			return;
			}
		n3=(PPP *)EqualGreatestSearch(&q,QQ, Numb,sizeof(PPP),SearchExe);
		if(  (Numb!=0 && n3!=NULL && n3->x!=q.x)
		  || (Numb!=0 && n3!=NULL && n3!=&QQ[Numb-1] && (n3+1)->x<=q.x)
		  || (Numb==0 && n3!=NULL)
		  || (Numb!=0 && n3==NULL && n1!=NULL)){
			printf("Error(3) %d\n",a);
			return;
			}

		n4=(PPP *)LessSearch(&q,QQ, Numb,sizeof(PPP),SearchExe);
		if(  (Numb!=0 && n4!=NULL && n4!=QQ && (n4-1)->x>=q.x)
		  || (Numb==0 && n4!=NULL)
		  || (Numb!=0 && n4==NULL && QQ[0].x<q.x)){
			printf("Error(4) %d\n",a);
			return;
			}
		n5=(PPP *)GreaterSearch(&q,QQ, Numb,sizeof(PPP),SearchExe);
		if(  (Numb!=0 && n5!=NULL && n5!=&QQ[Numb-1] && (n5+1)->x<=q.x)
		  || (Numb==0 && n5!=NULL)
		  || (Numb!=0 && n5==NULL && QQ[Numb-1].x>q.x)){
			printf("Error(5) %d\n",a);
			return;
			}
		printf("%u OK\n",a);
		}
}
*/


static void swap(char *a, char *b, unsigned width)
{
  char tmp;

  if (a != b)
  {
    while (width--) 
    {
      tmp = *a;
      *a++ = *b;
      *b++ = tmp;
    }
  }
}


static void shortsort(char *lo, char *hi, unsigned width, int (*comp)(const void *, const void *, const void *),void *sortref)
{
  char *p, *max;

  while (hi > lo) 
  {
    max = lo;
    for (p = lo+width; p <= hi; p += width) if (comp(p, max,sortref) > 0) max = p;
    swap(max, hi, width);
    hi -= width;
  }
}
#define CUTOFF 8

void QSort(void *base, unsigned num, unsigned width, int (*comp)(const void *, const void *, const void *),void *sortref)
{
  char *lo, *hi;
  char *mid;
  char *loguy, *higuy;
  unsigned size;
  char *lostk[30], *histk[30];
  int stkptr;

  if (num < 2 || width == 0) return;
  stkptr = 0;

  lo = (char *)base;
  hi = (char *) base + width * (num - 1);

recurse:
  size = (hi - lo) / width + 1;

  if (size <= CUTOFF) 
  {
    shortsort(lo, hi, width, comp ,sortref);
  }
  else 
  {
    mid = lo + (size / 2) * width;
    swap(mid, lo, width);

    loguy = lo;
    higuy = hi + width;

    for (;;) 
    {
      do { loguy += width; } while (loguy <= hi && comp(loguy, lo,sortref) <= 0);
      do { higuy -= width; } while (higuy > lo && comp(higuy, lo,sortref) >= 0);
      if (higuy < loguy) break;
      swap(loguy, higuy, width);
    }

    swap(lo, higuy, width);

    if (higuy - 1 - lo >= hi - loguy) 
    {
      if (lo + width < higuy) 
      {
        lostk[stkptr] = lo;
        histk[stkptr] = higuy - width;
        ++stkptr;
      }

      if (loguy < hi) 
      {
        lo = loguy;
        goto recurse;
      }
    }
    else
    {
      if (loguy < hi) 
      {
        lostk[stkptr] = loguy;
        histk[stkptr] = hi;
        ++stkptr;
      }

      if (lo + width < higuy) 
      {
        hi = higuy - width;
        goto recurse;
      }
    }
  }

  --stkptr;
  if (stkptr >= 0) 
  {
    lo = lostk[stkptr];
    hi = histk[stkptr];
    goto recurse;
  }
  else
    return;
}
