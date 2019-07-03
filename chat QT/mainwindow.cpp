#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cclient.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&client,SIGNAL(newMessageReceived(QString)),this,SLOT(newData(QString)));

    connect(ui->actionSettings,SIGNAL(triggered(bool)),this,SLOT(ShowDialog()));

}

MainWindow::~MainWindow()
{
    client.Disconnect();
    delete ui;

}
void MainWindow::AddButtonsToGroup()
{
    group.addButton(ui->ConnectButton);
    group.addButton(ui->DownButton,1);
    group.addButton(ui->LeftButton,2);
    group.addButton(ui->UpButton,3);
}
void MainWindow::ShowDialog()
{
    SettingsDlg dialog;
    QString _ip = client.GetIp();
    int _port = client.GetPort();
    dialog.SetData(_ip,_port);

    if(dialog.exec() == QDialog::Accepted)
    {
        _ip = dialog.GetIP();
        _port = dialog.GetPort();
        client.SetData(_ip,_port);
        client.Disconnect();
    }
}

void MainWindow::newData(QString txt)
{

     ui->ChatText->addItem("Server: " + txt);
}

//*****************buttons
/*void MainWindow::on_UpButton_pressed()
{
    QString str = "Move_Up!";
    client.sendMessage(str);
}*/
//Test purposes with JSON
void MainWindow::on_UpButton_pressed()
{
    package["Move_up"]=true;
    client.sendMessage(package);
}

void MainWindow::on_RightButton_pressed()
{

    QString str = "Move_Right!";
    client.sendMessage(str);
}

void MainWindow::on_DownButton_pressed()
{
    QString str = "Move_Down!";
    client.sendMessage(str);
}

void MainWindow::on_LeftButton_pressed()
{
    QString str = "Move_Left!";

    client.sendMessage(str,2.0);
}

void MainWindow::on_RightButton_released()
{
    //client.sData.message = "Reset";
    //client.sData.val = 1;
    QString str = "Reset";
    double val = 0.5;
    client.sendMessage(str,val);
}

void MainWindow::on_DownButton_released()
{
    QString str = "Reset";
    client.sendMessage(str);
}

void MainWindow::on_LeftButton_released()
{
    QString str = "Reset";
   // client.sendMessage(str);
    client.sendMessage(str,8.0);
}

void MainWindow::on_UpButton_released()
{
    QString str = "Reset";
   // client.sendMessage(str);

}

void MainWindow::on_DisconnectButton_clicked()
{
    if(client.CheckConnection())
    {
        client.sendMessage("Bye!");
        client.Disconnect();
        ui->ChatText->addItem("Disconnected From Server");
    }
    else ui->ChatText->addItem("Connection wasn't established, can't disconnect");


}

void MainWindow::on_ConnectButton_clicked()
{
    if(client.connect2Server())
    {
        ui->ChatText->addItem("Connected to server  IP:"
            + client.GetIp()+" PORT:" +QString::number(client.GetPort()));
       // client.sendMessage("Hello!");
    }
    else
    {
        ui->ChatText->addItem("Connection Failed");
    }

}


void MainWindow::on_ShootButton_clicked()
{
    client.sendMessage("Shoot!");
}
