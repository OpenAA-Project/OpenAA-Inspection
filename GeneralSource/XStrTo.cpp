/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XStrTo.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#define	_USE_MATH_DEFINES
#include<math.h>
#include<ctype.h>
#include<stdio.h>
#include<stdarg.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
#include<float.h>
#include"XGeneralFunc.h"


signed int strtoi(char *s,int &numb)
/*	文字列 -> 符号付き int 整数  の変換

	numb に変換に使用した文字数が返る
	変換しなかった場合、numb = 0 が返る
	*/
{
	int	i;
	int	j;
	char	*sa;
	numb=0;

	sa=s;
	while(*s==' ' || *s=='\t'){
		s++;
	}
	if(*s==0){
		numb=0;
		return(0);
		}
	if(*s=='-'){
		j=-1;
		s++;
		}
	else if(*s=='+'){
		j=-1;
		s++;
		}
	else if(isdigit(*s)==0){
		numb=0;
		return(0);
		}
	else{
		j=1;
	}

	while(*s=='0' && *(s+1)=='0'){
		s++;
		numb++;
		}
	if(*s=='0' && !isdigit(*(s+1)) ){
		numb++;
		return(0);
		}

	while(*s==' ' || *s=='0' || *s=='\t'){
		s++;
	}
	for(i=0;*s!=0;s++){
		if(isdigit(*s)==0){
			break;
		}
		i*=10;
		i+=(int)(*s-'0');
		}
	numb=(int)(s-sa);
	return(i*j);
}

signed long strtol(char *s,int &numb)
/*	文字列 -> 符号付き long 整数  の変換

	numb に変換に使用した文字数が返る
	変換しなかった場合、numb = 0 が返る
	*/
{
	long	i;
	long	j;
	char	*sa;
	numb=0;

	sa=s;
	while(*s==' ' || *s=='\t'){
		s++;
	}
	if(*s==0){
		numb=0;
		return(0);
		}
	if(*s=='-'){
		j=-1L;
		s++;
		}
	else if(*s=='+'){
		j=1L;
		s++;
		}
	else if(isdigit(*s)==0){
		numb=0;
		return(0);
		}
	else{
		j=1;
	}

	while(*s=='0' && *(s+1)=='0'){
		s++;
		numb++;
		}
	if(*s=='0' && !isdigit(*(s+1)) ){
		numb++;
		return(0);
		}

	while(*s==' ' || *s=='0' || *s=='\t'){
		s++;
	}
	for(i=0;*s!=0;s++){
		if(isdigit(*s)==0){
			break;
		}
		i*=10L;
		i+=(long)(*s-'0');
		}
	numb=(int)(s-sa);
	return(i*j);
}

unsigned int strtox(char *s,int &numb)
/*	文字列 -> 符号なし１６進整数  の変換

	numb に変換に使用した文字数が返る
	変換しなかった場合、numb = 0 が返る
	*/
{
	unsigned int	i;
	char	*sa;
	numb=0;

	sa=s;
	while(*s==' ' || *s=='\t'){
		s++;
	}
	if(*s==0 || isxdigit(*s)==0){
		numb=0;
		return(0);
		}
	while(*s=='0' && *(s+1)=='0'){
		s++;
		numb++;
		}
	if(*s=='0' && !isxdigit(*(s+1)) ){
		numb++;
		return(0);
		}

	for(i=0;*s!=0;s++){
		if(isxdigit(*s)==0){
			break;
		}
		i*=16;
		if(isdigit(*s)){
			i+=(int)(*s-'0');
			}
		else if('a'<=*s && *s<='f'){
			i+=(int)(*s-'a'+10);
			}
		else if('A'<=*s && *s<='F'){
			i+=(int)(*s-'A'+10);
			}
		}
	numb=(int)(s-sa);
	return(i);
}

