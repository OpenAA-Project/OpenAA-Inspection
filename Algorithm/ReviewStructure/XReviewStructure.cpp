#include <QRegularExpression>
#include <QDomElement>
#include <QRegularExpression>
#include <QRegion>

#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XDatabase.h"
#include "XDatabaseLoader.h"
#include "XOutlineOffset.h"
#include "XMainSchemeMemory.h"
#include "SetOutlineOffset.h"
#include "XReviewStructure.h"

#include "DXMLParser.h"
#include "JDTAnalyzer.h"
#include "XMLWriter.h"
#include "ReviewSequenceThread.h"
#include "XServiceForLayers.h"
#include "XParamDatabase.h"
#include "ui_ReviewStructurePropertyForm.h"

extern ReviewSequenceThread *ReviewSequenceThreadGlobal;

namespace debug_review{

	QFile DebugLogFile;
	QTextStream DebugLogStream;

}

void AppendDebugLog(QString str){
#ifdef NDEBUG
	return;
#else
	static QFile DebugLogFile;
	static QTextStream DebugLogStream;

	if(str.isEmpty()){
		return;
	}

	QDir dir(qApp->applicationDirPath());
	if(dir.exists(/**/"ReviewDebugLog")==false){
		dir.mkdir(/**/"ReviewDebugLog");
	}

	if(DebugLogFile.isOpen()==false){
		QString filename = QString(/**/"ReviewDebugLog/Debug_%1.txt").arg( XDateTime::currentDateTime().toString(/**/"yyyy-MM-dd-hhmmss") );
		DebugLogFile.setFileName( filename );
		DebugLogFile.open(QIODevice::WriteOnly | QIODevice::Text);
		if(DebugLogFile.isOpen()==true){
			DebugLogStream.setDevice( &DebugLogFile );
		}else{
			return;
		}
	}

	DebugLogStream << str << endl;
#endif
}

bool	ReviewPIInPage::LoadSlave(int MasterCode ,int MachineID ,int PhaseCode)
{
	DataInPage	*Dp=GetDataInPage();

	QStringList list = GetLayersBase()->GetParamGlobal()->ImageFilePath.split(';', QString::SplitBehavior::SkipEmptyParts);

	if(list.isEmpty()==true){
		return false;
	}

	for(int i=0; i<list.count(); i++){
		QString	ImageFileName=getMasterImageName(MasterCode, MachineID, PhaseCode, list[i]);
		if(QFile::exists (ImageFileName )==true){
			QFile	ImageFile(ImageFileName);
			ImageFile.open(QIODevice::ReadOnly);
			for(int LNumb=0;LNumb<GetLayerNumb();LNumb++){
				DataInLayer	*L=Dp->GetLayerData(LNumb);
				if(L->GetMasterBuff().Load(&ImageFile)==false){
					return false;
				}
				//QFile	ImageFile2(ImageFileName);
				//ImageFile2.open(QIODevice::ReadOnly);
				//QImage img = ImageBuffer::toImage(&ImageFile2, 0);
				//img.convertToFormat(QImage::Format_RGB32).save("Test.jpg");
				ImageBuffer	Dummy;
				if(Dummy.Load(&ImageFile)==false){
					return false;
				}
				if(Dummy.Load(&ImageFile)==false){
					return false;
				}
			}

			return true;
		}
	}

	return false;
}

QString ReviewPIInPage::getMasterImageName(int MasterCode ,int MachineID ,int PhaseCode, QString path)
{
	QString Sep=/**/"";
	QString s = path.right(1);
	if(s!=::GetSeparator() && s!=QString(/**/"\\")){
		Sep= GetSeparator();
	}
	QString	Ret;
	if(PhaseCode==0){
		Ret =path+Sep
			+QString(/**/"Image")+QString::number(MasterCode)+QString(/**/"-")
			+QString(/**/"Page")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(GetPage()))+QString(/**/"-")
			+QString(/**/"Mac")+QString::number(MachineID)
			+QString(/**/".img");
	}
	else{
		Ret =path+Sep
			+QString(/**/"Image")+QString::number(MasterCode)+QString(/**/"-")
			+QString(/**/"Phase")+QString::number(PhaseCode)+QString(/**/"-")
			+QString(/**/"Page")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(GetPage()))+QString(/**/"-")
			+QString(/**/"Mac")+QString::number(MachineID)
			+QString(/**/".img");
	}
	return Ret;
}

//======================================================================================

ReviewPIBase::ReviewPIBase(LayersBase *Base,EntryPointBase *EPoint)
	:AlgorithmBase(Base),m_VRSThread(NULL)
{
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	SetLayersBase(Base);
	EscapeLastTime=false;
	VRSOffsetX=0;
	VRSOffsetY=0;
	VRSDiffX	=0;
	VRSDiffY	=0;

	setSequenceEnable(false);

	initProperty();

	setSequenceThread(NULL);

	//// ファイル読み込み or 新規生成
	//QFile file(CommSettingFile);
	//if(QFile::exists(CommSettingFile)){
	//	if(file.open(QIODevice::ReadOnly)){
	//		QString	address;
	//		int		port;
	//		if(::Load(&file, address) && ::Load(&file, port)){
	//			setXMLServerState(address, port);
	//		}
	//		file.close();
	//	}else{
	//		QMessageBox::warning(NULL, "Server access config file error", "file is exist. But it is not correctly. State was initialized.(IP Address:localhost, Port No:12345)");
	//	}
	//}else{
	//	file.open(QIODevice::WriteOnly);
	//	::Save(&file, getXMLServerIPAddress());
	//	::Save(&file, getXMLServerPortNo());
	//	file.close();
	//}

	m_xmlWriter = new XMLWriter(this);
	m_xmlWriter->set(getXMLServerIPAddress(), getXMLServerPortNo());

	// サーバーハンドルインスタンス生成(&オープン)
	m_xmlServerHdl = new XMLServerHandle(getXMLServerIPAddress(), getXMLServerPortNo(), qApp);

	// select
	m_xmlServerHdl->WaitMilisec_Select = INT_MAX;
	m_xmlServerHdl->WaitMilisec_ChildSelect = INT_MAX;

	// first
	m_xmlServerHdl->WaitMilisec_SelectFirst = INT_MAX;
	m_xmlServerHdl->WaitMilisec_ChildSelectFirst = INT_MAX;

	// last
	m_xmlServerHdl->WaitMilisec_SelectLast = INT_MAX;
	m_xmlServerHdl->WaitMilisec_ChildSelectLast = INT_MAX;

	// next
	m_xmlServerHdl->WaitMilisec_SelectNext = INT_MAX;
	m_xmlServerHdl->WaitMilisec_ChildSelectNext = INT_MAX;

	// dup
	m_xmlServerHdl->WaitMilisec_DupOperation = INT_MAX;

	// enum
	m_xmlServerHdl->WaitMilisec_EnumTables = INT_MAX;


	QString appDirPath = qApp->applicationDirPath();
	QString appFilePath = qApp->applicationFilePath();
	QString appName = appFilePath.right(appFilePath.length() - appDirPath.length() - 1/* separator */);
	if(appName==/**/"RepairGUIMain.exe" || appName==/**/"InspectionEditer.exe" || appName==/**/"InspectionPlayer.exe"){
		//XML_Open();
		//xmlWriter->start();
	}
	if(appName==/**/"RepairGUIMain.exe"){
		freeMasterBufferEnable = true;
	}else{
		freeMasterBufferEnable = false;
	}

	clearRoundCurrentOrganizedHistoryIterator();

	clearRoundCurrentNGNailIterator();

	getMasterWholePageImageListPtr(Review::Front)->clear();
	getMasterWholePageImageListPtr(Review::Back)->clear();

	getMasterInfoPtr(Review::Front)->Side = Review::Front;
	getMasterInfoPtr(Review::Back)->Side = Review::Back;
}

