#ifndef LISTBOXPROCESSTIMEFORM_H
#define LISTBOXPROCESSTIMEFORM_H

#include "XGUIFormBase.h"
#include "ui_ListboxProcessTimeForm.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDataAlgorithm.h"

class	ExecuteTimeAlgorithm : public ExecuteTimeClass
{
public:
	QString	DLLRoot;
	QString	DLLName;

	ExecuteTimeAlgorithm(void){}

	virtual	bool    Save(QIODevice *f);
    virtual	bool    Load(QIODevice *f);
	virtual	ExecuteTimeClass	&operator=(ExecuteTimeClass &src);
};



class ListboxProcessTimeForm : public GUIFormBase
{
	Q_OBJECT

public:
	ListboxProcessTimeForm(LayersBase *Base ,QWidget *parent = 0);
	~ListboxProcessTimeForm();

	int		AlgorithmCount;
	ExecuteTimeAlgorithm	**ListByPage;
private:
	Ui::ListboxProcessTimeFormClass ui;

private slots:
	void on_tableWidgetAlgorithm_clicked(const QModelIndex &);
	void on_pushButtonClear_clicked();
	void on_pushButtonView_clicked();
	void	ResizeAction();
};

//============================================================================================

class	GUICmdReqProcessTime : public GUICmdPacketBase
{
public:

	GUICmdReqProcessTime(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendProcessTime : public GUICmdPacketBase
{
public:
	int						AlgorithmCount;
	ExecuteTimeAlgorithm	*ExecuteTimeData;
	DWORD					FilterTime;	

	GUICmdSendProcessTime(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendProcessTime(void);

	void	MakeData(int localPage);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqClearProcessTime : public GUICmdPacketBase
{
public:

	GUICmdReqClearProcessTime(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};



#endif // LISTBOXPROCESSTIMEFORM_H