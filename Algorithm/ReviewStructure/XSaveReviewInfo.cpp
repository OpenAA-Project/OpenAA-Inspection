#include "XReviewStructure.h"
#include "XCSV.h"

ForSaveTotalLot::ForSaveTotalLot(void)
{
	MasterIDTop	=-1;
	MasterIDBack=-1;
	CurrentRow	=-1;
	FocusPoint	=NULL;
	ReviewWorkerID	=-1;

	CountOK	=0;
	CountNG	=0;
	CountHalt	=0;

	NGCountTop	=0;
	NGCountBack	=0;

}

bool	ForSaveTotalLot::SaveCSV(const QString &FileName ,ReviewPIBase *Parent)
{
	QStringListListCSV	CSV;

	CSV.Set(0,0,"Master Code Top");
	CSV.Set(1,0,QString::number(MasterIDTop));
	CSV.Set(0,1,"Master Name Top");
	CSV.Set(1,1,MasterNameTop);
	CSV.Set(0,2,"Lot ID Top");
	CSV.Set(1,2,LotTableNameTop);
	CSV.Set(0,3,"Lot Name Top");
	CSV.Set(1,3,LotNameTop);
	CSV.Set(0,4,"Reviewer ID");
	CSV.Set(1,4,QString::number(ReviewWorkerID));
	CSV.Set(0,5,"Reviewer Name");
	CSV.Set(1,5,ReviewWorkerName);

	int	Line=6;
	if(MasterIDBack>=0){
		CSV.Set(0,Line+0,"Master Code Back");
		CSV.Set(1,Line+0,QString::number(MasterIDBack));
		CSV.Set(0,Line+1,"Master Name Back");
		CSV.Set(1,Line+1,MasterNameBack);
		CSV.Set(0,Line+2,"Lot ID Back");
		CSV.Set(1,Line+2,LotTableNameBack);
		CSV.Set(0,Line+3,"Lot Name Back");
		CSV.Set(1,Line+3,LotNameBack);
		Line+=4;
	}
	CSV.Set(0,Line,"");
	Line++;

	CSV.Set(0,Line,"ID");
	CSV.Set(1,Line,"Line");
	CSV.Set(2,Line,"InspectionTime");
	CSV.Set(3,Line,"EnteredTime");
	CSV.Set(4,Line,"Halt");
	CSV.Set(5,Line,"NG Line");
	CSV.Set(6,Line,"Side");
	CSV.Set(7,Line,"EnteredTime");
	CSV.Set(8,Line,"LeavingTime");
	CSV.Set(9,Line,"Key");
	CSV.Set(10,Line,"PosX");
	CSV.Set(11,Line,"PosY");
	CSV.Set(12,Line,"Cause");
	Line++;
	for(ForSaveOneInspection *a=HistryList.GetFirst();a!=NULL;a=a->GetNext()){
		CSV.Set(0,Line,QString::number(a->InspectionID));
		CSV.Set(1,Line,QString::number(a->LineNumber));
		CSV.Set(2,Line,a->InspectionTime.toString("yy/MM/dd hh:mm:ss"));
		CSV.Set(3,Line,a->Entering		.toString("yy/MM/dd hh:mm:ss"));
		CSV.Set(4,Line,QString::number(a->Halt));
		if(a->NGList.IsEmpty()==false){
			for(ForSaveNGPoint *c=a->NGList.GetFirst();c!=NULL;c=c->GetNext()){
				CSV.Set(5 ,Line,QString::number(c->LineNumber));
				CSV.Set(6 ,Line,QString::number(c->Side));
				CSV.Set(7 ,Line,c->Entering.toString("hh:mm:ss"));
				CSV.Set(8 ,Line,c->Leaving.toString("hh:mm:ss"));
				switch(c->FnKeyNumber){
					case -2:
						CSV.Set(9 ,Line,QString("Not"));	break;
					case -1:
						CSV.Set(9 ,Line,QString("Viewed"));	break;
					case 0:
						CSV.Set(9 ,Line,QString("F1"));		break;
					case 1:
						CSV.Set(9 ,Line,QString("F2"));		break;
					case 2:
						CSV.Set(9 ,Line,QString("F3"));		break;
					case 3:
						CSV.Set(9 ,Line,QString("F4"));		break;
					case 4:
						CSV.Set(9 ,Line,QString("F5"));		break;
					case 5:
						CSV.Set(9 ,Line,QString("F6"));		break;
					case 6:
						CSV.Set(9 ,Line,QString("F7"));		break;
					case 7:
						CSV.Set(9 ,Line,QString("F8"));		break;
					case 8:
						CSV.Set(9 ,Line,QString("F9"));		break;
					case 9:
						CSV.Set(9 ,Line,QString("F10"));	break;
					case 10:
						CSV.Set(9 ,Line,QString("F11"));	break;
					case 11:
						CSV.Set(9 ,Line,QString("F12"));	break;
					default:
						CSV.Set(9 ,Line,QString(""));		break;
				}

				int	CSVOffsetX=0;
				int	CSVOffsetY=0;
				if(Parent!=NULL){
					CSVOffsetX=Parent->getProperty().CSVOffsetX;
					CSVOffsetY=Parent->getProperty().CSVOffsetY;
				}
				int	XPos=(c->Position.x()+CSVOffsetX)*Parent->getProperty().CSVMagnificationX;
				int	YPos=(c->Position.y()+CSVOffsetY)*Parent->getProperty().CSVMagnificationY;
				if(Parent->getProperty().CSVReverseX==true){
					XPos=-XPos;
				}
				if(Parent->getProperty().CSVReverseY==true){
					YPos=-YPos;
				}

				if(Parent!=NULL && Parent->getProperty().CSVUnitMM==true){
					ParamGlobal	*G=Parent->GetParamGlobal();
					int		SmallNumberFigure=G->SmallNumberFigure;
					CSV.Set(10,Line,QString::number(G->TransformPixelToUnit(c->Side,XPos),'f',SmallNumberFigure));
					CSV.Set(11,Line,QString::number(G->TransformPixelToUnit(c->Side,YPos),'f',SmallNumberFigure));
				}
				else{
					CSV.Set(10,Line,QString::number(XPos));
					CSV.Set(11,Line,QString::number(YPos));
				}
				CSV.Set(12,Line,c->Cause);
				Line++;
			}
		}
		else{
			Line++;
		}
	}
	CSV.Set(0,Line,"");
	Line++;
	CSV.Set(0,Line,"Review Total");

	CSV.Set(1,Line,QString::number(HistryList.GetCount()));
	ForSaveOneInspection *a=GetFirstInspection();
	if(a!=NULL){
		CSV.Set(2,Line,a->InspectionTime.toString("yy/MM/dd hh:mm:ss"));
	}
	else{
		CSV.Set(2,Line,"");
	}
	ForSaveOneInspection *b=GetLastInspection();
	if(b!=NULL){
		CSV.Set(2,Line+1,b->InspectionTime.toString("yy/MM/dd hh:mm:ss"));
	}
	else{
		CSV.Set(2,Line+1,"");
	}

	XDateTime	Ar=GetFirstReviewTime();
	CSV.Set(3,Line,Ar.toString("yy/MM/dd hh:mm:ss"));
	XDateTime	Br=GetLastReviewTime();
	CSV.Set(3,Line+1,Br.toString("yy/MM/dd hh:mm:ss"));
	int	DiffSec=Ar.secsTo(Br);
	CSV.Set(3,Line+2,QString::number(DiffSec));


	Line+=3;
	CSV.Set(0,Line,"");
	Line++;

	CSV.Set(0,Line,"NoFKey");
	int	FnNo=GetFKeyCount(-1);
	CSV.Set(0,Line+1,QString::number(FnNo));
	CSV.Set(1,Line,"NoView");
	FnNo=GetFKeyCount(-2);
	CSV.Set(1,Line+1,QString::number(FnNo));
	for(int i=0;i<12;i++){
		CSV.Set(2+i,Line,QString("F")+QString::number(i+1));
		FnNo=GetFKeyCount(i);
		CSV.Set(2+i,Line+1,QString::number(FnNo));
	}

	Line+=2;
	CSV.Set(0,Line,"");
	Line++;

	CSV.Set(0,Line,"OK count");
	CSV.Set(1,Line,"NG count");
	CSV.Set(2,Line,"Halt count");
	CSV.Set(0,Line+1,QString::number(CountOK));
	CSV.Set(1,Line+1,QString::number(CountNG));
	CSV.Set(2,Line+1,QString::number(CountHalt));
	
	QFileInfo	CSVFileInfo(FileName);
	QString		AbsPath=CSVFileInfo.absolutePath();
	::ForceDirectories(AbsPath);

	return CSV.SaveFromCSVFile(FileName);
}

