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

#ifndef OUTPUTLOG_H
#define OUTPUTLOG_H

#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QThread>
#include <QTableWidget>
#include <QTextStream>
#include "outputlog_global.h"
#include "AllCheckedForm.h"
#include "UnloadCommentForm.h"
#include "PreAllCheckedForm.h"
#include "ErrorForm.h"
#include "OKCheckForm.h"
#include "MessageForm.h"

#define	DEFFUNCEX		__declspec(dllexport) 

//�v���Z�X�`�F�b�N�X���b�h
class ProcessCheckThread : public QThread
{
	Q_OBJECT

public:
	ProcessCheckThread();

	void Initial();
	void SetProcessName(QString ProcessName)	{	ProcessNameList.append(ProcessName);	}
	void FinModeOn()							{	FinMode=true;							}

signals:
	void SignalError(QString ProcessName);

protected:
	void run();

private:
	bool		FinMode;
	QStringList	ProcessNameList;
};

//NG�摜(JPEG)�ۑ��X���b�h
class NGImageSaveThread : public QThread
{
	Q_OBJECT

public:
	NGImageSaveThread();
	void SetParameter(QByteArray **Data[],int *NGI,int *Side,int *IDX,int *Index,QString *Name,int Count,QString *Time,QString *RealName);

//public slots:
//	void SlotAllCheckedFormClose();
//	void SlotUnloadCommentForm();
//	void SlotPreAllCheckedForm();
//	void SlotErrorForm();

signals:
	void SignalError(int Index);

protected:
	void run();

private:
	QList<QByteArray>	NGDataList[2];
	int		 			*iNGI;
	int				 	*iSide;
	int				 	*iIDX;
	int				 	*iIndex;
	QString				*KohenName;
	int					NGCount;
	QString				strTime;
	QString				*RealKohenName;

	QList<int>			NoNGImageRowList;
	bool				FirstComming;
};

typedef	struct	_NGInformation
{
	QString		NGNo;
	int 		PCNo;
	int 		TaiouKohenNumb;
	QString		X;
	QString		Y;
	QString		HanteiKekka;
	int 		TaiouKohenNo;
	QString		RealKohenNo;

}NGInformation;

typedef	struct	_KohenInformation
{
	QString					KohenNo;
	QString					KohenKekka;
	QList<NGInformation>	NGInfoList;
	int 					NGCount;

	_KohenInformation():KohenNo(/**/""),KohenKekka("OK"){}

}KohenInformation;

typedef	struct	_LogInformation
{
	QString				Hinsh;
	QString				Lot;
	QString				Jouge;
	QString				KibanNo;
	QString				UpdateTime;
	QStringList			HDNameList;
	int 				NGKohenNumb;
	int					NGNumb;
	KohenInformation	*KohenInfo;
	int					KohenNumb;
	QStringList			KohenNameList;	//""���܂�
	bool				IsOutputLog;

	_LogInformation():IsOutputLog(false),KohenInfo(NULL){}

}LogInformation;

static NGImageSaveThread	tNGImageSave;
static ProcessCheckThread	tProcessCheck;

