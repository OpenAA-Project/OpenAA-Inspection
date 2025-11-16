/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoSaveImage\XAutoSaveImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <QFileInfo>
#include <QDir>
#include "XAutoSaveImage.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "XGeneralStocker.h"
#include "PanelSaveImage.h";
#include "XForWindows.h"
#include "XLotInformation.h"
#include "swap.h"
#include "zlib.h"

//#define _USE_MATH_DEFINES
//#include "math.h"
//#include <omp.h>

AutoSaveImageThreshold::AutoSaveImageThreshold(AutoSaveImageItem *parent)
:AlgorithmThreshold(parent)
{
}

void	AutoSaveImageThreshold::CopyFrom(const AlgorithmThreshold &src)
{
}
bool	AutoSaveImageThreshold::Save(QIODevice *file)
{
	WORD	Ver=2;

	if(::Save(file,Ver)==false)
		return(false);
	return(true);
}
bool	AutoSaveImageThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);

	return(true);
}

AlgorithmItemPLI	&AutoSaveImageItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	return *this;
}

bool    AutoSaveImageItem::Save(QIODevice *f)
{
	WORD	Ver=3;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Save(f)==false)
		return false;
	return true;
}
bool    AutoSaveImageItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);

	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return false;

	return true;
}

//-------------------------------------------------------------------------------------

AutoSaveImageInLayer::AutoSaveImageInLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLI(parent)
{
	SThread=NULL;
	CyclicNumb=0;

	FolderNameFormat = "yyyy-MM-dd/hh";
}

void	AutoSaveImageInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetFileEntries	*CmdGetFileEntriesVar=dynamic_cast<CmdGetFileEntries *>(packet);
	if(CmdGetFileEntriesVar!=NULL){
		GetFileEntries(CmdGetFileEntriesVar->Entries,GetLayersBase()->GetMasterCode(),GetPage(),GetLayer());
		return;
	}
	CmdLoadFile	*CmdLoadFileVar=dynamic_cast<CmdLoadFile *>(packet);
	if(CmdLoadFileVar!=NULL){
		QStringList	StrFileNameExt=CmdLoadFileVar->FileName.split('.');
		QString	FileName;
		for(int i=0;i<StrFileNameExt.count()-1;i++){
			if(i<StrFileNameExt.count()-1){
				QStringList	StrValues=StrFileNameExt[i].split('-');
				for(int j=0;j<StrValues.count();j++){
					if(j<(StrValues.count()-1)){
						FileName=FileName+StrValues[j]+/**/QString('-');
					}
					else{
						char	LBuff[10];
						sprintf(LBuff,/**/"%02d",GetLayer());
						FileName=FileName+QString(LBuff)+/**/QString(/**/".piy");
					}
				}
			}
		}
		LoadFileToTarget(FileName);
		//LoadFileToTarget(CmdLoadFileVar->InspectionID,GetLayersBase()->GetMasterCode(),CmdLoadFileVar->LotAutoCount,GetPage(),GetLayer());
		return;
	}
	CmdImageLoadFile *CmdImageLoadFileVar=dynamic_cast<CmdImageLoadFile *>(packet);
	if(CmdImageLoadFileVar!=NULL){
		LoadFileToMaster(CmdImageLoadFileVar->FileName,GetPage(),GetLayer());
		return;
	}
}


