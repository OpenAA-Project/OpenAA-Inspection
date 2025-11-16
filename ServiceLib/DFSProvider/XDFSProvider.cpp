#include "XDFSProvider.h"
#include "XGeneralFunc.h"
#include "DFSProvider.h"
#include <QDir>
#include "XErrorCode.h"
#include "XDFSFilterBase.h"

extern	QString	ProviderName;

PathClass::PathClass(void)
{
	DLL_GetDLLType		=NULL;
	DLL_GetName			=NULL;
	DLL_GetVersion		=NULL;
	DLL_GetSystemVersion=NULL;
	DLL_GetExplain		=NULL;
	DLL_CheckCopyright	=NULL;
	DLL_Initial			=NULL;
	DLL_Close			=NULL;
	DLL_Load			=NULL;
	DLL_Save			=NULL;	
	DLL_ShowSetting		=NULL;	
	DLL_ExecuteSaveFileInDFS	=NULL;

	DFSFilterInst	=NULL;
	Priority		=0;
}
PathClass::~PathClass(void)
{
	if(DFSFilterInst!=NULL){
		if(DLL_Close!=NULL){
			DLL_Close(DFSFilterInst);
		}
		DFSFilterInst=NULL;
	}
}

bool	PathClass::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,Path)==false)
		return false;
	if(::Save(f,NetworkPath)==false)
		return false;
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,DFSFilterDLLFileName)==false)
		return false;
	if(::Save(f,DFSFilterParameter)==false)
		return false;
	if(DFSFilterDLLFileName.isEmpty()==false && DFSFilterInst!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		DFSFilterInst->Save(&Buff);
		QByteArray	Array=Buff.buffer();

		if(::Save(f,Array)==false)
			return false;
	}

	return true;
}

bool	PathClass::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,Path)==false)
		return false;
	if(::Load(f,NetworkPath)==false)
		return false;
	if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,DFSFilterDLLFileName)==false)
		return false;
	if(::Load(f,DFSFilterParameter)==false)
		return false;
	if(DFSFilterInst!=NULL){
		if(DLL_Close!=NULL){
			DLL_Close(DFSFilterInst);
		}
		DFSFilterInst=NULL;
	}
	if(DFSFilterDLLFileName.isEmpty()==false){
		int32 ErrorCode;
		if(LoadDLL(ErrorCode)==false){
			return false;
		}
		if(DFSFilterInst!=NULL){
			QByteArray	Array;
			if(::Load(f,Array)==false)
				return false;
			QBuffer	RBuff(&Array);
			RBuff.open(QIODevice::ReadOnly);
			DFSFilterInst->Load(&RBuff);
		}
	}
	return true;
}

bool	PathClass::LoadDLL(int32 &ErrorCode)
{
	DllLib.setFileName(DFSFilterDLLFileName);
	if(DllLib.load()==false){
		return(false);
	}
	if(DFSFilterInst!=NULL){
		if(DLL_Close!=NULL){
			DLL_Close(DFSFilterInst);
		}
		DFSFilterInst=NULL;
	}

	DLL_GetDLLType		=(WORD	(*)(void))DllLib.resolve("DLL_GetDLLType");
	if(DLL_GetDLLType==NULL){
		ErrorCode=Error_DFSFilter_NoFunc_DLL_GetDLLType;
		return(false);
	}
	DLL_GetName			=(bool (*)(QString &str))DllLib.resolve("DLL_GetName");
	if(DLL_GetName==NULL){
		ErrorCode=Error_DFSFilter_NoFunc_DLL_GetName;
		return(false);
	}
	DLL_GetVersion		=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	if(DLL_GetVersion==NULL){
		ErrorCode=Error_DFSFilter_NoFunc_DLL_GetVersion;
		return(false);
	}
	DLL_GetExplain				=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");
	if(DLL_GetExplain==NULL){
		ErrorCode=Error_DFSFilter_NoFunc_DLL_GetExplain;
		return(false);
	}

	DLL_CheckCopyright			=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");

	DLL_Initial			=(XDFSFilterBase *(*)(const QString &ParamStr))DllLib.resolve("DLL_Initial");
	if(DLL_Initial==NULL){
		ErrorCode=Error_DFSFilter_NoFunc_DLL_Initial;
		return(false);
	}
	DLL_Close			=(bool (*)(XDFSFilterBase *handle))DllLib.resolve("DLL_Close");
	if(DLL_Close==NULL){
		ErrorCode=Error_DFSFilter_NoFunc_DLL_Close;
		return(false);
	}
	DLL_Load			=(bool (*)(XDFSFilterBase *handle ,QIODevice &str))DllLib.resolve("DLL_Load");
	if(DLL_Load==NULL){
		ErrorCode=Error_DFSFilter_NoFunc_DLL_Load;
		return(false);
	}
	DLL_Save			=(bool (*)(XDFSFilterBase *handle,QIODevice &str))DllLib.resolve("DLL_Save");
	if(DLL_Save==NULL){
		ErrorCode=Error_DFSFilter_NoFunc_DLL_Save;
		return(false);
	}
	DLL_ShowSetting		=(bool (*)(XDFSFilterBase *handle, QWidget *parent))DllLib.resolve("DLL_ShowSetting");
	if(DLL_ShowSetting==NULL){
		ErrorCode=Error_DFSFilter_NoFunc_DLL_ShowSetting;
		return(false);
	}
	DLL_ExecuteSaveFileInDFS	=(bool (*)(XDFSFilterBase *handle ,FileSaveAttr *SavedAttr 
														,const QString &Provider ,const QString &LocalPath
														,int &Permit))DllLib.resolve("DLL_ExecuteSaveFileInDFS");
	if(DLL_ExecuteSaveFileInDFS==NULL){
		ErrorCode=Error_DFSFilter_NoFunc_DLL_ExecuteSaveFileInDFS;
		return(false);
	}

	DLL_GetName(FilterName);

	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			return false;
		}
	}
	if(DLL_Initial!=NULL){
		DFSFilterInst	=DLL_Initial(DFSFilterParameter);
	}

	ErrorCode=Error_Nothing;
	return(true);	
}

