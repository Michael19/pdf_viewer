/*
                          qpdf

    Copyright (C) 2015 Arthur Benilov,
    arthur.benilov@gmail.com
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.
    This software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    Lesser General Public License for more details.
*/

#include <QAction>
#include <QToolBar>
#include <QIcon>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QTextStream>
#include "QPdfWidget"
#include "mainwindow.h"
#include "stalking.h"

MainWindow::MainWindow(QWidget *pParent, Qt::WindowFlags flags)
    : QMainWindow(pParent, flags)
{
    setWindowIcon(QIcon(":/icons/pdf.png"));

    m_pPdfWidget = new QPdfWidget();
    setCentralWidget(m_pPdfWidget);

    m_stalking = new Stalking();
    m_stalking->show();

    createActions();
    createToolBar();

    connect(m_pPdfWidget, SIGNAL(add_phrase(QString)),
            m_stalking, SLOT(add_phrase(QString)));

    loadFile("/home/michael/Downloads/learnopengl_book.pdf");
}

void MainWindow::loadFile(const QString &path)
{
    if (m_pPdfWidget->loadFile(path)) {
        // Update window title with the file name
        QFileInfo fi(path);
        setWindowTitle(fi.fileName());
    }
}

void MainWindow::saveFilePhazes(const QString &path)
{
    QString filename = path;
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        for(const auto& values : m_pPdfWidget->getSave_phazes())
            stream << values << endl;
    }
}

void MainWindow::createActions()
{
    m_pOpenFileAction = new QAction(QIcon(":/icons/folder.png"), tr("&Open..."), this);
    connect(m_pOpenFileAction, &QAction::triggered, this, &MainWindow::onOpenFile);

    m_pSaveFileAction = new QAction(QIcon(":/icons/folder.png"), tr("&Save..."), this);
    connect(m_pSaveFileAction, &QAction::triggered, this, &MainWindow::onSavePhazes);
}

void MainWindow::createToolBar()
{
    QToolBar *pToolBar = addToolBar(tr("File"));
    pToolBar->setMovable(false);
    pToolBar->addAction(m_pOpenFileAction);
    pToolBar->addAction(m_pSaveFileAction);
}

void MainWindow::onOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open PDF file"),
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                    tr("PDF file (*.pdf)"));
    if (fileName.isEmpty()) {
        return;
    }

    loadFile(fileName);
}

void MainWindow::onSavePhazes()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF file"),
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                                                    );
    if (fileName.isEmpty()) {
        return;
    }

    saveFilePhazes(fileName);
}
