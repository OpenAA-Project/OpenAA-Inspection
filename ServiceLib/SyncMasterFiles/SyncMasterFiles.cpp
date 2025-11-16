#include "SyncMasterFiles.h"
#include <QDir>
#include <QDateTime>
#include "XForWindows.h"
#include "XGeneralFunc.h"
#include "AddExcludedFileDialog.h"

FileAndTimeStamp	&FileAndTimeStamp::operator=(FileAndTimeStamp &src)
{
	FileName	=src.FileName;
	TimeStamp	=src.TimeStamp;
	return *this;
}

FileAndTimeStampContainer	&FileAndTimeStampContainer::operator=(FileAndTimeStampContainer &src)
{
	RemoveAll();
	for(FileAndTimeStamp *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		FileAndTimeStamp *b=new FileAndTimeStamp ();
		*b=*a;
		AppendList(b);
	}
	return *this;
}


//==========================================================================================
ThreadMakeFileTable::ThreadMakeFileTable(SyncMasterFiles *pbase ,QObject *parent)
	:QThread(parent),PBase(pbase)
{
	TerminationFlag=false;
}

void	ThreadMakeFileTable::run(void)
{
	while(TerminationFlag==false){
		bool	Result=true;
		if(PBase->SrcPathExists==true){
			FileAndTimeStampContainer	CurrentSourceFiles;
			bool	CurrentSrcPathExists;
			PBase->MakeContainer(PBase->SourcePath ,CurrentSourceFiles,CurrentSrcPathExists);
			if(CurrentSrcPathExists==true){
				for(FileAndTimeStamp *s=CurrentSourceFiles.GetFirst();s!=NULL;s=s->GetNext()){
					FileAndTimeStamp *d;
					for(d=PBase->SrcFiles.GetFirst();d!=NULL;d=d->GetNext()){
						if(s->FileName.toUpper()==d->FileName.toUpper()){
							break;
						}
					}
					if(d==NULL){	//Copy new
						if(CopyFileInThread( PBase->SourcePath + QString("\\")+s->FileName
											,PBase->DestPath + QString("\\")+s->FileName)==false){
							Result=false;
							break;
						}
					}
					else if(s->TimeStamp!=d->TimeStamp){
						if(UpdateFile(PBase->SourcePath + QString("\\")+s->FileName
									 ,PBase->DestPath + QString("\\")+s->FileName)==false){
							Result=false;
						}
					}
				}
				if(Result==true){
					for(FileAndTimeStamp *d=PBase->SrcFiles.GetFirst();d!=NULL;d=d->GetNext()){
						FileAndTimeStamp *s;
						for(s=CurrentSourceFiles.GetFirst();s!=NULL;s=s->GetNext()){
							if(d->FileName.toUpper()==s->FileName.toUpper()){
								break;
							}
						}
						if(s==NULL){
							if(RemoveFile(PBase->DestPath + QString("\\")+d->FileName)==false){
								Result=false;
								break;
							}
						}
					}
				}
				if(Result==true){
					PBase->SrcFiles=CurrentSourceFiles;
				}

				emit	SignalStep();
			}
		}
		else{
			PBase->MakeContainer(PBase->SourcePath ,PBase->SrcFiles,PBase->SrcPathExists);
			emit	SignalStep();
		}
		for(int i=0;i<PBase->SleepTimeSec;i++){
			sleep(1);
			if(TerminationFlag==true){
				break;
			}
		}
	}
}

bool	ThreadMakeFileTable::CopyFileInThread(const QString &FileName ,const QString &DestPath)
{
	if(::MTCopyFile(FileName,DestPath,false)==true){
		PBase->MessagesMutex.lock();
		PBase->MessagesFromThread.append(FileName);
		PBase->MessagesMutex.unlock();
		emit	SignalCopyed();
		return true;
	}
	else{
		PBase->MessagesMutex.lock();
		PBase->MessagesFromThread.append(QString("False : ")+FileName);
		PBase->MessagesMutex.unlock();
		emit	SignalCopyed();
	}
	return false;
}
bool	ThreadMakeFileTable::UpdateFile(const QString &FileName ,const QString &DestPath)
{
	if(::MTCopyFile(FileName,DestPath,false)==true){
		PBase->MessagesMutex.lock();
		PBase->MessagesFromThread.append(FileName);
		PBase->MessagesMutex.unlock();
		emit	SignalUpdated();
		return true;
	}
	else{
		PBase->MessagesMutex.lock();
		PBase->MessagesFromThread.append(QString("False : ")+FileName);
		PBase->MessagesMutex.unlock();
		emit	SignalUpdated();
	}
	return false;
}

bool	ThreadMakeFileTable::RemoveFile(const QString &FileName)
{
	QFileInfo	FInfo(FileName);

	if(QFile::exists(FileName)==true){
		if(QFile::remove(FileName)==true){
			PBase->MessagesMutex.lock();
			PBase->MessagesFromThread.append(FileName);
			PBase->MessagesMutex.unlock();
			emit	SignalRemoved();
			return true;
		}
		else{
			PBase->MessagesMutex.lock();
			PBase->MessagesFromThread.append(QString("False : ")+FileName);
			PBase->MessagesMutex.unlock();
			emit	SignalRemoved();
		}
	}
	return false;
}

//==========================================================================================

