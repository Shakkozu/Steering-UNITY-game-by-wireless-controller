#ifndef CCLIENT_H
#define CCLIENT_H

#include <QObject>
#include<QTcpSocket>
#include <QHostInfo>
#include <QString>
#include <QDebug>
#include <QTimerEvent>
#include <QTimer>
#include <QTextCodec>
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>


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
        bool CheckConnection();
        void sendMessage(QString message);
        void sendMessage(QJsonObject package);
        void sendMessage(QString str, double val);
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
        QString m_IP;

        int m_port;
        int recievedCounter;

        struct sData
        {
            char str[30];
            double val = 0;

        };

        void SetUserName(QString str);
        void createTimer();


protected:
        void timerEvent(QTimerEvent *event);
};

#endif // CCLIENT_H
