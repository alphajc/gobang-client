#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QAbstractSocket>

#include "connectserver.h"
#include "connectplayer.h"
#include "message.h"
#include "game.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void init();
    void setConnect();

private:
    Ui::MainWidget *ui;
    Game *game;
    ConnectServer *connectServer;
    ConnectPlayer *connectPlayer;

public slots:
    void recvMessage();
    void modifyState(QAbstractSocket::SocketState state);
    void operateMessages(Messages msg);
    void on_listPlayers_doubleClicked(const QModelIndex &index);
    void finishedConnection();
};

#endif // MAINWIDGET_H
