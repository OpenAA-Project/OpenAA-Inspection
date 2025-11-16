#include "NGImageListForm.h"
#include "SelectRelationalMasterDataDialog.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"
#include "XIntegrationBase.h"
#include "XMeasureLineMove.h"
#include "XMeasureCommon.h"
#include <swap.h>
#include "NGImageAlgorithm.h"


const	int	ExcelMasterImageXLen=16;
const	int	ExcelMasterImageYLen=120;

const	int	ExcelImageXLen=16;
const	int	ExcelImageYLen=80;
const	int	MaxRowCountInPage=47;

bool	NGImageListForm::WriteExcel(const QString &ExcelFileName)
{
	InitialExcel();


	RemationMasterCodeList.RemoveAll();
	for(NGListWithImages *R=ResultList.GetFirst();R!=NULL;R=R->GetNext()){
		RemationMasterCodeList.Merge(R->RelationCode);
	}

	MakeExcelSheet1();
	MakeExcelSheet2();
	MakeExcelSheet3();
	MakeExcelSheet4();
	MakeExcelSheet5();
	
	wchar_t	FileNameStr[256];
	memset(FileNameStr,0,sizeof(FileNameStr));
	ExcelFileName.toWCharArray(FileNameStr);

	if(XLSXBook->save(FileNameStr)==false){
		delete	XLSXBook;
		return;
	}

	ReleaseExcel();
	return true;
}

//bool	NGImageListForm::MakeExcelSheet1(void)
//{
//	LayersBasePQSystem	*LBase=(LayersBasePQSystem *)GetLayersBase();
//	IntegrationBase	*MBase=GetLayersBase()->GetIntegrationBasePointer();
//
//	int	SheetNo=0;
//	int	Row=0;
//	WriteCell(Row, 0,"詳細データ",SheetNo);
//	Row++;
//	WriteCell(Row, 0,"作成日時",SheetNo);
//	WriteCell(Row, 1,QDateTime::currentDateTime().toString(Qt::SystemLocaleLongDate),SheetNo);
//	Row++;
//	for(IntClass *d=RemationMasterCodeList.GetFirst();d!=NULL;d=d->GetNext()){
//		int	MasterRelationCode=d->GetValue();
//		QString	RetRelationNumber;
//		QString	RetRelationName;
//		QString	RetRemark;
//		int		RetRelationType;
//		QByteArray	CommonData;
//		int32	ThresholdLevelID;
//		MBase->SetMasterRelationCode(MasterRelationCode);
//		if(MBase->GetInformation(RetRelationNumber
//								,RetRelationName
//								,RetRemark
//								,RetRelationType
//								,CommonData
//								,ThresholdLevelID)==false){
//			return false;
//		}
//
//
//		WriteCell(Row, 0,"マスター",SheetNo);
//		WriteCell(Row, 1,MasterRelationCode,SheetNo);
//		Row++;
//		WriteCell(Row, 0,LBase->GetParamPQSystem()->TitleMasterNumber,SheetNo);
//		WriteCell(Row, 1,RetRelationNumber,SheetNo);
//		WriteCell(Row, 2,RetRelationName,SheetNo);
//		Row++;
//		WriteCell(Row, 0,LBase->GetParamPQSystem()->TitleRemark,SheetNo);
//		WriteCell(Row, 1,RetRemark,SheetNo);
//		Row++;
//
//		XLSXSheet[SheetNo]->setRow(Row,ExcelMasterImageYLen);//256);
//		XLSXSheet[SheetNo]->setCol(0, MBase->MasterDatas.GetCount()-1,ExcelMasterImageXLen);
//
//		int	Col=0;
//		for(EachMaster *m=MBase->MasterDatas.GetFirst();m!=NULL;m=m->GetNext(),Col++){
//			m->CurrentLot=NULL;
//			int	SlaveNo=m->GetIntegrationSlaveNo();
//			QTemporaryFile	TmpImageFile;
//			TmpImageFile.setAutoRemove(true);
//			if(TmpImageFile.open()==true){
//				QString	TmpImageFileName=TmpImageFile.fileName();
//				QImage	TopView=LoadDataFromMaster(m->MasterCode);
//				TopView.save(&TmpImageFile,"PNG");
//				TmpImageFile.flush();
//				TmpImageFile.close();
//				wchar_t	TmpImageFileBuff[1000];
//				memset(TmpImageFileBuff,0,sizeof(TmpImageFileBuff));
//				TmpImageFileName.toWCharArray(TmpImageFileBuff);
//
//				int	ImageID=XLSXBook->addPicture(TmpImageFileBuff);
//				XLSXSheet[SheetNo]->setPicture2(Row, Col, ImageID, 256, 256,0,0,libxl::POSITION_ONLY_MOVE);
//			}
//		}
//
//		Row++;
//
//		WriteCell(Row, 0,"検査ID"	,SheetNo);
//		WriteCell(Row, 1,"日時"		,SheetNo);
//		WriteCell(Row, 2,LBase->GetParamPQSystem()->TitleLotID		,SheetNo);
//		WriteCell(Row, 3,LBase->GetParamPQSystem()->TitleLotNumber	,SheetNo);
//		WriteCell(Row, 4,LBase->GetParamPQSystem()->TitleSubCode	,SheetNo);
//		WriteCell(Row, 5,"検査"		,SheetNo);
//		
//		Row++;
//		for(NGListWithImages *R=ResultList.GetFirst();R!=NULL;R=R->GetNext()){
//			if(R->RelationCode==MasterRelationCode){
//				WriteCell(Row, 0,R->InspectionID	,SheetNo);
//				WriteCell(Row, 1,R->InspectionTime.toString("yy/MM/dd-hh:mm:ss"),SheetNo);
//				InspectionListByMaster	*LByMaster=R->LotPointer->CurrentInspection.GetFirst();
//				if(LByMaster!=NULL){
//					WriteCell(Row, 2,LByMaster->LotListData.LotName	,SheetNo);
//					WriteCell(Row, 3,LByMaster->LotListData.LotID	,SheetNo);
//					WriteCell(Row, 4,LByMaster->LotListData.Remark	,SheetNo);
//					for(NGListByMaster *M=R->NGImageBYMaster.GetFirst();M!=NULL;M=M->GetNext()){
//						EachMaster	*m=MBase->FindMaster(M->MachineID);
//						if(m!=NULL){
//							WriteCell(Row, 5,m->GetMachineName()	,SheetNo);
//						}
//						for(InspectionListByMaster *w=R->LotPointer->CurrentInspection.GetFirst();w!=NULL;w=w->GetNext()){
//							if(w->MachineID==m->GetMachineCode()){
//								m->CurrentLot=&w->LotListData;
//								m->LoadLot(&w->LotListData);
//							}
//						}
//
//						for(PointerList<IntegNGImage> *t=M->NGImages.GetFirst();t!=NULL;t=t->GetNext()){
//							SetRowHeight(Row,25,0);
//							SetNGImage(m,R->InspectionID,t->Get(),Row,6	,SheetNo);
//							Row++;
//						}
//					}
//				}
//			}
//		}
//	}
//	return true;
//}

class Sheet1ByImage: public NPList<Sheet1ByImage>
{
public:
	int			MachineID;
	int			LibType;
	int			LibID;
	int			UniqueID;
	int32		MasterX,MasterY;
	QString		LibName;
	QStringList	Causes;
	QImage		NGImage;

	Sheet1ByImage(void){}

	virtual	int	Compare(Sheet1ByImage &src)	{	return MachineID-src.MachineID;	}
};

class Sheet1ByID: public NPList<Sheet1ByID>
{
public:
	int			InspectionID;
	XDateTime	Time;
	NPListPack<Sheet1ByImage>	Images;

	Sheet1ByID(void){}

	virtual	int	Compare(Sheet1ByID &src)	{	return InspectionID-src.InspectionID;	}
};

class Sheet1Lot : public NPList<Sheet1Lot>
{
public:
	int	LotAutoCount;
	QString	LotID;
	QString	LotName;
	NPListPack<Sheet1ByID>	NGSheet;
	int		TotalCount[100];

	Sheet1Lot(void){}
	Sheet1ByID	*SearchByID(int id);

	virtual	int	Compare(Sheet1Lot &src)	{	return LotAutoCount-src.LotAutoCount;	}
};

class Sheet1Pack : public NPListPack<Sheet1Lot>
{
public:
	Sheet1Pack(void){}

	Sheet1Lot	*SearchByLotAutoCount(int id);
};


Sheet1ByID	*Sheet1Lot::SearchByID(int id)
{
	for(Sheet1ByID *s=NGSheet.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->InspectionID==id){
			return s;
		}
	}
	return NULL;
}

Sheet1Lot	*Sheet1Pack::SearchByLotAutoCount(int id)
{
	for(Sheet1Lot *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->LotAutoCount==id){
			return s;
		}
	}
	return NULL;
}

//----------------------------------------------------------------------------------

const	int		NGImageXCount=5;

