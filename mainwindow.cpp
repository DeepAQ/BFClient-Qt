#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sessionmgr.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(QString username) :
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
