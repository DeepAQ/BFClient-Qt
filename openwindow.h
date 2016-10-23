#ifndef OPENWINDOW_H
#define OPENWINDOW_H

#include <mainwindow.h>

#include <QDialog>

namespace Ui {
class OpenWindow;
}

class OpenWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OpenWindow(MainWindow *qMain, QWidget *parent = 0);
    ~OpenWindow();

private slots:
    void on_openButton_clicked();

    void on_cancelButton_clicked();

    void on_columnView_doubleClicked(const QModelIndex &index);

private:
    Ui::OpenWindow *ui;
    MainWindow *qMain;
};

#endif // OPENWINDOW_H
