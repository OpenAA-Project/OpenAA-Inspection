#ifndef FILTERINPHASEFORM_H
#define FILTERINPHASEFORM_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"

namespace Ui {
class FilterInPhaseForm;
}

class FilterInPhaseForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    int	PhaseNo;
    int	PageNo;
public:
    explicit FilterInPhaseForm(LayersBase *base ,int phaseNo,int pageNo,QWidget *parent = 0);
    ~FilterInPhaseForm();
    
private slots:
    void on_listWidgetFilterInstance_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonGet_clicked();
    void on_pushButtonReturn_clicked();

private:
    Ui::FilterInPhaseForm *ui;

    void	ShowFilterBank(void);
    void	ShowFilterInstance(void);
};

#endif // FILTERINPHASEFORM_H
