#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "XFileThread.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XResultDLL.h"
#include "XGeneralFunc.h"
#include "XMLGeneralFunc.h"
#include <QMessageBox>
#include "XNaming.h"
#include "XGeneralStocker.h"
#include "ResultDLLIntoFile.h"
#include "XLotInformation.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "swap.h"
#include "XResult.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "XExecuteInspectBase.h"
//#include "XExecuteInspectFast.h"
#include "XCriticalFunc.h"
#include "XLogOut.h"
#include "XShadowTree.h"

ResultDLLIntoFile::ResultDLLIntoFile(LayersBase *Base)
	:ResultDLLBaseRoot(Base)
	,RThrrad(Base,this)
{
	OutputLibData		=true;
	SaveNGImage			=false;
	WritePageDirectly	=false;
	DbgDim	=new struct	DbgInfoTable[1000];
	DbgWPoint			=0;
	LastTime			=0;
	LastPath			=/**/"";

	SharedFolder	=/**/"c:\\SharedFolder";
	UseLotNameInFileName	=false;

	ResultDLLBaseRoot::SetParam(&OutputLibData			, /**/"Data"	,/**/"OutputLibData"	,"if checked, output library data to XML server"	,0);
	ResultDLLBaseRoot::SetParam(&SharedFolder			, /**/"Data"	,/**/"SharedFolder"		,"Folder into result, accessing by Review");
	ResultDLLBaseRoot::SetParam(&SaveNGImage			, /**/"Data"	,/**/"SaveNGImage"		,"Mode to save NG image");
	ResultDLLBaseRoot::SetParam(&UseLotNameInFileName	, /**/"Data"	,/**/"UseLotNameInFileName"		,"Use LotName in RDT file name");
	ResultDLLBaseRoot::SetParam(&WritePageDirectly		, /**/"Data"	,/**/"WritePageDirectly"		,"Write page data directly");

	RThrrad.start();
}

ResultDLLIntoFile::~ResultDLLIntoFile(void)
{
	RThrrad.Terminated=true;
	delete	[]DbgDim;
	DbgDim=NULL;
	RThrrad.wait(1000);
}

	
QString	ResultDLLIntoFile::GetLotID(void)
{
	return GetLayersBase()->GetLot(0)->GetLotID();
}

QString	ResultDLLIntoFile::GetLotName(void)
{
	return GetLayersBase()->GetLot(0)->GetLotName();
}

int		ResultDLLIntoFile::GetMachineID(void)
{
	return GetLayersBase()->GetMachineID();
}
int		ResultDLLIntoFile::GetMasterCode(void)
{
	return GetLayersBase()->GetMasterCode();
}
QString	ResultDLLIntoFile::GetMasterName(void)
{
	return GetLayersBase()->GetMasterName();
}



bool	ResultDLLIntoFile::OutputCommon(ResultInspection &Res
										,ResultInspectionForStockPointerContainer &ShadowResStocks)
{
	/*
	if(OpenOperation(&HandleCommon)==false){
		return false;
	}
	*/
	QVariantList ReturnValue;
	QVariantList ArgValue;
	ArgValue.append(Res.GetInspectionID());
	GetLayersBase()->GetGeneralStocker()->GetData("InResultOutputCommon",ReturnValue,ArgValue);
	GetLayersBase()->GetLogCreater()->PutLogA1(__LINE__,"OutputCommon:Start",Res.GetInspectionID());

	return OutputCommonRaw(Res,ShadowResStocks);
}

