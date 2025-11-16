#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "XAlgorithmBase.h"
#include "XResultDLL.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "XNaming.h"
#include "XPieceForReview.h"
#include "XGeneralStocker.h"
#include "ResultXMLForPiece.h"
#include "XLotInformation.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "swap.h"

ResultXMLForPiece::ResultXMLForPiece(LayersBase *Base)
:ResultDLLBaseRoot(Base),XMLServerHandle("localhost",12345,NULL)
{
	HandleCommon=NULL;
	HandlePage	=NULL;
	HandleRemove=NULL;
	HandleLastID=NULL;
	HandlePiece	=NULL;
	HandleInsLib=NULL;
	OutputLibData=true;


	XMLServerHandle::SetParam(this);
	ResultDLLBaseRoot::SetParam(&IPAddress		, /**/"Access" ,/**/"IPAddress"		,"IP Address for XML Server"	);
	ResultDLLBaseRoot::SetParam(&PortNumber		, /**/"Access" ,/**/"PortNumber"	,"Port number for XML Server"	,0);
	ResultDLLBaseRoot::SetParam(&OutputLibData	, /**/"Data"	,/**/"OutputLibData","if checked, output library data to XML server"	,0);
}

ResultXMLForPiece::~ResultXMLForPiece(void)
{
}

