#ifndef LISTGENERATECHILDLIBRARYFORM_H
#define LISTGENERATECHILDLIBRARYFORM_H

#include "XGUIFormBase.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "LibFolderForm.h"

namespace Ui {
class ListGenerateChildLibraryForm;
}

class	GeneralLibFolderForm;
class	ListGenerateChildLibraryForm;

class	LibFolderTreeForm : public LibFolderForm
{
	ListGenerateChildLibraryForm	*Parent;
public:
	LibFolderTreeForm(ListGenerateChildLibraryForm *p ,int libType ,LayersBase *lbase ,QWidget *parent = 0);

protected:
	virtual	void mouseDoubleClickEvent ( QMouseEvent * event );
};

class ListGenerateChildLibraryForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit ListGenerateChildLibraryForm(LayersBase *Base,QWidget *parent = 0);
    ~ListGenerateChildLibraryForm();

	virtual	void	BuildForShow(void)		override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
	virtual	void	RxSync(QByteArray &f)	override;


private slots:
    void on_pushButtonGenerate_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void	ResizeAction();
public slots:
    void on_pushButtonSelect_clicked();

private:
    Ui::ListGenerateChildLibraryForm *ui;

	LibFolderTreeForm	*pLibFolderForm;
	int		LibFolderID;
};

#endif // LISTGENERATECHILDLIBRARYFORM_H
