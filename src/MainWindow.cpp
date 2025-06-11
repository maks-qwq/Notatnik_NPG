#include "MainWindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QColorDialog>
#include <QPushButton>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    textEdit = new QTextEdit(this);
    layout->addWidget(textEdit);
    colorButton = new QPushButton("Zmien koloru tekstu", this);
    layout ->addWidget(colorButton);

    //połączenie przysiuku do zmiany tekstu ze slotem
    connect(colorButton, &QPushButton::clicked, this, &MainWindow::onChangeTextColor);

    //przyciski undo i redo
    undoButton = new QPushButton("Undo", this);
    redoButton = new QPushButton("Redo", this);
    layout->addWidget(undoButton);
    layout->addWidget(redoButton);

    // połączenie przycisków ze slotami
    connect(undoButton, &QPushButton::clicked, this, &MainWindow::onUndo);
    connect(redoButton, &QPushButton::clicked, this, &MainWindow::onRedo);



    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    setWindowTitle("Notatnik");

    resize(800, 600);
    move(100, 100);
}

MainWindow::~MainWindow() = default;

void MainWindow::onChangeTextColor() {
    QColor color = QColorDialog::getColor(textEdit->textColor(), this, "Wybierz kolor tekstu");
    if (color.isValid()) {
        textEdit->setTextColor(color);
    }
}
void MainWindow::onUndo() {
    // operacja undo
    if (textEdit->document()->isUndoAvailable()) {
        textEdit->undo();
    }
}

void MainWindow::onRedo() {
    // operacja redo
    if (textEdit->document()->isRedoAvailable()) {
        textEdit->redo();
    }
}