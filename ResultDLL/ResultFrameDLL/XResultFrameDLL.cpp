#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XResultDLL.h"
#include "XGeneralFunc.h"
#include "XMLGeneralFunc.h"
#include <QMessageBox>
#include "XFrameDef.h"
#include "XGeneralStocker.h"
#include "ResultFrameDLL.h"
#include "XLotInformation.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "swap.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"



		
ResultFrameDLL::GroupPacket::GroupPacket(void)
{
	HandleCommon=NULL;
	HandlePage	=NULL;
	HandleRemove=NULL;
	HandleLastID=NULL;
	HandlePiece	=NULL;
	HandleInsLib=NULL;
}

ResultFrameDLL::GroupPacket::~GroupPacket(void)
{
	if(HandleCommon!=NULL){
		delete	HandleCommon;
		HandleCommon=NULL;
	}
	if(HandlePage!=NULL){
		delete	HandlePage;
		HandlePage=NULL;
	}
	if(HandleRemove!=NULL){
		delete	HandleRemove;
		HandleRemove=NULL;
	}
	if(HandleLastID!=NULL){
		delete	HandleLastID;
		HandleLastID=NULL;
	}
	if(HandlePiece!=NULL){
		delete	HandlePiece;
		HandlePiece=NULL;
	}
	if(HandleInsLib!=NULL){
		delete	HandleInsLib;
		HandleInsLib=NULL;
	}
}

//============================================================================

ResultFrameDLL::ResultFrameDLL(LayersBase *Base)
	:XMLServerHandle("localhost",12345,NULL)
	,ResultDLLBaseRoot(Base)
{
	OutputLibData=true;

	FlagCommon	=none3;
	FlagSlave	=none3;
	FixedConnection=false;
	TmpRes		=NULL;

	XMLServerHandle::SetParam(this);
	ResultDLLBaseRoot::SetParam(&IPAddress			, /**/"Access"	,/**/"IPAddress"		,"IP Address for XML Server"	);
	ResultDLLBaseRoot::SetParam(&PortNumber			, /**/"Access"	,/**/"PortNumber"		,"Port number for XML Server"	,0);
	ResultDLLBaseRoot::SetParam(&OutputLibData		, /**/"Data"	,/**/"OutputLibData"	,"if checked, output library data to XML server"	,0);
}


ResultFrameDLL::~ResultFrameDLL(void)
{
}

	
QString	ResultFrameDLL::GetLotID(int GroupNo)
{
	return GetLayersBase()->GetLot(GroupNo)->GetLotID();
}

QString	ResultFrameDLL::GetLotName(int GroupNo)
{
	return GetLayersBase()->GetLot(GroupNo)->GetLotName();
}

int64	ResultFrameDLL::GetInspectionNumber(int GroupNo,int FrameNumber)
{
	return TmpRes->GetInspectionNumber();
}
int		ResultFrameDLL::GetMachineID(void)
{
	return GetLayersBase()->GetMachineID();
}
int		ResultFrameDLL::GetMasterCode(void)
{
	return GetLayersBase()->GetMasterCode();
}
QString	ResultFrameDLL::GetMasterName(void)
{
	return GetLayersBase()->GetMasterName();
}
int64	ResultFrameDLL::GetInspectionID(int GroupNo,int FrameNumber)
{
	return TmpRes->GetInspectionID();
}


