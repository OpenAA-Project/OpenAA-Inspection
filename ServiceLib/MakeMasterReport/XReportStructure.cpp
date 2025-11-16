#include "XReportStructure.h"
#include <QSqlDatabase>
#include <QTemporaryFile>
#include <locale.h>

#include "XGUI.h"
#include "XIntClass.h"
#include "XDataInExe.h"
#include <stdio.h>
#include "XDatabase.h"
#include "XGeneralDialog.h"
#include "hasplib.h"
#include "Regulus64Version.h"
#include "XParamGlobal.h"
#include "XDatabase.h"
#include "XAlgorithmBase.h"
#include "XGeneralFunc.h"
#include "ShowExecutingDialog.h"
#include "XDataAlgorithmList.h"

static	const	wchar_t	*ExcelUser	=L"MASATOSHI SASAI";
static	const	wchar_t *ExcelKey = L"windows-252a28070ccee00f6fbd6d65ady7m2ue";

ThreadReport::ThreadReport(int masterCode ,LayersBase *base, QObject *parent)
	:QThread(parent),ServiceForLayers(base)
{
	MasterCode=masterCode;
	setStackSize(64000000);

	MachineID	=0;
	sALibC	=NULL;
	sLibID	=-1;
	RetLib	=NULL;
	Flag	=true;
	sRet	=true;

	LoadedLogicDLL		=NULL;
	LoadedLogicDLLCount	=0;

	LoadedLogicDLLCount=GetLayersBase()->GetLogicDLLBase()->GetCount();
	LoadedLogicDLL=new LogicDLL*[LoadedLogicDLLCount];
	for(int i=0;i<LoadedLogicDLLCount;i++){
		LoadedLogicDLL[i]=NULL;
	}
}

ThreadReport::~ThreadReport(void)
{
	if(LoadedLogicDLL!=NULL){
		delete	[]LoadedLogicDLL;
		LoadedLogicDLL=NULL;
	}
	if(RetLib!=NULL){
		delete	RetLib;
		RetLib=NULL;
	}
}

void	ThreadReport::LoadMaster(void)
{
	LoadDataFromMaster(MasterCode);
}

void ThreadReport::run ()
{
	//msleep(3000);
	if(LoadAlgorithmData()==true){
		MakeAlgoData();
	}
}

bool		LoadedImage=true;

