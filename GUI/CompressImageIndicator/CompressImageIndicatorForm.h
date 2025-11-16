#ifndef COMPRESSIMAGEINDICATORFORM_H
#define COMPRESSIMAGEINDICATORFORM_H

#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class CompressImageIndicatorForm;
}

class CompressImageIndicatorForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit CompressImageIndicatorForm(LayersBase *Base ,QWidget *parent = 0);
    ~CompressImageIndicatorForm();

	virtual	bool OnIdle(void)	override;
private:
    Ui::CompressImageIndicatorForm *ui;
};
//-----------------------------------------------------------------------------------------------------------

class	GUICmdReqCountOfCompressImage : public GUICmdPacketBase
{
public:
	GUICmdReqCountOfCompressImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendCountOfCompressImage : public GUICmdPacketBase
{
public:
	int32	Count;

	GUICmdSendCountOfCompressImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

#endif // COMPRESSIMAGEINDICATORFORM_H
