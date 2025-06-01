#include "MainWindow.h"
#include <QVBoxLayout>
#include <QWidget>
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

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    setWindowTitle("Notatnik");
        
    statusBar_ = new QStatusBar(this);
    setStatusBar(statusBar_);
    statusBar_->showMessage("Gotowy");

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