bool	AutoSaveImageInLayer::SaveLayerTarget(ImageBuffer *SavedImage, QString FilePath ,BYTE *CompressBuff,BYTE *CompressBuff2)
{
	int32 Version = 2;	//バージョン情報
	int32 PartialDot = ((AutoSaveImageBase *)GetParentBase())->PartialDot;

	QFile	File(FilePath);

	if(File.open(QIODevice::WriteOnly)==false)
		return false;
	if(::Save(&File,Version)==false)
		return false;
	if(::Save(&File,PartialDot)==false)
		return false;
	int32	DotPerLine=GetDotPerLine();
	if(::Save(&File,DotPerLine)==false)
		return false;
	int32	MaxLines=GetMaxLines();
	if(::Save(&File,MaxLines)==false)
		return false;

	bool	CompressMode=((AutoSaveImageBase *)GetParentBase())->CompressMode;
	if(::Save(&File,CompressMode)==false)
		return false;

	//_CrtCheckMemory();
	if(CompressMode==false){
		if(SavedImage->Save(&File)==false){
			return false;
		}
	}
	else{
		int	NYLen=CompressBuffSize/GetDotPerLine();
		int	NYBand=(GetMaxLines()+NYLen)/NYLen;
		int	BandByte=NYLen*GetDotPerLine();
		for(int b=0;b<NYBand;b++){
			memset(CompressBuff,0,BandByte);
			for(int y=0;y<NYLen;y++){
				int	Y=b*NYLen+y;
				if(Y>=GetMaxLines()){
					break;
				}
				memcpy(&CompressBuff[y*GetDotPerLine()],SavedImage->GetY(Y),GetDotPerLine());
			}
			unsigned long len	= BandByte;
			unsigned long comprLen	=CompressBuffSize;
			unsigned long uncomprLen	=CompressBuffSize;
			int err = compress(CompressBuff2, &comprLen, (const BYTE *)CompressBuff, len);
			if(err!=0){
				return false;
			}
			if(::Save(&File,comprLen)==false)
				return false;
			if(File.write((const char *)CompressBuff2,comprLen)!=comprLen){
				return false;
			}
			if(((AutoSaveImageBase *)GetParentBase())->SleepTimeForSave!=0){
				GSleep(((AutoSaveImageBase *)GetParentBase())->SleepTimeForSave);
			}
		}
	}
	//_CrtCheckMemory();

	return true;
}
bool	AutoSaveImageInLayer::LoadLayerTarget(ImageBuffer *Dest, QString FileName
									,BYTE *CompressBuff,BYTE *CompressBuff2)
{
	QFile	File(FileName);
	QString fnam = File.fileName();
	bool ret = File.exists();

	if(File.open(QIODevice::ReadOnly)==false)
		return false;

	int32	Version;
	if(::Load(&File,Version)==false)
		return false;
	if(Version==1){
		int32	PartialDot;
		if(::Load(&File,PartialDot)==false)
			return false;
		int32	iDotPerLine;
		if(::Load(&File,iDotPerLine)==false)
			return false;
		int32	iMaxLines;
		if(::Load(&File,iMaxLines)==false)
			return false;

		Dest->Set(0,0,iDotPerLine/(PartialDot+1), iMaxLines/(PartialDot+1));
		if(Dest->Load(&File)==false){
			return false;
		}
	}
	else{
		int32	PartialDot;
		if(::Load(&File,PartialDot)==false)
			return false;
		int32	iDotPerLine;
		if(::Load(&File,iDotPerLine)==false)
			return false;
		int32	iMaxLines;
		if(::Load(&File,iMaxLines)==false)
			return false;

		bool	CompressMode;
		if(::Load(&File,CompressMode)==false)
			return false;

		Dest->Set(0,0,(iDotPerLine+PartialDot)/(PartialDot+1), (iMaxLines+PartialDot)/(PartialDot+1));
		if(CompressMode==false){
			if(PartialDot==0){
				if(Dest->Load(&File)==false){
					return false;
				}
			}
			else{
				if(Dest->Load(&File)==false){
					return false;
				}
			}
		}
		else{
			int	NYLen=CompressBuffSize/GetDotPerLine();
			int	NYBand=(GetMaxLines()+NYLen)/NYLen;
			int	BandByte=NYLen*GetDotPerLine();
			for(int b=0;b<NYBand;b++){
				unsigned long len		= BandByte;
				unsigned long comprLen	=CompressBuffSize;
				unsigned long uncomprLen=CompressBuffSize;

				if(::Load(&File,comprLen)==false)
					return false;
				if(File.read((char *)CompressBuff,comprLen)!=comprLen){
					return false;
				}
				int err = uncompress(CompressBuff2, &uncomprLen, (const BYTE*)CompressBuff, comprLen);

				for(int y=0;y<NYLen;y++){
					int	Y=b*NYLen+y;
					if(Y>=GetMaxLines()){
						break;
					}
					memcpy(Dest->GetY(Y),&CompressBuff2[y*GetDotPerLine()],GetDotPerLine());
				}
			}
		}
	}

	return true;
}

//06-6562-0023

