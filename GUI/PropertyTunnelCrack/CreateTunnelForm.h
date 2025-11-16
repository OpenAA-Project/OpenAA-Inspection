#ifndef CREATETUNNELFORM_H
#define CREATETUNNELFORM_H

#include <QDialog>
#include "ui_CreateTunnelForm.h"
#include "XTunnelCrack.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class CreateTunnelForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	CreateTunnelForm(LayersBase *base ,QWidget *parent = 0);
	~CreateTunnelForm();

	TunnelCrackLibrary	*TempLib;
	int	SelectedLibID;
private:
	Ui::CreateTunnelFormClass ui;

	TunnelCrackBase	*GetTunnelCrackBase(void);
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	int		LibType;

private slots:
	void on_ButtonOK_clicked();
	void on_pushButtonEditLibrary_clicked();
	void on_pushButtonCancel_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // CREATETUNNELFORM_H
