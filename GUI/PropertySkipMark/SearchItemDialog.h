#ifndef SEARCHITEMDIALOG_H
#define SEARCHITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include"XPropertySkipMarkPacket.h"

namespace Ui {
class SearchItemDialog;
}

class	LibIDList : public NPList<LibIDList>
{
public:
	int		LibID;
	QString	LibName;

	LibIDList(void){	LibID=-1;	}
};

class	LibIDContainer : public NPListPack<LibIDList>
{
public:
	LibIDContainer(void){}

	LibIDList	*IsInclude(int LibID);
};


class SearchItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	int GlobalPage;
	int Layer;
	AlgorithmBase *ABase;
	ItemInfoContainer	ItemList;
	LibIDContainer		LibIDStock;
public:
    explicit SearchItemDialog(LayersBase *Base,AlgorithmBase *ABase,int GlobalPage ,int _Layer,QWidget *parent = 0);
    ~SearchItemDialog();

	int	ItemID;
private slots:
    void on_pushButtonSortByID_clicked();
    void on_pushButtonSortByName_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonSortByLibID_clicked();

private:
    Ui::SearchItemDialog *ui;

	void	ShowList(void);
};

#endif // SEARCHITEMDIALOG_H
