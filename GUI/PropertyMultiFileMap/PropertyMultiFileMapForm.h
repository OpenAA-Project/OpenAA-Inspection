#ifndef PROPERTYMULTIFILEMAPFORM_H
#define PROPERTYMULTIFILEMAPFORM_H

#include "XGUIFormBase.h"
#include "XMultiFileMap.h"
#include "XStandardPropertyForm.h"

namespace Ui {
class PropertyMultiFileMapForm;
}

class PropertyMultiFileMapForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyMultiFileMapForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyMultiFileMapForm();

	MultiFileMapBase	*GetMultiFileMapBase(void);

	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	MultiFileMapLibrary	*TempLib;
	int					LibType;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

private:
    Ui::PropertyMultiFileMapForm *ui;
};

#endif // PROPERTYMULTIFILEMAPFORM_H
