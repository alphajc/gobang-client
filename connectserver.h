#ifndef CONNECTSERVER_H
#define CONNECTSERVER_H

#include <QTcpSocket>

class ConnectServer:public QTcpSocket
{
    Q_OBJECT
private:
    void init();
    void newTCPConnect();//用于建立服务端与客户之间的连接函数
    static ConnectServer *connectServer;
    ConnectServer();
public:
    static ConnectServer *getInstance();
public slots:
    void displayError(QAbstractSocket::SocketError);
};

#endif // CONNECTSERVER_H
