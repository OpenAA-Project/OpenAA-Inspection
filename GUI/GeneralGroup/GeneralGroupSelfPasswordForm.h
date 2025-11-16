#pragma once

#include <QDialog>
#include "ui_GeneralGroupSelfPasswordForm.h"
#include "XServiceForLayers.h"

class GeneralGroupSelfPasswordForm : public QDialog,public ServiceForLayers
{
public:
	GeneralGroupSelfPasswordForm(LayersBase *base, QWidget *parent=0, Qt::WindowFlags=Qt::Widget);

public:
	QString password() const;

private:
	Ui::GeneralGroupSelfPasswordClass ui;
};
