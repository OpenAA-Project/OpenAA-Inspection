#include "XTypeDef.h"
#include "PasswordManager.h"
#include "ui_PasswordManager.h"
#include <QRegularExpressionValidator>

PasswordManager::PasswordManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PasswordManager)
    , m_pfo(parent)
{
    ui->setupUi(this);

    m_DragFrame = new PasswordDragFrame(this);
    m_DragFrame->setGeometry(ui->frmDrag->geometry());

    m_DragFrame->setPasswordFileOperator(&m_pfo);
    delete ui->frmDrag;

    loadPasswordFile();

    QRegularExpression rx(/**/"[a-zA-Z0-9]*");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->liedPassword->setValidator(validator);

    ui->tableItems->setShowGrid(true);
    ui->tableItems->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableItems->setAutoScroll(true);
    ui->tableItems->setDragEnabled(false);
    ui->tableItems->setSortingEnabled(false);

#if	QT_VERSION<0x050000
    ui->tableItems->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
#else
    ui->tableItems->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
#endif

    refleshData();

    QObject::connect(&m_pfo, SIGNAL(dataChanged()), this, SLOT(refleshData()));// データの変更と各UIの更新の接続
    QObject::connect(ui->listClassNames, SIGNAL(currentRowChanged(int)), this, SLOT(reviewClassProperty(int)));// クラスリストの変更に伴うクラス名とパスワードの表示
    QObject::connect(ui->btnAddClass, SIGNAL(clicked()), this, SLOT(openCreateClassForm()));// クラス新規作成
    QObject::connect(ui->btnDelClass, SIGNAL(clicked()), this, SLOT(deleteClass()));// クラス削除
    QObject::connect(ui->btnUpdateClassInfo, SIGNAL(clicked()), this, SLOT(updateClassInfo()));// クラス情報を表示
    QObject::connect(ui->btnDelItem, SIGNAL(clicked()), this, SLOT(deleteItem()));// パスワードオブジェクトを削除
    QObject::connect(ui->btnFileSave, SIGNAL(clicked()), this, SLOT(saveFile()));// ファイルを保存
    QObject::connect(ui->tableItems, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(exchangeFlag(int,int)));// 解除フラグを変更
    QObject::connect(ui->listClassNames, SIGNAL(currentRowChanged(int)), this, SLOT(refleshTable(int)));// 指定クラスの解除フラグに適用
}

PasswordManager::~PasswordManager()
{
    delete ui;
}

void PasswordManager::reviewClassProperty(int currentRow)
{
    //qDebug("Enter reviewClassProperty(int currentRow)");
    if(0<=currentRow && currentRow<m_pfo.getNumClass())
    {
        QString name = m_pfo.getClassName(currentRow);
        QString pass = m_pfo.getPassword(currentRow);
        ui->liedClassName->setText(name);
        ui->liedPassword->setText(pass);
    }
    //qDebug("Exit reviewClassProperty(int currentRow)");
}

void PasswordManager::openCreateClassForm()
{
    CreateClassFormDialog dialog(this);
    if(dialog.exec()){
        QString className = dialog.GetLiedClassName();
        QString Password = dialog.GetLiedPassword();
        QString name = dialog.GetLiedClassName();
        QString pass = dialog.GetLiedPassword();

        m_pfo.addClass(name, pass);

        refleshData();

        ui->listClassNames->setCurrentRow(m_pfo.getNumClass()-1);
    }
}

void PasswordManager::deleteClass()
{
    int row = ui->listClassNames->currentRow();
    if(row!=-1){
        QString targetClassName = ui->listClassNames->item(row)->text();
		QString	MText="Do you delete Class[%1]?";	//"クラス[%1]を削除しますか？";
        if(QMessageBox::information(this,
            tr("Delete Class"),
            MText.arg(targetClassName),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Cancel))
        {
            m_pfo.delClass(row);
            refleshData();
        }
    }
}

void PasswordManager::updateClassInfo()
{
    int row = ui->listClassNames->currentRow();
    if(row==-1)return;
    QString oldName = m_pfo.getClassName(row);
    QString oldPassword = m_pfo.getPassword(row);

    QString newName = ui->liedClassName->text();
    QString newPassword = ui->liedPassword->text();

    if(oldName==newName && oldPassword==newPassword)return;

	QString	MText="Do you change Class information?\nClassName:%1 -> %2\nPassword:%3 -> %4";	//"クラス情報の変更をしますか？\nクラス名：%1 -> %2\nパスワード：%3 -> %4";
    QString txt = MText.arg(oldName).arg(newName).arg(oldPassword).arg(newPassword);
    int ret = QMessageBox::warning(this,
        "Change Class information",	//"クラス情報変更",
        txt,
        QMessageBox::Ok | QMessageBox::Cancel,
        QMessageBox::Cancel);

    if(ret==QMessageBox::Ok){
        ui->liedClassName->setText(newName);
        ui->liedPassword->setText(newPassword);
        m_pfo.setClassName(row, newName);
        m_pfo.setPassword(row, newPassword);

        refleshData();

        ui->listClassNames->setCurrentRow(row);
    }
}

void PasswordManager::deleteItem(){
    int row = ui->tableItems->currentRow();
    if(row==-1)return;
    QString delItemName = m_pfo.getItem(row);

	QString	MText="Delete item?\nItemName :%1";	//"アイテムを削除しますか？\nアイテム名：%1";
    QString txt = MText.arg(delItemName.split("@").first());
    int ret = QMessageBox::warning(this,
        "Delete item",	//"アイテム削除",
        txt,
        QMessageBox::Ok | QMessageBox::Cancel,
        QMessageBox::Cancel);

    if(ret==QMessageBox::Ok){
        ui->tableItems->removeRow(row);
        m_pfo.delItem(delItemName);

        refleshData();

        ui->tableItems->setCurrentCell(row == 0 ? 0 : row - 1, 1);
    }
}

