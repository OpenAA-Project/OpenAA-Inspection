#ifndef MOVEXYDIALOG_H
#define MOVEXYDIALOG_H

#include <QDialog>
#include "NList.h"
#include "XServiceForLayers.h"

namespace Ui {
class MoveXYDialog;
}

class	MoveXYList : public NPList<MoveXYList>
{
public:
	int		GlobalPage;
	int		Dx,Dy;

	MoveXYList	&operator=(MoveXYList &src);
};

class MoveXYDialog : public QWidget ,public ServiceForLayers
{
    Q_OBJECT

	NPListPack<MoveXYList>	SavedMoveXYListContainer;
public:
	NPListPack<MoveXYList>	MoveXYListContainer;

	explicit MoveXYDialog(LayersBase *pbase,QWidget *parent = 0);
    ~MoveXYDialog();

	void	Init(void);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonSet_clicked();

private:
    Ui::MoveXYDialog *ui;
};



#endif // MOVEXYDIALOG_H
