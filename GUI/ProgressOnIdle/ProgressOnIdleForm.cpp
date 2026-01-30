/*
 * Copyright (C) 2020
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ProgressOnIdleResource.h"
#include "ProgressOnIdleForm.h"

ProgressOnIdleForm::ProgressOnIdleForm(LayersBase *Base,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ProgressOnIdleForm::~ProgressOnIdleForm()
{

}
void	ProgressOnIdleForm::ResizeAction()
{
	ui.progressBar->resize(width(),height());
}

bool ProgressOnIdleForm::OnIdle(void)
{
	if(ui.progressBar->value()>=ui.progressBar->maximum()){
		ui.progressBar->setValue(0);
	}
	else{
		ui.progressBar->setValue(ui.progressBar->value()+1);
	}
	return true;
}