#ifndef AUTOSAVEIMAGELISTFORSEARCH_H
#define AUTOSAVEIMAGELISTFORSEARCH_H

#include "autosaveimagelistforsearch_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	AutoSaveImageListForSearch : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	AutoSaveImageListForSearch(LayersBase *Base ,QWidget *parent);
	~AutoSaveImageListForSearch(void);
	
	virtual void	Prepare(void)	override;

	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdLoadAutoSaveImageFile : public GUICmdPacketBase
{
public:
	QStringList		AutoSaveImageFileNames;

	GUICmdLoadAutoSaveImageFile(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // AUTOSAVEIMAGELISTFORSEARCH_H