bool	ResultDLLIntoFile::OutputCommonRaw(ResultInspection &Res
											,ResultInspectionForStockPointerContainer &ShadowResStocks)
{
	struct	ResultHeader	Header;

	DWORD	d=::GetComputerMiliSec();
	while((::GetComputerMiliSec()-d)<2000){
		if(Res.GetPriorityCounter()==0){
			break;
		}
		GSleep(10);
	}
	Res.SetPriorityCounter(0);

	XDateTime QLocal=Res.GetStartTimeForInspection();

	Header.InspectionID	=Res.GetInspectionID();
	Header.Year			=QLocal.year()-2000;
	Header.Month		=QLocal.month();
	Header.Day			=QLocal.day();
	Header.Hour			=QLocal.hour();
	Header.Minute		=QLocal.minute();
	Header.Second		=QLocal.second();
	Header.MachineID	=GetMachineID();
	Header.MasterCode	=GetMasterCode();
	Header.LotAutoCount	=GetLayersBase()->GetLot(0)->GetLotAutoCount();
	Header.PhaseNumb	=GetPhaseNumb();
	Header.PageNumb		=GetPageNumb();
	int	RemarkLen=Res.GetRemarkStr(Header.RemarkData,sizeof(Header.RemarkData));
	memset(&Header.RemarkData[RemarkLen],0,sizeof(Header.RemarkData)-RemarkLen);
	Header.RemarkByte	=RemarkLen;
	
	Header.Result=0;
	NGFlag	=0;

	bool3 eOK;
	bool eMaxError;
	bool eTimeOver;
	Res.GatherResult(eOK ,eMaxError , eTimeOver,true,false);
	if(eTimeOver==true)
		Header.Result		=100;
	if(eMaxError==true)
		Header.Result		=101;
	if(eOK!=none3){
		if(eOK==true3){
			Header.Result		=1;
			NGFlag	=1;
		}
		else if(eOK==false3){
			Header.Result		=2;
			NGFlag	=2;
		}
		else{
			Header.Result		=0;
			NGFlag	=0;
		}
	}

	QString	FileName=GetFileName();
	QFileInfo	Info(FileName);
	QString	Path=Info.absolutePath();

	if(LastPath!=Path){
		DirectoryThread	Directory(GetLayersBase());
		Directory.ForceDirectories(Path);
		LastPath=Path;
	}
	FileThread	File(GetLayersBase(),FileName);
	if(File.open(QIODevice::Append)==false){
		return false;
	}
	GetLayersBase()->GetLogCreater()->PutLogA1(__LINE__,"OutputCommonRaw:Open",Res.GetInspectionID());

	//QBuffer	Buff;
	//Buff.open(QIODevice::WriteOnly);

	char	Ch='C';
	//if(::Save(&File,Ch)==false){
	if(File.Save(Ch)==false){
		return false;
	}

	if(File.write((const char *)&Header,sizeof(Header))!=sizeof(Header))
		return false;

	DbgDim[DbgWPoint].OTime=QLocal;
	DbgDim[DbgWPoint].InspectionID	=Res.GetInspectionID();
	DbgDim[DbgWPoint].FileName		=FileName;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(int page=0;page<GetPageNumb();page++){
			DbgDim[DbgWPoint].SaveInPage[phase][page]=false;
		}
	}
	DWORD	D=::GetComputerMiliSec();
	DbgDim[DbgWPoint].DiffMilisec=D-LastTime;
	LastTime=D;

	QString LotID;
	if(WritePageDirectly==true){
		//GSleep(50);
		for(int phase=0;phase<GetPhaseNumb();phase++){
			for(int page=0;page<GetPageNumb();page++){
				if(OutputResult(ShadowResStocks,File,GetMasterCode() ,Res.GetStartTimeForInspection() 
								,&Res 
								,LotID,phase, page)==false){
					return false;
				}
				DbgDim[DbgWPoint].SaveInPage[phase][page]=true;
			}
		}
	}
	DbgWPoint++;
	if(DbgWPoint>=1000){
		DbgWPoint=0;
	}
	//File.Save(Buff.buffer());
	if(GetParamGlobal()->UseSystemResultStocker==true){
		GetLayersBase()->PushSystemResult(File.GetData());
	}
	File.flush();

	return true;
}

bool	ResultDLLIntoFile::OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
										,int32 MachineID ,const XDateTime &InspectedTime 
										,ResultInspection *Res 
										,const QString &LotID,int phase, int localPage)
{
	if(Res->GetResultDLLBase()==NULL){
		return true;
	}
	if(WritePageDirectly==false){

		QString	FileName=GetFileName();
		QFileInfo	Info(FileName);
	
		FileThread	File(GetLayersBase(),FileName);
		if(File.open(QIODevice::Append)==false){
			return false;
		}
		if(OutputResult(ShadowResStocks
						,File,MachineID ,InspectedTime 
						,Res 
						,LotID,phase, localPage)==false){
			return false;
		}
		File.flush();
	}
	return true;
}

static	int	ResDbg=0;

