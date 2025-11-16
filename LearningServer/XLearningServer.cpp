
#include <QSqlQuery>
#include <QString>
#include <QBuffer>
#include <QImage>
#include <QString>
#include <QMessageBox>
#include <QSqlError>
#include <QFile>
#include <QTextStream>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlDriver>
//#include <qsql_ibase.h>

#include "XLearningServer.h"
#include<QIODevice>
#include"XGeneralFunc.h"
#include"swap.h"
#include"XDataInLayer.h"
#include"XLearningRegist.h"
#include "XDatabaseLoader.h"
#include"XAlgorithmLibrary.h"
#include "XMainSchemeMemory.h"
#include "XResult.h"
#include "XDataAlgorithm.h"
#include "XDataAlgorithmList.h"
#include "XCriticalFunc.h"
#include "LearningServer.h"

ServerBase	*ServerBaseData;


ParamLearningServer::ParamLearningServer(void)
{
	LocalDatabase_FileName	=/**/"D:/Data/Regulus64.fdb";
	LocalDatabase_Port		=3051;
	LocalDatabase_HostName	=/**/"localhost";
	TransDatabaseIP			=/**/"";
	TransDatabasePort		=16050;

	SetParamFileName(&LocalDatabase_FileName,/**/"File"	,/**/"LocalDatabase_FileName"	,"Local database file name with path"		,0);
	SetParam(&LocalDatabase_Port			,/**/"File"	,/**/"LocalDatabase_Port"		,"Local database Port number"				,1000,65535);
	SetParam(&LocalDatabase_HostName		,/**/"File"	,/**/"LocalDatabase_HostName"	,"Local Database host name"					,0);
	SetParam(&TransDatabaseIP				,/**/"File" ,/**/"TransDatabaseIP"			,"Trans Database host name / IP"			,0);
	SetParam(&TransDatabasePort				,/**/"File" ,/**/"TransDatabasePort"		,"Trans Database host Port(Default 16050)"	,0);

}

ParamLearningServer::~ParamLearningServer(void)
{
}

ParamLearningServer	&ParamLearningServer::operator=(ParamBase &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.SaveParam(&Buff,-1);
	Buff.seek(0);
	LoadParam(&Buff);
	return *this;
}
//=======================================================================

ServerBase::ServerBase(LayersBase *Base)
	:ServiceForLayers(Base)
{
	GlobalParam	=NULL;
}
ServerBase::~ServerBase(void)
{
	Release();
}

void	ServerBase::Initial(void)
{
	if(GlobalParam==NULL){
		GlobalParam=new ParamLearningServer();
	}
}
void	ServerBase::Release(void)
{
	if(GlobalParam!=NULL){
		delete	GlobalParam;
		GlobalParam=NULL;
	}
}
bool	ServerBase::LoadParam(const QString &ParamFileName)
{
	return GetParamGlobal()->LoadFromFile(ParamFileName);
}
bool	ServerBase::LoadDefault(void)
{
	return GetParamGlobal()->LoadDefault(GetLayersBase()->GetUserPath());
}

ParamLearningServer	*ServerBase::GetParamGlobal(void)
{
	if(GlobalParam==NULL){
		Initial();
	}
	return GlobalParam;
}

QSqlDatabase	&ServerBase::GetDatabase(void)
{
	return GetLayersBase()->GetDatabase();
}

//=======================================================================

ThreadServer::ThreadServer(LearningServer *p,LayersBase *Base)
:ServiceForLayers(Base)
,Parent(p)
{
	Terminated		=false;
	Running			=false;
	Halted			=true;
}

ThreadServer::~ThreadServer(void)
{
}

void	ThreadServer::StopExecute(void)
{
	Halted=true;
	while(Running==true){
		GSleep(100);
	}
}
void	ThreadServer::StartExecute(void)
{
	Halted=false;
}

void	ThreadServer::run()
{
	while(Terminated==false){
		if(Halted==false){
			Running=true;
			LoadDatabase();
			AlgorithmLibraryListContainer	ListContainer;
			MakeLibList(ListContainer);
			for(AlgorithmLibraryList *Lib=ListContainer.GetFirst();Lib!=NULL;Lib=Lib->GetNext()){
				OptimizeLib(*Lib);
			}
			if(Parent->CheckLearningListInDB()==true){
				emit	SignalUpdateList();
			}
			emit	SignalShowList();
			Running=false;
		}
		else{
			msleep(100);
		}
	}
}