bool ThreadReport::LoadDataFromMaster(int masterCode)
{
	QString	S=QString(/**/"SELECT SETTINGDATA"
							/**/",PAGENUMB"
							/**/",MACHINEID"
							/**/",REGTIME"
							/**/",WORKERID"
							/**/",MASTERNAME"
							/**/",REMARK"
							/**/",LASTEDITTIME"
							/**/",CATEGORYID"
							/**/",TOPVIEW"
							/**/",DOTPERLINE"
							/**/",MAXLINES"
							/**/",LAYERNUMB"
							/**/",PHASENUMB"
							/**/",LIBFOLDERID"
							/**/",THRESHOLDLEVELID"
							/**/",THRESHOLDLEVELPARENTID"
							/**/" from MASTERDATA where MASTERCODE=")+QString::number(masterCode);
	QSqlQuery query(S ,GetLayersBase()->GetDatabase());
	if(query.next()==true){
		MachineID=query.value(query.record().indexOf("MACHINEID"	)).toInt();
		QByteArray	Sd=query.value(query.record().indexOf("SETTINGDATA")).toByteArray();
		QBuffer	SettingBuff;
		SettingBuff.setData(Sd);
	
		SettingBuff.open(QIODevice::ReadOnly);
		if(GetLayersBase()->GetParamGlobal()->LoadParam(&SettingBuff)==false){
			emit	SignalStep("Could not load MasterParam");
			return false;
		}

		ReportData.ReportedTime	=XDateTime::currentDateTime();
		ReportData.MasterCode	=masterCode;
		ReportData.RegTime		=query.value(query.record().indexOf("REGTIME"		)).toDateTime();
		ReportData.BoardName	=query.value(query.record().indexOf("MASTERNAME"	)).toString();
		ReportData.Remark		=query.value(query.record().indexOf("REMARK"		)).toString();
		ReportData.WorkerID		=query.value(query.record().indexOf("WORKERID"		)).toInt();
		ReportData.MachineID	=MachineID;
		ReportData.LastEditedTime=query.value(query.record().indexOf("LASTEDITTIME"	)).toDateTime();
		ReportData.CategoryID	=query.value(query.record().indexOf("CATEGORYID"	)).toInt();

		ReportData.LibFolderID				=query.value(query.record().indexOf("LIBFOLDERID"	)).toInt();
		ReportData.ThresholdLevelID			=query.value(query.record().indexOf("THRESHOLDLEVELID")).toInt();
		ReportData.ThresholdLevelParentID	=query.value(query.record().indexOf("THRESHOLDLEVELPARENTID")).toInt();
		GetLayersBase()->SetThresholdLevel(ReportData.ThresholdLevelID);
		GetLayersBase()->SetLibFolderID(ReportData.LibFolderID);

		QByteArray	STopview=query.value(query.record().indexOf("TOPVIEW")).toByteArray();
		QBuffer	TopviewBuff;
		TopviewBuff.setData(STopview);
		if(TopviewBuff.open(QIODevice::ReadOnly)==true){
			if(ReportData.TopView.load(&TopviewBuff,"PNG")==false){
				LoadedImage=false;
			}
		}
		ReportData.DotPerLine	=query.value(query.record().indexOf("DOTPERLINE"	)).toInt();
		ReportData.MaxLines		=query.value(query.record().indexOf("MAXLINES"		)).toInt();
		ReportData.PageNumb		=query.value(query.record().indexOf("PAGENUMB"		)).toInt();
		ReportData.LayerNumb	=query.value(query.record().indexOf("LAYERNUMB"		)).toInt();
		ReportData.PhaseNumb	=query.value(query.record().indexOf("PHASENUMB"		)).toInt();

		QString	Sm=QString(/**/"SELECT NAME from MACHINE where MACHINEID=")+QString::number(MachineID);
		QSqlQuery MQuery(Sm ,GetLayersBase()->GetDatabase());
		if(MQuery.next()==true){
			ReportData.MachineName	=MQuery.value(query.record().indexOf("NAME"	)).toString();
		}

		QString	Sc=QString(/**/"SELECT FOLDERNAME from MASTERCATEGORY where CATEGORYID=")+QString::number(ReportData.CategoryID);
		QSqlQuery CQuery(Sc ,GetLayersBase()->GetDatabase());
		if(CQuery.next()==true){
			ReportData.Category	=CQuery.value(query.record().indexOf("FOLDERNAME"	)).toString();
		}

		QString	Sw=QString(/**/"SELECT NAME from WORKER where WORKERID=")+QString::number(ReportData.WorkerID);
		QSqlQuery WQuery(Sw ,GetLayersBase()->GetDatabase());
		if(WQuery.next()==true){
			ReportData.WorkerName	=WQuery.value(query.record().indexOf("NAME"	)).toString();
		}

		int	RelationCode=query.value(query.record().indexOf("RELATIONCODE"		)).toInt();
		QString	Sr=QString(/**/"SELECT MASTERCODE from MASTERDATA where RELATIONCODE=")+QString::number(RelationCode);
		QSqlQuery RQuery(Sr ,GetLayersBase()->GetDatabase());
		while(RQuery.next()==true){
			int	mcode	=RQuery.value(query.record().indexOf("MASTERCODE"	)).toInt();
			if(mcode!=masterCode){
				ReportData.RelatedMasterID.Add(mcode);
			}
		}
		return true;
	}
	return false;
}