bool	ResultFrameDLL::OutputCommon(ResultInspection &Res
									,ResultInspectionForStockPointerContainer &ShadowResStocks)
{
	TmpRes	=&Res;

	for(int GroupNo=0;GroupNo<GroupCount;GroupNo++){
		for(IntClass *v=Group[GroupNo].FrameNumber.GetFirst();v!=NULL;v=v->GetNext()){
			int	FrameNumber=v->GetValue();

			XDateTime QLocal=Res.GetStartTimeForInspection();
			XDateTime QGm=QLocal;
			QString FileMID;
			QString FileLID;
			QString FileTIM;
			char SerchStr[16384];
			strcpy(SerchStr,"<IST DAY=\"");
			strcat(SerchStr,QGm.toString("yyMMddhhmmss").toStdString().c_str());
			strcat(SerchStr,"\" NGJ=\"");
			strcat(SerchStr,CreateNGFileNameForCommon(&Res).toStdString().c_str());
			strcat(SerchStr,"\" MAC=\"");
			char MacID[16];
			sprintf(MacID,"%d",GetMachineID());
			strcat(SerchStr, MacID);

			char GroupStr[16];
			sprintf(GroupStr,"\" Group=\"%d",GroupNo);
			strcat(SerchStr, GroupStr);

			char FrameStr[16];
			sprintf(FrameStr,"\" Frame=\"%d",FrameNumber);
			strcat(SerchStr, FrameStr);

			strcat(SerchStr,"\">");
			//Str2
			strcat(SerchStr,"<TIM>");
			strcat(SerchStr,QGm.toString("yy/MM/dd hh:mm:ss").toStdString().c_str());
			strcat(SerchStr,"</TIM>");
			FileTIM=QGm.toString("hh").toStdString().c_str();
			//Str3
			strcat(SerchStr,"<VSN>20111010</VSN>");

			strcat(SerchStr,"<INM>");
			strcat(SerchStr,QString::number(GetInspectionNumber(GroupNo,FrameNumber)).toStdString().c_str());
			strcat(SerchStr,"</INM>");

			//Str4
			if(GetMasterName().isNull()==false){
				strcat(SerchStr,"<MNM MID=\"");
				char MCode[16];
				sprintf(MCode,"%d",GetMasterCode());
				strcat(SerchStr, MCode);
				strcat(SerchStr,"\">");
				QString StrMas=GetMasterName();
				int		StrMasLen=StrMas.length()*2+1;
				char	*buff;
				char	BuffDim[200];
				if(StrMasLen>=sizeof(BuffDim))
					buff=new char[StrMasLen];
				else
					buff=BuffDim;
				int		n1=::QString2Char(StrMas, buff, StrMasLen);
				strcat(SerchStr, buff);
				if(buff!=BuffDim){
					delete []buff;
				}
				strcat(SerchStr,"</MNM>");
				FileMID=QString::number(GetMasterCode());
			}
			//Str5
				strcat(SerchStr,"<INSPECT EID=\"");
				char InsID[16];
				sprintf(InsID,"%d",(int)GetInspectionID(GroupNo,FrameNumber));
				strcat(SerchStr, InsID);
				strcat(SerchStr, "\"/>");
			//Str6
			QString StrLID;
			QString StrLot;
			if(GetLotID(GroupNo).isNull()==false){
				strcat(SerchStr, "<LOT LID=\"");
				StrLID=GetLotID(GroupNo);
				int	StrLIDLen=StrLID.length()*2+1;
				char	*buff1;
				char	Buff1Dim[200];
				if(StrLIDLen>=sizeof(Buff1Dim))
					buff1=new char[StrLIDLen];	
				else
					buff1=Buff1Dim;
				::QString2Char(StrLID, buff1, StrLIDLen);
				strcat(SerchStr, buff1);
				strcat(SerchStr, "\">");
				if(buff1!=Buff1Dim)
					delete []buff1;

				StrLot=GetLotName(GroupNo);
				int	StrLotLen=StrLot.length()*2+1;
				char	Buff2Dim[200];
				char	*buff2;
				if(StrLotLen>=sizeof(Buff2Dim))
					buff2=new char[StrLotLen];
				else
					buff2=Buff2Dim;
				::QString2Char(StrLot, buff2, StrLotLen);
				strcat(SerchStr, buff2);
				strcat(SerchStr, "</LOT>");
				if(buff2!=Buff2Dim)
					delete []buff2;
				FileLID=StrLID;
			}
			else{
				strcat(SerchStr, "<LOT LID=\"-1\" />");
				FileLID="-1";
			}
			//Str7
			if(Res.GetTimeOutBreak()==true)
				strcat(SerchStr, "<RES>TimeOver</RES>");
			if(Res.GetMaxErrorBreak()==true)
				strcat(SerchStr, "<RES>MaxOver</RES>");
			if(Res.GetOutputCode()==1)
				strcat(SerchStr, "<RES>OK</RES>");
			else if(Res.GetOutputCode()==2)
				strcat(SerchStr, "<RES>NG</RES>");
			//Str8
				strcat(SerchStr, "</IST>");
				strcat(SerchStr, "\0");

			/*
			if(HandleCommon->InsertXML("",SerchStr)==false){
				return false;
			}
			*/
			Res.SetLotID(StrLID);
			Res.SetLotName(StrLot);

			FlagCommon=none3;
			emit	SignalOutputCommon(GroupNo,FrameNumber ,QString(SerchStr));
			while(FlagCommon==none3){
				GSleep(50);
			}
			if(FlagCommon!=true3){
				GSleep(2000);
				FlagCommon=none3;
				emit	SignalOutputCommon(GroupNo,FrameNumber ,QString(SerchStr));
				while(FlagCommon==none3){
					GSleep(50);
				}
				if(FlagCommon!=true3)
					return false;
			}
		}
	}
	return true;
}