void	ThreadServer::LoadDatabase(void)
{
	LearningInDBAll		TmpLearningList;
	QString	S=QString(	/**/"SELECT "
						/**/"LEARNINGID FROM LEARNING");
	GetLayersBase()->GetDatabaseLoader()->G_LockDB();
	{
		QSqlQuery query(S ,ServerBaseData->GetDatabase());
		while(query.next ()==true){
			int	LearningID	=query.value(query.record().indexOf(/**/"LEARNINGID")	).toInt();
			LearningInDB	*d=new LearningInDB();
			d->LearningID=LearningID;
			TmpLearningList.AppendList(d);
			if(Halted==true || Terminated==true){
				return;
			}
		}
	}
	GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();

	for(LearningInDB *c=TmpLearningList.GetFirst();c!=NULL;c=c->GetNext()){
		GetLayersBase()->GetDatabaseLoader()->G_LoadLearningInDB(ServerBaseData->GetDatabase(),c->LearningID,*c);
	}
	AccessData.lockForWrite();
	if(TmpLearningList!=LearningList){
		for(LearningInDB *s=LearningList.GetFirst();s!=NULL;){
			if(Halted==true || Terminated==true){
				return;
			}
			LearningInDB	*SNext=s->GetNext();
			LearningInDB	*p=TmpLearningList.Search(s->LearningID);
			if(p!=NULL){
				if(*s!=*p){
					*s=*p;
				}
			}
			else{
				LearningList.RemoveList(s);
				delete	s;
			}
			s=SNext;
		}
		for(LearningInDB *s=TmpLearningList.GetFirst();s!=NULL;){
			LearningInDB	*SNext=s->GetNext();
			LearningInDB	*p=LearningList.Search(s->LearningID);
			if(p==NULL){
				TmpLearningList.RemoveList(s);
				LearningList.AppendList(s);
			}
			s=SNext;
		}
	}
	AccessData.unlock();
}

void	ThreadServer::MakeLibList(AlgorithmLibraryListContainer &ListContainer)
{
	AccessData.lockForRead();
	for(LearningInDB *s=LearningList.GetFirst();s!=NULL;s=s->GetNext()){
		for(LearningParamInDB *a=s->NPListPackSaveLoad<LearningParamInDB>::GetFirst();a!=NULL;a=a->GetNext()){
			ListContainer.Merge(GetLayersBase(),a->LibType ,a->LibID);
		}
	}
	AccessData.unlock();
}