int	AutoSaveImageInLayer::GetFileEntries(FileEntryListContainer &Dest, int MasterCode,int Page , int Layer)
{
	QStringList FileMask;
	//FileMask << MakeFileMask(MasterCode, Page, Layer);
	FileMask<</**/"*.piy";
	QRegularExpression RegExpFileName("([0-9]{6})_([0-9]{6})_(.{6})_([0-9])_([0-9]).piy");

	QStringList dirs = GetRootPathList();	//処理したいディレクトリのスタック

	while(!dirs.isEmpty()){
		QDir dir = dirs[0];
		dirs.removeFirst();

		QString path = dir.path() + "/";

		QStringList subdirs = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name);
		for(int i=0; i<subdirs.count(); i++)
			dirs.append(dir.path() + "/" + subdirs[i]);
		
		QStringList files = dir.entryList(FileMask, QDir::Files, QDir::Name);
		
		for(int i=0; i<files.count(); i++){
			QRegularExpressionMatch	R=RegExpFileName.match(files[i]);
			if(R.hasMatch()){
				FileEntryList l;
				l.FileName = (path + files[i]);

				QFileInfo fi(path, files[i]);
				l.FileStamp = fi.lastModified();

				QStringList submatches = RegExpFileName.namedCaptureGroups();
				l.LotAutoCount	= submatches[1].toInt();
				l.InspectionID	= submatches[2].toInt();
				l.MasterCode	= submatches[3].replace(QRegularExpression("_"), "").toInt();
				l.Page			= submatches[4].toInt();
				l.Layer			= submatches[5].toInt();

				Dest.AppendList(l);
			}
			else{
				FileEntryList l;
				l.FileName = (path + files[i]);

				QFileInfo fi(path, files[i]);
				l.FileStamp = fi.lastModified();

				Dest.AppendList(l);
			}
		}
	}
	return 0;
}
QStringList AutoSaveImageInLayer::GetRootPathList(void)
{
	AutoSaveImageBase	*PBase=(AutoSaveImageBase *)GetParentBase();
	return PBase->GetRootPathList();
}
bool AutoSaveImageInLayer::LoadFileToTarget(int64 InspectionID, int MasterCode,int LotAutoCount ,int Page , int Layer)
{
/*	//ファイルを探す
	QStringList dirs = GetRootPathList();	//処理したいディレクトリのスタック

	QString FileName = MakeFileName(InspectionID, MasterCode, LotAutoCount, Page, Layer);
	QString FilePath;

	while(!dirs.isEmpty()){
		QDir dir = dirs[0];
		dirs.removeFirst();

		QStringList subdirs = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
		int subdircnt = subdirs.count();
		for(int i=0; i<subdirs.count(); i++)
			dirs.append(dir.path() + "/" + subdirs[i]);
		
		QStringList files = dir.entryList(QStringList("*.piy"), QDir::Files);
		
		for(int i=0; i<files.count(); i++){
			if(files[i] == FileName){
				FilePath = dir.path();
				break;
			}
		}
	}

	if(FilePath=="")
		return false;

	//ファイルを読み込む
	ImageBuffer *MiniImage;
	LoadLayerTarget(&MiniImage, FilePath + ::GetSeparator() + FileName);
	int miniWidth = MiniImage->GetWidth();
	int miniHeight = MiniImage->GetHeight();

	ImageBuffer *TargetBuff=&GetTargetBuff();
	int targetWidth = TargetBuff->GetWidth();
	int targetHeight = TargetBuff->GetHeight();

	//それなりに処理する
	//まずはあまりをうめておく
	for(int Y=0; Y<targetHeight; Y++){						// bug. なぜか埋まらない。大きい画像を読み込んだあと小さい画像を読み込むと前のが残っている
			BYTE *pTargetBuff = TargetBuff->GetY(Y);
			for(int X=Y<miniHeight?miniWidth:0; X<targetWidth; X++)
				pTargetBuff[X] = 0;
	}

	//ループの度いちいち&したくないから
	int minWidth = miniWidth<targetWidth?miniWidth:targetWidth;
	int minHeight = miniHeight<targetHeight?miniHeight:targetHeight;

	//
	for(int Y=0; Y<minHeight; Y++){
		BYTE *pTargetBuff = TargetBuff->GetY(Y);
		BYTE *pMiniBuff = MiniImage->GetY(Y);
		for(int X=0; X<minWidth; X++){
			pTargetBuff[X] = pMiniBuff[X];
		}
	}
	delete MiniImage;
*/
	return true;
}

bool AutoSaveImageInLayer::LoadFileToMaster(QString FileName, int Page, int Layer)
{
	return LoadFileTo(FileName ,GetMasterBuff());
}
bool AutoSaveImageInLayer::LoadFileToTarget(QString FileName)
{
	return LoadFileTo(FileName ,GetTargetBuff());
}

bool AutoSaveImageInLayer::LoadFileTo(const QString &FileName ,ImageBuffer &DestImage)
{
	QString saveFileName = FileName;
	ImageBuffer MiniImage;
	BYTE		*CompressBuff1=new BYTE[CompressBuffSize];
	BYTE		*CompressBuff2=new BYTE[CompressBuffSize];

	if ( LoadLayerTarget(&MiniImage, FileName,CompressBuff1,CompressBuff2) == false ) {
		delete	[]CompressBuff1;
		delete	[]CompressBuff2;
		return false;
	}
	int miniWidth  = MiniImage.GetWidth();
	int miniHeight = MiniImage.GetHeight();

	int masterWidth  = DestImage.GetWidth();
	int masterHeight = DestImage.GetHeight();

	AutoSaveImageBase	*PBase=(AutoSaveImageBase *)GetParentBase();
	int	PartialDot=(masterWidth+miniWidth-1)/miniWidth;
	if(PartialDot==1 && masterWidth==miniWidth && masterHeight==miniHeight){
		DestImage=MiniImage;
	}
	else{
		if(PartialDot==0)
			PartialDot=1;
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<masterHeight;y++){
				BYTE	*Src=MiniImage.GetY(y/PartialDot);
				BYTE	*Dst=DestImage.GetY(y);
				for(int x=0;x<masterWidth;x++){
					Dst[x]=Src[x/PartialDot];
				}
			}
		}
	}
	delete	[]CompressBuff1;
	delete	[]CompressBuff2;
	return true;
}