bool	ResultFrameDLL::OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
									,int32 MachineID ,const XDateTime &InspectedTime 
									,ResultInspection *Res
									,const QString &LotID,int phase, int localPage)
{
	if(Res->GetResultDLLBase()==NULL){
		return true;
	}
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"FrameDef");
	if(PBase==NULL)
		return false;
	FrameDefInPage	*PPage=dynamic_cast<FrameDefInPage *>(PBase->GetPageData(localPage));
	if(PPage==NULL)
		return false;

	for(int GroupNo=0;GroupNo<GroupCount;GroupNo++){
		for(IntClass *v=Group[GroupNo].FrameNumber.GetFirst();v!=NULL;v=v->GetNext()){
			int	FrameNumber=v->GetValue();

			QByteArray sMsg;
			QStringList	ResList;
			XDateTime QGm=InspectedTime;

			char SerchStr[100];
			strcpy(SerchStr,"<IST DAY=\"");
			strcat(SerchStr,QGm.toString("yyMMddhhmmss").toStdString().c_str());
			strcat(SerchStr,"\" MAC=\"");
			char MacID[16];
			sprintf(MacID,"%d",MachineID);
			strcat(SerchStr, MacID);

			char GroupStr[16];
			sprintf(GroupStr,"\" Group=\"%d",GroupNo);
			strcat(SerchStr, GroupStr);

			char FrameStr[16];
			sprintf(FrameStr,"\" Frame=\"%d",FrameNumber);
			strcat(SerchStr, FrameStr);

			strcat(SerchStr,"\"/>");

			ResList<<QString("<PHASE CODE=\"")+QString::number(phase)+QString("\">");
			ResList<<QString("<Page CODE=\"")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(localPage))+QString("\">");

			CmdOutputResult	Cmd(GetLayersBase());
			Cmd.GroupNumber	=GroupNo;
			Cmd.FrameNumber	=FrameNumber;
			Cmd.Res			=Res;
			Cmd.ResList		=&ResList;
			Cmd.phase		=phase;
			PPage->TransmitDirectly(&Cmd);


			ResList<<QString("</Page>");
			ResList<<QString("</PHASE>");

			QString	IFileName=Res->GetResultDLLBase()->CreateNGFileNameForSlaveWithDrive(localPage,Res);
			QFileInfo	Q(IFileName);
			QString	path=Q.dir().absolutePath();
			QDir	D;
			D.mkpath (path);
			for(int i=0;i<5;i++){
				QFile	F(IFileName);
				if(F.open(QIODevice::WriteOnly)==true){
					if(Res->SaveNGImage(&F,localPage)==true){
						break;
					}
				}
				GSleep(1000+GetLayersBase()->GetGlobalPageFromLocal(localPage)*50);
			}
			QString	ResAllStr;
			for(int i=0; i<ResList.count() ;i++){
				ResAllStr+=ResList[i];
			}

			Group[GroupNo].iLotID=LotID;

			FlagSlave=none3;
			emit	SignalOutputSlave(GroupNo,FrameNumber ,QString(SerchStr),QString(ResAllStr));
			while(FlagSlave==none3){
				GSleep(50);
			}
			if(FlagSlave==true3){
				return true;
			}
			else{
				GSleep(2000);
				GSleep(1000*GetLayersBase()->GetGlobalPageFromLocal(localPage));

				FlagSlave=none3;
				emit	SignalOutputSlave(GroupNo,FrameNumber ,QString(SerchStr),QString(ResAllStr));
				while(FlagSlave==none3){
					GSleep(50);
				}
				if(FlagSlave==true3){
					return true;
				}
				return false;
			}
		}
	}
	return true;
}

