#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QAbstractSocket>
#include <QMessageBox>
#include <QHostAddress>
#include "connectserver.h"
#include "connectplayer.h"
#include "message.h"
#include "messagehandle.h"
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
    MessageHandle *messageHandle;

public slots:
    void recvMessage();
    void modifyState(QAbstractSocket::SocketState state);
    void operateMessages(Messages msg);
private slots:
    void on_listPlayers_doubleClicked(const QModelIndex &index);
};

#endif // MAINWIDGET_H
