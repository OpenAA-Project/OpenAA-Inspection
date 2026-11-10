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

#include "CheckProgramRun.h"
#include "XSeqDLLGlobal.h"
#include <string.h>
#include <QFileInfo>
#include <QProcess>
#include "XDateTime.h"
#include "XGeneralFunc.h"


// Cross-platform function to get running process names using Qt
static bool GetProcessNames(QStringList &Processes)
{
	Processes.clear();
	QProcess process;

#ifdef Q_OS_WIN
	// Windows environment: use tasklist command
	process.start("tasklist", QStringList() << "/FO" << "CSV" << "/NH");
	process.waitForFinished();

	QString output = QString::fromLocal8Bit(process.readAllStandardOutput());
	QStringList lines = output.split("\n", Qt::SkipEmptyParts);

	for (const QString &line : lines) {
		QStringList tokens = line.split("\",\"");
		if (!tokens.isEmpty()) {
			QString name = tokens.first().remove("\"");
			Processes.append(name.trimmed());
		}
	}
#else
	// Linux/macOS environment: use ps command
	process.start("ps", QStringList() << "-e" << "-o" << "comm=");
	process.waitForFinished();

	QString output = QString::fromUtf8(process.readAllStandardOutput());
	QStringList lines = output.split("\n", Qt::SkipEmptyParts);

	for (const QString &line : lines) {
		Processes.append(line.trimmed());
	}
#endif

	return !Processes.isEmpty();
}

void	DLLSeq_GetDLLVersion(char *buff)
{
	strcpy(buff,"Check program to run");
}

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="CheckProgramRun";
	return true;
}

WORD		_cdecl	DLL_GetVersion(void)
//	return Light DLL version
{
	return 1;
}

bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString="Copyright(c) MEGATRADE 2007.9";
	return true;
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Check program to run";
}

DEFFUNCEX		void	DLLSeq_Close(void *handle)
{

}

bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr)
{
	if(cmdstr=="Check"){
		QString	Program=datastr;

		QStringList Processes;
		if(GetProcessNames(Processes)==true){
			for(int i=0;i<Processes.count();i++){
				if(Processes[i]==Program){
					return true;
				}
			}
		}
		return false;
	}
	return false;
}