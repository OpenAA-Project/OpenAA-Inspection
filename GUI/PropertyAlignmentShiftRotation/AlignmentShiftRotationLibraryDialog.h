#ifndef ALIGNMENTSHIFTROTATIONLIBRARYDIALOG_H
#define ALIGNMENTSHIFTROTATIONLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QTableWidget>
#include <QToolButton>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XDataAlgorithm.h"
#include "XAlignmentShiftRotation.h"
#include "XAlignmentShiftRotationCommon.h"


namespace Ui {
class AlignmentShiftRotationLibraryDialog;
}
class	GeneralLibFolderForm;
class	AlignmentShiftRotationLibraryDialog;
class	AlgorithmLibraryLevelContainer;

class AlignmentShiftRotationLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit AlignmentShiftRotationLibraryDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~AlignmentShiftRotationLibraryDialog();

    void	Initial(AlgorithmBase *InstBase);

private slots:
    void on_tableWidgetLibList_itemSelectionChanged();
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonAddAngle_clicked();
    void on_pushButtonSubAngle_clicked();
    void on_tableWidgetAngleList_cellDoubleClicked(int row, int column);
    void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::AlignmentShiftRotationLibraryDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	//LibListWidget	*LibListW;

	int		LibFolderID;
	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;
    RotationRangeContainer	Rotation;

	void ShowThresholdList(void);
	AlignmentShiftRotationBase	*GetAlignmentShiftRotationBase(void);
	AlgorithmLibraryListContainer	LibList;

    void	ShowAngleRange(void);
};

#endif // ALIGNMENTSHIFTROTATIONLIBRARYDIALOG_H
