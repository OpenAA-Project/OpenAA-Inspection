#ifndef EDITLIBRARY_H
#define EDITLIBRARY_H

#include <QDialog>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XDataAlgorithm.h"
#include "XLineEnhancer1L.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>

namespace Ui {
    class EditLibrary;
}
class	GeneralLibFolderForm;

class EditLibrary : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditLibrary(LayersBase *Base,QWidget *parent = 0);
    ~EditLibrary();

	void	Initial(AlgorithmBase *InstBase);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButton_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);

    void on_checkBoxFixedAngle_clicked();

private:
    Ui::EditLibrary *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	//LineEnhancer1LLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;

	void ShowThresholdList(void);
	LineEnhancer1LBase	*GetLineEnhancer1LBase(void);
	AlgorithmLibraryListContainer	LibList;
	QList<QToolButton *>	LayerPickButtons;
	QList<QToolButton *>	LayerSourceButtons;
	QList<QToolButton *>	LayerGenButtons;
};

#endif // EDITLIBRARY_H