void	ResultFrameDLL::SlotOutputCommon(int GroupNo,int FrameNumber ,QString Str)
{
	if(OpenOperation(GroupNo,&Group[GroupNo].HandleCommon)==false){
		FlagCommon=false3;
		return;
	}
	if(Group[GroupNo].HandleCommon->InsertXML(/**/"",Str)==false){
		FlagCommon=false3;
		return;
	}
	FlagCommon=true3;
}

void	ResultFrameDLL::SlotOutputSlave(int GroupNo,int FrameNumber ,QString SearchStr,QString InsData)
{
	if(OpenOperation(GroupNo,&Group[GroupNo].HandlePage)==false){
		FlagSlave=false3;
		return;
	}
	if(Group[GroupNo].HandlePage->InsertXML(SearchStr,InsData)==false){
		FlagSlave=false3;
		return;
	}
	FlagSlave=true3;
}

bool	ResultFrameDLL::RemoveResult(int32 MachineID ,const XDateTime &ResultTime,	int64 InspectionID)
{

//åüçıèåè"<IST DAY="**********" MAC="xx">"
	QString	SearchStr;

	SearchStr	=QString("<IST DAY=\"")
				+ResultTime.toString("yyMMddhhmmss")
				+QString("\" MAC=\"")
				+QString::number(MachineID)
				+QString("\"/>");

	for(int GroupNo=0;GroupNo<GroupCount;GroupNo++){
		QString		RetString;
		if(OpenOperation(GroupNo,&Group[GroupNo].HandleRemove)==false){
			return false;
		}
		if(Group[GroupNo].HandleRemove->SelectFirst("<*/>",SearchStr,/**/"",RetString)==true){
			Group[GroupNo].HandleRemove->DeleteXML();
		}
	}
	return true;
}
bool	ResultFrameDLL::GetLastInspectionID(int MasterID, QString LotID ,int64 &InspectionID)
{
	return false;
}

