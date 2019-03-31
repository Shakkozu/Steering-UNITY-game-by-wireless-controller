#include "cclient.h"

cClient::cClient(QObject *parent) : QObject(parent),
    m_port(10000),m_IP("127.0.0.1"),recievedCounter(0),userName("Shakkozu")
{
     m_timerId = startTimer(2000);

}

void cClient::sendMessage(QString message)
{
    QByteArray inBytes;
    // if(connect2Server())
    // {
         inBytes = message.toUtf8();
         m_socket.write(inBytes.constData());
        // Disconnect();
     //}
    //sDatagram inp;
   // inBytes = message.toUtf8();
    //strcpy(inp.tab,inBytes.constData());
   //inp.cmdID=1;
   // m_socket.write((char*)&inp,sizeof(inp));
   // m_socket.write(inBytes.constData());
   // m_socket.write(inBytes.constData(),sizeof(inBytes));
   // Disconnect();

}

void cClient::SetData(QString ip, int port)
{
    m_port = port;
    m_IP = ip;
}

int cClient::getMessagesCount()
{
    sDatagram sType, response;
    connect2Server();
    QByteArray inBytes = NULL;
    strcpy(sType.tab,inBytes.constData());
    sType.cmdID = 2;
    m_socket.write((char*)&sType,sizeof(sType));
    if(m_socket.waitForBytesWritten())
    {
        if(m_socket.waitForReadyRead())
        {
            m_socket.read((char*)&response,sizeof(response));
        }
    }
    m_socket.disconnectFromHost();

    qDebug() <<response.val1;
    return response.val1;

}

QString cClient::getMessage(int id)
{
    if(connect2Server())
    {
    sDatagram request,response;
    request.cmdID =3;
    request.val1 = id;

    QByteArray inBytes = NULL;
   // QString str;
    strcpy(request.tab,inBytes.constData());
    m_socket.write((char*)&request,sizeof(request));
    if(m_socket.waitForBytesWritten())
    {
        if(m_socket.waitForReadyRead())
        {
           m_socket.read((char*)&response,sizeof(response));
        }

    }
    switch(response.cmdID)
    {
    case 2:
        break;
    case -1:
        qDebug() <<"Wrong communicat number!";
        strcpy(response.tab,inBytes.constData());
         m_socket.disconnectFromHost();
         return "Permission Denied! Wrong ID";
        break;
    }
    m_socket.disconnectFromHost();
   // strcpy(str,response.tab);
    //return str;
    return QString::fromUtf8(response.tab);
    }
    else return "Connection Failed!";
}

void cClient::check()
{
    int N = getMessagesCount();
    for(int id = recievedCounter+1; id<N; id++)
    {
        QString msg = getMessage(id);
        emit newMessageReceived(msg); // emits signal
        recievedCounter=id;

    }
}

bool cClient::connect2Server() //if connection has failed returns FALSE, else TRUE
{

    QHostInfo info = QHostInfo::fromName(m_IP);
    //sDatagram ramka,odpowiedz;

    m_socket.connectToHost(info.addresses().first(),m_port);
   // m_socket.write((char*)&ramka,sizeof(ramka));

    if(m_socket.waitForConnected())
    {
          qDebug() <<"connected to server";
       if(m_socket.waitForReadyRead(20))
       {


       }
       return true;
    }
    else return false;
    //m_socket.disconnect()

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
}
void cClient::SetUserName(QString str)
{
    userName = str;
}

void cClient::TimerEvent(QTimerEvent *event)
{
   if(event->timerId()==m_timerId)
   {
    check();
    killTimer(m_timerId);
    }

}


