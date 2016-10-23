#include "openwindow.h"
#include "ui_openwindow.h"
#include "sessionmgr.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QMessageBox>

OpenWindow::OpenWindow(MainWindow *qMain, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenWindow)
{
    ui->setupUi(this);
    this->qMain = qMain;
    try {
        QStandardItemModel *model = new QStandardItemModel();
        QJsonArray list = SessionMgr::fileList();
        for (const QJsonValue& value_file : list) {
            QJsonObject file = value_file.toObject();
            QStandardItem *item_file = new QStandardItem(file.value("filename").toString());
            for (const QJsonValue& value_version : file.value("versions").toArray())
                item_file->appendRow(new QStandardItem(value_version.toString()));
            model->appendRow(item_file);
        }
        ui->columnView->setModel(model);
        QList<int> widths;
        widths << 180 << 180 << 0;
        ui->columnView->setColumnWidths(widths);
    }
    catch (std::logic_error& e) {
        QMessageBox::critical(this, "Error", e.what());
        close();
    }
}

OpenWindow::~OpenWindow()
{
    delete ui;
}

void OpenWindow::on_openButton_clicked()
{
    QItemSelectionModel *select = ui->columnView->selectionModel();
    if (select->hasSelection()) {
        QString file_version = select->selectedRows().at(0).data().toString();
        QString file_name = select->selectedRows().at(0).parent().data().toString();
        if (!file_name.isEmpty() && !file_version.isEmpty())
            try {
                QString code = SessionMgr::fileContent(file_name, file_version);
                qMain->file_name = file_name;
                qMain->file_version = file_version;
                qMain->original_code = code;
                qMain->ui->editCode->setPlainText(code);
                qMain->modified = false;
                close();
            }
            catch (const std::logic_error& e) {
                QMessageBox::critical(this, "Error", e.what());
            }
    }
}

void OpenWindow::on_cancelButton_clicked()
{
    close();
}

void OpenWindow::on_columnView_doubleClicked(const QModelIndex &index)
{
    on_openButton_clicked();
}