ReviewPIBase::~ReviewPIBase(void)
{
	XML_Close();
	if(m_xmlWriter!=NULL){
		m_xmlWriter->setFlash(true);
		if(m_xmlWriter->wait(500)==false){
			QMessageBox box(NULL);
			box.setText("Please wait while updating XML code.");
			box.setWindowTitle("XML update");
			m_xmlWriter->wait();
		}
	}

	//saveSetting();
}

void ReviewPIBase::Initial(LayersBase *Base)
{
	AlgorithmBase::Initial(Base);

	if(hasSequenceThread()==false || getSequenceThread()->GetLayersBase()!=Base){
		ReviewSequenceRequire req;
		req.setMoveZ( getVRSSetting().getVRSSideSetting().ZInitialDistance );
		setSequenceThread(new ReviewSequenceThread(Base, this));
		getSequenceThread()->append(req);
	}
}

AlgorithmDrawAttr	*ReviewPIBase::CreateDrawAttr(void)
{
	return NULL;
}

void ReviewPIBase::setXMLServerState(const QString &IPAddress, int portNo, bool nowReconnect)
{
	if(nowReconnect==true){
		XML_Open(IPAddress, portNo);
	}

	getProperty().XMLServerIPAddress = IPAddress;
	getProperty().XMLServerPortNo = portNo;
}

QMatrix ReviewPIBase::getVRSMatrixFromWhole(Review::SideType side) const
{
	return getVRSAlignment(side).getWholeAffinMatrix();
}

QList<QMatrix> ReviewPIBase::getVRSMatrixFromEachPage(Review::SideType side) const
{
	return getVRSAlignment(side).getEachPageAffinMatrix();
}

QMatrix ReviewPIBase::getVRSMatrixFromEachPage(Review::SideType side, int page) const
{
	return getVRSAlignment(side).getEachPageAffinMatrix(page);
}

