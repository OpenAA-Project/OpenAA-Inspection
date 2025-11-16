#ifndef SHOWLOADINGDLLFORM_H
#define SHOWLOADINGDLLFORM_H

#include <QWidget>
#include "XServiceForLayers.h"

namespace Ui {
    class ShowLoadingDLLForm;
}

class ShowLoadingDLLForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

	bool	Tested;
	QString	DLLLogFile;
public:
    explicit ShowLoadingDLLForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowLoadingDLLForm();

	void	Add(const QString &FileName);
	void	TestAdd(const QString &FileName);
private:
    Ui::ShowLoadingDLLForm *ui;
};

#endif // SHOWLOADINGDLLFORM_H
