#include "gamesocket.h"
#include <QDebug>

GameSocket * GameSocket::gameSocket = NULL;

GameSocket::GameSocket(){}

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
}

QTcpSocket *GameSocket::getSocket()
{
    return socket;
}

bool GameSocket::connectToHost(QStringList msg)
{
    socket = new QTcpSocket();
    socket->connectToHost(msg.at(0), msg.at(1).toInt());

    return true;
}

void GameSocket::setConnect()
{
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void GameSocket::displayError(QAbstractSocket::SocketError) //显示错误
{
    qDebug() << socket->errorString();
    socket->close();
}
