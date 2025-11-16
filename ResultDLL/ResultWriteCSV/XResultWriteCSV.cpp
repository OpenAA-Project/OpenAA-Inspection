#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "XResultDLL.h"
#include "XAlgorithmBase.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "ResultWriteCSV.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XCSV.h"
#include "XLotInformation.h"
#include "ShowMatrixImageCenter.h"
#include "XGUIFormBase.h"

ResultWriteCSV::ResultWriteCSV(LayersBase *Base)
	:ResultDLLBaseRoot(Base)
{
	OutputPath		="C:\\RegulusResultCSV";

	ResultDLLBaseRoot::SetParam(&OutputPath		, /**/"Access" ,/**/"OutputPath"		,"Path to Output CSV (Netwrk path from every slaves)");
}
ResultWriteCSV::~ResultWriteCSV(void)
{
}
		
QString	ResultWriteCSV::MakeLockFile(int32 MachineID ,int MasterCode ,const XDateTime &InspectedTime)
{
	QString	s= OutputPath
				+GetSeparator()
				+QString("Lock-Mac")
				+QString::number(MachineID)
				+QString("-Master")
				+QString::number(MasterCode)
				+QString("-")
				+InspectedTime.toString("yyMMdd-hhmmss")
				+QString(".lck");
	return s;
}
		
QString	ResultWriteCSV::MakeCSVFile(int32 MachineID ,int MasterCode ,const XDateTime &InspectedTime)
{
	QString	s= OutputPath
				+GetSeparator()
				+QString("Result-Mac")
				+QString::number(MachineID)
				+QString("-Master")
				+QString::number(MasterCode)
				+QString("-")
				+InspectedTime.toString("yyMMdd-hhmmss")
				+QString(".csv");
	return s;
}

bool	ResultWriteCSV::OutputCommon(ResultInspection &Res
									,ResultInspectionForStockPointerContainer &ShadowResStocks)
{
	ForceDirectories(OutputPath);
	QString	LockFileName=MakeLockFile(GetLayersBase()->GetMachineID() ,GetLayersBase()->GetMasterCode(),Res.GetStartTimeForInspection());
	QFile	LockFile(LockFileName);
	if(LockFile.open(QIODevice::WriteOnly)==true){
		LockFile.write("0");
	}
	LockFile.close();

	QString	CSVFileName=MakeCSVFile(GetLayersBase()->GetMachineID() ,GetLayersBase()->GetMasterCode(),Res.GetStartTimeForInspection());
	QFile	CSVFile(CSVFileName);
	if(CSVFile.open(QIODevice::WriteOnly)==false){
		LockFile.remove();
		return false;
	}

	QStringListListCSV	CSV;

	QStringList	List1;
	QStringList	List2;
	List1.append("MasterCode");
	List1.append("Lot ID");
	List1.append("Lot Name");
	List1.append("InspectionID");
	List1.append(" ");
	List1.append("X");
	List1.append("Y");
	List2.append(QString::number(GetLayersBase()->GetMasterCode()));
	List2.append(GetLayersBase()->GetLotBase()->GetLotID());
	List2.append(GetLayersBase()->GetLotBase()->GetLotName());
	List2.append(QString::number(Res.GetInspectionID()));
	List2.append(" ");
	List2.append(" ");
	List2.append(" ");
	CSV.append(List1);
	CSV.append(List2);

	CSV.SaveFromCSVFile(&CSVFile);
	CSVFile.close();
	LockFile.remove();
	return true;
}
	
bool	ResultWriteCSV::OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
									,int32 MachineID ,const XDateTime &InspectedTime 
									,ResultInspection *Res 
									,const QString &LotID,int phase, int localPage)
{
	QStringList	ResList;
	for(ResultBaseForAlgorithmRoot *B=Res->GetResultBaseDimFirst();B!=NULL;B=B->GetNext()){
		ResultBasePhase		*RPh=B->GetPageDataPhase(phase);
		ResultInPageRoot	*R=RPh->GetPageData(localPage);
		R->OutputResult(Res->GetLayersBase()->GetGlobalPageFromLocal(localPage) ,B->GetLogicDLL(), ResList);
	}
	CmdReqCenterInImage	RCmd(GetLayersBase());
	GUIFormBase	*G=GetLayersBase()->FindByName("ETC" ,"ShowMatrixImageCenter" ,"");
	if(G!=NULL){
		G->TransmitDirectly(&RCmd);
	}

	XYData	*XP=GetLayersBase()->GetGlobalOutlineOffset(GetLayersBase()->GetGlobalPageFromLocal(localPage));
	QStringListListCSV	CSV;
	int	N=ResList.count();
	for(int i=0;i<N;i++){
		QString	s=ResList[i];
		QStringList	L=s.split(QRegularExpression("[=\"\\t\\s<>]"));
		int	XPos=99999999;
		int	YPos=99999999;
		for(int j=0;j<L.count();j++){
			if(L[j]==QString("X")){
				XPos=L[j+2].toInt();
			}
			if(L[j]==QString("Y")){
				YPos=L[j+2].toInt();
			}
		}
		if(XPos!=99999999 && YPos!=99999999){
			double	X=(double)(XPos+XP->x-RCmd.x)*(double)GetParamGlobal()->ResolutionXNano/1000000.0;
			double	Y=(double)(YPos+XP->y-RCmd.y)*(double)GetParamGlobal()->ResolutionYNano/1000000.0;
			QStringList	RList;
			RList.append(" ");
			RList.append(" ");
			RList.append(" ");
			RList.append(" ");
			RList.append(" ");
			RList.append(QString::number(X));
			RList.append(QString::number(Y));
			CSV.append(RList);
		}
	}


	QString	LockFileName=MakeLockFile(MachineID ,GetLayersBase()->GetMasterCode(),InspectedTime);
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
	QString	CSVFileName=MakeCSVFile(MachineID ,GetLayersBase()->GetMasterCode(),InspectedTime);
	QFile	CSVFile(CSVFileName);
	if(CSVFile.open(QIODevice::Append)==false){
		LockFile.remove();
		return false;
	}

	CSV.SaveFromCSVFile(&CSVFile);
	CSVFile.close();
	LockFile.remove();
	return true;
}
bool	ResultWriteCSV::RemoveResult(int32 MachineID ,const XDateTime &ResultTime,	int64 InspectionID)
{
	QString	CSVFileName=MakeCSVFile(MachineID ,GetLayersBase()->GetMasterCode(),ResultTime);
	QFile	CSVFile(CSVFileName);
	CSVFile.remove();
	return true;
}