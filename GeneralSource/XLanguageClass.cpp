/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XLanguageClass.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include <QtGui>
#include <QTableWidget>
#include <QTabWidget>
#include <QTextCodec>
#include "XLanguageClass.h"
#include "XLanguageStockerLoader.h"
#include <QMessageBox>

LangSolverNew::LangSolverNew(const char *_IDName)
:IDName(_IDName)
{
	LPackPointer	=NULL;
	CompPointer		=NULL;
}

bool	LangSolverNew::SetLanguage(LanguagePackage &Stocker ,int LangCode)
{
	LPackPointer=&Stocker;
	LPackPointer->SetLanguage(LangCode);

	CompPointer	=LPackPointer->GetComponent(IDName);
	if(CompPointer!=NULL){
		return true;
	}
	return false;
}
QString	LangSolverNew::GetString(int FileID ,int LID)
{
	if(CompPointer!=NULL){
		return CompPointer->GetString(FileID ,LID);
	}
	return /**/"";
}
void	LangSolverNew::SetUI(QWidget *W)
{
	QString	UIClassName=W->objectName();
	QString	ObjName=W->objectName();
	if(CompPointer!=NULL){
		CompPointer->SetUIInner(W ,UIClassName,ObjName);
	}
}

int		LangSolverNew::GetLanguageCode(void)
{
	return LPackPointer->GetLanguageCode();
}




//============================================================================

LangSolverClass::LangSolverClass(struct LSStringResource _LSStrDictionary[]
								,struct LSUIResource _LSUIDictionary[]
								,char	*_CodecList[])
{	
	LSStrDictionary	=_LSStrDictionary;
	LSUIDictionary	=_LSUIDictionary;
	for(int i=0;i<MAXLANGUAGECOUNT;i++){
		CodecList[i]=_CodecList[i];
	}
	LanguageCode=0;	
	InitializedCodec=false;
}

bool	LangSolverClass::SetLanguage(int LangCode)
{
	LanguageCode=LangCode;
	return InitialCodec();
}

void	LangSolverClass::ErrorOut(void)
{
	QMessageBox::warning(NULL, "Different LanguageCode","LanguageCode is different");
}

QString	LangSolverClass::GetString(int FileID ,int LID)
{
	if(InitialCodec()==false){
		ErrorOut();
	}
	if(LSStrDictionary!=NULL){
		for(int i=0;;i++){
			if(LSStrDictionary[i].FileNameID==-1 && LSStrDictionary[i].ID==-1){
				break;
			}
			if(LSStrDictionary[i].FileNameID==FileID && LSStrDictionary[i].ID==LID){
				char	*Str=NULL;
				switch(LanguageCode){
					case 0:
						Str=LSStrDictionary[i].ListStrings1;	break;
					case 1:
						Str=LSStrDictionary[i].ListStrings2;	break;
					case 2:
						Str=LSStrDictionary[i].ListStrings3;	break;
					case 3:
						Str=LSStrDictionary[i].ListStrings4;	break;
					case 4:
						Str=LSStrDictionary[i].ListStrings5;	break;
					case 5:
						Str=LSStrDictionary[i].ListStrings6;	break;
					case 6:
						Str=LSStrDictionary[i].ListStrings7;	break;
					case 7:
						Str=LSStrDictionary[i].ListStrings8;	break;
					case 8:
						Str=LSStrDictionary[i].ListStrings9;	break;
					case 9:
						Str=LSStrDictionary[i].ListStrings10;break;
				}
				if(Str!=NULL){
					if(((unsigned char)Str[0])<0x20){
						Str=Str+2;
					}
					if(Str[0]==0){
						Str=LSStrDictionary[i].ListStrings1;
						if(((unsigned char)Str[0])<0x20){
							Str=Str+2;
						}
					}
					return QString::fromLocal8Bit(Str);
				}
			}
		}
	}
	return /**/"";
}


void	LangSolverClass::SetUI(QWidget *W)
{
	if(InitialCodec()==false){
		ErrorOut();
	}
	QString	UIClassName=W->objectName();
	SetUIInner(W ,UIClassName);
}

