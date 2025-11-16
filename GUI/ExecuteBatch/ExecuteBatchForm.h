#ifndef EXECUTEBATCHFORM_H
#define EXECUTEBATCHFORM_H

#include "XGUIFormBase.h"
#include "XExecuteBatch.h"
#include <QModelIndex>
#include "MessageForm.h"
#include "XMessagerClient.h"

namespace Ui {
class ExecuteBatchForm;
}

class ExecuteBatchForm : public GUIFormBase
{
    Q_OBJECT

	volatile	bool	CancelMode;
	int			ExecutingLine;
	bool		LoadedNewBatch;
	MessageForm	*HMessage;
	MessagerClient	MClient;
	QString			MessagerIPAddress;
public:
	BatchContainer	BatchData;

	explicit ExecuteBatchForm(LayersBase *base ,QWidget *parent = 0);
    ~ExecuteBatchForm();

	virtual	void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	Sleep(int MiliSec);
	void	ShowMessage(const QString &Message);
	void	CloseMessage(void);

signals:
	void	SignalExecute(void);

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();
    void on_pushButtonInsert_clicked();
    void on_pushButtonModify_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonExecuteAll_clicked();
    void on_pushButtonExecuteOne_clicked();
    void on_pushButtonStop_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonAppend_clicked();
	void SlotExecute(void);
	void	SlotReceived();
private:
    Ui::ExecuteBatchForm *ui;
	
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
	void	ShowList(void);
};

#endif // EXECUTEBATCHFORM_H