bool	ForSaveTotalLot::LoadCSV(const QString &FileName)
{
	QStringListListCSV	CSV;

	if(CSV.LoadFromCSVFile(FileName)==true){
		MasterIDTop		=CSV.Get(1, 0).toInt();
		MasterNameTop	=CSV.Get(1, 1);
		LotTableNameTop	=CSV.Get(1, 2);
		LotNameTop		=CSV.Get(1, 3);

		MasterIDBack	=CSV.Get(1, 4).toInt();
		MasterNameBack	=CSV.Get(1, 5);
		LotTableNameBack=CSV.Get(1, 6);
		LotNameBack		=CSV.Get(1, 7);

		int	Line=10;
		for(;;){
			bool	ok;
			int		LNumber;
			LNumber	=CSV.Get(1,Line).toInt(&ok);
			if(ok==false){
				break;
			}
			ForSaveOneInspection *a=new ForSaveOneInspection();
			a->InspectionID=CSV.Get(0,Line).toInt(&ok);
			if(ok==false){
				break;
			}
			a->LineNumber		=LNumber;
			a->InspectionTime	=XDateTime::fromString(CSV.Get(2,Line),"yy/MM/dd hh:mm:ss");
			a->Entering			=XDateTime::fromString(CSV.Get(3,Line),"yy/MM/dd hh:mm:ss");
			a->Halt				=CSV.Get(4,Line).toInt(&ok);
			for(;;){
				int	x=0,y=0;
				int	MNumber=CSV.Get(5,Line).toInt(&ok);
				if(ok==true){
					ForSaveNGPoint *c=new ForSaveNGPoint(MNumber);
					c->Side	=CSV.Get(6,Line).toInt(&ok);
					if(ok==false){
						delete	c;
						Line++;
						break;
					}
					c->Entering		=XDateTime::fromString(CSV.Get(7,Line),"hh:mm:ss");
					c->Leaving		=XDateTime::fromString(CSV.Get(8,Line),"hh:mm:ss");
					c->FnKeyNumber	=CSV.Get(9,Line).toInt(&ok);
					if(ok==false){
						delete	c;
						Line++;
						break;
					}				
					x	=CSV.Get(10,Line).toInt(&ok);
					if(ok==false){
						delete	c;
						Line++;
						break;
					}
					y	=CSV.Get(11,Line).toInt(&ok);
					if(ok==false){
						delete	c;
						Line++;
						break;
					}
					c->Position	=QPoint(x,y);
					c->Cause	=CSV.Get(12,Line);
					a->NGList.AppendList(c);
				}
				else{
					Line++;
					break;
				}
				Line++;
				if(CSV.Get(1,Line).isEmpty()==false){
					break;
				}
			}
		}
	}
	return true;
}

