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
    QString file_name = "";
    QString file_version = "";
    QString original_code = "";
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(QString &username);
    ~MainWindow();

private slots:
    void on_actionExecute_triggered();

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionLogout_triggered();

    void on_editCode_textChanged();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

private:
    Ui::MainWindow *ui;
    bool modified = false;
    void updateTitle();
};

#endif // MAINWINDOW_H
