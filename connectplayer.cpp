#include "connectplayer.h"
ConnectPlayer *ConnectPlayer::connectPlayer = NULL;

ConnectPlayer::ConnectPlayer()
{
}

ConnectPlayer *ConnectPlayer::getInstance()
{
    if(NULL == connectPlayer){
        connectPlayer = new ConnectPlayer();
    }

    return connectPlayer;
}

int ConnectPlayer::setRadomPort()
{
    QTime time = QTime::currentTime();
    qsrand(time.msec() + time.second() * 1000);

    int port = qrand() % (65536 - 1024) + 1024;

    while( !listen(QHostAddress::Any,port) )
        port = qrand() % (65536 - 1024) + 1024;



    return port;
}

void ConnectPlayer::setConnect()
{
    connect(this,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
}

void ConnectPlayer::acceptConnection()
{
    gameSocket->setSocket(nextPendingConnection());
}
