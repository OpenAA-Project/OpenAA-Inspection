/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\OutputLog\OutputLog.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "OutputLog.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>
//#include <QMessageBox>
#include <QDir>
#include <QTextCodec>
#include <QTableWidget>
#include <QHeaderView>
#include "MMCSettingForm.h"
#include "XCSV.h"
#include "XForWindows.h"

//#define Debug

static	LogInformation LogInfo;
static	LogInformation wLogInfo;

bool	FlagShowOKMsg		=true;
bool	FlagShowNGArea		=true;
int		PickupNGAreaNumbA	=5;
int		PickupNGAreaNumbB	=3;
int		PickupNGAreaNumbC	=4;
bool	FlagNotShowEID		=true;
bool	FlagShowPickupForm	=true;
QString	LogSaveDirectory	=/**/"";
bool	ShowPickupEnable	=false;
bool	FlagOKDoubleDone	=false;
bool	ShowMaxOverEnable	=false;
bool	FlagNGListControl	=false;
QString	LogOutputDirectory	="D:/";

bool	DLL_GetName(QString &str)
{
	str="Output log for MMC";
	return true;
}

void	DLL_SetLogInfo(QString *Hinsh,QString *Lot,QString *Jouge,QStringList *HDNameList,QStringList *KohenNameList)
{
	//スレッドが走っている場合は待たす
	while(tNGImageSave.isRunning()==true){}

	LogInfo.Hinsh			=*Hinsh;
	LogInfo.Lot				=*Lot;
	LogInfo.Jouge			=*Jouge;
	LogInfo.HDNameList		=*HDNameList;
	if(LogInfo.KohenInfo!=NULL){
		delete []LogInfo.KohenInfo;
	}
	LogInfo.KohenInfo		=new KohenInformation[KohenNameList->count()];
	LogInfo.KohenNumb		=KohenNameList->count();
	qSort(*KohenNameList);
	LogInfo.KohenNameList	=*KohenNameList;
	for(int i=0;i<LogInfo.KohenNumb;i++)
		LogInfo.KohenInfo[i].KohenNo=KohenNameList->at(i);	//個片名称はXMLで記述される「個片情報データ」から取得する
}

void	DLL_AppendNGInfo(QString *KohenName,int NGNo,int PCNo,int TaiouKohenNumb,QString *X,QString *Y,QString HanteiKekka,QString *RealKohenName)
{
	NGInformation NGInfo;
	NGInfo.NGNo				=QString::number(NGNo+1);
	if(PCNo<3){
		NGInfo.PCNo			=1;
	}
	else{
		NGInfo.PCNo			=2;
	}
//	NGInfo.TaiouKohenNumb	=TaiouKohenNumb;
//	NGInfo.TaiouKohenNumb	=KohenName->count(',')+1;
	NGInfo.TaiouKohenNumb	=RealKohenName->count(',')+1;
	NGInfo.X				=*X;
	NGInfo.Y				=*Y;
	NGInfo.HanteiKekka		=HanteiKekka;
	NGInfo.RealKohenNo		=*RealKohenName;

	if(LogInfo.KohenNumb==0){
		return;
	}

	QStringList KohenNameList=KohenName->split(',');
//	for(int i=0;i<NGInfo.TaiouKohenNumb;i++){
	for(int i=0;i<KohenNameList.count();i++){
		int KohenNo=LogInfo.KohenNameList.indexOf(KohenNameList[i]);	//個片名称（QList）のindexで取得する
		if(KohenNo<0){
			continue;
		}
		NGInfo.TaiouKohenNo=i;
		LogInfo.KohenInfo[KohenNo].NGInfoList.append(NGInfo);
	}
}

