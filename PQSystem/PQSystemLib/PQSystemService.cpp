#include "PQSystemService.h"
#include "XDataInLayer.h"
#include "XDatabaseLoader.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmDLL.h"
#include "XParamDatabase.h"
#include "XIntegrationBase.h"
#include "swap.h"
#include <QSqlQuery>
#include <QSqlRecord>


//=========================================================
static	const	wchar_t	*ExcelUser	=L"MASATOSHI SASAI";
static	const	wchar_t* ExcelKey = L"windows-252a28070ccee00f6fbd6d65ady7m2ue";


PQSystemRunner::PQSystemRunner(LayersBase *base ,const QString &root ,const QString &name
								,QWidget *parent)
	:QWidget(parent),ServiceForLayers(base),SRoot(root),SName(name)
{
	XLSXBook	=NULL;
	XLSXSheet[0]=NULL;
	SheetCount=0;
	Lang		=NULL;
	Fnt			=NULL;
}
PQSystemRunner::~PQSystemRunner()
{
}

bool	PQSystemRunner::GetMasterRelation(int RelationCode
										,QString &RetRelationNumber
										,QString &RetRelationName
										,QString &RetRemark
										,int &RetRelationType
										,QByteArray &CommonData
										,int32 &ThresholdLevelID)
{
	std::shared_ptr<DatabaseLoader>	Ld=GetLayersBase()->GetDatabaseLoader();
	if(Ld->G_GetMasterRelation(GetLayersBase()->GetDatabase()
								,RelationCode
								,RetRelationNumber
								,RetRelationName
								,RetRemark
								,RetRelationType
								,CommonData
								,ThresholdLevelID)==false){
		return false;
	}
	RelationMasterList MasterListDim[100];
	int	N=Ld->G_SearchMasterCode(GetLayersBase()->GetDatabase(),RelationCode
								 ,MasterListDim ,100);
	for(int i=0;i<N;i++){
		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			if(MasterListDim[i].MachineID==m->GetMachineCode()){
				m->SetMasterCode(MasterListDim[i].MasterCode);
				int32		MachineID	;
				XDateTime	RegTime		;
				QString		MasterName	;
				QString		Remark		;
				int32		Version		;
				XDateTime	LastEditTime;
				int32		CategoryID	;
				int16		MasterType	;
				int			iDotPerLine	;
				int			iMaxLines	;
				int			iLayerNumb	;
				int			iPageNumb	;
				int			iPhaseNumb	;
				int32		LibFolderID	;
				int32 		iThresholdLevelID;
				int32 		iThresholdLevelParentID;

				if(Ld->G_SQLLoadMasterData2(GetLayersBase()->GetDatabase()
							,m->GetMasterCode()
							,MachineID
							,RegTime
							,MasterName ,Remark
							,Version
							,LastEditTime
							,CategoryID
							,MasterType
							,iDotPerLine
							,iMaxLines
							,iLayerNumb
							,iPageNumb
							,iPhaseNumb
							,LibFolderID
							,iThresholdLevelID
							,iThresholdLevelParentID)==true){
					m->SetMasterName(MasterName);
					m->Reallocate(iPhaseNumb,iPageNumb);
					m->SetThresholdLevelID(iThresholdLevelID);
				}
			}
		}
	}
	return true;
}
bool	PQSystemRunner::LoadMasterImage(int RelationCode)
{
	std::shared_ptr<DatabaseLoader>	Ld=GetLayersBase()->GetDatabaseLoader();
	RelationMasterList MasterListDim[100];
	int	N=Ld->G_SearchMasterCode(GetLayersBase()->GetDatabase(),RelationCode
								 ,MasterListDim ,100);

	IntegrationBase	*LBase=GetLayersBase()->GetIntegrationBasePointer();
	for(EachMaster *m=LBase->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		for(int i=0;i<N;i++){
			if(m->GetMachineCode()==MasterListDim[i].MachineID){
				if(m->LoadMaster(MasterListDim[i].MasterCode)==false){
					return false;
				}
			}
		}
	}
	return true;
}
QImage PQSystemRunner::LoadDataFromMaster(int masterCode)
{
	QString	S=QString(/**/"SELECT"
							/**/" TOPVIEW"
							/**/" from MASTERDATA where MASTERCODE=")+QString::number(masterCode);
	QSqlQuery query(S ,GetLayersBase()->GetDatabase());
	if(query.next()==true){
		QByteArray	STopview=query.value(query.record().indexOf("TOPVIEW")).toByteArray();
		QBuffer	TopviewBuff;
		TopviewBuff.setData(STopview);
		if(TopviewBuff.open(QIODevice::ReadOnly)==true){
			QImage	TopView;
			if(TopView.load(&TopviewBuff,"PNG")==true){
				return TopView;
			}
		}
	}
	return QImage();
}

