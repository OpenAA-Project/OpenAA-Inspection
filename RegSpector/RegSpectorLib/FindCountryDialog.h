/*
 * Copyright (C) 2022
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

#ifndef FINDCOUNTRYDIALOG_H
#define FINDCOUNTRYDIALOG_H

#include <QDialog>
#include "XServiceRegSpector.h"

namespace Ui {
class FindCountryDialog;
}

class FindCountryDialog : public QDialog
{
    Q_OBJECT

    QStringList CodeList;
public:
    explicit FindCountryDialog(const QString &CSVFileName=CountryListFileName,QWidget *parent = nullptr);
    ~FindCountryDialog();

    QString CountryCode;

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::FindCountryDialog *ui;

    virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // FINDCOUNTRYDIALOG_H