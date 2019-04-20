#ifndef CCLIENT_H
#define CCLIENT_H

#include <QObject>
#include<QTcpSocket>
#include <QHostInfo>
#include <QString>
#include <QDebug>
#include <QTimerEvent>
#include <QTimer>



class cClient : public QObject
{
    Q_OBJECT

    public:
    int m_timerId;
    QString userName;
    explicit cClient(QObject *parent = 0);

    public slots:
        QString getMessage();
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
         void newMessageReceived(QString txt);


    private:
        QTcpSocket m_socket;
        int m_port;
        QString m_IP;
        int recievedCounter;
        void SetUserName(QString str);

        void createTimer();

protected:
        void timerEvent(QTimerEvent *event);
};

#endif // CCLIENT_H
