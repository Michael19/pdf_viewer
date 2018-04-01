#include "stalking.h"

#include <iostream>

#include <QFile>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTextStream>
#include <QString>

Stalking::Stalking(QWidget *pParent): QWidget(pParent)
{
    m_baseLayout = new QVBoxLayout();
    m_lineEdit = new QLineEdit();
    m_listWidget = new QListWidget();
    m_saveToFile = new QPushButton();
    m_phrases = new QStringList();
    m_plainText = new QTextEdit();

    m_dictionary = new YandexDictionary();
    m_translater = new YandexTranslate();

    m_dictonary = new  QHash<QString, QVector<DictionaryEntry>>();

    // Transfer information about supported languages.
    connect(m_translater, SIGNAL(languagesReceived(QMap<QString,QString>)),
            m_dictionary, SLOT(getLanguages(QMap<QString,QString>)));

    m_translater->getSupportedLanguages();   // Get a list of supported languages.
    m_dictionary->getTranslationDirections();   // Get supported translation directions for Dictionary API.


    m_baseLayout->addWidget(m_lineEdit);
    m_baseLayout->addWidget(m_plainText);
    m_baseLayout->addWidget(m_listWidget);
    m_baseLayout->addWidget(m_saveToFile);

    this->setLayout(m_baseLayout);

    connect(m_saveToFile, SIGNAL(clicked(bool)),
            this,SLOT(save_to_file()));

    load_dictonary(path_dictonary);
}

Stalking::~Stalking()
{
    delete m_baseLayout;
    delete m_lineEdit;
    delete m_phrases;
    delete m_listWidget;
    delete m_saveToFile;
    delete m_plainText;
    delete m_dictonary;
}

void Stalking::load_dictonary(const QString &path)
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
            m_dictonary->insert(entries.at(0).getText(), entries);
        }
        inputFile.close();
    }
}

void Stalking::backup_worlds()
{
    if (!path_dictonary.isEmpty()) {
        QFile file(path_dictonary);
        if (file.open(QIODevice::ReadWrite| QIODevice::Append)) {
            QTextStream stream(&file);
            for(const auto& values : *m_phrases)
                stream << values << endl;
        }
    }
}

void Stalking::add_phrase(const QString &str)
{
    m_lineEdit->setText(str);
    m_listWidget->addItem(str);


    QString respose = m_dictionary->getDictionaryEntry("English", "Russian", str);

    QString text;

    QVector<DictionaryEntry> entries = DictionaryEntry::make_from_string(respose);

    QVector<DictionaryEntry>::iterator iter;
    for(iter = entries.begin(); iter != entries.end(); ++iter)
    {
        iter->showEntry(text);

        m_plainText->setText(text);
    }
    if(entries.size() >=1)
        m_dictonary->insert(entries.at(0).getText(), entries);

    m_phrases->append(respose);

}

void Stalking::save_to_file()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF file"),
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                                                    );
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            for(const auto& values : *m_phrases)
                stream << values << endl;
        }
    }

    backup_worlds();

}