ExeResult	AutoSaveImageInLayer::ExecutePreAlignment(int ExeID ,ResultInLayerRoot *Res)
{
	AutoSaveImageInPage	*PPage=(AutoSaveImageInPage *)GetParentInPage();
	if(PPage->AutoSaveON==true){
		if( SaveTarget()==true){
			return _ER_true;
		}
	}
	return _ER_ReqRetryLater;
}
bool	AutoSaveImageInLayer::SaveTarget(void)
{
	AutoSaveImageBase	*PBase=(AutoSaveImageBase *)GetParentBase();
	if(SThread==NULL){
		SThread=new AutoSaveThread*[PBase->MaxBufferNumb];
		for(int i=0;i<PBase->MaxBufferNumb;i++){
			SThread[i]=NULL;
		}
	}
	if(SThread[CyclicNumb]==NULL){
		SThread[CyclicNumb]=new AutoSaveThread(GetLayersBase()->GetMainWidget());
		SThread[CyclicNumb]->Initial(0,this,(AutoSaveImageBase *)GetParentBase());
		SThread[CyclicNumb]->start();				
	}
	if(SThread[CyclicNumb]->StartMode==true){
		GetLayersBase()->SendErrorToMaster(0x1000FF , QString("HDD error 前回の書き込みが完了する前に次の書き込みを行おうとしています") ,ErrorCodeList::_Important);
	}
	int	N=0;
	for(int i=0;i<PBase->MaxBufferNumb;i++){
		if(SThread[i]!=NULL){
			if(SThread[i]->StartMode==true){
				N++;
			}
		}
	}
	if(N>=PBase->AlarmCountLimit){
		GetLayersBase()->SendErrorToMaster(0x1000FE , QString("HDD error バッファの蓄積数上限での警告") ,ErrorCodeList::_Important);
	}

	if(SThread[CyclicNumb]->CopyFromTarget()==false){
		GetLayersBase()->SendErrorToMaster(0x1000FC , QString("HDD error 保存残存要領不足での警告") ,ErrorCodeList::_Important);
	}
	SThread[CyclicNumb]->StartMode=true;
	//SThread[CyclicNumb]->start();				
	CyclicNumb++;
	if(CyclicNumb>=PBase->MaxBufferNumb)
		CyclicNumb=0;
	return true;
}
bool	AutoSaveImageInLayer::SaveMaster(void)
{
	AutoSaveImageBase	*PBase=(AutoSaveImageBase *)GetParentBase();
	if(SThread==NULL){
		SThread=new AutoSaveThread*[PBase->MaxBufferNumb];
		for(int i=0;i<PBase->MaxBufferNumb;i++){
			SThread[i]=NULL;
		}
	}
	if(SThread[CyclicNumb]==NULL){
		SThread[CyclicNumb]=new AutoSaveThread(GetLayersBase()->GetMainWidget());
		SThread[CyclicNumb]->Initial(0,this,(AutoSaveImageBase *)GetParentBase());
		SThread[CyclicNumb]->start();				
	}
	if(SThread[CyclicNumb]->StartMode==true){
		GetLayersBase()->SendErrorToMaster(0x1000FF , QString("HDD error 前回の書き込みが完了する前に次の書き込みを行おうとしています") ,ErrorCodeList::_Important);
	}
	int	N=0;
	for(int i=0;i<PBase->MaxBufferNumb;i++){
		if(SThread[i]!=NULL){
			if(SThread[i]->StartMode==true){
				N++;
			}
		}
	}
	if(N>=PBase->AlarmCountLimit){
		GetLayersBase()->SendErrorToMaster(0x1000FE , QString("HDD error バッファの蓄積数上限での警告") ,ErrorCodeList::_Important);
	}

	if(SThread[CyclicNumb]->CopyFromMaster()==false){
		GetLayersBase()->SendErrorToMaster(0x1000FC , QString("HDD error 保存残存要領不足での警告") ,ErrorCodeList::_Important);
	}
	SThread[CyclicNumb]->StartMode=true;
	//SThread[CyclicNumb]->start();				
	CyclicNumb++;
	if(CyclicNumb>=PBase->MaxBufferNumb)
		CyclicNumb=0;
	return true;
}

QString	AutoSaveImageInLayer::MakeDirPath(QString RootPath, QString &DefaultFolderName, int LocalPageNo)
{
	QList<QVariant> Arguments;
	QList<QVariant> ReturnedValues;
	Arguments
		<< AUTOSAVEIMAGE_FILEEXTENTION
		<< GetLayersBase()->GetGlobalPageFromLocal(LocalPageNo);
	if( true==(GetLayersBase()->GetGeneralStocker()->GetData("AutoSaveImage_DirPath", ReturnedValues, Arguments)) ){
		return ReturnedValues[0].toString();
	}else{
		char delim = '/';
		int layer(GetLayer());
		if(layer<=0)
			return(DefaultFolderName);

		//レイヤー番号1以上からはじめようとしているとき、番号0のフォルダを参照する
		//1.前のファイルが存在するならOK
		QString prevfilename = MakeFileName(GetLayer()-1);
		QFile file(RootPath + delim + DefaultFolderName + delim + prevfilename);
		if( file.exists() )
			return(DefaultFolderName);

		//2.フォルダを変えないといけないとき
		QDateTime tmpdt = QDateTime::fromString(DefaultFolderName, FolderNameFormat);
		QDateTime prevdatetime;
		//addSecs、なぜか時間しか-3600秒されないのでQDateとQTimeわける
		prevdatetime.setTime(tmpdt.addSecs(-3600).time());
		if(tmpdt.time().hour()==0)
			prevdatetime.setDate(tmpdt.date().addDays(-1));
		else
			prevdatetime.setDate(tmpdt.date());
		return prevdatetime.toString(FolderNameFormat);
	}
}

QString	AutoSaveImageInLayer::MakeFileName(int LayerNo)
{
	if(LayerNo==-1)
		LayerNo = GetLayer();

	return MakeFileName( GetLayersBase()->GetCurrentInspectIDForExecute(),
		GetLayersBase()->GetMasterCode(),
		GetLayersBase()->GetLotBase()->GetClusterID(),
		GetPage(),
		GetLayersBase()->GetGlobalPageFromLocal(GetPage()),
		LayerNo );
}

