#include "XLanguageCodec.h"
#include <QTextCodec>
#include <QFile>
#include "XGeneralFunc.h"

QString	LanguagePack::DefaultFileName		=/**/"LanguagePack.dat";

bool	LanguageClass::Save(QIODevice *f)
{
	if(::Save(f,ColumnNo)==false)
		return false;
	if(::Save(f,LanguageName)==false)
		return false;
	if(::Save(f,ExcelFont)==false)
		return false;
	if(::Save(f,QtCotec)==false)
		return false;
	return true;
}

bool	LanguageClass::Load(QIODevice *f)
{
	if(::Load(f,ColumnNo)==false)
		return false;
	if(::Load(f,LanguageName)==false)
		return false;
	if(::Load(f,ExcelFont)==false)
		return false;
	if(::Load(f,QtCotec)==false)
		return false;
	return true;
}


bool	LanguagePack::SaveDefault(void)
{
	QFile	File(DefaultFileName);
	if(File.open(QIODevice::WriteOnly)==false){
		return false;
	}
	if(Save(&File)==false){
		return false;
	}
	return true;
}

bool	LanguagePack::LoadDefault(void)
{
	QFile	File(DefaultFileName);
	if(File.open(QIODevice::ReadOnly)==false){
		return false;
	}
	if(Load(&File)==false){
		return false;
	}
	return true;
}

void	LanguagePack::AllocCodec(void)
{
	for(LanguageClass *c=GetFirst();c!=NULL;c=c->GetNext()){
		char	Buff[100];
		QString2Char(c->QtCotec,Buff ,sizeof(Buff));
		c->CurrentCodec= QTextCodec::codecForName(Buff);
	}
}

void	LanguagePack::SetCodec(int n)
{
	LanguageClass	*c=GetItem(n);
	if(c!=NULL){
		if(c->CurrentCodec!=NULL){
			//QTextCodec::setCodecForCStrings	(c->CurrentCodec);
			QTextCodec::setCodecForLocale	(c->CurrentCodec);
			//QTextCodec::setCodecForTr		(c->CurrentCodec);
		}
	}
}
