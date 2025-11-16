#ifndef INTEGRATIONSELECTMASTERFORM_H
#define INTEGRATIONSELECTMASTERFORM_H

#include <QWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QSqlTableModel>
#include <QTableView>
#include "IntegrationLib.h"

namespace Ui {
class IntegrationSelectMasterForm;
}

class IntegrationSelectMasterForm;
class	QSqlLoadRelationModel : public QSqlTableModel
{
	IntegrationSelectMasterForm	*ParentWindow;
public:
	QSqlLoadRelationModel(QObject * parent, QSqlDatabase db);
	QString selectStatement () const;
};

class IntegrationSelectMasterForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

	QTableView *MListView;
public:
    explicit IntegrationSelectMasterForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationSelectMasterForm();

private slots:
    void on_pushButtonSelect_clicked();
	void	ResizeAction();
	void	SlotClicked			(const QModelIndex &Index);
	void	SlotDoubleClicked	(const QModelIndex &Index);

private:
    Ui::IntegrationSelectMasterForm *ui;

	void	ShowListHeader(void);
};

#endif // INTEGRATIONSELECTMASTERFORM_H
