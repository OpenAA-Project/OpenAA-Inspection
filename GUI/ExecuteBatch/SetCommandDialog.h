#ifndef SETCOMMANDDIALOG_H
#define SETCOMMANDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QModelIndex>
#include "XExecuteBatch.h"
#include "XGUI.h"
#include "XAlgorithmBase.h"
#include "XResultDLLManager.h"
#include "NList.h"
#include "XServiceForLayers.h"

namespace Ui {
class SetCommandDialog;
}

class	ExecuteBatchForm;
class	ExportFuncForMacro;

class	ComponentLine : public NPList<ComponentLine>
{
public:
	GUIItemInstance	*DLLGui;
	LogicDLL		*DLLAlgo;
	ResultDLL		*DLLResult;

	ComponentLine(void);

	QString		GetDLLRoot(void);
	QString		GetDLLName(void);
	int		RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer);
};

class SetCommandDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	ExecuteBatchForm			*Parent;
	NPListPack<ComponentLine>	ComponentContainer;

	ComponentLine *CurrentSelected;

	struct ArgumentStruct
	{
		QLabel		*ArgLabel;
		QLineEdit	*ArgName;
		QLineEdit	*ArgValue;
	}ArgumentStructTable[10];

public:
    explicit SetCommandDialog(LayersBase *Base ,ExecuteBatchForm *parent = 0);
    ~SetCommandDialog();

	BatchLine	CurrentData;
	void	Initial(BatchLine &data);

private slots:
    void on_tableWidgetComponent_clicked(const QModelIndex &index);
    void on_tableWidgetCommand_clicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_tableWidgetCommand_itemSelectionChanged();

private:
    Ui::SetCommandDialog *ui;

	void	ShowComponent(void);
	void	ShowExportFuncForMacro( ExportFuncForMacro &R);
};

#endif // SETCOMMANDDIALOG_H