QString AutoSaveImageInLayer::MakeFileName(int64 InspectionID, int MasterCode, int LotAutoCount, int LocalPageNo, int GlobalPageNo, int LayerNo)
{
	QList<QVariant> Arguments;
	QList<QVariant> ReturnedValues;
	Arguments
		<< AUTOSAVEIMAGE_FILEEXTENTION
		<< GlobalPageNo;
	if( true==(GetLayersBase()->GetGeneralStocker()->GetData("AutoSaveImage_FileName", ReturnedValues, Arguments)) ){
		return ReturnedValues[0].toString();
	}else{
		AutoSaveImageBase	*PBase=(AutoSaveImageBase *)GetParentBase();
		if(PBase->StandardFolder==false){
			QString delim = "_";
			//FileName: LotAutoCount_CurrentInspectionIDForExecute_MasterCode_Page_Layer.piy
			//ex) 000123_000000_____-1_0_0.piy
			QString filename =  QString::number(LotAutoCount).rightJustified(6,'0') + delim  
							  + QString::number(InspectionID).rightJustified(6,'0') + delim
							  + QString::number(MasterCode).rightJustified(6,'_') + delim
							  + QString::number(GlobalPageNo) + delim
							  + QString::number(LayerNo)
							  + QString(".") + AUTOSAVEIMAGE_FILEEXTENTION;
			return filename;
		}
		else{
			AutoSaveImageInPage	*PPage=(AutoSaveImageInPage *)GetParentInPage();
			int	Year	=PBase->StoredTime.date().year();
			int	Month	=PBase->StoredTime.date().month();
			int	Day		=PBase->StoredTime.date().day();
			int	Hour	=PBase->StoredTime.time().hour();
			int	Minute	=PBase->StoredTime.time().minute();
			int	Second	=PBase->StoredTime.time().second();
			char	Buff[100];
			sprintf(Buff,"%02d%02d%02d-%02d/%02d%02d-%02d-%02d.piy",Year,Month,Day,Hour  ,Minute,Second,GlobalPageNo,LayerNo);
			return Buff;
		}
	}
}

//===========================================
AutoSaveImageInPage::AutoSaveImageInPage(AlgorithmBase *parent)
	:AlgorithmInPagePLI(parent)
{
	AutoSaveON=true;
}

void	AutoSaveImageInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetFileEntries	*CmdGetFileEntriesVar=dynamic_cast<CmdGetFileEntries *>(packet);
	if(CmdGetFileEntriesVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			CmdGetFileEntries	RCmd(GetLayersBase());
			GetLayerData(layer)->TransmitDirectly(&RCmd);
			CmdGetFileEntriesVar->Entries+=RCmd.Entries;
		}
		return;
	}
	CmdLoadFile	*CmdLoadFileVar=dynamic_cast<CmdLoadFile *>(packet);
	if(CmdLoadFileVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(CmdLoadFileVar);
		}
		return;
	}
	CmdImageLoadFile *CmdImageLoadFileVar=dynamic_cast<CmdImageLoadFile *>(packet);
	if(CmdImageLoadFileVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(CmdImageLoadFileVar);
		}
		return;
	}
	CmdLoadBandList	*CmdLoadBandListVar=dynamic_cast<CmdLoadBandList *>(packet);
	if(CmdLoadBandListVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			//((AutoSaveImageInLayer *)GetLayerData(layer))->LoadFileToTarget(CmdLoadBandListVar->FileNames[layer]);
			((AutoSaveImageInLayer *)GetLayerData(layer))->LoadFileTo(CmdLoadBandListVar->FileNames[layer]
																	,*CmdLoadBandListVar->Buff[layer]);
		}
		return;
	}
	CmdSaveImage	*CmdSaveImageVar=dynamic_cast<CmdSaveImage *>(packet);
	if(CmdSaveImageVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			if(CmdSaveImageVar->MasterImage==true)
				((AutoSaveImageInLayer *)GetLayerData(layer))->SaveMaster();
			else
				((AutoSaveImageInLayer *)GetLayerData(layer))->SaveTarget();
		}
		return;
	}
	CmdAutoSaveON	*CmdAutoSaveONVar=dynamic_cast<CmdAutoSaveON *>(packet);
	if(CmdAutoSaveONVar!=NULL){
		AutoSaveON=CmdAutoSaveONVar->AutoSaveON;
		return;
	}
}

ExeResult	AutoSaveImageInPage::ExecutePreAlignment(int ExeID ,ResultInPageRoot *Res)
{
	return AlgorithmInPagePLI::ExecutePreAlignment(ExeID ,Res);
}


