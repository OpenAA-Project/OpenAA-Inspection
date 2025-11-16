#ifndef SHOWMEASUREHOLEPOSRESULTLISTFORM_H
#define SHOWMEASUREHOLEPOSRESULTLISTFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XMeasureCommon.h"
#include <QModelIndex>

namespace Ui {
class ShowMeasureHolePosResultListForm;
}

class ShowMeasureHolePosResultListForm : public GUIFormBase
{
    Q_OBJECT

	MeasureHolePosDataContainer	MData;
public:
    explicit ShowMeasureHolePosResultListForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ShowMeasureHolePosResultListForm();

	virtual	void	ShowInPlayer(int64 shownInspectionID)	override;
	virtual	void	ShowInEdit	(void)						override;
private slots:
    void on_tableWidget_itemSelectionChanged();
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::ShowMeasureHolePosResultListForm *ui;
	
	void ShowGrid(void);

protected:
    virtual void    resizeEvent(QResizeEvent *event)  override;
};

//=========================================================
class	GUICmdReqMeasureHolePosResultData : public GUICmdPacketBase
{
public:

	GUICmdReqMeasureHolePosResultData(LayersBase *Base ,const QString& EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckMeasureHolePosResultData : public GUICmdPacketBase
{
public:
	MeasureHolePosDataContainer	Data;

	GUICmdAckMeasureHolePosResultData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};
#endif // SHOWMEASUREHOLEPOSRESULTLISTFORM_H
