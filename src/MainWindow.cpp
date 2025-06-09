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
//konstruktor głównego okna aplikacji
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
        
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget); //układ pionowy

    textEdit = new QTextEdit(this);
    QPushButton *openButton = new QPushButton("Otwórz", this); //przycisk do otwierania pliku tekstowego
    QPushButton *saveButton = new QPushButton("Zapisz", this); //przycisk do zapisu pliku
    layout->addWidget(openButton);
    layout->addWidget(saveButton);
    layout->addWidget(textEdit);
    //połączenie sygnałów z funkcjami
    connect(openButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveFile);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    setWindowTitle("Notatnik");
        
    statusBar_ = new QStatusBar(this); //pasek stanu
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
//funkcja otwierająca plik i wczytująca jego zawartość
void MainWindow::openFile() {

    QString fileName = QFileDialog::getOpenFileName(this, "Otwórz plik", "", "Pliki tekstowe (*.txt)");
	//sprwadzenie czy wybrano plik
    if (!fileName.isEmpty()) {

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Błąd", "Nie można otworzyć pliku.");
            return;
        }
        QTextStream in(&file);
        textEdit->setPlainText(in.readAll()); //wczytanie całej zawartości
        file.close();
        currentFile = fileName;
        statusBar()->showMessage("Plik otwarty: " + fileName);
    }
}
//funkcja zapisująca plik tekstowy
void MainWindow::saveFile() {
    QString filename = currentFile.isEmpty() ? QFileDialog::getSaveFileName(this, "Zapisz plik") : currentFile; //jeśli nie podano nazwy pliku, otwórz okno dialogowe zapisu
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
//funkcja tworząca nowy plik
void MainWindow::newFile() {
    textEdit->clear();
    currentFile.clear();
    statusBar()->showMessage("Nowy plik utworzony");
}

//funkcja pogrubienia
void MainWindow::toggleBold() {
    QTextCharFormat fmt;
    fmt.setFontWeight(textEdit->fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
    textEdit->mergeCurrentCharFormat(fmt);
}
//funkcja kursywy
void MainWindow::toggleItalic() {
    QTextCharFormat fmt;
    fmt.setFontItalic(!textEdit->fontItalic());
    textEdit->mergeCurrentCharFormat(fmt);
}
//funkcja podkreślenia
void MainWindow::toggleUnderline() {
    QTextCharFormat fmt;
    fmt.setFontUnderline(!textEdit->fontUnderline());
    textEdit->mergeCurrentCharFormat(fmt);
}
