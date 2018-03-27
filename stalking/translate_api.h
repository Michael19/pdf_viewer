#ifndef TRANSLATE_API_H
#define TRANSLATE_API_H

#include <QObject>

#include <QString>
#include <QStringList>
#include <QMap>

class YandexTranslate : public QObject
{
    Q_OBJECT
public:
    YandexTranslate();
    ~YandexTranslate();

    QMap<QString, QString>& getLanguages() { return languages; }

    void getSupportedLanguages();   // Get the list of supported languages from Translate API.
    QString detectLanguage(const QString &source_text);    // Detect and return a source text language name.
    QStringList translate(const QString &source_lang, const QString &target_lang, const QString &text_to_translate);   // Translate the text and return a result.

public slots:

signals:
    void languagesReceived(QMap<QString, QString> languages);   // This signal is emitted when getSupportedLanguages() is called.

private:
    QString trnsl_api_key = "trnsl.1.1.20180326T192832Z.7c24f476d42c0855.e02f7266029de9ae073df96ae6b7f35f83fb62c5";    // Put your Translate API key here.
    QMap<QString, QString> languages; // Supported languages are values, their codes are keys.
};

#endif // TRANSLATE_API_H
