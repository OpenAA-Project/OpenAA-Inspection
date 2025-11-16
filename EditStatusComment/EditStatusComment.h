#ifndef EDITSTATUSCOMMENT_H
#define EDITSTATUSCOMMENT_H

#include <QMainWindow>
#include "ui_EditStatusComment.h"
#include "XStatusController.h"

class EditStatusComment : public QMainWindow
{
	Q_OBJECT

public:
	EditStatusComment(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~EditStatusComment();
	StatusController	StatusControl;
	bool	HTMLMode;
	bool	HTMLModeToopTip;
private:
	Ui::EditStatusCommentClass ui;

	void	ShowOpinions(void);
	virtual	void	resizeEvent ( QResizeEvent * event )	override;

private slots:

	void on_tableWidgetGUIAll_clicked(const QModelIndex &);
	void on_pushButtonRegist_clicked();
	void on_pushButtonClose_clicked();
	void on_pushButtonSave_clicked();
	void on_pushButtonLoad_clicked();
    void on_listWidgetCommentOpinionList_clicked(const QModelIndex &index);
    void on_pushButtonLoadHTML_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonFont_clicked();
    void on_pushButtonLoadHTMLToolTip_clicked();
    void on_pushButtonFontToolTip_clicked();
    void on_pushButtonClearToolTip_clicked();
    void on_checkBoxEnableToolTip_clicked();
};

#endif // EDITSTATUSCOMMENT_H
