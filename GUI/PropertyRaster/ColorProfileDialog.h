#ifndef COLORPROFILEDIALOG_H
#define COLORPROFILEDIALOG_H

#include <QDialog>
#include "XRaster.h"
#include "mtPushButtonColored.h"
#include "XServiceForLayers.h"

namespace Ui {
class ColorProfileDialog;
}

class	PropertyRasterForm;

class	ColorProfileColorButton : public mtPushButtonColored
{
    Q_OBJECT

    int Line;
public:
    ColorProfileColorButton(int Line);
private slots:
	void	SlotClicked();
signals:
	void	SignalClicked(int Line);
};

class ColorProfileDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    PropertyRasterForm  *Parent;

public:
    bool    Changed;

    explicit ColorProfileDialog(LayersBase *base
                                ,PropertyRasterForm *p
                                ,ColorProfileContainerWithTable &_ColorProfiles
                                ,QWidget *parent = nullptr);
    ~ColorProfileDialog();

    ColorProfileContainerWithTable		ColorProfiles;
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();

    void	SlotImageClicked(int Line);
    void	SlotRasterClicked(int Line);

    void on_pushButtonClear_clicked();
    void on_pushButtonAppend_clicked();
    void on_pushButtonSaveDefault_clicked();
    void on_pushButtonLoadDefault_clicked();

private:
    Ui::ColorProfileDialog *ui;

    void    ShowGrid(void);
};

#endif // COLORPROFILEDIALOG_H
