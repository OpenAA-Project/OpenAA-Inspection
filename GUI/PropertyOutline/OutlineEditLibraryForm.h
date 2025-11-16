#ifndef OUTLINEEDITLIBRARYFORM_H
#define OUTLINEEDITLIBRARYFORM_H

#include <QDialog>
#include <QModelIndex>
#include <QToolButton>
#include "XOutlineInspect.h"
#include "XServiceForLayers.h"
#include "ShowRGBCube.h"

namespace Ui {
class OutlineEditLibraryForm;
}
class	GeneralLibFolderForm;

class OutlineEditLibraryForm : public QDialog, public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit OutlineEditLibraryForm(LayersBase* base, QWidget *parent = 0);
    ~OutlineEditLibraryForm();

    GeneralLibFolderForm* pLibFolderForm;
    int		LibFolderID;

    //OutlineInspectLibrary* TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
    int		LibType;
    void	ShowLibrary(AlgorithmLibraryLevelContainer& data);
    void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer& data);

    OutlineBase* GetOutlineBase(void);
    AlgorithmLibraryListContainer	LibList;

    ShowRGBSpace	ColorGenerator;
    ShowRGBSpace	ColorInside;
    ShowRGBSpace	ColorOutside;
    ShowRGBSpace	TrColorInside;
    ShowRGBSpace	TrColorOutside;

    ShowRGBSpace	ColorBInside;
    ShowRGBSpace	ColorBOutside;
    ShowRGBSpace	TrColorBInside;
    ShowRGBSpace	TrColorBOutside;

private slots:
    void on_toolButtonPickup_clicked();
    void on_toolButtonInspect_clicked();
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonGColor_clicked();
    void on_pushButtonInsideBColor_clicked();
    void on_pushButtonOutsideBColor_clicked();
    void on_pushButtonInsideColor_clicked();
    void on_pushButtonOutsideColor_clicked();
    void on_radioButtonInsideStable_toggled(bool checked);
    void on_radioButtonInsideTrans_toggled(bool checked);
    void on_radioButtonOutsideStable_toggled(bool checked);
    void on_radioButtonOutsideTrans_toggled(bool checked);
    void on_radioButtonInsideBStable_toggled(bool checked);
    void on_radioButtonInsideBTrans_toggled(bool checked);
    void on_radioButtonOutsideBStable_toggled(bool checked);
    void on_radioButtonOutsideBTrans_toggled(bool checked);
    void	SlotSelectLibFolder(int libFolderID, QString FolderName);
private:
    Ui::OutlineEditLibraryForm *ui;

    QList<QToolButton*>	LayerPickButtons;
    QList<QToolButton*>	LayerGenButtons;
};

#endif // OUTLINEEDITLIBRARYFORM_H