void	PQSystemRunner::GetAllAlgorithmPointers(AlgorithmBasePointerContainer &Container)
{
	Container.RemoveAll();
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypeProcessing)==true){
			Container.AppendList(new AlgorithmBasePointerList(L->GetInstance()));
		}
	}
}
bool	PQSystemRunner::LoadNGImageFile(const QString &FileName,NPListPack<IntegNGImage> NGImages[] ,int PhaseCount)
{
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		if(LoadNGImageFile(&File,NGImages, PhaseCount ,0,0)==false){
			return false;
		}
		int32	ShadowNumb;
		if(::Load(&File,ShadowNumb)==false){
			return false;
		}
		for(int i=0;i<ShadowNumb;i++){
			int		ShadowLevel=0;
			int		ShadowNumber=0;
			if(::Load(&File,ShadowLevel)==false){
				return false;
			}
			if(::Load(&File,ShadowNumber)==false){
				return false;
			}

			if(LoadNGImageFile(&File,NGImages, PhaseCount
								,ShadowLevel,ShadowNumber)==false){
				return false;
			}
		}
		return true;
	}
	return false;
}

bool	PQSystemRunner::LoadNGImageFile(QIODevice *f ,NPListPack<IntegNGImage> NGImages[],int PhaseCount
										,int ShadowLevel,int ShadowNumber)
{
	DWORD	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	int32	PhaseNumb;
	if(::Load(f,PhaseNumb)==false){
		return false;
	}
	for(int phase=0;phase<PhaseNumb;phase++){
		DWORD	PVer;
		if(::Load(f,PVer)==false){
			return false;
		}
		int32	Phase;
		if(::Load(f,Phase)==false){
			return false;
		}
		if(PVer<5){
			int32	N;
			if(::Load(f,N)==false){
				return false;
			}
			for(int i=0;i<N;i++){
				IntegNGImage	*G=new IntegNGImage(ShadowLevel,ShadowNumber);
				if(G->LoadJDT(f)==false)
					return false;
				if(0<=Phase && Phase<PhaseCount){
					NGImages[Phase].AppendList(G);
				}
				else{
					delete	G;
				}
			}
		}
		else{
			int16	SaveMode;
			if(::Load(f,SaveMode)==false){
				return false;
			}
			int32	N;
			if(::Load(f,N)==false){
				return false;
			}
			for(int i=0;i<N;i++){
				IntegNGImage	*G=new IntegNGImage(ShadowLevel,ShadowNumber);
				if(SaveMode==1){
					if(G->LoadJDT(f)==false)
						return false;
				}
				else
				if(SaveMode==0){
					if(G->LoadRawImage(f)==false)
						return false;
				}
				if(0<=Phase && Phase<PhaseCount){
					NGImages[Phase].AppendList(G);
				}
				else{
					delete	G;
				}
			}
		}
	}
	return true;
}

