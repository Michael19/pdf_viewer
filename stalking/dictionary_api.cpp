#include "dictionary_api.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QDebug>
#include <QMessageBox>


YandexDictionary::YandexDictionary()
{}

YandexDictionary::~YandexDictionary()
{}

void YandexDictionary::getLanguages(QMap<QString, QString> languages_)
{
    this->languages = languages_;
}

void YandexDictionary::getTranslationDirections()
{
    // Create a request.
    QUrl url(QString("https://dictionary.yandex.net/api/v1/dicservice.json/getLangs?")
             + QString("key=") + dict_api_key
             );

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Send the request.
    QEventLoop loop;
    QNetworkAccessManager manager;
    connect(&manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);

    // Receive a reply.
    QNetworkReply* reply = manager.get(request);
    loop.exec();

    // Parse the reply.
    QByteArray bytes = reply->readAll();

    /* Another approach to parsing the reply:
     * you can check a type of the reply data
     * in order to choose an appropriate strategy for the parsing process. */
    QJsonDocument doc = QJsonDocument::fromJson(bytes);
    if (doc.isObject())
    {
        QJsonObject obj = doc.object();
        // Check the response codes.
        if(obj.contains("code") && obj.contains("message"))
        {
            QMessageBox messageBox;
            messageBox.critical(0,QString::number(obj.value("code").toDouble()),obj.value("message").toString());
            messageBox.setFixedSize(500,200);
            // TODO: Error handling.
        }
    }
    else if(doc.isArray())
    {
        QJsonArray dirs = doc.array();
        for(QJsonValue v : dirs)
        {
            directions << v.toString();
        }
    }
}

QString YandexDictionary::getDictionaryEntry(const QString &source_lang, const QString &target_lang, const QString &text)
{
    QString dict_dir = languages.key(source_lang) + "-" + languages.key(target_lang);

    qDebug() << dict_dir;

    /* The following commented condition check is not necessary because
     * Dictionary API returns ERR_LANG_NOT_SUPPORTED code
     * if the specified translation direction is not supported.
     * But, anyway, inasmuch as we have our translation directions,
     * we could use it if we wanted to.
     * if (!directions.contains(dict_dir)) ... */

    // Create a request.
    QUrl url(QString("https://dictionary.yandex.net/api/v1/dicservice.json/lookup?")
             + QString("key=") + dict_api_key
             + QString("&lang=") + dict_dir
             + QString("&text=") + text
             //+ QString("&ui=") + <the language of the user's interface for displaying the dictionary entry>
             //+ QString("&flags=") + <search options (bitmask of flags)>
             );

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Send the request.
    QEventLoop loop;
    QNetworkAccessManager manager;
    connect(&manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);

    // Receive a reply.
    QNetworkReply* reply = manager.get(request);
    loop.exec();

    // Parse the reply.
    QByteArray bytes = reply->readAll();
    return QString::fromStdString( bytes.toStdString());
}
