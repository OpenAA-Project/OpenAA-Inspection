#ifndef EDITLIBRARYDIALOG_H
#define EDITLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QTableWidget>
#include <QToolButton>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XDataAlgorithm.h"
#include "XAlignmentFlexArea.h"

namespace Ui {
class EditLibraryDialog;
}
class	GeneralLibFolderForm;
class	EditLibraryDialog;
class	AlgorithmLibraryLevelContainer;

class	LibListWidget : public QTableWidget
{
	Q_OBJECT
		QPoint	dragStartPosition;
	EditLibraryDialog	*Parent;
public:
	LibListWidget(void);
	LibListWidget(QWidget *obj);

	virtual	void	mouseMoveEvent ( QMouseEvent * ) override;
	virtual	void	mousePressEvent ( QMouseEvent * ) override;

//signals:
//	void	clicked ( const QModelIndex & index );
};

class EditLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditLibraryDialog(LayersBase *Base ,QWidget *parent = 0);
    ~EditLibraryDialog();

	void	Initial(AlgorithmBase *InstBase);
	void	ShowCurrentList(void);
private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButtonClose_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void	SlotDrop(int FolderParentID ,int LibFolderID , QWidget *w);
private:
    Ui::EditLibraryDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	LibListWidget	*LibListW;

	int		LibFolderID;
	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;

	void ShowThresholdList(void);
	AlignmentFlexAreaBase	*GetAlignmentFlexAreaBase(void);
	AlgorithmLibraryListContainer	LibList;
	QList<QToolButton *>	LayerPickButtons;
	QList<QToolButton *>	LayerGenButtons;
};

#endif // EDITLIBRARYDIALOG_H
