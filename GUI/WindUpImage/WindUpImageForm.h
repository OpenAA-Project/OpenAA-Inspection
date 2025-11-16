#ifndef WINDUPIMAGEFORM_H
#define WINDUPIMAGEFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	LayersBase;

namespace Ui {
class WindUpImageForm;
}

class WindUpImageForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit WindUpImageForm(LayersBase *Base,QWidget *parent = 0);
    ~WindUpImageForm();
    
private slots:
    void on_pushButtonExecuteWindup_clicked();

private:
    Ui::WindUpImageForm *ui;
};

class	GUICmdExecuteWindUp : public GUICmdPacketBase
{
public:
	int	ShiftDown	;
	int	WindUp		;
	int	Brightness	;

	GUICmdExecuteWindUp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // WINDUPIMAGEFORM_H