bool	ReviewPIBase::LoadMaster(Review::SideType side, int PhaseCode ,int MasterCode, int32 &iMachineID
								,int &iPhaseNumb, MasterDataInfo &infoBuff, bool addMode)
{
	bool		ret=false;
	XDateTime	iRegTime;
	QString		iMasterName;
	QString		iRemark;
	int32		iVersion;
	XDateTime	iLastEditTime;
	int32		iCategoryID;
	int16		iMasterType;
	int			iDotPerLine;
	int			iMaxLines;
	int			iLayerNumb;
	int			iPageNumb;
	int32 		iLibFolderID;
	int32 		iThresholdLevelID;
	int32 		iThresholdLevelParentID;

	if(GetLayersBase()->GetDatabaseLoader()){
		ret=GetLayersBase()->GetDatabaseLoader()->G_SQLLoadMasterData2(GetLayersBase()->GetDatabase()
							,MasterCode
							,iMachineID
							,iRegTime
							,iMasterName ,iRemark
							,iVersion
							,iLastEditTime
							,iCategoryID
							,iMasterType
							,iDotPerLine
							,iMaxLines
							,iLayerNumb
							,iPageNumb
							,iPhaseNumb
							,iLibFolderID
							,iThresholdLevelID
							,iThresholdLevelParentID);

		if(ret==false){
			return false;
		}
		GetLayersBase()->SetLibFolderID(iLibFolderID);
		
		infoBuff.MasterCode = MasterCode;
		infoBuff.MachineID = iMachineID;
		infoBuff.RegTime = iRegTime;
		infoBuff.MasterName = iMasterName;
		infoBuff.Remark = iRemark;
		infoBuff.Version = iVersion;
		infoBuff.LastEditTime = iLastEditTime;
		infoBuff.CategoryID = iCategoryID;
		infoBuff.MasterType = iMasterType;
		infoBuff.DotPerLine = iDotPerLine;
		infoBuff.MaxLines = iMaxLines;
		infoBuff.LayerNumb = iLayerNumb;
		infoBuff.PageNumb = iPageNumb;
		if(iPhaseNumb==0){
			infoBuff.PhaseNumb = 1;
		}else{
			infoBuff.PhaseNumb = iPhaseNumb;
		}
		infoBuff.ThresholdLevelID		= iThresholdLevelID;
		infoBuff.ThresholdLevelParentID = iThresholdLevelParentID;

		// 変更準備
		GetLayersBase()->ClearAllAckFlag();
		
		QStringList list = GetLayersBase()->GetParamGlobal()->ImageFilePath.split(';', QString::SplitBehavior::SkipEmptyParts);

		for(int i=0; i<list.count(); i++){
			QString	GUIContentFileName=GetLayersBase()->CreateGUIContentFileName(MasterCode,iMachineID, list[i]);
			if(QFile::exists(GUIContentFileName)==true){
				QFile	GUIContentFile(GUIContentFileName);
				if(GUIContentFile.open(QIODevice::ReadOnly)==true){
					int32	GUIVer;
					if(::Load(&GUIContentFile,GUIVer)==false){
						return false;
					}
					int32	GUICount=0;
					if(::Load(&GUIContentFile,GUICount)==false){
						return false;
					}
					for(int i=0;i<GUICount;i++){
						QString	SRoot;
						QString	SName;
						QString	InstName;

						if(::Load(&GUIContentFile,SRoot)==false){
							break;
							//return false;
						}
						if(::Load(&GUIContentFile,SName)==false){
							break;
							//return false;
						}
						if(::Load(&GUIContentFile,InstName)==false){
							break;
							//return false;
						}
						QByteArray	GUIArray;
						if(::Load(&GUIContentFile,GUIArray)==false){
							break;
							//return false;
						}

						GUIFormBase	*h=GetLayersBase()->FindByName(SRoot,SName,InstName);
						if(h!=NULL){
							QBuffer	GUIBuff(&GUIArray);
							GUIBuff.open(QIODevice::ReadOnly);
							h->LoadContent(&GUIBuff);
						}
					}
				}
			}
		}
		// データベースからライブラリコードを引っ張ってくる
	//	InsLibCodeHash.clear();
	//	QSqlQuery query("select * from inspectlibtype");
	//	while(query.next()==true){
	//		int libcode = query.record().value("LIBTYPE").toInt();
	//		QString libname = query.record().value("TYPENAME").toString();
	//		InsLibCodeHash[libname] = libcode;
	//		qDebug() << "LibCode:" << libcode << " = " << libname;
	//	}

	//	LibNGTypePack.clear();
	//	query.exec("select * from anydatainlib");
	//	while(query.next()==true){
	//		LibNGTypeItemForReview item;
	//		item.LibType = -1;
	//		item.LibID = -1;
	//		item.NGName = "";
	//		item.LastUpdated = XDateTime();
	//		item.DataVersion = -1;

	//		item.Blink = -1;
	//		item.NextJumpMilisec = 0;
	//		item.NGColor = QColor(Qt::red);
	//		item.NGName = "";
	//		item.NGShape = LibNGTypeItem::NGShapeType::NG_Circle;
	//		item.Priority = -1;
	//		item.TypeCode = -1;
	//		item.TypeUniqueCode = -1;

	//		if(query.record().contains("LIBTYPE")==true){
	//			item.LibType = query.record().value("LIBTYPE").toInt();// Basic:BlockInspectionなどの判定コード
	//		}
	//		if(query.record().contains("LIBID")==true){
	//			item.LibID = query.record().value("LIBID").toInt();
	//		}
	//		if(query.record().contains("NGTYPEID")==true){
	//			item.TypeCode = query.record().value("NGTYPEID").toInt();
	//		}
	//		if(query.record().contains("DATANAME")==true){
	//			item.NGName = query.record().value("DATANAME").toString();
	//		}
	//		if(query.record().contains("LASTUPDATED")==true){
	//			item.LastUpdated = query.record().value("LASTUPDATED").toDateTime();
	//		}
	//		if(query.record().contains("DATAVERSION")==true){
	//			item.DataVersion = query.record().value("DATAVERSION").toInt();
	//		}
	//		if(query.record().contains("NGCOLOR")==true){
	//			QByteArray	ColorBlob	=query.value(query.record().indexOf("NGCOLOR")).toByteArray();
	//			QBuffer	ColorBuff(&ColorBlob);
	//			ColorBuff.open(QIODevice::ReadWrite);
	//			::Load(&ColorBuff, item.NGColor);
	//		}
	//		if(query.record().contains("MARKSHAPE")==true){
	//			item.NGShape = (LibNGTypeItem::NGShapeType)(query.record().value("MARKSHAPE").toInt());
	//		}
	//		if(query.record().contains("NEXTWAITINGTIME")==true){
	//			item.NextJumpMilisec = query.record().value("NEXTWAITINGTIME").toInt();
	//		}
	//		if(query.record().contains("PRIORITY")==true){
	//			item.Priority = query.record().value("PRIORITY").toInt();
	//		}
	//		if(query.record().contains("BLINK")==true){
	//			item.Blink = query.record().value("BLINK").toBool();
	//		}
	//		//if(query.record().contains("SPECIFIEDDATA")==true){
	//		//	query.record().value("SPECIFIEDDATA");
	//		//}
	//		if(query.record().contains("TYPEUNIQUEID")==true){
	//			item.TypeUniqueCode = query.record().value("TYPEUNIQUEID").toInt();
	//		}
	//			//LIBTYPE                         INTEGER Not Null
	//			//LIBID                           INTEGER Not Null
	//			//NGTYPEID                        INTEGER Not Null
	//			//DATANAME                        VARCHAR(32) Nullable
	//			//LASTUPDATED                     TIMESTAMP Nullable
	//			//DATAVERSION                     INTEGER Nullable
	//			//NGCOLOR                         BLOB segment 80, subtype BINARY Nullable
	//			//MARKSHAPE                       SMALLINT Nullable
	//			//NEXTWAITINGTIME                 INTEGER Nullable
	//			//PRIORITY                        SMALLINT Nullable
	//			//BLINK                           SMALLINT Nullable
	//			//SPECIFIEDDATA                   BLOB segment 80, subtype BINARY Nullable
	//			//TYPEUNIQUEID                    INTEGER Not Null

	//		LibNGTypePack.append(item);
	//	}
		if(PhaseCode==0){
			RelationMasterList MasterListDim[100];

			int	RelationCode=GetLayersBase()->SQLGetRelationCode(MasterCode);
			if(iPhaseNumb==0){
				iPhaseNumb=1;
			}
			int	TotalPhaseNumb=iPhaseNumb;
			
			if(addMode==true){
				TotalPhaseNumb += GetParamGlobal()->PhaseNumb;
			}
			//if(RelationCode!=-1){
			//	int	MasterListDimCount=GetLayersBase()->SQLSearchMasterCode(RelationCode ,MasterListDim ,100);

			//	for(int i=0;i<MasterListDimCount;i++){
			//		TotalPhaseNumb+=GetPhaseNumb(MasterListDim[i].MasterCode);
			//	}
			//}
			GetParamGlobal()->DotPerLine=iDotPerLine;
			GetParamGlobal()->MaxLines	=iMaxLines;
			GetLayersBase()->ResetSize();

			GetParamGlobal()->PhaseNumb	=TotalPhaseNumb;
			GetParamGlobal()->LayerNumb	=iLayerNumb;
			GetParamGlobal()->PageNumb	=iPageNumb;

			LayersBase *base = GetLayersBase();
			base->InitialAfterParamLoaded();
			base->InitialCreatePages(GetLayersBase()->GetEntryPoint());
			base->ReallocAlgorithm();
			base->InitialAllocExecuterDim();
			base->InitialResult();

			//base->ExecuteInitialAfterEdit(GetLayersBase()->GetEntryPoint());
			//base->WaitAllAcknowledged(60);
		}

		// アウトラインオフセット変更
		OutlineOffsetInBlob outlineBlob(GetLayersBase());
		ret = GetLayersBase()->GetDatabaseLoader()->G_SQLLoadOutlineOfset(GetLayersBase()->GetDatabase(), iMachineID, &outlineBlob);

		if(ret==false){
			return false;
		}

		for(int phase=0; phase<GetLayersBase()->GetPhaseNumb(); phase++){
			for(int page=0; page<GetLayersBase()->GetPageNumb(); page++){
				int x = outlineBlob.GetData(phase, page).Dx;
				int y = outlineBlob.GetData(phase, page).Dy;
				GetLayersBase()->GetPhaseData()[phase]->GetPageData(page)->GetOutlineOffset()->x = x;
				GetLayersBase()->GetPhaseData()[phase]->GetPageData(page)->GetOutlineOffset()->y = y;
			}
		}
	}
	return ret;
}

