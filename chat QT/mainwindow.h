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
   // void on_sendButton_released();
    void ShowDialog();
    void newData(QString text);

  //void on_downloadButton_released();
    void on_ConnectButton_clicked();
    void on_DisconnectButton_clicked();


    void on_UpButton_released();
    void on_UpButton_pressed();

    void on_RightButton_pressed();
    void on_RightButton_released();

    void on_DownButton_pressed();
    void on_DownButton_released();

    void on_LeftButton_pressed();
    void on_LeftButton_released();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H