bool	ResultFrameDLL::OutputInLotChangedSlave(int LocalPage)
{
	FrameDefBase	*Base=(FrameDefBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"FrameDef");
	if(Base!=NULL){
		/*
		if(OpenOperation(&HandlePiece)==false){
			return false;
		}

		NamingInPage	*P=(NamingInPage *)Base->GetPageData(LocalPage);
		for(AlgorithmItemPI	*c=P->GetFirstData();c!=NULL;c=c->GetNext()){
			QStringList	InsertStrings;
			char SerchStr[10240];
			strcpy(SerchStr,"<PCE PIECENAME=\"#");
			strcat(SerchStr,((NamingItem *)c)->GetItemName().toStdString().c_str());
			strcat(SerchStr,"\" PAGE=\"");
			char Buff[10000];
			sprintf(Buff,"%d",GetLayersBase()->GetGlobalPageFromLocal(LocalPage));
			strcat(SerchStr,Buff);
			strcat(SerchStr,"\" AREA=\"");
			FlexArea	*AreaPoint=&c->GetArea();
			if(AreaPoint->GetShape().Kind==BlockShape::_sRectangle){
				sprintf(Buff,"R%d,%d,%d,%d"	,(int)AreaPoint->GetMinX(),(int)AreaPoint->GetMinY()
											,(int)AreaPoint->GetMaxX(),(int)AreaPoint->GetMaxY());
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sEllipse){
				sprintf(Buff,"E%d,%d,%d,%d"	,(int)AreaPoint->GetMinX(),(int)AreaPoint->GetMinY()
											,(int)AreaPoint->GetMaxX(),(int)AreaPoint->GetMaxY());
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sRotEllipse){
				sprintf(Buff,"T%d,%d,%d,%d,%d"	
											,(int)AreaPoint->GetShape().Shape.bsRotEllipse.Cx,(int)AreaPoint->GetShape().Shape.bsRotEllipse.Cy
											,(int)AreaPoint->GetShape().Shape.bsRotEllipse.Rx,(int)AreaPoint->GetShape().Shape.bsRotEllipse.Ry
											,(int)(AreaPoint->GetShape().Shape.bsRotEllipse.Angle*180.0/M_PI));
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

				sprintf(Buff,"P%d,%d,%d,%d,%d,%d,%d,%d"	
											,(int)hX1,(int)hY1
											,(int)hX2,(int)hY2
											,(int)hX3,(int)hY3
											,(int)hX4,(int)hY4);
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
				sprintf(Buff,"R%d,%d,%d,%d,%d,%d,%d,%d"	
									,(int)X11,(int)Y11,(int)X12,(int)Y12
									,(int)X21,(int)Y21,(int)X22,(int)Y22);
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sFree){
				sprintf(Buff,"XX");
			}
			else if(AreaPoint->GetShape().Kind==BlockShape::_sPoly){
				int	Sep=(AreaPoint->GetShape().Shape.bsPoly.PointCount+99)/100;
				sprintf(Buff,"P");
				char	*wp=strchr(Buff,0);
				for(int i=0;i<AreaPoint->GetShape().Shape.bsPoly.PointCount;i+=Sep){
					wp=strchr(wp,0);
					if(i==0){
						sprintf(wp,"%d,%d"	,(int)AreaPoint->GetShape().Shape.bsPoly.XY[i].x
											,(int)AreaPoint->GetShape().Shape.bsPoly.XY[i].y);
					}
					else{
						sprintf(wp,",%d,%d"	,(int)AreaPoint->GetShape().Shape.bsPoly.XY[i].x
											,(int)AreaPoint->GetShape().Shape.bsPoly.XY[i].y);
					}
				}
			}
			strcat(SerchStr,Buff);
			strcat(SerchStr,"\"/>");

			InsertStrings.append(SerchStr);

			if(HandlePiece->InsertXML("",InsertStrings)==false){
				GSleep(2000);
				GSleep(1000*GetLayersBase()->GetGlobalPageFromLocal(LocalPage));
				if(HandlePiece->InsertXML("",InsertStrings)==false){
					return false;
				}
			}
		}
		*/
	}


	if(OutputLibData==true){
		XMLOperationHandle	*pHLib=NULL;
		/*
		if(OpenOperation(&HandleInsLib)==false){
			return false;
		}
		*/
		if(pHLib!=NULL){
			QStringList RetInsertStrings;
			char	BuffStr[1024];
			char	sbuff[256];
			for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				strcpy(BuffStr,"<INSLIB RAL=\"");
				QString	AlgoName	=L->GetDLLRoot()
									+QString(/**/":")
									+L->GetDLLName();
				::QString2Char(AlgoName, sbuff, sizeof(sbuff)-1);
				strcat(BuffStr,sbuff);
				strcat(BuffStr,"\"/>");
				QStringList	RetStoredLibStringList;
				IntList		RetStoredLibList;
				pHLib->Select("<INSLIB LIBCODE/>",BuffStr,/**/"",RetStoredLibStringList);
				for(int i=0;i<RetStoredLibStringList.count();i++){
					int	RetAttrValue;
					if(::GetXMLAttrInt (RetStoredLibStringList[i],"LIBCODE",RetAttrValue)==true){
						RetStoredLibList.Add(RetAttrValue);
					}
				}

				AlgorithmLibraryContainer	*pLib=L->GetLibContainer();
				if(pLib!=NULL){
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
					for(IntClass *s=LibIDList.GetFirst();s!=NULL;s=s->GetNext()){
						if(RetStoredLibList.IsInclude(s->GetValue())==false){
							OutputInLibData(L ,s->GetValue()
											,RetInsertStrings);
						}	
					}
				}
			}
			if(pHLib->InsertXML(/**/"",RetInsertStrings)==false){
				return false;
			}
		}
	}

	return true;
}
bool	ResultFrameDLL::OutputInLib(void)
{
	/*
	if(OpenOperation(&HandleInsLib)==false){
		return false;
	}
	if(OutputLibData==false){
		return true;
	}
	char	BuffStr[1024];
	char	sbuff[256];
	QStringList	InsertStrings;

	strcpy(BuffStr,"<MASTERINFO MASTER=\"");
	sprintf(sbuff,"%d\"/>",GetLayersBase()->GetMasterCode());
	strcat(BuffStr,sbuff);
	InsertStrings.append(BuffStr);

	strcpy(BuffStr,"<LOTINFO LAT=\"");
	sprintf(sbuff,"%d\"/>",GetLayersBase()->GetLot(0)->GetLotAutoCount());
	strcat(BuffStr,sbuff);
	InsertStrings.append(BuffStr);

	if(HandleInsLib->InsertXML("",InsertStrings)==false){
		return false;
	}
	*/
	return true;
}

