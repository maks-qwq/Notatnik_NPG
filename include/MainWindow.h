#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QStatusBar>
#include <QColorDialog>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void openFile();
    void saveFile();
    void newFile();

private:
    QTextEdit *textEdit;
    QString currentFile;

    void onChangeTextColor();


    QTextEdit *textEdit;

    QStatusBar *statusBar_;
    void openFile();
    void saveFile();

    QPushButton *colorButton;

};

#endif // MAINWINDOW_H
