#ifndef CONNECTSERVER_H
#define CONNECTSERVER_H

#include <QTcpSocket>
#include <QModelIndex>
#include <QMessageBox>
#include <QHostAddress>

#include "message.h"
#include "messagehandle.h"
#include "connectplayer.h"

class ConnectServer:public QTcpSocket
{
    Q_OBJECT
private:
    MessageHandle *messageHandle;

    void init();
    void newTCPConnect();//用于建立服务端与客户之间的连接函数
    static ConnectServer *connectServer;
    ConnectServer();
public:
    static ConnectServer *getInstance();
    qint64 sendToServer(MessageType type, QVariant data);
    Messages recvFromServer();

public slots:
    void displayError(QAbstractSocket::SocketError);
};

#endif // CONNECTSERVER_H
