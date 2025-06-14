#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QColorDialog>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    private slots:
        void onChangeTextColor();  // Slot do zmiany koloru czcionki
    void onUndo();  // Slot do wykonania operacji undo
    void onRedo();  // Slot do wykonania operacji redo

private:
    QTextEdit *textEdit;  // Edytor tekstu
    QPushButton *colorButton;  // Przycisk do zmiany koloru
    QPushButton *undoButton;  // Przycisk undo
    QPushButton *redoButton;  // Przycisk redo

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