//int DLL_OutputLog(QString *KibanNo,int NGNumb,QStringList &NGKohenNoList)
int DLL_OutputLog(QString *KibanNo,int NGNumb,QStringList &NGKohenNoList,QTextStream &FileStream)
{
	LogInfo.KibanNo			=KibanNo->rightJustified(4,'0');
	LogInfo.NGNumb			=NGNumb;

	//デバッグログ出力
	WriteDebugLogFile(LogInfo.KibanNo + " DLL_OutputLog() start.(In DLL)",FileStream);

	//保存先の設定
	QString strDate=QDateTime::currentDateTime().toString("yyyyMMdd");
//	QString strPath="D:/"
	QString LogOutputDir=LogOutputDirectory;
	if(LogOutputDirectory.right(1)!="/"){
		LogOutputDir+="/";
	}
	QString strPath=LogOutputDirectory
					+ strDate
					+ "/"
					+ LogInfo.Lot
					+ "/"
					+ LogInfo.KibanNo
					+ "/";

	//保存先のフォルダが無ければ作る
	char delim = '/';
	QStringList dirs = (strPath).split(delim, QString::SkipEmptyParts);
	QDir dir(dirs[0] + delim);
	for(int i=1; i<dirs.count(); i++){
		if(!dir.exists(dirs[i])){
			if(!dir.mkdir(dirs[i]))
				return -1;
		}
		if(!dir.cd(dirs[i]))
			return -1;
	}

	//ログデータ（個片毎）のセット
	int NGKohenNumb=0;
	for(int i=0;i<LogInfo.KohenNumb;i++){
		QString KohenKekka="OK";
		int NGCount=LogInfo.KohenInfo[i].NGInfoList.count();
		for(int j=0;j<NGCount;j++){
			if(LogInfo.KohenInfo[i].NGInfoList[j].RealKohenNo==/**/""){
				continue;
			}
			QString HanteiKekka=LogInfo.KohenInfo[i].NGInfoList[j].HanteiKekka;
			if(HanteiKekka=="NG"){
				QStringList RealKohenNameList=LogInfo.KohenInfo[i].NGInfoList[j].RealKohenNo.split(',');
				for(int k=0;k<RealKohenNameList.count();k++){
					if(NGKohenNoList.contains(RealKohenNameList[k])==true){
						continue;
					}
					KohenKekka="NG";
					NGKohenNumb++;
//					NGKohenNoList.append(LogInfo.KohenInfo[i].KohenNo);
					NGKohenNoList.append(RealKohenNameList[k]);
//					break;
					int No=LogInfo.KohenNameList.indexOf(RealKohenNameList[k]);	//個片名称（QList）のindexで取得する
					if(No>=0){
						LogInfo.KohenInfo[No].KohenKekka=KohenKekka;
					}
				}
			}
		}
//		LogInfo.KohenInfo[i].KohenKekka=KohenKekka;
	}
	LogInfo.NGKohenNumb=NGKohenNumb;

	//MaxOver対応
	for(int i=0;i<LogInfo.KohenNumb;i++){
		int NGCount=LogInfo.KohenInfo[i].NGInfoList.count();
		if(NGCount==0){
			continue;
		}
		QString HanteiKekka=LogInfo.KohenInfo[i].NGInfoList[0].HanteiKekka;
		if(HanteiKekka=="MaxOver"){
			QString KohenKekka="-";
			for(int j=0;j<LogInfo.KohenNumb;j++){
				LogInfo.KohenInfo[j].KohenKekka=KohenKekka;
			}
		}
		break;
	}

	//保存ファイル名の設定
	QString strTime=QDateTime::currentDateTime().toString("hhmmss");
	strPath+=LogInfo.Lot
			+ "_"
			+ LogInfo.Jouge
			+ "_"
			+ LogInfo.KibanNo
			+ "_"
			+ strTime
			+ ".csv";

	QFile	mfile(strPath);
	if(mfile.open(QIODevice::WriteOnly)==true){
		QTextStream mystream(&mfile);
//		mystream.setCodec(QTextCodec::codecForName("Shift-JIS"));
		QTextCodec *code=QTextCodec::codecForName (/**/"Shift-JIS");
		mystream << code->toUnicode("品種,")		<< LogInfo.Hinsh					<< "\n";
		mystream << code->toUnicode("ロット番号,")	<< LogInfo.Lot						<< "\n";
		mystream << code->toUnicode("上下,")		<< LogInfo.Jouge					<< "\n";
		mystream << code->toUnicode("基板番号,")	<< LogInfo.KibanNo					<< "\n";
		mystream << code->toUnicode("保存年月日,")	<< strDate							<< "\n";
		mystream << code->toUnicode("保存時刻,")	<< strTime							<< "\n";
		mystream << code->toUnicode("HD名");
		QString strHDName;
		if(LogInfo.HDNameList.count()>0){
			//HD名は"HD_xx-A～D"で、後ろが-A～Dならその部分を削除する
			QString strHDNameRight2=LogInfo.HDNameList[0].right(2);
			if(strHDNameRight2=="-A" || strHDNameRight2=="-B" || strHDNameRight2=="-C" || strHDNameRight2=="-D"){
				strHDName=LogInfo.HDNameList[0].left(LogInfo.HDNameList[0].length()-2);
				mystream << ","	 << strHDName;
			}
			else{
				strHDName=LogInfo.HDNameList[0];
				mystream << ","	 << LogInfo.HDNameList[0];
			}
		}
		for(int i=1;i<LogInfo.HDNameList.count();i++){
			QString wstrHDName;
			QString strHDNameRight2=LogInfo.HDNameList[i].right(2);
			if(strHDNameRight2=="-A" || strHDNameRight2=="-B" || strHDNameRight2=="-C" || strHDNameRight2=="-D"){
				wstrHDName=LogInfo.HDNameList[i].left(LogInfo.HDNameList[i].length()-2);
			}
			else{
				wstrHDName=LogInfo.HDNameList[i];
			}
			if(strHDName!=wstrHDName){
				mystream << ","	<< wstrHDName;
			}
		}
		mystream << "\n";
		mystream << code->toUnicode("NG個片数,")	<< LogInfo.NGKohenNumb				<< "\n";
		mystream << code->toUnicode("キズ候補数,")	<< QString::number(LogInfo.NGNumb)	<< "\n";
		mystream << code->toUnicode("個片番号");
		for(int i=0;i<LogInfo.KohenNumb;i++){
			if(LogInfo.KohenInfo[i].KohenNo==/**/"")
				continue;
			mystream << ","	<< LogInfo.KohenInfo[i].KohenNo;
		}
		mystream << "\n";
		mystream << code->toUnicode("個片結果");
		for(int i=0;i<LogInfo.KohenNumb;i++){
			if(LogInfo.KohenInfo[i].KohenNo==/**/"")
				continue;
			mystream << ","	<< LogInfo.KohenInfo[i].KohenKekka;
		}
		mystream << "\n";
		mystream << code->toUnicode("候補番号");
		int SumNG=0;
		for(int i=0;i<LogInfo.KohenNumb;i++){
			int j;
			int NGInfoListCnt=LogInfo.KohenInfo[i].NGInfoList.count();
//			int TaiouKohenCnt=0;
			for(j=0;j<NGInfoListCnt;j++){
				//保存NGは最大999個
//				if(LogInfo.KohenInfo[i].NGInfoList[j].NGNo.toInt()>999)
				if((SumNG+j+1)>999){
					break;
				}
				if(LogInfo.KohenInfo[i].NGInfoList[j].TaiouKohenNo>0){
//					TaiouKohenCnt++;
					continue;
				}
				mystream << ","	<< LogInfo.KohenInfo[i].NGInfoList[j].NGNo;
			}
//			//重複を含まないNGデータ数をカウントしておく
//			LogInfo.KohenInfo[i].NGCount=NGInfoListCnt-TaiouKohenCnt;

			//保存NGは最大999個
			if(j!=NGInfoListCnt){
				break;
			}
			SumNG+=NGInfoListCnt;
		}
		mystream << "\n";
		mystream << code->toUnicode("ＰＣ");
		for(int i=0;i<LogInfo.KohenNumb;i++){
			for(int j=0;j<LogInfo.KohenInfo[i].NGInfoList.count();j++){
				if(LogInfo.KohenInfo[i].NGInfoList[j].TaiouKohenNo>0){
					continue;
				}
				mystream << ","	<< LogInfo.KohenInfo[i].NGInfoList[j].PCNo;
			}
		}
		mystream << "\n";
		mystream << code->toUnicode("対応個片数");
		for(int i=0;i<LogInfo.KohenNumb;i++){
			for(int j=0;j<LogInfo.KohenInfo[i].NGInfoList.count();j++){
				if(LogInfo.KohenInfo[i].NGInfoList[j].TaiouKohenNo>0){
					continue;
				}
				mystream << ","	<< LogInfo.KohenInfo[i].NGInfoList[j].TaiouKohenNumb;
			}
		}
		mystream << "\n";
		mystream << code->toUnicode("候補座標Ｘ");
		for(int i=0;i<LogInfo.KohenNumb;i++){
			for(int j=0;j<LogInfo.KohenInfo[i].NGInfoList.count();j++){
				if(LogInfo.KohenInfo[i].NGInfoList[j].TaiouKohenNo>0){
					continue;
				}
				mystream << ","	<< LogInfo.KohenInfo[i].NGInfoList[j].X;
			}
		}
		mystream << "\n";
		mystream << code->toUnicode("候補座標Ｙ");
		for(int i=0;i<LogInfo.KohenNumb;i++){
			for(int j=0;j<LogInfo.KohenInfo[i].NGInfoList.count();j++){
				if(LogInfo.KohenInfo[i].NGInfoList[j].TaiouKohenNo>0){
					continue;
				}
				mystream << ","	<< LogInfo.KohenInfo[i].NGInfoList[j].Y;
			}
		}
		mystream << "\n";
		mystream << code->toUnicode("判定結果");
		for(int i=0;i<LogInfo.KohenNumb;i++){
			for(int j=0;j<LogInfo.KohenInfo[i].NGInfoList.count();j++){
				if(LogInfo.KohenInfo[i].NGInfoList[j].TaiouKohenNo>0){
					continue;
				}
				mystream << ","	<< LogInfo.KohenInfo[i].NGInfoList[j].HanteiKekka;
			}
		}
		mystream << "\n";
		mfile.close();
	}
	else{
		WriteDebugLogFile(LogInfo.KibanNo + " DLL_OutputLog() mfile.open(QIODevice::WriteOnly) false.(In DLL)",FileStream);
		return -1;
	}
	LogInfo.IsOutputLog=true;

	//デバッグログ出力
	WriteDebugLogFile(LogInfo.KibanNo + " DLL_OutputLog() end.(In DLL)",FileStream);
	return NGKohenNumb;
}

