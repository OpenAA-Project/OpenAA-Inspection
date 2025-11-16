#ifndef EXECUTOROFPIXLISTFORM_H
#define EXECUTOROFPIXLISTFORM_H

#include <QWidget>
#include <QPushButton>
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ExecutorOfPixListForm;
}

class ExecutorOfPixListForm : public GUIFormBase
{
    Q_OBJECT

public:
	class	ExecutorList : public NPList<ExecutorList>
	{
		ExecutorOfPixListForm	*Parent;
	public:
		QString	FolderName;
		QString	FileName;
		bool3	Judge;

		ExecutorList(ExecutorOfPixListForm *p,const QString &foldername ,const QString &filename)
			:Parent(p),FolderName(foldername),FileName(filename),Judge(none3){}
		virtual	int	Compare(ExecutorList &src)	override;
	};
	class	ExecutorListContainerClass : public NPListPack<ExecutorList>
	{
	public:
		ExecutorList	*Find(const QString &foldername ,const QString &filename);
	};

	ExecutorListContainerClass	ExecutorListContainer;
	QStringList		DefaultFolders;
	int32			PhaseToLoad;
	volatile	bool	Canceled;

    explicit ExecutorOfPixListForm(LayersBase *Base ,QWidget *parent = 0);
    ~ExecutorOfPixListForm();

	void	Prepare(void) override;

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonExecute_clicked();
    void on_pushButtonDeleteList_clicked();
    void on_pushButtonAddFolder_clicked();
    void on_pushButtonUpdate_clicked();
    void on_tableWidget_itemSelectionChanged();
    void on_pushButtonAll_clicked();
    void on_toolButtonCancel_clicked();
    void on_toolButtonFilter_clicked();
	void	ResizeAction();

private:
    Ui::ExecutorOfPixListForm *ui;

	void	ShowList(void);
	bool	LoadImageData(const QString &FileName);
	bool	ExecuteOne(void);
	void	ShowRow(int Row);
	void	ShowClearResult(int Row);
};

class	GUICmdPushed : public GUICmdPacketBase
{
public:
	int64	InspectionID;
	bool	IsExecInitialAfterEdit;
	QString	ImageType;	//"Master" "Target"
	int32	MaxInspectMilisec;

	GUICmdPushed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUIAckPushed : public GUICmdPacketBase
{
public:
	bool	Ok;
	int		NGCount;

	GUIAckPushed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	CmdInspectionAgainReplied : public GUICmdPacketBase
{
public:
	enum	__Result
	{
		_OK			=1
		,_NG		=2
		,_Nothing	=3
	}Result;
	int64		NGCounts;
	bool		TimeOutBreak;
	bool		MaxErrorBreak;
	int			ExecuterID;

	CmdInspectionAgainReplied(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // EXECUTOROFPIXLISTFORM_H
