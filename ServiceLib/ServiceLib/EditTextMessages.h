#ifndef EDITTEXTMESSAGES_H
#define EDITTEXTMESSAGES_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditTextMessages;
}

class EditTextMessages : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit EditTextMessages(LayersBase *base,TextMessageContainer &TextMessageContainerData,QWidget *parent = 0);
    ~EditTextMessages();

    TextMessageContainer	TextMessageContainerData;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();

private:
    Ui::EditTextMessages *ui;

    void	GetDataFromWindow(void);
    void	SetDataToWindow(void);

    virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // EDITTEXTMESSAGES_H