QImage	ReviewPIBase::GetMasterWholeImage(Review::SideType side, int phase, int width, int height ,double ZoomImageFromFile)
{
	QList<QImage> *TargetPageImages;
	QSize TargetWholeImgSize;
	QList<QPoint> TargetWholeOutlines;
	QList<QPoint> TargetWholeImgDrawOutlines;

	if(getMasterWholePageImageListPtr(side)->count()<=phase){
		return QImage();
	}
	TargetPageImages = getMasterWholePageImageListPtr(side, phase);
	TargetWholeImgSize = getMasterWholeImageSize(side, phase);
	TargetWholeOutlines = getMasterWholePageOutlineList(side, phase);
	TargetWholeImgDrawOutlines = getMasterWholeImgDrawPoints(side, phase);

	//switch(side){
	//case Review::Front:
	//	if(FrontPageImages.count()<=phase){
	//		return QImage();
	//	}
	//	TargetPageImages = &FrontPageImages[phase];
	//	TargetWholeImgSize = FrontMasterWholeImgSize[phase];
	//	TargetWholeOutlines = FrontOutline[phase];
	//	TargetWholeImgDrawOutlines = &FrontMasterWholeImgDrawPoints[phase];
	//	AppendDebugLog(/**/"[Front Image Buffer Update]");
	//	break;
	//case Review::Back:
	//	if(BackPageImages.count()<=phase){
	//		return QImage();
	//	}
	//	TargetPageImages = &BackPageImages[phase];
	//	TargetWholeImgSize = BackMasterWholeImgSize[phase];
	//	TargetWholeOutlines = BackOutline[phase];
	//	TargetWholeImgDrawOutlines = &BackMasterWholeImgDrawPoints[phase];
	//	AppendDebugLog(/**/"[Back Image Buffer Update]");
	//	break;
	//default:
	//	return QImage();
	//}

	if(TargetPageImages->isEmpty()){
		return QImage();
	}

	bool isNull = true;
	for(int i=0; i<TargetPageImages->count(); i++){
		if((*TargetPageImages)[i].isNull()==false){
			isNull = false;
			break;
		}
	}

	if(isNull==true){
		return QImage();
	}

	AppendDebugLog( QString(/**/"Size(%1,%2)").arg(width).arg(height) );

	QImage image(width, height, QImage::Format_RGB32);
	image.fill(QColor(Qt::black).rgb());

	QSize tmp = TargetWholeImgSize;
	double zoomRate;
	if(width>=0 || height>=0){
		tmp.scale(width, height, Qt::KeepAspectRatio);
		zoomRate = tmp.width() / (double)TargetWholeImgSize.width();
	}else{
		zoomRate = 1.0; // 100%
	}

	AppendDebugLog( QString(/**/"Scaling to %1").arg(zoomRate) );

	QPainter painter;
	painter.begin(&image);
	for(int i=0; i<TargetPageImages->count(); i++){
		double	Z=zoomRate*ZoomImageFromFile*getMasterImageNormalizeZoomRate();
		QImage img = (*TargetPageImages)[i].scaled((*TargetPageImages)[i].size()*Z, Qt::KeepAspectRatio);
		img.save("C:\\Tmp\\FrontImage.bmp","BMP");

		//(*TargetPageImages)[i].scaled(QSize(500, 500), Qt::KeepAspectRatio).save("Test.png");

		//if(!img.save("test.jpg", "JPG")){
		//	//QMessageBox::warning(NULL, "error", QString("test.jpg save is failed.\n(%1,%2)").arg((*TargetPageImages)[i].width()*zoomRate).arg((*TargetPageImages)[i].height()*zoomRate));
		//}


		painter.drawImage( TargetWholeImgDrawOutlines[i].x()*zoomRate, TargetWholeImgDrawOutlines[i].y()*zoomRate,// 貼り付け位置
			img);

		//(*TargetPageImages)[i].save(QString("ForntWholePage-%1.jpg").arg(i), "JPG");
		//QMessageBox::about(NULL, "OutlinePos", QString("%1,%2").arg((*TargetWholeImgDrawOutlines)[i].x()).arg((*TargetWholeImgDrawOutlines)[i].y()));

		AppendDebugLog( QString(/**/"TopLeft(%1, %2), ImageWH(%3, %4)").arg(TargetWholeImgDrawOutlines[i].x()*zoomRate).arg(TargetWholeImgDrawOutlines[i].y()*zoomRate)
			.arg((*TargetPageImages)[i].width()*zoomRate).arg((*TargetPageImages)[i].height()*zoomRate));

	}
	painter.end();

	//switch(side){
	//case Review::Front:
	//	image.save( "FrontImageOnDisplay.jpg", "JPG" );
	//	AppendDebugLog("Front Image on display is saved.");
	//	break;
	//case Review::Back:
	//	image.save( "BackImageOnDisplay.jpg", "JPG" );
	//	AppendDebugLog("Back Image on display is saved.");
	//	break;
	//default:
	//	AppendDebugLog("This is uncurrent side.");
	//	return QImage();
	//}

	return image;
}

QImage ReviewPIBase::GetMasterImagePiece(Review::SideType side, int phase, int page, int x, int y, int width, int height)
{
	QList<QImage> TargetPageImages;// phaseの各ページ画像
	QList<QPoint> TargetWholeOutlines;// 各ページのアウトライン情報
	MasterDataInfo MInfo = getMasterInfo(side);

	if(getMasterWholePageImageList(side).isEmpty()){
		return QImage();
	}
	TargetPageImages = getMasterWholePageImageList(side, phase);
	TargetWholeOutlines = getMasterWholePageOutlineList(side, phase);

	//switch(side){
	//case Review::Front:
	//	if(FrontPageImages.isEmpty()){
	//		return QImage();
	//	}
	//	TargetPageImages = &FrontPageImages[phase];
	//	TargetWholeOutlines = FrontOutline[phase];
	//	break;
	//case Review::Back:
	//	if(BackPageImages.isEmpty()){
	//		return QImage();
	//	}
	//	TargetPageImages = &BackPageImages[phase];
	//	TargetWholeOutlines = BackOutline[phase];
	//	break;
	//default:
	//	return QImage();
	//}

	// 戻り画像
	QImage image(width, height, QImage::Format_RGB32);

	QPainter painter;
	painter.begin(&image);

	QRect pieceRect(TargetWholeOutlines[page].x() + x, TargetWholeOutlines[page].y() + y, width, height);

	QList<QPoint> ShiftOutlines = TargetWholeOutlines;
	for(int i=0; i<ShiftOutlines.count(); i++){
		ShiftOutlines[i] -= pieceRect.topLeft();// 注目ページを基準
	}
	for(int i=0; i<ShiftOutlines.count(); i++){
		ShiftOutlines[i] /= getMasterImageNormalizeZoomRate();
	}
	QRect viewPort(0,0,width,height);
	QImage pieceImg = TargetPageImages[page].copy(x / getMasterImageNormalizeZoomRate(), y / getMasterImageNormalizeZoomRate(), width / getMasterImageNormalizeZoomRate(), height / getMasterImageNormalizeZoomRate());
	painter.drawImage(0, 0, pieceImg.scaled(pieceImg.size() * getMasterImageNormalizeZoomRate()));

	//for(int i=0; i<ShiftOutlines.count(); i++){
	//	QRect rect(-ShiftOutlines[i], QSize(width, height) / getMasterImageNormalizeZoomRate());
	//	QRect drawRect = QRect(QPoint(0,0),QSize(width, height) / getMasterImageNormalizeZoomRate()).intersected(rect);
	//	if(drawRect.isValid()==false){
	//		continue;
	//	}
	//	painter.drawImage( drawRect.x(), drawRect.y(), TargetPageImages[i].copy(rect) );
	//}
	painter.end();

	return image;
}

