#ifndef EDITTUNNELCRACKLIBRARY_H
#define EDITTUNNELCRACKLIBRARY_H

#include <QDialog>
#include "ui_EditTunnelCrackLibrary.h"
#include "XTunnelCrack.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class EditTunnelCrackLibrary : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	EditTunnelCrackLibrary(LayersBase *base ,QWidget *parent = 0);
	~EditTunnelCrackLibrary();

private:
	Ui::EditTunnelCrackLibraryClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	TunnelCrackLibrary	*TempLib;
	int		LibType;
	void	ShowLibrary(TunnelCrackLibrary &data);
	void	GetLibraryFromWindow(TunnelCrackLibrary &data);

	TunnelCrackBase	*GetTunnelCrackBase(void);
	void		ShowSubtractList(TunnelCrackLibrary &data);
	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_pushButton_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // EDITTUNNELCRACKLIBRARY_H
