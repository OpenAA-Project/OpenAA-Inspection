#ifndef SHOWTHINMETALRESULTLISTFORM_H
#define SHOWTHINMETALRESULTLISTFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "NListComp.h"

namespace Ui {
class ShowThinMetalResultListForm;
}

class	ThinMetalSamplingResult : public NPListSaveLoad<ThinMetalSamplingResult>
{
public:
	QString	FileName;
	double	MatchingRate;

	ThinMetalSamplingResult(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	ThinMetalSamplingResultConatiner : public NPListPackSaveLoad<ThinMetalSamplingResult>
{
public:
	ThinMetalSamplingResultConatiner(void){}

	virtual	ThinMetalSamplingResult	*Create(void)	{	return new ThinMetalSamplingResult();	}
};


class ShowThinMetalResultListForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	ThinMetalSamplingResultConatiner	CurrentContainer;
	int	CurrentPage;

    explicit ShowThinMetalResultListForm(LayersBase *base ,QWidget *parent = 0);
    ~ShowThinMetalResultListForm();
    
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
private:
    Ui::ShowThinMetalResultListForm *ui;

private slots:
	void	ResizeAction();
    void on_tableWidget_doubleClicked(const QModelIndex &index);
};

//======================================================================================

class	GUICmdReqThinMetalSamplingResultConatiner : public GUICmdPacketBase
{
public:
	int	Layer;
	int	ItemID;
	int	MaxCount;

	GUICmdReqThinMetalSamplingResultConatiner(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckThinMetalSamplingResultConatiner : public GUICmdPacketBase
{
public:
	ThinMetalSamplingResultConatiner	CurrentContainer;

	GUICmdAckThinMetalSamplingResultConatiner(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdDelThinMetalSampling : public GUICmdPacketBase
{
public:
	int	Layer;
	int	ItemID;
	QString	DeleteFileName;

	GUICmdDelThinMetalSampling(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdLoadThinMetalSampling : public GUICmdPacketBase
{
public:
	int	Layer;
	int	ItemID;
	QString	FileName;

	GUICmdLoadThinMetalSampling(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // SHOWTHINMETALRESULTLISTFORM_H