QImage ReviewPIBase::GetMasterImagePiece(Review::SideType side, int phase, int x, int y, int width, int height)
{
	QList<QImage> TargetPageImages;// phaseの各ページ画像
	QList<QPoint> TargetWholeOutlines;// 各ページのアウトライン情報

	TargetPageImages = getMasterWholePageImageList(side, phase);
	TargetWholeOutlines = getMasterWholeImgDrawPoints(side, phase);

	//switch(side){
	//case Review::Front:
	//	if(FrontPageImages.isEmpty()){
	//		return QImage();
	//	}
	//	TargetPageImages = &FrontPageImages[phase];
	//	TargetWholeOutlines = FrontMasterWholeImgDrawPoints[phase];
	//	break;
	//case Review::Back:
	//	if(BackPageImages.isEmpty()){
	//		return QImage();
	//	}
	//	TargetPageImages = &BackPageImages[phase];
	//	TargetWholeOutlines = BackMasterWholeImgDrawPoints[phase];
	//	break;
	//default:
	//	return QImage();
	//}

	// 戻り画像
	QImage image(width/getMasterImageNormalizeZoomRate(), height/getMasterImageNormalizeZoomRate(), QImage::Format_RGB32);
	image.fill(0);

	QPainter painter;
	painter.begin(&image);
	for(int i=0; i<TargetPageImages.count(); i++){
		//QImage	TmpImg=TargetPageImages[i].copy(QRect(x/getMasterImageNormalizeZoomRate(),y/getMasterImageNormalizeZoomRate(),width/getMasterImageNormalizeZoomRate(),height/getMasterImageNormalizeZoomRate()));

		int	x1=(x-TargetWholeOutlines[i].x())/getMasterImageNormalizeZoomRate();
		int	y1=(y-TargetWholeOutlines[i].y())/getMasterImageNormalizeZoomRate();
		int	w=width/getMasterImageNormalizeZoomRate();
		int	h=height/getMasterImageNormalizeZoomRate();
		if(0<=(x1+w) && 0<=(y1+h)){
			QImage	TmpImg=TargetPageImages[i].copy(QRect(x1,y1,w,h));
			//painter.drawImage( TargetWholeOutlines[i].x()/getMasterImageNormalizeZoomRate(), TargetWholeOutlines[i].y()/getMasterImageNormalizeZoomRate(), TmpImg);
			painter.drawImage( 0, 0, TmpImg);
		}
	}
	painter.end();

	return image;
}

int	ReviewPIBase::GetPhaseNumb(int masterCode)
{
	if(GetLayersBase()->GetDatabaseLoader()){
		int32		iMachineIDFromMaster;
		XDateTime	iRegTime;
		QString		iMasterName;
		QString		iRemark;
		int32		iVersion;
		XDateTime	iLastEditTime;
		int32		iCategoryID;
		int16		iMasterType;
		int			iDotPerLine;
		int			iMaxLines;
		int			iLayerNumb;
		int			iPageNumb;
		int			iPhaseNumb;
		int32		iLibFolderID;
		int32 		iThresholdLevelID;
		int32 		iThresholdLevelParentID;

		bool	ret=GetLayersBase()->GetDatabaseLoader()->G_SQLLoadMasterData2(GetLayersBase()->GetDatabase()
							,masterCode
							,iMachineIDFromMaster
							,iRegTime
							,iMasterName ,iRemark
							,iVersion
							,iLastEditTime
							,iCategoryID
							,iMasterType
							,iDotPerLine
							,iMaxLines
							,iLayerNumb
							,iPageNumb
							,iPhaseNumb
							,iLibFolderID
							,iThresholdLevelID
							,iThresholdLevelParentID);

		if(ret==true){
			if(iPhaseNumb==0)
				return 1;
			return iPhaseNumb;
		}
	}
	return 0;
}

bool ReviewPIBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	return true;
}

InsLibraryList ReviewPIBase::getInsLibraryList(Review::SideType side, QString Ral) const
{
	return getInsLibraryList(side, Ral);
}

InsLibraryItem ReviewPIBase::getInsLibraryItem(Review::SideType side, QString Ral, int LC) const
{
	InsLibraryItem ret;

	InsLibraryList list = getInsLibraryList(side, Ral);

	for(int i=0; i<list.count(); i++){
		if(list[i].LibCode == LC){
			ret = list[i];
			break;
		}
	}

	return ret;
}

InsLibraryItem::TypeNameTag ReviewPIBase::getInsLibraryItemTypeNameTag(Review::SideType side, QString Ral, int LC, int TC) const
{
	return getInsLibSearchHash(side)[Ral][LC][TC];
}

void ReviewPIBase::updateInsLibSearchHash(Review::SideType side)
{
	InsLibSearchHash hash;

	hash.clear();

	QList<QString> RalList = getInsLibHash(side).uniqueKeys();

	for(int i=0; i<RalList.count(); i++){
		InsLibraryList ItemList = getInsLibHash(side).values(RalList[i]);
		for(int j=0; j<ItemList.count(); j++){
			for(int k=0; k<ItemList[j].TypeNameList.count(); k++){
				hash[RalList[i]][ItemList[j].LibCode][ItemList[j].TypeNameList[k].TCode] = ItemList[j].TypeNameList[k];
			}
		}
	}

	setInsLibSearchHash(side, hash);

	//if(side==Review::Front){// 表側
	//	// 前状態のハッシュをクリア
	//	FrontInsLibSearchHash.clear();
	//	QList<QString> RalList;

	//	RalList = FrontInsLibHash.uniqueKeys();
	//	for(int i=0; i<RalList.count(); i++){
	//		QList<InsLibraryItem> ItemList = FrontInsLibHash.values(RalList[i]);
	//		for(int j=0; j<ItemList.count(); j++){
	//			for(int k=0; k<ItemList[j].TypeNameList.count(); k++){
	//				FrontInsLibSearchHash[RalList[i]][ItemList[j].LibCode][ItemList[j].TypeNameList[k].TCode] = ItemList[j].TypeNameList[k];
	//			}
	//		}
	//	}
	//}else{// 裏側
	//	BackInsLibSearchHash.clear();
	//	QList<QString> RalList;

	//	RalList = BackInsLibHash.uniqueKeys();
	//	for(int i=0; i<RalList.count(); i++){
	//		QList<InsLibraryItem> ItemList = BackInsLibHash.values(RalList[i]);
	//		for(int j=0; j<ItemList.count(); j++){
	//			for(int k=0; k<ItemList[j].TypeNameList.count(); k++){
	//				BackInsLibSearchHash[RalList[i]][ItemList[j].LibCode][ItemList[j].TypeNameList[k].TCode] = ItemList[j].TypeNameList[k];
	//			}
	//		}
	//	}
	//}
}

