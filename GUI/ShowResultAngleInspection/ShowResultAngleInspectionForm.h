#ifndef SHOWRESULTANGLEINSPECTIONFORM_H
#define SHOWRESULTANGLEINSPECTIONFORM_H

#include "XGUIFormBase.h"
#include <QIODevice>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


namespace Ui {
class ShowResultAngleInspectionForm;
}

class ShowResultAngleInspectionForm : public GUIFormBase
{
    Q_OBJECT

public:
	int32	Page;

    explicit ShowResultAngleInspectionForm(LayersBase *base,QWidget *parent = nullptr);
    ~ShowResultAngleInspectionForm();

	virtual void	ShowInPlayer		(int64 shownInspectionID=-1)	override;
private:
    Ui::ShowResultAngleInspectionForm *ui;
};

//============================================================================================

class	GUICmdReqShowResultAngleInspection : public GUICmdPacketBase
{
public:

	GUICmdReqShowResultAngleInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckShowResultAngleInspection : public GUICmdPacketBase
{
public:
	double		ResultAngle;
	bool3		Result;

	GUICmdAckShowResultAngleInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};
#endif // SHOWRESULTANGLEINSPECTIONFORM_H
