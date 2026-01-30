/*
 * Copyright (C) 2012
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