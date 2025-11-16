#ifndef SHOWRESULTDIALOG_H
#define SHOWRESULTDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XTypeDef.h"
#include "XGUIPacketForDLL.h"
#include "XDustReducerAI.h"

class	DustReducerAI;

namespace Ui {
class ShowResultDialog;
}

class	DustReducerAI;
class	DustRegListPointer;

class ShowResultDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	DustReducerAI	*Parent;

	QImage	*CurrentImage;
	QImage	*RegImage;
	DustRegListPointer *Current;

public:
    explicit ShowResultDialog(LayersBase *base ,DustReducerAI *P,QWidget *parent = 0);
    ~ShowResultDialog();
    
private slots:
    void on_pushButtonRegOK_clicked();
    void on_pushButtonRegNG_clicked();
    void on_tableWidgetResult_clicked(const QModelIndex &index);
    void on_pushButtonChangeReg_clicked();
    void on_pushButtonDeleteReg_clicked();
    void on_pushButtonLoadRegPack_clicked();
    void on_pushButtonSaveRegPack_clicked();
    void on_pushButtonClearRegPack_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::ShowResultDialog *ui;

	void	MakeImage(QImage *Img,BYTE *Pattern[3],int LayerNumb,int XLen,int YLen);
	void	ShowList(void);
};

//============================================================================
class	GUICmdReqRADustReducerAIAddCurrent : public GUICmdPacketBase
{
public:
	int		ResultAnalizerItemBaseID;
	QString	Comment;
	JudgeDust	OkNg;

	GUICmdReqRADustReducerAIAddCurrent(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdReqRADustReducerAIUpdateRegLib : public GUICmdPacketBase
{
public:
	int		ResultAnalizerItemBaseID;
	int		DustRegListID;
	QString	Comment;
	JudgeDust	OkNg;

	GUICmdReqRADustReducerAIUpdateRegLib(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdReqRADustReducerAIDeleteRegLib : public GUICmdPacketBase
{
public:
	int		ResultAnalizerItemBaseID;
	int		DustRegListID;

	GUICmdReqRADustReducerAIDeleteRegLib(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // SHOWRESULTDIALOG_H
