/*
 * Copyright (C) 2026
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

#include "XProcess.h"
#include <QCoreApplication>

ProcessManager::ProcessManager(QObject *parent)
    : QObject(parent), m_process(new QProcess(this))
{
}

ProcessManager::~ProcessManager()
{
    // メインプログラム終了時に呼ばれる
    if (m_process->state() != QProcess::NotRunning) {
        m_process->terminate(); // 終了シグナルを送る
        
        // 少し待って終了しなければ強制終了
        if (!m_process->waitForFinished(1000)) {
            m_process->kill();
        }
    }
}

void ProcessManager::killExistingProcess(const QString &programPath)
{
    QString exeName = QFileInfo(programPath).fileName();
    if (exeName.isEmpty()) return;

    qDebug() << "既存プロセスのチェック中: " << exeName;

    // OSのコマンドを使って同名のプロセスを強制終了する
    // ※ QProcess::execute はブロッキング実行（完了するまで待つ）です
#ifdef Q_OS_WIN
    // Windows: taskkill /F /IM <exe名>
    QProcess::execute("taskkill", QStringList() << "/F" << "/IM" << exeName);
#else
    // Linux/macOS: pkill -x <exe名>
    // -x は完全一致
    QProcess::execute("pkill", QStringList() << "-x" << exeName);
#endif
}

void ProcessManager::startExternalProgram(const QString &programPath, 
                                          const QString &workingDir, 
                                          const QStringList &arguments)
{
    // 1. 起動前に既存のプロセスがあれば終了させる
    killExistingProcess(programPath);

    // 2. パラメータの設定
    m_process->setProgram(programPath);
    m_process->setWorkingDirectory(workingDir);
    m_process->setArguments(arguments);

    // 3. 非同期で起動（並行動作）
    // start() は処理をブロックせず即座に戻ってきます
    m_process->start();

    if (m_process->waitForStarted(1000)) {
        qDebug() << "外部プロセス起動成功 (PID:" << m_process->processId() << ")";
    } else {
        qWarning() << "外部プロセス起動失敗:" << m_process->errorString();
    }
}