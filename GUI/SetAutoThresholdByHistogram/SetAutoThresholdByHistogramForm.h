#ifndef SETAUTOTHRESHOLDBYHISTOGRAMFORM_H
#define SETAUTOTHRESHOLDBYHISTOGRAMFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class SetAutoThresholdByHistogramForm;
}

class SetAutoThresholdByHistogramForm : public GUIFormBase
{
    Q_OBJECT
public:
    int32   LibType;
    int32   LibID;
    IntList HistID;
    int32   Strength;
	QString	ButtonName;

    explicit SetAutoThresholdByHistogramForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~SetAutoThresholdByHistogramForm();

    virtual void	ReadyParam(void)    override;
    virtual void	BuildForShow(void)  override;
	virtual	bool	SaveContent(QIODevice *f)   override;
	virtual	bool	LoadContent(QIODevice *f)   override;
    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_horizontalSliderStrength_valueChanged(int value);
    void on_toolButton_clicked();

private:
    Ui::SetAutoThresholdByHistogramForm *ui;

	void    ShowStrength(void);
	void    ShowSlider(void);
	void    UpdateThresholdByHistogram(void);
};

class	GUICmdSetAutoThresholdByHistogram: public GUICmdPacketBase
{
public:
    int32   LibType;
    int32   LibID;
    IntList HistID;
    int32   Strength;

	GUICmdSetAutoThresholdByHistogram(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // SETAUTOTHRESHOLDBYHISTOGRAMFORM_H