//===========================================
AutoSaveImageBase::AutoSaveImageBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	PartialDot	=4;
	MaxBufferNumb	=16;
	AlarmCountLimit	=8;

	SavedFolder1	=/**/"c:/Image";
	SavedFolder2	=/**/"c:/Image";
	SavedFolder3	=/**/"c:/Image";
	SavedFolder4	=/**/"c:/Image";
	SavedFolder5	=/**/"c:/Image";
	SavedFolder6	=/**/"c:/Image";
	SavedFolder7	=/**/"c:/Image";
	SavedFolder8	=/**/"c:/Image";
	SavedFolder9	=/**/"c:/Image";
	SavedFolder10	=/**/"c:/Image";
	StandardFolder	=false;
	CompressMode	=false;
	CurrentFolderNumber=0;
	SleepTimeForSave=10;
	MaxCountToSave	=-1;

	SetParam(&MaxBufferNumb		, /**/"Setting"	,/**/"MaxBufferNumb"	,"Mximum count of Buffer");
	SetParam(&AlarmCountLimit	, /**/"Setting"	,/**/"AlarmCountLimit"	,"Mximum count to alarm till Buffer full");
	SetParam(&PartialDot		, /**/"Setting"	,/**/"PartialDot"		,"Partial Dot");
	SetParamPath(&SavedFolder1	, /**/"Folder"	,/**/"SavedFolder1"		,"Saved Folder1");
	SetParamPath(&SavedFolder2	, /**/"Folder"	,/**/"SavedFolder2"		,"Saved Folder2");
	SetParamPath(&SavedFolder3	, /**/"Folder"	,/**/"SavedFolder3"		,"Saved Folder3");
	SetParamPath(&SavedFolder4	, /**/"Folder"	,/**/"SavedFolder4"		,"Saved Folder4");
	SetParamPath(&SavedFolder5	, /**/"Folder"	,/**/"SavedFolder5"		,"Saved Folder4");
	SetParamPath(&SavedFolder6	, /**/"Folder"	,/**/"SavedFolder6"		,"Saved Folder6");
	SetParamPath(&SavedFolder7	, /**/"Folder"	,/**/"SavedFolder7"		,"Saved Folder7");
	SetParamPath(&SavedFolder8	, /**/"Folder"	,/**/"SavedFolder8"		,"Saved Folder8");
	SetParamPath(&SavedFolder9	, /**/"Folder"	,/**/"SavedFolder9"		,"Saved Folder9");
	SetParamPath(&SavedFolder10	, /**/"Folder"	,/**/"SavedFolder10"	,"Saved Folder10");
	SetParam(&StandardFolder	, /**/"Setting"	,/**/"StandardFolder"	,"Use standard folder");
	SetParam(&CompressMode		, /**/"Setting"	,/**/"CompressMode"		,"Mode of image compression");
	SetParam(&SleepTimeForSave	, /**/"Setting"	,/**/"SleepTimeForSave"	,"Sleep Time(ms) for saving data");
	SetParam(&MaxCountToSave	, /**/"Setting"	,/**/"MaxCountToSave"	,"Max count to save images. if -1, this is unlimited");
}

AlgorithmDrawAttr	*AutoSaveImageBase::CreateDrawAttr(void)
{
	return NULL;
}

bool	AutoSaveImageBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	return true;
}
ExeResult	AutoSaveImageBase::ExecutePreAlignment		(int ExeID ,ResultBaseForAlgorithmRoot *Res)
{
	StoredTime	=QDateTime::currentDateTime();
	return AlgorithmBase::ExecutePreAlignment(ExeID ,Res);
}
void	AutoSaveImageBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetFileEntries	*CmdGetFileEntriesVar=dynamic_cast<CmdGetFileEntries *>(packet);
	if(CmdGetFileEntriesVar!=NULL){
		GetPageData(CmdGetFileEntriesVar->LocalPage)->TransmitDirectly(CmdGetFileEntriesVar);
		return;
	}
	CmdLoadFile	*CmdLoadFileVar=dynamic_cast<CmdLoadFile *>(packet);
	if(CmdLoadFileVar!=NULL){
		GetPageData(CmdLoadFileVar->LocalPage)->TransmitDirectly(CmdLoadFileVar);
		return;
	}
	CmdImageFileList *CmdImageFileListVar=dynamic_cast<CmdImageFileList *>(packet);
	if(CmdImageFileListVar!=NULL) {
		GetAutoSaveImageList(CmdImageFileListVar);
		return;
	}
	CmdImageLoadFile *CmdImageLoadFileVar=dynamic_cast<CmdImageLoadFile *>(packet);
	if ( CmdImageLoadFileVar!=NULL) {
		GetPageData(CmdImageLoadFileVar->LocalPage)->TransmitDirectly(CmdImageLoadFileVar);
		return;
	}
	CmdGetRootPathList	*CmdGetRootPathListVar=dynamic_cast<CmdGetRootPathList *>(packet);
	if(CmdGetRootPathListVar!=NULL){
		CmdGetRootPathListVar->RootPaths	=GetRootPathList();
		return;
	}
	CmdSearchFileList	*CmdSearchFileListVar=dynamic_cast<CmdSearchFileList *>(packet);
	if(CmdSearchFileListVar!=NULL){
		//QStringList	L=GetRootPathList();
		for(int i=0;i<CmdSearchFileListVar->RootPaths.count();i++){
			SearchFileList(CmdSearchFileListVar->RootPaths[i],CmdSearchFileListVar);
		}
		return;
	}
	CmdReqFolderList	*CmdReqFolderListVar=dynamic_cast<CmdReqFolderList *>(packet);
	if(CmdReqFolderListVar!=NULL){
		if(SavedFolder1.isEmpty()==false)
			CmdReqFolderListVar->FolderList.append(SavedFolder1);
		if(SavedFolder2.isEmpty()==false)
			CmdReqFolderListVar->FolderList.append(SavedFolder2);
		if(SavedFolder3.isEmpty()==false)
			CmdReqFolderListVar->FolderList.append(SavedFolder3);
		if(SavedFolder4.isEmpty()==false)
			CmdReqFolderListVar->FolderList.append(SavedFolder4);
		if(SavedFolder5.isEmpty()==false)
			CmdReqFolderListVar->FolderList.append(SavedFolder5);
		if(SavedFolder6.isEmpty()==false)
			CmdReqFolderListVar->FolderList.append(SavedFolder6);
		if(SavedFolder7.isEmpty()==false)
			CmdReqFolderListVar->FolderList.append(SavedFolder7);
		if(SavedFolder8.isEmpty()==false)
			CmdReqFolderListVar->FolderList.append(SavedFolder8);
		return;
	}
	CmdSetFolderNumber	*CmdSetFolderNumberVar=dynamic_cast<CmdSetFolderNumber *>(packet);
	if(CmdSetFolderNumberVar!=NULL){
		CurrentFolderNumber=CmdSetFolderNumberVar->FolderNumber;
		return;
	}
	CmdSaveImage	*CmdSaveImageVar=dynamic_cast<CmdSaveImage *>(packet);
	if(CmdSaveImageVar!=NULL){
		StoredTime	=QDateTime::currentDateTime();
		for(int page=0;page<GetPageNumb();page++){
			GetPageData(page)->TransmitDirectly(packet);
		}
		return;
	}
}
bool	AutoSaveImageBase::NextFolder(void)
{
	CurrentFolderNumber++;
	return true;
}