PCEList ReviewPIBase::getPCEMatch(Review::SideType side, int MasterID, int page, const QStringList &PCENameList) const
{
	PCEList retList;
	PCEList list = getPCEList(side);

	if(PCENameList.isEmpty()==false){
		for(int i=0; i<list.count(); i++){
			if(PCENameList.contains(list[i].pieceName())==true){
				retList.append(list[i]);
			}
		}
	}
	return retList;

	//for(int i=0; i<list.count(); i++){
	//	if(list[i].isValid()==false){
	//		continue;
	//	}

	//	PCEItem::AreaType type = list[i].areaType();

	//	if(type==PCEItem::Rect){
	//		QList<QPoint> pList = list[i].areaPointList();
	//		QPoint p1(pList[0].x(), pList[0].y()), p2(pList[1].x(), pList[1].y());
	//		
	//		QRect rect = QRect(p1, p1).unite(QRect(p2,p2));

	//		if(rect.contains(x, y)==true){
	//			retList.append(list[i]);
	//		}
	//		
	//	}else if(type==PCEItem::Ellipse){
	//		QList<QPoint> pList = list[i].areaPointList();
	//		QPoint p1(pList[0].x(), pList[0].y()), p2(pList[1].x(), pList[1].y());
	//		
	//		QRect rect = QRect(p1, p1).unite(QRect(p2,p2));

	//		QRegion ellipse(rect, QRegion::Ellipse);
	//		if(ellipse.contains(QPoint(x, y))==true){
	//			retList.append(list[i]);
	//		}

	//	}else if(type==PCEItem::Polygon){
	//		QVector<QPoint> pList = list[i].areaPointList().toVector();
	//		QPolygon polygon(pList);

	//		if(polygon.containsPoint(QPoint(x, y), Qt::FillRule::OddEvenFill)==true){
	//			retList.append(list[i]);
	//		}

	//	}else{
	//		// no work : include PCEItem::AreaType::None
	//	}
	//}

	//return retList;
}

Review::SideType ReviewPIBase::getSideType(const NGNailItemRef &refItem) const
{
	if(getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)->indexOf(refItem)!=-1){
		return getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)->getWhitchSide(refItem);
	}else{
		const OrganizedHistoryList &list = getOrganizedHistoryList();
		for(int i=0; i<list.count(); i++){
			if(list[i].indexOf(refItem)!=-1){
				return list[i].getWhitchSide(refItem);
			}
		}
	}
	return Review::NoSide;
}

Review::SideType ReviewPIBase::getCurrentSideType() const
{
	if(getRoundCurrentNGNailIterator(Review::CurrentPos)==NGNailList::Iterator()){
		return Review::Front;
	}else{
		NGNailList::Iterator it = getRoundCurrentNGNailIterator(Review::CurrentPos);
		if(it!=NGNailList::Iterator()){
			return getSideType(*it);
		}else{
			return Review::Front;
		}
	}
}

void ReviewPIBase::deleteHistoryNGImageReader(Review::SideType side)
{
	HistoryList *list = &getHistoryList(side);
	#pragma omp parallel
	{
		HistoryList::Iterator it;
		#pragma omp single private(it)
		for(it=list->begin(); it!=list->end(); it++){
			#pragma omp task
			{
				it->deleteReader();
			}
		}
	}
	//switch(side){
	//case Review::Front:
	//	#pragma omp for
	//	for(int i=0; i<FrontHistoryList.count(); i++){
	//		FrontHistoryList[i].deleteReader();
	//		//for(int j=0; j<FrontHistoryList[i].getNGNails().count(); j++){
	//		//	FrontHistoryList[i].NGNails[j].deleteReader();
	//		//}
	//	}
	//	break;
	//case Review::Back:
	//	#pragma omp for
	//	for(int i=0; i<BackHistoryList.count(); i++){
	//		BackHistoryList[i].deleteReader();
	//		//for(int j=0; j<BackHistoryList[i].getNGNails().count(); j++){
	//		//	BackHistoryList[i].NGNails[j].deleteReader();
	//		//}
	//	}
	//	break;
	//default:
	//	break;
	//}
}

void ReviewPIBase::OrganizeHistoryList(void)
{
	QList<OrganizedHistoryItem> Temp;
	
	//qSort(FrontHistoryList.begin(), FrontHistoryList.end());// ID順でソート
	//qSort(BackHistoryList.begin(), BackHistoryList.end());// ID順でソート

	qSort(getHistoryList(Review::Front));
	qSort(getHistoryList(Review::Back));

	for(QList<HistoryItem>::ConstIterator itf=getHistoryList(Review::Front).constBegin(), itb=getHistoryList(Review::Back).constBegin(); ;){
		if(itf==getHistoryList(Review::Front).constEnd()){
			while(itb!=getHistoryList(Review::Back).constEnd()){
				OrganizedHistoryItem item;
				item.setHistoryItem(&itb.i->t(), Review::Back);
				item.setSide(Review::BackOnly);
				Temp.append(item);
				itf++;
				itb++;
			}
			break;
		}else if(itb==getHistoryList(Review::Back).constEnd()){
			while(itf!=getHistoryList(Review::Front).constEnd()){
				OrganizedHistoryItem item;
				item.setHistoryItem(&itf.i->t(), Review::Front);
				item.setSide(Review::FrontOnly);
				Temp.append(item);
				itf++;
			}
			break;
		}

		if(itf->InspectID() == itb->InspectID()){ // 同じ時
			OrganizedHistoryItem item;
			item.setHistoryItem(&itf.i->t(), Review::Front);
			item.setHistoryItem(&itb.i->t(), Review::Back);
			item.setSide(Review::Both);
			Temp.append(item);
			itf++;
			itb++;
		}else if(itf->InspectID() < itb->InspectID()){
			OrganizedHistoryItem item;
			item.setHistoryItem(&itf.i->t(), Review::Front);
			item.setSide(Review::FrontOnly);
			Temp.append(item);
			itf++;
		}else{
			OrganizedHistoryItem item;
			item.setHistoryItem(&itb.i->t(), Review::Back);
			item.setSide(Review::BackOnly);
			Temp.append(item);
			itb++;
		}
	}

	setOrganizedHistoryList(Temp);

	sortHistoryList();
	sortNGNailList();

	setCurrentOrganizedHistory(Review::First);
}

OrganizedHistoryList::Iterator ReviewPIBase::getOrganizedHistoryIterator(int GlobalIndex)
{
	if(GlobalIndex<0 || GlobalIndex>=getOrganizedHistoryList().count())return OrganizedHistoryList::Iterator();

	return (static_cast<OrganizedHistoryList::Iterator>(getOrganizedHistoryIteratorBegin() + GlobalIndex));
}

OrganizedHistoryList::Iterator ReviewPIBase::getOrganizedHistoryIteratorBegin()
{
	return m_HistoryPack.begin();
}

OrganizedHistoryList::Iterator ReviewPIBase::getOrganizedHistoryIteratorEnd()
{
	return m_HistoryPack.end();
}

void ReviewPIBase::setCurrentOrganizedHistory(Review::ListLocate locate, int GlobalIndex)
{
	switch(locate){
	case Review::First:
		setRoundCurrentOrganizedHistoryIterator(
			OrganizedHistoryList::Iterator(),
			getOrganizedHistoryIterator(0),
			getOrganizedHistoryIterator(1)
			);
		break;
	case Review::End:
		setRoundCurrentOrganizedHistoryIterator(
			getOrganizedHistoryIterator(getOrganizedHistoryList().count()-2),
			getOrganizedHistoryIterator(getOrganizedHistoryList().count()-1),
			OrganizedHistoryList::Iterator()
			);
		break;
	case Review::Manual:
		setRoundCurrentOrganizedHistoryIterator(
			getOrganizedHistoryIterator(GlobalIndex-1),
			getOrganizedHistoryIterator(GlobalIndex),
			getOrganizedHistoryIterator(GlobalIndex+1)
			);
		break;
	default:
		clearRoundCurrentOrganizedHistoryIterator();
		clearRoundCurrentNGNailIterator();
		break;
	}
}

