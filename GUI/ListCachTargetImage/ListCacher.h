#ifndef LISTCACHER_H
#define LISTCACHER_H


#include "ui_ListCacher.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "XCacheTargetImage.h"

class ListCacher : public GUIFormBase
{
	Q_OBJECT

public:
	ListCacher(LayersBase *Base ,QWidget *parent = 0);
	~ListCacher();

	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
private:
	Ui::ListCacherClass ui;

	CacheTargetImageBase	*GetCacheTargetImageBase(void);

	bool SaveImage(int RNumber,const QString &FileName);

private slots:
	void on_pushButtonSavePix_clicked();
	void on_pushButtonSetToTarget_clicked();
};

//========================================================================================================

class	GUICmdSetToTarget : public GUICmdPacketBase
{
public:
	int	Number;

	GUICmdSetToTarget(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqSaveCacheImage : public GUICmdPacketBase
{
public:
	int	TopY;
	int	YCount;
	int	Layer;
	int	Number;

	GUICmdReqSaveCacheImage(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSaveCacheImage : public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdSendSaveCacheImage(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // LISTCACHER_H
