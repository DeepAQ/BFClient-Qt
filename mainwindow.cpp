#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sessionmgr.h"
#include "loginwindow.h"
#include "openwindow.h"

#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QString &username, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuUser->setTitle("Logged in as: " + username);
    updateTitle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTitle()
{
    QString title = modified ? "* " : "";
    title.append(file_name.isEmpty() ? "Untitled.bf" : file_name+".bf ("+file_version+")");
    title.append(" - BrainFuck IDE");
    this->setWindowTitle(title);
}

bool MainWindow::checkSaved()
{
    if (!modified) return true;
    int ret = QMessageBox::question(this, "Confirmation", "File not saved, save it?",
                                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
        case QMessageBox::Save:
            on_actionSave_triggered();
            return false;
        case QMessageBox::Discard:
            return true;
        default:
            return false;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (checkSaved())
        event->accept();
    else
        event->ignore();
}

void MainWindow::on_editCode_textChanged()
{
    modified = (ui->editCode->toPlainText() != original_code);
    updateTitle();
}

void MainWindow::on_actionNew_triggered()
{
    if (!checkSaved()) return;
    ui->editCode->clear();
    file_name = file_version = original_code = "";
    modified = false;
    updateTitle();
}

void MainWindow::on_actionOpen_triggered()
{
    if (!checkSaved()) return;
    OpenWindow *w = new OpenWindow(this);
    w->show();
}

void MainWindow::on_actionSave_triggered()
{
    if (!modified) return;
    if (file_name.isEmpty())
        on_actionSave_as_triggered();
    else try {
        QString new_version = SessionMgr::saveFile(ui->editCode->toPlainText(), file_name);
        if (!new_version.isEmpty()) {
            file_version = new_version;
            original_code = ui->editCode->toPlainText();
            modified = false;
            updateTitle();
        }
    }
    catch (const std::logic_error& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString input = QInputDialog::getText(this, "Prompt", "Filename:");
    if (input.isEmpty()) return;
    file_name = input;
    modified = true;
    on_actionSave_triggered();
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
    catch (const std::logic_error& e) {
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
