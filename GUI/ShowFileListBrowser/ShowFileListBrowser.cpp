/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowFileListBrowser\ShowFileListBrowser.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowFileListBrowser.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QInputDialog>
#include <QMenu>
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XCriticalFunc.h"
#include "ButtonLoadBmpJpg.h"
#include "XForWindows.h"
#include <QScreen>
#include <QGuiApplication>
#include <QMessageBox>
#include <QApplication>

const	char	*sRoot=/**/"General";
const	char	*sName=/**/"ShowFileListBrowser";


QImage	LoadJpeg(const QString &PFileName);
bool	LoadJpeg(const QString &PFileName ,ImageBuffer *Buff[] ,int LayerNumb);

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show file list browser");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowFileListBrowser(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Path";
	Data[0].Pointer				 =&((ShowFileListBrowser *)Instance)->Path;
	Data[1].Type				 =/**/"QStringList";
	Data[1].VariableNameWithRoute=/**/"Suffix";
	Data[1].Pointer				 =&((ShowFileListBrowser *)Instance)->Suffix;
	Data[2].Type				 =/**/"QFont";
	Data[2].VariableNameWithRoute=/**/"TextFont";
	Data[2].Pointer				 =&((ShowFileListBrowser *)Instance)->TextFont;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"UpdatePageSizeMode";
	Data[3].Pointer				 =&((ShowFileListBrowser *)Instance)->UpdatePageSizeMode;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"IconWidth";
	Data[4].Pointer				 =&((ShowFileListBrowser *)Instance)->IconWidth;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"IconHeight";
	Data[5].Pointer				 =&((ShowFileListBrowser *)Instance)->IconHeight;
	Data[6].Type				 =/**/"MasterImage,TargetImage";
	Data[6].VariableNameWithRoute=/**/"ImageType";
	Data[6].Pointer				 =&((ShowFileListBrowser *)Instance)->ImageType;
	Data[7].Type				 =/**/"NoLoadImage,ChangeOnePageSize,ChangeAllPageSize,TransformImage";
	Data[7].VariableNameWithRoute=/**/"TransformImage";
	Data[7].Pointer				 =&((ShowFileListBrowser *)Instance)->TransformImage;

	return(8);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowFileListBrowser.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=======================================================================================
#define	ButtonHeight	24
#define	ScrollerHeight	20


