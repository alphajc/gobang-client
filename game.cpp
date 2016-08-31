#include "game.h"
#include <QDebug>

Game::Game(QWidget *parent)
{
    parent;
    gameSocket = GameSocket::getInstance();
}

void Game::setConnect()
{
    connect(gameSocket, SIGNAL(setedSocket()), this, SLOT(setSocketConnect()));
}

QTcpSocket *Game::getSocket()
{
    return gameSocket->getSocket();
}

void Game::run()
{
    setConnect();
}

void Game::recvMessage()
{
    QString data = getSocket()->readAll();
    qDebug() << data;
}

void Game::setSocketConnect()
{
    connect(getSocket(), SIGNAL(readyRead()), this, SLOT(recvMessage()));
    connect(getSocket(), SIGNAL(error(QAbstractSocket::SocketError)),gameSocket, SLOT(displayError(QAbstractSocket::SocketError)));
}