bool ThreadReport::LoadAlgorithmData(void)
{
	GetLayersBase()->InitialCreatePages(false);
	emit	SignalStep("InitialCreatePages");
	GetLayersBase()->ReallocAlgorithm();

	for(LogicDLL *p=GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext()){
		AlgorithmBase	*base=GetLayersBase()->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
		if(base==NULL){
			continue;
		}
		for(int phase=0;phase<GetLayersBase()->GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*pbase=base->GetPageDataPhase(phase);
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				DataInPage	*Pd=GetLayersBase()->GetPageDataPhase(phase)->GetPageData(page);
				AlgorithmInPageRoot	*ap=pbase->GetPageData(page);
				if(ap==NULL){
					continue;
				}

				QStringList	TrialPath;
				QStringList	ImagePathes=GetParamGlobal()->ImageFilePath.split(QChar(';'));
				QString		ImagePath;
				QString		LogicFileName;
				bool		FoundGUIContentFileName=false;
				for(int h=0;h<ImagePathes.count();h++){
					ImagePath=ImagePathes[h];
					LogicFileName=Pd->CreateLogicFileName(MasterCode,p,MachineID,ImagePath
														,0,0);
					TrialPath.append(LogicFileName);
					if(QFile::exists(LogicFileName)==true){
						FoundGUIContentFileName=true;
						break;
					}
				}
				if(FoundGUIContentFileName==false){
					ShowExecutingDialog	*Parent=dynamic_cast<ShowExecutingDialog *>(parent());
					ImagePathes=Parent->GlobalParam->ImageFilePath.split(QChar(';'));
					FoundGUIContentFileName=false;
					for(int h=0;h<ImagePathes.count();h++){
						ImagePath=ImagePathes[h];
						LogicFileName=Pd->CreateLogicFileName(MasterCode,p,MachineID,ImagePath
															,0,0);
						TrialPath.append(LogicFileName);
						if(QFile::exists(LogicFileName)==true){
							FoundGUIContentFileName=true;
							break;
						}
					}
				}
				if(FoundGUIContentFileName==true){
					QFile	LogicFile(LogicFileName);
					if(LogicFile.open(QIODevice::ReadOnly)==true){
						if(LogicFile.size()!=0){
							if(base->LoadOnlyBase(&LogicFile)==false){
								continue;
							}
							if(pbase->LoadOnly(&LogicFile)==false){
								return false;
							}
							if(ap->Load(&LogicFile)==false){
								continue;
							}
							for(int i=0;i<LoadedLogicDLLCount;i++){
								if(LoadedLogicDLL[i]==p){
									break;
								}
								if(LoadedLogicDLL[i]==NULL){
									LoadedLogicDLL[i]=p;
									break;
								}
							}
							emit	SignalStep(QString("Load successful : ")+LogicFileName);
						}
						//_CrtCheckMemory();
					}
				}
				else if(FoundGUIContentFileName==false){
					for(int i=0;i<TrialPath.count();i++){
						QString	Str=QString("Can not find file : ")+TrialPath[i];
						emit	SignalStep(Str);
					}
				}
			}
		}
	}
	return true;
}

static	bool FuncItemsWithoutLib(void *caller,AlgorithmItemRoot *item)
{
	if(item->GetLibID()<0){
		return true;
	}
	return false;
}

