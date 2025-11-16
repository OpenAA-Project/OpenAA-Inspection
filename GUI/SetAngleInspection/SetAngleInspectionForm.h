#ifndef SETANGLEINSPECTIONFORM_H
#define SETANGLEINSPECTIONFORM_H

#include "XGUIFormBase.h"
#include <QIODevice>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class SetAngleInspectionForm;
}

class SetAngleInspectionForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit SetAngleInspectionForm(LayersBase *base,QWidget *parent = nullptr);
    ~SetAngleInspectionForm();

    virtual void	BuildForShow(void)  override;

private slots:
    void on_pushButtonSet_clicked();

private:
    Ui::SetAngleInspectionForm *ui;
};

//============================================================================================

class	GUICmdSetAngleInspection : public GUICmdPacketBase
{
public:
	double		OKAngleL;
	double		OKAngleH;

	GUICmdSetAngleInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAngleInspection : public GUICmdPacketBase
{
public:

	GUICmdReqAngleInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAngleInspection : public GUICmdPacketBase
{
public:
	double		OKAngleL;
	double		OKAngleH;

	GUICmdAckAngleInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

#endif // SETANGLEINSPECTIONFORM_H
