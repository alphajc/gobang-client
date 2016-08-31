#ifndef GAME_H
#define GAME_H

#include <QThread>
#include "gamesocket.h"

class Game : public QThread
{
    Q_OBJECT
public:
    Game(QWidget *parent = Q_NULLPTR);
    QTcpSocket *getSocket();

protected:
    void run();

private:
    GameSocket *gameSocket;
    void setConnect();

public slots:
    void recvMessage();
    void setSocketConnect();

};

#endif // GAME_H
