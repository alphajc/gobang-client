#include "gamesocket.h"
#include <QDebug>

GameSocket * GameSocket::gameSocket = NULL;

GameSocket::GameSocket(){
    socket = new QTcpSocket();
}

GameSocket * GameSocket::getInstance()
{
    if(NULL == gameSocket){
        gameSocket = new GameSocket();
    }

    return gameSocket;
}

void GameSocket::setSocket(QTcpSocket *socket)
{
    this->socket = socket;
    emit setedSocket();
}

QTcpSocket *GameSocket::getSocket()
{
    return socket;
}

bool GameSocket::connectToHost(QStringList msg)
{
    socket->abort();
    socket->connectToHost(msg.at(0), msg.at(1).toInt());

    return true;
}

void GameSocket::displayError(QAbstractSocket::SocketError) //显示错误
{
    qDebug() << socket->errorString();
    socket->close();
}
