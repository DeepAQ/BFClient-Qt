#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(QString username);
    ~MainWindow();

private slots:
    void on_actionExecute_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
