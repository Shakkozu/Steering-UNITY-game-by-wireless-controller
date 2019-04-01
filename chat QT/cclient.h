#ifndef CCLIENT_H
#define CCLIENT_H

#include <QObject>
#include<QTcpSocket>
#include <QHostInfo>
#include <QString>
#include <QDebug>
#include <QTimerEvent>
#include <QTimer>
//#include "mainwindow.h"


class cClient : public QObject
{
    Q_OBJECT
    int m_timerId;
    public:
    QString userName;
        explicit cClient(QObject *parent = 0);
        int getMessagesCount();
        QString getMessage();

        /*struct sDatagram
        {
          int cmdID;
          int val1;
          char tab[100];
        };
        */
    public slots:
        bool connect2Server();
        void sendMessage(QString message);
        void SetData(QString ip, int port);
        //**
        QString GetIp();
        int GetPort();
        //**
        void Disconnect();
        void check();

    signals:
      //  void newMessageRecieved(QString);
         void newMessageReceived(QString msg);


    private:
        //bool connect2Server();
        QTcpSocket m_socket;
        int m_port;
        //int m_timerId;
        QString m_IP;
        int recievedCounter;
        void SetUserName(QString str);
protected:
        void TimerEvent(QTimerEvent *event);
};

#endif // CCLIENT_H
