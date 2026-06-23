#include "settingchild_appLauncher.h"
#include "./ui_settingchild_appLauncher.h"

#include "../../../GlobalConstants.h"
#include "ZcJsonLib.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>

SettingChild_AppLauncher::SettingChild_AppLauncher(QWidget *parent)
    : QWidget(parent), ui(new Ui::SettingChild_AppLauncher)
{
    ui->setupUi(this);
    ui->tableWidget_Commands->horizontalHeader()->setStretchLastSection(true);
    loadFromConfig();
}

SettingChild_AppLauncher::~SettingChild_AppLauncher()
{
    delete ui;
}

void SettingChild_AppLauncher::on_BreadcrumbBar_breadcrumbClicked(
    QString breadcrumb, QStringList lastBreadcrumbList)
{
    Q_UNUSED(breadcrumb);
    Q_UNUSED(lastBreadcrumbList);
}

void SettingChild_AppLauncher::loadFromConfig()
{
    ZcJsonLib config(JsonSettingPath);
    const QJsonArray commands =
        config.value("appLauncher/commands", QJsonArray()).toArray();

    ui->tableWidget_Commands->setRowCount(0);
    for (int i = 0; i < commands.size(); ++i)
    {
        const QJsonObject obj = commands[i].toObject();
        const QString keyword = obj.value("keyword").toString();
        const QString path = obj.value("path").toString();
        if (keyword.isEmpty() && path.isEmpty())
            continue;

        const int row = ui->tableWidget_Commands->rowCount();
        ui->tableWidget_Commands->insertRow(row);

        auto *itemIndex = new QTableWidgetItem(QString::number(row + 1));
        itemIndex->setFlags(itemIndex->flags() & ~Qt::ItemIsEditable);
        itemIndex->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_Commands->setItem(row, 0, itemIndex);

        ui->tableWidget_Commands->setItem(
            row, 1, new QTableWidgetItem(keyword));
        ui->tableWidget_Commands->setItem(
            row, 2, new QTableWidgetItem(path));
    }
}

void SettingChild_AppLauncher::saveToConfig()
{
    QJsonArray commands;
    for (int i = 0; i < ui->tableWidget_Commands->rowCount(); ++i)
    {
        const QString keyword =
            ui->tableWidget_Commands->item(i, 1)
                ? ui->tableWidget_Commands->item(i, 1)->text().trimmed()
                : QString();
        const QString path =
            ui->tableWidget_Commands->item(i, 2)
                ? ui->tableWidget_Commands->item(i, 2)->text().trimmed()
                : QString();
        if (keyword.isEmpty() || path.isEmpty())
            continue;

        QJsonObject obj;
        obj["keyword"] = keyword;
        obj["path"] = path;
        commands.append(obj);
    }

    ZcJsonLib config(JsonSettingPath);
    config.setValue("appLauncher/commands", commands);

    emit appLauncherConfigChanged();
}

void SettingChild_AppLauncher::on_pushButton_Add_clicked()
{
    bool ok = false;
    const QString keyword =
        QInputDialog::getText(this, "添加应用调用", "请输入触发关键词：",
                              QLineEdit::Normal, QString(), &ok);
    if (!ok || keyword.trimmed().isEmpty())
        return;

    const QString path =
        QFileDialog::getOpenFileName(this, "选择应用或文件", QString(),
                                     "所有文件 (*.*);;可执行文件 (*.exe);;快捷方式 (*.lnk)");
    if (path.isEmpty())
        return;

    const int row = ui->tableWidget_Commands->rowCount();
    ui->tableWidget_Commands->insertRow(row);

    auto *itemIndex = new QTableWidgetItem(QString::number(row + 1));
    itemIndex->setFlags(itemIndex->flags() & ~Qt::ItemIsEditable);
    itemIndex->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_Commands->setItem(row, 0, itemIndex);

    ui->tableWidget_Commands->setItem(
        row, 1, new QTableWidgetItem(keyword.trimmed()));
    ui->tableWidget_Commands->setItem(
        row, 2, new QTableWidgetItem(path));

    saveToConfig();
}

void SettingChild_AppLauncher::on_pushButton_Delete_clicked()
{
    const int row = ui->tableWidget_Commands->currentRow();
    if (row < 0)
    {
        QMessageBox::information(this, "提示", "请先选中要删除的行。");
        return;
    }

    ui->tableWidget_Commands->removeRow(row);
    refreshTable();
    saveToConfig();
}

void SettingChild_AppLauncher::refreshTable()
{
    // 更新序号列
    for (int i = 0; i < ui->tableWidget_Commands->rowCount(); ++i)
    {
        auto *item = ui->tableWidget_Commands->item(i, 0);
        if (item)
            item->setText(QString::number(i + 1));
    }
}
