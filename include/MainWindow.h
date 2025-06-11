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
};

#endif // MAINWINDOW_H
