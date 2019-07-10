#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cclient.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   // connect(&client,SIGNAL(newMessageReceived(QString)),this,SLOT(newData(QString)));
    connect(&client,SIGNAL(ConnectionFailed()),this,SLOT(RenewConnection()));


    connect(ui->actionSettings,SIGNAL(triggered(bool)),this,SLOT(ShowDialog()));

    AddButtonsToGroup();
    connect(&group, static_cast<void(QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonReleased),
            [=](QAbstractButton *button) {
        package["Reset"] = true;
        client.sendMessage(package);
    });

}

MainWindow::~MainWindow()
{
    client.Disconnect();
    delete ui;

}
void MainWindow::AddButtonsToGroup()
{
    group.addButton(ui->DownButton);
    group.addButton(ui->LeftButton);
    group.addButton(ui->RightButton);
    group.addButton(ui->UpButton);
}


void MainWindow::ReleaseSteeringButton()
{
    package["Reset"]=true;
    package["Message"]="Reset!";
    client.sendMessage(package);
    resetPackage();

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

void MainWindow::RenewConnection()
{
    bool isConnected=false;
    while(!isConnected)
    {
    ui->ChatText->addItem("Connection Lost, trying to renew the connection!");
   isConnected = client.connect2Server();
    Sleep(100);
    }
}
void MainWindow::newData(QString txt)
{

     ui->ChatText->addItem("Server: " + txt);
}

void MainWindow::resetPackage()
{
    package["Move_up"] = false;
    package["Move_down"]=false;
    package["Move_left"] = false;
    package["Move_right"]=false;
    package["Shoot"] = false;
    package["Reset"]=false;
    package["Message"]="";

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
    package["Reset"]=false;
    package["Message"]="ruszylem sie w gore";
    client.sendMessage(package);
    resetPackage();

}

void MainWindow::on_RightButton_pressed()
{

    //QString str = "Move_Right!";
    package["Move_right"] = true;
    package["Reset"]=false;
    package["Message"]="ruszylem sie w prawo";
    client.sendMessage(package);
    resetPackage();

}

void MainWindow::on_DownButton_pressed()
{
    package["Move_down"]=true;
    package["Reset"]=false;
     package["Message"]="ruszylem sie w dol";
    client.sendMessage(package);
    resetPackage();

}

void MainWindow::on_LeftButton_pressed()
{
    package["Move_left"]=true;
    package["Reset"]=false;
     package["Message"]="ruszylem sie w lewo";
    client.sendMessage(package);
    resetPackage();

}




void MainWindow::on_DisconnectButton_clicked()
{
    if(client.CheckConnection())
    {

        package["Message"]="Bye!";
        client.sendMessage(package);
        client.Disconnect();

        ui->ChatText->addItem("Disconnected From Server");
    }
    else ui->ChatText->addItem("Connection wasn't established, can't disconnect");


}

void MainWindow::on_ConnectButton_clicked()
{
    if(client.connect2Server())
    {
        package["Message"]="Hello";
        client.sendMessage(package);
        resetPackage();
       // client.sendMessage("Hello");
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
    package["Shoot"]=true;
    client.sendMessage(package);
}
