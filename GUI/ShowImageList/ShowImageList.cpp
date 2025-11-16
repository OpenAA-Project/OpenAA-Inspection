/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowImageList\ShowImageList.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowImageList.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QInputDialog>
#include <QMenu>
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XCriticalFunc.h"
#include <QMessageBox>
#include <setjmp.h>

extern	"C"
{
extern	jmp_buf err_jmpbuf;
};

const	char	*sRoot=/**/"General";
const	char	*sName=/**/"ShowImageList";


QImage	*read_jpeg_stream(FILE *fp);
bool	read_jpeg_stream(FILE *fp,ImageBuffer *Buff[] ,int LayerNumb);

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show image list");
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
	return(new ShowImageList(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"HorizontalMode";
	Data[0].Pointer				 =&((ShowImageList *)Instance)->HorizontalMode;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"IconSize";
	Data[1].Pointer				 =&((ShowImageList *)Instance)->IconSize;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"IconIsolation";
	Data[2].Pointer				 =&((ShowImageList *)Instance)->IconIsolation;
	Data[3].Type				 =/**/"QStringList";
	Data[3].VariableNameWithRoute=/**/"Path";
	Data[3].Pointer				 =&((ShowImageList *)Instance)->Path;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"SavedSuffix";
	Data[4].Pointer				 =&((ShowImageList *)Instance)->SavedSuffix;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowImageList.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=======================================================================================
#define	ButtonHeight	24
#define	ScrollerHeight	20


ShowImageList::ShowImageList(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent),Scroller(this),SaveButton(this)
{
    HorizontalMode	=true;
	IconSize		=40;
	IconIsolation	=20;
	SavedSuffix		=/**/"png";
	resize(100,100);
	connect(this,SIGNAL(SignalResize())			,this,SLOT(ResizeAction()));
	connect(&Scroller,SIGNAL(sliderMoved(int))	,this,SLOT(SlotSliderMoved(int)));
	connect(&Scroller,SIGNAL(valueChanged(int))	,this,SLOT(SlotSliderValueChanged(int)));
	connect(&SaveButton,SIGNAL(clicked())		,this,SLOT(SlotSaveClicked()));
}

ShowImageList::~ShowImageList()
{
}
void	ShowImageList::Prepare(void)
{
	if(GetEditMode()==false){
		if(HorizontalMode==true){
			Scroller.setOrientation ( Qt::Horizontal );
		}
		ScanFolders();
	}
}

void	ShowImageList::ResizeAction()
{
	if(HorizontalMode==true){
		Scroller.setParent(this);
		Scroller	.setGeometry(0,height()-ScrollerHeight,width(),ScrollerHeight);
		SaveButton	.setGeometry(0,0,width(),ButtonHeight);
		SaveButton	.setText("Save");

		int	n=width()/(IconSize+IconIsolation);
		if(n==0)
			n=1;
		Scroller.setPageStep(n);
	}
}

void	ShowImageList::TransmitDirectly(GUIDirectMessage *packet)
{
	ShowImageList::CmdSetPath	*CmdSetPathVar=dynamic_cast<ShowImageList::CmdSetPath *>(packet);
	if(CmdSetPathVar!=NULL){
		Path=CmdSetPathVar->Path;
		ScanFolders();
		return;
	}
	CmdShowList	*CmdShowListVar=dynamic_cast<CmdShowList *>(packet);
	if(CmdShowListVar!=NULL){
		ScanFolders();
		return;
	}
}

void	ShowImageList::ScanFolders(void)
{
	FileListContainer.RemoveAll();
	QString	dir=QDir::currentPath();
	for(int i=0;i<Path.count();i++){
		QString	folder=Path[i];
		QDir	CD;
		CD.setCurrent(folder);

		QStringList	NameFilder;
		NameFilder<</**/"*.bmp";
		NameFilder<</**/"*.jpg";
		NameFilder<</**/"*.jpeg";
		NameFilder<</**/"*.png";
		NameFilder<</**/"*.wmv";
		NameFilder<</**/"*.mjpg";
		NameFilder<</**/"*.avi";
		NameFilder<</**/"*.mpg";
		QFileInfoList Info=CD.entryInfoList ( NameFilder, QDir::Files, QDir::Time );
		for(int j=0;j<Info.count();j++){
			FileList	*f=new FileList(this);
			f->FileNameWithPath	=Info[j].absoluteFilePath();
			f->FileName			=Info[j].fileName();
			f->Suffix			=Info[j].suffix();
			f->Selected			=false;
			if(f->LoadImageForIcon(IconSize)==true){
				FileListContainer.AppendList(f);
			}
			else{
				delete	f;
			}
		}
	}
	QDir::setCurrent(dir);

	Scroller.setMaximum(FileListContainer.GetCount());
}

void	ShowImageList::AddedFolders(void)
{
	QString	dir=QDir::currentPath();
	for(int i=0;i<Path.count();i++){
		QString	folder=Path[i];
		QDir	CD;
		CD.setCurrent(folder);

		QStringList	NameFilder;
		NameFilder<</**/"*.bmp";
		NameFilder<</**/"*.jpg";
		NameFilder<</**/"*.jpeg";
		NameFilder<</**/"*.png";
		NameFilder<</**/"*.wmv";
		NameFilder<</**/"*.mjpg";
		NameFilder<</**/"*.avi";
		NameFilder<</**/"*.mpg";
		QFileInfoList Info=CD.entryInfoList ( NameFilder, QDir::Files, QDir::Time );
		for(int j=0;j<Info.count();j++){
			FileList	*f=new FileList(this);
			f->FileNameWithPath	=Info[j].absoluteFilePath();
			f->FileName			=Info[j].fileName();
			f->Suffix			=Info[j].suffix();
			f->Selected			=false;
			bool	Found=false;
			for(FileList *g=FileListContainer.GetFirst();g!=NULL;g=g->GetNext()){
				if(g->FileNameWithPath.toUpper()==f->FileNameWithPath.toUpper()){
					Found=true;
					break;
				}
			}
			if(Found==false && f->LoadImageForIcon(IconSize)==true){
				FileListContainer.AppendList(f);
			}
			else{
				delete	f;
			}
		}
	}
	QDir::setCurrent(dir);

	Scroller.setMaximum(FileListContainer.GetCount());
}
void	ShowImageList::ShowList(void)
{
	
}
void ShowImageList::paintEvent ( QPaintEvent * )
{
	QPainter	pnt(this);

	QBrush	B(Qt::white);
	pnt.setBrush(B);
	pnt.setPen(Qt::white);
	if(HorizontalMode==true){
		int	Left=Scroller.value();
		int	Row=0;
		pnt.fillRect(0,0,width(),height(),Qt::black);
		for(FileList *f=FileListContainer[Left];f!=NULL;f=f->GetNext(),Row++){
			int	x1=Row*(IconSize+IconIsolation)+IconIsolation/2;
			int	y1=IconIsolation+ButtonHeight;
			if(x1>=width())
				break;
			pnt.drawImage(x1,y1,f->IconImage);
			pnt.drawText(x1-IconIsolation/2,y1+IconSize+IconIsolation+5,IconSize+IconIsolation,100
							,Qt::AlignLeft,f->FileName);
		}
		pnt.setPen(Qt::red);
		Row=0;
		for(FileList *f=FileListContainer[Left];f!=NULL;f=f->GetNext(),Row++){
			if(f->Selected==true){
				int	x1=Row*(IconSize+IconIsolation)+IconIsolation/2;
				int	y1=IconIsolation+ButtonHeight;
				if(x1>=width())
					break;
				pnt.drawLine(x1-2			,y1-2			,x1+IconSize+2		,y1-2);
				pnt.drawLine(x1+IconSize+2	,y1-2			,x1+IconSize+2		,y1+IconSize+2);
				pnt.drawLine(x1+IconSize+2	,y1+IconSize+2	,x1-2				,y1+IconSize+2);
				pnt.drawLine(x1-2			,y1+IconSize+2	,x1-2				,y1-2);
			}
		}
	}
}

void ShowImageList::mousePressEvent ( QMouseEvent * event )
{
	int	x=event->x();
	int	y=event->y();
	if(GetEditMode()==false){
		if(HorizontalMode==true){
			int	Left=Scroller.value();
			int	Row=0;
			for(FileList *f=FileListContainer[Left];f!=NULL;f=f->GetNext(),Row++){
				int	x1=Row*(IconSize+IconIsolation)+IconIsolation/2;
				int	y1=IconIsolation+ButtonHeight;
				if(x1>=width())
					break;
				if((x1-2)<=x && (y1-2)<y && x<(x1+IconSize+2) && y<(y1+IconSize+IconIsolation+2)){
					if(event->button()==Qt::RightButton){
						SelectedNo	=Left+Row;
						QMenu	Menu(this);
						Menu.addAction ("Delete file"	, this, SLOT(SlotDeleteFile()));
						Menu.addAction ("Change name"	, this, SLOT(SlotChangeName()));
						QPoint	Q=mapToGlobal(QPoint(x,y));
						Menu.exec(Q);
					}
					else{
						for(FileList *g=FileListContainer.GetFirst();g!=NULL;g=g->GetNext()){
							g->Selected=false;
						}
						f->LoadImage(GetLayersBase()->GetPageData(0));
						f->Selected=true;
						BroadcastRepaintAll();
					}
					break;
				}
			}
		}
	}
	GUIFormBase::mousePressEvent ( event );
}

void	ShowImageList::SlotSliderMoved(int n)
{
	repaint();
}
void	ShowImageList::SlotSliderValueChanged(int n)
{
	repaint();
}
void	ShowImageList::SlotDeleteFile()
{
	FileList *f=FileListContainer[SelectedNo];
	if(f!=NULL){
		if(QMessageBox::warning(NULL,"Delete"
							,f->FileName+QString(" : Delete OK?")
							,QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
			QFile::remove(f->FileNameWithPath);
			ScanFolders();
			Repaint();
		}
	}
}
void	ShowImageList::SlotChangeName()
{
	FileList *f=FileListContainer[SelectedNo];
	if(f!=NULL){
		bool	ok;
		QString FileName=QInputDialog::getText ( NULL, "Change file name"
										, "Change file name"
										, QLineEdit::Normal
										, f->FileName
										, &ok);
		if(ok==true){
			f->FileName=FileName;
			QFileInfo	Info(f->FileNameWithPath);
			QString	s=Info.absolutePath()+/**/"/"+FileName;
			QFile::rename(f->FileNameWithPath,s);
			f->FileNameWithPath=s;
			Repaint();
		}
	}
}
void	ShowImageList::ShowInPlayer(int64 shownInspectionID)
{
	/*
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		ExecuteInspectBase::MotionMode	M=GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetMode();
		if(M!=ExecuteInspectBase::_CaptureContinuously){

			AddedFolders();
			Repaint();
		}
	}
	*/
}
void	ShowImageList::SlotSaveClicked()
{
	QString	folder;
	if(Path.count()!=0)
		folder=Path[0];
	QString	FileName=QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss")+QString(".")+SavedSuffix;
	QString	s=folder+/**/"/"+FileName;

	ImagePointerContainer Images;
	DataInPage	*P=GetLayersBase()->GetPageData(0);
	P->GetTargetImages(Images);

	QImage DstImg(GetLayersBase()->GetMaxDotPerLine(),GetLayersBase()->GetMaxMaxLines(),QImage::Format_ARGB32);
	P->CopyTo(DstImg ,false);

	char	*fformat;
	if(SavedSuffix.toLower()=="png")
		fformat=/**/"png";
	if(SavedSuffix.toLower()=="bmp")
		fformat=/**/"bmp";
	if(SavedSuffix.toLower()=="jpg")
		fformat=/**/"jpg";
	if(SavedSuffix.toLower()=="jpeg")
		fformat=/**/"jpg";

	if(DstImg.save(s,fformat)==true){
		FileList	*f=new FileList(this);
		f->FileNameWithPath	=s;
		f->FileName			=FileName;
		f->Suffix			=SavedSuffix;
		f->Selected			=true;
		for(FileList *g=FileListContainer.GetFirst();g!=NULL;g=g->GetNext()){
			g->Selected=false;
		}
		if(f->LoadImageForIcon(IconSize)==true){
			FileListContainer.AppendList(f);
		}
		else{
			delete	f;
		}
		Repaint();
	}
	else{
		QMessageBox::warning(NULL,"Alert"
								,"Can not save image file");
	}
}
void	ShowImageList::EmitSignalSelectFile(const QString &FileName)
{
	emit	SignalSelectFile(FileName);
}

//==============================================================================
bool	ShowImageList::FileList::LoadImageForIcon(int IconSize)
{
	bool	Ret=false;
	QImage	Pic;
	if(Pic.load(FileNameWithPath)==true){
		IconImage=Pic.scaled(IconSize,IconSize);
		return true;
	}
	else{
		QFile	File(FileNameWithPath);
		if(Suffix.toUpper()==/**/"JPG" || Suffix.toUpper()==/**/"JPEG"){
			char	NameBuff[256];
			QString2Char(FileNameWithPath ,NameBuff,sizeof(NameBuff));

			FILE	*file=fopen(NameBuff,"rb");
			if(file!=NULL){
				int c = setjmp(err_jmpbuf);
				if (c == 0) {
					QImage	*Img=read_jpeg_stream(file);
					if(Img!=NULL){
						IconImage=Img->scaled(IconSize,IconSize);
						Ret=true;
					}
				}
				fclose(file);
			}
		}
		else
		if(Suffix.toUpper()==/**/"MJPG"
		|| Suffix.toUpper()==/**/"AVI"
		|| Suffix.toUpper()==/**/"WMV"
		|| Suffix.toUpper()==/**/"MPG"){
			char	NameBuff[256];
			QString2Char(FileNameWithPath ,NameBuff,sizeof(NameBuff));
			IconImage.load(QString::fromUtf8(":/Resources/PlayN.png"));
			Ret=true;
		}
	}
	return Ret;
}
bool	ShowImageList::FileList::LoadImage(DataInPage *P)
{
	QImage	Pic;
	if(Pic.load(FileNameWithPath)==true){
		Parent->EmitSignalSelectFile(FileNameWithPath);
		P->CopyFrom(Pic,false);
		return true;
	}
	else{
		QFile	File(FileNameWithPath);
		ImagePointerContainer Images;
		P->GetTargetImages(Images);

		ImageBuffer	*Buff[100];
		for(int L=0;L<P->GetLayerNumb();L++){
			Buff[L]=Images[L];
		}
		if(Suffix.toUpper()==/**/"JPG" || Suffix.toUpper()==/**/"JPEG"){
			char	NameBuff[256];
			QString2Char(FileNameWithPath ,NameBuff,sizeof(NameBuff));

			FILE	*file=fopen(NameBuff,"rb");
			if(file!=NULL){
				int c = setjmp(err_jmpbuf);
				if (c == 0) {
					bool	Ret=read_jpeg_stream(file,Buff ,P->GetLayerNumb());
					fclose(file);
					Parent->EmitSignalSelectFile(FileNameWithPath);
					return Ret;
				}
				fclose(file);
			}
		}
		else
		if(Suffix.toUpper()==/**/"MJPG"
		|| Suffix.toUpper()==/**/"AVI"
		|| Suffix.toUpper()==/**/"WMV"
		|| Suffix.toUpper()==/**/"MPG"){
			Parent->EmitSignalSelectFile(FileNameWithPath);
			return true;
		}
	}
	return false;
}

