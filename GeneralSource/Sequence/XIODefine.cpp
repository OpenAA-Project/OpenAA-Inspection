/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\XIODefine.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include "XIODefine.h"
#include "XGeneralFunc.h"
//---------------------------------------------------------------------------


IODefineClass::IODefineClass(void)
{
    BoardNumb=0;
    INumb=NULL;
    ONumb=NULL;

    DefInName   =NULL;
    DefOutName  =NULL;
}
IODefineClass::~IODefineClass(void)
{
    Release();
}
void    IODefineClass::Release(void)
{
    if(DefInName!=NULL){
        for(int i=0;i<BoardNumb;i++){
            if(DefInName[i]!=NULL){
                for(int k=0;k<INumb[i];k++){
					if(DefInName[i][k]!=NULL){
                        delete  []DefInName[i][k];
					}
				}
			}
			delete  []DefInName[i];
		}
        delete  []DefInName;
        DefInName=NULL;
	}
    if(DefOutName!=NULL){
        for(int i=0;i<BoardNumb;i++){
            if(DefOutName[i]!=NULL){
                for(int k=0;k<ONumb[i];k++){
					if(DefOutName[i][k]!=NULL){
						delete  []DefOutName[i][k];
					}
				}
			}
            delete  []DefOutName[i];
		}
        delete  []DefOutName;
        DefOutName=NULL;
	}

	if(INumb!=NULL){
        delete  []INumb;
	}
    INumb=NULL;

	if(ONumb!=NULL){
        delete  []ONumb;
	}
    ONumb=NULL;
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    IODefineClass::ReadDefFile(char *DefFileName)
{
    FILE    *file;
    char    *fp,*gp;
    int     BoardNumber=0;

    char    buff[256];
    Release();

	if((file=fopen(DefFileName,"rt"))==NULL){
        return(false);
	}
    while(fgets(buff, sizeof(buff)-1, file)!=NULL){
        fp=buff;
		while((*fp==' ') || (*fp=='\t')){
            fp++;
		}
        if(strnicmp(fp,"BOARD",5)==0){
            fp+=5;
			while(*fp==' ' || *fp=='\t'){
                fp++;
			}
            BoardNumb++;
            }
        }
    fclose(file);

    INumb=new int[BoardNumb];
    ONumb=new int[BoardNumb];
    DefInName =new char**[BoardNumb];
    DefOutName=new char**[BoardNumb];
    for(int i=0;i<BoardNumb;i++){
        INumb[i]=0;
        ONumb[i]=0;
        DefInName [i]=NULL;
        DefOutName[i]=NULL;
        }


    if((file=fopen(DefFileName,"rt"))==NULL)
        return(false);
    while(fgets(buff, sizeof(buff)-1, file)!=NULL){
        fp=buff;
		while(*fp==' ' || *fp=='\t'){
            fp++;
		}
        if(strnicmp(fp,"IN",2)==0){
            fp+=2;
			while((*fp==' ') || (*fp=='\t')){
                fp++;
			}
            int d;
			if(sscanf(fp,"%d",&d)!=1){
                continue;
			}
			if(d<0){
                continue;
			}
            INumb[BoardNumber]=d+1;
		}
        else if(strnicmp(fp,"OUT",3)==0){
            fp+=3;
			while((*fp==' ') || (*fp=='\t')){
                fp++;
			}
            int d;
			if(sscanf(fp,"%d",&d)!=1){
                continue;
			}
			if(d<0){
                continue;
			}
            ONumb[BoardNumber]=d+1;
		}
        else if(strnicmp(fp,"BOARD",5)==0){
            fp+=5;
			while((*fp==' ') || (*fp=='\t')){
                fp++;
			}
            int d;
            if(sscanf(fp,"%d",&d)!=1){
                continue;
                }
            if(d>=0 && d<BoardNumb){
                BoardNumber=d;
			}
		}
	}
    fclose(file);
    for(int i=0;i<BoardNumb;i++){
        DefInName [i]=new char *[INumb[i]];
        for(int k=0;k<INumb[i];k++){
            DefInName [i][k]=NULL;
		}
        DefOutName[i]=new char *[ONumb[i]];
        for(int k=0;k<ONumb[i];k++){
            DefOutName [i][k]=NULL;
		}
	}

    BoardNumber=0;
	if((file=fopen(DefFileName,"rt"))==NULL){
        return(false);
	}
    while(fgets(buff, sizeof(buff)-1, file)!=NULL){
        fp=buff;
		while((*fp==' ') || (*fp=='\t')){
            fp++;
		}
        if(strnicmp(fp,"IN",2)==0){
            fp+=2;
			while((*fp==' ') || (*fp=='\t')){
                fp++;
			}
            int d;
			if(sscanf(fp,"%d",&d)!=1){
                continue;
			}
			if(d<0 || d>=INumb[BoardNumber]){
                continue;
			}
            fp++;
			while((*fp!=' ') && (*fp!='\t') && (*fp!=0)){
                fp++;
			}
			while((*fp==' ') || (*fp=='\t')){
                fp++;
			}
			if(*fp!='\"'){
                continue;
			}
            gp=strchr(buff,0)-1;
			while((*gp!='\"') && (gp>buff)){
                gp--;
			}
			if(*gp!='\"'){
                continue;
			}
			if(gp==fp){
                continue;
			}
            fp++;
            *gp=0;
			if(DefInName[BoardNumber][d]!=NULL){
                delete  []DefInName[BoardNumber][d];
			}
            DefInName[BoardNumber][d]=new char[strlen(fp)+1];
            strcpy(DefInName[BoardNumber][d],fp);
            }
        else if(strnicmp(fp,"OUT",3)==0){
            fp+=3;
			while((*fp==' ') || (*fp=='\t')){
                fp++;
			}
            int d;
			if(sscanf(fp,"%d",&d)!=1){
                continue;
			}
			if(d<0 || d>=ONumb[BoardNumber]){
                continue;
			}
            fp++;
			while((*fp!=' ') && (*fp!='\t') && (*fp!=0)){
                fp++;
			}
			while((*fp==' ') || (*fp=='\t')){
                fp++;
			}
			if(*fp!='\"'){
                continue;
			}
            gp=strchr(buff,0)-1;
			while((*gp!='\"') && (gp>buff)){
                gp--;
			}
			if(*gp!='\"'){
                continue;
			}
			if(gp==fp){
                continue;
			}
            fp++;
            *gp=0;
			if(DefOutName[BoardNumber][d]!=NULL){
                delete  []DefOutName[BoardNumber][d];
			}
            DefOutName[BoardNumber][d]=new char[strlen(fp)+1];
            strcpy(DefOutName[BoardNumber][d],fp);
		}
        else if(strnicmp(fp,"BOARD",5)==0){
            fp+=5;
			while((*fp==' ') || (*fp=='\t')){
                fp++;
			}
            int d;
            if(sscanf(fp,"%d",&d)!=1){
                continue;
			}
            if((d>=0) && (d<BoardNumb)){
                BoardNumber=d;
			}
		}
	}
    fclose(file);
    return(true);
}



