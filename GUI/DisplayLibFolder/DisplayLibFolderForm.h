#ifndef DISPLAYLIBFOLDERFORM_H
#define DISPLAYLIBFOLDERFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XStandardPropertyForm.h"

namespace Ui {
    class DisplayLibFolderForm;
}

class	GeneralLibFolderForm;

class DisplayLibFolderForm : public GUIFormBase
{
    Q_OBJECT

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	QString FolderName;
public:
    explicit DisplayLibFolderForm(LayersBase *base ,QWidget *parent = 0);
    ~DisplayLibFolderForm();

	int		SelectedLibFolderID;
	QString SelectedFolderName;

private slots:
    void on_pushButtonSet_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);

private:
    Ui::DisplayLibFolderForm *ui;

	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // DISPLAYLIBFOLDERFORM_H
