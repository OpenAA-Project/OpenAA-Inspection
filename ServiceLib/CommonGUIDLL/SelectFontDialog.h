#ifndef SELECTFONTDIALOG_H
#define SELECTFONTDIALOG_H

#include <QDialog>
#include <QFont>

namespace Ui {
class SelectFontDialog;
}

class SelectFontDialog : public QDialog
{
    Q_OBJECT
    QFont	CurrentFont;

public:
    explicit    SelectFontDialog(QWidget *parent = 0);
	explicit    SelectFontDialog(const QFont & initial, QWidget *parent = 0);
    ~SelectFontDialog();
    
	QFont	currentFont()const;
	QFont	selectedFont()const;
	void	setCurrentFont(const QFont & initial);

private slots:
    void on_listWidgetFont_currentRowChanged(int currentRow);
    void on_listWidgetStyle_currentRowChanged(int currentRow);
    void on_listWidgetSize_currentRowChanged(int currentRow);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectFontDialog *ui;

	virtual void showEvent ( QShowEvent * event )   override;
};

#endif // SELECTFONTDIALOG_H
