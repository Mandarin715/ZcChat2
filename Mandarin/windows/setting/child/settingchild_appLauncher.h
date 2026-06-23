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
    void on_pushButton_add_clicked();

  private:
    Ui::SettingChild_AppLauncher *ui;
    void loadCommands();
    void saveCommands();
    void addCommandRow(int index, const QString &keyword, const QString &path);
};

#endif // SETTINGCHILD_APPLAUNCHER_H
