#ifndef SETTINGCHILD_APPLAUNCHER_H
#define SETTINGCHILD_APPLAUNCHER_H

#include <QWidget>

namespace Ui
{
class SettingChild_AppLauncher;
}

class SettingChild_AppLauncher : public QWidget
{
    Q_OBJECT

  public:
    explicit SettingChild_AppLauncher(QWidget *parent = nullptr);
    ~SettingChild_AppLauncher();

  signals:
    void appLauncherConfigChanged();

  private slots:
    void on_BreadcrumbBar_breadcrumbClicked(QString breadcrumb,
                                            QStringList lastBreadcrumbList);
    void on_pushButton_Add_clicked();
    void on_pushButton_Delete_clicked();

  private:
    Ui::SettingChild_AppLauncher *ui;
    void loadFromConfig();
    void saveToConfig();
    void refreshTable();
};

#endif //SETTINGCHILD_APPLAUNCHER_H
