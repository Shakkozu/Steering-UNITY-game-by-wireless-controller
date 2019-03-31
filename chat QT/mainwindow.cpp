#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cclient.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    cClient client;
    ui->setupUi(this);
    connect(&client,SIGNAL(newMessageReceived(QString)),this,SLOT(newData(QString)));
    connect(ui->actionSettings,SIGNAL(triggered(bool)),this,SLOT(ShowDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::on_sendButton_released()
{
    QString str = ui->lineMsg->text();
    if(str == "\\total") // to check number of all messages send
    {
       ui->ChatText->addItem("Total number of messages send: " + QString::number(client.getMessagesCount()));
    }
    else
    ui->ChatText->addItem(client.userName+":"+ui->lineMsg->text());
    client.sendMessage(str);
    ui->lineMsg->setText("");

}*/
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

void MainWindow::newData(QString text)
{
    ui->ChatText->addItem(text);
}

/*void MainWindow::on_downloadButton_released()
{
    int id = ui->lineID->text().toInt();
    ui->ChatText->addItem("Server: "+client.getMessage(id));
    ui->lineID->setText("");
}*/





void MainWindow::on_UpButton_pressed()
{
    QString str = "Move_Up!";
    client.sendMessage(str);
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
    client.sendMessage(str);
}
void MainWindow::on_RightButton_released()
{
    QString str = "Reset";
    client.sendMessage(str);
}
void MainWindow::on_DownButton_released()
{
    QString str = "Reset";
    client.sendMessage(str);
}
void MainWindow::on_LeftButton_released()
{
    QString str = "Reset";
    client.sendMessage(str);
}
void MainWindow::on_UpButton_released()
{
    QString str = "Reset";
    client.sendMessage(str);
   // client.sendMessage(str);
}


void MainWindow::on_DisconnectButton_clicked()
{
    client.Disconnect();
    ui->ChatText->addItem("Disconnected From Server");
}
void MainWindow::on_ConnectButton_clicked()
{
    if(client.connect2Server())
    {
        ui->ChatText->addItem("Connected to server  IP:"
            + client.GetIp()+" PORT:" +QString::number(client.GetPort()));
    }
    else
    {
        ui->ChatText->addItem("Connection Failed");
    }
}