bool	ResultDLLIntoFile::OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
										,FileThread &File,int32 MachineID 
										,const XDateTime &InspectedTime 
										,ResultInspection *Res 
										,const QString &LotID,int phase, int localPage)
{
	GetLayersBase()->GetLogCreater()->PutLog(__LINE__,"OutputResult:Start");
	char	Ch='S';
	if(File.Save(Ch)==false){
		return false;
	}
	int32	iPhase=phase;
	if(File.Save(iPhase)==false)
		return false;
	int32	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
	if(File.Save(GlobalPage)==false)
		return false;

	int32	AlgoNumb=0;
	for(ResultBaseForAlgorithmRoot *B=Res->GetResultBaseDimFirst();B!=NULL;B=B->GetNext()){
		AlgoNumb++;
	}
	AlgoNumb+=200000000;
	if(File.Save(AlgoNumb)==false){
		return false;
	}
	int32	Ver=3;
	if(File.Save(Ver)==false){
		return false;
	}
	int32	ShadowTotalCount=GetLayersBase()->GetShadowTotalChildrenCount();
	if(File.Save(ShadowTotalCount)==false){
		return false;
	}

	int	eWrittenNGCount=0;
	for(ResultBaseForAlgorithmRoot *B=Res->GetResultBaseDimFirst();B!=NULL;B=B->GetNext()){
		ResultBasePhase		*RPh=B->GetPageDataPhase(phase);
		ResultInPageRoot	*R=RPh->GetPageData(localPage);
		int	tmpeWrittenNGCount=0;
		if(R->OutputResult(Res->GetLayersBase()->GetGlobalPageFromLocal(localPage) 
							,B->GetLogicDLL(), &File,tmpeWrittenNGCount)==false){
			return false;
		}
		eWrittenNGCount+=tmpeWrittenNGCount;
	}
	bool3 eOK;
	bool eMaxError;
	bool eTimeOver;
	Res->GatherResult(eOK ,eMaxError , eTimeOver,true,false);
	if((NGFlag==1 && eOK!=true3) || (NGFlag==2 && eOK!=false3)){
		ResDbg++;
	}
	if(NGFlag==2 && eWrittenNGCount==0){
		ResDbg++;
	}
	if(GetLayersBase()->ShadowOutputResult(Res
								,LotID,phase,localPage
								,File)==false){
		return false;
	}

	NGImageContainerInPhase	*NGPhase=Res->GetNGImageInPhase(phase);
	int32	N=0;
	if(NGPhase!=NULL){
		if(NGPhase->GetNGImageInPage(localPage)!=NULL){
			for(NGImage *m=NGPhase->GetNGImageInPage(localPage)->GetNGImageDataFirst();m!=NULL;m=m->GetNext()){
				N++;
			}
		}
	}
	if(NGFlag==2 && N<=0){
		ResDbg++;
	}
	N+=GetLayersBase()->ShadowGetNGImageCount(Res
								,LotID,phase,localPage);
	if(File.Save(N)==false){
		return false;
	}
	if(NGFlag==2 && N<=0){
		ResDbg++;
	}

	int	ImageNumb=0;
	if(NGPhase!=NULL){
		if(NGPhase->GetNGImageInPage(localPage)!=NULL){
			for(NGImage *m=NGPhase->GetNGImageInPage(localPage)->GetNGImageDataFirst();m!=NULL;m=m->GetNext()){
				int mx1,my1,mx2,my2;
				m->GetXY(mx1,my1,mx2,my2);

				struct	NGIInfo	NGIData;
				NGIData.X	=mx1;
				NGIData.Y	=my1;
				NGIData.W	=m->GetWidth();
				NGIData.H	=m->GetHeight();
				NGIData.MX	=m->GetMx();
				NGIData.MY	=m->GetMy();
				NGIData.IDX	=Res->GetLayersBase()->GetGlobalPageFromLocal(localPage);
				NGIData.Index=m->GetNumber();
				if(File.write((const char *)&NGIData,sizeof(NGIData))!=sizeof(NGIData)){
					return false;
				}
				ImageNumb++;
			}
		}
	}
	if(NGFlag==2 && ImageNumb<=0){
		ResDbg++;
	}
	if(GetLayersBase()->ShadowWriteNGImage(Res
								,LotID,phase,localPage
								,File)==false){
		return false;
	}

	//if(localPage==0 && N!=0){
	if(N!=0){
		int Milisec;
		QString	IFileName=Res->GetResultDLLBase()->CreateNGFileNameForSlaveMilisecWithDrive(localPage,Res,Milisec);
		char	IFileNameStr[64];
		::QString2Char(IFileName,IFileNameStr ,sizeof(IFileNameStr));
		int16	FileNameLen=strlen(IFileNameStr)+1;
		if(File.Save(FileNameLen)==false){
			return false;
		}
		if(File.write((const char *)IFileNameStr,FileNameLen)!=FileNameLen){
			return false;
		}
		if(SaveNGImage==true){
			QFileInfo	Q(IFileName);
			QString	path=Q.dir().absolutePath();
			QDir	D;
			D.mkpath (path);

			FileThread	F(GetLayersBase(),IFileName);
			if(F.open(QIODevice::WriteOnly)==true){
				if(Res->SaveNGImage(&F,localPage)==false){
					F.flush();
					return false;
				}
				int32	ShadowNumb=GetLayersBase()->GetShadowTotalChildrenCount();
				if(F.Save(ShadowNumb)==false){
					F.flush();
					return false;
				}
				if(GetLayersBase()->ShadowSaveNGImage(Res
											,LotID,phase,localPage
											,F)==false){
					F.flush();
					return false;
				}
				F.flush();
			}
			else{
				return false;
			}
		}
	}
	else{
		int16	FileNameLen=0;
		if(File.Save(FileNameLen)==false){
			return false;
		}
	}
	return true;
}


