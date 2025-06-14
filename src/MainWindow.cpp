#include "MainWindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    textEdit = new QTextEdit(this);
    layout->addWidget(textEdit);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    setWindowTitle("Notatnik");

    resize(800, 600);
    move(100, 100);

    // 🔽 Dodajemy menu „Pomoc” z akcją „O programie”
    QMenu *helpMenu = menuBar()->addMenu("Pomoc");
    QAction *aboutAction = new QAction("O programie", this);
    helpMenu->addAction(aboutAction);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);
}

MainWindow::~MainWindow() = default;

// 🔽 Dodajemy funkcję showAboutDialog
void MainWindow::showAboutDialog() {
    QString aboutText =
        "📝 <b>Notatnik</b><br>"
        "Wersja 1.0.0<br><br>"
        "Prosty edytor tekstu napisany w Qt.<br><br>"
        "Autorzy: Maksymilian Zych, Hubert Wawak, Wojciech Trojak, Adraizn Witek, Michał Wójcik <br><br>"
        "© 2025<br>";

    QMessageBox::about(this, "O programie", aboutText);
}