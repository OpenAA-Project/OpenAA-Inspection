/*
 * Copyright (C) 2025
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

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "XResultDLL.h"
#include "XAlgorithmBase.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "ResultWriteCSVBarcodeLine.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XCSV.h"
#include "XLotInformation.h"
#include "XGUIFormBase.h"

ResultWriteCSVBarcodeLine::ResultWriteCSVBarcodeLine(LayersBase *Base)
	:ResultDLLBaseRoot(Base)
{
	OutputPath		="C:\\ResultWriteCSVBarcodeLine";

	ResultDLLBaseRoot::SetParam(&OutputPath		, /**/"Access" ,/**/"OutputPath"		,"Path to Output CSV (Netwrk path from every slaves)");
}
ResultWriteCSVBarcodeLine::~ResultWriteCSVBarcodeLine(void)
{
}
		
QString	ResultWriteCSVBarcodeLine::MakeLockFile(int32 MachineID ,int MasterCode,int Page)
{
	QString	s= OutputPath
				+GetSeparator()
				+QString("Lock-Mac")
				+QString::number(MachineID)
				+QString("-Master")
				+QString::number(MasterCode)
				+QString("-Page")
				+QString::number(Page)
		+QString(".lck");
	return s;
}
		
QString	ResultWriteCSVBarcodeLine::MakeCSVFile(int32 MachineID ,int MasterCode,int Page)
{
	QString	s= OutputPath
				+GetSeparator()
				+QString("Result-Mac")
				+QString::number(MachineID)
				+QString("-Master")
				+QString::number(MasterCode)
				+QString("-Page")
				+QString::number(Page)
		+QString(".csv");
	return s;
}

bool	ResultWriteCSVBarcodeLine::OutputCommon(ResultInspection &Res
									,ResultInspectionForStockPointerContainer &ShadowResStocks)
{
	ForceDirectories(OutputPath);
	return true;
}

void GetBCodeInResult(ResultInItemRoot *Item ,void *Something)
{
	QStringList &BCodeResList = *(QStringList *)Something;
	QString	s=Item->GetResultMessage();
	BCodeResList.append(s);
}

class ResultColorDifferenceInfo : public NPList<ResultColorDifferenceInfo>
{
public:
	int32	ItemID;
	int32	Page;
	int32	Phase;
	double	ResultDeltaE;
	double	ResultDeltaEManual;
	double	ResultDense;
	double	ResultDenseManual;
};

void GetColorDifference(ResultInItemRoot *Item ,void *Something)
{
	NPListPack<ResultColorDifferenceInfo> *ColorDiffList = (NPListPack<ResultColorDifferenceInfo> *)Something;

	ResultColorDifferenceInfo *CDI=new ResultColorDifferenceInfo();
	CDI->ItemID = Item->GetItemID();
	CDI->Page	= Item->GetPage();
	CDI->Phase	= Item->GetPhaseCode();
	for(ResultPosList	*r=Item->GetPosListFirst();r!=NULL;r=r->GetNext()){
		if(r->result==0x10100){
			CDI->ResultDeltaE=r->GetResultDouble();
		}
		if(r->result==0x10002){
			CDI->ResultDense=r->GetResultDouble();
		}
		if(r->result==0x10110){
			CDI->ResultDeltaEManual=r->GetResultDouble();
		}
		if(r->result==0x10012){
			CDI->ResultDenseManual=r->GetResultDouble();
		}
	}
	ColorDiffList->AppendList(CDI);
}
	
