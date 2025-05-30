#include "MainWindow.h"
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    textEdit = new QTextEdit(this);
    layout->addWidget(textEdit);

    colorButton = new QPushButton("Zmien koloru tekstu", this);
    layout ->addWidget(colorButton);

    connect(colorButton, &QPushButton::clicked, this, &MainWindow::onChangeTextColor);

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