bool	DLL_IsOutputLog(void)
{
	return LogInfo.IsOutputLog;
}

void	DLL_SetIsOutputLog(bool IsOutputLog)
{
	LogInfo.IsOutputLog=IsOutputLog;
}

void	DLL_RemoveNGInfo(QString *KohenName)
{
	QStringList KohenNameList=KohenName->split(',');
	for(int i=0;i<KohenNameList.count();i++){
		int KohenNo=LogInfo.KohenNameList.indexOf(KohenNameList[i]);	//個片名称（QList）のindexで取得する
		if(KohenNo<0){
			continue;
		}
		if(LogInfo.KohenInfo[KohenNo].NGInfoList.count()==0){
			continue;
		}
		LogInfo.KohenInfo[KohenNo].NGInfoList.removeLast();
	}
}

int	DLL_AllCheckedFormShow(QStringList &NGKohenNoList,QString LotName,bool &IsMaxOver)
{
	if(ACForm==NULL){
		ACForm=new AllCheckedForm();
	}

	//戻り値（OKかNGか）
	int Result=0;

	//抜き取り判断
	ShowMaxOverEnable=false;
	ShowPickupEnable=false;

	//品種A
	if(LotName=="A"){
		if(LogInfo.Jouge=="B"){
			//上流の場合の処理
			if(IsMaxOver==true){
				if(FlagShowPickupForm==true){
					//MaxOver表示
					ACForm->SetShowMaxOverEnable(LogInfo.KibanNo);
					ShowMaxOverEnable=true;
				}
				Result=1;
			}
			else if(NGKohenNoList.count()>=PickupNGAreaNumbA){
				if(FlagShowPickupForm==true){
					//抜き取り表示
					ACForm->SetShowPickupEnable(LogInfo.KibanNo);
					ShowPickupEnable=true;
				}
				Result=1;
			}
		}
		else if(LogInfo.Jouge=="F"){
			//下流の場合の処理
			int Ret;
			if((Ret=IsShowPickupEnable(NGKohenNoList,PickupNGAreaNumbA))==2 || IsMaxOver==true){
				if(FlagShowPickupForm==true){
					//MaxOver表示
					ACForm->SetShowMaxOverEnable(LogInfo.KibanNo);
					ShowMaxOverEnable=true;
				}
				Result=1;
			}
			else if(Ret==1){
				if(FlagShowPickupForm==true){
					//抜き取り表示
					ACForm->SetShowPickupEnable(LogInfo.KibanNo);
					ShowPickupEnable=true;
				}
				Result=1;
			}
		}
	}
	//品種B
	else if(LotName=="B"){
		if(LogInfo.Jouge=="B"){
			//上流の場合の処理
			if(IsMaxOver==true){
				if(FlagShowPickupForm==true){
					//MaxOver表示
					ACForm->SetShowMaxOverEnable(LogInfo.KibanNo);
					ShowMaxOverEnable=true;
				}
				Result=1;
			}
			else if(NGKohenNoList.count()>=PickupNGAreaNumbB){
				if(FlagShowPickupForm==true){
					//抜き取り表示
					ACForm->SetShowPickupEnable(LogInfo.KibanNo);
					ShowPickupEnable=true;
				}
				Result=1;
			}
		}
		else if(LogInfo.Jouge=="F"){
			//下流の場合の処理
			int Ret;
			if((Ret=IsShowPickupEnable(NGKohenNoList,PickupNGAreaNumbB))==2 || IsMaxOver==true){
				if(FlagShowPickupForm==true){
					//MaxOver表示
					ACForm->SetShowMaxOverEnable(LogInfo.KibanNo);
					ShowMaxOverEnable=true;
				}
				Result=1;
			}
			else if(Ret==1){
				if(FlagShowPickupForm==true){
					//抜き取り表示
					ACForm->SetShowPickupEnable(LogInfo.KibanNo);
					ShowPickupEnable=true;
				}
				Result=1;
			}
		}
	}
	//品種C
	else if(LotName=="C"){
		if(LogInfo.Jouge=="B"){
			//上流の場合の処理
			if(IsMaxOver==true){
				if(FlagShowPickupForm==true){
					//MaxOver表示
					ACForm->SetShowMaxOverEnable(LogInfo.KibanNo);
					ShowMaxOverEnable=true;
				}
				Result=1;
			}
			else if(NGKohenNoList.count()>=PickupNGAreaNumbC){
				if(FlagShowPickupForm==true){
					//抜き取り表示
					ACForm->SetShowPickupEnable(LogInfo.KibanNo);
					ShowPickupEnable=true;
				}
				Result=1;
			}
		}
		else if(LogInfo.Jouge=="F"){
			//下流の場合の処理
			int Ret;
			if((Ret=IsShowPickupEnable(NGKohenNoList,PickupNGAreaNumbC))==2 || IsMaxOver==true){
				if(FlagShowPickupForm==true){
					//MaxOver表示
					ACForm->SetShowMaxOverEnable(LogInfo.KibanNo);
					ShowMaxOverEnable=true;
				}
				Result=1;
			}
			else if(Ret==1){
				if(FlagShowPickupForm==true){
					//抜き取り表示
					ACForm->SetShowPickupEnable(LogInfo.KibanNo);
					ShowPickupEnable=true;
				}
				Result=1;
			}
		}
	}

	ACForm->show();
	return Result;
}

