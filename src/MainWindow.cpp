/*
#-----------------------------------------------------------------------#
|                                                                       |
|  Projekt notatnika stworzony na zajęcia z Narzędzi Pracy Grupowej     |
|                                AiR AGH I rok                          |
|                                                                       |
#-----------------------------------------------------------------------#

#-----------------------------------------------------------------------#
|                                                                       |
| Przy tworzeniu projektu korzystaliśmy z języka C++ i frameworku Qt    |
| A także z Trello i git'a                                              |
|                                                                       |
#-----------------------------------------------------------------------#


*/
#include "MainWindow.h"
#include <QVBoxLayout>
#include <QWidget>

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

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

    autoSaveTimer = new QTimer(this); //stworzenie timera
    connect(autoSaveTimer, &QTimer::timeout, this, &MainWindow::autoSaveFile);
    autoSaveTimer->start(5 * 60 * 1000); //ustawienie 5 minut jako timer autozapisu


    textEdit = new QTextEdit(this); // stworzenie QTextEdit (edytor tekstu)
    QPushButton *openButton = new QPushButton("Otwórz", this); //przycisk do otwierania pliku tekstowego
    QPushButton *saveButton = new QPushButton("Zapisz", this); //przycisk do zapisu pliku


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


    colorButton = new QPushButton("Zmien koloru tekstu", this); // przycisk do zmiany koloru czcionki
    layout ->addWidget(colorButton);

    // połączenie przycisku z odpowiednim slotem

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




// Cofanie operacji
void MainWindow::onUndo() {
    if (textEdit->document()->isUndoAvailable()) {
        textEdit->undo();

    }
}

// Otwieranie pliku tekstowego
void MainWindow::openFile() {

    QString filename = QFileDialog::getOpenFileName(this, "Otwórz plik"); //otwarcie pliku .txt
    if (!filename.isEmpty()) { //sprawdzenie czy plik istnieje
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) { // sprawdzenie czy plik jest otwarty i czy możemy na nim działać
            QTextStream in(&file);
            textEdit->setPlainText(in.readAll());
            file.close();
            currentFile = filename;
            statusBar()->showMessage("Plik otwarty: " + filename); //komunikat o otwarciu pliku
        } else {
            QMessageBox::warning(this, "Błąd", "Nie można otworzyć pliku."); // komunikat o błędzie otwarcia pliku

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
*/

        }
        QTextStream in(&file);
        textEdit->setPlainText(in.readAll());
        file.close();
        currentFile = filename;
        statusBar()->showMessage("Plik otwarty: " + filename);
    }
}


// ---------- funkcja zapisz plik --------------- //

void MainWindow::saveFile() {

    QString filename = QFileDialog::getSaveFileName(this, "Zapisz plik"); //stworzenie przycisku umożliwiającego zapis
    if (!filename.isEmpty()) { // sprawdzenie czy plik który próbujemy zapisać istnieje

    //QString filename = currentFile.isEmpty() ? QFileDialog::getSaveFileName(this, "Zapisz plik") : currentFile; //jeśli nie podano nazwy pliku, otwórz okno dialogowe zapisu
    //if (!filename.isEmpty()) {

        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) { // sprawdzenie czy plik jest otwarty i czy możemy na nim działać
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
            currentFile = filename;

            statusBar()->showMessage("Plik zapisany: " + filename); //zmiana statusu pliku

        } else {
            QMessageBox::warning(this, "Błąd", "Nie można zapisać pliku."); // wyrzucenie błędu z powodu problemu z plikiem
        }
    }
}



// ---------- funkcja nowy plik --------------- //
void MainWindow::newFile()
{
    textEdit->clear();
    currentFile.clear();
    statusBar()->showMessage("Nowy plik utworzony");
}

// Funkcja zmieniająca kolor czcionki
void MainWindow::onChangeTextColor()
{
    QColor color = QColorDialog::getColor(textEdit->textColor(), this, "Wybierz kolor tekstu");
    if (color.isValid())
    {
        textEdit->setTextColor(color);
    }
}


void MainWindow::onRedo()
{
    //  operacja redo
    if (textEdit->document()->isRedoAvailable()) {
        textEdit->redo();
    }
}


void MainWindow::autoSaveFile() { // funkcja autozapisu
    if (currentFile.isEmpty()) { // nie zapisuje jeśli plik nie został wybrany
        return;
    }

    QFile file(currentFile); //nadpisanie pliku
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close(); //zamknięcie pliku
        statusBar()->showMessage("Autozapisano: " + currentFile); //wiadomość do użytkownika że plik został zapisany
    } else {
        statusBar()->showMessage("Blad autozapisu"); //wiadomość do użytkownika że jest problem z autozapisem pliku

    }
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


