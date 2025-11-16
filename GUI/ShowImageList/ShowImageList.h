#ifndef SHOWIMAGELIST_H
#define SHOWIMAGELIST_H

#include "showimagelist_global.h"
#include <QScrollBar>
#include <QTranslator>
#include <QToolButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ShowImageList : public GUIFormBase
{
	Q_OBJECT

	QScrollBar	Scroller;
	QToolButton	SaveButton;
public:
	bool	HorizontalMode;
	int32	IconSize;
	int32	IconIsolation;	
	QStringList	Path;
	QString	SavedSuffix;
	class	FileList : public NPList<FileList>
	{
		ShowImageList	*Parent;
	public:
		QString	FileNameWithPath;
		QString	FileName;
		QString	Suffix;
		QImage	IconImage;
		bool	Selected;

		FileList(ShowImageList *p):Parent(p){	Selected=false;	}

		bool	LoadImageForIcon(int IconSize);
		bool	LoadImage(DataInPage *P);
	};
	NPListPack<FileList>	FileListContainer;
	int	SelectedNo;


	class	CmdSetPath : public GUIDirectMessage
	{
	public:
		QStringList Path;
		CmdSetPath(LayersBase *base):GUIDirectMessage(base){}
	};

	ShowImageList(LayersBase *Base ,QWidget *parent);
	~ShowImageList();

	virtual  void	Prepare(void)								override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	ShowList(void);
	void	ScanFolders(void);
	void	AddedFolders(void);
	void	EmitSignalSelectFile(const QString &FileName);
private:
	virtual void paintEvent ( QPaintEvent * ) override;
	virtual	void mousePressEvent ( QMouseEvent * event )override; 
private slots:
	void	ResizeAction();
	void	SlotSliderMoved(int n);
	void	SlotSliderValueChanged(int n);
	void	SlotDeleteFile();
	void	SlotChangeName();
	void	SlotSaveClicked();
signals:
	void	SignalSelectFile(const QString &FileName);
};

class	CmdShowList : public GUIDirectMessage
{
public:
	CmdShowList(LayersBase *base):GUIDirectMessage(base){}
};



#endif // SHOWIMAGELIST_H
