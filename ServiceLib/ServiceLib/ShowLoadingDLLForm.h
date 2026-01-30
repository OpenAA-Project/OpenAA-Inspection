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