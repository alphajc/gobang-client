#ifndef CONNECTPLAYER_H
#define CONNECTPLAYER_H

#include <QTcpServer>
#include <QTime>
#include "gamesocket.h"

class ConnectPlayer:public QTcpServer
{
    Q_OBJECT
private:
    GameSocket *gameSocket;
    static ConnectPlayer *connectPlayer;
    ConnectPlayer();

public:
    static ConnectPlayer *getInstance();
    int setRadomPort();
    void setConnect();

public slots:
    void acceptConnection();

};

#endif // CONNECTPLAYER_H
