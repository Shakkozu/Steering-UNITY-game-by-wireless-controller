#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cclient.h"
#include "settingsdlg.h"
#include <QButtonGroup>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int timerID;


public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
    cClient client;
    QButtonGroup group;
public slots:

     void newData(QString text);
private slots:

    void ShowDialog();
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


    void AddButtonsToGroup();






  //  void on_ShootButton_released();

  //  void on_ShootButton_pressed();
//
    void on_ShootButton_clicked();

private:
    Ui::MainWindow *ui;
    QJsonObject package
    {
      {"Move_up",false},
      {"Move_down",false},
      {"Move_left",false},
      {"Move_right",false},
     { "Shoot",false},
     { "Reset",false},
     {"Message", "test"},
    };

};

#endif // MAINWINDOW_H