void	ResultFrameDLL::OutputInLibData(LogicDLL *L ,int LibID
									,QStringList &RetInsertStrings)
{
	char	BuffStr[1024];
	char	sbuff[256];

	AlgorithmBase	*ABase		=L->GetInstance();
	AlgorithmLibraryList	ALibList;
	ABase->GetLibraryContainer()->GetLibraryList(LibID,ALibList);
	LibNGTypeInAlgorithm NGTypeContainer;
	ABase->GetNGTypeContainer(LibID,NGTypeContainer);
	if(NGTypeContainer.IsEmpty()==false){
		for(LibNGTypeItem *NGItem=NGTypeContainer.GetFirst();NGItem!=NULL;NGItem=NGItem->GetNext()){
			strcpy(BuffStr,"<INSLIB RAL=\"");
			QString	AlgoName	=L->GetDLLRoot()
								+QString(/**/":")
								+L->GetDLLName();
			//QString	AlgoName	=pLib->GetLibTypeName();
			::QString2Char(AlgoName, sbuff, sizeof(sbuff)-1);
			strcat(BuffStr,sbuff);
			strcat(BuffStr,"\"");

			strcat(BuffStr," LIBCODE=\"");
			sprintf(sbuff,"%d\"",LibID);
			strcat(BuffStr,sbuff);

			strcat(BuffStr," LIBNAME=\"");
			QString	LibName=ALibList.GetLibName();
			::QString2Char(LibName, sbuff, sizeof(sbuff)-1);
			strcat(BuffStr,sbuff);
			strcat(BuffStr,"\"");

			strcat(BuffStr," TCODE=\"");
			sprintf(sbuff,"%d\"",NGItem->TypeCode);
			strcat(BuffStr,sbuff);
						
			strcat(BuffStr," TNAME=\"");
			QString	TypeName=NGItem->NGName;
			::QString2Char(TypeName, sbuff, sizeof(sbuff)-1);
			strcat(BuffStr,sbuff);
			strcat(BuffStr,"\"");

			strcat(BuffStr," NGCOLOR=\"");
			sprintf(sbuff,"%d,%d,%d\"",NGItem->NGColor.red(),NGItem->NGColor.green(),NGItem->NGColor.blue());
			strcat(BuffStr,sbuff);

			switch(NGItem->NGShape){
				case LibNGTypeItem::NG_Circle:	//Åõ ìhÇËÇ¬Ç‘Ç≥Ç»Ç¢ä€
					strcat(BuffStr," NGSHAPE=\"Circle\"");
					break;
				case LibNGTypeItem::NG_FilledCircle	:	//Åú ìhÇËÇ¬Ç‘ÇµÇΩä€
					strcat(BuffStr," NGSHAPE=\"Filled circle\"");
					break;
				case LibNGTypeItem::NG_Rectangle	:	//Å† ìhÇËÇ¬Ç‘Ç≥Ç»Ç¢éläp
					strcat(BuffStr," NGSHAPE=\"Rectangle\"");
					break;
				case LibNGTypeItem::NG_FilledRect	:	//Å° ìhÇËÇ¬Ç‘ÇµÇΩéläp
					strcat(BuffStr," NGSHAPE=\"Filled Rectangle\"");
					break;
				case LibNGTypeItem::NG_X			:	//Çw ÉoÉbÉeÉì
					strcat(BuffStr," NGSHAPE=\"X\"");
					break;
				case LibNGTypeItem::NG_Star			:	//Åô
					strcat(BuffStr," NGSHAPE=\"Star\"");
					break;
				case LibNGTypeItem::NG_FilledStar	:	//Åö
					strcat(BuffStr," NGSHAPE=\"Filled Star\"");
					break;
				case LibNGTypeItem::NG_Cross		:	//?
					strcat(BuffStr," NGSHAPE=\"Cross\"");
					break;
				case LibNGTypeItem::NG_Sharp		:	//ÅÚ
					strcat(BuffStr," NGSHAPE=\"Sharp\"");
					break;
			}

			if(NGItem->Blink==true){
				strcat(BuffStr," NGBLINK=\"200\"");
			}
			
			strcat(BuffStr," NGPRIORITY=\"");
			sprintf(sbuff,"%d\"",(int)NGItem->Priority);
			strcat(BuffStr,sbuff);
						
			strcat(BuffStr," WAIT=\"");
			sprintf(sbuff,"%d\"",(int)NGItem->NextJumpMilisec);
			strcat(BuffStr,sbuff);

			strcat(BuffStr,"/>");

			RetInsertStrings.append(BuffStr);
			//if(HandleInsLib->InsertXML("",BuffStr)==false){
			//	return false;
			//}
		}
	}
	else{
		strcpy(BuffStr,"<INSLIB RAL=\"");

		QString	AlgoName	=L->GetDLLRoot()
							+QString(/**/":")
							+L->GetDLLName();
		//QString	AlgoName	=pLib->GetLibTypeName();
		::QString2Char(AlgoName, sbuff, sizeof(sbuff)-1);
		strcat(BuffStr,sbuff);
		strcat(BuffStr,"\"");

		strcat(BuffStr," LIBCODE=\"");
		sprintf(sbuff,"%d\"",LibID);
		strcat(BuffStr,sbuff);

		strcat(BuffStr," LIBNAME=\"");
		QString	LibName=ALibList.GetLibName();
		::QString2Char(LibName, sbuff, sizeof(sbuff)-1);
		strcat(BuffStr,sbuff);
		strcat(BuffStr,"\"/>");

		//if(HandleInsLib->InsertXML("",BuffStr)==false){
		//	return false;
		//}
		RetInsertStrings.append(BuffStr);
	}
}

