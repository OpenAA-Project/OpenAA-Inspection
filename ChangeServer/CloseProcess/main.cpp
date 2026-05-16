/*
 * Copyright (C) 2021
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

#include <QtCore/QCoreApplication>
#include <stdio.h>
#include <string.h>
#include "XMacro.h"

void	ShowHelp(void)
{
	printf("");
}

bool	CloseProcessFunction(char *ProcessImageName,int MaxWaitForTerminte);


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	int	MaxWaitForTerminte=0;

	char ProcessImageName[256];
    for(int i=0; i<argc; i++){
        // C文字列をQtのQStringに変換して扱いやすくする
        QString arg = QString::fromLocal8Bit(argv[i]);

        // stricmp(argv[i], "/?") のQt版代替
        if(arg.compare("/?", Qt::CaseInsensitive) == 0){
            ShowHelp();
            break;
        }
        // stricmp(argv[i], "-?") のQt版代替
        else if(arg.compare("-?", Qt::CaseInsensitive) == 0){
            ShowHelp();
            break;
        }
        // strnicmp(argv[i], "-W", 2) のQt版代替（-Wから始まるかどうかの判定）
        else if(arg.startsWith("-W", Qt::CaseInsensitive)){
            // "-W"より後ろの文字列を切り出して整数に変換 (sscanfの代わり)
            MaxWaitForTerminte = arg.mid(2).toInt();
        }
        else{
            // QStringからC言語の配列へコピー
            QByteArray bytes = arg.toLocal8Bit();
            strncpy(ProcessImageName, bytes.constData(), sizeof(ProcessImageName) - 1);
            ProcessImageName[sizeof(ProcessImageName) - 1] = '\0'; // バッファオーバーラン対策
        }
    }
	CloseProcessFunction(ProcessImageName,MaxWaitForTerminte);


	return 0;
}