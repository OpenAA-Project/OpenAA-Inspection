#ifndef PROPERTYCOLORCORRECTORFORM_H
#define PROPERTYCOLORCORRECTORFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XGUIFormBase.h"
#include "XColorCorrector.h"
#include "XPropertyColorCorrectorPacket.h"

namespace Ui {
class PropertyColorCorrectorForm;
}
class ColorCorrectorBase;

class PropertyColorCorrectorForm : public GUIFormBase
{
    Q_OBJECT

    ColorCorrectorGridListContainer GridList;
public:
    explicit PropertyColorCorrectorForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~PropertyColorCorrectorForm();

    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private slots:
    void on_tableWidget_cellClicked(int row, int column);
    void on_pushButtonExecuteTarget_clicked();
    void on_pushButtonAutoGenerate_clicked();

private:
    Ui::PropertyColorCorrectorForm *ui;

    ColorCorrectorBase	*GetColorCorrectorBase(void);
    void    ShowList(void);
};

#endif // PROPERTYCOLORCORRECTORFORM_H