bool	PQSystemRunner::DrawMasterImage(EachMaster *M ,QImage &Image,int Phase 
							,int MovX,int MovY ,double ZoomRate)
{
	int	GWidth	=Image.width();
	int	GHeight	=Image.height();
	double	Z=1.0/ZoomRate;
	for(int page=0;page<M->GetPageNumb();page++){
		int	tDotPerLine	=M->GetDotPerLine(Phase ,page);
		int	tMaxLines	=M->GetMaxLines(Phase ,page);
		XYData	*XY=M->GetOutlineOffset(Phase, page);
		if(M->GetLayerNumb(0,page)==3){
			ImageBuffer	*L0=M->GetMasterImage(Phase,page ,0);
			ImageBuffer	*L1=M->GetMasterImage(Phase,page ,1);
			ImageBuffer	*L2=M->GetMasterImage(Phase,page ,2);
			if(L0==NULL || L1==NULL || L2==NULL){
				return false;
			}
			#pragma omp parallel
			{
				#pragma omp for
				for(int y=0;y<GHeight;y++){
					int	Y=y*Z-MovY - XY->y;
					QRgb	*d=(QRgb *)Image.scanLine(y);
					if(0<=Y && Y<tMaxLines){
						BYTE	*s0=L0->GetY(Y);
						BYTE	*s1=L1->GetY(Y);
						BYTE	*s2=L2->GetY(Y);
						for(int x=0;x<GWidth;x++,d++){
							int	X=x*Z-MovX - XY->x;
							if(0<=X && X<tDotPerLine){
								*d=qRgba(s0[X],s1[X],s2[X],255);
							}
							else{
								*d=qRgba(0,0,0,255);
							}
						}
					}
					else{
						for(int x=0;x<GWidth;x++,d++){
							*d=qRgba(0,0,0,255);
						}
					}
				}
			}
		}
		else if(M->GetLayerNumb(0,page)==2){
			ImageBuffer	*L0=M->GetMasterImage(Phase,page ,0);
			ImageBuffer	*L1=M->GetMasterImage(Phase,page ,1);
			if(L0==NULL || L1==NULL){
				return false;
			}
			#pragma omp parallel
			{
				#pragma omp for
				for(int y=0;y<GHeight;y++){
					int	Y=y*Z-MovY - XY->y;
					QRgb	*d=(QRgb *)Image.scanLine(y);
					if(0<=Y && Y<tMaxLines){
						BYTE	*s0=L0->GetY(Y);
						BYTE	*s1=L1->GetY(Y);
						for(int x=0;x<GWidth;x++,d++){
							int	X=x*Z-MovX - XY->x;
							if(0<=X && X<tDotPerLine){
								*d=qRgba(s0[X],s1[X],s1[X],255);
							}
							else{
								*d=qRgba(0,0,0,255);
							}
						}
					}
					else{
						for(int x=0;x<GWidth;x++,d++){
							*d=qRgba(0,0,0,255);
						}
					}
				}
			}
		}
		if(M->GetLayerNumb(0,page)==1){
			ImageBuffer	*L0=M->GetMasterImage(Phase,page ,0);
			if(L0==NULL){
				return false;
			}
			#pragma omp parallel
			{
				#pragma omp for
				for(int y=0;y<GHeight;y++){
					int	Y=y*Z-MovY - XY->y;
					QRgb	*d=(QRgb *)Image.scanLine(y);
					if(0<=Y && Y<tMaxLines){
						BYTE	*s0=L0->GetY(Y);
						for(int x=0;x<GWidth;x++,d++){
							int	X=x*Z-MovX - XY->x;
							if(0<=X && X<tDotPerLine){
								*d=qRgba(s0[X],s0[X],s0[X],255);
							}
							else{
								*d=qRgba(0,0,0,255);
							}
						}
					}
					else{
						for(int x=0;x<GWidth;x++,d++){
							*d=qRgba(0,0,0,255);
						}
					}
				}
			}
		}
	}
	return true;
}

