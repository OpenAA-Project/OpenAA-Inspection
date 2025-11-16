#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <QWidget>
#include <QListWidget>
#include <QMessageBox>

#include "CreateClassFormDialog.h"
#include "PasswordDragFrame.h"
#include "PasswordFileOperator.h"

namespace Ui {
class PasswordManager;
}
class PasswordDragFrame;

class PasswordManager : public QWidget
{
    Q_OBJECT
    
public:
    explicit PasswordManager(QWidget *parent = 0);
    ~PasswordManager();

public:
    void addPassword(QString tagObjectName);
    void loadPasswordFile();
    QString getPasswordFilePath();
public slots:
    void refleshData();
    void reviewClassProperty(int currentRow);
    void openCreateClassForm();
    void deleteClass();
    void updateClassInfo();
    void deleteItem();
    void saveFile();
    void exchangeFlag(int row, int column);
    void refleshTable(int row);
private:
    Ui::PasswordManager *ui;

protected:
    PasswordDragFrame *m_DragFrame;
private:
    PasswordFileOperator m_pfo;
signals:
    void dataChanged();
};

#endif // PASSWORDMANAGER_H