ExeResult	ResultFrameDLL::ExecuteInitialAfterEdit		(int ExeID ,ResultInspection *Res)
{
	ExeResult	Ret=_ER_true;
	if(FixedConnection==false){
		setParent(GetLayersBase()->GetMainWidget());

		if(!connect(this,SIGNAL(SignalOutputCommon(int ,int ,QString)),this,SLOT(SlotOutputCommon(int ,int ,QString)),Qt::QueuedConnection)){
			Ret=_ER_false;
		}
		if(!connect(this,SIGNAL(SignalOutputSlave(int ,int ,QString,QString)),this,SLOT(SlotOutputSlave(int ,int ,QString,QString)),Qt::QueuedConnection)){
			Ret=_ER_false;
		}
		if(Ret==_ER_true){
			FixedConnection=true;
		}
	}

	return Ret;
}
	
bool	ResultFrameDLL::SearchLotID(const QString &iLotID)
{
	QString	TblStr=GetXMLTableName(iLotID);
	bool Ret;
	if(FindTable(TblStr ,Ret)==true){
		return Ret;
	}
	return false;
}
bool	ResultFrameDLL::CheckConnection(void)
{
	if(GetState()==false){
		if(Open()==false){
			return false;
		}
	}
	return true;
}
bool	ResultFrameDLL::OpenOperation(int GroupNo,XMLOperationHandle **Handle)
{
	if(GetState()==false){
		if(Open()==false){
			return false;
		}
	}
	if(*Handle==NULL){
		*Handle=OpenXMLOperation(GetXMLTableName(GroupNo));
	}
	else if((*Handle)->GetTableStr()!=GetXMLTableName(GroupNo)){
		(*Handle)->Close();
		delete	(*Handle);
		(*Handle)=OpenXMLOperation(GetXMLTableName(GroupNo));
	}
	if(*Handle==NULL){
		if(Close()==false){
			return false;
		}
		if(Open()==false){
			return false;
		}
		if(*Handle==NULL){
			*Handle=OpenXMLOperation(GetXMLTableName(GroupNo));
		}
		else if((*Handle)->GetTableStr()!=GetXMLTableName(GroupNo)){
			(*Handle)->Close();
			delete	(*Handle);
			(*Handle)=OpenXMLOperation(GetXMLTableName(GroupNo));
		}
		if(*Handle==NULL){
			return false;
		}
	}
	return true;
}