bool	NGImageListForm::MakeExcelSheet1(void)
{
	LayersBasePQSystem	*LBase=(LayersBasePQSystem *)GetLayersBase();
	IntegrationBase	*MBase=GetLayersBase()->GetIntegrationBasePointer();

	int	PageRow=0;
	int	SheetNo=0;
	int	Row=0;
	WriteCell(Row, 0,"詳細データ",SheetNo);
	Row++;
	WriteCell(Row, 0,"検索日時",SheetNo);
	WriteCell(Row, 1,StartTime.toString()
					+QString("-")
					+EndTime.toString()
					,SheetNo);
	Row++;
	PageRow+=2;

	for(IntClass *d=RemationMasterCodeList.GetFirst();d!=NULL;d=d->GetNext()){
		int	MasterRelationCode=d->GetValue();
		QString	RetRelationNumber;
		QString	RetRelationName;
		QString	RetRemark;
		int		RetRelationType;
		QByteArray	CommonData;
		int32	ThresholdLevelID;
		MBase->SetMasterRelationCode(MasterRelationCode);
		if(MBase->GetInformation(RetRelationNumber
								,RetRelationName
								,RetRemark
								,RetRelationType
								,CommonData
								,ThresholdLevelID)==false){
			return false;
		}


		WriteCell(Row, 0,"マスター",SheetNo);
		WriteCell(Row, 1,MasterRelationCode,SheetNo);
		Row++;
		WriteCell(Row, 0,LBase->GetParamPQSystem()->TitleMasterNumber,SheetNo);
		WriteCell(Row, 1,RetRelationNumber,SheetNo);
		WriteCell(Row, 2,RetRelationName,SheetNo);
		Row++;
		WriteCell(Row, 0,LBase->GetParamPQSystem()->TitleRemark,SheetNo);
		WriteCell(Row, 1,RetRemark,SheetNo);
		Row++;
		PageRow+=3;

		XLSXSheet[SheetNo]->setRow(Row,ExcelMasterImageYLen);//256);
		XLSXSheet[SheetNo]->setCol(0, MBase->MasterDatas.GetCount()-1,ExcelMasterImageXLen);

		int	Col=0;
		for(EachMaster *m=MBase->MasterDatas.GetFirst();m!=NULL;m=m->GetNext(),Col++){
			m->ClearCurrentLot();
			int	SlaveNo=m->GetIntegrationSlaveNo();
			QTemporaryFile	TmpImageFile;
			TmpImageFile.setAutoRemove(true);
			if(TmpImageFile.open()==true){
				QString	TmpImageFileName=TmpImageFile.fileName();
				QImage	TopView=LoadDataFromMaster(m->GetMasterCode());
				TopView.save(&TmpImageFile,"PNG");
				TmpImageFile.flush();
				TmpImageFile.close();
				wchar_t	TmpImageFileBuff[1000];
				memset(TmpImageFileBuff,0,sizeof(TmpImageFileBuff));
				TmpImageFileName.toWCharArray(TmpImageFileBuff);

				int	ImageID=XLSXBook->addPicture(TmpImageFileBuff);
				XLSXSheet[SheetNo]->setPicture2(Row, Col, ImageID, 256, 256,0,0,libxl::POSITION_ONLY_MOVE);
			}
		}
		PageRow+=(ExcelMasterImageYLen+15)/16;

		Row++;
		Col=0;
		
		Sheet1Pack	Sheet1LotData;

		Col=1;
		for(NGListWithImages *R=ResultList.GetFirst();R!=NULL;R=R->GetNext()){
			if(R->RelationCode==MasterRelationCode){
				InspectionListByMaster	*LByMaster=R->LotPointer->CurrentInspection.GetFirst();
				if(LByMaster!=NULL){
					Sheet1Lot	*sLot=Sheet1LotData.SearchByLotAutoCount(LByMaster->LotListData.GlobalID);
					if(sLot==NULL){
						sLot=new Sheet1Lot();
						sLot->LotAutoCount	=LByMaster->LotListData.GlobalID;
						sLot->LotID			=LByMaster->LotListData.LotID;
						sLot->LotName		=LByMaster->LotListData.LotName;
						Sheet1LotData.AppendList(sLot);
					}
					for(NGListByMaster *M=R->NGImageBYMaster.GetFirst();M!=NULL;M=M->GetNext()){
						EachMaster	*m=MBase->FindMaster(M->MachineID);
						for(InspectionListByMaster *w=R->LotPointer->CurrentInspection.GetFirst();w!=NULL;w=w->GetNext()){
							if(w->MachineID==m->GetMachineCode()){
								m->SetCurrentLot(&w->LotListData);
								m->LoadLot(&w->LotListData);
							}
						}

						for(PointerList<IntegNGImage> *t=M->NGImages.GetFirst();t!=NULL;t=t->GetNext()){
							Sheet1ByID	*sSheetID=sLot->SearchByID(R->InspectionID);
							if(sSheetID==NULL){
								sSheetID=new Sheet1ByID();
								sSheetID->InspectionID	=R->InspectionID;
								sSheetID->Time			=R->InspectionTime;
								sLot->NGSheet.AppendList(sSheetID);
							}
							
							Sheet1ByImage	*sImg	=SetNGImage3(m ,R->InspectionID ,t->Get());
							if(sImg!=NULL){
								sSheetID->Images.AppendList(sImg);
							}
						}
					}
				}
			}
		}

		Row++;
		int		CountInPage=0;
		for(Sheet1Lot *sLot=Sheet1LotData.GetFirst();sLot!=NULL;sLot=sLot->GetNext()){
			WriteCell(Row+0, 0,LBase->GetParamPQSystem()->TitleLotID		,SheetNo);
			WriteCell(Row+1, 0,LBase->GetParamPQSystem()->TitleLotNumber	,SheetNo);

			WriteCell(Row+0, 1,sLot->LotName	,SheetNo);
			WriteCell(Row+1, 1,sLot->LotID	,SheetNo);
			Row+=2;
			PageRow+=2;

			for(Sheet1ByID *sSheetID=sLot->NGSheet.GetFirst();sSheetID!=NULL;sSheetID=sSheetID->GetNext()){
				Col=0;
				for(Sheet1ByImage *sImg=sSheetID->Images.GetFirst();sImg!=NULL;sImg=sImg->GetNext()){
					if(Col==0 || Col>=NGImageXCount){
						if(Col>=NGImageXCount){
							Row+=7;
						}
						Col=0;
						WriteCell(Row+0, Col,"日時/ID"	,SheetNo);
						WriteCell(Row+1, Col,"カメラ"			,SheetNo);
						WriteCell(Row+2, Col,"検査ライブラリ"	,SheetNo);
						WriteCell(Row+3, Col,"判定理由"			,SheetNo);
						WriteCell(Row+4, Col,"座標"				,SheetNo);
						WriteCell(Row+5, Col,"NG画像"			,SheetNo);
						
						WriteCell(Row+0, Col+1,sSheetID->Time.toString("yy/MM/dd-hh:mm:ss"),SheetNo);
						WriteCell(Row+0, Col+2,sSheetID->InspectionID	,SheetNo);
						Col=1;
					}
					
					
					EachMaster *m=MBase->FindMaster(sImg->MachineID);
					if(m!=NULL){
						WriteCell(Row+1, Col,m->GetMachineName()	,SheetNo);
					}
					WriteCell(Row+2, Col,sImg->LibName,SheetNo);
					QStringList	List=sImg->Causes;
					QString		Str=/**/"";
					if(sImg->Causes.count()>=3){
						Str=sImg->Causes[2];
					}
					else
					if(sImg->Causes.count()>=2){
						Str=sImg->Causes[0];
					}
					else{
						for(int e=0;e<List.count();e++){
							Str+=List[e];
							if(e!=(List.count()-1)){
								Str+=QString(/**/",");
							}
						}
					}
					WriteCell(Row+3, Col,Str,SheetNo);
					WriteCell(Row+4, Col,QString::number(sImg->MasterX)
										+QString(",")
										+QString::number(sImg->MasterY),SheetNo);

					QTemporaryFile	TmpImageFile;
					TmpImageFile.setAutoRemove(true);
					if(TmpImageFile.open()==true){
						XLSXSheet[SheetNo]->setRow(Row+5 ,ExcelImageYLen);	//256);
						XLSXSheet[SheetNo]->setCol(Col ,Col,ExcelImageXLen);

						QString	TmpImageFileName=TmpImageFile.fileName();
						sImg->NGImage.save(&TmpImageFile,"PNG");
						TmpImageFile.flush();
						TmpImageFile.close();
						wchar_t	TmpImageFileBuff[10000];
						memset(TmpImageFileBuff,0,sizeof(TmpImageFileBuff));
						TmpImageFileName.toWCharArray(TmpImageFileBuff);

						int	ImageID=XLSXBook->addPicture(TmpImageFileBuff);
						XLSXSheet[SheetNo]->setPicture2(Row+5, Col, ImageID, sImg->NGImage.width(), sImg->NGImage.height(),0,0,libxl::POSITION_ONLY_MOVE);
					}
					Col++;
					CountInPage++;

					if((PageRow+6+(ExcelImageYLen+15)/16)>=MaxRowCountInPage){
						XLSXSheet[SheetNo]->setHorPageBreak(Row);
						PageRow=0;
						CountInPage=0;
					}
				}
				Row+=7;
				if(CountInPage!=0){
					PageRow+=6+(ExcelImageYLen+15)/16;
					if((PageRow+6+(ExcelImageYLen+15)/16)>=MaxRowCountInPage){
						XLSXSheet[SheetNo]->setHorPageBreak(Row);
						PageRow=0;
						CountInPage=0;
					}
				}
			}
			if(CountInPage!=0){
				XLSXSheet[SheetNo]->setHorPageBreak(Row);
				PageRow=0;
				CountInPage=0;
			}
		}
	}
	return true;
}
bool	NGImageListForm::MakeExcelSheet2(void)
{
	LayersBasePQSystem	*LBase=(LayersBasePQSystem *)GetLayersBase();
	IntegrationBase	*MBase=GetLayersBase()->GetIntegrationBasePointer();

	int	SheetNo=1;
	AddSheet("集計");
	int	Row=0;
	WriteCell(Row, 0,"検査集計",SheetNo);
	Row++;
	WriteCell(Row, 0,"検索日時",SheetNo);
	WriteCell(Row, 1,StartTime.toString()
					+QString("-")
					+EndTime.toString()
					,SheetNo);
	Row++;

	for(IntClass *d=RemationMasterCodeList.GetFirst();d!=NULL;d=d->GetNext()){
		int	MasterRelationCode=d->GetValue();
		QString	RetRelationNumber;
		QString	RetRelationName;
		QString	RetRemark;
		int		RetRelationType;
		QByteArray	CommonData;
		int32	ThresholdLevelID;
		MBase->SetMasterRelationCode(MasterRelationCode);
		if(MBase->GetInformation(RetRelationNumber
								,RetRelationName
								,RetRemark
								,RetRelationType
								,CommonData
								,ThresholdLevelID)==false){
			return false;
		}


		WriteCell(Row, 0,"マスター",SheetNo);
		WriteCell(Row, 1,MasterRelationCode,SheetNo);
		Row++;
		WriteCell(Row, 0,LBase->GetParamPQSystem()->TitleMasterNumber,SheetNo);
		WriteCell(Row, 1,RetRelationNumber,SheetNo);
		WriteCell(Row, 2,RetRelationName,SheetNo);
		Row++;
		WriteCell(Row, 0,LBase->GetParamPQSystem()->TitleRemark,SheetNo);
		WriteCell(Row, 1,RetRemark,SheetNo);
		Row++;

		int	NGTotalCount[100];
		int	Col=0;
		for(EachMaster *m=MBase->MasterDatas.GetFirst();m!=NULL;m=m->GetNext(),Col++){
			WriteCell(Row, Col+2,m->GetMachineName(),SheetNo);
			NGTotalCount[Col]=0;
		}
		WriteCell(Row, Col+2,/**/"刃不良",SheetNo);
		int	FinalTotalCount=0;
		Row++;



		Sheet1Pack	Sheet1LotData;

		Col=1;
		for(NGListWithImages *R=ResultList.GetFirst();R!=NULL;R=R->GetNext()){
			if(R->RelationCode==MasterRelationCode){
				InspectionListByMaster	*LByMaster=R->LotPointer->CurrentInspection.GetFirst();
				if(LByMaster!=NULL){
					Sheet1Lot	*sLot=Sheet1LotData.SearchByLotAutoCount(LByMaster->LotListData.GlobalID);
					if(sLot==NULL){
						sLot=new Sheet1Lot();
						sLot->LotAutoCount	=LByMaster->LotListData.GlobalID;
						sLot->LotID			=LByMaster->LotListData.LotID;
						sLot->LotName		=LByMaster->LotListData.LotName;
						Sheet1LotData.AppendList(sLot);
					}
					for(NGListByMaster *M=R->NGImageBYMaster.GetFirst();M!=NULL;M=M->GetNext()){
						EachMaster	*m=MBase->FindMaster(M->MachineID);
						for(InspectionListByMaster *w=R->LotPointer->CurrentInspection.GetFirst();w!=NULL;w=w->GetNext()){
							if(w->MachineID==m->GetMachineCode()){
								m->SetCurrentLot(&w->LotListData);
								m->RemoveAllCurrentInspection();
								m->LoadLot(&w->LotListData);
								sLot->TotalCount[m->GetMachineCode()]=m->GetCurrentInspection().GetCount();
							}
						}

						for(PointerList<IntegNGImage> *t=M->NGImages.GetFirst();t!=NULL;t=t->GetNext()){
							Sheet1ByID	*sSheetID=sLot->SearchByID(R->InspectionID);
							if(sSheetID==NULL){
								sSheetID=new Sheet1ByID();
								sSheetID->InspectionID	=R->InspectionID;
								sSheetID->Time			=R->InspectionTime;
								sLot->NGSheet.AppendList(sSheetID);
							}
							
							Sheet1ByImage	*sImg	=SetNGImage3(m ,R->InspectionID ,t->Get());
							if(sImg!=NULL){
								sSheetID->Images.AppendList(sImg);
							}
						}
					}
				}
			}
		}

		int	AllTotalNGCount[100];
		int	AllTotalCount=0;
		int	AllNGCountMeasure=0;
		memset(AllTotalNGCount,0,sizeof(AllTotalNGCount));

		for(Sheet1Lot *sLot=Sheet1LotData.GetFirst();sLot!=NULL;sLot=sLot->GetNext()){
			WriteCell(Row  , 0,sLot->LotName+QString(/**/":")+sLot->LotID,SheetNo);
			WriteCell(Row  , 1,"ＮＧ数",SheetNo);
			WriteCell(Row+1, 1,"全数",SheetNo);
			Col=2;
			int	TotalCount=0;
			int	NGCountMeasure=0;
			for(EachMaster *m=MBase->MasterDatas.GetFirst();m!=NULL;m=m->GetNext(),Col++){
				int	MachineCode=m->GetMachineCode();
				int	NGCountInCam=0;
				for(Sheet1ByID *sSheetID=sLot->NGSheet.GetFirst();sSheetID!=NULL;sSheetID=sSheetID->GetNext()){
					for(Sheet1ByImage *sImg=sSheetID->Images.GetFirst();sImg!=NULL;sImg=sImg->GetNext()){
						if(sImg->MachineID==MachineCode){
							if(sImg->LibType==DefLibTypeMeasureLineMove
							&& sImg->UniqueID<10){
								NGCountMeasure++;
							}
							NGCountInCam++;
							break;
						}
					}
				}
				if(m->GetMachineCode()==2){
					WriteCell(Row  , 2+MBase->MasterDatas.GetCount(),NGCountMeasure	,SheetNo);
					AllNGCountMeasure	+=NGCountMeasure;
				}
				WriteCell(Row  , Col								,NGCountInCam	,SheetNo);
				AllTotalNGCount[MachineCode]+=NGCountInCam;			
				TotalCount=max(TotalCount,sLot->TotalCount[MachineCode]);
			}
			WriteCell(Row+1, 2,TotalCount,SheetNo);
			AllTotalCount+=TotalCount;
			Row+=2;
		}

		WriteCell(Row, 1,"合計NG数",SheetNo);
		Col=0;
		for(EachMaster *m=MBase->MasterDatas.GetFirst();m!=NULL;m=m->GetNext(),Col++){
			int	MachineCode=m->GetMachineCode();
			WriteCell(Row, Col+2,AllTotalNGCount[MachineCode],SheetNo);
		}
		WriteCell(Row, Col+2,AllNGCountMeasure,SheetNo);
		Row++;
		WriteCell(Row, 1,"合計数",SheetNo);
		WriteCell(Row, 2,AllTotalCount,SheetNo);
		
		Row++;
	}
	return true;
}

