#include "MainWindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QColorDialog>
#include <QPushButton>
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

    // Przycisk otwierania i zapisu pliku
    QPushButton *openButton = new QPushButton("Otwórz", this);
    QPushButton *saveButton = new QPushButton("Zapisz", this);
    layout->addWidget(openButton);
    layout->addWidget(saveButton);

    // Przycisk zmiany koloru tekstu
    colorButton = new QPushButton("Change Text Color", this);
    layout->addWidget(colorButton);

    // Przyciski undo i redo
    undoButton = new QPushButton("Undo", this);
    redoButton = new QPushButton("Redo", this);
    layout->addWidget(undoButton);
    layout->addWidget(redoButton);

    layout->addWidget(textEdit);

    // Połączenia sygnałów z funkcjami
    connect(openButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveFile);
    connect(colorButton, &QPushButton::clicked, this, &MainWindow::onChangeTextColor);
    connect(undoButton, &QPushButton::clicked, this, &MainWindow::onUndo);
    connect(redoButton, &QPushButton::clicked, this, &MainWindow::onRedo);

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

// Zmiana koloru tekstu
void MainWindow::onChangeTextColor() {
    QColor color = QColorDialog::getColor(textEdit->textColor(), this, "Select Text Color");

    if (color.isValid()) {
        textEdit->setTextColor(color);
    }
}

// Cofanie operacji
void MainWindow::onUndo() {
    if (textEdit->document()->isUndoAvailable()) {
        textEdit->undo();
    }
}

// Otwieranie pliku tekstowego
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

// Zapisywanie pliku tekstowego
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

    }
}
//funkcja tworząca nowy plik
void MainWindow::newFile() {
    textEdit->clear();
    currentFile.clear();
    statusBar()->showMessage("Nowy plik utworzony");
}


void MainWindow::onRedo() {
    //  operacja redo
    if (textEdit->document()->isRedoAvailable()) {
        textEdit->redo();
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