unsigned long strtoX(char *s,int &numb)
/*	文字列 -> 符号なし１６進整数  の変換

	numb に変換に使用した文字数が返る
	変換しなかった場合、numb = 0 が返る
	*/
{
	unsigned long	i;
	char	*sa;
	numb=0;

	sa=s;
	while(*s==' ' || *s=='\t'){
		s++;
	}
	if(*s==0 || isxdigit(*s)==0){
		numb=0;
		return(0);
		}
	while(*s=='0' && *(s+1)=='0'){
		s++;
		numb++;
		}
	if(*s=='0' && isxdigit(*(s+1)) ){
		numb++;
		return(0);
		}

	for(i=0;*s!=0;s++){
		if(isxdigit(*s)==0){
			break;
		}
		i*=16L;
		if(isdigit(*s)){
			i+=(long)(*s-'0');
			}
		else if('a'<=*s && *s<='f'){
			i+=(long)(*s-'a'+10);
			}
		else if('A'<=*s && *s<='F'){
			i+=(long)(*s-'A'+10);
			}
		}
	numb=(int)(s-sa);
	return(i);
}

unsigned int strtoo(char *s,int &numb)
/*	文字列 -> 符号なし８進整数  の変換

	numb に変換に使用した文字数が返る
	変換しなかった場合、numb = 0 が返る
	*/
{
	unsigned int	i;
	char	*sa;
	numb=0;

	sa=s;
	while(*s==' ' || *s=='\t'){
		s++;
	}
	if(*s==0 || (*s<'0' || '8'<=*s)){
		numb=0;
		return(0);
		}
	while(*s=='0' && *(s+1)=='0'){
		s++;
		numb++;
		}
	if(*s=='0' && '0'<=*(s+1) && *(s+1)<='7' ){
		numb++;
		return(0);
		}

	for(i=0;*s!=0;s++){
		if(*s<'0' || '8'<=*s){
			break;
		}
		i*=8;
		i+=(int)(*s-'0');
	}
	numb=(int)(s-sa);
	return(i);
}

unsigned long strtoO(char *s,int &numb)
/*	文字列 -> 符号なし８進整数  の変換

	numb に変換に使用した文字数が返る
	変換しなかった場合、numb = 0 が返る
	*/
{
	unsigned long	i;
	char	*sa;
	numb=0;

	sa=s;
	while(*s==' ' || *s=='\t'){
		s++;
	}
	if(*s==0 || (*s<'0' || '8'<=*s)){
		numb=0;
		return(0);
		}
	while(*s=='0' && *(s+1)=='0'){
		s++;
		numb++;
		}
	if(*s=='0' && '0'<=*(s+1) && *(s+1)<='7' ){
		numb++;
		return(0);
		}

	for(i=0;*s!=0;s++){
		if(*s<'0' || '8'<=*s){
			break;
		}
		i*=8L;
		i+=(long)(*s-'0');
	}
	numb=(int)(s-sa);
	return(i);
}



long double strtodouble(char *s,int &numb)
/*	文字列 -> 符号付きlong double 浮動小数 の変換

	numb に変換に使用した文字数が返る
	変換しなかった場合、numb = 0 が返る
	*/
{
	long double	i,j,k,m,n,t;
	char	*sa;

	sa=s;
	i=j=k=0.0;
	m=n=1.0;
	while(*s==' ' || *s=='\t'){
		s++;
	}
	if(*s=='0' && strchr(" \t\n",*(s+1))!=NULL ){
		numb=1;
		return(0);
		}

	if(*s==0){
		numb=0;
		return(0);
		}
	if(*s=='+'){
		s++;
		m=1.0;
		}
	else if(*s=='-'){
		s++;
		m=-1.0;
		}
	else if(isdigit(*s) || *s=='.'){	m=1.0;	}
	else{
		numb=0;
		return(0);
		}
	//while(*s==' ' || *s=='\t')	s++;

	for(;*s!=0;s++){
		if(isdigit(*s)==0){
			break;
		}
		i*=10.0;
		i+=(long double)(*s-'0');
		}
	//while(*s==' ' || *s=='\t')	s++;
	if(*s=='.'){
		s++;
		while(*s==' ' || *s=='\t'){
			s++;
		}
		t=0.1;
		for(;*s!=0;s++){
			if(isdigit(*s)==0){
				break;
			}
			j+=(long double)(*s-'0')*t;
			t*=0.1;
			}
		}
	//while(*s==' ' || *s=='\t')	s++;
	if(*s=='e' || *s=='E'){
		s++;
		//while(*s==' ' || *s=='\t')	s++;
		if(*s=='+'){
			s++;
			n=1.0;
			}
		else if(*s=='-'){
			s++;
			n=-1.0;
			}
		else if(isdigit(*s) || *s=='.'){
			n=1.0;
		}
		//while(*s==' ' || *s=='\t')	s++;
		for(;*s!=0;s++){
			if(isdigit(*s)==0){
				break;
			}
			k*=10.0;
			k+=(long double)(*s-'0');
			}
		}
	numb=(int)(s-sa);
	return(m*(i+j)*powl(10.0,k*n));
}