bool	NGImageListForm::MakeExcelSheet3(void)
{
	LayersBasePQSystem	*LBase=(LayersBasePQSystem *)GetLayersBase();
	IntegrationBase	*MBase=GetLayersBase()->GetIntegrationBasePointer();

	int	SheetNo=2;
	AddSheet("種類別集計");
	int	Row=0;
	WriteCell(Row, 0,"NG種類別集計",SheetNo);
	Row++;
	WriteCell(Row, 0,"検索日時",SheetNo);
	WriteCell(Row, 1,StartTime.toString()
					+QString("-")
					+EndTime.toString()
					,SheetNo);
	Row++;

	for(IntClass *d=RemationMasterCodeList.GetFirst();d!=NULL;d=d->GetNext()){
		int	MasterRelationCode=d->GetValue();
		QString	RetRelationNumber;
		QString	RetRelationName;
		QString	RetRemark;
		int		RetRelationType;
		QByteArray	CommonData;
		int32	ThresholdLevelID;
		MBase->SetMasterRelationCode(MasterRelationCode);
		if(MBase->GetInformation(RetRelationNumber
								,RetRelationName
								,RetRemark
								,RetRelationType
								,CommonData
								,ThresholdLevelID)==false){
			return false;
		}


		WriteCell(Row, 0,"マスター",SheetNo);
		WriteCell(Row, 1,MasterRelationCode,SheetNo);
		Row++;
		WriteCell(Row, 0,LBase->GetParamPQSystem()->TitleMasterNumber,SheetNo);
		WriteCell(Row, 1,RetRelationNumber,SheetNo);
		WriteCell(Row, 2,RetRelationName,SheetNo);
		Row++;
		WriteCell(Row, 0,LBase->GetParamPQSystem()->TitleRemark,SheetNo);
		WriteCell(Row, 1,RetRemark,SheetNo);
		Row++;

		int	IndexSlaveNo=-1;
		BladeMeasure	BladeMeasureData[10];
		BladeMeasure	FilmMeasureData[10];
		for(int SlaveNo=0;SlaveNo<10;SlaveNo++){
			QVariant	data;
			QString	FieldName=QString(/**/"DentMeasureBlade")+QString::number(SlaveNo);
			if(GetLayersBase()->LoadRelationFieldData(MasterRelationCode
													,FieldName, data)==true){
				QByteArray	BData=data.toByteArray();
				QBuffer	File(&BData);
				if(File.open(QIODevice::ReadOnly)==true){
					BladeMeasureData[SlaveNo].Load(&File);
					FilmMeasureData[SlaveNo].Load(&File);
					if(BladeMeasureData[SlaveNo].CountGenDatas>0){
						IndexSlaveNo=SlaveNo;
					}
				}
			}
		}


		NPListPack<LibTypeIDList>	LibTypeIDListPack[100];

		for(LotListContainerWithRelationCode *R=AllLotList.GetFirst();R!=NULL;R=R->GetNext()){
			if(R->RelationCode==MasterRelationCode){
				for(LotListWithResult *L=R->Container.GetFirst();L!=NULL;L=L->GetNext()){
					if(L->Effective==true){
						InspectionListByMaster	*p=L->CurrentInspection.GetFirst();
						if(p!=NULL){
							for(EachMaster *m=MBase->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
								for(InspectionListByMaster	*s=L->CurrentInspection.GetFirst();s!=NULL;s=s->GetNext()){
									if(s->LotListData.LotName==p->LotListData.LotName
									&& s->LotListData.LotID==p->LotListData.LotID
									&& s->MachineID==m->GetMachineCode()){
										m->ClearCurrentLot();
										m->SetCurrentLot(&s->LotListData);
										m->LoadLot(&s->LotListData);
										int	NGCount=0;
										int	TotalCount=0;
										for(InspectionList *L=m->GetCurrentInspection().GetFirst();L!=NULL;L=L->GetNext()){
											for(NGPointInAllPage *Ph=L->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
												for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
													for(NGPoint *p=Pg->NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
														if(LibraryExist(p->LibType,p->LibID)==true){
															LibTypeIDList *t;
															for(t=LibTypeIDListPack[s->MachineID].GetFirst();t!=NULL;t=t->GetNext()){
																if(p->LibType==DefLibTypeMeasureLineMove
																&& p->LibType==t->LibType
																&& p->LibID==t->LibID
																&& p->UniqueID==t->UniqueID){
																	if(p->Error>1){
																		t->NGCount++;
																	}
																	t->ResultValueList.Add(p->DoubleCause);
																	break;
																}
																else
																if(p->LibType!=DefLibTypeMeasureLineMove
																&& p->LibType==t->LibType
																&& p->LibID==t->LibID){
																	if(p->Error>1){
																		t->NGCount++;
																	}
																	t->ResultValueList.Add(p->DoubleCause);
																	break;
																}
															}
															if(t==NULL){
																t=new LibTypeIDList;
																t->LibType	=p->LibType;
																t->LibID	=p->LibID;
																t->UniqueID	=p->UniqueID;
																if(p->Error>1){
																	t->NGCount	=1;
																}
																else{
																	t->NGCount	=0;
																}
																t->ResultValueList.Add(p->DoubleCause);
																LibTypeIDListPack[s->MachineID].AppendList(t);
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		Row++;
		for(EachMaster *m=MBase->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			WriteCell(Row, 0,m->GetMachineName(),SheetNo);
			Row++;
			WriteCell(Row, 0,"ライブラリ種類"	,Qt::green,SheetNo);
			WriteCell(Row, 1,"ライブラリID"		,Qt::green,SheetNo);
			WriteCell(Row, 2,"名称"				,Qt::green,SheetNo);
			WriteCell(Row, 3,"ＮＧ箇所"			,Qt::green,SheetNo);
			Row++;
			for(LibTypeIDList *t=LibTypeIDListPack[m->GetMachineCode()].GetFirst();t!=NULL;t=t->GetNext()){
				if(t->LibType==DefLibTypeMeasureLineMove){
					if(IndexSlaveNo<0){
						AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(t->LibType);
						if(ABase!=NULL)
							WriteCell(Row, 0,ABase->GetNameByCurrentLanguage()/*GetLayersBase()->GetLibTypeName(t->LibType)*/,SheetNo);
						else
							WriteCell(Row, 0,GetLayersBase()->GetLibTypeName(t->LibType),SheetNo);
						WriteCell(Row, 1,t->LibID	,SheetNo);
						WriteCell(Row, 2,t->UniqueID,SheetNo);
						WriteCell(Row, 3,t->NGCount	,SheetNo);
					}
					else{
						AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(t->LibType);
						if(ABase!=NULL)
							WriteCell(Row, 0,ABase->GetNameByCurrentLanguage()/*GetLayersBase()->GetLibTypeName(t->LibType)*/,SheetNo);
						else
							WriteCell(Row, 0,GetLayersBase()->GetLibTypeName(t->LibType),SheetNo);
						WriteCell(Row, 1,t->LibID	,SheetNo);
						if(0<=t->UniqueID && t->UniqueID<1000){
							QString	VName=QString::fromLocal8Bit(BladeMeasureData[IndexSlaveNo].GenDatas[t->UniqueID].MeasureName);
							WriteCell(Row, 2,VName,SheetNo);
							WriteCell(Row, 3,t->NGCount	,SheetNo);
						}
						else
						if(1000<=t->UniqueID && t->UniqueID<2000){
							int	n=t->UniqueID-1000;
							QString	VName=QString::fromLocal8Bit(FilmMeasureData[IndexSlaveNo].GenDatas[n].MeasureName);
							WriteCell(Row, 2,VName,SheetNo);
							WriteCell(Row, 3,t->NGCount	,SheetNo);
						}
					}
				}
				else{
					AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(t->LibType);
					if(ABase!=NULL)
						WriteCell(Row, 0,ABase->GetNameByCurrentLanguage()/*GetLayersBase()->GetLibTypeName(t->LibType)*/,SheetNo);
					else
						WriteCell(Row, 0,GetLayersBase()->GetLibTypeName(t->LibType),SheetNo);
					WriteCell(Row, 1,t->LibID	,SheetNo);
					WriteCell(Row, 2,GetLayersBase()->GetLibraryName(t->LibType,t->LibID),SheetNo);
					WriteCell(Row, 3,t->NGCount	,SheetNo);
				}
				Row++;
			}
			Row++;
		}
	}
	return true;
}


bool	NGImageListForm::MakeExcelSheet4(void)
{
	LayersBasePQSystem	*LBase=(LayersBasePQSystem *)GetLayersBase();
	IntegrationBase	*MBase=GetLayersBase()->GetIntegrationBasePointer();

	int	SheetNo=3;
	AddSheet("ＮＧデータ");
	int	Row=0;
	WriteCell(Row, 0,"ＮＧデータ",SheetNo);
	Row++;
	WriteCell(Row, 0,"検索日時",SheetNo);
	WriteCell(Row, 1,StartTime.toString()
					+QString("-")
					+EndTime.toString()
					,SheetNo);
	Row++;
	for(IntClass *d=RemationMasterCodeList.GetFirst();d!=NULL;d=d->GetNext()){
		int	MasterRelationCode=d->GetValue();
		QString	RetRelationNumber;
		QString	RetRelationName;
		QString	RetRemark;
		int		RetRelationType;
		QByteArray	CommonData;
		int32	ThresholdLevelID;
		MBase->SetMasterRelationCode(MasterRelationCode);
		if(MBase->GetInformation(RetRelationNumber
								,RetRelationName
								,RetRemark
								,RetRelationType
								,CommonData
								,ThresholdLevelID)==false){
			return false;
		}

		WriteCell(Row, 0,"マスター",SheetNo);
		WriteCell(Row, 1,MasterRelationCode,SheetNo);
		Row++;
		WriteCell(Row, 0,LBase->GetParamPQSystem()->TitleMasterNumber,SheetNo);
		WriteCell(Row, 1,RetRelationNumber	,SheetNo);
		WriteCell(Row, 2,RetRelationName	,SheetNo);
		Row++;
		WriteCell(Row, 0,LBase->GetParamPQSystem()->TitleRemark,SheetNo);
		WriteCell(Row, 1,RetRemark,SheetNo);
		Row++;

		bool	FirstOne=true;

		for(EachMaster *m=MBase->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			AlgorithmForReport	AlgoL(m->GetMasterCode(),m->GetMachineCode(),GetLayersBase());

			AlgoL.run();
			for(ReportDataStructure::ReportAlgorithmList *A=AlgoL.ReportData.ReportAlgorithmContainer.GetFirst();A!=NULL;A=A->GetNext()){
				if(A->DLLRoot==/**/"Basic"
				&& A->DLLName==/**/"DotColorMatching"){
					AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(A->DLLRoot,A->DLLName);
					AlgorithmLibraryContainer	*ALibC=(ABase!=NULL)?ABase->GetLibraryContainer():NULL;
					for(ReportDataStructure::ReportAlgorithmList::ReportLibraryList *L=A->ReportLibraryContainer.GetFirst();L!=NULL;L=L->GetNext()){

						//Row++;

						//WriteCell(Row, 2,"ItemCount"					,SheetNo);
						//WriteCell(Row, 3,QString::number(L->ItemCount)	,SheetNo);
						//Row++;
						//
						//WriteCell(Row, 2,"TotalArea"						,SheetNo);
						//WriteCell(Row, 3,QString::number(L->TotalAreaDots)	,SheetNo);
						//Row++;

						//if(L->LibID>=0){
						//	if(L->LibraryTopics.IsEmpty()==false){
						//		WriteCell(Row  , 2,"LibData"	,SheetNo);
						//		int Col=0;
						//		for(ReportedTopic *t=L->LibraryTopics.GetFirst();t!=NULL;t=t->GetNext(),Col++){
						//			WriteCell(Row   , 3+Col,t->Title	,SheetNo);
						//			WriteCellV(Row+1, 3+Col,t->Data		,SheetNo);
						//		}
						//		Row+=2;
						//	}
						//}

						if(FirstOne==true){
							if(L->ItemTypicalTopics.IsEmpty()==false){
								WriteCell(Row, 2,"ライブラリID"	,SheetNo);
								WriteCell(Row, 3,"ライブラリ名"	,SheetNo);
								WriteCell(Row, 4,"カメラ名"		,SheetNo);
								int Col=0;
								for(ReportedTopic *t=L->ItemTypicalTopics.GetFirst();t!=NULL;t=t->GetNext(),Col++){
									if(Col<=8){
										WriteCell(Row   , 5+Col,t->Title	,SheetNo);
									}
								}
								Row++;
								FirstOne=false;
							}
						}

						if(L->ItemTypicalTopics.IsEmpty()==false){
							//WriteCell(Row, 1,"Library",SheetNo);
							if(L->LibID>=0){
								WriteCell(Row, 2,QString::number(L->LibID)	,SheetNo);
								if(ALibC!=NULL){
									WriteCell(Row, 3,ALibC->GetLibraryName(L->LibID)	,SheetNo);
								}
								else{
									WriteCell(Row, 3,L->LibName	,SheetNo);
								}
							}
							else{
								WriteCell(Row, 2,QString("No Library")	,SheetNo);
							}
							WriteCell(Row, 4,m->GetMachineName(),SheetNo);

							int Col=0;
							for(ReportedTopic *t=L->ItemTypicalTopics.GetFirst();t!=NULL;t=t->GetNext(),Col++){
								if(Col<=8){
									WriteCellV(Row, 5+Col,t->Data		,SheetNo);
								}
							}
							Row++;
						}
					}
				}
			}
		}

		//NPListPack<NGInfoList>		NGInfoListData[100];
		NPListPack<NGInfoListInLot>	NGInfoListInLotPack;
		NPListPack<NGLibTypeIDList>	NGLibTypeIDListPack;
		//IntList						LotGlobalID;

		for(LotListContainerWithRelationCode *R=AllLotList.GetFirst();R!=NULL;R=R->GetNext()){
			if(R->RelationCode==MasterRelationCode){
				for(LotListWithResult *L=R->Container.GetFirst();L!=NULL;L=L->GetNext()){
					if(L->Effective==true){
						InspectionListByMaster	*p=L->CurrentInspection.GetFirst();
						if(p!=NULL){
							for(EachMaster *m=MBase->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
								for(InspectionListByMaster	*s=L->CurrentInspection.GetFirst();s!=NULL;s=s->GetNext()){
									if(s->LotListData.LotName==p->LotListData.LotName
									&& s->LotListData.LotID==p->LotListData.LotID
									&& s->MachineID==m->GetMachineCode()){
										//LotGlobalID.Merge(p->LotListData.GlobalID);
										NGInfoListInLot *CLot=NULL;
										for(NGInfoListInLot *h=NGInfoListInLotPack.GetFirst();h!=NULL;h=h->GetNext()){
											if(h->LotAutoCount==p->LotListData.GlobalID){
												CLot=h;
												break;
											}
										}
										if(CLot==NULL){
											CLot=new NGInfoListInLot();
											CLot->LotAutoCount=p->LotListData.GlobalID;
											NGInfoListInLotPack.AppendList(CLot);
										}

										m->ClearCurrentLot();
										m->SetCurrentLot(&s->LotListData);
										m->LoadLot(&s->LotListData);
										int	NGCount=0;
										int	TotalCount=0;
										for(InspectionList *IL=m->GetCurrentInspection().GetFirst();IL!=NULL;IL=IL->GetNext()){
											bool	FoundData=false;
											for(NGPointInAllPage *Ph=IL->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
												for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
													for(NGPoint *np=Pg->NPListPack<NGPoint>::GetFirst();np!=NULL;np=np->GetNext()){
														if(np->LibType!=DefLibTypeMeasureLineMove
														&& LibraryExist(np->LibType,np->LibID)==true){
															int	FoundK=-1;
															NGLibTypeIDList	*Found;
															int	k=0;
															for(NGLibTypeIDList *d=NGLibTypeIDListPack.GetFirst();d!=NULL;d=d->GetNext(),k++){
																if(d->LibType==np->LibType
																&& d->LibID==np->LibID
																&& d->NGType==np->GetCauseType()){
																	FoundK=k;
																	Found=d;
																	break;
																}
															}
															if(FoundK==-1){
																FoundK=k;
																NGLibTypeIDList	*d=new NGLibTypeIDList();
																Found=d;
																d->LibType	=np->LibType;
																d->LibID	=np->LibID;
																d->NGType	=np->GetCauseType();
																d->ResultType=np->ResultType;
																NGLibTypeIDListPack.AppendList(d);
															}
															NGInfoList	*G=new NGInfoList();
															G->GType		=Found;
															G->Master		=m;
															G->InspectionID	=IL->ID;
															G->DoubleCause		=np->DoubleCause;
															G->Cause[0]			=np->Cause[0];
															G->Cause[1]			=np->Cause[1];
															CLot->NGInfoListData[FoundK].AppendList(G);
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		Row++;
		int	k=0;
		for(NGLibTypeIDList *d=NGLibTypeIDListPack.GetFirst();d!=NULL;d=d->GetNext(),k++){
			DetailResultInfoListContainer ItemDetailList;
			AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(d->LibType);
			if(ABase!=NULL){
				QRgb		NGColor;

				ResultPosList	RPos;
				RPos.result		=d->NGType;

				RPos.Px			=0;
				RPos.Py			=0;
				RPos.Rx			=0;
				RPos.Ry			=0;

				ABase->GetDrawResultDetail(NULL ,&RPos ,ItemDetailList);
			}
			WriteCell(Row  , k+2,ABase->GetNameByCurrentLanguage()/*GetLayersBase()->GetLibTypeName(d->LibType)*/,SheetNo);
			WriteCell(Row+1, k+2,GetLayersBase()->GetLibraryName(d->LibType,d->LibID),SheetNo);

			QStringList	ResultString;
			ItemDetailList.GetInfoStringList(ResultString);
			if(ResultString.count()>0){
				if(ResultString.count()>=2){
					WriteCell(Row+2, k+2,ResultString[0],SheetNo);
					//WriteCell(Row+3, k+2,ResultString[1],SheetNo);
				}
				else{
					WriteCell(Row+2, k+2,ResultString[0],SheetNo);
				}
			}
			else{
				WriteCell(Row+2, k+2,QString::number(d->NGType),SheetNo);
			}
		}
		WriteCell(Row+3,0,"ロット名",SheetNo);
		WriteCell(Row+3,1,"検査ID"	,SheetNo);
		Row+=4;
		int	TypeCount=NGLibTypeIDListPack.GetCount();

		for(NGInfoListInLot *C=NGInfoListInLotPack.GetFirst();C!=NULL;C=C->GetNext()){
		//for(IntClass *c=LotGlobalID.GetFirst();c!=NULL;c=c->GetNext()){
			int	LotNo=C->LotAutoCount;
			int	LastInspectionID=-1;
			NGInfoList	*PointerG[100];
			for(int k=0;k<TypeCount;k++){
				PointerG[k]=C->NGInfoListData[k].GetFirst();
			}
			for(;;){
				int	MinInspectionID=999999999;
				for(int k=0;k<TypeCount;k++){
					if(PointerG[k]!=NULL
					&& PointerG[k]->InspectionID>LastInspectionID){
						if(MinInspectionID>PointerG[k]->InspectionID){
							MinInspectionID=PointerG[k]->InspectionID;
						}
					}
				}
				if(MinInspectionID<999999999){
					WriteCell(Row, 1,QString::number(MinInspectionID),SheetNo);
					for(int k=0;k<TypeCount;k++){
						if(PointerG[k]!=NULL
						&& PointerG[k]->InspectionID==MinInspectionID){

							QString	CauseStr;
							if(PointerG[k]->GType->ResultType==_ResultDouble){
								CauseStr=QString::number(PointerG[k]->Master->TransformUnitToPixel(PointerG[k]->DoubleCause),'f',2);
										
							}
							else{
								if((PointerG[k]->GType->NGType&0xFF)==2){
									CauseStr=QString::number(PointerG[k]->Master->TransformPixelToUnit(PointerG[k]->Cause[1]),'f',2);
								}
								else{
									CauseStr=QString::number(PointerG[k]->Master->TransformPixelToUnitSquare(PointerG[k]->Cause[0]),'f',2);
								}
							}

							WriteCell(Row, 2+k,CauseStr,SheetNo);
							PointerG[k]=PointerG[k]->GetNext();
						}
						else{
							WriteCell(Row, 2+k,/**/"",SheetNo);
						}
					}
				}
				else{
					break;
				}
				for(LotListContainerWithRelationCode *R=AllLotList.GetFirst();R!=NULL;R=R->GetNext()){
					if(R->RelationCode==MasterRelationCode){
						for(LotListWithResult *L=R->Container.GetFirst();L!=NULL;L=L->GetNext()){
							if(L->Effective==true){
								InspectionListByMaster	*p=L->CurrentInspection.GetFirst();
								if(p!=NULL){
									if(p->LotListData.GlobalID==LotNo){
										WriteCell(Row, 0,p->LotListData.LotName,SheetNo);
										goto CBreak;
									}
								}
							}
						}
					}
				}
				CBreak:;
				LastInspectionID=MinInspectionID;
				Row++;
			}
		}
	}
	return true;
}

bool	NGImageListForm::MakeExcelSheet5(void)
{
	LayersBasePQSystem	*LBase=(LayersBasePQSystem *)GetLayersBase();
	IntegrationBase	*MBase=GetLayersBase()->GetIntegrationBasePointer();

	for(IntClass *d=RemationMasterCodeList.GetFirst();d!=NULL;d=d->GetNext()){
		int	MasterRelationCode=d->GetValue();
		QString	RetRelationNumber;
		QString	RetRelationName;
		QString	RetRemark;
		int		RetRelationType;
		QByteArray	CommonData;
		int32	ThresholdLevelID;
		MBase->SetMasterRelationCode(MasterRelationCode);
		if(MBase->GetInformation(RetRelationNumber
								,RetRelationName
								,RetRemark
								,RetRelationType
								,CommonData
								,ThresholdLevelID)==false){
			return false;
		}
		int	IndexSlaveNo=-1;
		BladeMeasure	BladeMeasureData[10];
		BladeMeasure	FilmMeasureData[10];
		for(int SlaveNo=0;SlaveNo<10;SlaveNo++){
			QVariant	data;
			QString	FieldName=QString(/**/"DentMeasureBlade")+QString::number(SlaveNo);
			if(GetLayersBase()->LoadRelationFieldData(MasterRelationCode
													,FieldName, data)==true){
				QByteArray	BData=data.toByteArray();
				QBuffer	File(&BData);
				if(File.open(QIODevice::ReadOnly)==true){
					BladeMeasureData[SlaveNo].Load(&File);
					FilmMeasureData[SlaveNo].Load(&File);
					if(BladeMeasureData[SlaveNo].CountGenDatas>0){
						IndexSlaveNo=SlaveNo;
					}
				}
			}
		}
		if(IndexSlaveNo<0){
			return false;
		}
	}




	int	SheetNo=4;
	AddSheet("計測データ");
	int	Row=0;
	WriteCell(Row, 0,"計測データ",SheetNo);
	Row++;
	WriteCell(Row, 0,"検索日時",SheetNo);
	WriteCell(Row, 1,StartTime.toString()
					+QString("-")
					+EndTime.toString()
					,SheetNo);
	Row++;

	for(IntClass *d=RemationMasterCodeList.GetFirst();d!=NULL;d=d->GetNext()){
		int	MasterRelationCode=d->GetValue();
		QString	RetRelationNumber;
		QString	RetRelationName;
		QString	RetRemark;
		int		RetRelationType;
		QByteArray	CommonData;
		int32	ThresholdLevelID;
		MBase->SetMasterRelationCode(MasterRelationCode);
		if(MBase->GetInformation(RetRelationNumber
								,RetRelationName
								,RetRemark
								,RetRelationType
								,CommonData
								,ThresholdLevelID)==false){
			return false;
		}


		WriteCell(Row, 0,"マスター",SheetNo);
		WriteCell(Row, 1,MasterRelationCode,SheetNo);
		Row++;
		WriteCell(Row, 0,LBase->GetParamPQSystem()->TitleMasterNumber,SheetNo);
		WriteCell(Row, 1,RetRelationNumber,SheetNo);
		WriteCell(Row, 2,RetRelationName,SheetNo);
		Row++;
		WriteCell(Row, 0,LBase->GetParamPQSystem()->TitleRemark,SheetNo);
		WriteCell(Row, 1,RetRemark,SheetNo);
		Row++;

		int	IndexSlaveNo=-1;
		BladeMeasure	BladeMeasureData[10];
		BladeMeasure	FilmMeasureData[10];
		for(int SlaveNo=0;SlaveNo<10;SlaveNo++){
			QVariant	data;
			QString	FieldName=QString(/**/"DentMeasureBlade")+QString::number(SlaveNo);
			if(GetLayersBase()->LoadRelationFieldData(MasterRelationCode
													,FieldName, data)==true){
				QByteArray	BData=data.toByteArray();
				QBuffer	File(&BData);
				if(File.open(QIODevice::ReadOnly)==true){
					BladeMeasureData[SlaveNo].Load(&File);
					FilmMeasureData[SlaveNo].Load(&File);
					if(BladeMeasureData[SlaveNo].CountGenDatas>0){
						IndexSlaveNo=SlaveNo;
					}
				}
			}
		}
		if(IndexSlaveNo<0){
			return false;
		}
		double	*MeasureData[100];
		bool	*ResultOK[100];
		int	MeasureCount=0;
		int	MaxIDCount=min(BladeMeasureData[IndexSlaveNo].CountGenDatas,100);
		const	int	MaxMeasureDataCount=1000000;
		for(int i=0;i<MaxIDCount;i++){
			MeasureData[i]=new double[MaxMeasureDataCount];
			ResultOK[i]=new bool [MaxMeasureDataCount];
			for(int k=0;k<MaxMeasureDataCount;k++){
				(MeasureData[i])[k]=0.0;
				(ResultOK[i])[k]=true;
			}
		}
		double	*FMeasureData[100];
		bool	*FResultOK[100];
		int	FilmMaxIDCount=min(FilmMeasureData[IndexSlaveNo].CountGenDatas,100);
		const	int	FilmMaxMeasureDataCount=1000000;
		for(int i=0;i<FilmMaxIDCount;i++){
			FMeasureData[i]=new double[FilmMaxMeasureDataCount];
			FResultOK[i]=new bool [FilmMaxMeasureDataCount];
			for(int k=0;k<FilmMaxMeasureDataCount;k++){
				(FMeasureData[i])[k]=0.0;
				(FResultOK[i])[k]=true;
			}
		}
		NPListPack<LibTypeIDList>	LibTypeIDListPack[100];

		for(LotListContainerWithRelationCode *R=AllLotList.GetFirst();R!=NULL;R=R->GetNext()){
			if(R->RelationCode==MasterRelationCode){
				for(LotListWithResult *L=R->Container.GetFirst();L!=NULL;L=L->GetNext()){
					if(L->Effective==true){
						InspectionListByMaster	*p=L->CurrentInspection.GetFirst();
						if(p!=NULL){
							for(EachMaster *m=MBase->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
								for(InspectionListByMaster	*s=L->CurrentInspection.GetFirst();s!=NULL;s=s->GetNext()){
									if(s->LotListData.LotName==p->LotListData.LotName
									&& s->LotListData.LotID==p->LotListData.LotID
									&& s->MachineID==m->GetMachineCode()){
										m->ClearCurrentLot();
										m->SetCurrentLot(&s->LotListData);
										m->LoadLot(&s->LotListData);
										int	NGCount=0;
										int	TotalCount=0;
										for(InspectionList *IL=m->GetCurrentInspection().GetFirst();IL!=NULL;IL=IL->GetNext()){
											bool	FoundData=false;
											for(NGPointInAllPage *Ph=IL->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
												for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
													for(NGPoint *p=Pg->NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
														if(p->LibType==DefLibTypeMeasureLineMove){
															if(0<=p->UniqueID && p->UniqueID<MaxIDCount){
																(MeasureData[p->UniqueID])[MeasureCount]=p->DoubleCause;
																if(p->Error>=2){
																	(ResultOK[p->UniqueID])[MeasureCount]=false;
																}
																FoundData=true;
															}
															else
															if(1000<=p->UniqueID && p->UniqueID<2000){
																int	ID=p->UniqueID-1000;
																(FMeasureData[ID])[MeasureCount]=p->DoubleCause;
																if(p->Error>=2){
																	(FResultOK[ID])[MeasureCount]=false;
																}
																FoundData=true;
															}														}
													}
												}
											}
											if(FoundData==true){
												MeasureCount++;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		Row++;
		for(int i=0;i<MaxIDCount;i++){
			WriteCell(Row, i+1,QString::fromLocal8Bit(BladeMeasureData[IndexSlaveNo].GenDatas[i].MeasureName),SheetNo);
		}
		for(int i=0;i<FilmMaxIDCount;i++){
			WriteCell(Row, MaxIDCount+i+1,QString::fromLocal8Bit(FilmMeasureData[IndexSlaveNo].GenDatas[i].MeasureName),SheetNo);
		}

		Row++;
		WriteCell(Row  ,0,"下限値",SheetNo);
		WriteCell(Row+1,0,"上限値",SheetNo);
		for(int i=0;i<MaxIDCount;i++){
			double	LLevel=BladeMeasureData[IndexSlaveNo].GenDatas[i].CorrectLength-BladeMeasureData[IndexSlaveNo].GenDatas[i].OKWidth/2.0;
			double	HLevel=BladeMeasureData[IndexSlaveNo].GenDatas[i].CorrectLength+BladeMeasureData[IndexSlaveNo].GenDatas[i].OKWidth/2.0;
			WriteCell(Row+0, i+1,LLevel,SheetNo);
			WriteCell(Row+1, i+1,HLevel,SheetNo);
		}
		for(int i=0;i<FilmMaxIDCount;i++){
			double	LLevel=FilmMeasureData[IndexSlaveNo].GenDatas[i].CorrectLength-FilmMeasureData[IndexSlaveNo].GenDatas[i].OKWidth/2.0;
			double	HLevel=FilmMeasureData[IndexSlaveNo].GenDatas[i].CorrectLength+FilmMeasureData[IndexSlaveNo].GenDatas[i].OKWidth/2.0;
			WriteCell(Row+0, MaxIDCount+i+1,LLevel,SheetNo);
			WriteCell(Row+1, MaxIDCount+i+1,HLevel,SheetNo);
		}
		Row+=2;
		for(int k=0;k<MeasureCount;k++){
			WriteCell(Row+k, 0,k+1,SheetNo);
		}
		for(int i=0;i<MaxIDCount;i++){
			for(int k=0;k<MeasureCount;k++){
				if((ResultOK[i])[k]==true){
				}
				WriteCell(Row+k, i+1,(MeasureData[i])[k],SheetNo);

				double	LLevel=BladeMeasureData[IndexSlaveNo].GenDatas[i].CorrectLength-BladeMeasureData[IndexSlaveNo].GenDatas[i].OKWidth/2.0;
				double	HLevel=BladeMeasureData[IndexSlaveNo].GenDatas[i].CorrectLength+BladeMeasureData[IndexSlaveNo].GenDatas[i].OKWidth/2.0;

				WriteCell(Row+k, 10+i*2 ,LLevel,SheetNo);
				WriteCell(Row+k, 10+i*2+1,HLevel,SheetNo);
			}
		}
		for(int i=0;i<FilmMaxIDCount;i++){
			for(int k=0;k<MeasureCount;k++){
				if((FResultOK[i])[k]==true){
				}
				WriteCell(Row+k, MaxIDCount+i+1,(FMeasureData[i])[k],SheetNo);

				double	LLevel=FilmMeasureData[IndexSlaveNo].GenDatas[i].CorrectLength-FilmMeasureData[IndexSlaveNo].GenDatas[i].OKWidth/2.0;
				double	HLevel=FilmMeasureData[IndexSlaveNo].GenDatas[i].CorrectLength+FilmMeasureData[IndexSlaveNo].GenDatas[i].OKWidth/2.0;

				WriteCell(Row+k, 10+(MaxIDCount+i)*2  ,LLevel,SheetNo);
				WriteCell(Row+k, 10+(MaxIDCount+i)*2+1,HLevel,SheetNo);
			}
		}

		int	CenterKDim[100];
		for(int i=0;i<MaxIDCount;i++){
			double	BandL[1000];
			double	Step=0.1;
			int		Histgram[1000];
			for(int k=0;k<sizeof(BandL)/sizeof(BandL[0]);k++){
				BandL[k]=k*Step;
				Histgram[k]=0;
			}
			
			for(int k=0;k<MeasureCount;k++){
				double	d=(MeasureData[i])[k];
				int	n=d/Step;
				if(0<=n && n<sizeof(BandL)/sizeof(BandL[0])){
					Histgram[n]++;
				}
			}
			int	MaxHist=0;
			int	CenterK=0;
			for(int k=0;k<sizeof(BandL)/sizeof(BandL[0]);k++){
				if(Histgram[k]>MaxHist){
					MaxHist=Histgram[k];
					CenterK=k;
					CenterKDim[i]=k;
				}
			}
			if(i==1)
				CenterK=CenterKDim[0];
			else if(i==4)
				CenterK=CenterKDim[3];
			else if(i==6)
				CenterK=CenterKDim[5];
			else if(i==8)
				CenterK=CenterKDim[7];

			double	LLevel=BladeMeasureData[IndexSlaveNo].GenDatas[i].CorrectLength-BladeMeasureData[IndexSlaveNo].GenDatas[i].OKWidth/2.0;
			double	HLevel=BladeMeasureData[IndexSlaveNo].GenDatas[i].CorrectLength+BladeMeasureData[IndexSlaveNo].GenDatas[i].OKWidth/2.0;

			int	LLevelK=LLevel/Step;
			int	HLevelK=HLevel/Step;

			int	MinK=Clipping(CenterK-20,0,sizeof(BandL)/sizeof(BandL[0]));
			int	MaxK=Clipping(CenterK+20,0,sizeof(BandL)/sizeof(BandL[0]));

			int	k=0;
			for(int m=MinK;m<MaxK;m++,k++){
				WriteCell(Row+k, 26+i*3		,BandL[m],SheetNo);
				WriteCell(Row+k, 26+i*3+1	,Histgram[m],SheetNo);
				if(LLevelK==m || HLevelK==m){
					WriteCell(Row+k, 26+i*3+2,MaxHist,SheetNo);
				}
				else{
					WriteCell(Row+k, 26+i*3+2,0,SheetNo);
				}
			}
		}
		int	FilmCenterKDim[100];
		for(int i=0;i<FilmMaxIDCount;i++){
			double	BandL[1000];
			double	Step=0.2;
			int		Histgram[1000];
			for(int k=0;k<sizeof(BandL)/sizeof(BandL[0]);k++){
				BandL[k]=k*Step;
				Histgram[k]=0;
			}
			
			for(int k=0;k<MeasureCount;k++){
				double	d=(FMeasureData[i])[k];
				int	n=d/Step;
				if(0<=n && n<sizeof(BandL)/sizeof(BandL[0])){
					Histgram[n]++;
				}
			}
			int	MaxHist=0;
			int	CenterK=0;
			for(int k=0;k<sizeof(BandL)/sizeof(BandL[0]);k++){
				if(Histgram[k]>MaxHist){
					MaxHist=Histgram[k];
					CenterK=k;
					FilmCenterKDim[i]=k;
				}
			}
			if(i==1)
				CenterK=FilmCenterKDim[0];

			double	LLevel=FilmMeasureData[IndexSlaveNo].GenDatas[i].CorrectLength-FilmMeasureData[IndexSlaveNo].GenDatas[i].OKWidth/2.0;
			double	HLevel=FilmMeasureData[IndexSlaveNo].GenDatas[i].CorrectLength+FilmMeasureData[IndexSlaveNo].GenDatas[i].OKWidth/2.0;

			int	LLevelK=LLevel/Step;
			int	HLevelK=HLevel/Step;

			int	MinK=Clipping(CenterK-20,0,sizeof(BandL)/sizeof(BandL[0]));
			int	MaxK=Clipping(CenterK+20,0,sizeof(BandL)/sizeof(BandL[0]));

			int	k=0;
			for(int m=MinK;m<MaxK;m++,k++){
				WriteCell(Row+k, 26+(i+MaxIDCount)*3	,BandL[m],SheetNo);
				WriteCell(Row+k, 26+(i+MaxIDCount)*3+1	,Histgram[m],SheetNo);
				if(LLevelK==m || HLevelK==m){
					WriteCell(Row+k, 26+(i+MaxIDCount)*3+2,MaxHist,SheetNo);
				}
				else{
					WriteCell(Row+k, 26+(i+MaxIDCount)*3+2,0,SheetNo);
				}
			}
		}

		for(int i=0;i<MaxIDCount;i++){
			delete	[]MeasureData[i];
			delete	[]ResultOK[i];
			delete	[]FMeasureData[i];
			delete	[]FResultOK[i];
		}
	}
	return true;
}

bool	NGImageListForm::LibraryExist(int LibType,int LibID)
{
	QString	LibName=GetLayersBase()->GetLibraryName(LibType,LibID);
	if(LibName.isEmpty()==true)
		return false;
	return true;
}

void	NGImageListForm::SetNGImage(EachMaster *m ,int64 InspectionID ,IntegNGImage *g
									,int Row,int Col,int SheetNo)
{
	QTemporaryFile	TmpImageFile;
	TmpImageFile.setAutoRemove(true);
	if(TmpImageFile.open()==true){
		XLSXSheet[SheetNo]->setRow(Row,ExcelImageYLen);	//256);
		XLSXSheet[SheetNo]->setCol(Col, Col,ExcelImageXLen);

		QString	TmpImageFileName=TmpImageFile.fileName();
		g->GetImage().save(&TmpImageFile,"PNG");
		TmpImageFile.flush();
		TmpImageFile.close();
		wchar_t	TmpImageFileBuff[10000];
		memset(TmpImageFileBuff,0,sizeof(TmpImageFileBuff));
		TmpImageFileName.toWCharArray(TmpImageFileBuff);

		int	ImageID=XLSXBook->addPicture(TmpImageFileBuff);
		//SetCellHeight(100,SheetNo);

		XLSXSheet[SheetNo]->setPicture2(Row, Col, ImageID, g->GetImage().width(), g->GetImage().height(),0,0,libxl::POSITION_ONLY_MOVE);
	}
	int	InsNumb=m->GetCurrentInspection().GetCount();
	int	t=0;
	for(InspectionList *L=m->GetCurrentInspection().GetFirst();L!=NULL;L=L->GetNext(),t++){
		if(L->ID!=InspectionID){
			continue;
		}
		for(NGPointInAllPage *Ph=L->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
			for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
				for(NGPoint *Rp=Pg->NPListPack<NGPoint>::GetFirst();Rp!=NULL;Rp=Rp->GetNext()){
					if(LibraryExist(Rp->LibType,Rp->LibID)==true){
						int	TargetCx,TargetCy;
						Rp->GetTargetCenter(TargetCx,TargetCy);
						if(Rp->IsNG()==true
						&& g->x1 <=TargetCx && TargetCx<g->x2
						&& g->y1 <=TargetCy && TargetCy<g->y2){
							QString	LibName=GetLayersBase()->GetDatabaseLoader()->G_GetLibraryName2(*GetLayersBase()->GetDataBase(), Rp->LibType,Rp->LibID);
							WriteCell(Row, 3,Rp->LibID,SheetNo);
							QStringList	List=GetInformation(L,Rp);
							Col++;
							for(int e=0;e<List.count();e++){
								QString		Str=List[e];
								WriteCell(Row, Col,Str,SheetNo);
								Col++;
							}
							return;
						}
					}
				}
			}
		}
	}
}

void	NGImageListForm::SetNGImage2(EachMaster *m ,int64 InspectionID ,IntegNGImage *g
									,int Row,int Col,int SheetNo)
{
	int	InsNumb=m->GetCurrentInspection().GetCount();
	int	t=0;
	for(InspectionList *L=m->GetCurrentInspection().GetFirst();L!=NULL;L=L->GetNext(),t++){
		if(L->ID!=InspectionID){
			continue;
		}
		for(NGPointInAllPage *Ph=L->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
			for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
				for(NGPoint *Rp=Pg->NPListPack<NGPoint>::GetFirst();Rp!=NULL;Rp=Rp->GetNext()){
					if(LibraryExist(Rp->LibType,Rp->LibID)==true){
						int	TargetCx,TargetCy;
						Rp->GetTargetCenter(TargetCx,TargetCy);
						if(Rp->IsNG()==true
						&& g->x1 <=TargetCx && TargetCx<g->x2
						&& g->y1 <=TargetCy && TargetCy<g->y2){
							QString	LibName=GetLayersBase()->GetDatabaseLoader()->G_GetLibraryName2(*GetLayersBase()->GetDataBase(), Rp->LibType,Rp->LibID);
							LibName+=QString(/**/"(")
									+QString::number(Rp->LibID)
									+QString(/**/")");

							WriteCell(Row+0, Col,LibName,SheetNo);
							QStringList	List=GetInformation(L,Rp);
							QString		Str=/**/"";
							for(int e=0;e<List.count();e++){
								Str+=List[e];
								if(e!=(List.count()-1)){
									Str+=QString(/**/",");
								}
							}
							WriteCell(Row+1, Col,Str,SheetNo);
							goto	ToImg;
						}
					}
				}
			}
		}
	}
	ToImg:;

	QTemporaryFile	TmpImageFile;
	TmpImageFile.setAutoRemove(true);
	if(TmpImageFile.open()==true){
		XLSXSheet[SheetNo]->setRow(Row+2 ,ExcelImageYLen);	//256);
		XLSXSheet[SheetNo]->setCol(Col ,Col,ExcelImageXLen);

		QString	TmpImageFileName=TmpImageFile.fileName();
		g->GetImage().save(&TmpImageFile,"PNG");
		TmpImageFile.flush();
		TmpImageFile.close();
		wchar_t	TmpImageFileBuff[10000];
		memset(TmpImageFileBuff,0,sizeof(TmpImageFileBuff));
		TmpImageFileName.toWCharArray(TmpImageFileBuff);

		int	ImageID=XLSXBook->addPicture(TmpImageFileBuff);
		//SetCellHeight(100,SheetNo);

		XLSXSheet[SheetNo]->setPicture2(Row+2, Col, ImageID, g->GetImage().width(), g->GetImage().height(),0,0,libxl::POSITION_ONLY_MOVE);
	}

}


Sheet1ByImage	*NGImageListForm::SetNGImage3(EachMaster *m ,int64 InspectionID ,IntegNGImage *g)
{
	Sheet1ByImage	*sImg=NULL;
	int	InsNumb=m->GetCurrentInspection().GetCount();
	int	t=0;
	for(InspectionList *L=m->GetCurrentInspection().GetFirst();L!=NULL;L=L->GetNext(),t++){
		if(L->ID!=InspectionID){
			continue;
		}
		for(NGPointInAllPage *Ph=L->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
			for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
				for(NGPoint *Rp=Pg->NPListPack<NGPoint>::GetFirst();Rp!=NULL;Rp=Rp->GetNext()){
					if(LibraryExist(Rp->LibType,Rp->LibID)==true){
						int	TargetCx,TargetCy;
						Rp->GetTargetCenter(TargetCx,TargetCy);
						if(Rp->IsNG()==true
						&& g->x1 <=TargetCx && TargetCx<g->x2
						&& g->y1 <=TargetCy && TargetCy<g->y2){
							QString	LibName=GetLayersBase()->GetDatabaseLoader()->G_GetLibraryName2(*GetLayersBase()->GetDataBase(), Rp->LibType,Rp->LibID);
							LibName+=QString(/**/"(")
									+QString::number(Rp->LibID)
									+QString(/**/")");

							sImg=new Sheet1ByImage();
							sImg->MachineID	=m->GetMachineCode();
							sImg->LibType	=Rp->LibType;
							sImg->LibID		=Rp->LibID;
							sImg->LibName	=LibName;
							sImg->UniqueID	=Rp->UniqueID;
							sImg->Causes	=GetInformation(L,Rp);
							sImg->NGImage	=g->GetImage();
							sImg->MasterX	=Rp->MasterX	;
							sImg->MasterY	=Rp->MasterY	;
							goto	ToImg;
						}
					}
				}
			}
		}
	}
ToImg:;
	return sImg;
}

QStringList	NGImageListForm::GetInformation(InspectionList *L,NGPoint *Rp)
{
	QString	CauseStr;
	QString	LibName;
	DetailResultInfoListContainer ItemDetailList;
	if(Rp->LibType!=0){
		if(Rp->LibID>=0){
			LibName=GetLayersBase()->GetIntegrationBasePointer()->GetLibraryName(Rp->LibType ,Rp->LibID);
		}
		if(Rp->ResultType==_ResultDouble){
			if(Rp->Cause[0]!=0 || (Rp->Cause[0]==0 && Rp->DoubleCause==0.0)){
				CauseStr=QString::number(Rp->DoubleCause,'f',2)
						+QString('[')
						+QString::number(L->GetMaster()->TransformPixelToUnit(Rp->Cause[0]),'f',2)
						+QString(']');
			}
			else{
				CauseStr=QString::number(Rp->DoubleCause,'f',2);
			}
		}
		else{
			if((Rp->PosResult&0xFF)==2){
				CauseStr=QString::number(Rp->Cause[1])
						+QString('[')
						+QString::number(L->GetMaster()->TransformPixelToUnit(Rp->Cause[1]),'f',2)
						+QString("mm]");
			}
			else{
				CauseStr=QString::number(Rp->Cause[0])
						+QString('[')
						+QString::number(L->GetMaster()->TransformPixelToUnitSquare(Rp->Cause[0]),'f',2)
						+QString("mm2]");
			}
		}
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(Rp->LibType);
		if(ABase!=NULL){
			QRgb		NGColor;

			ResultPosList	RPos;
			RPos.result		=Rp->PosResult;
			if(Rp->ResultType==_ResultDouble){
				RPos.SetResult(Rp->DoubleCause);
			}
			else
			if(Rp->ResultType==_ResultDWORD){
				RPos.SetResult1(Rp->Cause[0]);
				RPos.SetResult2(Rp->Cause[1]);
			}
			RPos.Px			=Rp->MasterX;
			RPos.Py			=Rp->MasterY;
			RPos.Rx			=Rp->HX;
			RPos.Ry			=Rp->HY;
			ABase->GetDrawResultDetail(NULL ,&RPos ,ItemDetailList);
		}
	}
	else{
		LibName=Rp->Message;
		if(Rp->ResultType==_ResultDouble){
			CauseStr=QString::number(Rp->DoubleCause,'f',2);
		}
	}

	QStringList	Ret;
	if(LibName.isEmpty()==false){
		Ret.append(LibName
					+QString(/**/",")
					+CauseStr);
	}
	else{
		Ret.append(CauseStr);
	}
	Ret.append(L->InspectionTime.toString("hh:mm:ss")
				+QString(/**/" (")
				+QString::number(L->ID)
				+QString(/**/")"));
	if(ItemDetailList.count()>0){
		DetailResultInfoList	*L=ItemDetailList.NPListPack<DetailResultInfoList>::GetFirst();
		Ret.append(L->GetInfoString());
	}

	return Ret;
}