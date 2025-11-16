/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XCSV.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XCSV.h"
#include <QTextStream>
#include <QFile>


static	int	StrToHex(char c)
{
	switch(c){
		case '0':	return 0;
		case '1':	return 1;
		case '2':	return 2;
		case '3':	return 3;
		case '4':	return 4;
		case '5':	return 5;
		case '6':	return 6;
		case '7':	return 7;
		case '8':	return 8;
		case '9':	return 9;
		case 'a':	return 10;
		case 'A':	return 10;
		case 'b':	return 11;
		case 'B':	return 11;
		case 'c':	return 12;
		case 'C':	return 12;
		case 'd':	return 13;
		case 'D':	return 13;
		case 'e':	return 14;
		case 'E':	return 14;
		case 'f':	return 15;
		case 'F':	return 15;
	}
	return 0;
}

QString	QStringListListCSV::Get(int column, int row)	const
{
	if(count()<=row){
		return /**/"";
	}
	QStringList	v=at(row);
	if(v.count()<=column){
		return /**/"";
	}
	return v.at(column);
}


int	QStringListListCSV::GetMaxColumnCount(void)	const
{
	int	RMax=0;
	int	RNumb=GetRowCount();
	for(int r=0;r<RNumb;r++){
		int	c=GetColumnCount(r);
		if(c>RMax){
			RMax=c;
		}
	}
	return	RMax;
}

bool	QStringListListCSV::LoadFromCSVFile(const QString &FileName)
{
	QFile	file(FileName);
	if(file.open(QIODevice::ReadOnly | QIODevice::Text)==false){
		return false;
	}
	return LoadFromCSVFile(&file);
}

static	QString	CutWord(QString	&s,QString &CellWord ,bool &ok)
{
	int	Start=0;
	bool dq=false;
	if(s.left(1)=='\"'){
		Start=1;
		dq=true;
	}
	int	Len=s.length();
	QString	R;
	for(int i=Start;i<Len;i++){
		QChar	C=s[i];
		if(C==QChar('\"')){
			if((i+1)<Len && s[i+1]!=QChar('\"') && dq==true){
				CellWord=R;
				QString	Ret=s.mid(i+1);
				ok=true;
				return Ret;
			}
		}
		else if(C==',' && dq==false){
			CellWord=R.trimmed();
			QString	Ret=s.mid(i);
			ok=true;
			return Ret;
		}
		R.append(C);
	}
	if(dq==false){
		CellWord=R.trimmed();
		QString	Ret=s.mid(Len);
		ok=true;
		return Ret;
	}
	ok=false;
	return "";
}
bool	QStringListListCSV::LoadFromCSVFile(QIODevice *f)
{
	QTextStream	Text(f);
	while(Text.atEnd()==false){
		QStringList	StrList;
		QString	s=Text.readLine().trimmed();
		for(;;){
			QString	CellWord;
			bool	ok;
			s=CutWord(s,CellWord ,ok);
			if(ok==false)
				break;
			StrList.append(CellWord);

			s=s.trimmed();
			if(s.left(1)==','){
				s=s.mid(1);
				s=s.trimmed();
			}
			else{
				break;
			}
		}
		append(StrList);
	}
	return true;
}

bool	QStringListListCSV::SaveFromCSVFile(const QString &FileName)
{
	QFile	file(FileName);
	if(file.open(QIODevice::WriteOnly | QIODevice::Text)==false){
		return false;
	}
	return SaveFromCSVFile(&file);
}

bool	QStringListListCSV::SaveFromCSVFile(QIODevice *f)
{
	QTextStream	FStr(f);
	for(int i=0;i<count();i++){
		QStringList	s=value(i);
		for(int j=0;j<s.count();j++){
			FStr<<"\"";
			QString	t=s.value(j);
			FStr << t;
			FStr<<"\"";
			if(j<s.count()-1){
				FStr<<",";
			}
		}
		FStr<<"\n";
	}
	return true;

}

void	QStringListListCSV::Set(int column, int row ,const QString &str)
{
	if(count()<=row){
		for(int i=count();i<=row;i++){
			QStringList	s;
			append(s);
		}
	}
	QStringList	s=value(row);
	if(s.count()<=column){
		for(int i=s.count();i<=column;i++){
			QString	c;
			s.append(c);
		}
	}
	s.replace(column,str);
	replace(row,s);
}


bool	QStringListListCSV::operator==(QStringListListCSV &src)	const
{
	int	Yd=GetRowCount();
	int	Ys=src.GetRowCount();
	if(Ys!=Yd){
		return false;
	}
	for(int row=0;row<Ys;row++){
		int	ColumnCountd=GetColumnCount(row);
		int	ColumnCounts=src.GetColumnCount(row);
		if(ColumnCountd!=ColumnCounts){
			return false;
		}
		for(int c=0;c<ColumnCountd;c++){
			if(Get(c,row)!=src.Get(c,row)){
				return false;
			}
		}
	}
	return true;
}

bool	QStringListListCSV::operator!=(QStringListListCSV &src)	const
{
	if(QStringListListCSV::operator==(src)==true){
		return false;
	}
	return true;
}

