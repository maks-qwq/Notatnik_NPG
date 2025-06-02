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

    colorButton = new QPushButton("Zmien koloru tekstu", this);
    layout ->addWidget(colorButton);

    connect(colorButton, &QPushButton::clicked, this, &MainWindow::onChangeTextColor);

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

void MainWindow::openFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Otwórz plik");
    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            textEdit->setPlainText(in.readAll());
            file.close();
            QMessageBox::information(this, "Otworzono", "Plik otwarty.");
        } else {
            QMessageBox::warning(this, "Błąd", "Nie można otworzyć pliku.");
        }
    }
}

void MainWindow::saveFile() {
    QString filename = QFileDialog::getSaveFileName(this, "Zapisz plik");
    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
            QMessageBox::information(this, "Zapisano", "Plik zapisany.");
        } else {
            QMessageBox::warning(this, "Błąd", "Nie można zapisać pliku.");
        }
    }
}

MainWindow::~MainWindow() = default;

/*
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
    QString fileName = currentFile.isEmpty() ? QFileDialog::getSaveFileName(this, "Zapisz plik", "", "Pliki tekstowe (*.txt)") : currentFile;
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Błąd", "Nie można zapisać pliku.");
            return;
        }
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
        currentFile = fileName;
        statusBar()->showMessage("Plik zapisany: " + fileName);
    }
}*/

void MainWindow::newFile()
{
    textEdit->clear();
    currentFile.clear();
    statusBar()->showMessage("Nowy plik utworzony");
}
void MainWindow::onChangeTextColor() {
    QColor color = QColorDialog::getColor(textEdit->textColor(), this, "Wybierz kolor tekstu");
    if (color.isValid()) {
        textEdit->setTextColor(color);
    }

}