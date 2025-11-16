#ifndef EDITITEMDIALOG_H
#define EDITITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include"XPropertySkipMarkPacket.h"

namespace Ui {
class EditItemDialog;
}

class EditItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	bool AdditionalMode;
	AlgorithmBasePointerContainer	AlgoBases;
	NamingInfoListContainer			NamingContainer;
public:
    explicit EditItemDialog(bool AdditionalMode ,LayersBase *Base,int globalPage ,int Layer ,QWidget *parent = 0);
    ~EditItemDialog();

	int			GlobalPage;
	int			Layer;

	QString		ItemName;
	QString		NamingDLLRoot;
	QString		NamingDLLName;
	int32		NamingID;

	void	Reflect(void);
private slots:
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonModify_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditItemDialog *ui;

	void	ShowList(void);
};

#endif // EDITITEMDIALOG_H
