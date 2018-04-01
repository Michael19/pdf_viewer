#ifndef STALKING_H
#define STALKING_H

#include "stalking_global.h"
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include "dictionary_api.h"
#include "translate_api.h"
#include "dictonarydata.h"

class STALKINGSHARED_EXPORT Stalking: public QWidget
{
    Q_OBJECT
public:
    Stalking(QWidget *pParent = nullptr);
    ~Stalking();

private:
    void load_dictonary(const QString& path);

    void backup_worlds();

private slots:
    void add_phrase(const QString& str);
    void save_to_file();

private:
    const QString path_dictonary = "/home/michael/Documents/y.json";

private:
    QLineEdit *m_lineEdit;
    QVBoxLayout *m_baseLayout;
    QListWidget *m_listWidget;
    QPushButton *m_saveToFile;
    QStringList *m_phrases;
    QTextEdit *m_plainText;
    YandexDictionary *m_dictionary;
    YandexTranslate *m_translater;

    QHash<QString, QVector<DictionaryEntry>> *m_dictonary;
};

#endif // STALKING_H