void ReviewPIBase::setCurrentOrganizedHistory(int GlobalIndex)
{
	setCurrentOrganizedHistory(Review::ListLocate::Manual, GlobalIndex);
}

void ReviewPIBase::setCurrentNGNail(Review::ListLocate locate, int GlobalIndex)
{
	if(getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)!=OrganizedHistoryList::Iterator()){
		int currentNGNailCount = getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)->getNGNailCount();
		switch(locate){
		case Review::First:
			setRoundCurrentNGNailIterator(
				NGNailList::Iterator(),
				getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)->getNGNailItemIterator(0),
				getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)->getNGNailItemIterator(1)
				);
			break;
		case Review::End:
			setRoundCurrentNGNailIterator(
				getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)->getNGNailItemIterator(currentNGNailCount-2),
				getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)->getNGNailItemIterator(currentNGNailCount-1),
				NGNailList::Iterator()
				);
			break;
		case Review::Manual:
			setRoundCurrentNGNailIterator(
				getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)->getNGNailItemIterator(GlobalIndex-1),
				getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)->getNGNailItemIterator(GlobalIndex),
				getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)->getNGNailItemIterator(GlobalIndex+1)
				);
			break;
		default:
			clearRoundCurrentNGNailIterator();
			break;
		}
	}else{
		clearRoundCurrentNGNailIterator();
	}
}

void ReviewPIBase::setCurrentNGNail(int GlobalIndex)
{
	setCurrentNGNail(Review::ListLocate::Manual, GlobalIndex);
}

void ReviewPIBase::loadNGImageRoundCurrent(void)
{
	if(getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)==OrganizedHistoryList::Iterator()){
		return;
	}
	loadNGImage( getOrganizedHistoryList().indexOf(*getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)) );
}

void ReviewPIBase::loadNGImage(int OrgHistroyIndex)
{
	if(getOrganizedHistoryList().isEmpty() || OrgHistroyIndex<0 || getOrganizedHistoryList().count()<=OrgHistroyIndex){
		return;
	}

	//QTime time = QTime::currentTime();

	//time.start();

	//qDebug() << "Start Thread Load";

	//if(HistoryPack[OrgHistroyIndex].hasFront()==true){
	//	#pragma omp for
	//	for(int i=0; i<HistoryPack[OrgHistroyIndex].getFront()->NGNails.count(); i++){
	//		if(HistoryPack[OrgHistroyIndex].getFront()->NGNails[i].isLoaded()==false// 読み込まれていなく、なおかつ読み込み中でない場合読み込みを開始
	//			&& HistoryPack[OrgHistroyIndex].getFront()->NGNails[i].NGImage->isRunning()==false){
	//			HistoryPack[OrgHistroyIndex].getFront()->NGNails[i].loadImage();
	//		}
	//	}
	//}

	//if(HistoryPack[OrgHistroyIndex].hasBack()==true){
	//	#pragma omp for
	//	for(int i=0; i<HistoryPack[OrgHistroyIndex].getBack()->NGNails.count(); i++){
	//		if(HistoryPack[OrgHistroyIndex].getBack()->NGNails[i].isLoaded()==false// 読み込まれていなく、なおかつ読み込み中でない場合読み込みを開始
	//			&& HistoryPack[OrgHistroyIndex].getBack()->NGNails[i].NGImage->isRunning()==false){
	//			HistoryPack[OrgHistroyIndex].getBack()->NGNails[i].loadImage();
	//		}
	//	}
	//}

//#pragma omp parallel
	{
	// 前の削除
	//qDebug() << "unload forword";
		//#pragma omp for
		for(int t=0; t<OrgHistroyIndex-getProperty().PreLoadNGImageLength; t++){
			//qDebug() << t;
			OrganizedHistoryList::Iterator outIt = getOrganizedHistoryIterator(t);
			if(outIt!=OrganizedHistoryList::Iterator()){
				if(outIt->hasFront()==true){
					//#pragma omp for
					for(int i=0; i<outIt->getFront()->getNGNails().count(); i++){
						//if(outIt->getFront()->NGNails[i].NGImage->isRunning()==true){
						//	outIt->getFront()->NGNails[i].NGImage->terminate();
						//	while(!outIt->getFront()->NGNails[i].NGImage->isFinished()){}
						//}
						outIt->getFront()->getNGNails()[i].unloadImage();
					}
				}
				if(outIt->hasBack()==true){
					//#pragma omp for
					for(int i=0; i<outIt->getBack()->getNGNails().count(); i++){
						//if(outIt->getBack()->NGNails[i].NGImage->isRunning()==true){
						//	outIt->getBack()->NGNails[i].NGImage->terminate();
						//	while(!outIt->getBack()->NGNails[i].NGImage->isFinished()){}
						//}
						outIt->getBack()->getNGNails()[i].unloadImage();
					}
				}
			}
		}
	// 現在周辺のロード
	//qDebug() << "load round current";
		//#pragma omp for
		for(int t=OrgHistroyIndex-getProperty().PreLoadNGImageLength; t<OrgHistroyIndex+getProperty().PreLoadNGImageLength; t++){
			//qDebug() << t;
			OrganizedHistoryList::Iterator nextIt = getOrganizedHistoryIterator(t);
			if(nextIt!=OrganizedHistoryList::Iterator()){
				if(nextIt->hasFront()==true){
					//#pragma omp for
					//for(int i=0; i<nextIt->getFront()->NGNails.count(); i++){
					//	if(nextIt->getFront()->NGNails[i].isLoaded()==false// 読み込まれていなく、なおかつ読み込み中でない場合読み込みを開始
					//	&& nextIt->getFront()->NGNails[i].NGImage->isRunning()==false){
					//		nextIt->getFront()->NGNails[i].loadImage();
					//	}
					//}
					nextIt->getFront()->loadNGImage();
				}
				if(nextIt->hasBack()==true){
					//#pragma omp for
					//for(int i=0; i<nextIt->getBack()->NGNails.count(); i++){
					//	if(nextIt->getBack()->NGNails[i].isLoaded()==false// 読み込まれていなく、なおかつ読み込み中でない場合読み込みを開始
					//		&& nextIt->getBack()->NGNails[i].NGImage->isRunning()==false){
					//		nextIt->getBack()->NGNails[i].loadImage();
					//	}
					//}
					nextIt->getBack()->loadNGImage();
				}
			}
		}
	// 先のアンロード
	//qDebug() << "unload reword";
		//#pragma omp for
		for(int t=OrgHistroyIndex+getProperty().PreLoadNGImageLength; t<getOrganizedHistoryList().count(); t++){
			//qDebug() << t;
			OrganizedHistoryList::Iterator outIt = getOrganizedHistoryIterator(t);
			if(outIt!=OrganizedHistoryList::Iterator()){
				if(outIt->hasFront()==true){
					//#pragma omp for
					for(int i=0; i<outIt->getFront()->getNGNails().count(); i++){
						//if(outIt->getFront()->NGNails[i].NGImage->isRunning()==true){
						//	outIt->getFront()->NGNails[i].NGImage->terminate();
						//	while(!outIt->getFront()->NGNails[i].NGImage->isFinished()){}
						//}
						outIt->getFront()->getNGNails()[i].unloadImage();
					}
				}
				if(outIt->hasBack()==true){
					//#pragma omp for
					for(int i=0; i<outIt->getBack()->getNGNails().count(); i++){
						//if(outIt->getBack()->NGNails[i].NGImage->isRunning()==true){
						//	outIt->getBack()->NGNails[i].NGImage->terminate();
						//	while(!outIt->getBack()->NGNails[i].NGImage->isFinished()){}
						//}
						outIt->getBack()->getNGNails()[i].unloadImage();
					}
				}
			}
		}
	}


	//qDebug() << "End Thread Load";

	//qDebug() << "Thread moding elapsed is " << time.elapsed() << "[ms]";
}

