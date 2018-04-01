#include "filemapper.h"
#include <iostream>

#include <QFile>
#include <QTextStream>

FileMapper::FileMapper()
{

}

void FileMapper::load_file(const QString &path)
{
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            std::cout << "line" << std::endl;

            QVector<DictionaryEntry> entries = DictionaryEntry::make_from_string(line);
            if(entries.size() >=1)
                m_dictonary.insert(entries.at(0).getText(), entries);
        }
        inputFile.close();
    }
}

bool FileMapper::is_entry(const QString &phraze, QVector<DictionaryEntry> &result)
{
    QHash<QString, QVector<DictionaryEntry>>::const_iterator out_iter = m_dictonary.find(phraze);
    if(out_iter != m_dictonary.end()){
        result = out_iter.value();
        return true;
    }

    return false;
}

int FileMapper::count() const
{
    return m_dictonary.size();
}

QList<QString> FileMapper::words() const
{
    return m_dictonary.keys();
}
