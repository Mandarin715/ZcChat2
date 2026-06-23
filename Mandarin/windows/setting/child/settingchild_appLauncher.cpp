#include "settingchild_appLauncher.h"
#include "ui_settingchild_appLauncher.h"

#include "../../../GlobalConstants.h"
#include "ZcJsonLib.h"

#include "ElaScrollPageArea.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

SettingChild_AppLauncher::SettingChild_AppLauncher(QWidget *parent)
    : QWidget(parent), ui(new Ui::SettingChild_AppLauncher)
{
    ui->setupUi(this);
    loadCommands();
}

SettingChild_AppLauncher::~SettingChild_AppLauncher()
{
    delete ui;
}

void SettingChild_AppLauncher::loadCommands()
{
    // 清空旧控件
    QLayout *layout = ui->verticalLayout_commands;
    while (QLayoutItem *item = layout->takeAt(0))
    {
        if (item->widget())
            item->widget()->deleteLater();
        delete item;
    }

    ZcJsonLib config(JsonSettingPath);
    const QJsonArray commands =
        config.value("appLauncher/commands", QJsonValue(QJsonArray())).toArray();

    for (int i = 0; i < commands.size(); ++i)
    {
        const QJsonObject obj = commands[i].toObject();
        const QString keyword = obj.value("keyword").toString();
        const QString path = obj.value("path").toString();

        addCommandRow(i, keyword, path);
    }

    // 末尾加 stretch
    qobject_cast<QVBoxLayout *>(layout)->addStretch();
}

void SettingChild_AppLauncher::addCommandRow(int index, const QString &keyword,
                                              const QString &path)
{
    auto *area = new ElaScrollPageArea(ui->widget_commandsContainer);
    auto *row = new QHBoxLayout(area);
    row->setContentsMargins(12, 4, 12, 4);

    // 序号标签
    auto *labelIndex = new QLabel(QString::number(index + 1), area);
    labelIndex->setFixedWidth(24);
    labelIndex->setStyleSheet("color: #888; font-size: 12px;");
    row->addWidget(labelIndex);

    // 关键词输入
    auto *editKeyword = new QLineEdit(keyword, area);
    editKeyword->setPlaceholderText("关键词（如：打开浏览器）");
    editKeyword->setMinimumWidth(160);
    row->addWidget(editKeyword, 3);

    // 路径输入
    auto *editPath = new QLineEdit(path, area);
    editPath->setPlaceholderText("文件路径或URL");
    row->addWidget(editPath, 5);

    // 浏览按钮
    auto *btnBrowse = new QPushButton("浏览", area);
    btnBrowse->setFixedWidth(50);
    connect(btnBrowse, &QPushButton::clicked, this, [this, editPath]() {
        const QString p = QFileDialog::getOpenFileName(
            this, "选择文件/应用", QString(),
            "所有文件 (*.*);;可执行文件 (*.exe);;快捷方式 (*.lnk)");
        if (!p.isEmpty())
            editPath->setText(p);
    });
    row->addWidget(btnBrowse);

    // 删除按钮
    auto *btnDelete = new QPushButton("✕", area);
    btnDelete->setFixedWidth(36);
    btnDelete->setStyleSheet(
        "QPushButton { color: #e44; font-weight: bold; border: none; }"
        "QPushButton:hover { color: #f00; }");
    connect(btnDelete, &QPushButton::clicked, this, [this, area]() {
        ui->verticalLayout_commands->removeWidget(area);
        area->deleteLater();
        saveCommands();
    });
    row->addWidget(btnDelete);

    // 输入变化时保存
    auto saveOnChange = [this](const QString &) { saveCommands(); };
    connect(editKeyword, &QLineEdit::textChanged, this, saveOnChange);
    connect(editPath, &QLineEdit::textChanged, this, saveOnChange);

    ui->verticalLayout_commands->insertWidget(
        ui->verticalLayout_commands->count() - 1, area); // 插到 stretch 前面
}

void SettingChild_AppLauncher::saveCommands()
{
    QJsonArray commands;
    QLayout *layout = ui->verticalLayout_commands;
    for (int i = 0; i < layout->count(); ++i)
    {
        QLayoutItem *item = layout->itemAt(i);
        if (!item || !item->widget())
            continue;

        // 从 ElaScrollPageArea 的子布局中提取
        QHBoxLayout *row = qobject_cast<QHBoxLayout *>(item->widget()->layout());
        if (!row || row->count() < 5)
            continue;

        auto *editKeyword = qobject_cast<QLineEdit *>(row->itemAt(1)->widget());
        auto *editPath = qobject_cast<QLineEdit *>(row->itemAt(2)->widget());
        if (!editKeyword || !editPath)
            continue;

        const QString kw = editKeyword->text().trimmed();
        const QString p = editPath->text().trimmed();
        if (kw.isEmpty() || p.isEmpty())
            continue;

        QJsonObject obj;
        obj["keyword"] = kw;
        obj["path"] = p;
        commands.append(obj);
    }

    ZcJsonLib config(JsonSettingPath);
    config.setValue("appLauncher/commands", QJsonValue(commands));
    emit appLauncherConfigChanged();
}

void SettingChild_AppLauncher::on_pushButton_add_clicked()
{
    // 直接加一个空行
    addCommandRow(ui->verticalLayout_commands->count() - 1, "", "");
    saveCommands();
}
