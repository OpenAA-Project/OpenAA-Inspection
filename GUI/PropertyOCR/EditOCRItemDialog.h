#ifndef EDITOCRITEMDIALOG_H
#define EDITOCRITEMDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XTypeDef.h"
#include "XColorSpace.h"

namespace Ui {
class EditOCRItemDialog;
}

class EditOCRItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditOCRItemDialog(LayersBase *Base, QWidget *parent = 0);
    ~EditOCRItemDialog();

	int32		Mergin;

	QString		ItemName;
	int			RegNumber;
	bool		InspectMatching;
	bool		SaveIntoResult;
	bool		OKByFailingRecognition;
	QStringList		CorrectList;

	void	ReflectToWindow(void);
	void	FromWindow(void);

private slots:
    void on_listWidgetMatchingList_doubleClicked(const QModelIndex &index);
    void on_pushButtonAddMatchingList_clicked();
    void on_pushButtonSubMatchingList_clicked();
    void on_ButtonSaveNewItem_clicked();
    void on_ButtonUpdateItem_clicked();
    void on_pushButtonClose_clicked();

    void on_ButtonDeleteItem_clicked();


private:
    Ui::EditOCRItemDialog *ui;
};

#endif // EDITOCRITEMDIALOG_H