bool ThreadReport::MakeAlgoData(void)
{
	//for(LogicDLL *p=GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext()){
	for(int Li=0;Li<LoadedLogicDLLCount;Li++){
		LogicDLL *p=LoadedLogicDLL[Li];
		if(p==NULL){
			break;
		}

		AlgorithmBase	*base=GetLayersBase()->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
		if(base==NULL){
			continue;
		}
		ReportDataStructure::ReportAlgorithmList	*ReportedAlgo=new ReportDataStructure::ReportAlgorithmList();
		ReportData.ReportAlgorithmContainer.AppendList(ReportedAlgo);

		ReportedAlgo->DLLRoot	=p->GetDLLRoot();
		ReportedAlgo->DLLName	=p->GetDLLName();
		emit	SignalStep(QString("Algorithm ")
							+ReportedAlgo->DLLRoot
							+QString(":")
							+ReportedAlgo->DLLName);

		base->MakeReportedTopics(ReportedAlgo->AlgorithmTopics);

		AlgorithmLibraryContainer	*ALibC=base->GetLibraryContainer();
		for(int phase=0;phase<GetLayersBase()->GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*pbase=base->GetPageDataPhase(phase);
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				DataInPage	*Pd=GetLayersBase()->GetPageDataPhase(phase)->GetPageData(page);
				AlgorithmInPageRoot	*ap=pbase->GetPageData(page);
				if(ap==NULL){
					continue;
				}
				IntList LibIDList;
				ap->EnumLibID(LibIDList);
				ReportedAlgo->TotalItemCount+=ap->GetItemCount();
				for(IntClass *LibD=LibIDList.GetFirst();LibD!=NULL;LibD=LibD->GetNext()){
					int	LibID=LibD->GetValue();
					AlgorithmItemPointerListContainer ItemContainer;
					ap->MakeItemList(LibID,ItemContainer);

					ReportDataStructure::ReportAlgorithmList::ReportLibraryList	*RL=NULL;
					bool	FoundLibrary=false;

					sALibC=ALibC;
					sLibID=LibID;
					if(RetLib!=NULL){
						delete	RetLib;
					}
					RetLib=new AlgorithmLibraryLevelContainer(ALibC);
					ALibC->GetLibrary(LibID,*RetLib);
					AlgorithmLibrary	*L=RetLib->GetLibrary(ReportData.ThresholdLevelID);
					if(L!=NULL){
						//Flag=false;
						//emit	SignalReqLibrary();
						//while(Flag==false){
						//	msleep(100);
						//}
						//if(sRet==true){
						//	FoundLibrary=true;
						//}
						
						for(ReportDataStructure::ReportAlgorithmList::ReportLibraryList	*r=ReportedAlgo->ReportLibraryContainer.GetFirst();r!=NULL;r=r->GetNext()){
							if(r->LibID==LibID){
								RL=r;
								break;
							}
						}
						if(RL==NULL){
							RL=new ReportDataStructure::ReportAlgorithmList::ReportLibraryList();
							RL->LibID=LibID;
							if(FoundLibrary==true){
								RL->LibName=L->GetLibName();
							}
							ReportedAlgo->ReportLibraryContainer.AppendList(RL);
						}
						//if(FoundLibrary==true){
							ReportedTopicContainer RetReportContainer;
							L->MakeReportedTopics(RetReportContainer);
							RL->LibraryTopics+=RetReportContainer;
						//}
						RL->ItemCount+=ItemContainer.GetCount();
	
						for(AlgorithmItemPointerList *b=ItemContainer.GetFirst();b!=NULL;b=b->GetNext()){
							RL->TotalAreaDots+=b->GetItem()->GetArea().GetPatternByte();
							const	AlgorithmThreshold	*thre=b->GetItem()->GetThresholdBaseReadable();
							if(thre!=NULL){
								if(RL->ItemTypicalTopics.GetFirst()==NULL){
									((AlgorithmThreshold *)thre)->MakeReportedTopics(RL->ItemTypicalTopics);
								}
							}
						}
					}
				}

				AlgorithmItemPointerListContainer ItemsWithoutLib;
				ap->EnumItems(NULL,ItemsWithoutLib, FuncItemsWithoutLib);
				for(AlgorithmItemPointerList *a=ItemsWithoutLib.GetFirst();a!=NULL;a=a->GetNext()){
					const	AlgorithmThreshold	*thre=a->GetItem()->GetThresholdBaseReadable();
					if(thre!=NULL){
						bool Found=false;
						for(AlgorithmItemPointerList *b=ItemsWithoutLib.GetFirst();b!=NULL;b=b->GetNext()){
							if(a==b){
								break;
							}
							const	AlgorithmThreshold	*threB=b->GetItem()->GetThresholdBaseReadable();
							if(threB!=NULL){
								if(((AlgorithmThreshold *)thre)->IsEqual(*threB)==true){
									Found=true;
									break;
								}
							}
						}

						if(Found==false){
							ReportDataStructure::ReportAlgorithmList::ReportLibraryList	*RLNoLib=new ReportDataStructure::ReportAlgorithmList::ReportLibraryList();
							RLNoLib->LibID=-1;
							ReportedAlgo->ReportLibraryContainer.AppendList(RLNoLib);
							((AlgorithmThreshold *)thre)->MakeReportedTopics(RLNoLib->ItemTypicalTopics);
							RLNoLib->ItemCount=1;
							RLNoLib->TotalAreaDots=a->GetItem()->GetArea().GetPatternByte();

							for(AlgorithmItemPointerList *b=a->GetNext();b!=NULL;b=b->GetNext()){
								const	AlgorithmThreshold	*threB=b->GetItem()->GetThresholdBaseReadable();
								if(threB!=NULL){
									if(((AlgorithmThreshold *)thre)->IsEqual(*threB)==true){
										RLNoLib->ItemCount++;
										RLNoLib->TotalAreaDots+=b->GetItem()->GetArea().GetPatternByte();
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return true;
}


void	ThreadReport::GetLibraryOutOfThread(void)
{
	sRet=sALibC->GetLibrary(sLibID ,*RetLib);
	Flag=true;
}

bool	ThreadReport::SaveEXCEL(const QString &filename)
{
	return ReportData.SaveEXCEL(GetLayersBase(),filename);
}

void	ReportDataStructure::WriteCell(int Row, int Col ,const QString &Str)
{
	wchar_t	Buff[1000];
	memset(Buff,0,sizeof(Buff));
	Str.toWCharArray(Buff);

	XLSXSheet->setCellFormat(Row, Col,Lang);
	XLSXSheet->writeStr(Row, Col,Buff);
}

void	ReportDataStructure::WriteCellV(int Row, int Col ,const QVariant &Data)
{
	XLSXSheet->setCellFormat(Row, Col,Lang);

	wchar_t	Buff[1000];
	memset(Buff,0,sizeof(Buff));
	if(Data.type()==QVariant::Bool){
		if(Data.toBool()==true){
			XLSXSheet->writeStr(Row, Col,L"true");
		}
		else{
			XLSXSheet->writeStr(Row, Col,L"false");
		}
	}
	else if(Data.type()==QVariant::Char){
		QString	s(Data.toChar());
		s.toWCharArray(Buff);	
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::Date){
		QString	s(Data.toDate().toString());
		s.toWCharArray(Buff);	
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::DateTime){
		QString	s(Data.toDateTime().toString());
		s.toWCharArray(Buff);	
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::Double){
		QString	s=QString::number(Data.toDouble(),'f');
		s.toWCharArray(Buff);
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::Int){
		QString	s=QString::number(Data.toInt());
		s.toWCharArray(Buff);
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::String){
		QString	s=Data.toString();
		s.toWCharArray(Buff);
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::Time){
		QString	s(Data.toTime().toString());
		s.toWCharArray(Buff);	
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::UInt){
		QString	s=QString::number(Data.toUInt());
		s.toWCharArray(Buff);
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else{
		XLSXSheet->writeStr(Row, Col,L"Error");
	}
}

bool	ReportDataStructure::SaveEXCEL(LayersBase *base ,const QString &XLSXFileName)
{
	XLSXBook = xlCreateXMLBook();
	XLSXBook->setKey(ExcelUser, ExcelKey);
	XLSXSheet=XLSXBook->addSheet(L"Master");

	Lang	=XLSXBook->addFormat();
	Fnt	=XLSXBook->addFont();
	QString	FontName;
	switch (base->GetLanguageCode()) {
	case 0:	FontName = "ＭＳ Ｐゴシック";	break;
	case 1:	FontName = "Arial";				break;
	case 2:	FontName = "SimSun";			break;
	case 3:	FontName = "MingLiU";			break;
	case 4:	FontName = "Gulim";				break;
	}
	wchar_t	WBuff[100];
	memset(WBuff, 0, sizeof(WBuff));
	FontName.toWCharArray(WBuff);
	Fnt->setName(WBuff);

	Lang->setFont(Fnt);

	int	Row=0;
	WriteCell(Row, 0,"Reported");
	WriteCell(Row, 1,ReportedTime.toString());

	Row++;
	WriteCell(Row, 0,"MasterCode");
	WriteCell(Row, 1,QString::number(MasterCode));
	Row++;
	WriteCell(Row, 0,"BoardName");
	WriteCell(Row, 1,BoardName);
	Row++;
	WriteCell(Row, 0,"BoardRemark");
	WriteCell(Row, 1,Remark);
	Row++;
	Row++;
	WriteCell(Row, 0,"WorkerID");	
	WriteCell(Row, 1,QString::number(WorkerID));
	Row++;
	WriteCell(Row, 0,"WorkerName");
	WriteCell(Row, 1,WorkerName);
	Row++;
	WriteCell(Row, 0,"Created");
	WriteCell(Row, 1,RegTime.toString());
	Row++;
	WriteCell(Row, 0,"LastEdited");
	WriteCell(Row, 1,LastEditedTime.toString());
	Row++;
	Row++;
	WriteCell(Row, 0,"MachineID");
	WriteCell(Row, 1,QString::number(MachineID));
	QString MachineNetID;
	QString MachineName;
	QString MachineVersion;
	QString MachineRemark;

	base->SQLGetMachineInfo(MachineID
					  ,MachineNetID
					  ,MachineName
					  ,MachineVersion
					  ,MachineRemark);
	WriteCell(Row, 2,MachineName);
	WriteCell(Row, 3,MachineRemark);

	Row++;
	WriteCell(Row, 0,"CategoryID");
	WriteCell(Row, 1,QString::number(CategoryID));
	Row++;
	WriteCell(Row, 0,"MasterCategory");
	WriteCell(Row, 1,Category);
	Row++;
	WriteCell(Row, 0,"MasterCategory");
	WriteCell(Row, 1,QString::number(ThresholdLevelID));
	WriteCell(Row, 2,base->GetThresholdLevelName(ThresholdLevelID));

	Row++;
	Row++;
	XLSXSheet->setRow(Row,256);
	WriteCell(17, 0,"Image");
	QTemporaryFile	TmpImageFile;
	TmpImageFile.setAutoRemove(true);
	if(TmpImageFile.open()==true){
		QString	TmpImageFileName=TmpImageFile.fileName();
		TopView.save(&TmpImageFile,"PNG");
		TmpImageFile.flush();
		TmpImageFile.close();
		wchar_t	TmpImageFileBuff[1000];
		memset(TmpImageFileBuff,0,sizeof(TmpImageFileBuff));
		TmpImageFileName.toWCharArray(TmpImageFileBuff);

		int	ImageID=XLSXBook->addPicture(TmpImageFileBuff);
		XLSXSheet->setPicture2(Row, 1, ImageID, 256, 256);
	}
	Row++;
	Row++;

	WriteCell(Row, 0,"DotPerLine");
	WriteCell(Row, 1,QString::number(DotPerLine));
	Row++;
	WriteCell(Row, 0,"MaxLines");
	WriteCell(Row, 1,QString::number(MaxLines));
	Row++;
	WriteCell(Row, 0,"PageNumb");
	WriteCell(Row, 1,QString::number(PageNumb));
	Row++;
	WriteCell(Row, 0,"LayerNumb");
	WriteCell(Row, 1,QString::number(LayerNumb));
	Row++;
	WriteCell(Row, 0,"PhaseNumb");
	WriteCell(Row, 1,QString::number(PhaseNumb));

	Row++;
	if(RelatedMasterID.IsEmpty()==false){
		WriteCell(Row, 0,"Related");
		int	Col=0;
		for(IntClass *d=RelatedMasterID.GetFirst();d!=NULL;d=d->GetNext(),Col++){
			WriteCell(Row, 1+Col,QString::number(d->GetValue()));
		}
		Row++;
	}
	Row++;

	for(ReportAlgorithmList *A=ReportAlgorithmContainer.GetFirst();A!=NULL;A=A->GetNext()){
		WriteCell(Row, 0,"Algorithm");
		WriteCell(Row, 1,A->DLLRoot);
		WriteCell(Row, 2,A->DLLName);
		Row++;

		WriteCell(Row, 1,"TotalItem");
		WriteCell(Row, 2,QString::number(A->TotalItemCount));
		Row++;

		if(A->AlgorithmTopics.IsEmpty()==false){
			for(ReportedTopic *t=A->AlgorithmTopics.GetFirst();t!=NULL;t=t->GetNext()){
				WriteCell(Row, 1,t->Title);
				WriteCellV(Row, 2,t->Data);
				Row++;
			}
			Row++;
		}
		AlgorithmBase	*ABase=base->GetAlgorithmBase(A->DLLRoot,A->DLLName);
		AlgorithmLibraryContainer	*ALibC=(ABase!=NULL)?ABase->GetLibraryContainer():NULL;

		for(ReportAlgorithmList::ReportLibraryList *L=A->ReportLibraryContainer.GetFirst();L!=NULL;L=L->GetNext()){
			WriteCell(Row, 1,"Library");
			if(L->LibID>=0){
				WriteCell(Row, 2,QString::number(L->LibID));
				if(ALibC!=NULL){
					WriteCell(Row, 3,ALibC->GetLibraryName(L->LibID));
				}
				else{
					WriteCell(Row, 3,L->LibName);
				}
			}
			else{
				WriteCell(Row, 2,QString("No Library"));
			}
			Row++;

			WriteCell(Row, 2,"ItemCount");
			WriteCell(Row, 3,QString::number(L->ItemCount));
			Row++;

			WriteCell(Row, 2,"TotalArea");
			WriteCell(Row, 3,QString::number(L->TotalAreaDots));
			Row++;

			if(L->LibID>=0){
				if(L->LibraryTopics.IsEmpty()==false){
					WriteCell(Row  , 2,"LibData");
					int Col=0;
					for(ReportedTopic *t=L->LibraryTopics.GetFirst();t!=NULL;t=t->GetNext(),Col++){
						WriteCell(Row   , 3+Col,t->Title);
						WriteCellV(Row+1, 3+Col,t->Data);
					}
					Row+=2;
				}
			}
			if(L->ItemTypicalTopics.IsEmpty()==false){
				WriteCell(Row  , 2,"ItemData");
				int Col=0;
				for(ReportedTopic *t=L->ItemTypicalTopics.GetFirst();t!=NULL;t=t->GetNext(),Col++){
					WriteCell(Row   , 3+Col,t->Title);
					WriteCellV(Row+1, 3+Col,t->Data);
				}
				Row+=2;
			}
		}
	}
	wchar_t	FileNameStr[256];
	memset(FileNameStr,0,sizeof(FileNameStr));
	XLSXFileName.toWCharArray(FileNameStr);

	if(XLSXBook->save(FileNameStr)==false){
		delete	XLSXBook;
		return false;
	}
	XLSXBook->release();

	return true;
}
