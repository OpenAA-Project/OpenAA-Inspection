#ifndef ShowColorDifferenceEditManualForm_H
#define ShowColorDifferenceEditManualForm_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XColorDifference.h"

namespace Ui {
class ShowColorDifferenceEditManualForm;
}

class ShowColorDifferenceEditManualForm : public GUIFormBase
{
    Q_OBJECT

	ColorDifferenceResultInfoContainer	CurrentResults;

public:
    explicit ShowColorDifferenceEditManualForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ShowColorDifferenceEditManualForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
    virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;

private slots:
    void on_pushButtonAddMeasure_clicked();
	void	ResizeAction();
private:
    Ui::ShowColorDifferenceEditManualForm *ui;
};



class	GUICmdReqColorDifferenceResult: public GUICmdPacketBase
{
public:

	GUICmdReqColorDifferenceResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckColorDifferenceResult: public GUICmdPacketBase
{
public:
	ColorDifferenceResultInfoContainer	Results;

	GUICmdAckColorDifferenceResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};


class	GUICmdSetColorDifferenceManualDeltaE: public GUICmdPacketBase
{
public:
	int		ItemID;
	double	DeltaE;

	GUICmdSetColorDifferenceManualDeltaE(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSetColorDifferenceManualDense: public GUICmdPacketBase
{
public:
	int		ItemID;
	double	Dense;

	GUICmdSetColorDifferenceManualDense(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // SHOWCOLORDIFFERENCERESULTLISTFORM_H