void	PQSystemRunner::InitialExcel(void)
{
	if(XLSXBook!=NULL){
		XLSXBook->release();
		delete	XLSXBook;
	}
	SheetCount=0;
	XLSXBook = xlCreateXMLBook();
	XLSXBook->setKey(ExcelUser, ExcelKey);

	wchar_t	filename[1000];
	memset(filename,0,sizeof(filename));
	ReferredExcelFileName.toWCharArray(filename);
	bool	Loaded=false;
	if(XLSXBook->load(filename)==true){
		if(XLSXBook->sheetCount()>0){
			XLSXSheet[0]=XLSXBook->getSheet(0);
			Loaded=true;
		}
	}
	if(Loaded==false){
		XLSXSheet[0]=XLSXBook->addSheet(L"詳細");
	}
	Lang	=XLSXBook->addFormat();
	Fnt	=XLSXBook->addFont();
	QString	FontName;
	switch(GetLayersBase()->GetLanguageCode()){
		case 0:	FontName= "ＭＳ Ｐゴシック";	break;
		case 1:	FontName= "Arial";				break;
		case 2:	FontName= "SimSun";				break;
		case 3:	FontName= "MingLiU";			break;
		case 4:	FontName= "Gulim";				break;
	}
	wchar_t	WBuff[100];
	memset(WBuff, 0, sizeof(WBuff));
	FontName.toWCharArray(WBuff);
	Fnt->setName(WBuff);

	Lang->setFont(Fnt);
	Lang->setBorder();

	SheetCount++;
}

void	PQSystemRunner::AddSheet(const QString &SheetName)
{
	wchar_t	WBuff[100];
	memset(WBuff, 0, sizeof(WBuff));
	SheetName.toWCharArray(WBuff);
	if(XLSXBook->sheetCount()>SheetCount){
		XLSXSheet[SheetCount]=XLSXBook->getSheet(SheetCount);
	}
	else{
		XLSXSheet[SheetCount]=XLSXBook->addSheet(WBuff);
	}
	SheetCount++;
}

void	PQSystemRunner::ReleaseExcel(void)
{
	XLSXBook->release();
	//delete	XLSXBook;
	XLSXBook=NULL;
}

bool	PQSystemRunner::SaveExcel(const QString &ExcelFileName)
{
	wchar_t	FileNameStr[256];
	memset(FileNameStr,0,sizeof(FileNameStr));
	ExcelFileName.toWCharArray(FileNameStr);

	if(XLSXBook->save(FileNameStr)==false){
		XLSXBook->release();
		delete	XLSXBook;
		XLSXBook=NULL;
		return false;
	}
	return true;
}

void	PQSystemRunner::SetCellHeight(int height ,int SheetNo)
{
	XLSXSheet[SheetNo]->setDefaultRowHeight(height);
}

void	PQSystemRunner::WriteCell(int Row, int Col ,const QString &Str,int SheetNo)
{
	wchar_t	Buff[1000];
	memset(Buff,0,sizeof(Buff));
	Str.toWCharArray(Buff);

	Lang->setWrap(true);
	XLSXSheet[SheetNo]->setCellFormat(Row, Col,Lang);
	XLSXSheet[SheetNo]->writeStr(Row, Col,Buff);
}
void	PQSystemRunner::WriteCell(int Row, int Col ,int N	,int SheetNo)
{
	XLSXSheet[SheetNo]->setCellFormat(Row, Col,Lang);
	XLSXSheet[SheetNo]->writeNum(Row, Col,N);
}
void	PQSystemRunner::WriteCell(int Row, int Col ,int64 N	,int SheetNo)
{
	XLSXSheet[SheetNo]->setCellFormat(Row, Col,Lang);
	XLSXSheet[SheetNo]->writeNum(Row, Col,N);
}
void	PQSystemRunner::WriteCell(int Row, int Col ,double N,int SheetNo)
{
	XLSXSheet[SheetNo]->setCellFormat(Row, Col,Lang);
	XLSXSheet[SheetNo]->writeNum(Row, Col,N);
}

