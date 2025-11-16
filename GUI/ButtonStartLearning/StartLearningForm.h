#ifndef STARTLEARNINGFORM_H
#define STARTLEARNINGFORM_H

#include "XGUIFormBase.h"
#include "ui_StartLearningForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XLearning.h"
#include "XTypeDef.h"

class StartLearningForm : public GUIFormBase
{
	Q_OBJECT

public:
	StartLearningForm(LayersBase *base,QWidget *parent = 0);
	~StartLearningForm();

private:
	Ui::StartLearningFormClass ui;

	QStringList	PWAFilesName;

private slots:
	void on_pushButtonClear_clicked();
	void on_pushButton_clicked();
	void on_pushButtonStart_clicked();
};


class	GUICmdReqStartLearning : public GUICmdPacketBase
{
public:
	int MasterCode;
	int LotAutoCount;

	GUICmdReqStartLearning(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdLearningReqStartOne: public GUICmdPacketBase
{
public:

	GUICmdLearningReqStartOne(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){		return true;	}
	virtual	bool	Save(QIODevice *f){		return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdLearningAckStartOne: public GUICmdPacketBase
{
public:
	double	ResultValueInPage;

	GUICmdLearningAckStartOne(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdLearningExeTop: public GUICmdPacketBase
{
public:

	GUICmdLearningExeTop(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){		return true;	}
	virtual	bool	Save(QIODevice *f){		return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdLearningExeLoopTop: public GUICmdPacketBase
{
public:

	GUICmdLearningExeLoopTop(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){		return true;	}
	virtual	bool	Save(QIODevice *f){		return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdLearningExeLoopNext: public GUICmdPacketBase
{
public:
	double	ResultValueInPage;

	GUICmdLearningExeLoopNext(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdLearningReqData: public GUICmdPacketBase
{
public:

	GUICmdLearningReqData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){		return true;	}
	virtual	bool	Save(QIODevice *f){		return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdLearningAckData: public GUICmdPacketBase
{
public:
	LearningLeafForSaveContainer	Data;

	GUICmdLearningAckData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdLearningSetData: public GUICmdPacketBase
{
public:
	LearningLeafForSaveContainer	Data;

	GUICmdLearningSetData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // STARTLEARNINGFORM_H