bool	ResultDLLIntoFile::OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
										,QBuffer &File,int32 MachineID 
										,const XDateTime &InspectedTime 
										,ResultInspection *Res 
										,const QString &LotID,int phase, int localPage)
{
	GetLayersBase()->GetLogCreater()->PutLog(__LINE__,"OutputResult:Start");
	char	Ch='S';
	if(::Save(&File,Ch)==false){
		return false;
	}
	int32	iPhase=phase;
	if(::Save(&File,iPhase)==false)
		return false;
	int32	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
	if(::Save(&File,GlobalPage)==false)
		return false;

	int32	AlgoNumb=0;
	for(ResultBaseForAlgorithmRoot *B=Res->GetResultBaseDimFirst();B!=NULL;B=B->GetNext()){
		AlgoNumb++;
	}
	AlgoNumb+=200000000;
	if(::Save(&File,AlgoNumb)==false){
		return false;
	}
	int32	Ver=3;
	if(::Save(&File,Ver)==false){
		return false;
	}
	int32	ShadowTotalCount=GetLayersBase()->GetShadowTotalChildrenCount();
	if(::Save(&File,ShadowTotalCount)==false){
		return false;
	}

	int	eWrittenNGCount=0;
	for(ResultBaseForAlgorithmRoot *B=Res->GetResultBaseDimFirst();B!=NULL;B=B->GetNext()){
		ResultBasePhase		*RPh=B->GetPageDataPhase(phase);
		ResultInPageRoot	*R=RPh->GetPageData(localPage);
		int	tmpeWrittenNGCount=0;
		if(R->OutputResult(Res->GetLayersBase()->GetGlobalPageFromLocal(localPage) 
							,B->GetLogicDLL(), &File,tmpeWrittenNGCount)==false){
			return false;
		}
		eWrittenNGCount+=tmpeWrittenNGCount;
	}
	bool3 eOK;
	bool eMaxError;
	bool eTimeOver;
	Res->GatherResult(eOK ,eMaxError , eTimeOver,true,false);
	if((NGFlag==1 && eOK!=true3) || (NGFlag==2 && eOK!=false3)){
		ResDbg++;
	}
	if(NGFlag==2 && eWrittenNGCount==0){
		ResDbg++;
	}
	if(GetLayersBase()->ShadowOutputResult(Res
								,LotID,phase,localPage
								,File)==false){
		return false;
	}

	NGImageContainerInPhase	*NGPhase=Res->GetNGImageInPhase(phase);
	int32	N=0;
	if(NGPhase!=NULL){
		if(NGPhase->GetNGImageInPage(localPage)!=NULL){
			for(NGImage *m=NGPhase->GetNGImageInPage(localPage)->GetNGImageDataFirst();m!=NULL;m=m->GetNext()){
				N++;
			}
		}
	}
	if(NGFlag==2 && N<=0){
		ResDbg++;
	}
	N+=GetLayersBase()->ShadowGetNGImageCount(Res
								,LotID,phase,localPage);
	if(::Save(&File,N)==false){
		return false;
	}
	if(NGFlag==2 && N<=0){
		ResDbg++;
	}

	int	ImageNumb=0;
	if(NGPhase!=NULL){
		if(NGPhase->GetNGImageInPage(localPage)!=NULL){
			for(NGImage *m=NGPhase->GetNGImageInPage(localPage)->GetNGImageDataFirst();m!=NULL;m=m->GetNext()){
				int mx1,my1,mx2,my2;
				m->GetXY(mx1,my1,mx2,my2);

				struct	NGIInfo	NGIData;
				NGIData.X	=mx1;
				NGIData.Y	=my1;
				NGIData.W	=m->GetWidth();
				NGIData.H	=m->GetHeight();
				NGIData.MX	=m->GetMx();
				NGIData.MY	=m->GetMy();
				NGIData.IDX	=Res->GetLayersBase()->GetGlobalPageFromLocal(localPage);
				NGIData.Index=m->GetNumber();
				if(File.write((const char *)&NGIData,sizeof(NGIData))!=sizeof(NGIData)){
					return false;
				}
				ImageNumb++;
			}
		}
	}
	if(NGFlag==2 && ImageNumb<=0){
		ResDbg++;
	}
	if(GetLayersBase()->ShadowWriteNGImage(Res
								,LotID,phase,localPage
								,File)==false){
		return false;
	}

	//static	int	Error=0;
	//if(N>0 && Res->GetNGImageCount()==0){
	//	Error++;
	//}
	if(localPage==0 && N!=0){
		int Milisec;
		QString	IFileName=Res->GetResultDLLBase()->CreateNGFileNameForSlaveMilisecWithDrive(localPage,Res,Milisec);
		char	IFileNameStr[64];
		::QString2Char(IFileName,IFileNameStr ,sizeof(IFileNameStr));
		int16	FileNameLen=strlen(IFileNameStr)+1;
		if(::Save(&File,FileNameLen)==false){
			return false;
		}
		if(File.write((const char *)IFileNameStr,FileNameLen)!=FileNameLen){
			return false;
		}
		if(SaveNGImage==true){
			QFileInfo	Q(IFileName);
			QString	path=Q.dir().absolutePath();
			QDir	D;
			D.mkpath (path);

			FileThread	F(GetLayersBase(),IFileName);
			if(F.open(QIODevice::WriteOnly)==true){
				if(Res->SaveNGImage(&F,localPage)==false){
					F.flush();
					return false;
				}
				int32	ShadowNumb=GetLayersBase()->GetShadowTotalChildrenCount();
				if(F.Save(ShadowNumb)==false){
					F.flush();
					return false;
				}
				if(GetLayersBase()->ShadowSaveNGImage(Res
											,LotID,phase,localPage
											,F)==false){
					F.flush();
					return false;
				}
				F.flush();
			}
			else{
				return false;
			}
		}
	}
	else{
		int16	FileNameLen=0;
		if(::Save(&File,FileNameLen)==false){
			return false;
		}
	}
	return true;
}



