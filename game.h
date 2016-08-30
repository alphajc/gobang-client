#ifndef GAME_H
#define GAME_H

#include <QThread>
#include "gamesocket.h"

class Game : public QThread
{
    Q_OBJECT
public:
    Game(QWidget *parent = Q_NULLPTR);
    void init();
    void setConnect();
    QTcpSocket *getSocket();

protected:
    void run();

private:
    GameSocket *gameSocket;

public slots:
    void recvMessage();

};

#endif // GAME_H
