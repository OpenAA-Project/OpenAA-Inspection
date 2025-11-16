#ifndef SELECTLIBRARYFORGENERATEDIALOG_H
#define SELECTLIBRARYFORGENERATEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include "XServiceForLayers.h"
namespace Ui {
class SelectLibraryForGenerateDialog;
}
class	CartonMenuForm;
class   SetThresholdLevelForm;

const   int    GenerationMaxCamDimCount =10;
const   int    GenerationMaxLibCount    =100;

class SelectLibraryForGenerateDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	CartonMenuForm	*Parent;
    QPushButton     *SelectionButton[GenerationMaxCamDimCount][GenerationMaxLibCount];
    SetThresholdLevelForm	*SForm;
public:
    explicit SelectLibraryForGenerateDialog(CartonMenuForm *p,QWidget *parent = 0);
    ~SelectLibraryForGenerateDialog();
    
private slots:
    void on_PushButtonStartGenerate_clicked();
    void on_PushButtonCancel_clicked();
    void    SlotChangeThresholdLevelID(int ThresholdLevelID);

private:
    Ui::SelectLibraryForGenerateDialog *ui;
};

#endif // SELECTLIBRARYFORGENERATEDIALOG_H
