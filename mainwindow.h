#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QPushButton *welcomeButton;
    QPushButton *resetButton;
    QPushButton *closeButton;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QPushButton* buttons[3][3];

    void checkWinner();
    void showWinner();
    void showDraw();

    bool draw;
    bool gameDone;
    bool win;


public slots:
    void gameButtonClicked();
    void resetButtonClicked();
    void closeButtonClicked();

};
#endif // MAINWINDOW_H
