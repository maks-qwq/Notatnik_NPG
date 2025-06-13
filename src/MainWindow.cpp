/*
Projekt notatnika stworzony na zajęcia z Narzędzi Pracy Grupowej - AiR AGH I rok

Przy tworzeniu projektu korzystaliśmy z języka C++ i frameworku Qt

*/
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

    textEdit = new QTextEdit(this); // stworzenie QTextEdit (edytor tekstu)
    QPushButton *openButton = new QPushButton("Otwórz", this);
    QPushButton *saveButton = new QPushButton("Zapisz", this);
    layout->addWidget(openButton);
    layout->addWidget(saveButton);
    layout->addWidget(textEdit);
    
    connect(openButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveFile);

    colorButton = new QPushButton("Zmien koloru tekstu", this); // przycisk do zmiany koloru czcionki
    layout ->addWidget(colorButton);

    // połączenie przycisku z odpowiednim slotem
    connect(colorButton, &QPushButton::clicked, this, &MainWindow::onChangeTextColor);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    setWindowTitle("Notatnik");
        
    statusBar_ = new QStatusBar(this);
    setStatusBar(statusBar_);
    statusBar_->showMessage("Gotowy");

    // ---------------- Menu Plik ---------------- //
    QMenu *fileMenu = menuBar()->addMenu("Plik");
        // opcja nowy w plik
        fileMenu->addAction("Nowy", this, &MainWindow::newFile);
        //opcja otwórz w plik
        fileMenu->addAction("Otwórz", this, &MainWindow::openFile);
        // opcja zapisz w plik
        fileMenu->addAction("Zapisz", this, &MainWindow::saveFile);

    // ustawienie wymiarów okna notatnika
    resize(800, 600);
    //ustawienie położenia notatnika na ekranie
    move(100, 100);
}
// ---------- funkcja Otwórz plik --------------- //
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

// ---------- funkcja zapisz plik --------------- //
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
-------------- a tutaj doszło do podwójnego napisania kodu o tych samych funkcjonalnościach --------------

// ---------- funkcja Otwórz plik --------------- //
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


// ---------- funkcja zapisz plik --------------- //
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


// ---------- funkcja nowy plik --------------- //
void MainWindow::newFile()
{
    textEdit->clear();
    currentFile.clear();
    statusBar()->showMessage("Nowy plik utworzony");
}
// Funkcja zmieniająca kolor czcionki
void MainWindow::onChangeTextColor() {
    QColor color = QColorDialog::getColor(textEdit->textColor(), this, "Wybierz kolor tekstu");
    if (color.isValid()) {
        textEdit->setTextColor(color);
    }

}