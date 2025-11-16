/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoSaveImage\XAutoSaveImage.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XAUTOSAVEIMAGE_H)
#define	XAUTOSAVEIMAGE_H


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

const QString	AUTOSAVEIMAGE_FILEEXTENTION = "piy";

class	AutoSaveImageItem;
class	AutoSaveImageInLayer;
class	AutoSaveImageBase;
class	FileEntryListContainer;
class   SaveImageFileListContainer;
class   CmdImageFileList;
class	SaveImageFileListContainer;
class	CmdSearchFileList;

const int	CompressBuffSize	= 10000000;

class	AutoSaveImageThreshold : public AlgorithmThreshold
{
public:

	AutoSaveImageThreshold(AutoSaveImageItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	AutoSaveImageItem : public AlgorithmItemPLI
{
public:

	AutoSaveImageItem(void){}

	const	AutoSaveImageThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const AutoSaveImageThreshold *)GetThresholdBaseReadable(base);	}
	AutoSaveImageThreshold			*GetThresholdW(LayersBase *base=NULL){	return (AutoSaveImageThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new AutoSaveImageThreshold(this);	}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AutoSaveImageItem();	}
	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
};

class	AutoSaveThread : public QThread
{
	AutoSaveImageInLayer *Layer;
	AutoSaveImageBase    *Base;
public:
	QString	FileName;
	QString	FolderName;	//親フォルダの下に作るフォルダ名('/'で区切られることもある)
	QString RootPath;
	int InspectionID;
	int ClusterID;
	int LocalPageNo;
	int GlobalPageNo;
	volatile	bool	StartMode;

	ImageBuffer	*SavedImage;
	BYTE		*CompressBuff1;
	BYTE		*CompressBuff2;

	AutoSaveThread(QObject * parent );
	~AutoSaveThread(void);

	void	Initial(int n ,AutoSaveImageInLayer *Layer,AutoSaveImageBase *Base);

	virtual void run ()	override;

	bool	CopyFromTarget(void);
	bool	CopyFromMaster(void);
	void	CopyToTarget(void);
	bool	SaveLayerTarget(void);
	bool	LoadLayerTarget(QString FileName);
	QString	GetRootPath(int n);

public slots:
	void SlotFinished();
	bool	CopyFrom(ImageBuffer &ImageBuff);
};

class   AutoSaveImageInLayer : public AlgorithmInLayerPLI
{
	AutoSaveThread	**SThread;
	ImageBuffer		*MiniImage;
public:
	QString FolderNameFormat;	//QDateTimeでtoString()できるフォーマットyyyy-mm-dd/hhなど　区切り/もOK
	
	
	QStringList	FileNames;
	int	CyclicNumb;


	AutoSaveImageInLayer(AlgorithmInPageRoot *parent);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType)	override
		{	
			AutoSaveImageItem	*a=new AutoSaveImageItem();	
			a->SetParent(this);
			return a;
		}
	bool	SaveLayerTarget(ImageBuffer *SavedImage, QString FilePath 
					,BYTE *CompressBuff,BYTE *CompressBuff2);
	bool	LoadLayerTarget(ImageBuffer *Dest, QString FileName	
					,BYTE *CompressBuff,BYTE *CompressBuff2);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	ExeResult	ExecutePreAlignment(int ExeID ,ResultInLayerRoot *Res)	override;

	bool	SaveTarget(void);
	bool	SaveMaster(void);

	int		GetFileEntries(FileEntryListContainer &Dest, int MasterCode,int Page , int Layer);
	bool	LoadFileToTarget(int64 InspectionID, int MasterCode,int LotAutoCount,int Page , int Layer);

	bool	LoadFileToMaster(QString FileName, int Page, int Layer);
	bool	LoadFileToTarget(QString FileName);
	bool	LoadFileTo(const QString &FileName ,ImageBuffer &DestImage);

	QString MakeDirPath(QString RootPath, QString &DefaultFolderName, int LocalPageNo);
	QString MakeFileName(int layerNumb=-1);
	QString MakeFileName(int64 InspectionID, int MasterCode, int LotAutoCount, int LocalPageNo, int GlobalPageNo, int Layer);
	QString MakeFileMask(int MasterCode, int Page, int Layer);
private:
	QStringList GetRootPathList(void);

};


class   AutoSaveImageInPage : public AlgorithmInPagePLI
{
public:
	bool	AutoSaveON;

	AutoSaveImageInPage(AlgorithmBase *parent);

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new AutoSaveImageInLayer(parent);	}

	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,ResultInPageRoot *Res)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	AutoSaveImageBase : public AlgorithmBase
{
public:
	int32	PartialDot;		//間引いて保存する際の間引くドット数
	QString	SavedFolder1;	//8つあるのは外付けUSBメディアを抜き差ししながら保存するかららしい
	QString	SavedFolder2;
	QString	SavedFolder3;
	QString	SavedFolder4;
	QString	SavedFolder5;
	QString	SavedFolder6;
	QString	SavedFolder7;
	QString	SavedFolder8;
	QString	SavedFolder9;
	QString	SavedFolder10;
	int		MaxBufferNumb;
	int		AlarmCountLimit;
	bool	StandardFolder;
	bool	CompressMode;
	int		SleepTimeForSave;
	int		MaxCountToSave;

	int		CurrentFolderNumber;

	QDateTime		StoredTime;

	AutoSaveImageBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new AutoSaveImageInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("AutoSaveImage");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigAutoSaveImage.dat");		}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	QStringList GetRootPathList(void);

	void GetAutoSaveImageList(CmdImageFileList *cmd);
	bool MakeAutoSaveImageList(QString strDir, SaveImageFileListContainer &lstSaveImageFile);
	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,ResultBaseForAlgorithmRoot *Res)	override;