bool	ResultWriteCSVBarcodeLine::OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
									,int32 MachineID ,const XDateTime &InspectedTime 
									,ResultInspection *Res 
									,const QString &LotID,int phase, int localPage)
{
	QStringList	BCodeResList;
	for(ResultBaseForAlgorithmRoot *B=Res->GetResultBaseDimFirst();B!=NULL;B=B->GetNext()){
		QString		DLLRoot,DLLName;
		B->GetAlgorithm(DLLRoot,DLLName);
		if(DLLRoot==/**/"Basic" && DLLName==/**/"BCRInspection"){
			ResultBasePhase		*RPh=B->GetPageDataPhase(phase);
			ResultInPageRoot	*R=RPh->GetPageData(localPage);
			R->ExecuteInAllItems(GetBCodeInResult,&BCodeResList);
		}
	}

	NPListPack<ResultColorDifferenceInfo> ColorDiffList;
	for(ResultBaseForAlgorithmRoot *B=Res->GetResultBaseDimFirst();B!=NULL;B=B->GetNext()){
		QString		DLLRoot,DLLName;
		B->GetAlgorithm(DLLRoot,DLLName);
		if(DLLRoot==/**/"Basic" && DLLName==/**/"ColorDifference"){
			ResultBasePhase		*RPh=B->GetPageDataPhase(phase);
			ResultInPageRoot	*R=RPh->GetPageData(localPage);
			R->ExecuteInAllItems(GetColorDifference,&ColorDiffList);
		}
	}


	QString	LockFileName=MakeLockFile(MachineID ,GetLayersBase()->GetMasterCode(),localPage);
	QFile	LockFile(LockFileName);
	LoopAgain:;
	while(LockFile.exists()==true){
		GSleep(500);
	}
	if(LockFile.open(QIODevice::ReadWrite)==true){
		GSleep(200*GetLayersBase()->GetGlobalPageFromLocal(localPage));
		char	data[1];
		if(LockFile.read(data,1)==1){
			LockFile.close();
			goto	LoopAgain;
		}
		LockFile.write("0");
	}
	LockFile.close();
	QString	CSVFileName=MakeCSVFile(MachineID ,GetLayersBase()->GetMasterCode(),localPage);
	QFile	CSVFile(CSVFileName);
	if(CSVFile.open(QIODevice::ReadWrite)==false){
		LockFile.remove();
		return false;
	}
	QStringListListCSV	CSV;

	CSV.LoadFromCSVFile(&CSVFile);

	int	RowN = CSV.GetRowCount();
	//if(RowN>0){
	//	QString	s=CSV.Get(0, RowN-1);
	//	bool	ok;
	//	int	InspectionID = s.toInt(&ok);
	//	if(ok==true && InspectionID!=Res->GetInspectionID()){
	//		RowN=RowN-1;
	//	}
	//}
	if(RowN==0){
		CSV.Set(0,RowN,/**/"InspectionID");
		int	Column=1;
		for(int i=0;i<BCodeResList.count();i++){
			CSV.Set(Column,RowN,/**/"Barcode");
			Column++;
		}
		for(ResultColorDifferenceInfo *r=ColorDiffList.GetFirst();r!=NULL;r=r->GetNext()){
			ResultBaseForAlgorithmRoot *B = Res->GetResultBaseForAlgorithm(/**/"Basic",/**/"ColorDifference");
			ResultBasePhase *Rh = B->GetPageDataPhase(r->Phase);
			ResultInItemRoot *RItem = Rh->GetPageData(r->Page)->FindResultInItem(0,r->ItemID);
			AlgorithmItemRoot *Item = RItem->GetAlgorithmItem();
			QString ItemName =Item ->GetItemName();
			if(ItemName.isEmpty()==true){
				ItemName = QString("ItemID%1").arg(r->ItemID);
			}
			CSV.Set(Column,RowN,ItemName+QString(/**/"-DeltaE"));
			Column++;
			CSV.Set(Column,RowN,ItemName+QString(/**/"-DeltaEM"));
			Column++;
			CSV.Set(Column,RowN,ItemName+QString(/**/"-Dense"));
			Column++;
			CSV.Set(Column,RowN,ItemName+QString(/**/"-DenseM"));
			Column++;
		}
		RowN++;
	}
	CSV.Set(0,RowN,QString::number(Res->GetInspectionID()));
	{
		int	Column=1;
		for(int i=0;i<BCodeResList.count();i++){
			CSV.Set(Column,RowN,BCodeResList[i]);
			Column++;
		}
		for(ResultColorDifferenceInfo *r=ColorDiffList.GetFirst();r!=NULL;r=r->GetNext()){
			ResultBaseForAlgorithmRoot *B = Res->GetResultBaseForAlgorithm(/**/"Basic",/**/"ColorDifference");
			ResultBasePhase *Rh = B->GetPageDataPhase(r->Phase);
			ResultInItemRoot *RItem = Rh->GetPageData(r->Page)->FindResultInItem(0,r->ItemID);
			AlgorithmItemRoot *Item = RItem->GetAlgorithmItem();
			QString ItemName =Item ->GetItemName();
			if(ItemName.isEmpty()==true){
				ItemName = QString("ItemID%1").arg(r->ItemID);
			}
			CSV.Set(Column,RowN,QString::number(r->ResultDeltaE,'f',2));
			Column++;
			CSV.Set(Column,RowN,QString::number(r->ResultDeltaEManual,'f',2));
			Column++;
			CSV.Set(Column,RowN,QString::number(r->ResultDense,'f',2));
			Column++;
			CSV.Set(Column,RowN,QString::number(r->ResultDenseManual,'f',2));
			Column++;
		}
	}
	CSVFile.seek(0);
	CSV.SaveFromCSVFile(&CSVFile);

	CSVFile.close();
	LockFile.remove();
	return true;
}
bool	ResultWriteCSVBarcodeLine::RemoveResult(int32 MachineID ,const XDateTime &ResultTime,	int64 InspectionID)
{
	return true;
}