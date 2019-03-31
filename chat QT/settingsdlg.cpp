#include "settingsdlg.h"
#include "ui_settingsdlg.h"

SettingsDlg::SettingsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDlg)
{
    ui->setupUi(this);

}

SettingsDlg::~SettingsDlg()
{
    delete ui;
}

void SettingsDlg::SetData(QString ip, int port)
{
    ui->linePort->setText(QString::number(port));
    ui->lineIp->setText(ip);

}
int SettingsDlg::GetPort()
{
    return ui->linePort->text().toInt();
}
QString SettingsDlg::GetIP()
{
    return ui->lineIp->text();
}