void	AutoSaveImageBase::SearchFileList(QString &Folder,CmdSearchFileList *Ret)
{
	if(StandardFolder==true){
		QDir	dir(Folder);
		if(dir.cd(Folder)==false)
			return;
		QStringList nameFilters;
		nameFilters.append("*.*");
		//QStringList	FolderOfDateTime=dir.entryList (nameFilters, QDir::Dirs);
		QStringList	FolderOfDateTime=dir.entryList ();
		for(int i=0;i<FolderOfDateTime.count();i++){
			QDateTime	s=MakeQDateTime(FolderOfDateTime[i]);
			if(MakeDateHour(Ret->TimeFrom)<=s && s<=MakeDateHour(Ret->TimeTo)){
				QString	SearchStr(Folder+QDir::separator()+FolderOfDateTime[i]);
				FindFiles(SearchStr,Ret);
			}
		}
	}
}

QDateTime	AutoSaveImageBase::MakeQDateTime(QString &filderName)
//	YYMMDD-HH
{
	bool	ok;
	int	year	=filderName.mid(0,4).toInt(&ok);	if(ok==false)	return QDateTime();
	int	month	=filderName.mid(4,2).toInt(&ok);	if(ok==false)	return QDateTime();
	int	day		=filderName.mid(6,2).toInt(&ok);	if(ok==false)	return QDateTime();
	int	hour	=filderName.mid(9,2).toInt(&ok);	if(ok==false)	return QDateTime();

	QDateTime	Ret(QDate(year,month,day),QTime(hour,0,0));
	return Ret;
}

QDateTime	AutoSaveImageBase::MakeDateHour(QDateTime &s)
{
	int	year	=s.date().year();
	int	month	=s.date().month();
	int	day		=s.date().day();
	int	hour	=s.time().hour();

	QDateTime	Ret(QDate(year,month,day),QTime(hour,0,0));
	return Ret;
}

void	AutoSaveImageBase::FindFiles(QString &SearchPath, CmdSearchFileList *Ret)
{
	QStringList	Parts=SearchPath.split(QDir::separator());
	QString	filderName=Parts[Parts.count()-1];
	bool	ok;
	int	year	=filderName.mid(0,4).toInt(&ok);	if(ok==false)	return;
	int	month	=filderName.mid(4,2).toInt(&ok);	if(ok==false)	return;
	int	day		=filderName.mid(6,2).toInt(&ok);	if(ok==false)	return;
	int	hour	=filderName.mid(9,2).toInt(&ok);	if(ok==false)	return;

	QDir	dir;
	if(dir.cd(SearchPath)==true){
		QStringList nameFilters;
		nameFilters.append("*.*");
		QStringList	iFiles=dir.entryList (nameFilters, QDir::Files,QDir::Name);
		for(int i=0;i<iFiles.count();i++){
			//	mmss-ii
			bool	ok;
			int	FileMin		=iFiles[i].mid(0,2).toInt(&ok);	if(ok==false)	continue;
			int	FileSec		=iFiles[i].mid(2,2).toInt(&ok);	if(ok==false)	continue;
			int	FilePage	=iFiles[i].mid(5,2).toInt(&ok);	if(ok==false)	continue;
			int	FileLayer	=iFiles[i].mid(8,2).toInt(&ok);	if(ok==false)	continue;
			QDateTime	FileStamp(QDate(year,month,day),QTime(hour,FileMin,FileSec));
			if(Ret->TimeFrom<=FileStamp && FileStamp<=Ret->TimeTo){
				QString	FileName=SearchPath+QDir::separator()+iFiles[i];
				if(FilePage==0 && FileLayer==0){
					BandImageFileList	*L=new BandImageFileList();
					char	Buff[200];
					sprintf(Buff,"%02d%02d-00-00",FileMin,FileSec);
					L->BaseFileName=SearchPath+QDir::separator()+QString(Buff);
					L->EachFileNames.append(FileName);
					Ret->RetFile.AppendList(L);
				}
				else{
					char	Buff[200];
					sprintf(Buff,"%02d%02d-00-00",FileMin,FileSec);
					QString	BaseFileName=SearchPath+QDir::separator()+QString(Buff);
					for(BandImageFileList *L=Ret->RetFile.GetFirst();L!=NULL;L=L->GetNext()){
						if(L->BaseFileName==BaseFileName){
							L->EachFileNames.append(FileName);
						}
					}
				}
			}
		}
	}
}