void	DLL_AllCheckedFormClose(void)
{
	if(ACForm==NULL){
		return;
	}
	ACForm->close();
	delete ACForm;
	ACForm=NULL;
}

void	DLL_UnloadCommentFormShow(void)
{
	if(UCForm==NULL){
		UCForm=new UnloadCommentForm();
	}
	if(ShowMaxOverEnable==true){
		UCForm->SetShowMaxOverEnable(LogInfo.KibanNo);
	}
	else if(ShowPickupEnable==true){
		UCForm->SetShowPickupEnable(LogInfo.KibanNo);
	}
	UCForm->show();
}

void	DLL_UnloadCommentFormClose(void)
{
	if(UCForm==NULL){
		return;
	}
	UCForm->close();
	delete UCForm;
	UCForm=NULL;
}

bool	DLL_SaveNGImage(QByteArray **NGDataList[],int *NGI,int *Side,int *IDX,int *Index,QString *KohenName,int NGCount,QString *strTime,QString *RealKohenName)
{
	//スレッドが走っている場合は待たす
	while(tNGImageSave.isRunning()==true){}

	tNGImageSave.SetParameter(NGDataList,NGI,Side,IDX,Index,KohenName,NGCount,strTime,RealKohenName);
	tNGImageSave.start();
	return true;
}

void	DLL_ClearNGInfoList(void)
{
	//スレッドが走っている場合は待たす
	while(tNGImageSave.isRunning()==true){}

	//clear
	for(int i=0;i<LogInfo.KohenNumb;i++)
		LogInfo.KohenInfo[i].NGInfoList.clear();
}

bool	DLL_PreNext(bool IsBack)
{
	if(PreACForm!=NULL){
		PreACForm->close();
		delete PreACForm;
		PreACForm=NULL;
		if(IsBack==true){
			return true;
		}
		return false;
	}
	else{
		if(IsBack==true){
			return false;
		}
		PreACForm=new PreAllCheckedForm();
		if(FlagOKDoubleDone==true){
			PreACForm->ui.lbMessage_3->setText("これで良い場合は「OK」ボタンを２回押して下さい。");	//とりあえず日本語で表示させる
		}
		else{
			PreACForm->ui.lbMessage_3->setText("これで良い場合は「OK」ボタンを押して下さい。");	//とりあえず日本語で表示させる
		}
		PreACForm->show();
		return true;
	}
}

//void	DLL_ErrorFormShow(void)		//D-20091106
void	DLL_ErrorFormShow(int Code)	//A-20091106
{
	if(ErrForm==NULL){
//		ErrForm=new ErrorForm(LogInfo.KibanNo);			//D-20091106
		ErrForm=new ErrorForm(LogInfo.KibanNo,Code);	//A-20091106
	}
	else{
		return;
	}
	ErrForm->show();
}

void	DLL_ErrorFormClose(void)
{
	if(ErrForm==NULL){
		return;
	}
	ErrForm->close();
	delete ErrForm;
	ErrForm=NULL;
}

void	DLL_OKCheckFormShow(void)
{
	if(OKChkForm==NULL){
		OKChkForm=new OKCheckForm();
	}
	else{
		return;
	}
	OKChkForm->show();
}