static	void	SearchRecPath(QString &CPath ,QStringList &AbsPathList)
{
	QDir	cd(CPath);
	QFileInfoList	FolderInfo=cd.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot,QDir::Name);
	for(int i=0;i<FolderInfo.count();i++){
		QString	AbsPath=FolderInfo[i].absoluteFilePath();
		AbsPathList.append(AbsPath);
		SearchRecPath(AbsPath ,AbsPathList);
	}
}

void	PathClass::ReqEnumFolders(TreeFolderContainer &FolderData)
{
	QDir	cd(Path);

	QStringList		AbsPathList;
	SearchRecPath(Path,AbsPathList);
	for(int i=0;i<AbsPathList.count();i++){
		QString	RelativePath=cd.relativeFilePath(AbsPathList[i]);
		FolderData.AddPath(RelativePath);
	}
}

void	PathClass::ReqEnumFiles(const QString &RelativePath ,FileAttrContainer &FilesData)
{
	QString	tPath=Path;
	if(RelativePath.isEmpty()==false)
		tPath+=::GetSeparator()+RelativePath;
	QDir	cd(tPath);
	QFileInfoList	FInfo=cd.entryInfoList(QDir::Files | QDir::NoDotAndDotDot,QDir::Name);
	for(int i=0;i<FInfo.count();i++){
		//QString	AbsPath	=FInfo[i].absolutePath();
		FileAttrList	*a=new FileAttrList();
		a->RelativePath	=RelativePath;
		a->FileName		=FInfo[i].fileName();
		a->FileSize		=FInfo[i].size();
		a->Provider		=ProviderName;
		a->FileStamp	=FInfo[i].lastModified();
		FilesData.AppendList(a);
	}
}
int		PathClass::GetPriorityToSaveFile(FileSaveAttr &SaveAttr)
{
	if(DFSFilterInst!=NULL && DLL_ExecuteSaveFileInDFS!=NULL){
		int		Permit;
		if(DLL_ExecuteSaveFileInDFS(DFSFilterInst,&SaveAttr,ProviderName,Path,Permit)==true){
			return Permit;
		}
	}
	return Priority;
}
void	PathClass::ReqLoadFile(FileLoadAttr &LoadedAttr,QString &DestNetworkFile)
{
	QString	tPath=Path;
	if(LoadedAttr.SourceRelativePath.isEmpty()==false)
		tPath+=::GetSeparator()+LoadedAttr.SourceRelativePath;
	QDir	cd(tPath);
	if(cd.exists(LoadedAttr.FileName)==true){
		if(LoadedAttr.SourceRelativePath.isEmpty()==false)
			DestNetworkFile	=	NetworkPath + ::GetSeparator()+ LoadedAttr.SourceRelativePath+::GetSeparator()+ LoadedAttr.FileName;
		else
			DestNetworkFile	=	NetworkPath + ::GetSeparator() + LoadedAttr.FileName;
	}
}

void	PathClass::ReqRemoveFile(FileLoadAttr &LoadedAttr)
{
	QString	tPath=Path;
	if(LoadedAttr.SourceRelativePath.isEmpty()==false)
		tPath+=::GetSeparator()+LoadedAttr.SourceRelativePath;
	QDir	cd(tPath);
	if(cd.exists(LoadedAttr.FileName)==true){
		cd.remove(LoadedAttr.FileName);
	}
}
bool	PathClass::ReqAddFolder(AddFolderAttr &AddedAttr)
{
	QString	tPath=Path;
	if(AddedAttr.SourceRelativePath.isEmpty()==false)
		tPath+=::GetSeparator()+AddedAttr.SourceRelativePath;
	QDir	cd(tPath);
	if(cd.mkdir(AddedAttr.NewFolderName)==true)
		return true;
	return false;
}

