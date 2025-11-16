#ifndef MESSAGEFORM_H
#define MESSAGEFORM_H

#include <QWidget>
#include "XServiceForLayers.h"

namespace Ui {
class MessageForm;
}

class MessageForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit MessageForm(LayersBase *base, QWidget *parent = 0);
    ~MessageForm();

	void	SetMessage(const QString &Message);

private slots:
    void on_pushButtonClose_clicked();

private:
    Ui::MessageForm *ui;
};

#endif // MESSAGEFORM_H