bool	ResultDLLIntoFile::OutputInLotChangedSlave(int LocalPage)
{
	QString	FileName=GetFileName();
	QFileInfo	Info(FileName);

	QFile	File(FileName);
	if(File.open(QIODevice::Append)==false){
		return false;
	}
	char	Ch='N';
	if(::Save(&File,Ch)==false){
		return false;
	}
	int32	N=0;
	NamingBase	*Base=(NamingBase *)(GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Naming"));
	if(Base!=NULL){
		NamingInPage	*P=(NamingInPage *)Base->GetPageData(LocalPage);
		
		for(AlgorithmItemPI	*c=P->GetFirstData();c!=NULL;c=c->GetNext()){
			FlexArea	*AreaPoint=&c->GetArea();
			if(AreaPoint->GetShape().Kind==BlockShape::_sRectangle){
				N++;
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sEllipse){
				N++;
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sRotEllipse){
				N++;
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sRotRectangle){
				N++;
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sRing){
				N++;
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sFree){
				N++;
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sPoly){
				N++;
			}
		}
		if(::Save(&File,N)==false){
			return false;
		}
		for(AlgorithmItemPI	*c=P->GetFirstData();c!=NULL;c=c->GetNext()){

			if(::Save(&File,((NamingItem *)c)->GetItemName())==false){
				return false;
			}
			int32	iGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
			if(::Save(&File,iGlobalPage)==false){
				return false;
			}
			FlexArea	*AreaPoint=&c->GetArea();
			if(AreaPoint->GetShape().Kind==BlockShape::_sRectangle){
				struct	NGAreaRectangle		NGAreaData;
				NGAreaData.Type	='R';
				NGAreaData.X1	=AreaPoint->GetMinX();
				NGAreaData.Y1	=AreaPoint->GetMinY();
				NGAreaData.X2	=AreaPoint->GetMaxX();
				NGAreaData.Y2	=AreaPoint->GetMaxY();
				if(File.write((const char *)&NGAreaData,sizeof(NGAreaData))!=sizeof(NGAreaData)){
					return false;
				}
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sEllipse){
				struct	NGAreaEllipse		NGAreaData;
				NGAreaData.Type	='E';
				NGAreaData.X1	=AreaPoint->GetMinX();
				NGAreaData.Y1	=AreaPoint->GetMinY();
				NGAreaData.X2	=AreaPoint->GetMaxX();
				NGAreaData.Y2	=AreaPoint->GetMaxY();
				if(File.write((const char *)&NGAreaData,sizeof(NGAreaData))!=sizeof(NGAreaData)){
					return false;
				}
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sRotEllipse){
				struct	NGAreaRotEllipse		NGAreaData;
				NGAreaData.Type	='T';
				NGAreaData.Cx	=AreaPoint->GetShape().Shape.bsRotEllipse.Cx;
				NGAreaData.Cy	=AreaPoint->GetShape().Shape.bsRotEllipse.Cy;
				NGAreaData.Rx	=AreaPoint->GetShape().Shape.bsRotEllipse.Rx;
				NGAreaData.Ry	=AreaPoint->GetShape().Shape.bsRotEllipse.Ry;
				NGAreaData.Angle=AreaPoint->GetShape().Shape.bsRotEllipse.Angle;
				if(File.write((const char *)&NGAreaData,sizeof(NGAreaData))!=sizeof(NGAreaData)){
					return false;
				}
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sRotRectangle){
				double	CosS=cos(AreaPoint->GetShape().Shape.bsRotRectangle.Angle);
				double	SinS=sin(AreaPoint->GetShape().Shape.bsRotRectangle.Angle);
				double	Cx=(AreaPoint->GetShape().Shape.bsRotRectangle.X1+AreaPoint->GetShape().Shape.bsRotRectangle.X2)/2.0;
				double	Cy=(AreaPoint->GetShape().Shape.bsRotRectangle.X1+AreaPoint->GetShape().Shape.bsRotRectangle.X2)/2.0;
				double	dX1=AreaPoint->GetShape().Shape.bsRotRectangle.X1-Cx;
				double	dY1=AreaPoint->GetShape().Shape.bsRotRectangle.Y1-Cy;
				double	dX2=AreaPoint->GetShape().Shape.bsRotRectangle.X2-Cx;
				double	dY2=AreaPoint->GetShape().Shape.bsRotRectangle.Y2-Cy;

				double	hX1=dX1*CosS-dY1*SinS+Cx;
				double	hY1=dX1*SinS+dY1*CosS+Cy;
				double	hX2=dX2*CosS-dY1*SinS+Cx;
				double	hY2=dX2*SinS+dY1*CosS+Cy;
				double	hX3=dX2*CosS-dY2*SinS+Cx;
				double	hY3=dX2*SinS+dY2*CosS+Cy;
				double	hX4=dX1*CosS-dY2*SinS+Cx;
				double	hY4=dX1*SinS+dY2*CosS+Cy;

				char	Type='P';
				if(File.write((const char *)&Type,sizeof(Type))!=sizeof(Type)){
					return false;
				}
				int32	PointCount=4;
				if(::Save(&File,PointCount)==false){
					return false;
				}
				int32	Point[4][2];
				Point[0][0]=hX1;
				Point[0][1]=hY1;
				Point[1][0]=hX2;
				Point[1][1]=hY2;
				Point[2][0]=hX3;
				Point[2][1]=hY3;
				Point[3][0]=hX4;
				Point[3][1]=hY4;
				if(File.write((const char *)&Point,sizeof(Point))!=sizeof(Point)){
					return false;
				}
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sRing){
				int	X11=AreaPoint->GetShape().Shape.bsRing.Cx-AreaPoint->GetShape().Shape.bsRing.Rx1;
				int	Y11=AreaPoint->GetShape().Shape.bsRing.Cy-AreaPoint->GetShape().Shape.bsRing.Ry1;
				int	X12=AreaPoint->GetShape().Shape.bsRing.Cx+AreaPoint->GetShape().Shape.bsRing.Rx1;
				int	Y12=AreaPoint->GetShape().Shape.bsRing.Cy+AreaPoint->GetShape().Shape.bsRing.Ry1;
				int	X21=AreaPoint->GetShape().Shape.bsRing.Cx-AreaPoint->GetShape().Shape.bsRing.Rx2;
				int	Y21=AreaPoint->GetShape().Shape.bsRing.Cy-AreaPoint->GetShape().Shape.bsRing.Ry2;
				int	X22=AreaPoint->GetShape().Shape.bsRing.Cx+AreaPoint->GetShape().Shape.bsRing.Rx2;
				int	Y22=AreaPoint->GetShape().Shape.bsRing.Cy+AreaPoint->GetShape().Shape.bsRing.Ry2;
				if(AreaPoint->GetShape().Shape.bsRing.Rx1<AreaPoint->GetShape().Shape.bsRing.Rx2){
					swap(X11,X21);
					swap(Y11,Y21);
					swap(X12,X22);
					swap(Y12,Y22);
				}
				struct	NGAreaRing		NGAreaData;
				NGAreaData.Type	='I';
				NGAreaData.X11	=X11;
				NGAreaData.Y11	=Y11;
				NGAreaData.X12	=X12;
				NGAreaData.Y12	=Y12;
				NGAreaData.X21	=X21;
				NGAreaData.Y21	=Y21;
				NGAreaData.X22	=X22;
				NGAreaData.Y22	=Y22;
				if(File.write((const char *)&NGAreaData,sizeof(NGAreaData))!=sizeof(NGAreaData)){
					return false;
				}
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sFree){
				//sprintf(Buff,"XX");
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sPoly){
				int	Sep=(AreaPoint->GetShape().Shape.bsPoly.PointCount+99)/100;
				char	Type='P';
				if(File.write((const char *)&Type,sizeof(Type))!=sizeof(Type)){
					return false;
				}
				int32	PointCount=0;
				for(int i=0;i<AreaPoint->GetShape().Shape.bsPoly.PointCount;i+=Sep){
					PointCount++;
				}
				if(::Save(&File,PointCount)==false){
					return false;
				}
				for(int i=0;i<AreaPoint->GetShape().Shape.bsPoly.PointCount;i+=Sep){
					int32	Point[2];
					Point[0]=AreaPoint->GetShape().Shape.bsPoly.XY[i].x;
					Point[1]=AreaPoint->GetShape().Shape.bsPoly.XY[i].y;
					if(File.write((const char *)&Point,sizeof(Point))!=sizeof(Point)){
						return false;
					}
				}
			}
		}
	}
	else{
		if(::Save(&File,N)==false){
			return false;
		}
	}

	if(OutputLibData==true){
		char	Ch='O';
		if(::Save(&File,Ch)==false){
			return false;
		}

		N=GetLayersBase()->GetLogicDLLBase()->GetCount();
		if(::Save(&File,N)==false){
			return false;
		}

		QStringList RetInsertStrings;
		for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			QString	AlgoName	=L->GetDLLRoot()
								+QString(/**/":")
								+L->GetDLLName();

			if(::Save(&File,AlgoName)==false){
				return false;
			}

			AlgorithmLibraryContainer	*pLib=L->GetLibContainer();
			if(pLib!=NULL){
				bool	ExistLib=true;
				if(::Save(&File,ExistLib)==false){
					return false;
				}
				IntList	LibIDList;
				AlgorithmBase	*ABase		=L->GetInstance();
				for(int phase=0;phase<GetPhaseNumb();phase++){
					AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(phase);
					IntList	tmpLibIDList;
					AlgorithmInPageRoot	*PPage=Ph->GetPageData(LocalPage);
					if(PPage!=NULL){
						PPage->EnumLibID(tmpLibIDList);
						LibIDList.Merge(tmpLibIDList);
					}
				}
				int32	LibIDListCount=LibIDList.GetCount();
				if(::Save(&File,LibIDListCount)==false){
					return false;
				}
				for(IntClass *s=LibIDList.GetFirst();s!=NULL;s=s->GetNext()){
					if(OutputInLibData(L ,s->GetValue(),&File)==false){
						return false;
					}
				}
			}
			else{
				bool	ExistLib=false;
				if(::Save(&File,ExistLib)==false){
					return false;
				}
			}
		}
	}

	return true;
}
bool	ResultDLLIntoFile::OutputInLib(void)
{
	if(OutputLibData==false){
		return true;
	}
	QString	FileName=GetFileName();
	QFileInfo	Info(FileName);

	QFile	File(FileName);
	if(File.open(QIODevice::Append)==false){
		return false;
	}

	char	Ch='L';
	if(::Save(&File,Ch)==false){
		return false;
	}

	if(::Save(&File,GetLayersBase()->GetMasterCode())==false){
		return false;
	}
	if(::Save(&File,GetLayersBase()->GetLot(0)->GetLotAutoCount())==false){
		return false;
	}

	return true;
}