void	PQSystemRunner::WriteCell(int Row, int Col ,const QString &Str ,const QColor &aColor ,int SheetNo)
{
	wchar_t	Buff[1000];
	memset(Buff,0,sizeof(Buff));
	Str.toWCharArray(Buff);

	FillPattern	tPtn=Lang->fillPattern();
	Lang->setFillPattern(FILLPATTERN_SOLID);

	libxl::Color	tCol=Lang->patternBackgroundColor();
	if(aColor==Qt::red)
		Lang->setPatternBackgroundColor(libxl::COLOR_RED);
	else if(aColor==Qt::green)
		Lang->setPatternBackgroundColor(libxl::COLOR_GREEN);
	else if(aColor==Qt::blue)
		Lang->setPatternBackgroundColor(libxl::COLOR_BLUE);

	XLSXSheet[SheetNo]->setCellFormat(Row, Col,Lang);
	XLSXSheet[SheetNo]->writeStr(Row, Col,Buff,Lang);

	Lang->setFillPattern(tPtn);
	Lang->setPatternBackgroundColor(tCol);
}

void	PQSystemRunner::WriteCellV(int Row, int Col ,const QVariant &Data,int SheetNo)
{
	XLSXSheet[SheetNo]->setCellFormat(Row, Col,Lang);

	wchar_t	Buff[1000];
	memset(Buff,0,sizeof(Buff));
	if(Data.type()==QVariant::Bool){
		if(Data.toBool()==true){
			XLSXSheet[SheetNo]->writeStr(Row, Col,L"true");
		}
		else{
			XLSXSheet[SheetNo]->writeStr(Row, Col,L"false");
		}
	}
	else if(Data.type()==QVariant::Char){
		QString	s(Data.toChar());
		s.toWCharArray(Buff);	
		XLSXSheet[SheetNo]->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::Date){
		QString	s(Data.toDate().toString());
		s.toWCharArray(Buff);	
		XLSXSheet[SheetNo]->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::DateTime){
		QString	s(Data.toDateTime().toString());
		s.toWCharArray(Buff);	
		XLSXSheet[SheetNo]->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::Double){
		QString	s=QString::number(Data.toDouble(),'f');
		s.toWCharArray(Buff);
		XLSXSheet[SheetNo]->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::Int){
		QString	s=QString::number(Data.toInt());
		s.toWCharArray(Buff);
		XLSXSheet[SheetNo]->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::String){
		QString	s=Data.toString();
		s.toWCharArray(Buff);
		XLSXSheet[SheetNo]->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::Time){
		QString	s(Data.toTime().toString());
		s.toWCharArray(Buff);	
		XLSXSheet[SheetNo]->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::UInt){
		QString	s=QString::number(Data.toUInt());
		s.toWCharArray(Buff);
		XLSXSheet[SheetNo]->writeStr(Row, Col,Buff);
	}
	else{
		XLSXSheet[SheetNo]->writeStr(Row, Col,L"Error");
	}
}

void	PQSystemRunner::SetRowHeight(int row,int height,int SheetNo)
{
	XLSXSheet[SheetNo]->setRow(row, height);
}

InspectionListByMaster::InspectionListByMaster(void)
{
}
InspectionListByMaster::~InspectionListByMaster()
{
}
InspectionListByMaster	&InspectionListByMaster::operator=(const InspectionListByMaster &src)
{
	LotListData	=src.LotListData;
	MachineID	=src.MachineID;
	return *this;
};

void	InspectionListByMaster::Move(InspectionListContainer &src)
{
	InspectionList	*s;
	while((s=src.GetFirst())!=NULL){
		src.RemoveList(s);
		NPListPack<InspectionList>::AppendList(s);
	}
}