void ReviewPIBase::slot_propertyModified()
{
	ReviewStructureProperty pro;
	getPropertyFromUi(pro);
	setProperty(pro);
	getProperty().save();
}


QString ReviewPIBase::convertedSaveNGFileName(Review::SideType side, const OrganizedHistoryList::Iterator &hIt, NGNailList::Iterator ngIt) const
{
	QString ret = getSaveNGImageFileNameFormat();

	MasterDataInfo MInfo = getMasterInfo(side);

	ret.replace("%m", QString::number(MInfo.MasterCode));
	ret.replace("%M", MInfo.MasterName);

	ret.replace("%l", getCurrentLotInfo(side).LotName);
	ret.replace("%i", QString::number(hIt->getInspectID()));
	ret.replace("%S", Review::toString(side));

	int row = hIt->indexOf(ngIt->getNGNailItemRef());
	ret.replace("%n", QString::number(row+1));

	int srow;
	if(side==Review::Back){
		// 表がある場合
		if(hIt->hasFront()==true){
			// 表の数
			int frontNGCount = hIt->getFront()->getNGNails().count();
			// 表の数以上なら裏確定
			if(row>=frontNGCount){
				srow = row - frontNGCount;// 裏の連番
			}else{
				srow = row;// そのまま
			}
		}else{
			srow = row;// そのまま
		}
	}else{
		srow = row;// そのまま
	}
	ret.replace("%N", QString::number(srow+1));

		//<< QPair<QString, QString>("%m", "MasterID")
		//<< QPair<QString, QString>("%M", "MasterName")
		//<< QPair<QString, QString>("%l", "LotName")
		//<< QPair<QString, QString>("%i", "InspectionID")
		//<< QPair<QString, QString>("%S", "NGSide; \"Front\" or \"Back\"")
		//<< QPair<QString, QString>("%n", "NG Number(same as row)")
		//<< QPair<QString, QString>("%N", "NG Number(index on side)")
		//<< QPair<QString, QString>("/", "Directory Separator");
	
	for(int i=0; i<ret.count(); i++){
		if(ret[i].cell()==QChar('\\').cell()){
			ret[i] = QChar('/');
		}
	}
	while(true){
		QString searchStr = /**/"//";
		int index = ret.indexOf(searchStr);
		if(index==-1)break;

		ret.replace(index, searchStr.length(), "/Empty/");
	}

	return ret;
}

LotInfoItem	ReviewPIBase::XML_GetLotInfo(const QString &TableName)
{
	LotInfoItem ret;
	QRegularExpression exp(QString("(") + QDir::separator() + "d+)-(" + QDir::separator() + "d+)/.+");
	if(exp.exactMatch(TableName)==false){
		return ret;
	}

	int MachineCode = exp.cap(1).toInt();
	int MasterCode = exp.cap(2).toInt();

	ret.MasterCode = MasterCode;
	ret.MachineCode = MachineCode;
	ret.TableName = TableName;
	
	QString qStr = QString(/**/"SELECT LOTNAME,REMARK FROM INSPECTIONLOT WHERE MASTERCODE=%1 AND IDNAME='%2'").arg(MasterCode).arg(ret.Filename().toUpper());
	QSqlQuery query(qStr);

	if(query.next()){
		ret.LotName = query.value(0).toString();
		ret.Remark = query.value(1).toString();
		return ret;
	}

	XMLOperationHandle *hdl = getXMLServerHandle()->OpenXMLOperation(TableName);
	if(hdl!=NULL){
		QString retStr;
		hdl->SelectFirst(/**/"<* *>*</*>", /**/"<LOT */>", /**/"", retStr);
		if(retStr!=/**/"<BOF/>"){
			LotSingleParser parser;
			if(parser.setContent(retStr)==true){
				ret.LotName = parser.getLotName();
			}else{
				ret.LotName = "**!Error!**";
			}
		}else{
			ret.LotName = "(irregularity)";
		}
	}else{
		ret.LotName = /**/"**!Error!**";
	}

	getXMLServerHandle()->CloseXMLOperation(hdl);
	delete hdl;

	return ret;
}

void ReviewPIBase::loadOutlineOffset(Review::SideType side, int MachineID, int MasterCode)
{
	// 保存先
	QList<QList<QPoint> > *TargetOutlines = getMasterWholePageOutlineListPtr(side);

	// データベースからアウトライン情報を取得
	CmdReqOutlineOffset	RCmd(GetLayersBase());
	RCmd.MasterCode=MasterCode;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Review" ,/**/"SetOutlineOffset" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&RCmd);
	}
	if(RCmd.Result==true){
		// アウトライン情報を格納
		(*TargetOutlines) = QVector<QList<QPoint> >(RCmd.Data.GetPhaseCount()).toList();
		for(int phase=0; phase<TargetOutlines->count(); phase++){
			(*TargetOutlines)[phase] = QVector<QPoint>(RCmd.Data.GetPageCount(phase)).toList();
			for(int page=0; page<(*TargetOutlines)[phase].count(); page++){
				(*TargetOutlines)[phase][page] = QPoint(RCmd.Data.GetData(phase, page).Dx, RCmd.Data.GetData(phase, page).Dy);
			}
		}
	}
	else{
		OutlineOffsetInBlob blob(GetLayersBase());
		GetLayersBase()->GetDatabaseLoader()->G_SQLLoadOutlineOfset(GetDatabase(), MachineID, &blob);
	
		// アウトライン情報を格納
		(*TargetOutlines) = QVector<QList<QPoint> >(blob.GetPhaseCount()).toList();
		for(int phase=0; phase<TargetOutlines->count(); phase++){
			(*TargetOutlines)[phase] = QVector<QPoint>(blob.GetPageCount(phase)).toList();
			for(int page=0; page<(*TargetOutlines)[phase].count(); page++){
				(*TargetOutlines)[phase][page] = QPoint(blob.GetData(phase, page).Dx, blob.GetData(phase, page).Dy);
			}
		}
	}
}