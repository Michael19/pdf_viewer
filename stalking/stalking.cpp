#include "stalking.h"

#include <QFile>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTextStream>

Stalking::Stalking(QWidget *pParent): QWidget(pParent)
{
    m_baseLayout = new QVBoxLayout();
    m_lineEdit = new QLineEdit();
    m_listWidget = new QListWidget();
    m_saveToFile = new QPushButton();
    m_phrases = new QStringList();

    m_baseLayout->addWidget(m_lineEdit);
    m_baseLayout->addWidget(m_listWidget);
    m_baseLayout->addWidget(m_saveToFile);

    this->setLayout(m_baseLayout);

    connect(m_saveToFile, SIGNAL(clicked(bool)),
            this,SLOT(save_to_file()));
}

Stalking::~Stalking()
{
    delete m_baseLayout;
    delete m_lineEdit;
    delete m_phrases;
    delete m_listWidget;
    delete m_saveToFile;
}

void Stalking::add_phrase(const QString &str)
{
    m_lineEdit->setText(str);
    m_listWidget->addItem(str);
    m_phrases->append(str);
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

}
