#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTextEdit *textEdit;
};
void PlikZapisany() {
    cout << "Plik zapisany";
}

void PlikOtwarty() {
    cout << "Plik otwarty";
}

#endif // MAINWINDOW_H
