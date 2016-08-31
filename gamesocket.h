#ifndef GAMESOCKET_H
#define GAMESOCKET_H

#include <QTcpSocket>

class GameSocket:public QObject
{
    Q_OBJECT
private:
    QTcpSocket * socket;
    static GameSocket * gameSocket;
    GameSocket();

public:
    static GameSocket * getInstance();
    void setSocket(QTcpSocket *socket);
    QTcpSocket *getSocket();
    bool connectToHost(QStringList msg);

public slots:
    void displayError(QAbstractSocket::SocketError);

signals:
    void setedSocket();
};

#endif // GAMESOCKET_H