void PasswordManager::saveFile()
{
    m_pfo.save(getPasswordFilePath());
    emit dataChanged();
}

void PasswordManager::exchangeFlag(int row, int colomn)
{
    if(row==-1)return;
    if(m_pfo.getNumClass()==0)return;
    int classIndex = ui->listClassNames->currentRow();
    if(classIndex==-1)return;
    bool newflag = !m_pfo.getItemFlag(classIndex, row);

    m_pfo.setItemFlag(classIndex, row, newflag);

    if(newflag==true){
        QTableWidgetItem *item = new QTableWidgetItem(QIcon(QPixmap(/**/"images/dragpict.png")), "Will Unlock");
        item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
        ui->tableItems->setItem(row, 0, item);
    }else{
        QTableWidgetItem *item = new QTableWidgetItem(/**/"Never");
        item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
        ui->tableItems->setItem(row, 0, item);
    }
}

void PasswordManager::refleshTable(int row)
{
    if(row==-1)row = 0;
    for(int flagIndex=0; flagIndex<m_pfo.getNumItem(); flagIndex++){
        if( m_pfo.getNumClass()!=0){
            if(m_pfo.getItemFlag(row, flagIndex)==true){
                QTableWidgetItem *item = new QTableWidgetItem(QIcon(QPixmap(/**/"images/dragpict.png")), "Will Unlock");
                item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
                ui->tableItems->setItem(flagIndex, 0, item);
            }else{
                QTableWidgetItem *item = new QTableWidgetItem(/**/"Never");
                item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
                ui->tableItems->setItem(flagIndex, 0, item);
            }
        }else{
            QTableWidgetItem *item = new QTableWidgetItem("No Class!");
            item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
            ui->tableItems->setItem(flagIndex, 0, item);
        }
    }
}

void PasswordManager::refleshData()
{
    //qDebug("Enter refleshData()");

    // Diconnect for updateView before
    QObject::disconnect(ui->listClassNames, SIGNAL(currentRowChanged(int)), this, SLOT(refleshTable(int)));

    int classRow = ui->listClassNames->currentRow();
    ui->listClassNames->clear();
    if(m_pfo.getNumClass()>0){
        for(int classIndex=0; classIndex<m_pfo.getNumClass(); classIndex++)
        {
            ui->listClassNames->addItem(m_pfo.getClassName(classIndex));
        }


        if(classRow<m_pfo.getNumClass())ui->listClassNames->setCurrentRow(classRow);
        if(classRow!=-1 && classRow<m_pfo.getNumClass()){
            ui->liedClassName->setText(m_pfo.getClassName(classRow));
            ui->liedPassword->setText(m_pfo.getPassword(classRow));
        }else{
            ui->liedClassName->clear();
            ui->liedPassword->clear();
        }
    }

    QStringList itemList = m_pfo.getItems();

    ui->tableItems->clear();

    ui->tableItems->setColumnCount(2/*3*/);
    ui->tableItems->setRowCount(itemList.size());

    QStringList labels;
    labels << "State" << "Item Name";// << "Object Info";
    ui->tableItems->setHorizontalHeaderLabels(labels);

    for(int itemIndex = 0; itemIndex<itemList.size(); itemIndex++){
        QStringList itemInfo = itemList[itemIndex].split('@');
        QTableWidgetItem *item = new QTableWidgetItem(itemInfo[0]);
        item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
        ui->tableItems->setItem(itemIndex, 1, item);
        //ui->tableItems->setItem(itemIndex, 2, new QTableWidgetItem(itemInfo[1]));
    }
    if(m_pfo.getNumClass()>0 && m_pfo.getNumItem()>0){
        for(int flagIndex=0; flagIndex<itemList.size(); flagIndex++){
            if(m_pfo.getItemFlag(0, flagIndex)==true){
                QTableWidgetItem *item = new QTableWidgetItem(QIcon(QPixmap(/**/"images/dragpict.png")), "Will Unlock");
                item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
                ui->tableItems->setItem(flagIndex, 0, item);
            }else{
                QTableWidgetItem *item = new QTableWidgetItem(QIcon(QPixmap(/**/"")), "Never");
                item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
                ui->tableItems->setItem(flagIndex, 0, item);
            }
        }
    }

    if(ui->listClassNames->currentRow()==-1 && m_pfo.getNumClass()!=0){
        ui->listClassNames->setCurrentRow(0);
        refleshTable(0);
        reviewClassProperty(0);
    }
    else
        refleshTable(ui->listClassNames->currentRow());

    // Connect for updateView after
    QObject::connect(ui->listClassNames, SIGNAL(currentRowChanged(int)), this, SLOT(refleshTable(int)));

    //qDebug("Exit refleshData()");
}

void PasswordManager::addPassword(QString tagObjectName)
{
    m_DragFrame->addItem(tagObjectName);
}

void PasswordManager::loadPasswordFile()
{
    QString passFileName = qApp->applicationFilePath();
    passFileName = passFileName.left(passFileName.lastIndexOf('.')) + /**/".pwd";
    m_pfo.load(passFileName);
}

QString PasswordManager::getPasswordFilePath()
{
    QString passFileName = qApp->applicationFilePath();
    passFileName = passFileName.left(passFileName.lastIndexOf('.')) + /**/".pwd";
    return passFileName;
}
