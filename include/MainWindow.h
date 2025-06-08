#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QStatusBar>
#include <QTimer>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTextEdit *textEdit;
    QStatusBar *statusBar_;
    void openFile();
    void saveFile();
    QTimer *autoSaveTimer; //zapisywanie z timerem
    QString currentFile;
};

#endif // MAINWINDOW_H
