#ifndef AUTOGENERATORFORM_H
#define AUTOGENERATORFORM_H

#include <QWidget>
#include"XServiceForLayers.h"

namespace Ui {
class AutoGeneratorForm;
}

class AutoGeneratorButtonForm;


class AutoGeneratorForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    AutoGeneratorButtonForm *Parent;

public:
    explicit AutoGeneratorForm(LayersBase *base,AutoGeneratorButtonForm *p ,QWidget *parent = nullptr);
    ~AutoGeneratorForm();

private slots:
    void on_pushButtonAddLine_clicked();
    void on_pushButtonDelLine_clicked();
    void on_pushButtonClearAll_clicked();
    void on_pushButtonSaveList_clicked();
    void on_pushButtonLoadList_clicked();

    void    SlotChangeDXFFileName(int column,int row);
    void    SlotChangePDFFileName(int column,int row);
    void    SlotChangeAlignFileName(int column,int row);
    void    SlotChangeSpecialFileName(int column,int row);
private:
    Ui::AutoGeneratorForm *ui;

    void    ShowGrid(void);
    void    SetGridButton(void);
    void    GetDataFromWindow(void);

    virtual void    closeEvent(QCloseEvent *event)  override;
    virtual void    resizeEvent(QResizeEvent *)     override;
};

#endif // AUTOGENERATORFORM_H
