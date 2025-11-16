#ifndef INDICATORWINDOW_H
#define INDICATORWINDOW_H

#include <QDialog>
#include <QTimer>

namespace Ui {
    class IndicatorWindow;
}

class CopyMultiple;

class IndicatorWindow : public QWidget
{
    Q_OBJECT

	QTimer	TM;
	CopyMultiple	*Parent;
	int		DestCount;
public:
    explicit IndicatorWindow(QWidget *parent = 0);
    ~IndicatorWindow();

	virtual	void closeEvent ( QCloseEvent * event )	override;

private:
    Ui::IndicatorWindow *ui;

private slots:
	void	SlotTimeout ();

};

#endif // INDICATORWINDOW_H