bool	PathClass::ReqRemoveFolder(const QString &RelativeFolder)
{
	QString	tPath=Path;
	if(RelativeFolder.isEmpty()==false)
		tPath+=::GetSeparator()+RelativeFolder;
	QDir	cd;
	if(cd.rmdir(tPath)==true)
		return true;
	return false;
}

bool	PathClass::ReqFindFile(const QString &RelativeFolder,const QString &FileName,FileFindAttr &FFindInfo)
{
	QString	tPath=Path;
	if(RelativeFolder.isEmpty()==false)
		tPath+=::GetSeparator()+RelativeFolder;
	QDir	cd(tPath);
	if(cd.exists(FileName)==true){
		QFileInfo	FInfo(tPath+::GetSeparator()+FileName);
		FFindInfo.FileName	=FileName;
		FFindInfo.FileSize	=FInfo.size();
		FFindInfo.FileStamp	=FInfo.lastModified();
		if(RelativeFolder.isEmpty()==false)
			FFindInfo.NetworkPath=	NetworkPath + ::GetSeparator()+ RelativeFolder+::GetSeparator()+ FileName;
		else
			FFindInfo.NetworkPath		=NetworkPath + ::GetSeparator() + FileName;
		FFindInfo.Provider				=ProviderName;
		FFindInfo.SourceRelativePath	=RelativeFolder;
		return true;
	}
	return false;
}


//-------------------------------------------------------

DFSClientInProvider::DFSClientInProvider(QObject *parent ,const QString &IPAddress,int PortNumber)
	:DFSSocket(parent ,IPAddress,PortNumber)
{
	Parent=(DFSProvider *)parent;
}


void	DFSClientInProvider::Received(int cmd ,QByteArray &data)
{
	if(cmd==DFSCmd_ReqEnumFolders){
		TreeFolderContainer	FolderData;
		Parent->ReqEnumFolders(FolderData);

		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		FolderData.Save(&Buff);
		Send(DFSCmd_AckEnumFolders,Buff.buffer());
	}
	else if(cmd==DFSCmd_ReqEnumFiles){
		FileAttrContainer	FilesData;

		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		QString	RelativePath;
		::Load(&RBuff,RelativePath);
		Parent->ReqEnumFiles(RelativePath,FilesData);

		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		FilesData.Save(&Buff);
		Send(DFSCmd_AckEnumFiles,Buff.buffer());
	}
	else if(cmd==DFSCmd_ReqSaveFile){
		FileSaveAttr	SaveAttr;

		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		SaveAttr.Load(&RBuff);
		
		QString	DestFolder;
		int32	Priority;
		Parent->ReqSaveFile(SaveAttr,DestFolder,Priority);

		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		::Save(&Buff,DestFolder);
		::Save(&Buff,Priority);
		Send(DFSCmd_AckSaveFile,Buff.buffer());
	}
	else if(cmd==DFSCmd_ReqLoadFile){
		FileLoadAttr	LoadedAttr;

		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		LoadedAttr.Load(&RBuff);
		
		QString	DestNetworkFile;
		Parent->ReqLoadFile(LoadedAttr,DestNetworkFile);

		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		::Save(&Buff,DestNetworkFile);
		Send(DFSCmd_AckLoadFile,Buff.buffer());
	}
	else if(cmd==DFSCmd_ReqRemoveFile){
		FileLoadAttr	LoadedAttr;

		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		LoadedAttr.Load(&RBuff);
		
		Parent->ReqRemoveFile(LoadedAttr);

		Send(DFSCmd_AckRemoveFile);
	}
	else if(cmd==DFSCmd_ReqMakeFolder){
		AddFolderAttr	AddedAttr;

		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		AddedAttr.Load(&RBuff);
		
		Parent->ReqAddFolder(AddedAttr);

		Send(DFSCmd_AckMakeFolder);
	}
	else if(cmd==DFSCmd_ReqRemoveFolder){
		QString	RelativeFolder;

		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		::Load(&RBuff,RelativeFolder);
		
		Parent->ReqRemoveFolder(RelativeFolder);

		Send(DFSCmd_AckRemoveFolder);
	}
	else if(cmd==DFSCmd_ReqFindFile){
		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		QString		RelativeFolder;
		QString		FileName;
		::Load(&RBuff,RelativeFolder);
		::Load(&RBuff,FileName);
		
		FileFindAttr	FFindInfo;
		Parent->ReqFindFile(RelativeFolder,FileName,FFindInfo);

		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		FFindInfo.Save(&Buff);
		Send(DFSCmd_AckFindFile,Buff.buffer());
	}
}