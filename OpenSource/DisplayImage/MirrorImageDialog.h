#ifndef MIRRORIMAGEDIALOG_H
#define MIRRORIMAGEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class MirrorImageDialog;
}
class	LayersBase;

class MirrorImageDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit MirrorImageDialog(LayersBase *Base,QWidget *parent = 0);
    ~MirrorImageDialog();
    
	bool	FlagMaster;
	bool	FlagTarget;

	bool	MirrorX;
	bool	MirrorY;
	bool	RetMode;

private slots:
    void on_pushButtonGo_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::MirrorImageDialog *ui;
};

#endif // MIRRORIMAGEDIALOG_H
