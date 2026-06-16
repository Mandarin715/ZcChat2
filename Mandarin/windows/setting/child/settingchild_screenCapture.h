#ifndef SETTINGCHILD_SCREENCAPTURE_H
#define SETTINGCHILD_SCREENCAPTURE_H

#include <QWidget>

namespace Ui
{
class SettingChild_ScreenCapture;
}

class SettingChild_ScreenCapture : public QWidget
{
    Q_OBJECT

  public:
    explicit SettingChild_ScreenCapture(QWidget *parent = nullptr);
    ~SettingChild_ScreenCapture();

  signals:
    void screenCaptureConfigChanged();

  private slots:
    void on_BreadcrumbBar_breadcrumbClicked(QString breadcrumb,
                                            QStringList lastBreadcrumbList);
    void on_ToggleSwitch_ScreenCaptureEnable_toggled(bool checked);

  private:
    Ui::SettingChild_ScreenCapture *ui;
};

#endif //SETTINGCHILD_SCREENCAPTURE_H
