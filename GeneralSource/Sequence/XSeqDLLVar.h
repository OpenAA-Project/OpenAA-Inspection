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

#if	!defined(XSeqDLLVar_h)
#define	XSeqDLLVar_h

#include <QString>
#include <QApplication>
#include "XDLLManager.h"
#include "XTypeDef.h"

class	GUIDirectMessage;
class	LayersBase;

class   DLLVarInterface : public DLLManager
{
public:
	WORD	(*DLL_GetDLLType)(void);
	bool	(*DLL_GetName)(QString &str);
	const char	*(*DLL_GetExplain)(void);
	WORD	(*DLL_GetVersion)(void);
	bool	(*DLL_CheckCopyright)(QString &CopyrightString);

    void	( *LGetDLLVersion)(char *buff);
	void *( *DLLInitial)(LayersBase *Base ,const QString &param);
    bool ( *DLLCmd)			(void *handle ,QApplication &,const QString &cmd);
    bool ( *DLLCmdStr)		(void *handle ,QApplication &,const QString &cmd ,const QByteArray &datastr);
    bool ( *DLLCmdStrInt)	(void *handle ,QApplication &,const QString &cmd ,const QByteArray &datastr,int *datastr2);
    bool ( *DLLCmdStrRet)	(void *handle ,QApplication &,const QString &cmd ,const QByteArray &datastr ,QByteArray &Buff);
    bool ( *DLLCmdStrRetInt)(void *handle ,QApplication &,const QString &cmd ,const QByteArray &datastr ,QByteArray &Buff ,int *datastr2);
    bool ( *DLLCmdInt)		(void *handle ,QApplication &,const QString &cmd ,int *datastr);
    bool ( *DLLCmdFloat)	(void *handle ,QApplication &,const QString &cmd ,double *datastr);
    bool ( *DLLCmdInt2)		(void *handle ,QApplication &,const QString &cmd ,int *datastr1,int *datastr2);
    bool ( *DLLCmdInt3)		(void *handle ,QApplication &,const QString &cmd ,int *datastr1,int *datastr2,int *datastr3);
    bool ( *DLLCmdInt4)		(void *handle ,QApplication &,const QString &cmd ,int *datastr1,int *datastr2,int *datastr3,int *datastr4);
    void ( *DLLClose)		(void *handle);
    void ( *DLLDebugShow)	(void *handle ,QApplication &);
	void ( *DLL_TransmitDirectly)(void *handle ,GUIDirectMessage *packet);
	QLibrary 	DllLib;
	void		*Handle;
  public:
    QString  FileName;
	QString  Param;

    QString  Data;
    QString  VersionStr;


    DLLVarInterface(void);
    ~DLLVarInterface(void);

	bool	IsDLLVarDLL(void)	const;
	bool	LoadDLL(LayersBase *base ,const QString &filename);
    QString	GetDLLVarName(void)	const;
    virtual	void	GetExportFunctions(QStringList &Str)	override;
    
	QString	GetFileName(void)	const;
	void	SetFileName(const QString filename);
	void	SetParam(const QString &param);
	
	QString	GetCopyright(void)	const;
	WORD	GetVersion(void)	const;
	WORD	GetDLLType(void)	const;
	const QString	GetExplain(void)	const;
	
	bool    OpenInitialize(LayersBase *base);
	bool    IsDebugMode(void)	const;
	void    DLLDebug(QApplication *app);
	
	void	TransmitDirectly(GUIDirectMessage *packet);

};



#endif