private:
	void		SearchFileList(QString &Folder,CmdSearchFileList *Ret);
	QDateTime	MakeQDateTime(QString &filderName);
	QDateTime	MakeDateHour(QDateTime &s);
	void		FindFiles(QString &SearchPath, CmdSearchFileList *Ret);
	bool		NextFolder(void);
};

//==================================================================================

class	FileEntryList : public NPList<FileEntryList>
{
public:
	int32		MasterCode;
	int32		LotAutoCount;
	int			Page;
	int32		Layer;
	int64		InspectionID;
	QString		FileName;
	QDateTime	FileStamp;

	FileEntryList(void)
	{
		MasterCode	=-1;
		LotAutoCount=-1;
		Page		=0;
		Layer		=0;
		InspectionID=0;
	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	FileEntryList	&operator=(FileEntryList &src);
};

class	FileEntryListContainer : public NPListPack<FileEntryList>
{
public:
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	FileEntryListContainer	&operator=(FileEntryListContainer &src);
	FileEntryListContainer	&operator+=(FileEntryListContainer &src);
};

class	CmdGetFileEntries: public GUIDirectMessage
{
public:
	int	LocalPage;
	FileEntryListContainer	Entries;

	CmdGetFileEntries(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdLoadFile: public GUIDirectMessage
{
public:
	int	LocalPage;
	int	LotAutoCount;
	int	InspectionID;
	QString	FileName;

	CmdLoadFile(LayersBase *base):GUIDirectMessage(base){}
};

class MsgInitialAutoSaveImageThread: public GUIDirectMessage
{
public:
	QString FilePath;
	int	LocalPage;
	int	LotAutoCount;
	int	InspectionID;
	MsgInitialAutoSaveImageThread(LayersBase *base):GUIDirectMessage(base){}
};

class MsgDestroyAutoSaveImageThread: public GUIDirectMessage
{
public:
	QString FilePath;
	int	LocalPage;
	int	LotAutoCount;
	int	InspectionID;
	MsgDestroyAutoSaveImageThread(LayersBase *base):GUIDirectMessage(base){}
};

class SaveImageFileList : public NPList<SaveImageFileList>
{
public:
	QString FileDrv;
	QString FileDate;
	QString LotNo;
	QString BaseNoStr;
	QString FileTime;
	int Page;
	QString FileName;
	QString FilePath;

	int	BaseNoInt;
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	SaveImageFileList	&operator=(SaveImageFileList &src);
};

class SaveImageFileListContainer : public NPListPack<SaveImageFileList>
{
public:
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	SaveImageFileListContainer	&operator=(SaveImageFileListContainer &src);
	SaveImageFileListContainer	&operator+=(SaveImageFileListContainer &src);

	void sort();
};

class CmdImageFileList: public GUIDirectMessage
{
public :
	SaveImageFileListContainer SaveImageList;
	QString strDir1;
	QString strDir2;

	CmdImageFileList(LayersBase *base):GUIDirectMessage(base){}
};

class CmdImageLoadFile : public GUIDirectMessage
{
public :
	QString FileName;
	int	LocalPage;
	CmdImageLoadFile(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdGetLotStringList : public GUIDirectMessage
{
public :
	QStringList	LotList;
	CmdGetLotStringList(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSetLotString : public GUIDirectMessage
{
public :
	QString	LotString;
	CmdSetLotString(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdGetRootPathList : public GUIDirectMessage
{
public :
	QStringList	RootPaths;
	CmdGetRootPathList(LayersBase *base):GUIDirectMessage(base){}
};

class	BandImageFileList : public NPList<BandImageFileList>
{
public:
	QString		BaseFileName;
	QStringList	EachFileNames;

	BandImageFileList(void){}

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);

	BandImageFileList	&operator=(BandImageFileList &src);
};

class	BandImageFileContainer : public NPListPack<BandImageFileList>
{
public:
	BandImageFileContainer(void){}

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);

	BandImageFileContainer	&operator=(BandImageFileContainer &src);
};


class	CmdSearchFileList : public GUIDirectMessage
{
public :
	QStringList	RootPaths;
	QDateTime	TimeFrom;
	QDateTime	TimeTo;

	BandImageFileContainer	RetFile;

	CmdSearchFileList(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdLoadBandList : public GUIDirectMessage
{
public :
	QStringList			FileNames;
	ImageBuffer			*Buff[100];
	int					BufferDimCounts;

	CmdLoadBandList(LayersBase *base):GUIDirectMessage(base){}
};

class CmdSaveImage : public GUIDirectMessage
{
public :
	bool	MasterImage;

	CmdSaveImage(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdReqFolderList : public GUIDirectMessage
{
public :
	QStringList	FolderList;

	CmdReqFolderList(LayersBase *base):GUIDirectMessage(base){}
	CmdReqFolderList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetFolderNumber : public GUIDirectMessage
{
public :
	int		FolderNumber;

	CmdSetFolderNumber(LayersBase *base):GUIDirectMessage(base){}
	CmdSetFolderNumber(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAutoSaveON: public GUIDirectMessage
{
public:
	bool	AutoSaveON;

	CmdAutoSaveON(LayersBase *base):GUIDirectMessage(base){}
};

#endif

