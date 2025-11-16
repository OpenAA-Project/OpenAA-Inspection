#ifndef COPYLIBRARYFORM_H
#define COPYLIBRARYFORM_H

#include <QDialog>
#include "ui_CopyLibraryForm.h"
#include "XAlgorithmLibrary.h"
#include "XDataAlgorithm.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class CopyLibraryForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	CopyLibraryForm(const QString &AlgoRoot , const QString &AlgoName 
					, LayersBase *base ,QWidget *parent = 0);
	~CopyLibraryForm();

	QString AlgoRoot;
	QString AlgoName;
	AlgorithmBase	*ABase;

	int		LibType;
	GeneralLibFolderForm	*pLibFolderFormSrc;
	int		LibFolderIDSrc;
	void	ShowLibrarySrc(AlgorithmLibrary &data);

	GeneralLibFolderForm	*pLibFolderFormDst;
	int		LibFolderIDDst;
	void	ShowLibraryDst(AlgorithmLibrary &data);

private:
	Ui::CopyLibraryFormClass ui;

	AlgorithmLibraryListContainer	LibIDListSrc;
	AlgorithmLibraryListContainer	LibIDListDst;

private slots:
	void on_pushButtonAll_clicked();
	void on_pushButtonClose_clicked();
	void on_pushButtonCopy_clicked();
	void	SlotSelectLibFolderSrc(int LibFolderID ,QString FolderName);
	void	SlotSelectLibFolderDst(int LibFolderID ,QString FolderName);
};

#endif // COPYLIBRARYFORM_H
