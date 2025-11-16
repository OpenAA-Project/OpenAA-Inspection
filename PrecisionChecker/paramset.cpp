#include "paramset.h"

#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QMessageBox>

ParamSet::ParamSet(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	bAxisFlg = false;

	defParamFnam = "./PrecisionChecker.dat";
	loadParam(defParamFnam);
}

ParamSet::~ParamSet()
{

}


void ParamSet::on_pushButton_clicked()
{
	close();
}

void ParamSet::getThreshValue(int &min, int &max, bool &mode) {
	min = ui.txtThreshVal_1->text().toInt();
	max = ui.txtThreshVal_2->text().toInt();
	if ( ui.chkEffect->checkState() == Qt::Checked ) {
		mode = true;
	} else {
		mode = false;
	}
}

bool ParamSet::getAxisVal(double &val) {
	if ( bAxisFlg == false ) {
		val = ui.txtPadVal_1->text().toDouble();
		return false;
	} else {
		val = ui.txtPadVal_2->text().toDouble();
		return true;
	}
}

int ParamSet::getZScale(int idx) {
	QLineEdit *txtEdit;
	switch( idx ) {
	case 1 :
		txtEdit = ui.txtScaleZ_1;
		break;
	case 2 :
		txtEdit = ui.txtScaleZ_2;
		break;
	case 3 :
		txtEdit = ui.txtScaleZ_3;
		break;
	case 4 :
		txtEdit = ui.txtScaleZ_4;
		break;
	default :
		return 1;
	}

	int ret = txtEdit->text().toInt();
	return ret;
}

bool ParamSet::getChartType(int idx) {
	QCheckBox *chkBox;
	switch( idx ) {
	case 1 :
		chkBox = ui.chkBar_1;
		break;
	case 2 :
		chkBox = ui.chkBar_2;
		break;
	case 3 :
		chkBox = ui.chkBar_3;
		break;
	case 4 :
		chkBox = ui.chkBar_4;
		break;
	default :
		return false;
	}

	if ( chkBox->checkState() == Qt::Checked ) {
		return true;
	}
	return false;
}

void ParamSet::getInitRotation(int &x, int &y, int &z) {
	x = ui.txtRotation_x->text().toInt();
	y = ui.txtRotation_y->text().toInt();
	z = ui.txtRotation_z->text().toInt();
}

void ParamSet::getPadValueRange(int &min, int &max) {
	min = ui.txtPadValue_1->text().toInt();
	max = ui.txtPadValue_2->text().toInt();
}

void ParamSet::getBrightMode(bool &mode) {
	mode = false;
	if ( ui.chkMode->checkState() == Qt::Checked ) {
		mode = true;
	}
}

void ParamSet::on_rbAxis_1_toggled(bool)
{
	if ( ui.rbAxis_1->isChecked() == true ) {
		bAxisFlg = false;
	} else {
		bAxisFlg = true;
	}
}

void ParamSet::on_rbAxis_2_toggled(bool)
{
	if ( ui.rbAxis_2->isChecked() == true ) {
		bAxisFlg = true;
	} else {
		bAxisFlg = false;
	}
}


