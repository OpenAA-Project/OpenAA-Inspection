#ifndef SHOWPLAYERINSIDE_H
#define SHOWPLAYERINSIDE_H

#include <QWidget>
#include <QTimer>
#include "XServiceForLayers.h"

namespace Ui {
    class ShowPlayerInside;
}

class ShowPlayerInside : public QWidget,public ServiceForLayers
{
    Q_OBJECT

	QTimer	Timer;
public:
    explicit ShowPlayerInside(LayersBase *base ,QWidget *parent = 0);
    ~ShowPlayerInside();

private:
    Ui::ShowPlayerInside *ui;
private slots:
	void	TimeOut();
};

#endif // SHOWPLAYERINSIDE_H