bool	LotListWithResult::LoadResult(IntegrationBase *Base)
{
	//CurrentInspection.RemoveAll();
	//if(Base!=NULL){
	//	int	GlobalID=0;
	//	Base->SelectLot(GlobalID);
	//	for(EachMaster *m=Base->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
	//		InspectionListByMaster	*L=new InspectionListByMaster();
	//		L->MachineID=m->GetMachineCode();
	//		L->Move(m->CurrentInspection);
	//		if(m->CurrentLot!=NULL){
	//			L->LotListData=*m->CurrentLot;
	//			CurrentInspection.AppendList(L);
	//		}
	//	}
	//}
	IntList	GlobalIDList;
	for(InspectionListByMaster *L=CurrentInspection.GetFirst();L!=NULL;L=L->GetNext()){
		GlobalIDList.Merge(L->LotListData.GlobalID);
	}
	CurrentInspection.RemoveAll();
	if(Base!=NULL){
		for(IntClass *v=GlobalIDList.GetFirst();v!=NULL;v=v->GetNext()){
			int	GlobalID=v->GetValue();
			Base->SelectLot(GlobalID);
			for(EachMaster *m=Base->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
				InspectionListByMaster	*L=new InspectionListByMaster();
				L->MachineID=m->GetMachineCode();
				InspectionListContainer	tmpL=m->GetCurrentInspection();
				L->Move(tmpL);
				if(m->GetCurrentLot()!=NULL){
					L->LotListData=*m->GetCurrentLot();
					CurrentInspection.AppendList(L);
				}
			}
		}
	}
	return true;
}

LotListWithResult	&LotListWithResult::operator=(const LotListWithResult &src)
{
	CurrentInspection.RemoveAll();
	for(InspectionListByMaster *a=src.CurrentInspection.GetFirst();a!=NULL;a=a->GetNext()){
		InspectionListByMaster *b=new InspectionListByMaster();
		*b=*a;
		CurrentInspection.AppendList(b);
	}
	return *this;
}

//===========================================================================
ImagePanel::ImagePanel(ScrollPanel *p)
	:Parent(p)
{}
ImagePanel::~ImagePanel()
{}

void	ImagePanel::Add(const QImage &s)
{
	Image=s;
	setGeometry(0,0,Image.width(),Image.height());
}
void	ImagePanel::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);
	paint(Pnt);
}
void	ImagePanel::paint(QPainter &Pnt)
{
	Pnt.drawImage(0,0,Image);
}

ScrollPanel::ScrollPanel(QWidget *parent)
	:QScrollArea(parent),W(NULL)
{
}
ScrollPanel::~ScrollPanel()
{
}
ImagePanel	*ScrollPanel::CreatePanel(void)
{
	ImagePanel	*a=new ImagePanel(this);
	return a;
}
void	ScrollPanel::Clear(void)
{
	Panels.RemoveAll();
	if(W!=NULL){
		delete	W;
		W=NULL;
	}
}
ImagePanel	*ScrollPanel::Add(const QImage &s)
{
	ImagePanel	*a=CreatePanel();
	a->Add(s);
	Panels.AppendList(a);
	return a;
}
void	ScrollPanel::Assign(void)
{
	int	Px=0;
	int	Py=0;
	int	H=0;
	int	MaxW=0;
	int	MaxH=0;
	if(W!=NULL){
		for(ImagePanel *p=Panels.GetFirst();p!=NULL;p=p->GetNext()){
			p->setParent(NULL);
		}
		delete	W;
	}

	W=new QWidget(this);
	W->setParent(this);
	int	XMergin=5;
	int	YMergin=5;
	
	for(ImagePanel *p=Panels.GetFirst();p!=NULL;p=p->GetNext()){
		p->setParent(W);
		if(Px+p->width()<width()){
			p->move(Px,Py);
			Px+=p->width()+XMergin;
			if(H<p->height()){
				H=p->height();
			}
			MaxW=max(MaxW,p->geometry().right());
			MaxH=max(MaxH,p->geometry().bottom());
		}
		else{
			Py+=H+YMergin;
			Px=0;
			p->move(Px,Py);
			H=p->height();
			Px+=p->width()+XMergin;
			MaxW=max(MaxW,p->geometry().right());
			MaxH=max(MaxH,p->geometry().bottom());
		}
	}
	W->setGeometry(0,0,MaxW,MaxH);
	setWidget(W);
	show();
}