bool	ResultXMLForPiece::OutputCommon(ResultInspection &Res
									,ResultInspectionForStockPointerContainer &ShadowResStocks)
{
	if(OpenOperation(&HandleCommon)==false){
		return false;
	}
	PieceForReviewBase	*ABase=(PieceForReviewBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PieceForReview");

	for(IntClass *ItemCount=ABase->AreaNumberList.GetFirst();ItemCount!=NULL;ItemCount=ItemCount->GetNext()){

		XDateTime QLocal=Res.GetStartTimeForInspection();
		XDateTime QGm=QLocal;
		QString FileMID;
		QString FileLID;
		QString FileTIM;
		char SerchStr[8192];
		strcpy(SerchStr,"<IST DAY=\"");
		strcat(SerchStr,QGm.toString("yyMMddhhmmss").toStdString().c_str());
		strcat(SerchStr,"\" NGJ=\"");
		strcat(SerchStr,CreateNGFileNameForCommon(&Res).toStdString().c_str());
		strcat(SerchStr,"\" MAC=\"");
		char MacID[16];
		sprintf(MacID,"%d",GetLayersBase()->GetMachineID());
		strcat(SerchStr, MacID);

		strcat(SerchStr, "\" SID=\"");
		sprintf(MacID,"%d",(int)ItemCount->GetValue());
		strcat(SerchStr, MacID);

		strcat(SerchStr,"\">");
		//Str2
		strcat(SerchStr,"<TIM>");
		strcat(SerchStr,QGm.toString("yy/MM/dd hh:mm:ss").toStdString().c_str());
		strcat(SerchStr,"</TIM>");
		FileTIM=QGm.toString("hh").toStdString().c_str();
		//Str3
		strcat(SerchStr,"<VSN>20111010</VSN>");

		strcat(SerchStr,"<INM>");
		strcat(SerchStr,QString::number(Res.GetInspectionNumber()).toStdString().c_str());
		strcat(SerchStr,"</INM>");

		//Str4
		if(GetLayersBase()->GetMasterName().isNull()==false){
			strcat(SerchStr,"<MNM MID=\"");
			char MCode[16];
			sprintf(MCode,"%d",GetLayersBase()->GetMasterCode());
			strcat(SerchStr, MCode);
			strcat(SerchStr,"\">");
			QString StrMas=GetLayersBase()->GetMasterName();
			char	*buff=new char[StrMas.length()*2+1];
			int		n1=::QString2Char(StrMas, buff, StrMas.length()*2+1);
			strcat(SerchStr, buff);
			delete []buff;
			strcat(SerchStr,"</MNM>");
			FileMID=QString::number(GetLayersBase()->GetMasterCode());
		}
		//Str5
			strcat(SerchStr,"<INSPECT EID=\"");
			char InsID[16];
			sprintf(InsID,"%d",(int)Res.GetInspectionID());
			strcat(SerchStr, InsID);
			strcat(SerchStr, "\" SID=\"");
			sprintf(InsID,"%d",(int)ItemCount->GetValue());
			strcat(SerchStr, InsID);
			strcat(SerchStr, "\"/>");
		//Str6
		if(GetLayersBase()->GetLot(0)->GetLotID()!=0){
			strcat(SerchStr, "<LOT LID=\"");
			QString StrLID=GetLayersBase()->GetLot(0)->GetLotID();
			char	*buff1=new char[StrLID.length()*2+1];
			int		n1=::QString2Char(StrLID, buff1, StrLID.length()*2+1);
			strcat(SerchStr, buff1);
			strcat(SerchStr, "\">");
			delete []buff1;
			QString StrLot=GetLayersBase()->GetLot(0)->GetLotName();
			char	*buff2=new char[StrLot.length()*2+1];
			int		n2=::QString2Char(StrLot, buff2, StrLot.length()*2+1);
			strcat(SerchStr, buff2);
			strcat(SerchStr, "</LOT>");
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

		if(HandleCommon->InsertXML(/**/"",SerchStr)==false){
			return false;
		}
	}
	return true;
}

QString	ResultXMLForPiece::CreateNGFileNameForSlaveWithDrive(int localPage ,ResultInspection *Res ,int PieceAreaID)
{
	XDateTime	nowTm=Res->GetStartTimeForInspection();
	QString	ret=nowTm.toString (/**/"yyMMdd-hh")
				+GetSeparator() 
				+nowTm.toString (/**/"mmss")
				+QString(/**/"-")
				+QString::number(Res->GetLayersBase()->GetGlobalPageFromLocal(localPage))
				+QString(/**/"-PCE")
				+QString::number(PieceAreaID)
				+QString(/**/".jdt");
	QString	LStr;
	if(PathNGImage.right(1)==QString(/**/"\\") || PathNGImage.right(1)==::GetSeparator()){
		LStr=PathNGImage+ret;
	}
	else{
		LStr=PathNGImage+GetSeparator()+ret;
	}

	return LStr;
}


bool	ResultXMLForPiece::OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
										,int32 MachineID ,const XDateTime &InspectedTime 
										,ResultInspection *Res 
										,const QString &LotID,int phase, int localPage)
{
	if(Res->GetResultDLLBase()==NULL){
		return true;
	}
	if(OpenOperation(&HandlePage)==false){
		return false;
	}

	PieceForReviewInPage	*P=NULL;
	PieceForReviewBase	*Base=(PieceForReviewBase *)(GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PieceForReview"));
	if(Base!=NULL){
		AlgorithmInPageInOnePhase	*PPhase=Base->GetPageDataPhase(phase);
		if(PPhase!=NULL){
			P=(PieceForReviewInPage *)PPhase->GetPageData(localPage);
		}
	}

	for(AlgorithmItemPI	*m=P->GetFirstData();m!=NULL;m=m->GetNext()){
		PieceForReviewItem	*Am=(PieceForReviewItem *)m;

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
		strcat(SerchStr, "\" SID=\"");
		sprintf(MacID,"%d",(int)Am->AreaNumber);
		strcat(SerchStr, MacID);
		strcat(SerchStr,"\"/>");

		QVariantList ReturnValue;
		QVariantList ArgValue;
		if(localPage==0){
			if(GetLayersBase()->GetGeneralStocker()->GetData("ResultRemarkSlave",ReturnValue,ArgValue)==true){
				ResList<<ReturnValue[0].toString();
			}
		}
		ResList<<QString("<PHASE CODE=\"")+QString::number(phase)+QString("\">");
		ResList<<QString("<Page CODE=\"")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(localPage))+QString("\">");

		for(ResultBaseForAlgorithmRoot *B=Res->GetResultBaseDimFirst();B!=NULL;B=B->GetNext()){
			ResultBasePhase		*RPh=B->GetPageDataPhase(phase);
			ResultInPageRoot	*R=RPh->GetPageData(localPage);
			R->OutputResult( Am->GetArea()
							,-Am->GetArea().GetMaxX(),-Am->GetArea().GetMaxY()
							,Res->GetLayersBase()->GetGlobalPageFromLocal(localPage)
							,B->GetLogicDLL(), ResList);
		}
		NGImageContainerInPhase	*NGPhase=Res->GetNGImageInPhase(phase);
		if(NGPhase!=NULL){
			if(NGPhase->GetNGImageInPage(localPage)!=NULL){
				for(NGImage *m=NGPhase->GetNGImageInPage(localPage)->GetNGImageDataFirst();m!=NULL;m=m->GetNext()){
					int	Cx,Cy;
					int mx1,my1,mx2,my2;
					m->GetXY(mx1,my1,mx2,my2);
					Cx=(mx1+mx2)/2;
					Cy=(my1+my2)/2;
					if(Am->GetArea().IsInclude(Cx,Cy)==true){
						ResList<<QString("<NGI X=\"")
								+QString::number(mx1-Am->GetArea().GetMaxX())
								+QString("\" Y=\"")
								+QString::number(my1-Am->GetArea().GetMaxY())
								+QString("\" W=\"")
								+QString::number(m->GetWidth())
								+QString("\" H=\"")
								+QString::number(m->GetHeight())
								+QString("\" IDX=\"")
								+QString::number(Res->GetLayersBase()->GetGlobalPageFromLocal(localPage))
								+QString("\" Index=\"")
								+QString::number(m->GetNumber())
								+QString("\"/>");
					}
				}
			}
		}
		ResList<<QString("</Page>");
		ResList<<QString("</PHASE>");

		//QString	IFileName=Res->GetResultDLLBase()->CreateNGFileNameForSlaveWithDrive(localPage,Res);
		QString	IFileName=CreateNGFileNameForSlaveWithDrive(localPage,Res,Am->AreaNumber);
		QFileInfo	Q(IFileName);
		QString	path=Q.dir().absolutePath();
		QDir	D;
		D.mkpath (path);
		QFile	F(IFileName);
		if(F.open(QIODevice::WriteOnly)==true){
			Res->SaveNGImage(Am->GetArea()
							,-Am->GetArea().GetMaxX(),-Am->GetArea().GetMaxY()
							,&F,localPage);
		}
		QString	ResAllStr;
		for(int i=0; i<ResList.count() ;i++){
			ResAllStr+=ResList[i];
		}
		if(HandlePage->InsertXML(SerchStr,ResAllStr)==false){
			return false;
		}
		/*
		for(int i=0; i<ResList.count() ;i++){
			if(HandlePage->InsertXML(SerchStr,ResList[i])==false){
				return false;
			}
			GSleep(100);
		}
		*/
	}
	return true;
}

bool	ResultXMLForPiece::RemoveResult(int32 MachineID ,const XDateTime &ResultTime,	int64 InspectionID)
{
	if(OpenOperation(&HandleRemove)==false){
		return false;
	}

//åüçıèåè"<IST DAY="**********" MAC="xx">"
	QString	SearchStr;

	SearchStr	=QString("<IST DAY=\"")
				+ResultTime.toString("yyMMddhhmmss")
				+QString("\" MAC=\"")
				+QString::number(MachineID)
				+QString("\"/>");

	QString		RetString;
	if(HandleRemove->SelectFirst("<*/>",SearchStr,/**/"",RetString)==false){
		return false;
	}
	if(HandleRemove->DeleteXML()==false){
		return false;
	}
	return true;
}
bool	ResultXMLForPiece::GetLastInspectionID(int MasterID, QString LotID ,int64 &InspectionID)
{
	if(OpenOperation(&HandleLastID)==false){
		return false;
	}

	QString RetString;
	if(HandleLastID->SelectLast	("<IST DAY EID/>","<*/>","ASC EID",RetString)==false){
		return false;
	}
	int	n=RetString.indexOf ("EID");
	if(n>=0){
		QString	EIDStr=RetString.mid(n+5);
		int	n2=EIDStr.indexOf ('\"');
		if(n2>=0){
			QString	EIDNumber=EIDStr=RetString.left(n2);
			bool	ok;
			InspectionID=EIDNumber.toInt(&ok);
			if(ok==true){
				return true;
			}
		}
	}
	return false;
}
bool	ResultXMLForPiece::SearchLotID(const QString &iLotID)
{
	QString	TblStr=GetXMLTableName(iLotID);
	bool Ret;
	if(FindTable(TblStr ,Ret)==true){
		return Ret;
	}
	return false;
}
bool	ResultXMLForPiece::OutputInLotChangedSlave(int LocalPage)
{
	NamingBase	*Base=(NamingBase *)(GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Naming"));
	if(Base!=NULL){
		if(OpenOperation(&HandlePiece)==false){
			return false;
		}

		QStringList	InsertStrings;
		NamingInPage	*P=(NamingInPage *)Base->GetPageData(LocalPage);
		for(AlgorithmItemPI	*c=P->GetFirstData();c!=NULL;c=c->GetNext()){
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
		}

		if(HandlePiece->InsertXML(/**/"",InsertStrings)==false){
			return false;
		}
	}
	return true;
}
bool	ResultXMLForPiece::OutputInLib(void)
{
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

	if(HandleInsLib->InsertXML(/**/"",InsertStrings)==false){
		return false;
	}
	return true;
}

void	ResultXMLForPiece::OutputInLibData(LogicDLL *L ,int LibID
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
				case LibNGTypeItem::NG_Cross		:	//Å{
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


bool	ResultXMLForPiece::OpenOperation(XMLOperationHandle **Handle)
{
	if(GetState()==false){
		if(Open()==false){
			return false;
		}
	}
	if(*Handle==NULL){
		*Handle=OpenXMLOperation(GetXMLTableName());
	}
	else if((*Handle)->GetTableStr()!=GetXMLTableName()){
		(*Handle)->Close();
		delete	(*Handle);
		(*Handle)=OpenXMLOperation(GetXMLTableName());
	}
	if(*Handle==NULL){
		if(Close()==false){
			return false;
		}
		if(Open()==false){
			return false;
		}
		if(*Handle==NULL){
			*Handle=OpenXMLOperation(GetXMLTableName());
		}
		else if((*Handle)->GetTableStr()!=GetXMLTableName()){
			(*Handle)->Close();
			delete	(*Handle);
			(*Handle)=OpenXMLOperation(GetXMLTableName());
		}
		if(*Handle==NULL){
			return false;
		}
	}
	return true;
}


QString	ResultXMLForPiece::GetXMLTableName(void)
{
	int		MasterID	=GetLayersBase()->GetMasterCode();
	int		MachineID	=GetLayersBase()->GetMachineID();
	QString	LotID		=GetLayersBase()->GetLot(0)->GetLotID();

	return   QString::number(MachineID)
			+QString("-")
			+QString::number(MasterID)
			+::GetSeparator()
			+LotID;
}
QString	ResultXMLForPiece::GetXMLTableName(const QString &iLotID)
{
	int		MasterID	=GetLayersBase()->GetMasterCode();
	int		MachineID	=GetLayersBase()->GetMachineID();
	
	return   QString::number(MachineID)
			+QString("-")
			+QString::number(MasterID)
			+::GetSeparator()
			+iLotID;
}