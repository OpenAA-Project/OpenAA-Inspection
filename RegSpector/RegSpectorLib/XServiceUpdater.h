#pragma once

#include "NListComp.h"
#include <QString>
#include <QDateTime>
#include <QTextStream>
#include "XTypeDef.h"

#define		TmpFolderNameToUpdate	"_UpdatedFiles"

class UpdatedFileList : public NPListSaveLoad<UpdatedFileList>
{
public:
	enum Operation
	{
		_Update
		,_ForceUpdate
		,_Delete
	};
	Operation	FileOperation;
	QString		RelativeFileName;
	QDateTime	FileStamp;

	UpdatedFileList(void);
	~UpdatedFileList(void);

	virtual	bool	Save(QIODevice* f)	override;
	virtual	bool	Load(QIODevice* f)	override;
private:
};

class UpdatedFileListContainer : public NPListPackSaveLoad<UpdatedFileList>
{
public:
	QString		Version;

	UpdatedFileListContainer(void) {}
	~UpdatedFileListContainer(void) {}

	virtual	UpdatedFileList* Create(void)	override;

	bool	LoadFromFileList(const QString& AbsPath, QTextStream &Txt);
	bool	SaveFileList(const QString& AbsPath, QTextStream& Txt);

	UpdatedFileListContainer	&operator=(const UpdatedFileListContainer &src);

	virtual	bool	Save(QIODevice* f)	override;
	virtual	bool	Load(QIODevice* f)	override; 

private:

};