bool	ResultDLLIntoFile::OutputInLibData(LogicDLL *L ,int32 LibID
									,QIODevice *f)
{
	AlgorithmBase	*ABase		=L->GetInstance();
	AlgorithmLibraryList	ALibList;
	ABase->GetLibraryContainer()->GetLibraryList(LibID,ALibList);
	LibNGTypeInAlgorithm NGTypeContainer;
	ABase->GetNGTypeContainer(LibID,NGTypeContainer);
	
	int32	NGTypeContainerCount=NGTypeContainer.GetCount();
	if(::Save(f,NGTypeContainerCount)==false){
		return false;
	}
	if(NGTypeContainer.IsEmpty()==false){
		int32	N=0;
		for(LibNGTypeItem *NGItem=NGTypeContainer.GetFirst();NGItem!=NULL;NGItem=NGItem->GetNext()){
			N++;
		}
		if(::Save(f,N)==false){
			return false;
		}

		for(LibNGTypeItem *NGItem=NGTypeContainer.GetFirst();NGItem!=NULL;NGItem=NGItem->GetNext()){

			QString	AlgoName	=L->GetDLLRoot()
								+QString(/**/":")
								+L->GetDLLName();

			if(::Save(f,AlgoName)==false){
				return false;
			}

			if(::Save(f,LibID)==false){
				return false;
			}
			QString	LibName=ALibList.GetLibName();
			if(::Save(f,LibName)==false){
				return false;
			}
			if(::Save(f,NGItem->TypeCode)==false){
				return false;
			}
			QString	TypeName=NGItem->NGName;
			if(::Save(f,TypeName)==false){
				return false;
			}
			if(::Save(f,NGItem->NGColor)==false){
				return false;
			}
			int32	NGShape=(int32)NGItem->NGShape;
			if(::Save(f,NGShape)==false){
				return false;
			}
			if(::Save(f,NGItem->Blink)==false){
				return false;
			}
			if(::Save(f,NGItem->Priority)==false){
				return false;
			}
			int32	NextJumpMilisec=NGItem->NextJumpMilisec;
			if(::Save(f,NextJumpMilisec)==false){
				return false;
			}
		}
	}
	else{
		QString	AlgoName	=L->GetDLLRoot()
							+QString(/**/":")
							+L->GetDLLName();

		if(::Save(f,AlgoName)==false){
			return false;
		}
		if(::Save(f,LibID)==false){
			return false;
		}
		QString	LibName=ALibList.GetLibName();
		if(::Save(f,LibName)==false){
			return false;
		}
	}
	return true;
}