extern	"C"{
DEFFUNCEX	bool	_cdecl	DLL_GetName					(QString &str);
DEFFUNCEX   void	_cdecl  DLL_SetLogInfo				(QString *Hinsh,QString *Lot,QString *Jouge,QStringList *HDNameList,QStringList *KohenNameList);
DEFFUNCEX   void	_cdecl  DLL_AppendNGInfo			(QString *KohenName,int NGNo,int PCNo,int TaiouKohenNumb,QString *X,QString *Y,QString HanteiKekka,QString *RealKohenName);
//DEFFUNCEX   int		_cdecl  DLL_OutputLog				(QString *KibanNo,int NGNumb,QStringList &NGKohenNoList);
DEFFUNCEX   int		_cdecl  DLL_OutputLog				(QString *KibanNo,int NGNumb,QStringList &NGKohenNoList,QTextStream &FileStream);
DEFFUNCEX	bool	_cdecl	DLL_IsOutputLog				(void);
DEFFUNCEX	void	_cdecl	DLL_SetIsOutputLog			(bool IsOutputLog);
DEFFUNCEX   void	_cdecl  DLL_RemoveNGInfo			(QString *KohenName);
DEFFUNCEX	int		_cdecl	DLL_AllCheckedFormShow		(QStringList &NGKohenNoList,QString LotName,bool &IsMaxOver);
DEFFUNCEX	void	_cdecl	DLL_AllCheckedFormClose		(void);
DEFFUNCEX	void	_cdecl	DLL_UnloadCommentFormShow	(void);
DEFFUNCEX	void	_cdecl	DLL_UnloadCommentFormClose	(void);
//DEFFUNCEX	bool	_cdecl	DLL_SaveNGImage				(QByteArray *NGDataList,QString *KohenName,int NGNo,QString *strTime);
//DEFFUNCEX	bool	_cdecl	DLL_SaveNGImage				(QByteArray **NGDataList[],int *NGI,int *Side,int *IDX,int *Index,QString *KohenName,int NGNo,QString *strTime);
DEFFUNCEX	bool	_cdecl	DLL_SaveNGImage				(QByteArray **NGDataList[],int *NGI,int *Side,int *IDX,int *Index,QString *KohenName,int NGNo,QString *strTime,QString *RealKohenName);
DEFFUNCEX	void	_cdecl	DLL_ClearNGInfoList			(void);
DEFFUNCEX	bool	_cdecl	DLL_PreNext					(bool IsBack);
//DEFFUNCEX	void	_cdecl	DLL_ErrorFormShow			(void);		//D-20091106
DEFFUNCEX	void	_cdecl	DLL_ErrorFormShow			(int Code);	//A-20091106
DEFFUNCEX	void	_cdecl	DLL_ErrorFormClose			(void);
DEFFUNCEX	void	_cdecl	DLL_OKCheckFormShow			(void);
DEFFUNCEX	void	_cdecl	DLL_OKCheckFormClose		(void);
DEFFUNCEX	QObject	*_cdecl	DLL_GetThreadInstance		(void);
DEFFUNCEX	bool	_cdecl	DLL_SaveLotNameFile			(QString &LotName);
DEFFUNCEX	bool	_cdecl	DLL_GetReviewEnable			(void);
DEFFUNCEX	void	_cdecl	DLL_SetReviewEnable			(bool Enable);
DEFFUNCEX	bool	_cdecl	DLL_IsAllCheckedFormShow	(void);
DEFFUNCEX	bool	_cdecl	DLL_IsUnloadCommentFormShow	(void);
DEFFUNCEX	bool	_cdecl	DLL_IsPreNext				(void);
DEFFUNCEX	bool	_cdecl	DLL_IsErrorFormShow			(void);
DEFFUNCEX	void	_cdecl	DLL_SetMessageFormLabel		(QString &Message);
DEFFUNCEX	void	_cdecl	DLL_SetMessageForm			(QColor &TextColor,QColor &BackgroundColor);
DEFFUNCEX	void	_cdecl	DLL_MessageFormShow			(bool BlinkEnable);
DEFFUNCEX	void	_cdecl	DLL_MessageFormClose		(void);
DEFFUNCEX	bool	_cdecl	DLL_SaveHistoryList			(QTableWidget *W,QStringList &HeaderList,bool IsFirst);
DEFFUNCEX	bool	_cdecl	DLL_GetShowPickupForm		(void);
DEFFUNCEX	bool	_cdecl	DLL_GetShowPickupEnable		(void);
DEFFUNCEX	void	_cdecl	DLL_SetShowPickupEnable		(bool Enable);
DEFFUNCEX   void	_cdecl  DLL_SetLogInfoHDNameList	(QStringList *HDNameList);
DEFFUNCEX   void	_cdecl  DLL_StartProcessCheckThread	(bool Enable);
DEFFUNCEX	QObject	*_cdecl	DLL_GetCheckThreadInstance	(void);

DEFFUNCEX	void	_cdecl	DLL_SetMMCSettingList		(QStringList &List);
DEFFUNCEX	bool	_cdecl	DLL_MMCSettingFormShow		(QStringList &List);
DEFFUNCEX	bool	_cdecl	DLL_GetShowOKMsg			(void);
DEFFUNCEX	bool	_cdecl	DLL_GetShowNGArea			(void);
DEFFUNCEX	int		_cdecl	DLL_GetPickupNGAreaNumbA	(void);
DEFFUNCEX	int		_cdecl	DLL_GetPickupNGAreaNumbB	(void);
DEFFUNCEX	int		_cdecl	DLL_GetPickupNGAreaNumbC	(void);
DEFFUNCEX	bool	_cdecl	DLL_GetNotShowEID			(void);
DEFFUNCEX	void	_cdecl	DLL_SetMMCParameter			(QTableWidget *W,QStringList &HeaderList);
DEFFUNCEX	bool	_cdecl	DLL_GetOKDoubleDone			(void);
DEFFUNCEX	bool	_cdecl	DLL_GetNGListControl		(void);

static AllCheckedForm		*ACForm		=NULL;
static UnloadCommentForm	*UCForm		=NULL;
static PreAllCheckedForm	*PreACForm	=NULL;
static ErrorForm			*ErrForm	=NULL;
static OKCheckForm			*OKChkForm	=NULL;
static MessageForm			*MsgForm	=NULL;

static bool					ReviewEnable=true;

static int	IsShowPickupEnable(QStringList &NGKohenNoList,int MaxNGAreaNumb);

static void	WriteDebugLogFile(const QString &WriteMsg,QTextStream &FileStream);	//�f�o�b�O���O�o��
};

#endif // OUTPUTLOG_H