void	DLL_OKCheckFormClose(void)
{
	if(OKChkForm==NULL){
		return;
	}
	OKChkForm->close();
	delete OKChkForm;
	OKChkForm=NULL;
}

QObject	*DLL_GetThreadInstance(void)
{
	return &tNGImageSave;
}

bool	DLL_SaveLotNameFile(QString &LotName)
{
	//保存先の設定
//	QString strPath="D:/LotNameFile.txt";
	QString LogOutputDir=LogOutputDirectory;
	if(LogOutputDirectory.right(1)!="/"){
		LogOutputDir+="/";
	}
	QString strPath = LogOutputDir
					+ "LotNameFile.txt";

	QFile	mfile(strPath);
	if(mfile.open(QIODevice::WriteOnly)==true){
		QTextStream mystream(&mfile);
		mystream << LotName;
		mfile.close();
		return true;
	}
	return false;
}

bool	DLL_GetReviewEnable(void)
{
	return ReviewEnable;
}

void	DLL_SetReviewEnable(bool Enable)
{
	ReviewEnable=Enable;
}

bool	DLL_IsAllCheckedFormShow(void)
{
	if(ACForm==NULL){
		return false;
	}
	return true;
}

bool	DLL_IsUnloadCommentFormShow(void)
{
	if(UCForm==NULL){
		return false;
	}
	return true;
}

bool	DLL_IsPreNext(void)
{
	if(PreACForm==NULL){
		return false;
	}
	return true;
}

bool	DLL_IsErrorFormShow(void)
{
	if(ErrForm==NULL){
		return false;
	}
	return true;
}

void	DLL_SetMessageFormLabel(QString &Message)
{
	if(MsgForm==NULL){
		MsgForm=new MessageForm();
	}
	MsgForm->ui.lbMessage->setText(Message);
}

void	DLL_SetMessageForm(QColor &TextColor,QColor &BackgroundColor)
{
	if(MsgForm==NULL){
		MsgForm=new MessageForm();
	}
	QPalette palette;
	palette.setColor(QPalette::WindowText,TextColor);
	MsgForm->ui.lbMessage->setPalette(palette);
	MsgForm->palette[0].setColor(QPalette::Window,BackgroundColor);
	MsgForm->setPalette(MsgForm->palette[0]);
}

void	DLL_MessageFormShow(bool BlinkEnable)
{
	if(MsgForm==NULL){
		MsgForm=new MessageForm();
	}
	if(BlinkEnable==true){
		MsgForm->SetBlink();
	}
	MsgForm->show();
}

void	DLL_MessageFormClose(void)
{
	if(MsgForm==NULL){
		return;
	}
	MsgForm->close();
	delete MsgForm;
	MsgForm=NULL;
}

bool	DLL_SaveHistoryList(QTableWidget *W,QStringList &HeaderList,bool IsFirst)
{
	//リストが空の場合は何もしない
	if(W->rowCount()==0){
		return true;
	}

	//保存先の設定
//	QString strPath="D:/";
	QString strPath=LogOutputDirectory;
	if(LogOutputDirectory.right(1)!="/"){
		strPath+="/";
	}

/*	//HistoryListのフォルダを作成しておく
	QDir dir(strPath);
	if(!dir.exists("HistoryList")){
		if(!dir.mkdir("HistoryList")){
			return false;
		}
	}
*/
	//保存ファイル名の設定
	strPath+=LogInfo.Lot + "_HistoryList.csv";
//	strPath+="HistoryList/" + LogInfo.Lot + "_HistoryList.csv";

	QFile	mfile(strPath);
	if(mfile.open(QIODevice::Append)==true){
		QTextStream mystream(&mfile);

		QString HeaderTitle=",INM,EID,TIM,NGP,NG Area";
		if(IsFirst==true){
			//ヘッダータイトル
			mystream << HeaderTitle;
			mystream << "\n";
		}
		else{
			//リストデータ（最新の１行）
			QStringList HeaderTitleList=HeaderTitle.split(",");
			int ColCnt=HeaderTitleList.count();
			QTableWidgetItem *Item;
			for(int Col=0;Col<ColCnt;Col++){
				if(Col==0){
					if((Item=W->verticalHeaderItem(0))!=NULL){
						mystream << Item->text();
					}
				}
				else if((Item=W->item(0,HeaderList.indexOf(HeaderTitleList[Col])))!=NULL){
					mystream << ",";
					mystream << Item->text();
				}
			}
			mystream << "\n";
		}
		mfile.close();
		return true;
	}
	return false;
}

bool	DLL_GetShowPickupForm(void)
{
	return FlagShowPickupForm;
}

bool	DLL_GetShowPickupEnable(void)
{
	return ShowPickupEnable;
}

void	DLL_SetShowPickupEnable(bool Enable)
{
	ShowPickupEnable=Enable;
}

void	DLL_SetLogInfoHDNameList(QStringList *HDNameList)
{
	LogInfo.HDNameList=*HDNameList;
}

void	DLL_StartProcessCheckThread(bool Enable)
{
	if(Enable==true){
		tProcessCheck.Initial();
		tProcessCheck.SetProcessName("Messager.exe");
		tProcessCheck.SetProcessName("LogCheckInReview.exe");
		while(tProcessCheck.isRunning()==true){}
		tProcessCheck.start();
	}
	else{
		tProcessCheck.FinModeOn();
	}
}

QObject	*DLL_GetCheckThreadInstance(void)
{
	return &tProcessCheck;
}