AlgorithmThreshold	*ThreadServer::CalcProcess(LearningInDB *s,LearningParamInDB *L
								,AlgorithmThreshold *AController
								,bool &Ret)
{
	bool	Initialised=true;
	if(s->LayerForCalc==NULL){
		s->LayerForCalc=new ServerLayerBase(GetLayersBase(),GetLayersBase()->GetEntryPoint());
		Initialised=false;
	}
	ServerLayerBase	*LBase=(ServerLayerBase *)s->LayerForCalc;
	if(s->EPointForCalc==NULL){
		s->EPointForCalc=new ServerEntryPoint(LBase);
		s->LayerForCalc->SetEntryPoint(s->EPointForCalc);
		Initialised=false;
	}
	int	LayerNumb=s->Layer;
	if(Initialised==false){
		LBase->InitialForServer(s->XSize ,s->YSize ,s->Layer);

		LBase->InitialAllocExecuterDim();
		LBase->InitialResult(false);


		ImageBuffer *MasterBuffDim[100];
		ImageBuffer *TargetBuffDim[100];
		QBuffer	MasterBuff(&s->MasterImage);
		QBuffer	TargetBuff(&s->TargetImage);
		MasterBuff.open(QIODevice::ReadWrite);
		TargetBuff.open(QIODevice::ReadWrite);

		for(int Layer=0;Layer<LayerNumb;Layer++){
			DataInLayer	*Ly=LBase->GetPageData(0)->GetLayerData(Layer);
			MasterBuffDim[Layer]=&Ly->GetMasterBuff();
			MasterBuffDim[Layer]->Load(&MasterBuff);
			TargetBuffDim[Layer]=&Ly->GetTargetBuff();
			TargetBuffDim[Layer]->Load(&TargetBuff);
		}
	
		QBuffer	PBuff(&s->PointData);
		PBuff.open(QIODevice::ReadOnly);

		FlexArea	PointArea;
		PointArea.Load(&PBuff);

		LBase->SampleType	=s->SampleType;
		LBase->PointArea	=PointArea;
		LBase->LoadItemParamData(L->LibType , L->LibID ,L->ParamData);
	}
	
	if(Initialised==false){
		ExecuteInitialAfterEditInfo EInfo;
		LBase->ExecuteInitialAfterEdit	(EInfo,false);
	}
	AlgorithmBase	*ABase=LBase->GetAlgorithmBase(L->LibType);
	if(ABase==NULL){
		return NULL;
	}
	AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(0);
	if(Ah==NULL){
		return NULL;
	}
	AlgorithmInPageRoot		*Ap=Ah->GetPageData(0);
	if(Ap==NULL){
		return NULL;
	}
	AlgorithmItemPointerListContainer ItemPointers;
	Ap->EnumAllItems(ItemPointers);
	for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmItemRoot	*AItem=a->GetItem();
		if(AItem->GetArea().GetPatternByte()==0){
			AItem->GetArea().SetRectangle(0,0,AItem->GetDotPerLine(),AItem->GetMaxLines());
			ResultInItemRoot *Res=AItem->GetCurrentResult();
			ExecuteInitialAfterEditInfo	EInfo;
			AItem->ExecuteInitialAfterEdit	(0,0,Res,EInfo);
		}
		AlgorithmThreshold	*AThr=AItem->GetThresholdBaseWritable(LBase);
		if(AController!=NULL){
			AThr->CopyFrom(*AController);
		}
		else{
			AController=AItem->CreateThresholdInstance();
			AController->CopyFrom(*AThr);
		}
	}

	ListPhasePageLayerPack	CapturedList;
	LBase->MakeCapturedAllList(CapturedList);
	LBase->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
	LBase->ExecuteStartByInspection	(false);
	LBase->ExecuteCaptured			(CapturedList,false);
	LBase->ExecutePreAlignment		(false);
	LBase->ExecuteAlignment			(false);
	LBase->ExecutePreProcessing		(false);
	LBase->ExecuteProcessing		(false);
	LBase->ExecuteProcessingRevived	(false);
	LBase->ExecutePostProcessing	(false);

	ResultInspection	*CurrentResult=LBase->GetCurrentResultForCalc();
	bool3	OK=true3;
	bool	MaxError=false;
	bool	TimeOver=false;
	if(CurrentResult!=NULL){
		CurrentResult->GatherResult(OK ,MaxError , TimeOver,true,false);
	}
	if(OK==true3 && MaxError==false && TimeOver==false){
		Ret=true;
		s->Result=1;	//OK
	}
	else{
		L->ResultList.RemoveAll();
		for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmItemRoot	*AItem=a->GetItem();
			ResultInItemRoot	*R=AItem->GetCurrentResult();
			ResultPosList	*Pos=R->GetPosListFirst();
			ABase->GetDrawResultDetail(AItem,Pos,L->ResultList);
		}
		Ret=false;
		s->Result=2;	//NG
	}
	return AController;
}

