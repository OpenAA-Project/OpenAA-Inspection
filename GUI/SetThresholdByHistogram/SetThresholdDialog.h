#ifndef SETTHRESHOLDDIALOG_H
#define SETTHRESHOLDDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class SetThresholdDialog;
}

class	IntStringContainer;
class	ShowThresholdHistgramForm;

class	AlgoHistList : public NPListSaveLoad<AlgoHistList>
{
public:
	bool	Use;
	int		HistID;
	QString	HistName;

	AlgoHistList(void){	Use=false;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	AlgoHistListContainer : public NPListPackSaveLoad<AlgoHistList>
{
public:
	virtual	AlgoHistList	*Create(void)	{	return new AlgoHistList();	}
};

class	AlgorithmListForHistgram : public NPListSaveLoad<AlgorithmListForHistgram>
{
public:
	bool	Use;
	QString	AlgoRoot;
	QString	AlgoName;

	AlgoHistListContainer	AlgoHistData;

	AlgorithmListForHistgram(void)	{	Use=false;	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	AlgorithmListContainerForHistgram : public NPListPackSaveLoad<AlgorithmListForHistgram>
{
public:
	AlgorithmListContainerForHistgram(void){}

	virtual	AlgorithmListForHistgram	*Create(void)	{	return new AlgorithmListForHistgram();	}
	void	Merge(const QString &AlgoRoot ,const QString &AlgoName ,IntStringContainer &src);
};


class SetThresholdDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	AlgorithmListContainerForHistgram	AList;
	int		LastAlgo;
	ShowThresholdHistgramForm	*Thr;
public:
    explicit SetThresholdDialog(LayersBase *base ,QWidget *parent = 0);
    ~SetThresholdDialog();

private slots:
    void on_tableWidgetAlgorithm_clicked(const QModelIndex &index);
    void on_pushButtonSet_clicked();
    void on_pushButtonCancel_clicked();
    void on_checkBoxCheckAllAlgorithm_clicked();
    void on_checkBoxCheckAllHistogram_clicked();

    void on_tableWidgetHistogram_doubleClicked(const QModelIndex &index);

private:
    Ui::SetThresholdDialog *ui;

	void	ShowAlgoList(void);
	void	FromWindow(int AlgoNo);
	void	ToWindow(int AlgoNo);
};



//==============================================================================================

class	GUICmdReqEnumEffectiveHistgram : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;

	GUICmdReqEnumEffectiveHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntStringList : public NPListSaveLoad<IntStringList>
{
public:
	int		Data;
	QString	Str;

	IntStringList(void){	Data=0;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	IntStringContainer : public NPListPackSaveLoad<IntStringList>
{
public:
	IntStringContainer(void){}

	virtual	IntStringList	*Create(void)	{	return new IntStringList();		}
};


class	GUICmdAckEnumEffectiveHistgram : public GUICmdPacketBase
{
public:
	IntStringContainer	HistData;

	GUICmdAckEnumEffectiveHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//==============================================================================================

class	GUICmdReqExecuteAutoThreshold : public GUICmdPacketBase
{
public:
	bool		ModeOneWork;
	bool		ModeMultiWork;
	double		AdoptRate;
	double		SigmaMultiply;
	AlgorithmListContainerForHistgram	AList;

	GUICmdReqExecuteAutoThreshold(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // SETTHRESHOLDDIALOG_H
