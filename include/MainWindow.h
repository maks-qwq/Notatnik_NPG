#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QStatusBar>
#include <QTimer>
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
    void onChangeTextColor();
    void toggleBold();
    void toggleItalic();
    void toggleUnderline();

private:
    QTextEdit *textEdit;
    QPushButton *colorButton;
    QStatusBar *statusBar_;

    void openFile();
    void saveFile();
    QTimer *autoSaveTimer; //zapisywanie z timerem
    QString currentFile;

    

    QAction *boldAction;
    QAction *italicAction;
    QAction *underlineAction;
    QString currentFile;

    void onChangeTextColor();


    QStatusBar *statusBar_;
    //void openFile();
    //void saveFile();

    QPushButton *colorButton;


};

#endif // MAINWINDOW_H
