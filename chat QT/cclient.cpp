#include "cclient.h"
#include <QString>


cClient::cClient(QObject *parent) : QObject(parent),
    m_port(10000),m_IP("127.0.0.1"),recievedCounter(0),userName("Shakkozu")
{
   // QTimer *timer = new QTimer(this);
    //connect(timer,SIGNAL(timeout()),this,SLOT(check()));
   //timer->start(200);
    m_timerId = startTimer(10000);


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

/*int cClient::getMessagesCount()
{
    //sDatagram sType, response;
    connect2Server();
    QByteArray inBytes = NULL;
  //  strcpy(sType.tab,inBytes.constData());
   // sType.cmdID = 2;
  //  m_socket.write((char*)&sType,sizeof(sType));
    if(m_socket.waitForBytesWritten())
    {
        if(m_socket.waitForReadyRead())
        {
           // recievedCounter +=1;
            m_socket.read((char*)&response,sizeof(response));
        }
    }
    m_socket.disconnectFromHost();

    qDebug() <<response.val1;
    return response.val1;

}*/

QString cClient::getMessage()
{
    qDebug() <<"im in getmessage";
    QString  str = NULL;
    //if(connect2Server())
   // {
        while(!m_socket.atEnd())
        {
            //qDebug() <<"im in loop" <<str;
            QByteArray data = m_socket.read(100);//m_socket.read(100);

            str = QString::fromUtf8(data);

           // return str;
        }
        return str;
       // return str;
   // sDatagram request,response;
    //request.cmdID =3;
   // request.val1 = id;

 /*   QByteArray inBytes = NULL;
   // QString str;
   // strcpy(request.tab,inBytes.constData());
    m_socket.write(inBytes);
    if(m_socket.waitForBytesWritten())
    {
        if(m_socket.waitForReadyRead())
        {
           m_socket.read(inBytes.constData());
           qDebug <<QString::fromAscii(inBytes);
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
    else return "Connection Failed!";*/
//}
  //  return str;
}

void cClient::check()
{
    QString msg = NULL;
    qDebug() <<"im in check";
    if(m_socket.waitForReadyRead(1000))
    {
        recievedCounter +=1;
        msg = getMessage();
        qDebug() <<"signal send with val: " <<msg;
        emit newMessageReceived(msg);
    }

    //int N = getMessagesCount();
  /*TODO REMOVE
   *   for(int id = recievedCounter+1; id<N; id++)
    {

        QString msg = getMessage();
        emit newMessageReceived(msg); // emits signal
        recievedCounter=id;

    }TODO REMOVE*/
}

bool cClient::connect2Server() //if connection has failed returns FALSE, else TRUE
{

    QHostInfo info = QHostInfo::fromName(m_IP);
    m_socket.connectToHost(info.addresses().first(),m_port);

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
    qDebug() <<"im in timer!";
   if(event->timerId()==m_timerId)
   {
       qDebug() <<"im in timer!";
    //check();
    killTimer(m_timerId);
    }

}