ForSaveOneInspection	*ForSaveTotalLot::GetFirstInspection(void)
{
	ForSaveOneInspection *F=HistryList.GetFirst();
	ForSaveOneInspection *b=F;
	while(b!=NULL){
		if(F->InspectionTime>b->InspectionTime){
			F=b;
		}
		b=b->GetNext();
	}
	return F;
}
ForSaveOneInspection	*ForSaveTotalLot::GetLastInspection(void)
{
	ForSaveOneInspection *F=HistryList.GetFirst();
	ForSaveOneInspection *b=F;
	while(b!=NULL){
		if(F->InspectionTime<b->InspectionTime){
			F=b;
		}
		b=b->GetNext();
	}
	return F;
}

XDateTime	ForSaveTotalLot::GetFirstReviewTime(void)
{
	ForSaveOneInspection *F=HistryList.GetFirst();
	ForSaveOneInspection *b=F;
	while(b!=NULL){
		if(F->Entering>b->Entering){
			F=b;
		}
		b=b->GetNext();
	}
	return F->Entering;
}

XDateTime	ForSaveTotalLot::GetLastReviewTime(void)
{
	ForSaveOneInspection *F=HistryList.GetFirst();
	ForSaveOneInspection *b=F;
	while(b!=NULL){
		if(F->Entering<b->Entering){
			F=b;
		}
		b=b->GetNext();
	}
	if(F==NULL)
		return XDateTime();
	ForSaveNGPoint	*Last=F->NGList.GetFirst();
	ForSaveNGPoint	*k=Last;
	while(k!=NULL){
		if(Last->Leaving<k->Leaving){
			Last=k;
		}
		k=k->GetNext();
	}
	if(Last==NULL){
		return F->Entering;
	}
	return Last->Leaving;
}