void	DLL_SetMMCSettingList(QStringList &List)
{
	for(int Cnt=0;Cnt<List.count();Cnt++){
		switch(Cnt){
			case 0:
				FlagShowOKMsg=List.at(Cnt).toInt();			//Show OK Message
				break;
			case 1:
				FlagShowNGArea=List.at(Cnt).toInt();		//Show NG Area
				break;
			case 2:
				PickupNGAreaNumbA=List.at(Cnt).toInt();		//Max NG Area Number A
				break;
			case 3:
				PickupNGAreaNumbB=List.at(Cnt).toInt();		//Max NG Area Number B
				break;
			case 4:
				PickupNGAreaNumbC=List.at(Cnt).toInt();		//Max NG Area Number C
				break;
			case 5:
				FlagNotShowEID=List.at(Cnt).toInt();		//Not Show EID
				break;
			case 6:
				FlagShowPickupForm=List.at(Cnt).toInt();	//Show Pickup Form
				break;
			case 7:
				LogSaveDirectory=List.at(Cnt);				//Log Save Directory
				break;
			case 8:
				FlagOKDoubleDone=List.at(Cnt).toInt();		//OK Double Done
				break;
			case 9:
				FlagNGListControl=List.at(Cnt).toInt();		//NG List Control
				break;
			case 10:
				LogOutputDirectory=List.at(Cnt);			//Log Output Directory
				break;
		}
	}
}

bool	DLL_MMCSettingFormShow(QStringList &List)
{
	MMCSettingForm SettingForm;
	if(!SettingForm.exec()){
		return false;
	}
	List << QString::number(FlagShowOKMsg);			//Show OK Message
	List << QString::number(FlagShowNGArea);		//Show NG Area at History List
	List << QString::number(PickupNGAreaNumbA);		//Max NG Area Number A
	List << QString::number(PickupNGAreaNumbB);		//Max NG Area Number B
	List << QString::number(PickupNGAreaNumbC);		//Max NG Area Number C
	List << QString::number(FlagNotShowEID);		//Not Show EID at History List
	List << QString::number(FlagShowPickupForm);	//Show Pickup Form
	List << LogSaveDirectory;						//Log Save Directory
	List << QString::number(FlagOKDoubleDone);		//OK Double Done
	List << QString::number(FlagNGListControl);		//NG List Control
	List << LogOutputDirectory;						//Log Output Directory
	return true;
}

bool	DLL_GetShowOKMsg(void)
{
	return FlagShowOKMsg;
}

bool	DLL_GetShowNGArea(void)
{
	return FlagShowNGArea;
}

int		DLL_GetPickupNGAreaNumbA(void)
{
	return PickupNGAreaNumbA;
}

int		DLL_GetPickupNGAreaNumbB(void)
{
	return PickupNGAreaNumbB;
}

int		DLL_GetPickupNGAreaNumbC(void)
{
	return PickupNGAreaNumbC;
}

bool	DLL_GetNotShowEID(void)
{
	return FlagNotShowEID;
}

void	DLL_SetMMCParameter(QTableWidget *W,QStringList &HeaderList)
{
	if(FlagShowNGArea==true){
		W->showColumn(HeaderList.indexOf("NG Area"));
		W->horizontalHeader()->setSectionResizeMode(HeaderList.indexOf("TIM"),QHeaderView::Interactive);
		W->setColumnWidth(HeaderList.indexOf("TIM"),60);
	}
	else{
		W->hideColumn(HeaderList.indexOf("NG Area"));
		W->horizontalHeader()->setSectionResizeMode(HeaderList.indexOf("TIM"),QHeaderView::Stretch);
	}
	if(FlagNotShowEID==true){
		W->hideColumn(HeaderList.indexOf("EID"));
	}
	else{
		W->showColumn(HeaderList.indexOf("EID"));
	}
}

bool	DLL_GetOKDoubleDone(void)
{
	return FlagOKDoubleDone;
}

bool	DLL_GetNGListControl(void)
{
	return FlagNGListControl;
}

int	IsShowPickupEnable(QStringList &NGKohenNoList,int MaxNGAreaNumb)
{
	//上流側のログデータ(csv)を検索して、NGの個片を調べる
	char delim = '/';
	QDir dir(LogSaveDirectory + delim);
	QString	SearchDate="????????";	//20090210
	QStringList DateFilters(SearchDate);
	QStringList DateList=dir.entryList(DateFilters,QDir::Dirs,QDir::Time);
	for(int i=0;i<DateList.count();i++){
		QString FileDirectory=LogSaveDirectory + delim + DateList[i] + delim + LogInfo.Lot + delim + LogInfo.KibanNo + delim;
		QString	SearchFile=LogInfo.Lot + "_B_" + LogInfo.KibanNo + "_*.csv";
		QStringList nameFilters(SearchFile);
		QStringList FileList=QDir(FileDirectory).entryList(nameFilters,QDir::Files,QDir::Time);
		if(FileList.count()==0){
			continue;
		}
		QString FilePath=FileDirectory + FileList[0];

		//QStringListListCSVクラスを使用してcsvファイルを読込む
		QStringListListCSV CSV;
		if(CSV.LoadFromCSVFile(FilePath)==true){
			//MaxOverかどうかの判定をする
			if(CSV[16].count()>1){
				if((CSV[16])[1]=="MaxOver"){
					return 2;
				}
			}
			for(int j=1;j<CSV[9].count();j++){
				if((CSV[10])[j]=="NG"){
					if(NGKohenNoList.contains((CSV[9])[j])==false){
						NGKohenNoList.append((CSV[9])[j]);
					}
				}
			}
		}
		else{
			return -1;
		}
		break;
	}

	if(NGKohenNoList.count()>=MaxNGAreaNumb){
		return 1;
	}
	return 0;
}

void WriteDebugLogFile(const QString &WriteMsg,QTextStream &FileStream)
{
	FileStream << QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ss.zzz : ") << WriteMsg << endl;
}

