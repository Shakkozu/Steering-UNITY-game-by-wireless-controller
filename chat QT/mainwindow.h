#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cclient.h"
#include "settingsdlg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    cClient client;
   // SettingsDlg dialog;


private slots:
    void on_sendButton_released();
    void ShowDialog();
    void newData(QString text);

    void on_downloadButton_released();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
