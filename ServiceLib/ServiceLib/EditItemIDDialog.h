#ifndef EDITITEMIDDIALOG_H
#define EDITITEMIDDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditItemIDDialog;
}

class   AlgorithmBase;

class EditItemIDDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    AlgorithmBase *ABase;
    bool    EnableMessage;
    int     Phase;
    int     Page ;
    int     Layer;
public:
    explicit EditItemIDDialog(LayersBase *base,QWidget *parent = nullptr);
    ~EditItemIDDialog();

    void    Initial(AlgorithmBase *ABase
                    ,int Phase ,int Page ,int Layer
                    ,int OldItemID, int NewItemID
                    ,bool EnableMessage=true);
    int     NewItemID;

private slots:
    void on_pushButtonUpdate_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditItemIDDialog *ui;
};

#endif // EDITITEMIDDIALOG_H
