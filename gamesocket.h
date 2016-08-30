#ifndef GAMESOCKET_H
#define GAMESOCKET_H

#include <QTcpSocket>

class GameSocket:public QObject
{
    Q_OBJECT
private:
    QTcpSocket *socket;
    GameSocket();
    static GameSocket * gameSocket;

public:
    static GameSocket * getInstance();
    void setSocket(QTcpSocket *socket);
    QTcpSocket *getSocket();
    bool connectToHost(QStringList msg);
    void setConnect();

public slots:
    void displayError(QAbstractSocket::SocketError);
};

#endif // GAMESOCKET_H
