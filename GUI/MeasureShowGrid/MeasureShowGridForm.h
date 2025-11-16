#ifndef MEASURESHOWGRIDFORM_H
#define MEASURESHOWGRIDFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XMeasureCommon.h"

namespace Ui {
    class MeasureShowGridForm;
}

class MeasureShowGridForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit MeasureShowGridForm(LayersBase *Base ,QWidget *parent = 0);
    ~MeasureShowGridForm();

	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	virtual void	ShowInEdit	(void)							override;

private slots:
    void on_pushButtonSaveCSV_clicked();

private:
    Ui::MeasureShowGridForm *ui;

	MeasureDataContainer	MData;
	void ShowGrid(void);
};

//=========================================================
class	GUICmdReqMeasureData : public GUICmdPacketBase
{
public:

	GUICmdReqMeasureData(LayersBase *Base ,const QString& EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckMeasureData : public GUICmdPacketBase
{
public:
	MeasureDataContainer	Data;

	GUICmdAckMeasureData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

#endif // MEASURESHOWGRIDFORM_H
