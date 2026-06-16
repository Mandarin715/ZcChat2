#include "settingchild_screenCapture.h"
#include "ui_settingchild_screenCapture.h"

#include "../../../GlobalConstants.h"

#include "ZcJsonLib.h"

SettingChild_ScreenCapture::SettingChild_ScreenCapture(QWidget *parent)
    : QWidget(parent), ui(new Ui::SettingChild_ScreenCapture)
{
    ui->setupUi(this);

    ui->BreadcrumbBar->setTextPixelSize(25);
    ui->BreadcrumbBar->appendBreadcrumb("屏幕捕获设置");

    ZcJsonLib config(JsonSettingPath);
    ui->ToggleSwitch_ScreenCaptureEnable->setIsToggled(
        config.value("screenCapture/Enable", false).toBool());
}

SettingChild_ScreenCapture::~SettingChild_ScreenCapture()
{
    delete ui;
}

void SettingChild_ScreenCapture::on_BreadcrumbBar_breadcrumbClicked(
    QString breadcrumb, QStringList lastBreadcrumbList)
{
    Q_UNUSED(breadcrumb);
    Q_UNUSED(lastBreadcrumbList);
    ui->stackedWidget->setCurrentIndex(0);
}

void SettingChild_ScreenCapture::on_ToggleSwitch_ScreenCaptureEnable_toggled(
    bool checked)
{
    ZcJsonLib config(JsonSettingPath);
    config.setValue("screenCapture/Enable", checked);
    emit screenCaptureConfigChanged();
}