ExeResult	ResultDLLIntoFile::ExecuteInitialAfterEdit		(int ExeID ,ResultInspection *Res)
{
	ExeResult	Ret=_ER_true;
	return Ret;
}

bool	ResultDLLIntoFile::OutputResultDirectly(int mode,ResultInspection &Res,GUIDirectMessage *packet)
{
	if(mode==-1 && WritePageDirectly==true){
		RThrrad.Push(&Res);
	}
	return true;
}


QString	ResultDLLIntoFile::GetFileName(void)
{
	int		MasterID	=GetLayersBase()->GetMasterCode();
	int		MachineID	=GetLayersBase()->GetMachineID();
	QString	LotID		=GetLayersBase()->GetLot(0)->GetLotID();
	QString	LotName		=GetLayersBase()->GetLot(0)->GetLotName();

	if(UseLotNameInFileName==true){
		return   SharedFolder
				+::GetSeparator()
				+QString::number(MachineID)
				+QString("-")
				+QString::number(MasterID)
				+::GetSeparator()
				+LotID
				+QString("--")
				+LotName
				+QString(".rdt");
	}
	else{
		return   SharedFolder
				+::GetSeparator()
				+QString::number(MachineID)
				+QString("-")
				+QString::number(MasterID)
				+::GetSeparator()
				+LotID
				+QString(".rdt");
	}
}

