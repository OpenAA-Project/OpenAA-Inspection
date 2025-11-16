#ifndef EDITDOTCOLORMATCHINGLIBRARYDIALOG_H
#define EDITDOTCOLORMATCHINGLIBRARYDIALOG_H

#include <QDialog>
#include "XDotColorMatching.h"
#include "XDotColorMatchingLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditDotColorMatchingLibraryDialog;
}
class	GeneralLibFolderForm;
class AlgorithmLibraryLevelContainer;

class EditDotColorMatchingLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditDotColorMatchingLibraryDialog(LayersBase *base ,QWidget *parent = 0);
    ~EditDotColorMatchingLibraryDialog();

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
    int     MasterNoOriginCode;
	bool	OnChanging;

	AlgorithmLibraryLevelContainer	*LLib;

	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	DotColorMatchingBase	*GetDotColorMatchingBase(void);
	void		ShowSubtractList(DotColorMatchingLibrary &data);
	AlgorithmLibraryListContainer	LibList;

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_toolButtonPickup_clicked();
    void on_toolButtonInspect_clicked();
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButton_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
    void on_EditSelfSearch_valueChanged(int arg1);
    void on_doubleSpinBoxSelfSearch_valueChanged(double arg1);
    void on_pushButtonColor_clicked();
    void on_toolButtonExplain_clicked();
    void on_pushButtonMasterNo_clicked();
    void on_pushButtonSubtractLibID_clicked();
    void on_EditAreaSearchX_valueChanged(int arg1);
    void on_doubleSpinBoxAreaSearchX_valueChanged(double arg1);
    void on_EditAreaSearchY_valueChanged(int arg1);
    void on_doubleSpinBoxAreaSearchY_valueChanged(double arg1);

    void on_EditOKDotB_valueChanged(int arg1);
    void on_doubleSpinBoxOKDotB_valueChanged(double arg1);
    void on_EditOKDotN_valueChanged(int arg1);
    void on_doubleSpinBoxOKDotN_valueChanged(double arg1);

private:
    Ui::EditDotColorMatchingLibraryDialog *ui;
};

#endif // EDITDOTCOLORMATCHINGLIBRARYDIALOG_H
