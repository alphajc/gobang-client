#include "game.h"
#include <QDebug>

Game::Game(QWidget *parent)
{
    parent;
}

void Game::init()
{
    gameSocket = GameSocket::getInstance();
}

void Game::setConnect()
{
    connect(getSocket(), SIGNAL(readyRead()), this, SLOT(recvMessage()));
}

QTcpSocket *Game::getSocket()
{
    return gameSocket->getSocket();
}

void Game::run()
{
    init();
    setConnect();
}

void Game::recvMessage()
{
    QString data = getSocket()->readAll();
    qDebug() << data;
}