ResultDLLIntoThread::ResultDLLIntoThread(LayersBase *Base,ResultDLLIntoFile *p)
	:ServiceForLayers(Base),Parent(p)
{
	Terminated=false;
	WPoint=0;
	RPoint=0;
	LastTime=0;
	CountResBuff	=sizeof(ResBuff)/sizeof(ResBuff[0]);
}

void	ResultDLLIntoThread::Push(ResultInspection *Res)
{
	ResultInspectionForStockPointerContainer ShadowResStocks;
	ShadowResBuff[WPoint].RemoveAll();
	GetLayersBase()->WriteResultShadowPickupForWriteInSlave(ShadowResBuff[WPoint]
												,Res->GetStartTimeForInspection());

	ResBuff[WPoint]=Res;
	DWORD	D=::GetComputerMiliSec();
	PushedTime[WPoint]=D-LastTime;
	LastTime=D;

	ChangePoint.lock();
	WPoint++;
	if(WPoint>=CountResBuff){
		WPoint=0;
	}
	ChangePoint.unlock();
}

static	bool	StopToWrite=false;

void	ResultDLLIntoThread::run()
{
	while(GetLayersBase()->GetOnTerminating()==false && Terminated==false){
		if(WPoint!=RPoint && StopToWrite==false){
			Parent->OutputCommonRaw(*ResBuff[RPoint],ShadowResBuff[RPoint]);
			if(GetLayersBase()->GetEntryPoint()!=NULL && GetParamGlobal()->ReDrawByInspection==false){
				ExecuteInspectBase	*EBase=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
				if(EBase!=NULL){
					CmdReqInspectionRefresh	Cmd;
					Cmd.InspectionID=ResBuff[RPoint]->GetInspectionID();
					EBase->SpecifiedDirectly(&Cmd);
				}
			}
			ShadowResBuff[RPoint].RemoveAll();
			ChangePoint.lock();
			RPoint++;
			if(RPoint>=CountResBuff){
				RPoint=0;
			}
			ChangePoint.unlock();
		}
		msleep(20);
	}
}
