#include <QString>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include "SimplePasswordForm.h"
#include "XSimpleLockWithPassword.h"

bool	SimpleLockWIthPassword::Load(void)
{
	QString	Str=QCoreApplication::applicationName ();
	QString	FileName=Str+/**/".pwd";
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		QTextStream	FStr(&File);
		while(FStr.atEnd()==false){
			QString Buff=FStr.readLine();
			QString L=Buff.trimmed();
			if(L.isEmpty()==false){
				LoadedPassword=L;
				return true;
			}
		}
	}
	return false;
}

bool	SimpleLockWIthPassword::CheckPassword(void)
{
	if(LoadedPassword!=CurrentPassword){
		SimplePasswordForm	D(NULL);
		if(D.exec()==(int)true){
			CurrentPassword=D.Password;
		}
	}
	if(LoadedPassword==CurrentPassword){
		return true;
	}
	return false;
}

bool	SimpleLockWIthPassword::CheckPasswordEverytime(void)
{
	SimplePasswordForm	D(NULL);
	if(D.exec()==(int)true){
		CurrentPassword=D.Password;
		if(LoadedPassword==CurrentPassword){
			return true;
		}
	}
	return false;
}