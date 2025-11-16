#ifndef SELECTONEPAGE_H
#define SELECTONEPAGE_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
    class SelectOnePage;
}

class SelectOnePage : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectOnePage(LayersBase *pbase ,QWidget *parent = 0);
	explicit SelectOnePage(LayersBase *pbase ,const IntList &pageList,QWidget *parent = 0);
    ~SelectOnePage();

	int	SelectedPage;
private slots:
    void on_listWidgetPage_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();

private:
    Ui::SelectOnePage *ui;

	IntList		PageList;
};

#endif // SELECTONEPAGE_H