NGImageSaveThread::NGImageSaveThread()
{
}

void NGImageSaveThread::SetParameter(QByteArray **Data[],int *NGI,int *Side,int *IDX,int *Index,QString *Name,int Count,QString *Time,QString *RealName)
{
//	NGDataList		=Data;
	iNGI			=NGI;
	iSide			=Side;
	iIDX			=IDX;
	iIndex			=Index;
	KohenName		=Name;
	NGCount			=Count;
	strTime			=*Time;
	RealKohenName	=RealName;

	//LogInfoの退避
	wLogInfo.Hinsh			=LogInfo.Hinsh;
	wLogInfo.Lot			=LogInfo.Lot;
	wLogInfo.Jouge			=LogInfo.Jouge;
	wLogInfo.KibanNo		=LogInfo.KibanNo;
	wLogInfo.UpdateTime		=LogInfo.UpdateTime;
	wLogInfo.HDNameList		=LogInfo.HDNameList;
	wLogInfo.NGNumb			=LogInfo.NGNumb;
	wLogInfo.KohenNumb		=LogInfo.KohenNumb;
	wLogInfo.KohenNameList	=LogInfo.KohenNameList;
	wLogInfo.IsOutputLog	=LogInfo.IsOutputLog;
	if(wLogInfo.KohenInfo!=NULL){
		delete []wLogInfo.KohenInfo;
	}
	wLogInfo.KohenInfo		=new KohenInformation[wLogInfo.KohenNumb];
	for(int i=0;i<wLogInfo.KohenNumb;i++){
		wLogInfo.KohenInfo[i]=LogInfo.KohenInfo[i];
	}

	NGDataList[0].clear();
	NGDataList[1].clear();
	NoNGImageRowList.clear();
	for(int Row=0;Row<NGCount;Row++){
		if(Data[iSide[Row]]==NULL || iNGI[Row]==-1 || iIDX[Row]==-1){
			//NG画像がない場合
			NoNGImageRowList.append(Row);
			continue;
		}
//		if(Data[iSide[Row]][iIDX[Row]]==NULL){
//			//NG画像がない場合
//			continue;
//		}
		NGDataList[iSide[Row]].append(Data[iSide[Row]][iIDX[Row]][iIndex[Row]]);
	}
}
/*
void NGImageSaveThread::SlotAllCheckedFormClose()
{
	if(ACForm==NULL)
		return;
	ACForm->close();
	delete ACForm;
	ACForm=NULL;
	ReviewEnable=true;
}
*/
void NGImageSaveThread::run()
{
	//DEBUG
	QString strPath;
	int NGInfoListCntSum,NGInfoListNGCount;
	int NGNoInKohen;
	int KohenNo;

	FirstComming=true;
	int Index=0;
	for(int Row=0;Row<NGCount;Row++,Index++){
		//NG画像がない場合は飛ばす
		if(NoNGImageRowList.contains(Row)==true){
			Index--;
			continue;
		}

		//個片名称の数を取得
//		int KohenNameCnt=KohenName[Row].count(',')+1;
		int KohenNameCnt=RealKohenName[Row].count(',')+1;

		//個片名称をリストに保存
		QStringList KohenNameList;
		KohenNameList=KohenName[Row].split(',');
		QStringList RealKohenNameList;
		RealKohenNameList=RealKohenName[Row].split(',');

		//個片名称が無い場合の処理
		if((KohenNo=wLogInfo.KohenNameList.indexOf(KohenName[Row]))==-1){	//個片名称（QList）のindexで取得する
			if(KohenNameList.count()>1){
				KohenNo=wLogInfo.KohenNameList.indexOf(KohenNameList[0]);
				if(KohenNo<0){
					emit SignalError(1);
					return;
				}
			}
			else{
				emit SignalError(2);
				return;
			}
		}

		//保存NG画像は最大999個
		if(Row>=999){
//			emit SignalError();
			return;
		}

		//保存先の設定
		QString strDate=QDateTime::currentDateTime().toString("yyyyMMdd");
//		QString strPath="D:/"
		strPath="D:/"
						+ strDate
						+ "/"
						+ wLogInfo.Lot
						+ "/";

		//保存先のフォルダが無ければ作る
		char delim = '/';
		QStringList dirs = (strPath).split(delim, QString::SkipEmptyParts);
		QDir dir(dirs[0] + delim);
		for(int i=1; i<dirs.count(); i++){
			if(!dir.exists(dirs[i])){
				if(!dir.mkdir(dirs[i])){
					emit SignalError(3);
					return;
				}
			}
			if(!dir.cd(dirs[i])){
				emit SignalError(4);
				return;
			}
		}
		//OKのフォルダを作成しておく
		if(!dir.exists("OK")){
			if(!dir.mkdir("OK")){
				emit SignalError(5);
				return;
			}
		}
		//NGのフォルダを作成しておく
		if(!dir.exists("NG")){
			if(!dir.mkdir("NG")){
				emit SignalError(6);
				return;
			}
		}
		//NDのフォルダを作成しておく
		if(!dir.exists("ND")){
			if(!dir.mkdir("ND")){
				emit SignalError(7);
				return;
			}
		}

		if(FirstComming==true){
			//既に同じNGファイルがある場合、削除しておく
			QString strDirs[3];
			strDirs[0]="OK";
			strDirs[1]="NG";
			strDirs[2]="ND";
			QDir Dirs[3];
			Dirs[0]=Dirs[1]=Dirs[2]=dir;
			QString	SearchFile=wLogInfo.Jouge + "_" + wLogInfo.KibanNo + "_*.jpg";
			QStringList nameFilters(SearchFile);
			for(int Cnt=0;Cnt<3;Cnt++){
				if(!Dirs[Cnt].cd(strDirs[Cnt])){
					emit SignalError(8);
					return;
				}
				QStringList List=Dirs[Cnt].entryList(nameFilters,QDir::Files,QDir::NoSort);
				for(int i=0;i<List.size();i++){
					QFile file(strPath + strDirs[Cnt] + "/" + List[i]);
					if(file.remove()==false){
						emit SignalError(9);
						return;
					}
				}
			}
			FirstComming=false;
		}

/*		//既に同じNGファイルがある場合、削除しておく
		QString	SearchFile=wLogInfo.Jouge + "_" + wLogInfo.KibanNo + "_" + QString::number(Row+1).rightJustified(3,'0') + "-*.jpg";
		QStringList nameFilters(SearchFile);
		QStringList List=dir.entryList(nameFilters,QDir::Files,QDir::NoSort);
		for(int i=0;i<List.size();i++){
			QFile file(strPath + List[i]);
			if(file.remove()==false){
				emit SignalError();
				return;
			}
		}
*/
/*		//個片内でのNG番号を取得
		int NGInfoListCntSum=0,NGInfoListNGCount=0;
		int NGNoInKohen=0;
		for(int i=0;i<wLogInfo.KohenNumb;i++){
			if(((NGInfoListNGCount=wLogInfo.KohenInfo[i].NGCount)+NGInfoListCntSum)>Row){
				NGNoInKohen=Row-NGInfoListCntSum;
				break;
			}
			NGInfoListCntSum+=NGInfoListNGCount;
		}
		int Count=0;
		for(int i=0,Cnt=0;i<wLogInfo.KohenInfo[KohenNo].NGInfoList.count();i++){
			if(wLogInfo.KohenInfo[KohenNo].NGInfoList[i].TaiouKohenNo>0){
				Count++;
				continue;
			}
			if(Cnt==NGNoInKohen){
				break;
			}
			Cnt++;
		}
		NGNoInKohen+=Count;
*/
		//個片内でのNG番号を取得
		NGInfoListCntSum=0;
		NGInfoListNGCount=0;
		NGNoInKohen=0;
		for(int i=0;i<wLogInfo.KohenNumb;i++){
			int NGInfoListCnt=wLogInfo.KohenInfo[i].NGInfoList.count();
			int TaiouKohenCnt=0;
			for(int j=0;j<NGInfoListCnt;j++){
				if(wLogInfo.KohenInfo[i].NGInfoList[j].TaiouKohenNo>0){
					TaiouKohenCnt++;
					continue;
				}
			}
			//重複を含まないNGデータ数をカウント
			wLogInfo.KohenInfo[i].NGCount=NGInfoListCnt-TaiouKohenCnt;

			if(((NGInfoListNGCount=wLogInfo.KohenInfo[i].NGCount)+NGInfoListCntSum)>Row){
				NGNoInKohen=Row-NGInfoListCntSum;
				break;
			}
			NGInfoListCntSum+=NGInfoListNGCount;
		}
		int Count=0;
		for(int i=0,Cnt=0;i<wLogInfo.KohenInfo[KohenNo].NGInfoList.count();i++){
			if(wLogInfo.KohenInfo[KohenNo].NGInfoList[i].TaiouKohenNo>0){
				Count++;
				continue;
			}
			if(Cnt==NGNoInKohen){
				break;
			}
			Cnt++;
		}
		NGNoInKohen+=Count;

#ifdef Debug
		QString AAA;
		for(int a=0;a<wLogInfo.KohenNumb;a++){
			for(int b=0;b<wLogInfo.KohenInfo[a].NGInfoList.count();b++){
				AAA=wLogInfo.KohenInfo[a].NGInfoList[b].HanteiKekka;
				AAA=AAA;
			}
		}
#endif
		//保存先の設定
		if(NGNoInKohen>=wLogInfo.KohenInfo[KohenNo].NGInfoList.count()){
			continue;
		}
		else{
			strPath +=wLogInfo.KohenInfo[KohenNo].NGInfoList[NGNoInKohen].HanteiKekka
					+ "/";
		}

		//保存ファイル名の設定
		for(int i=0;i<KohenNameCnt;i++){
			QString FilePath=strPath;
			FilePath+=wLogInfo.Jouge
					+ "_"
					+ wLogInfo.KibanNo
					+ "_"
					+ QString::number(Row+1).rightJustified(3,'0')
					+ "-"
					+ QString::number(wLogInfo.KohenInfo[KohenNo].NGInfoList[NGNoInKohen].TaiouKohenNumb)
					+ "_"
					+ RealKohenNameList[i]
					+ "_"
					+ strTime
					+ "_"
					+ wLogInfo.KohenInfo[KohenNo].NGInfoList[NGNoInKohen].HanteiKekka
					+ ".jpg";

			QFile file(FilePath);
			if(!file.open(QIODevice::WriteOnly)){
				emit SignalError(10);
				return;
			}
			if(file.write(NGDataList[iSide[Row]][Index])!=NGDataList[iSide[Row]][Index].size()){
				emit SignalError(11);
			}
			file.close();
		}
	}
}

ProcessCheckThread::ProcessCheckThread()
{
	FinMode=false;
}

void ProcessCheckThread::Initial()
{
	FinMode=false;
	ProcessNameList.clear();
}

void ProcessCheckThread::run()
{
	for(;;){
		msleep(500);
		if(FinMode==true){
			break;
		}

		QStringList Processes;
		if(GetProcessNames(Processes)==true){
			if(FinMode==true){
				break;
			}
			int	i;
			for(i=0;i<ProcessNameList.count();i++){
				if(Processes.contains(ProcessNameList[i])==false){
					break;
				}
			}
			if(i==ProcessNameList.count()){
				continue;
			}
			else{
				emit SignalError(ProcessNameList[i]);
				break;
			}
		}
	}
}
