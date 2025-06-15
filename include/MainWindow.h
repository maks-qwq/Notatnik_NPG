#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

#include <QStatusBar>
#include <QTimer>

#include <QColorDialog>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void autoSaveFile();

    private slots:
        void onChangeTextColor();  // Slot do zmiany koloru czcionki
    void onUndo();  // Slot do wykonania operacji undo
    void onRedo();  // Slot do wykonania operacji redo

private slots:
    void showAboutDialog(); // ← Dodany slot

private:
    QTextEdit *textEdit;  // Edytor tekstu
    QPushButton *colorButton;  // Przycisk do zmiany koloru
    QPushButton *undoButton;  // Przycisk undo
    QPushButton *redoButton;  // Przycisk redo

private slots:

    void openFile();
    void saveFile();
    void newFile();
    //void onChangeTextColor();
    void toggleBold();
    void toggleItalic();
    void toggleUnderline();

private:



    QTimer *autoSaveTimer; //zapisywanie z timerem
    QString currentFile;

    

    QAction *boldAction;
    QAction *italicAction;
    QAction *underlineAction;


    //void onChangeTextColor();


    QStatusBar *statusBar_;
    //void openFile();
    //void saveFile();




};

#endif // MAINWINDOW_H