void ParamSet::on_btnSelect_clicked()
{
	QString fldNam = QFileDialog::getExistingDirectory(this,tr("Output Folder Select"),
		ui.txtOutDir->text(),QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
	if ( fldNam == "" ) {
		return;
	}
	ui.txtOutDir->setText(fldNam);
}

QString ParamSet::getOutDir() {
	return ui.txtOutDir->text();
}

void ParamSet::getAvgXY(int &x, int &y) {
	x = ui.avgx->value();
	y = ui.avgy->value();
}

bool ParamSet::loadParam(QString fnam) {
	QFile file(fnam);
	if ( file.exists() == false ) {
		return false;
	}
	if ( !file.open(QIODevice::ReadOnly|QIODevice::Text) ) {
		return false;
	}
	QTextStream in(&file);
	QString buf = in.readLine();
	QStringList lst = buf.split(",");
	ui.txtThreshVal_1->setText(lst.at(0));
	ui.txtThreshVal_2->setText(lst.at(1));
	ui.txtPadValue_1->setText(lst.at(2));
	ui.txtPadValue_2->setText(lst.at(3));
	ui.txtOutDir->setText(lst.at(4));
	ui.txtRotation_x->setText(lst.at(5));
	ui.txtRotation_y->setText(lst.at(6));
	ui.txtRotation_x->setText(lst.at(7));
	ui.txtScaleZ_1->setText(lst.at(8));
	ui.txtScaleZ_2->setText(lst.at(9));
	ui.txtScaleZ_3->setText(lst.at(10));
	ui.txtScaleZ_4->setText(lst.at(11));
	if ( lst.at(12) == "true" ) {
		ui.rbAxis_1->setChecked(true);
		ui.rbAxis_2->setChecked(false);
		bAxisFlg = false;
	} else {
		ui.rbAxis_1->setChecked(false);
		ui.rbAxis_2->setChecked(true);
		bAxisFlg = true;
	}
	ui.txtPadVal_1->setText(lst.at(13));
	ui.txtPadVal_2->setText(lst.at(14));

	if ( lst.size() > 15 ) {
		ui.avgx->setValue(lst.at(15).toInt());
		ui.avgy->setValue(lst.at(16).toInt());
	} else {
		ui.avgx->setValue(3);
		ui.avgy->setValue(2);
	}
	if ( lst.at(17) == "true" ) {
		ui.chkEffect->setChecked(true);
	} else {
		ui.chkEffect->setChecked(false);
	}
	if ( lst.at(18) == "true" ) {
		ui.chkMode->setChecked(true);
	} else {
		ui.chkMode->setChecked(false);
	}
	file.close();
	return true;
}

bool ParamSet::saveParam(QString fnam) {
	if ( fnam == "" ) {
		fnam = defParamFnam;
	}

	QString buf = "";
	buf += ui.txtThreshVal_1->text()+",";
	buf += ui.txtThreshVal_2->text()+",";
	buf += ui.txtPadValue_1->text()+",";
	buf += ui.txtPadValue_2->text()+",";
	buf += ui.txtOutDir->text()+",";
	buf += ui.txtRotation_x->text()+",";
	buf += ui.txtRotation_y->text()+",";
	buf += ui.txtRotation_z->text()+",";
	buf += ui.txtScaleZ_1->text()+",";
	buf += ui.txtScaleZ_2->text()+",";
	buf += ui.txtScaleZ_3->text()+",";
	buf += ui.txtScaleZ_4->text()+",";
	if ( ui.rbAxis_1->isChecked() == true ) {
		buf += "true,";
	} else {
		buf += "false,";
	}
	buf += ui.txtPadVal_1->text()+",";
	buf += ui.txtPadVal_2->text()+",";
	buf += ui.avgx->text()+",";
	buf += ui.avgy->text()+",";
	
	if ( ui.chkEffect->checkState() == Qt::Checked ) {
		buf += "true,";
	} else {
		buf += "false,";
	}
	if ( ui.chkMode->checkState() == Qt::Checked ) {
		buf += "true,";
	} else {
		buf += "false,";
	}
	QFile file(fnam);
	if ( !file.open(QIODevice::WriteOnly|QIODevice::Text) ) {
		return false;
	}
	QTextStream out(&file);
	out << buf << "\n";
	file.close();

	return true;
}

void ParamSet::on_pushButton_2_clicked()
{
	QString fnam = QFileDialog::getOpenFileName(this,tr("LoadParam File Select"),"./","*.dat");
	if ( fnam == "" ) {
		return;
	}
	loadParam(fnam);
}

void ParamSet::on_pushButton_3_clicked()
{

	QString	fnam = QFileDialog::getSaveFileName(this,tr("SaveParam File Select"),"./"+defParamFnam,"*.dat");
	if ( fnam == "" ) {
		return;
	}
	saveParam(fnam);
}