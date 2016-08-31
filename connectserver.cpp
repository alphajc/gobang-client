#include "connectserver.h"

ConnectServer * ConnectServer::connectServer = NULL;

void ConnectServer::init()
{
    newTCPConnect();
    messageHandle = MessageHandle::getInstance();

    connect(this,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

}

void ConnectServer::newTCPConnect()
{
    abort();
    connectToHost("192.168.5.128",5267);
}

ConnectServer::ConnectServer()
{
    init();
}

ConnectServer * ConnectServer::getInstance()
{
    if( NULL == connectServer ){
        connectServer = new ConnectServer();
    }

    return connectServer;
}

qint64 ConnectServer::sendToServer(MessageType type, QVariant data)
{

    Messages messages;
    messages.messageType = type;
    switch(type){
    case MESSAGE_TYPE_INVITATION:{
        messages.msg.append(localAddress().toString());
        messages.msg.append(data.toString().split("\t").at(0));
        ConnectPlayer *connectPlayer = ConnectPlayer::getInstance();
        messages.msg.append(QString("%1").arg(connectPlayer->setRadomPort()));
        break;
    }
    case MESSAGE_TYPE_REPLY:
        messages.msg.append(data.toStringList());
        break;
    default:;
    }

    QString dat = messageHandle->packageMesssages(messages);
    qDebug() << "sendToServer:" << dat;
    return write(dat.toLatin1().data(),dat.size());
}

Messages ConnectServer::recvFromServer()
{
    QString data = readAll();
    qDebug() << "recvFromServer:" << data;
    return messageHandle->analyzeMessages(data);
}

void ConnectServer::displayError(QAbstractSocket::SocketError) //显示错误
{
    qDebug() << errorString();
    close();
}
