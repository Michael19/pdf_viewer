#ifndef DICTIONARY_API_H
#define DICTIONARY_API_H

#include <QObject>

#include <QVector>
#include <QString>
#include <QStringList>
#include <QMap>

class QTextStream;


class YandexDictionary : public QObject
{
    Q_OBJECT
public:
    YandexDictionary();
    ~YandexDictionary();

    QMap<QString, QString>& getLanguages() { return languages; }

    void getTranslationDirections();// Get a list of translation directions from Dictionary API.
    QString getDictionaryEntry(const QString& source_lang, const QString& target_lang, const QString& text);    // Get an automatically generated dictionary entry for a word or phrase.

public slots:
    void getLanguages(QMap<QString, QString> languages_);    // Get languages and their codes from Translate API.

private:
    QString dict_api_key = "dict.1.1.20180326T192530Z.1d55d60ab82d06ca.088871108ac6e257c8bfbfc1cbfbac87f155008d";   // Put your Dictionary API key here.
    QStringList directions; // Translation directions. They can be "en-en", "ru-ru", for example, but we don't consider this case.
    QMap<QString, QString> languages; // Supported languages are values, their codes are keys. They're acquired from Translate API!
};

#endif // DICTIONARY_API_H
