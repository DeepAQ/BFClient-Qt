#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "sessionmgr.h"
#include "mainwindow.h"

#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->editUser->text(),
            password = ui->editPass->text(),
            server = ui->editServer->text();
    if (username.isEmpty() || password.isEmpty() || server.isEmpty())
        return;
    SessionMgr::host = server;
    try {
        SessionMgr::login(username, password);
        // TODO after login
    }
    catch (const std::logic_error e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}
