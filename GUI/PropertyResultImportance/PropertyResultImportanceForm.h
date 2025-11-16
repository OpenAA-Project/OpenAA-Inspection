#ifndef PROPERTYRESULTIMPORTANCEFORM_H
#define PROPERTYRESULTIMPORTANCEFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XResultImportancePacket.h"
#include <QModelIndex>
#include <QToolButton>

namespace Ui {
    class PropertyResultImportanceForm;
}

class	ResultImportanceBase;

class PropertyResultImportanceForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyResultImportanceForm(LayersBase *base,QWidget *parent = 0);
    ~PropertyResultImportanceForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

private slots:
    void on_tableWidgetImportanceList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetAreaList_clicked(const QModelIndex &index);
    void on_tableWidgetAreaList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelectLines_clicked();

	void tbImportanceColorClicked();

private:
    Ui::PropertyResultImportanceForm *ui;

	void ShowAreaGrid(void);
	ResultImportanceBase	*GetResultImportanceBase(void);
	ResultImportanceListForPacketPack	ResultImportanceInfo;
	ResultImportanceList	**PointerList;
	NPListPack<ImportanceCounter>	ImportanceCounterContainer;

	QColor	ResultImportanceColor;
	void	SetBackgroundColor(QToolButton *Button,QColor C);
	void	SetResultImportanceColor(QColor C);
};

#endif // PROPERTYRESULTIMPORTANCEFORM_H
