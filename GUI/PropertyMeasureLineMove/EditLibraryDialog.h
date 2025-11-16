#ifndef EDITLIBRARYDIALOG_H
#define EDITLIBRARYDIALOG_H

#include <QDialog>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XDataAlgorithm.h"
#include "XMeasureLineMove.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>

namespace Ui {
    class EditLibraryDialog;
}
class	GeneralLibFolderForm;

class EditLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditLibraryDialog(LayersBase *Base,QWidget *parent = 0);
    ~EditLibraryDialog();

	void	Initial(AlgorithmBase *InstBase);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButton_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);

private:
    Ui::EditLibraryDialog *ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;

	void ShowThresholdList(void);
	MeasureLineMoveBase	*GetMeasureLineMoveBase(void);
};

#endif // EDITLIBRARYDIALOG_H
