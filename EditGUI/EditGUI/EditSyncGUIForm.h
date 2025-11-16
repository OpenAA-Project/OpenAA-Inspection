#ifndef EDITSYNCGUIFORM_H
#define EDITSYNCGUIFORM_H

#include <QWidget>
#include "XServiceForLayers.h"

namespace Ui {
class EditSyncGUIForm;
}

class EditSyncGUIForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit EditSyncGUIForm(LayersBase *base ,QWidget *parent = 0);
    ~EditSyncGUIForm();

    void	SetFileNameFromGlobalParam(void);
    void	Show(void);
    void	LoadFromWindow(void);

private slots:
    void on_pushButtonFileName_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonAddLine_clicked();
    void on_pushButtonDelLine_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonSaveNew_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::EditSyncGUIForm *ui;
};

#endif // EDITSYNCGUIFORM_H