int matchscanattr=0;	// ０の時、大文字小文字を区別する

int matchscanf(char *buff,char *form,...)
/*	マッチングしながらデータの値を得る

	buff に被抽出文字列バッファを入れる
	form の形式
		%hd	%d	%ld	%c	%lE	%s
		%hi	%i	%li	%f	%lF
		%ho	%o	%lo	%e
		%hu	%u	%lu	%lf
		%hx	%x	%lx	%le
				%D	%F
				%I	%E
				%O
				%U
				%X
		スペース ・・・ １個以上のスペースかタブとマッチングする
		タブ・・・・・	０個以上のスペースかタブとマッチングする
		それ以外の文字	大文字小文字の区別をして１文字ずつマッチングして行く

	リターン
		正：	正常にマッチング終了した。格納した数値の個数が返る
		負：	マッチングが正常に行われなかった。
			格納した数値の個数にー１を掛けたもの ー１ になる。

	正常終了の条件
		抽出した数値が数値の範囲内にある
		文字列がマッチングする
		数値が必要な場所に数値がある
	    これらの条件が form の終わりまで満たされた場合、正常終了となる
*/
{
	const char	*formmaster[]={
			"%hd","%hi","%ho","%hu","%hx",
			"%d" ,"%i" ,"%o" ,"%u" ,"%x",
			"%ld","%li","%lo","%lu","%lx",
			"%D" ,"%I" ,"%O" ,"%U" ,"%X",
			"%c" ,"%f" ,"%e" ,"%lf","%le","%F","%E",
			"%lF","%lE",
			"%s","%0x","%0X"
			""
			};
	char	*fp,c;
	va_list ap;
	int	i1;
	long	i2;
	unsigned int	i3;
	unsigned long	i4;
	long double	i5;
	int	n,tnumb;
	int	i,j;

	fp=form;
	va_start(ap,form);
	for(tnumb=0;;){
		for(i=0;i<32;i++){
			if(memcmp(fp,formmaster[i],strlen(formmaster[i]))==0){
				break;
			}
		}
		if(i<32){
			if(i==0){
				signed char *a = va_arg(ap,signed char *);
				i1=strtoi(buff,n);
				if(n==0 || i1<-128 || i1>127){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i1;
			}
			else if(i==1){
				unsigned char *a = va_arg(ap,unsigned char *);
				if(buff[0]=='0'){
					if(buff[1]=='x' || buff[1]=='X'){
					//if(memcmp(buff,"0x",2)==0 || memcmp(buff,"0X",2)==0){
						buff+=2;
						i3=strtox(buff,n);
						}
					else if(buff[1]=='d' || buff[1]=='D'){
					//else if(memcmp(buff,"0d",2)==0 || memcmp(buff,"0D",2)==0){
						buff+=2;
						i1=strtoi(buff,n);
						i3=i1;
						}
					else{
					//else if(memcmp(buff,"0",1)==0){
						buff++;
						i3=strtoo(buff,n);
						}
					}
				else{
					i3=strtox(buff,n);
					if(*(fp+n)!='h' && *(fp+n)!='H'){
						i3=strtoo(buff,n);
						if(*(fp+n)!='O' && *(fp+n)!='o'){
							i1=strtoi(buff,n);
							if(*(fp+n)=='D' || *(fp+n)=='d'){
								n++;
							}
							i3=i1;
							}
						else{
							n++;
						}
					}
					else{
						n++;
					}
				}
				if(n==0 || i3>255){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i3;
			}
			else if(i==2){
				unsigned char *a = va_arg(ap,unsigned char *);
				i3=strtoo(buff,n);
				if(n==0 || i3>255){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i3;
			}
			else if(i==3){
				unsigned char *a = va_arg(ap,unsigned char *);
				i1=strtoi(buff,n);
				if(n==0 || i1<0 || i1>256){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i1;
			}
			else if(i==4){
				unsigned char *a = va_arg(ap,unsigned char *);
				i3=strtox(buff,n);
				if(n==0 || i3>255){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i3;
			}
			else if(i==30){
				unsigned char *a = va_arg(ap,unsigned char *);
				if(!isdigit(buff[0])){
					va_end(ap);
					return(-tnumb-1);
				}
				i3=strtox(buff,n);
				if(n==0 || i3>255){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i3;
			}
			else if(i==31){
				unsigned short *a = va_arg(ap,unsigned short *);
				if(!isdigit(buff[0])){
					va_end(ap);
					return(-tnumb-1);
				}
				i3=strtox(buff,n);
				*a=i3;
			}
			else if(i==5){
				signed int *a = va_arg(ap,signed int *);
				i1=strtoi(buff,n);
				if(n==0){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i1;
			}
			else if(i==6){
				unsigned int *a = va_arg(ap,unsigned int *);
				if(buff[0]=='0'){
					if(buff[1]=='x' || buff[1]=='X'){
					//if(memcmp(buff,"0x",2)==0 || memcmp(buff,"0X",2)==0){
						buff+=2;
						i3=strtox(buff,n);
						}
					else if(buff[1]=='d' || buff[1]=='D'){
					//else if(memcmp(buff,"0d",2)==0 || memcmp(buff,"0D",2)==0){
						buff+=2;
						i1=strtoi(buff,n);
						i3=i1;
						}
					else{
					//else if(memcmp(buff,"0",1)==0){
						buff++;
						i3=strtoo(buff,n);
						}
					}
				else{
					i3=strtox(buff,n);
					if(*(fp+n)!='h' && *(fp+n)!='H'){
						i3=strtoo(buff,n);
						if(*(fp+n)!='O' && *(fp+n)!='o'){
							i1=strtoi(buff,n);
							if(*(fp+n)=='D' || *(fp+n)=='d'){
								n++;
							}
							i3=i1;
							}
						else{
							n++;
						}
					}
					else{
						n++;
					}
				}
				if(n==0){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i3;
			}
			else if(i==7){
				unsigned int *a = va_arg(ap,unsigned int *);
				i3=strtoo(buff,n);
				if(n==0){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i3;
			}
			else if(i==8){
				unsigned int *a = va_arg(ap,unsigned int *);
				i1=strtoi(buff,n);
				if(n==0){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i1;
			}
			else if(i==9){
				unsigned int *a = va_arg(ap,unsigned int *);
				i3=strtox(buff,n);
				if(n==0){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i3;
			}
			else if(i==10 || i==15){
				signed long *a = va_arg(ap,signed long *);
				i2=strtol(buff,n);
				if(n==0){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i2;
			}
			else if(i==11 || i==16){
				unsigned long *a = va_arg(ap,unsigned long *);
				if(buff[0]=='0'){
					if(buff[1]=='x' || buff[1]=='X'){
					//if(memcmp(buff,"0x",2)==0 || memcmp(buff,"0X",2)==0){
						buff+=2;
						i4=strtoX(buff,n);
						}
					else if(buff[1]=='d' || buff[1]=='D'){
					//else if(memcmp(buff,"0d",2)==0 || memcmp(buff,"0D",2)==0){
						buff+=2;
						i2=strtol(buff,n);
						i4=i2;
						}
					else{
					//else if(memcmp(buff,"0",1)==0){
						buff++;
						i4=strtoO(buff,n);
						}
					}
				else{
					i4=strtoX(buff,n);
					if(*(fp+n)!='h' && *(fp+n)!='H'){
						i4=strtoO(buff,n);
						if(*(fp+n)!='O' && *(fp+n)!='o'){
							i2=strtol(buff,n);
							if(*(fp+n)=='D' || *(fp+n)=='d'){
								n++;
							}
							i4=i2;
							}
						else{
							n++;
						}
					}
					else{
						n++;
					}		
				}
				if(n==0){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i4;
			}
			else if(i==12 || i==17){
				unsigned long *a = va_arg(ap,unsigned long *);
				i4=strtoO(buff,n);
				if(n==0){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i4;
			}
			else if(i==13 || i==18){
				unsigned long *a = va_arg(ap,unsigned long *);
				i2=strtol(buff,n);
				if(n==0){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i2;
			}
			else if(i==14 || i==19){
				unsigned long *a = va_arg(ap,unsigned long *);
				i4=strtoX(buff,n);
				if(n==0){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i4;
			}
			else if(i==20){
				char *a = va_arg(ap,char *);
				for(n=0;*(buff+n)!=0;n++){
					if(*(buff+n)!=' ' && *(buff+n)!='\t'){
						break;
					}
				}
				if(*(buff+n)==0){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=*(buff+n);
				n++;
			}
			else if(i==21 || i==22){
				float *a = va_arg(ap,float *);
				i5=strtodouble(buff,n);
				if(n==0 || (fabsl(i5)<FLT_MIN && i5!=0.0) || FLT_MAX<fabsl(i5)){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=(float)i5;
			}
			else if(i==23 || i==24 || i==25 || i==26){
				double *a = va_arg(ap,double *);
				i5=strtodouble(buff,n);
				if(n==0 || (fabsl(i5)<DBL_MIN && i5!=0.0) || DBL_MAX<fabsl(i5)){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=(double)i5;
			}
			else if(i==27 || i==28){
				long double *a = va_arg(ap,long double *);
				i5=strtodouble(buff,n);
				if(n==0){
					va_end(ap);
					return(-tnumb-1);
					}
				*a=i5;
			}
			else if(i==29){
				char *a = va_arg(ap,char *);
				for(j=0;;j++){
					c=*(fp+strlen(formmaster[i])+j);
					if(c==0){
						break;
					}
					if(c==' ' || c=='\t'){
						continue;
					}
					break;
				}
				for(n=0;*(buff+n)!=0;n++){
					if(*(buff+n)!=' ' && *(buff+n)!='\t'){
						break;
					}
				}
				if(*(buff+n)==0){
					va_end(ap);
					return(-tnumb-1);
					}
				for(;;){
					*(char *)a=*(buff+n);
					if(*(buff+n)==' ' || *(buff+n)=='\t' || *(buff+n)==0){
						*a=0;
						break;
						}
					if(strchr(",./<>?:*]}[{~@\\|`^=-)(\'&%$#\"!",c)!=NULL && *(buff+n)==c){
						*a=0;
						break;
						}
					a++;
					n++;
					}
				}			
			fp+=strlen(formmaster[i]);
			buff+=n;
			if(*fp!=' '){
				while(*buff==' ' || *buff=='\t'){
					buff++;
				}
			}
			tnumb++;
			}
		else if(*fp==' '){
			if(*buff!=' ' && *buff!='\t'){
				return(-tnumb-1);
				}
			while(*buff==' ' || *buff=='\t'){
				buff++;
			}
			while(*fp==' ' || *fp=='\t'){
				fp++;
			}
		}
		else if(*fp=='\t'){
			while(*buff==' ' || *buff=='\t'){
				buff++;
			}
			while(*fp==' ' || *fp=='\t'){
				fp++;
			}
		}
		else if(*fp==0){
			va_end(ap);
			return(tnumb);
			}
		else if(matchscanattr==0){
			if(*fp!=*buff || *buff==0){
				va_end(ap);
				return(-tnumb-1);
				}
			fp++;
			buff++;
			}
		else if(matchscanattr!=0){
			if(tolower(*fp)!=tolower(*buff) || *buff==0){
				va_end(ap);
				return(-tnumb-1);
				}
			fp++;
			buff++;
			}
		}
	va_end(ap);

}








int CheckPath(char *path)
/*	パス名の正当性のみをチェックする
	リターン：
		０：正当
		１：ドライブ名が不当
		２：ディレクトリ名が不当
		３：ファイルベース名が不当
		４：ファイル拡張子が不当
	*/
{
	char	*kpath,*fp,*lfp;

	kpath=path;
	if((fp=strchr(kpath,':'))!=NULL){
		if(fp-kpath+1>_MAX_DRIVE-1)	return(1);
		kpath=fp+1;
		}
	lfp=fp=strchr(path,0)-1;
	while(*fp!='.' && fp>=kpath)	fp--;
	if(*fp=='.'){
		if(lfp-fp+1>_MAX_EXT-1) return(4);
		lfp=fp-1;
		if(lfp<kpath)	lfp=kpath;
		}
	fp=lfp;
	while(*fp!='\\' && fp>kpath)	fp--;
	if(*fp=='\\')	fp++;
	if(lfp-fp+1>_MAX_FNAME-1 || *fp=='.')	return(3);
	if(fp-kpath>_MAX_DIR)		return(2);

	return(0);

}