void	LangSolverClass::SetUIInner(QWidget *W ,const QString &UIClassName)
{
	QString	ObjName=W->objectName();
	char	*Str;
	QString	TableStr;

	if(LSUIDictionary!=NULL){
		for(int i=0;;i++){
			if(LSUIDictionary[i].UIClassName[0]==0 && LSUIDictionary[i].ControlName[0]==0){
				break;
			}
			if(UIClassName==LSUIDictionary[i].UIClassName && ObjName==LSUIDictionary[i].ControlName){
				Str=NULL;
				switch(LanguageCode){
					case 0:		Str=LSUIDictionary[i].ListStrings1;	break;
					case 1:		Str=LSUIDictionary[i].ListStrings2;	break;
					case 2:		Str=LSUIDictionary[i].ListStrings3;	break;
					case 3:		Str=LSUIDictionary[i].ListStrings4;	break;
					case 4:		Str=LSUIDictionary[i].ListStrings5;	break;
					case 5:		Str=LSUIDictionary[i].ListStrings6;	break;
					case 6:		Str=LSUIDictionary[i].ListStrings7;	break;
					case 7:		Str=LSUIDictionary[i].ListStrings8;	break;
					case 8:		Str=LSUIDictionary[i].ListStrings9;	break;
					case 9:		Str=LSUIDictionary[i].ListStrings10;	break;
				}
				if(Str!=NULL){
					if(((unsigned char)Str[0])<0x20){
						Str=Str+2;
					}
					if(Str[0]==0){
						Str=LSUIDictionary[i].ListStrings1;
						if(((unsigned char)Str[0])<0x20){
							Str=Str+2;
						}
					}
					if(strlen(LSUIDictionary[i].PropertyName)!=0){
						if(strcmp(LSUIDictionary[i].ClassTypeName,"QTableWidget")==0){
							QTableWidget	*TableW=dynamic_cast<QTableWidget *>(W);
							if(TableW!=NULL){
								for(int j=0;j<TableW->columnCount();j++){
									QTableWidgetItem	*f=TableW->horizontalHeaderItem(j);
									if(f!=NULL){
										QString	HLabel=f->text();
#if	QT_VERSION<0x050000
										QTextCodec::setCodecForTr (FirstCodec);
										TableStr=QObject::tr(LSUIDictionary[i].ListStrings1);
										QTextCodec::setCodecForTr (CurrentCodec);
#else
										QTextCodec::setCodecForLocale(FirstCodec);
										TableStr = QObject::tr(LSUIDictionary[i].ListStrings1);
										QTextCodec::setCodecForLocale(CurrentCodec);
#endif
										if(HLabel==TableStr){
											f->setText(Str);
										}
									}
								}
							}

						}
						else{
							W->setProperty(LSUIDictionary[i].PropertyName,QString(Str));
						}
					}
					else{
						if(W->parentWidget()!=NULL){
							QTabWidget	*ETab=dynamic_cast<QTabWidget *>(W->parentWidget()->parentWidget());
							if(ETab!=NULL){
								for(int j=0;j<ETab->count();j++){
									QWidget	*C=ETab->widget(j);
									QString	TbName=C->objectName();
									if(TbName==QString(LSUIDictionary[i].ControlName)){
										ETab->setTabText(j,Str);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	QObjectList WList=W->children ();
	for(int i=0;i<WList.count();i++){
		QWidget	*w=dynamic_cast<QWidget	*>(WList.value(i));
		if(w!=NULL){
			SetUIInner(w ,UIClassName);
		}
	}
}

bool	LangSolverClass::InitialCodec(void)
{
	bool	ret=true;
	char	*c;
	if(CodecList[LanguageCode]!=NULL || CodecList[0]!=NULL){
		if(InitializedCodec==false){
			if(CheckCodec()==false){
				ret=false;
			}
			FirstCodec= QTextCodec::codecForName(CodecList[0]);
			CurrentCodec = QTextCodec::codecForName(CodecList[LanguageCode]);
			if(CurrentCodec!=NULL){
#if	QT_VERSION<0x050000
				QTextCodec::setCodecForCStrings(CurrentCodec);
				QTextCodec::setCodecForLocale (CurrentCodec);
				QTextCodec::setCodecForTr (CurrentCodec);
#else
				QTextCodec::setCodecForLocale(CurrentCodec);
#endif
			}
			else{				
				QList<QByteArray> L=QTextCodec::availableCodecs ();
				for(int i=0;i<L.count();i++){
					QByteArray	a=L.value(i);
					c=a.data();
					if(strcmp(c,CodecList[LanguageCode])==0){
						c=a.data();
						CurrentCodec = QTextCodec::codecForName(c);
						if(CurrentCodec!=NULL){
#if	QT_VERSION<0x050000
							QTextCodec::setCodecForCStrings(CurrentCodec);
							QTextCodec::setCodecForLocale (CurrentCodec);
							QTextCodec::setCodecForTr (CurrentCodec);
#else
							QTextCodec::setCodecForLocale(CurrentCodec);
#endif						
						}
					}
				}
			}
			InitializedCodec=true;
		}
	}
	return ret;
}

bool	LangSolverClass::CheckCodec(void)
{
	QTextCodec	*codec = QTextCodec::codecForName(CodecList[LanguageCode]);
	if(codec==NULL){
		return false;

	}
	bool	ret=true;
#if	QT_VERSION<0x050000
	QTextCodec	*c1=QTextCodec::codecForCStrings();
	if(c1!=NULL && c1->name()!=codec->name()){
		ret=false;
	}
	QTextCodec	*c2=QTextCodec::codecForLocale();
	if(c2!=NULL && c2->name()!=codec->name()){
		ret=false;
	}
	QTextCodec	*c3=QTextCodec::codecForTr();
	if(c3!=NULL && c3->name()!=codec->name()){
		ret=false;
	}
	if(c1==NULL || c2==NULL || c3==NULL){
		ret=true;
	}
#else
	QTextCodec* c1 = QTextCodec::codecForLocale();
	if (c1 != NULL && c1->name() != codec->name()) {
		ret = false;
	}
#endif
	return ret;
}