ShowFileListBrowser::ShowFileListBrowser(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
	,Model(this),View(this)
{
	resize(100,100);
	IconWidth	=100;
	IconHeight	=100;
	ImageType	=/**/"MasterImage";
	TransformImage	=/**/"ChangeOnePageSize";

	TextFont.setPixelSize(14);
	UpdatePageSizeMode	=true;

	LabelPath.setParent(this);

	connect(this,SIGNAL(SignalResize())			,this,SLOT(ResizeAction()));

	Model.setFilter(QDir::AllDirs | QDir::Files | QDir::Drives | QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
	ButtonUpper.setParent(this);
	ButtonUpper.setGeometry(0,0,31,31);
	ButtonUpperIcon.addFile(/**/":Resources/icon/20/02.png",QSize(),QIcon::Normal,QIcon::Off);
	ButtonUpperIcon.addFile(/**/":Resources/icon/20/01.png",QSize(),QIcon::Normal,QIcon::On);
	ButtonUpper.setIcon(ButtonUpperIcon);
	ButtonUpper.setCheckable(true);
	connect(&ButtonUpper,SIGNAL(clicked()),this,SLOT(SlotButtonUpperClicked()));

	ViewPort=new QListViewPort(this,NULL);
	ViewPort->setToolTip("XXXYYYY");
	View.setViewport(ViewPort);
	View.viewport()->setAcceptDrops(true);

	View.setModel(&Model);
	View.setViewMode(QListView::IconMode);
	View.setIconSize (QSize(IconWidth,IconHeight));
	View.setUniformItemSizes(true);
	thumbviewDelegate = new ThumbViewDelegate(this,this);
	View.setItemDelegate(thumbviewDelegate);
	View.setSpacing(2);
	View.setBaseSize(1000,3000);
	View.setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	View.setSelectionMode(QAbstractItemView::SingleSelection);
	View.setDragDropMode(QAbstractItemView::DropOnly);
	View.setAcceptDrops(true);

	//View.resizeColumnToContents(1);
	//View.resizeColumnToContents(2);
	connect(&View,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(SlotDoubleClicked ( const QModelIndex &))); 
}

ShowFileListBrowser::~ShowFileListBrowser()
{
}
void	ShowFileListBrowser::ReadyParam(void)
{
	QStringList	NameList;

	for(int i=0;i<Suffix.count();i++){
		NameList.append(QString(/**/"*.")+Suffix[i]);
	}

	LabelPath.setText(Path);

	Model.setNameFilters(NameList);
	Model.setNameFilterDisables(false);
	if(Path.isEmpty()==false){
		QModelIndex	Index=Model.setRootPath(Path);
		View.setRootIndex(Index);
	}
}

void	ShowFileListBrowser::ResizeAction()
{
	LabelPath.setGeometry(32,0,width()-32,31);
	View.setGeometry(0,31,width(),height()-31);
}

void	ShowFileListBrowser::Repaint(void)
{
	View.repaint();
}
void	ShowFileListBrowser::TransmitDirectly(GUIDirectMessage *packet)
{
	ShowFileListBrowser::CmdSetPath	*CmdSetPathVar=dynamic_cast<ShowFileListBrowser::CmdSetPath *>(packet);
	if(CmdSetPathVar!=NULL){
		Path=CmdSetPathVar->Path;

		QModelIndex	Index=Model.setRootPath(CmdSetPathVar->Path);
		View.setRootIndex(Index);
		QString	RPath=Model.rootPath();
		LabelPath.setText(RPath);
		//View.resizeColumnToContents(1);
		//View.resizeColumnToContents(2);
		return;
	}
	CmdLoadImageInBrowser	*CmdLoadImageInBrowserVar=dynamic_cast<CmdLoadImageInBrowser *>(packet);
	if(CmdLoadImageInBrowserVar!=NULL){
		if(LoadImage(CmdLoadImageInBrowserVar->FileName,CmdLoadImageInBrowserVar->LoadedPage)==true){
			emit	SignalDoubleClickedFile(CmdLoadImageInBrowserVar->FileName);
			SlotCopyPic();
			CmdLoadImageInBrowserVar->Result=true;
		}
		else{
			CmdLoadImageInBrowserVar->Result=false;
		}
		return;
	}
}
void	ShowFileListBrowser::SlotDoubleClicked ( const QModelIndex & index )
{
	QFileInfo	FInfo=Model.fileInfo(index);
	QString	FileName=FInfo.absoluteFilePath();
	if(FInfo.suffix().toUpper()==/**/"PDF"){
		QMessageBox::warning(nullptr,"注意"
									,"PDFファイルは読み込めません");
		return;
	}
	if(LoadImage(FileName)==true){
		emit	SignalDoubleClickedFile(FileName);

		static	int	ConnectedCount=0;
		if(ConnectedCount==0){
			connect(this,SIGNAL(SignalCopyPic()),this,SLOT(SlotCopyPic()),Qt::QueuedConnection);
			ConnectedCount++;
		}
		emit	SignalCopyPic();
		//disconnect(this,SIGNAL(SignalCopyPic()),this,SLOT(SlotCopyPic()));
	}
	else{
		QModelIndex	Index=Model.setRootPath(FileName);
		Path=FileName;
		View.setRootIndex(Index);
		LabelPath.setText(Path);
		QDir	cd(Path);
		if(cd.cdUp()==true){
			ButtonUpper.setEnabled(true);
		}
		else{
			ButtonUpper.setEnabled(false);
		}
	}
}

void	ShowFileListBrowser::SlotCopyPic()
{
	BYTE	BackColor=0x40;
	if(ImageType==/**/"MasterImage"){
		if(GetTargetPage()>=0){
			if(GetTargetPage()<GetPageNumb()){
				DataInPage	*dp=GetLayersBase()->GetPageData(GetTargetPage());
				ImagePointerContainer Images;
				dp->GetMasterImages	(Images);
				for(ImagePointerList *p=Images.GetFirst();p!=NULL;p=p->GetNext()){
					p->GetImage()->Memset(BackColor);
				}
				dp->CopyFrom(Pic,true);
			}
		}
		else{
			DataInPage	*dp=GetLayersBase()->GetPageData(0);
			ImagePointerContainer Images;
			dp->GetMasterImages	(Images);
			for(ImagePointerList *p=Images.GetFirst();p!=NULL;p=p->GetNext()){
				p->GetImage()->Memset(BackColor);
			}
			dp->CopyFrom(Pic,true);
		}
	}
	else{
		if(GetTargetPage()>=0){
			if(GetTargetPage()<GetPageNumb()){
				DataInPage	*dp=GetLayersBase()->GetPageData(GetTargetPage());
				ImagePointerContainer Images;
				dp->GetTargetImages	(Images);
				for(ImagePointerList *p=Images.GetFirst();p!=NULL;p=p->GetNext()){
					p->GetImage()->Memset(BackColor);
				}
				dp->CopyFrom(Pic,false);
			}
		}
		else{
			DataInPage	*dp=GetLayersBase()->GetPageData(0);
			ImagePointerContainer Images;
			dp->GetTargetImages	(Images);
			for(ImagePointerList *p=Images.GetFirst();p!=NULL;p=p->GetNext()){
				p->GetImage()->Memset(BackColor);
			}
			dp->CopyFrom(Pic,false);
		}
	}
	BroadcastRepaintAll();
}

void	ShowFileListBrowser::SlotButtonUpperClicked()
{
	if(ButtonUpper.isChecked()==true){
		QDir	cd(Path);
		if(cd.cdUp()==true){
			Path=cd.path();
			QModelIndex	Index=Model.setRootPath(Path);
			View.setRootIndex(Index);
			LabelPath.setText(Path);
			QDir	cd2(Path);
			if(cd2.cdUp()==true){
				ButtonUpper.setEnabled(true);
			}
			else{
				ButtonUpper.setEnabled(false);
			}
		}
		else{
			ButtonUpper.setEnabled(false);
		}
		ButtonUpper.setChecked(false);
	}
}


bool	ShowFileListBrowser::LoadImage(const QString &FileNameWithPath ,int page)
{
	if(TransformImage==/**/"NoLoadImage")
		return true;
	if(page<0){
		page=GetTargetPage();
	}
	if(Pic.load(FileNameWithPath)==true){
		if(UpdatePageSizeMode==true){
			if(Pic.width ()!=GetLayersBase()->GetMaxDotPerLine()
			|| Pic.height()!=GetLayersBase()->GetMaxMaxLines  ()){
				if(page>=0 && page<GetPageNumb()){
					if(TransformImage==/**/"ChangeOnePageSize"){
						GetLayersBase()->ReallocXYPixelsPage(GetLayersBase()->GetCurrentPhase(),page,Pic.width(),Pic.height());
					}
					else
					if(TransformImage==/**/"ChangeAllPageSize" || TransformImage==/**/"ChangeOnePageSize"){
						GetLayersBase()->ReallocXYPixels(Pic.width(),Pic.height());
					}
					else
					if(TransformImage==/**/"TransformImage"){
						QImage		tPic=Pic.scaled (GetLayersBase()->GetDotPerLine(page)
													,GetLayersBase()->GetMaxLines(page)
													, Qt::KeepAspectRatio, Qt::SmoothTransformation);
						Pic=tPic;
					}
				}
			}
		}
		//BroadcastRepaintAll();
		return true;
	}
	else{
		QFileInfo	Info(FileNameWithPath);
		QString	Suf=Info.suffix();

		if(Suf.toUpper()==/**/"MJPG"
		|| Suf.toUpper()==/**/"AVI"
		|| Suf.toUpper()==/**/"MPG"
		|| Suf.toUpper()==/**/"MPEG"
		|| Suf.toUpper()==/**/"WMV"){
			return true;
		}
		//CmdLoadBmpJpgPacketTarget	Cmd(GetLayersBase());
		CmdLoadBmpJpgPacketQImage	Cmd(GetLayersBase());
		Cmd.FileName	=FileNameWithPath;
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ButtonLoadBmpJpg",/**/"");
		if(f!=NULL){
			f->TransmitDirectly(&Cmd);
			if(Cmd.Success==true){
				Pic=Cmd.Image;
				if(Pic.width ()!=GetLayersBase()->GetMaxDotPerLine()
				|| Pic.height()!=GetLayersBase()->GetMaxMaxLines  ()){
					if(TransformImage==/**/"ChangeOnePageSize" && page>=0){
						GetLayersBase()->ReallocXYPixelsPage(GetLayersBase()->GetCurrentPhase(),page,Pic.width(),Pic.height());
					}
					else
					if(TransformImage==/**/"ChangeAllPageSize" || (TransformImage==/**/"ChangeOnePageSize" && page>=0)){
						GetLayersBase()->ReallocXYPixels(Pic.width(),Pic.height());
					}
					else
					if(TransformImage==/**/"TransformImage"){
						QImage		tPic=Pic.scaled (GetLayersBase()->GetDotPerLine(page)
													,GetLayersBase()->GetMaxLines(page)
													, Qt::KeepAspectRatio, Qt::SmoothTransformation);
						Pic=tPic;
					}
				}
			}
			return Cmd.Success;
		}
	}
	return false;
}

ThumbViewDelegate::ThumbViewDelegate(ShowFileListBrowser *p,QObject *parent)
	:Parent(p)
{
}

QSize ThumbViewDelegate::sizeHint(const QStyleOptionViewItem &  option ,
                              const QModelIndex & index) const
{
    return QSize(Parent->IconWidth,Parent->IconHeight);
}

void	DivideStr(const QString &Str ,QStringList &TextList ,int DivN)
{
	int	N=Str.length();
	int	Numb=N/DivN;
	int	StartPoint=0;
	for(int i=0;i<DivN;i++){
		QString	s;
		if(i+1>=DivN){
			Numb=N-StartPoint;
		}
		for(int k=0;k<Numb;k++){
			s.append(Str[StartPoint+k]);
		}
		TextList.append(s);
		StartPoint+=Numb;
	}
}

QString	FormatterPath(const QString &s)
{
	QString	Ret;

	int	Len=s.length();
	for(int i=0;i<Len;i++){
		QChar	c=s.at(i);
		if(c==/**/'/' || c==/**/'\\')
			c=/**/'/';
		Ret.append(c.toUpper());
	}
	return Ret.trimmed();
}

void ThumbViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
	if(Parent->Path.isEmpty()==false && Parent->GetLayersBase()->GetEventPriority()==0){
		QString	s1=FormatterPath(Parent->Model.rootPath());
		QString	s2=FormatterPath(Parent->Path);
		if(s1!=s2){
			QDir	cd(Parent->Path);
			if(cd.exists()==true){
				QModelIndex	Index=Parent->Model.setRootPath(Parent->Path);
				Parent->View.setRootIndex(Index);
				Parent->Repaint();
			}
		}
		else
		if(s1==s2){
			painter->save();

			QScreen	*W=qApp->screens()[0];
			QString filenameText = qvariant_cast<QString>(index.data(Qt::EditRole));
			int	WDPI=W->physicalDotsPerInchX();
			/*
			int	WDPI2=W->physicalDpiX();
			int	Wid1=W->widthMM ();
			int	Wid2=W->width();
			double	Op=W->windowOpacity();

			QRect	R1=W->availableGeometry();
			QRect	R2=W->screenGeometry();
			*/
			double	ZRate=((double)WDPI)/96.0;

			int	YMergin=6;
			int	LineMergin=3;
			int	XMergin=5;
			//QFont font = qvariant_cast<QFont>(index.data(Qt::FontRole));
			//font.setPixelSize(10);
			QFontMetrics fm(Parent->TextFont);

			int	TextWidth	=fm.boundingRect(filenameText).width();
			int	TextHeight	=fm.height();

			QStringList	TextList;
			TextList.append(filenameText);
			int	DivN=1;
			while(Parent->IconWidth-XMergin*2<TextWidth*ZRate){
				DivN++;
				TextList.clear();
				DivideStr(filenameText ,TextList ,DivN);
				TextWidth=0;
				for(int i=0;i<DivN;i++){
					int	Len=fm.boundingRect(TextList[i]).width();
					if(TextWidth<Len){
						TextWidth=Len;
					}
				}
			}
			if(DivN>2){
				QString	t=filenameText;
				QString	fstr=t.mid(0,7)
							+QString(/**/"...")
							+t.mid(t.length()-5,5);
				TextList.clear();
				TextList.append(fstr);
				DivN=1;
			}

			QSize iconsize = QSize(Parent->IconWidth-XMergin*2
								  ,Parent->IconHeight-TextHeight*DivN-LineMergin*(DivN-1)-YMergin*2);	//icon.actualSize(option.decorationSize);
			QRect item = option.rect;
			QRect iconRect(item.left()+4, item.top()+4, iconsize.width(), iconsize.height());
			QPainterPath iconPath;
			iconPath.addRoundedRect(iconRect, 12, 12);

			QRect textRect = item;
			textRect.setTop(item.top()+item.height()-TextHeight*DivN-LineMergin*(DivN-1)-YMergin*2);				//item.top()+item.height()-fm.height()-10);
			QPainterPath textPath;
			textPath.addRoundedRect(textRect, 8, 8);

			painter->setRenderHint(QPainter::Antialiasing, true);
			painter->setRenderHint(QPainter::TextAntialiasing, true);

			painter->setFont(Parent->TextFont);
//			  painter->fillPath(textPath, Qt::gray);
//			  painter->drawRoundedRect(textRect, 6, 6);
			for(int i=0;i<DivN;i++){
				painter->drawText(textRect.left()+XMergin
								,textRect.top()+YMergin+(TextHeight+LineMergin)*(i+1)
								, TextList[i]);
			}

			painter->setPen(Qt::darkGray);
			painter->setClipping(true);
			painter->setClipPath(iconPath);
				
			QString	iPath=Parent->Model.rootPath();
			QString	PFileName=iPath+::GetSeparator()+filenameText;
			QPixmap	PMap;
			if(PMap.load(PFileName)==true && PMap.isNull()==false){
				QPixmap IconMap=PMap.scaled ( iconsize, Qt::KeepAspectRatio);
				painter->drawPixmap(iconRect, IconMap);
			}
			else{
				QImage	PImg;
				QFileInfo	FInfo(PFileName);
				QString	Suf=FInfo.suffix().toUpper();
				if(Suf==/**/"JPG" || Suf=="JPEG"){
					PImg=LoadJpeg(PFileName);
				}
				if(PImg.isNull()==false){
					QImage IconMap=PImg.scaled ( iconsize, Qt::KeepAspectRatio);
					painter->drawImage(iconRect, IconMap);
				}
				else{
					if(filenameText==/**/".."){
						QIcon	icon(/**/":Resources/UpperFolder.png");
						QSize iconsize = QSize(Parent->IconWidth,Parent->IconHeight);//icon.actualSize(option.decorationSize);
						painter->drawPixmap(iconRect, icon.pixmap(iconsize.width(),iconsize.height()));
					}
					else{
						QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
						QSize iconsize = QSize(Parent->IconWidth,Parent->IconHeight);//icon.actualSize(option.decorationSize);
						painter->drawPixmap(iconRect, icon.pixmap(iconsize.width(),iconsize.height()));
					}
				}
			}
			painter->setClipping(false);

			painter->setPen(Qt::darkGray);
			painter->drawPath(iconPath);

			painter->setPen(Qt::darkGray);
			if (option.state & QStyle::State_Selected) {
			    QPen pen(Qt::red);
			    pen.setWidth(2);
			    painter->setPen(pen);
			}
			painter->drawRoundedRect(item, 8, 8);
			painter->restore();
		}
	}
}
void	ShowFileListBrowser::SlotDelete()
{
	QModelIndex	Index=View.indexAt ( ReleasedPoint );
	QFileInfo	FInfo=Model.fileInfo(Index);
	if(FInfo.isFile()==true){
		QString	FileName=FInfo.absoluteFilePath();
		
		if(QMessageBox::question ( NULL, "ファイル削除"
								, FileName+ QString(" を削除しますか？")
								, QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
			QFile::remove(FileName);
		}
	}
	else
	if(FInfo.isDir()==true){
		QString	FolderName=FInfo.absoluteFilePath();
		if(QMessageBox::question ( NULL, "フォルダ削除"
								, FolderName+QString(" を削除しますか？")
								, QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
			QStringList	List;
			List.append(/**/"*.*");
			QDir	dir(FolderName);
			QFileInfoList	FileInfo=dir.entryInfoList(List,QDir::Files | QDir::NoDotAndDotDot);
			for(int i=0;i<FileInfo.count();i++){
				dir.remove(FileInfo[i].fileName());
			}
			dir.rmdir(FolderName);
		}
	}
}

void	ShowFileListBrowser::SlotCopy()
{
	QModelIndex	Index=View.indexAt ( ReleasedPoint );
	QFileInfo	FInfo=Model.fileInfo(Index);
	QString	FileName=FInfo.absoluteFilePath();

	QClipboard *clipboard = QApplication::clipboard();

	// Ownership of the new data is transferred to the clipboard.
	QMimeData* newMimeData = new QMimeData();

	// Copy path of file
	newMimeData->setText(FileName);
	
	// Copy file
	QList<QUrl>	UrlList;
	UrlList<<QUrl::fromLocalFile(FileName);
	newMimeData->setUrls(UrlList);
	
	// Copy file (gnome)
	QByteArray gnomeFormat = QByteArray("copy\n").append(QUrl::fromLocalFile(FileName).toEncoded());
	newMimeData->setData("x-special/gnome-copied-files", gnomeFormat);
	
	// Set the mimedata
	clipboard->setMimeData(newMimeData);
}

void	ShowFileListBrowser::SlotPaste()
{
	const QClipboard *clipboard = QApplication::clipboard();
	const QMimeData *mimeData = clipboard->mimeData();

	//QStringList	FList;
	//FList=mimeData->formats();
	//QString	FormatStr;
	//int	D=0;
	//for(int i=0;i<FList.count();i++){
	//	FormatStr=FList[i];
	//	D++;
	//}
	if (mimeData->hasUrls()==true){
		QList<QUrl>	UList=mimeData->urls ();
		for(int i=0;i<UList.count();i++){
			QString	Src=UList[i].toLocalFile();
			QFileInfo	FInfo(Src);
			if(FInfo.isFile()==true){
				QString DestFileName=Path
									+GetSeparator()
									+FInfo.fileName();
					
				::MTCopyFile(Src ,DestFileName ,false);
			}
		}
		
	}
}

void	ShowFileListBrowser::SlotOpen()
{
	QModelIndex	Index=View.indexAt ( ReleasedPoint );
	SlotDoubleClicked ( Index );
}

void	ShowFileListBrowser::SlotChangeFileName()
{
	QModelIndex	Index=View.indexAt ( ReleasedPoint );
	QFileInfo	FInfo=Model.fileInfo(Index);
	QString	Path=FInfo.path();
	QString	FileName=FInfo.fileName();
	QString	OldFileName=FInfo.absoluteFilePath();
	bool ok;
	QString Str=QInputDialog::getText(NULL
									, "ファイル名変更"
									, "新しいファイル名を入力"
									, QLineEdit::Normal
									, FileName, &ok);
	if(ok==true){
		QDir	Dir(Path);
		Dir.rename(FileName,Str);
	}
}

QFileListListView::QFileListListView(ShowFileListBrowser * parent )
	:QListView(parent),Parent(parent)
{
	TM.setInterval(200);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}

void	QFileListListView::mouseReleaseEvent ( QMouseEvent * event ) 
{
	if(event->button()==Qt::RightButton){
		Parent->ReleasedPoint=event->pos();
		QMenu	Menu("ファイル操作",this);
		Menu.addAction ("削除"				, Parent, SLOT(SlotDelete())		, Qt::Key_Delete);
		Menu.addAction ("コピー"			, Parent, SLOT(SlotCopy())			, Qt::Key_Copy);
		Menu.addAction ("貼り付け"			, Parent, SLOT(SlotPaste())			, Qt::Key_Paste);
		Menu.addAction ("ファイル名変更"	, Parent, SLOT(SlotChangeFileName()));
		Menu.addAction ("開く"				, Parent, SLOT(SlotOpen())			, Qt::Key_Enter);
		Menu.exec(mapToGlobal(Parent->ReleasedPoint));
	}
}
void	QFileListListView::dragEnterEvent ( QDragEnterEvent * event )
{
	if(event->mimeData()->hasUrls()) {
		event->acceptProposedAction();
    }
}
void	QFileListListView::dropEvent ( QDropEvent * event )
{
   if (event->mimeData()->hasUrls()) {
		QList<QUrl>	UList=event->mimeData()->urls ();
		for(int i=0;i<UList.count();i++){
			QString	Src=UList[i].toLocalFile();
			QFileInfo	FInfo(Src);
			if(FInfo.isFile()==true){
				QString DestFileName=Parent->Path
									+GetSeparator()
									+FInfo.fileName();
					
				::MTCopyFile(Src ,DestFileName ,false);
			}
		}
	}
}
bool	QFileListListView::event(QEvent *event)
{
	if(event->type()==QEvent::ToolTip){
		QCoreApplication::processEvents();
		QPoint GPos=QCursor::pos();
		QPoint Pos=mapFromGlobal(GPos);
		QModelIndex index=indexAt(Pos);
		QString filenameText = qvariant_cast<QString>(index.data(Qt::EditRole));
		QWidget	*v=viewport();
		v->setToolTip(filenameText);
		//event->accept();
	}
	return QListView::event(event);
}

void	QFileListListView::SlotTimeOut()
{
	QCoreApplication::processEvents();
	QPoint GPos=QCursor::pos();
	QPoint Pos=mapFromGlobal(GPos);
	QModelIndex index=indexAt(Pos);
	QString filenameText = qvariant_cast<QString>(index.data(Qt::EditRole));
	QWidget	*v=viewport();
	v->setToolTip(filenameText);
}


QListViewPort::QListViewPort(ShowFileListBrowser *parent,QWidget *p)
	:QWidget(p),Parent(parent)
{
	setMouseTracking(true);
	setAcceptDrops(true);
}
void	QListViewPort::dragEnterEvent ( QDragEnterEvent * event )
{
	if(event->mimeData()->hasUrls()) {
		event->acceptProposedAction();
    }
}
void	QListViewPort::dropEvent ( QDropEvent * event )
{
}
void	QListViewPort::mouseMoveEvent(QMouseEvent *event)
{
	XPos=event->x();
	YPos=event->y();
}