double	ThreadServer::CalcEnStrength(AlgorithmLibraryList &Lib,AlgorithmThreshold	*AControler)
{
	AccessData.lockForRead();
	double	EnStrength=0;

	for(LearningInDB *s=LearningList.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->LayerForCalc==NULL){
			for(LearningParamInDB *a=s->NPListPackSaveLoad<LearningParamInDB>::GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibType==Lib.GetLibType() && a->LibID==Lib.GetLibID()){
					bool	bRet;
					if(AControler!=NULL){
						CalcProcess(s,a,AControler,bRet);
					}
					else{
						AControler=CalcProcess(s,a,AControler,bRet);
						if(AControler!=NULL){
							LearnigAlgorithmThresholdPointer	*A=new LearnigAlgorithmThresholdPointer(AControler,Lib.GetLibType() ,Lib.GetLibID());
							A->GetThreshold()->SetLearningParam(A->ParamThreshold);
							AThrContainer.AppendList(A);
						}
					}
				}
			}
		}
	}


	LearningInDB *s;
	#pragma omp parallel	num_threads(4)
	#pragma omp single private(s)
	for(s=LearningList.GetFirst();s!=NULL;s=s->GetNext()){
		#pragma omp task
		{
			for(LearningParamInDB *a=s->NPListPackSaveLoad<LearningParamInDB>::GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibType==Lib.GetLibType() && a->LibID==Lib.GetLibID()){
					bool	bRet;
					if(AControler!=NULL){
						CalcProcess(s,a,AControler,bRet);
					}
					else{
						AControler=CalcProcess(s,a,AControler,bRet);
						if(AControler!=NULL){
							#pragma omp critical
							{
								LearnigAlgorithmThresholdPointer	*A=new LearnigAlgorithmThresholdPointer(AControler,Lib.GetLibType() ,Lib.GetLibID());
								A->GetThreshold()->SetLearningParam(A->ParamThreshold);
								AThrContainer.AppendList(A);
							}
						}
					}
					if(AControler!=NULL){
						if(s->SampleType==2 && bRet==true){
							#pragma omp critical
							{
								EnStrength+=100-s->Priority;
							}
						}
						else
						if(s->SampleType==1 && bRet==false){
							#pragma omp critical
							{
								EnStrength+=-(100-s->Priority);
							}
						}
					}
				}
			}
		}
	}
	AccessData.unlock();
	return EnStrength;
}
void	ThreadServer::OptimizeLib(AlgorithmLibraryList &Lib)
{
	AccessData.lockForRead();
	LearnigAlgorithmThresholdPointer	*AControler=(LearnigAlgorithmThresholdPointer *)AThrContainer.SearchPointer(Lib.GetLibType() ,Lib.GetLibID());
	AccessData.unlock();

	//double	EnStrength=CalcEnStrength(Lib,AControler);

	LibTypeIDResult	*R=GetLibTypeIDResultData(Lib.GetLibType(), Lib.GetLibID());
	if(R!=NULL){
		double	MinEnStrength=fabs(R->EnStrength);
		bool	Changed=false;
		for(int V=1;V<10;V++){
			Changed=false;
			for(LearningInDBThresholdParamBase *a=AControler->ParamThreshold.GetFirst();a!=NULL;a=a->GetNext()){
				AlgorithmThreshold	*AThr=AControler->GetThreshold();
				a->BackupValue(AThr);
				a->StepStrict(AThr,1.0*V);
				bool3	ChangedStrict=none3;
				double	EnStrength1=CalcEnStrength(Lib,AThr);
				if(MinEnStrength>fabs(EnStrength1)){
					MinEnStrength=fabs(EnStrength1);
					ChangedStrict=true3;
				}
				a->RestoreValue(AThr);
				a->StepLoose(AThr,1.0*V);
				double	EnStrength2=CalcEnStrength(Lib,AThr);
				if(MinEnStrength>fabs(EnStrength2)){
					MinEnStrength=fabs(EnStrength2);
					ChangedStrict=false3;
				}
				a->RestoreValue(AThr);
				if(ChangedStrict==true3){
					a->StepStrict(AThr,1.0*V);
					Changed=true;
				}
				else if(ChangedStrict==false3){
					a->StepLoose(AThr,1.0*V);
					Changed=true;
				}
			}
			if(Changed==true || MinEnStrength==0.0){
				break;
			}
		}
		if(Changed==false && fabs(MinEnStrength)>0){
			for(int V=4;V>=0;V--){
				Changed=false;
				for(LearningInDBThresholdParamBase *a=AControler->ParamThreshold.GetFirst();a!=NULL;a=a->GetNext()){
					AlgorithmThreshold	*AThr=AControler->GetThreshold();
					a->BackupValue(AThr);
					a->StepStrict(AThr,0.2*V);
					bool3	ChangedStrict=none3;
					double	EnStrength1=CalcEnStrength(Lib,AThr);
					if(MinEnStrength>fabs(EnStrength1)){
						MinEnStrength=fabs(EnStrength1);
						ChangedStrict=true3;
					}
					a->RestoreValue(AThr);
					a->StepLoose(AThr,0.2*V);
					double	EnStrength2=CalcEnStrength(Lib,AThr);
					if(MinEnStrength>fabs(EnStrength2)){
						MinEnStrength=fabs(EnStrength2);
						ChangedStrict=false3;
					}
					a->RestoreValue(AThr);
					if(ChangedStrict==true3){
						a->StepStrict(AThr,0.2*V);
						Changed=true;
					}
					else if(ChangedStrict==false3){
						a->StepLoose(AThr,0.2*V);
						Changed=true;
					}
				}
				if(Changed==true || MinEnStrength==0.0){
					break;
				}
			}
		}

		R->EnStrength=CalcEnStrength(Lib,AControler->GetThreshold());
	}
	else{
		R=new LibTypeIDResult();
		R->LibType		=Lib.GetLibType();
		R->LibID		=Lib.GetLibID();
		R->EnStrength	=CalcEnStrength(Lib,NULL);	//AControler->GetThreshold());
		R->ParamNumber	=0;
		LibTypeIDResultData.AppendList(R);
	}
}				

LibTypeIDResult	*ThreadServer::GetLibTypeIDResultData(int LibType, int LibID)
{
	for(LibTypeIDResult *a=LibTypeIDResultData.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LibType==LibType && a->LibID==LibID){
			return a;
		}
	}
	return NULL;
}
