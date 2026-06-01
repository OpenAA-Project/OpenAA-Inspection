#ifndef SHOWCOLORDIFFERENCERESULTLISTFORM_H
#define SHOWCOLORDIFFERENCERESULTLISTFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XColorDifference.h"

namespace Ui {
class ShowColorDifferenceResultListForm;
}

class ShowColorDifferenceResultListForm : public GUIFormBase
{
    Q_OBJECT

	ColorDifferenceResultInfoContainer	CurrentResults;

public:
    explicit ShowColorDifferenceResultListForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ShowColorDifferenceResultListForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
    virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;

private slots:
	void	ResizeAction();
private:
    Ui::ShowColorDifferenceResultListForm *ui;
};



class	GUICmdReqShowColorDifferenceResult: public GUICmdPacketBase
{
public:

	GUICmdReqShowColorDifferenceResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckShowColorDifferenceResult: public GUICmdPacketBase
{
public:
	ColorDifferenceResultInfoContainer	Results;

	GUICmdAckShowColorDifferenceResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

#endif // SHOWCOLORDIFFERENCERESULTLISTFORM_H