QStringList AutoSaveImageBase::GetRootPathList(void)
{
	QStringList paths;
	AddUnique(paths,SavedFolder1);
	AddUnique(paths,SavedFolder2);
	AddUnique(paths,SavedFolder3);
	AddUnique(paths,SavedFolder4);
	AddUnique(paths,SavedFolder5);
	AddUnique(paths,SavedFolder6);
	AddUnique(paths,SavedFolder7);
	AddUnique(paths,SavedFolder8);
	AddUnique(paths,SavedFolder9);
	AddUnique(paths,SavedFolder10);

	return paths;
}

void AutoSaveImageBase::GetAutoSaveImageList(CmdImageFileList *cmd) {
	SaveImageFileListContainer tlst1;
	SaveImageFileListContainer tlst2;
	MakeAutoSaveImageList(cmd->strDir1,tlst1);
	MakeAutoSaveImageList(cmd->strDir2,tlst2);

	SaveImageFileListContainer lst;
	lst  = tlst1;
	lst += tlst2;
	lst.sort();
	cmd->SaveImageList = lst;
}

bool AutoSaveImageBase::MakeAutoSaveImageList(QString strDir, SaveImageFileListContainer &lstSaveImageFile) {
	QDir dir(strDir+"/Image");
	QString fDate = "";
	QString fBaseNo = "";
	QStringList filter1;
	filter1 << "??????????";
	dir.setNameFilters(filter1);
	QFileInfoList lstDateDir = dir.entryInfoList();
	int cnt = lstDateDir.size();
	for( int j=0; j<cnt; j++ ) {
		QFileInfo fInfo = lstDateDir.at(j);
		fDate = fInfo.fileName();
		if ( fInfo.isDir() == true ) {
			QDir dir2(fInfo.filePath());
			QStringList filter2;
			filter2 << "??";
			dir2.setNameFilters(filter2);
			QFileInfoList lstBaseDir = dir2.entryInfoList();
			if ( lstBaseDir.size() <= 0 ) continue;

			for( int k=0; k<lstBaseDir.size(); k++ ) {
				QFileInfo fBaseInfo = lstBaseDir.at(k);
				fBaseNo = fBaseInfo.fileName();
				if ( fBaseInfo.fileName() == "." || fBaseInfo.fileName() == ".." ) continue;
				if ( fBaseInfo.isDir() == true ) {
					QDir dir3(fBaseInfo.filePath());
					QStringList filter3;
					filter3 << "*.piy";
					dir3.setNameFilters(filter3);
					QFileInfoList lstPiyFile = dir3.entryInfoList();
					if ( lstPiyFile.size() <= 0 ) continue;

					for( int i=0; i<lstPiyFile.size(); i++ ) {
						QFileInfo fPiyFile = lstPiyFile.at(i);
						QString fName = fPiyFile.fileName();
						QStringList arr = fName.split("_");
						SaveImageFileList *rec = new SaveImageFileList();
						rec->FileDrv	= strDir+"Image/"+fDate+"/"+fBaseNo+"/";
						rec->FileDate	= fDate+" "+fBaseNo;
						rec->LotNo		= arr[0];
						rec->BaseNoStr	= arr[1];
						rec->BaseNoInt	=rec->BaseNoStr.toInt();
						rec->Page		= arr[arr.size()-2].toInt();
						rec->FileName	= fName;
						lstSaveImageFile.AppendList(rec);
					}
				}
			}
		}
	}

	/*
	QStringList oFilter;
	oFilter << "HD_*_D_ImageList.csv";
	dir.setNameFilters(oFilter);
	QFileInfoList lstFile = dir.entryInfoList();

	int cnt = lstFile.size();
	for( int j=0; j<lstFile.size(); j++ ) {
		QFileInfo fInfo = lstFile.at(j);
		QString fnm = fInfo.filePath();
		QFile file(fInfo.filePath());
		if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) ) {
			return false;
		}
		QString buf;
		while( !file.atEnd() ) {
			buf = file.readLine();
			QStringList arr = buf.split(",");
			SaveImageFileList *rec = new SaveImageFileList();
			rec->FileDrv  = strDir+arr[0]+"/"+arr[1]+"/"+arr[3]+"/";
			rec->FileDate = arr[0];
			rec->LotNo    = arr[1];
			rec->BaseNo   = arr[3];
			rec->Page     = arr[4].toInt();
			rec->FileName = arr[5];

			lstSaveImageFile.AppendList(rec);
		}
	}
	*/
	return true;
}


//===========================================
