#pragma once

#include <QString>
#include <QStringList>

bool IsEmptyDirectory(const QString &dirPath);

QStringList GetDirectoryFileList(const QString &dirPath, const QString &wildCardFilter="?*");

bool DeleteFileApi(const QString &filename);

bool RemoveDirectoryApi(const QString &directoryPath);