#ifndef SELECTRESULTLOTFRAMEDIALOG_H
#define SELECTRESULTLOTFRAMEDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QByteArray>
#include <QIODevice>
#include <QBuffer>
#include "XIntClass.h"
#include "XServiceForLayers.h"
#include "XDateTime.h"

namespace Ui {
class SelectResultLotFrameDialog;
}
class	GUIFormBase;

class SelectResultLotFrameDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	GUIFormBase	*ParentGUI;
public:
    explicit SelectResultLotFrameDialog(bool ShowMode ,LayersBase *Base ,QWidget *parent = 0, QWidget *parentGUI=0);
    ~SelectResultLotFrameDialog();

	bool		RetMode;
	int			SelectedLotAutoCount;
	QString		SelectedLotID;
	int			SelectedIDNumber;
	QString		SelectedLotName;
	XDateTime	SelectedLastUpdated;
	QString		SelectedRemark;

	bool	RxSync(QByteArray &f);
	bool	RxSync(QIODevice &Buff);

	virtual	void	TxSync(QBuffer &f);

private slots:
    void on_ButtonCreate_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::SelectResultLotFrameDialog *ui;

	IntList	LotAutoCounts;

	bool ExecuteCreateNew(void);
};

#endif // SELECTRESULTLOTFRAMEDIALOG_H
