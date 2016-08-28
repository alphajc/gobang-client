#include "connectserver.h"

ConnectServer * ConnectServer::connectServer = NULL;

void ConnectServer::init()
{
    newTCPConnect();

    //readyRead()表示服务端发送数据过来即发动信号，接着revData()进行处理。
    connect(this,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

}

void ConnectServer::newTCPConnect()
{
    abort();
    connectToHost("127.0.0.1",5267);
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

void ConnectServer::displayError(QAbstractSocket::SocketError) //显示错误
{
    qDebug() << errorString();
    close();
}