SyncMasterFiles::SyncMasterFiles(const QString &_SourcePath ,const QString &_DestPath ,int _SleepTimeSec
								,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),ThreadChecker(this,this)
	,SourcePath(_SourcePath)
	,DestPath(_DestPath)
	,SleepTimeSec(_SleepTimeSec)
{
	ui.setupUi(this);

	QFile	SettingFile(GetSettingFileName());
	if(SettingFile.open(QIODevice::ReadOnly)==true){
		Load(&SettingFile);
	}
	ui.listWidgetExcluded	->clear();
	ui.listWidgetExcluded->addItems(ExcludedFiles);

	bool PathExists;
	MakeContainer(SourcePath ,SrcFiles,SrcPathExists);
	MakeContainer(DestPath   ,DstFiles,PathExists);

	ui.lineEditSource		->setText(SourcePath);
	ui.lineEditDestination	->setText(DestPath);
	ui.progressBar->setValue(0);

	ui.listWidgetSource->clear();
	for(FileAndTimeStamp *s=SrcFiles.GetFirst();s!=NULL;s=s->GetNext()){
		ui.listWidgetSource->addItem(s->FileName);
	}

	bool	Ret;
	Ret=(connect(&ThreadChecker,SIGNAL(SignalCopyed())	,this,SLOT(SlotCopyed())	,Qt::QueuedConnection))?true:false;
	Ret=(connect(&ThreadChecker,SIGNAL(SignalUpdated())	,this,SLOT(SlotUpdated())	,Qt::QueuedConnection))?true:false;
	Ret=(connect(&ThreadChecker,SIGNAL(SignalRemoved())	,this,SLOT(SlotRemoved())	,Qt::QueuedConnection))?true:false;
	Ret=(connect(&ThreadChecker,SIGNAL(SignalStep())	,this,SLOT(SlotStep())		,Qt::QueuedConnection))?true:false;

	ThreadChecker.start();
}
SyncMasterFiles::~SyncMasterFiles()
{
	ThreadChecker.TerminationFlag=true;
	ThreadChecker.deleteLater();
}

bool	SyncMasterFiles::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,ExcludedFiles)==false)
		return false;
	return true;
}

bool	SyncMasterFiles::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,ExcludedFiles)==false)
		return false;
	return true;
}

int	SyncMasterFiles::MakeContainer(const QString &path ,FileAndTimeStampContainer &ret ,bool &PathExists)
{
	QDir	Dir(path);
	if(Dir.exists()==true){
		PathExists=true;
	}
	else{
		PathExists=false;
		return 0;
	}
	QFileInfoList List=Dir.entryInfoList  (QDir::Files);
	int	N=0;
	for(int i=0;i<List.count();i++){
		bool	DoExclude=false;
		for(int j=0;j<ExcludedFiles.count();j++){
			if(ExcludedFiles[j]==List[i].fileName()){
				DoExclude=true;
				break;
			}
		}
		if(DoExclude==false){
			FileAndTimeStamp	*d=new FileAndTimeStamp();
			d->FileName	=List[i].fileName();
			d->TimeStamp.operator=(List[i].lastModified());
			ret.AppendList(d);
			N++;
		}
	}
	return N;
}

void	SyncMasterFiles::SlotCopyed()
{
	MessagesMutex.lock();
	QString	Msg=MessagesFromThread[0];
	MessagesFromThread.removeAt(0);
	MessagesMutex.unlock();

	ui.listWidgetAddition->addItem(Msg);
}
void	SyncMasterFiles::SlotUpdated()
{
	MessagesMutex.lock();
	QString	Msg=MessagesFromThread[0];
	MessagesFromThread.removeAt(0);
	MessagesMutex.unlock();

	ui.listWidgetUpdate->addItem(Msg);
}
void	SyncMasterFiles::SlotRemoved()
{
	MessagesMutex.lock();
	QString	Msg=MessagesFromThread[0];
	MessagesFromThread.removeAt(0);
	MessagesMutex.unlock();

	ui.listWidgetRemove->addItem(Msg);
}

void	SyncMasterFiles::SlotStep()
{
	ui.listWidgetSource->clear();
	for(FileAndTimeStamp *s=SrcFiles.GetFirst();s!=NULL;s=s->GetNext()){
		ui.listWidgetSource->addItem(s->FileName);
	}
	if(ui.progressBar->value()>=ui.progressBar->maximum()){
		ui.progressBar->setValue(0);
	}
	else{
		ui.progressBar->setValue(ui.progressBar->value()+1);
	}
}

void	SyncMasterFiles::closeEvent(QCloseEvent *ev)
{
	ev->accept();
	ThreadChecker.TerminationFlag=true;
	ThreadChecker.wait(5000);
}

void SyncMasterFiles::on_pushButtonAddExcluded_clicked()
{
	AddExcludedFileDialog	D;
	if(D.exec()==true){
		ExcludedFiles.append(D.FileName);
		ui.listWidgetExcluded	->clear();
		ui.listWidgetExcluded	->addItems(ExcludedFiles);

		QFile	SettingFile(GetSettingFileName());
		if(SettingFile.open(QIODevice::WriteOnly)==true){
			Save(&SettingFile);
		}
	}
}

void SyncMasterFiles::on_pushButtonDelExcluded_clicked()
{
	int	Row=ui.listWidgetExcluded->currentRow();
	if(Row<0)
		return;
	ExcludedFiles.removeAt(Row);

	ui.listWidgetExcluded	->clear();
	ui.listWidgetExcluded	->addItems(ExcludedFiles);
}
