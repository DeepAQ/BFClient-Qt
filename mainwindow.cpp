#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sessionmgr.h"
#include "loginwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(QString &username) :
    QMainWindow(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuUser->setTitle("Logged in as: " + username);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->editCode->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->editCode->redo();
}

void MainWindow::on_actionCut_triggered()
{
    ui->editCode->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->editCode->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->editCode->paste();
}

void MainWindow::on_actionExecute_triggered()
{
    try {
        auto result = SessionMgr::execute(ui->editCode->toPlainText(), ui->editInput->toPlainText());
        ui->editOutput->setText(result.first + "\n====================\nExecution success, used " + result.second + "ms");
    }
    catch (const std::logic_error e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::aboutQt(this, "About");
}

void MainWindow::on_actionLogout_triggered()
{
    SessionMgr::logout();
    LoginWindow *w = new LoginWindow();
    w->show();
    close();
}