QString	ResultFrameDLL::GetXMLTableName(int GroupNo)
{
	int		MasterID	=GetLayersBase()->GetMasterCode();
	int		MachineID	=GetLayersBase()->GetMachineID();
	QString	LotID		=Group[GroupNo].iLotID;

	return   QString::number(MachineID)
			+QString("-")
			+QString::number(MasterID)
			+::GetSeparator()
			+LotID;
}


QString	ResultFrameDLL::GetXMLTableName(const QString &iLotID)
{
	int		MasterID	=GetLayersBase()->GetMasterCode();
	int		MachineID	=GetLayersBase()->GetMachineID();
	
	return   QString::number(MachineID)
			+QString("-")
			+QString::number(MasterID)
			+::GetSeparator()
			+iLotID;
}



void	ResultFrameDLL::TransmitDirectly(GUIDirectMessage *packet)
{
	/*
	CmdChangeResultMultiGroupLotInfo	*CmdChangeResultLotInfoVar=dynamic_cast<CmdChangeResultMultiGroupLotInfo *>(packet);
	if(CmdChangeResultLotInfoVar!=NULL){
		for(int i=0;i<GetParamGlobal()->MaxLotGroupCount && i<GroupInfoList.count();i++){
			if(CmdChangeResultLotInfoVar->LotID.count()<=i){
				break;
			}
			if(CmdChangeResultLotInfoVar->LotName.count()<=i){
				break;
			}
			Group[i].iLotID		=CmdChangeResultLotInfoVar->LotID[i];
			Group[i].iLotName	=CmdChangeResultLotInfoVar->LotName[i];
			Group[i].InspectionID=1;
			iRemark		=CmdChangeResultLotInfoVar->Remark;
		}
		return;
	}
	*/
}
