#ifndef EDITSOURCEDIALOG_H
#define EDITSOURCEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include"XPropertySkipMarkPacket.h"

namespace Ui {
class EditSourceDialog;
}

class EditSourceDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	int	GlobalPage;
	int	Layer;
	int	ItemID;
	SkipMarkSourceAlgoContainer		Sources;
	ItemInfoContainer				ItemList;
public:
    explicit EditSourceDialog(LayersBase *Base,SkipMarkInfo *Info ,QWidget *parent = 0);
    ~EditSourceDialog();

private slots:
    void on_tableWidgetAlgorithm_clicked(const QModelIndex &index);
    void on_pushButtonDeleteLines_clicked();
    void on_pushButtonAddItem_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditSourceDialog *ui;

	void	ShowAlgorithm(void);
	void	ShowItemList(void);
};

#endif // EDITSOURCEDIALOG_H
