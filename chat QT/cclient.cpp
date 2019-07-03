#include "cclient.h"
#include <QString>


cClient::cClient(QObject *parent) : QObject(parent),
    m_port(10000),m_IP("127.0.0.1"),recievedCounter(0),userName("Shakkozu")
{
    m_timerId = 0;

}

void cClient::sendMessage(QString message)  // IN UTF8
{
    QByteArray inBytes;
    inBytes.append(message.toUtf8());
    m_socket.write(inBytes.constData());
}

//Test purposes
void cClient::sendMessage(QJsonObject package)  // IN UTF8
{

    if(!package.isEmpty())
    {
    //creates a QJsonDocument from QJsonPackage
    QJsonDocument doc(package);
    QJsonDocument tst;
    //Converts QJsonDoc to QByteArray
     QByteArray inBytes = doc.toJson();


    //inBytes = inBytes.constData();
    qDebug() <<"inBytes: " << inBytes;
    qDebug() <<"inBytes.constData(): " <<inBytes.constData();
   // qDebug() <<"inBytes_constData: " << inBytes.constData();
    m_socket.write(inBytes.constData());
    //ZWRÓĆ UWAGĘ NA DANE WYSYŁANE (InBytes), i dojdź, jak przesłac je w formie inBytes.constData()
    }
}




void cClient::sendMessage(QString str, double val) //in UTF8
{

   /*
    *    sData temp;
    temp.val = val;
    strcpy(temp.str,qPrintable(str));
    //temp.messageLength = str.length();

     //double tab[5] = {2.32, 4.235, -865567.356346545, 52.234, 23.1208};
    QByteArray buffor (reinterpret_cast<const char*>(&temp), sizeof(temp));

*/
val=4;
     int strLen = str.length();
      QByteArray buffor(reinterpret_cast<const char*>(&strLen), sizeof(int));
     //int dataLen = buffor.size();
     //reinterpret_cast<target_type>(expression)
     //To send string,double,int, etc. To my QByteArray i need to convert it to byte type,
     //so i cast it to 'const char*', and then i relate to it's memory.

     //As first i will send to my buffor length of the string, that comes right after strLen

     //QByteArray buffor(reinterpret_cast<const char*>(&dataLen), sizeof(int));
     buffor.append(str.toUtf8());

     qDebug() <<str;
     qDebug() <<"rozmiar  ramki:  " <<buffor.size();
     m_socket.write(buffor.constData());
   //  m_socket.write((char*)&temp,sizeof(temp));


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

bool cClient::CheckConnection()
{
    if(m_socket.waitForConnected())
        return true;

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


