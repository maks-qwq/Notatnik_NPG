#include "MainWindow.h"
#include <QVBoxLayout>
#include <QWidget>

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QMainWindow>
#include <QTextEdit>
#include <QToolBar>
#include <QAction>
#include <QApplication>
#include <QTextCharFormat>
#include <QFont>
#include <QKeySequence>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
        
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    textEdit = new QTextEdit(this);
    QPushButton *openButton = new QPushButton("Otwórz", this);
    QPushButton *saveButton = new QPushButton("Zapisz", this);
    layout->addWidget(openButton);
    layout->addWidget(saveButton);
    layout->addWidget(textEdit);
    
    connect(openButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveFile);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    setWindowTitle("Notatnik");
        
    statusBar_ = new QStatusBar(this);
    setStatusBar(statusBar_);
    statusBar_->showMessage("Gotowy");

    // ---------------- Menu Plik ---------------- //
    QMenu *fileMenu = menuBar()->addMenu("Plik");

    fileMenu->addAction("Nowy", this, &MainWindow::newFile);
    fileMenu->addAction("Otwórz", this, &MainWindow::openFile);
    fileMenu->addAction("Zapisz", this, &MainWindow::saveFile);

    resize(800, 600);
    move(100, 100);
}
MainWindow::~MainWindow() = default;
void MainWindow::openFile() {

    QString fileName = QFileDialog::getOpenFileName(this, "Otwórz plik", "", "Pliki tekstowe (*.txt)");

    if (!fileName.isEmpty()) {

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Błąd", "Nie można otworzyć pliku.");
            return;
        }
        QTextStream in(&file);
        textEdit->setPlainText(in.readAll());
        file.close();
        currentFile = fileName;
        statusBar()->showMessage("Plik otwarty: " + fileName);
    }
}

void MainWindow::saveFile() {
    QString filename = currentFile.isEmpty() ? QFileDialog::getSaveFileName(this, "Zapisz plik") : currentFile;
    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
            currentFile = filename;
            statusBar()->showMessage("Plik zapisany: " + filename);
        } else {
            QMessageBox::warning(this, "Błąd", "Nie można zapisać pliku.");
        }
    }
}

void MainWindow::newFile() {
    textEdit->clear();
    currentFile.clear();
    statusBar()->showMessage("Nowy plik utworzony");
}


void MainWindow::toggleBold() {
    QTextCharFormat fmt;
    fmt.setFontWeight(textEdit->fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
    textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::toggleItalic() {
    QTextCharFormat fmt;
    fmt.setFontItalic(!textEdit->fontItalic());
    textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::toggleUnderline() {
    QTextCharFormat fmt;
    fmt.setFontUnderline(!textEdit->fontUnderline());
    textEdit->mergeCurrentCharFormat(fmt);
}
