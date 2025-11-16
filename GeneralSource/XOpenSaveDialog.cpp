#include "XTypeDef.h"
#include <QString>
#include <QFile>
#include "XDataInLayer.h"
#include "XGeneralFunc.h"

#define	FileNameForLastPathOfFileDialog	"/LastPathOfFileDialog.dat"

QString LayersBase::LGetExistingDirectory (QWidget * parent, const QString & caption , const QString & dir)
{
	TmpHideProcessingForm();

	QString FileName=QDir::tempPath ()+QString(FileNameForLastPathOfFileDialog);
	QFile	RFile(FileName);
	QString MDir=dir;
	if(RFile.exists()==true){
		if(RFile.open(QIODevice::ReadOnly)==true){
			QTextStream	F(&RFile);
			F>>MDir;
		}
	}

	QString f=QFileDialog::getExistingDirectory ( parent , caption, MDir);
	if(f.isEmpty()==false){
		QFile	WFile(FileName);
		if(WFile.open(QIODevice::WriteOnly)==true){
			QTextStream	F(&WFile);
			F<<f;			
		}
	}
	TmpRercoverProcessingForm();

	return f;
}
QString LayersBase::LGetOpenFileName (QWidget * parent, const QString & caption, const QString & dir, const QString & filter, QString * selectedFilter)
{
	TmpHideProcessingForm();

	QString FileName=QDir::tempPath ()+QString(FileNameForLastPathOfFileDialog);
	QString MDir=dir;
	QFile	RFile(FileName);
	if(RFile.exists()==true){
		if(RFile.open(QIODevice::ReadOnly)==true){
			QTextStream	F(&RFile);
			F>>MDir;
		}
	}

	QString f=QFileDialog::getOpenFileName ( parent, caption, MDir, filter, selectedFilter);
	if(f.isEmpty()==false){
		QFile	WFile(FileName);
		if(WFile.open(QIODevice::WriteOnly)==true){
			QFileInfo	FInfo(f);
			QTextStream	F(&WFile);
			F<<FInfo.path();			
		}
	}
	TmpRercoverProcessingForm();

	return f;
}
QStringList LayersBase::LGetOpenFileNames (QWidget * parent, const QString & caption, const QString & dir, const QString & filter, QString * selectedFilter)
{
	TmpHideProcessingForm();

	QString FileName=QDir::tempPath ()+QString(FileNameForLastPathOfFileDialog);
	QString MDir=dir;
	QFile	RFile(FileName);
	if(RFile.exists()==true){
		if(RFile.open(QIODevice::ReadOnly)==true){
			QTextStream	F(&RFile);
			F>>MDir;
		}
	}

	QStringList flist=QFileDialog::getOpenFileNames ( parent, caption, MDir, filter, selectedFilter);
	if(flist.count()!=0){
		QFile	WFile(FileName);
		if(WFile.open(QIODevice::WriteOnly)==true){
			QFileInfo	FInfo(flist.value(0));
			QTextStream	F(&WFile);
			F<<FInfo.path();			
		}
	}
	TmpRercoverProcessingForm();

	return flist;
}
QString LayersBase::LGetSaveFileName (QWidget * parent, const QString & caption, const QString & dir, const QString & filter, QString * selectedFilter)
{
	TmpHideProcessingForm();

	QString FileName=QDir::tempPath ()+QString(FileNameForLastPathOfFileDialog);
	QString MDir=dir;
	QFile	RFile(FileName);
	if(RFile.exists()==true){
		if(RFile.open(QIODevice::ReadOnly)==true){
			QTextStream	F(&RFile);
			F>>MDir;
		}
	}

	QString f=QFileDialog::getSaveFileName( parent, caption, MDir, filter, selectedFilter);
	if(f.isEmpty()==false){
		QFile	WFile(FileName);
		if(WFile.open(QIODevice::WriteOnly)==true){
			QFileInfo	FInfo(f);
			QTextStream	F(&WFile);
			F<<FInfo.path();			
		}
	}
	TmpRercoverProcessingForm();

	return f;
}