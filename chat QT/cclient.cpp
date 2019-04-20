#include "cclient.h"
#include <QString>


cClient::cClient(QObject *parent) : QObject(parent),
    m_port(10000),m_IP("127.0.0.1"),recievedCounter(0),userName("Shakkozu")
{
    m_timerId = 0;

}

void cClient::sendMessage(QString message) //in UTF8
{
    QByteArray inBytes;
    //inBytes.push_back(QByteArray::number(544));
    inBytes = message.toUtf8();
         m_socket.write(inBytes.constData());


}

void cClient::SetData(QString ip, int port)
{
    m_port = port;
    m_IP = ip;
}



QString cClient::getMessage()
{
    QString  str = NULL;
        while(!m_socket.atEnd())
        {

            QByteArray data = m_socket.read(100);

            str = QString::fromUtf8(data);

        }
        return str;
}

void cClient::check()
{
    QString msg = NULL;
    if(m_socket.waitForReadyRead(50))
    {
        recievedCounter +=1;
        msg = getMessage();
        qDebug() <<"signal send with val: " <<msg;
        emit newMessageReceived(msg);
    }
}

bool cClient::connect2Server() //if connection has failed returns FALSE, else TRUE
{
    createTimer();
    QHostInfo info = QHostInfo::fromName(m_IP);
    m_socket.connectToHost(info.addresses().first(),m_port);

    if(m_socket.waitForConnected())
    {
          qDebug() <<"connected to server";
       // sendMessage("Connected to server");
       if(m_socket.waitForReadyRead(20))
       {


       }
       return true;
    }
    else return false;
}

QString cClient::GetIp()
{
    return m_IP;
}

int cClient::GetPort()
{
    return m_port;
}

void cClient::Disconnect()
{
    m_socket.disconnectFromHost();
    killTimer(m_timerId);
}
void cClient::SetUserName(QString str)
{
    userName = str;
}

void cClient::createTimer()
{
    m_timerId = startTimer(150);
}

void cClient::timerEvent(QTimerEvent *event)
{

   if(event->timerId()==m_timerId)
   {
       check();
    }

}


