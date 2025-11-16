#ifndef EDITLIBRARY_H
#define EDITLIBRARY_H

#include <QDialog>
#include <QToolButton>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XDataAlgorithm.h"
#include "XAreaShader.h"

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

private:
    Ui::EditLibrary *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	//AreaShaderLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;

	void ShowThresholdList(void);
	AreaShaderBase	*GetAreaShaderBase(void);
	AlgorithmLibraryListContainer	LibList;
	QList<QToolButton *>	LayerPickButtons;
	QList<QToolButton *>	LayerGenButtons;
};

#endif // EDITLIBRARY_H
