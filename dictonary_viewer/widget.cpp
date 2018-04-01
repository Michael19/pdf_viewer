#include "widget.h"
#include "ui_widget.h"

#include <QStandardPaths>
#include <QDir>

#include "mapper.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    m_mapper = new FileMapper();

    QString folder=QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);


    ui->plainTextEdit->appendPlainText(folder);

    QString file_name =folder +  "/y.json";
    m_mapper.load_file(file_name);

    m_phrazes = m_mapper.words();
    m_iter = m_phrazes.begin();

    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(next()));

    this->setLayout(ui->verticalLayout);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::next()
{
    ui->plainTextEdit->clear();

    m_iter = (m_iter+1) != m_phrazes.end() ? m_iter+1 : m_phrazes.begin();

    QString value = *m_iter;

    QVector<DictionaryEntry> out;
    if(m_mapper.is_entry(value,out))
    {
        for(DictionaryEntry entry : out){
            ui->plainTextEdit->appendPlainText(entry.getText() + "  ["+ entry.getTranscription() + "]\n");

            QVector <Translation> transl = entry.getTranslations();
            for(const Translation& tr : transl){
                ui->plainTextEdit->appendPlainText(tr.getText() + "\n");
            }
        }
    }

}