int	ForSaveTotalLot::GetTopNGCount(void)
{
	int	NGCount=0;
	for(ForSaveOneInspection *a=HistryList.GetFirst();a!=NULL;a=a->GetNext()){
		NGCount+=a->GetTopNGCount();
	}
	return NGCount;
}

int	ForSaveTotalLot::GetBottomNGCount(void)
{
	int	NGCount=0;
	for(ForSaveOneInspection *a=HistryList.GetFirst();a!=NULL;a=a->GetNext()){
		NGCount+=a->GetBottomNGCount();
	}
	return NGCount;
}

int	ForSaveTotalLot::GetFKeyCount(int key)
{
	int	Count=0;
	for(ForSaveOneInspection *a=HistryList.GetFirst();a!=NULL;a=a->GetNext()){
		for(ForSaveNGPoint *c=a->NGList.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->FnKeyNumber==key){
				Count++;
			}
		}
	}
	return Count;
}

bool	ForSaveTotalLot::PutListingTitle(const QString &ListingFileName)
{
	QFile	LFile(ListingFileName);
	if(LFile.exists()==false){
		if(LFile.open(QIODevice::WriteOnly)==true){
			QTextStream		Txt(&LFile);
			Txt<<"\""<<"AFVI Machine No"<<"\",";
			Txt<<"\""<<"Master Code Top"<<"\",";
			Txt<<"\""<<"Master Name Top"<<"\",";
			Txt<<"\""<<"Lot ID Top"<<"\",";
			Txt<<"\""<<"Lot Name Top"<<"\",";
			Txt<<"\""<<"Master Code Back"<<"\",";
			Txt<<"\""<<"Master Name Back"<<"\",";
			Txt<<"\""<<"Lot ID Back"<<"\",";
			Txt<<"\""<<"Lot Name Back"<<"\",";
			Txt<<"\""<<"OK count"<<"\",";
			Txt<<"\""<<"NG count"<<"\",";
			Txt<<"\""<<"Halt count"<<"\",";
			Txt<<"\""<<"NG Point A-side"<<"\",";
			Txt<<"\""<<"NG Point B-side"<<"\",";
			Txt<<"\""<<"Inspection time Start"<<"\",";
			Txt<<"\""<<"Inspection time End"<<"\",";
			Txt<<"\""<<"Verify time Start"<<"\",";
			Txt<<"\""<<"Verify time End"<<"\"";
			Txt<<"\r\n";
		}
	}
	return true;
}

QString	GetLotIDStripped(const QString &LotID)
{
	QStringList	L=LotID.split('/');
	if(L.count()==1){
		return L[0];
	}
	if(L.count()>=2){
		return L[1];
	}
	return "";
}

bool	ForSaveTotalLot::AppendListing(const QString &ListingFileName ,const QString &CSVFileName)
{
	PutListingTitle(ListingFileName);

	QFile	LFile(ListingFileName);
	if(LFile.open(QIODevice::Append)==true){
		QTextStream		Txt(&LFile);
		Txt<<QString::number(InspectedMachine)<<",";
		Txt<<QString::number(MasterIDTop)<<",";
		Txt<<"\""<<MasterNameTop<<"\",";
		Txt<<"\""<<GetLotIDStripped(LotTableNameTop)<<"\",";
		Txt<<"\""<<LotNameTop<<"\",";
		Txt<<QString::number(MasterIDBack)<<",";
		Txt<<"\""<<MasterNameBack<<"\",";
		Txt<<"\""<<GetLotIDStripped(LotTableNameBack)<<"\",";
		Txt<<"\""<<LotNameBack<<"\",";
		Txt<<QString::number(CountOK)<<",";
		Txt<<QString::number(CountNG)<<",";
		Txt<<QString::number(CountHalt)<<",";
		Txt<<QString::number(NGCountTop)<<",";
		Txt<<QString::number(NGCountBack)<<",";
		Txt<<"\""<<InspectionTimeFirst.toString("yy/MM/dd hh:mm:ss")<<"\",";
		Txt<<"\""<<InspectionTimeLast.toString("yy/MM/dd hh:mm:ss")<<"\",";
		Txt<<"\""<<GetFirstReviewTime().toString("yy/MM/dd hh:mm:ss")<<"\",";
		Txt<<"\""<<GetLastReviewTime().toString("yy/MM/dd hh:mm:ss")<<"\"";
		Txt<<"\r\n";
		return true;
	}
	return false;
}

