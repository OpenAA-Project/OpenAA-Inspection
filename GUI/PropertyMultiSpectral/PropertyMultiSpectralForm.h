#ifndef PROPERTYMULTISPECTRALFORM_H
#define PROPERTYMULTISPECTRALFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XMultiSpectral.h"
#include "XStandardPropertyForm.h"

namespace Ui {
class PropertyMultiSpectralForm;
}

class PropertyMultiSpectralForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT

public:
    explicit PropertyMultiSpectralForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyMultiSpectralForm();
    
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

	void	ClearLibList(void);
	void	SetLib(int LibID);

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

private slots:
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_pushButtonEditLibrary_clicked();

private:
    Ui::PropertyMultiSpectralForm *ui;

    MultiSpectralBase	*GetMultiSpectralBase(void);
	AlgorithmLibraryLevelContainer		*LLib;
	int				LibType;

	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;

	void	ShowList(void);
};

#endif // PROPERTYMULTISPECTRALFORM_H
