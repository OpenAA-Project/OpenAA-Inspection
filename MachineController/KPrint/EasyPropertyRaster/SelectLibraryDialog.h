#ifndef SELECTLIBRARYDIALOG_H
#define SELECTLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XRaster.h"
#include "XRasterLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectLibraryDialog;
}
class	GeneralLibFolderForm;
class	AlgorithmLibraryLevelContainer;

class SelectLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectLibraryDialog(LayersBase *base ,QWidget *parent = 0);
    ~SelectLibraryDialog();
    
	int	SelectedLibID;

private slots:
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectLibraryDialog *ui;

	GeneralLibFolderForm			*pLibFolderForm;
	int								LibFolderID;
	int								LibType;
	AlgorithmLibraryListContainer	LibList;

	RasterBase	*GetRasterBase(void);
};

#endif // SELECTLIBRARYDIALOG_H
