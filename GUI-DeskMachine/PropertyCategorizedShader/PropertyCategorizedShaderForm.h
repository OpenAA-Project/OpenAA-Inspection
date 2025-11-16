#ifndef PROPERTYCATEGORIZEDSHADERFORM_H
#define PROPERTYCATEGORIZEDSHADERFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyCategorizedShaderForm.h"
#include "XCategorizedShader.h"
#include "XPropertyCategorizedShaderPacket.h"

class PropertyCategorizedShaderForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyCategorizedShaderForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyCategorizedShaderForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	StartPage	(void)	override;

private:
	Ui::PropertyCategorizedShaderFormClass ui;
};

#endif // PROPERTYCATEGORIZEDSHADERFORM_H
