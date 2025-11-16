#ifndef SHOWHISTGRAMSELECTFORM_H
#define SHOWHISTGRAMSELECTFORM_H

#include "XGUIFormBase.h"
#include "XShowHistgramTotalPacket.h"

namespace Ui {
    class ShowHistgramSelectForm;
}

class ShowHistgramSelectForm : public GUIFormBase
{
    Q_OBJECT

	HistgramTypeListContainer	HContainer;
	LibraryItemListContainer	LibContainer;
public:
    explicit ShowHistgramSelectForm(LayersBase *base ,QWidget *parent = 0);
    ~ShowHistgramSelectForm();

private slots:
    void on_pushButtonSelect_clicked();
    void on_pushButtonReDraw_clicked();
    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void on_tableWidget_2_doubleClicked(const QModelIndex &index);

private:
    Ui::ShowHistgramSelectForm *ui;
};

#endif // SHOWHISTGRAMSELECTFORM_H
