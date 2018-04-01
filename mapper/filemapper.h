#ifndef FILEMAPPER_H
#define FILEMAPPER_H

#include <QObject>
#include <QHash>

#include "dictonarydata.h"

class FileMapper
{
public:
    FileMapper();

    void load_file(const QString& path);

    bool is_entry(const QString& phraze, QVector<DictionaryEntry> & result);

    int count() const;

    QList<QString> words()const;

private:
    QString m_path;
    QHash<QString, QVector<DictionaryEntry>> m_dictonary;

};

#endif // FILEMAPPER_H
